#include "stm32f10x.h"

GPIO_InitTypeDef 					GPIO_InitStructure;

uint32_t Timingdelay;

void GPIO_Configuration(void);
void Dms_sys_noint(uint16_t time);
void SysTick_Configuration(void);

int main(void)
{
	SysTick_Configuration();
	GPIO_Configuration();
  while (1)
  {
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(1^GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)));
		Dms_sys_noint(3000);
  }
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Dms_sys_noint(uint16_t time)
	{
		Timingdelay = time;
		while(Timingdelay!=0)
			{
				while( (SysTick->CTRL&0x10000)==0x10000)
					{
						Timingdelay--;
					}
			}
	}
void SysTick_Configuration(void)
	{
		SysTick->VAL =0;
		SysTick->LOAD = 72000-1;	
		SysTick->CTRL = 0x00000005;

	}
