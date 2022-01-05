#include "stm32f10x.h"
 
int main (void)
{		
		RCC_DeInit();
		
		RCC_HSEConfig(RCC_HSE_ON); // Enable HSE
		RCC_PLLCmd(DISABLE); // Disable PLL
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);// PLL clock should be HSE x 9 = 72MHZ
		RCC_PLLCmd(ENABLE); // enable pll
		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{ }
		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
		/* Set HCLK, PCLK1, and PCLK2 to SCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); // HCLK is = SYSCLK 
		RCC_PCLK1Config(RCC_HCLK_Div2); // PCLK1 is 36MHZ
		RCC_PCLK2Config(RCC_HCLK_Div1); // PCLK2 is 72MHZ
		
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef GPIO_InitStruct;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOC, ENABLE);
		
		/* setup GPIO for LEDs */
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
		
		TIM_TimeBaseStructure.TIM_Prescaler = 0x1C1F;
		TIM_TimeBaseStructure.TIM_Period = 0x270F;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
		NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =4;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		TIM_Cmd(TIM1, ENABLE); // Start the Timer
	
		while(1)
		{
		}	
}

void TIM1_UP_IRQHandler()
{
		if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
		{
				TIM_ClearFlag(TIM1, TIM_FLAG_Update);
				GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)));
		}
}
