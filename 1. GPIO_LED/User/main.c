#include "stm32f10x.h"

 
void Delay(uint32_t nTime);

 
int main (void)
{
		GPIO_InitTypeDef GPIO_InitStruct;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
		
		GPIO_Init(GPIOC, &GPIO_InitStruct);
	
		// Config SysTick Timer
		if (SysTick_Config(SystemCoreClock / 1000))
		while (1);
		
    while (1)
    {

			GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
			Delay(2000);
			GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
			Delay(2000);

				
    }
}
 
// Timer code
static __IO uint32_t TimingDelay;
void Delay(uint32_t nTime){
		TimingDelay = nTime;
		while(TimingDelay != 0);
}
void SysTick_Handler(void){
	if (TimingDelay != 0x00)
		TimingDelay --;
}
