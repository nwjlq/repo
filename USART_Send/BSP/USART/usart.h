#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"
#include <stdio.h>
#define USART   							USART1
#define BAUD    							115200
#define USART_GPIO_CLK 				RCC_APB2Periph_GPIOA  
#define USART_CLK   					RCC_APB2Periph_USART1
#define USART_GPIO_PORT 			GPIOA
#define USART_TX_PORT   			GPIO_Pin_9


void USART_Config(void);
void USART_SendByte(uint8_t data);
void USART_SendArray(uint8_t *pData,uint8_t num);
void USART_SendStr(char *pData);
#endif

