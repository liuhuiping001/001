#include "stm32f4xx.h"
#include "stdio.h"

uint8_t uart1_rx_buf[5];
uint8_t uart1_flag;
uint32_t uart1_count;

void Uart1_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
	//1.����ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	
	//2. �������Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9-->USART1_TX
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10-->USART1_TX
	
	
	//3.GPIO�˿ڳ�ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	//4.���ڲ�����ʼ��
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
    //5. ��ʼ���жϿ�����--NVIC
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn ; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0x02;  //��ռ���ȼ�2��0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0x02;    //��Ӧ���ȼ�2�� 0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd= ENABLE;      //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);   //�ж����ȼ������ʼ��
	
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�򿪴��ڿ����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�򿪴��ڽ����ж�
    
	//6.ʹ�ܴ���
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1

}

void USART1_IRQHandler(void)
{
    uint32_t i, uart_num = 0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{	
		uart1_rx_buf[uart1_count] = (char)USART_ReceiveData(USART1); //������
		if(uart1_rx_buf[0] == 0xaa)
		{
            uart1_count++ ;
		}
        if(uart1_count == 5)
        {
            uart1_count = 0;//��λ
            for(i = 0; i<4; i++)
                uart_num += uart1_rx_buf[i];
            
            uart_num = uart_num & 0xFF;//�����Ͱ�λ
            
            if(uart_num == uart1_rx_buf[4])
                uart1_flag = 1;//��λ����������
            else
                uart1_flag = 2;//��λ����������
        }  
	}
    else if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)//���ڿ����ж�������������ݰ� 
    {
        uart1_count = USART1->DR;//��ȡ�Ĵ������ж�
        uart1_count = 0;//��λ
    }
}

void Put_Char(USART_TypeDef* USARTx, uint16_t Data)
{	
	USART_SendData(USARTx,Data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); //�ȴ����ݷ���
}

uint16_t Get_Char(USART_TypeDef* USARTx)
{	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET); //�����ȴ���������
	return USART_ReceiveData(USARTx);
}

int fputc(int c, FILE *stream)//������������ں�
{
	USART_SendData(USART1,c); //��������
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return c;
}

int fgetc(FILE *stream)//�������������ں�
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return USART_ReceiveData(USART1);
}



