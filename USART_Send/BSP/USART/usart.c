#include "usart.h"


void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK|USART_CLK,ENABLE);
	
	//TX引脚初始化
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Pin=USART_TX_PORT;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(USART_GPIO_PORT,&GPIO_InitStruct);
	
	//USART初始化
	
	USART_InitStruct.USART_BaudRate=BAUD;//波特率
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//发送 接收模式
	USART_InitStruct.USART_Parity=USART_Parity_No;//无校验
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//1 位停止位
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8位数据位
	
	USART_Init(USART,&USART_InitStruct);
	//使能USART
	USART_Cmd(USART,ENABLE);
}
//发送字节
void USART_SendByte(uint8_t data)
{
	USART_SendData(USART,data);
	while(USART_GetFlagStatus(USART,USART_FLAG_TXE)==RESET);//等待发送完成
}
//发送数组
void USART_SendArray(uint8_t *pData,uint8_t num)
{
	while(num--)
	{
		USART_SendByte(*pData++);
	}
}
//发送字符串
void USART_SendStr(char *pData)
{
	while(*pData!='\0')
	{
		USART_SendByte(*pData++);
	}
}

//重定向printf
int fputc(int ch,FILE *file)
{
	USART_SendByte(ch);
	return ch;
}

