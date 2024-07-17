/*
 * alt_main.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Hamichev
 */

#ifndef INC_ALT_MAIN_H_
#define INC_ALT_MAIN_H_



#ifdef __cplusplus
extern "C"
{



#include <alt_Inc/alt_UART.h>
#include <alt_Inc/alt_GPIO.h>

void Ini_GPIO();
void Ini_UART();

void USART1_callback();
void USART2_callback();
void USART3_callback();
void UART5_callback();

#endif

int alt_main();
void alt_UART_IRQ(USART_TypeDef *uart);



#ifdef __cplusplus
}
#endif

#endif /* INC_ALT_MAIN_H_ */
