#include "usart.h"


void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK|USART_CLK,ENABLE);
	
	//TX���ų�ʼ��
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//�����������
	GPIO_InitStruct.GPIO_Pin=USART_TX_PORT;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(USART_GPIO_PORT,&GPIO_InitStruct);
	
	//USART��ʼ��
	
	USART_InitStruct.USART_BaudRate=BAUD;//������
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//���� ����ģʽ
	USART_InitStruct.USART_Parity=USART_Parity_No;//��У��
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//1 λֹͣλ
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8λ����λ
	
	USART_Init(USART,&USART_InitStruct);
	//ʹ��USART
	USART_Cmd(USART,ENABLE);
}
//�����ֽ�
void USART_SendByte(uint8_t data)
{
	USART_SendData(USART,data);
	while(USART_GetFlagStatus(USART,USART_FLAG_TXE)==RESET);//�ȴ��������
}
//��������
void USART_SendArray(uint8_t *pData,uint8_t num)
{
	while(num--)
	{
		USART_SendByte(*pData++);
	}
}
//�����ַ���
void USART_SendStr(char *pData)
{
	while(*pData!='\0')
	{
		USART_SendByte(*pData++);
	}
}

//�ض���printf
int fputc(int ch,FILE *file)
{
	USART_SendByte(ch);
	return ch;
}

