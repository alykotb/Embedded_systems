/*
 * Timer.h
 *
 *  Created on: May 24, 2019
 *      Author: Karim Sherif Aref
 */

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "application/token_ring/token_ring.h"
#include "MCAL/DIO/LED.h"


extern void Timer_Init(void);



#endif /* MCAL_TIMER_H_ */
