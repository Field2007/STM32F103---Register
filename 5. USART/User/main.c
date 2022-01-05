#include "stm32f10x.h"

 
void USART_PutChar(char c);
void USART_PutString(char *s);
uint16_t USART_GetChar(void);

int main (void)
{

    // Enable Peripheral Clocks

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |
														RCC_APB2Periph_AFIO |
														RCC_APB2Periph_GPIOA |
														RCC_APB2Periph_GPIOC, ENABLE);
 
		GPIO_InitTypeDef	GPIO_InitStruct;
		GPIO_StructInit(&GPIO_InitStruct);
	
	// Config PC13 for LED
		GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOC, &GPIO_InitStruct);
	
    // Initialize USART1_Tx
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
	
		// Initialize USART1_Rx
		GPIO_StructInit(&GPIO_InitStruct);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
		USART_InitTypeDef USART_InitStructure;
		//Initialize USART structure
		USART_StructInit(&USART_InitStructure);
		// Modify USART_InitStructure for non-default values , e.g.
		// USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_Cmd(USART1, ENABLE);
		
		USART_PutString("Hello, World!\n");
		
    while (1)
    {
				// Get a char from PC
        uint16_t data = USART_GetChar();
        if (data == 'L')
        {
            // If received char is 'H' then turn on orange LED
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
						USART_PutString(" - LED is OFF\n");
        }
        else if (data == 'H')
        {
            // If received char is 'L' then turn off orange LED
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
						USART_PutString(" - LED is ON\n");
        } 
    }
}
 

void USART_PutChar(char c)
{
    // Wait until transmit data register is empty
    while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
    // Send a char using USART1
    USART_SendData(USART1, c);
}

void USART_PutString(char *s)
{
    // Send a string
    while (*s)
    {
        USART_PutChar(*s++);
    }
}

uint16_t USART_GetChar(void)
{
    // Wait until data is received
    while (!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
    // Read received char
    return USART_ReceiveData(USART1);
}




