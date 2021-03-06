#ifndef UART_H_
#define UART_H_

#include "stm32l1xx.h"
#include <stdlib.h>
#include <string.h>

#define BufferSize 32



void uart_gpio_init(void);
void USART_Init(USART_TypeDef * USARTx);
void USART_Write(USART_TypeDef * USARTx, uint8_t * buffer, int nBytes);
void USART_IRQHandler(USART_TypeDef * USARTx,
											uint8_t * buffer,
											uint8_t * pRx_counter);

#endif // UART_H_