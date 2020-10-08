#include"Delay.h"

void Delay_us(u32 i)	 //简单的延时函数
{
	SysTick_count = i;
	SysTick_Config(168);//时钟设定1us，并启动	

	while(SysTick_count != 0);
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;//时钟关闭
}


void Delay_ms(u32 i)	
 {
	SysTick_count = i;
	SysTick_Config(168*1000);//时钟设定1ms，并启动	
	while(SysTick_count != 0);
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;//时钟关闭
 }
