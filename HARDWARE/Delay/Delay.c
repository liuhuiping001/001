#include"Delay.h"

void Delay_us(u32 i)	 //�򵥵���ʱ����
{
	SysTick_count = i;
	SysTick_Config(168);//ʱ���趨1us��������	

	while(SysTick_count != 0);
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;//ʱ�ӹر�
}


void Delay_ms(u32 i)	
 {
	SysTick_count = i;
	SysTick_Config(168*1000);//ʱ���趨1ms��������	
	while(SysTick_count != 0);
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;//ʱ�ӹر�
 }
