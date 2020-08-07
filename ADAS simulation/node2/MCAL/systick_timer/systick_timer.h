/*
 * Timer.h
 *
 *  Created on: May 24, 2019
 *      Author: Karim Sherif Aref
 */

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_
#include "application/token_ring/token_ring.h"
#pragma CHECK_MISRA("none")

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "MCAL/DIO/LED.h"

#pragma RESET_MISRA("all")

extern void Timer_Init(void);
extern void SysTickIntHandler(void);



#endif /* MCAL_TIMER_H_ */
