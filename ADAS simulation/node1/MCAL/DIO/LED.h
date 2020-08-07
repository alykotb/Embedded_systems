/*
 * LED.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Karim Sherif Aref
 */

#ifndef LED_H_
#define LED_H_

#pragma CHECK_MISRA("none")

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#pragma RESET_MISRA("all")

#define null 				 0U
#define RED_LED              0X02U
#define BLUE_LED 			 0x04U
#define GREEN_LED 			 0x08U


extern void LED_Init(void);
extern void LED_ON(uint8_t color);
extern void LED_OFF(void);


#endif
