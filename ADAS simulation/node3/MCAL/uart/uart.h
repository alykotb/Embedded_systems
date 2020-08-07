/*
 * uart.h
 *
 *  Created on: 20 Apr 2019
 *      Author: Aly
 */

#ifndef UART_UART_H_
#define UART_UART_H_
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

extern void Init_uart(void);





#endif /* UART_UART_H_ */
