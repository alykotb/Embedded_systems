/*
 * LED.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Karim Sherif Aref
 */

#ifndef LED_H_
#define LED_H_


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


#define NULL 				 0U
#define RED_LED	  	    	 GPIO_PIN_1
#define BLUE_LED 			 GPIO_PIN_2
#define GREEN_LED 			 GPIO_PIN_3


extern void LED_Init(void);
extern void LED_ON(uint8_t color);
extern void LED_OFF(void);


#endif /* LED_H_ */
