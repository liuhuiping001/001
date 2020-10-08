#include "stm32f4xx.h" 
#include "Delay.h" 
#include "Led.h" 
#include "Key.h" 
#include "Beep.h" 
#include "exti.h"
#include "usart.h"
#include "stdio.h"
#include "timer6.h"

extern uint8_t uart1_rx_buf[5];
extern uint8_t uart1_flag;
extern uint32_t uart1_count;

int main(void)
{ 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //只做1次分组设置就ok
	Led_Init();
	Key_Init();
	Beep_Init();
	Exti_Init();
	Uart1_Init(115200);
    Timer6_Init();
    
	while(1)
	{
        ;
        /*if(uart1_flag != 0)
        {
            if(uart1_flag == 1)
                printf("ok\n");
            else if(uart1_flag == 2)
                printf("error\n");
            
            uart1_flag = 0;
        }*/
	}
}
 



