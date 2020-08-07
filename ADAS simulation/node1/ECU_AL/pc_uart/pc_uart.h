/*
 * pc_uart.h
 *
 *  Created on: 2 Jun 2019
 *      Author: Aly
 */

#ifndef ECU_AL_PC_UART_PC_UART_H_
#define ECU_AL_PC_UART_PC_UART_H_
#include"MCAL/UARTs/UART.h"
#include"Servicelayer/diagnostic_manager/diagnostic.h"

extern void UART_OutString(uint8_t *pt);
extern void UART_InString(char *bufPt, uint16_t max);


#endif /* ECU_AL_PC_UART_PC_UART_H_ */
