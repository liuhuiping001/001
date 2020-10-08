#ifndef H_Key_H
#define H_Key_H
#include "stm32f4xx.h"
#define key1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define key2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define key3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define key4 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)

void Key_Init(void);


#endif 

