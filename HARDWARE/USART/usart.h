#ifndef __USART_H__
#define __USART_H__
#include "stm32f4xx.h" 

void Uart1_Init(uint32_t bound);
void Put_Char(USART_TypeDef* USARTx, uint16_t Data);	
uint16_t Get_Char(USART_TypeDef* USARTx);

#endif  
