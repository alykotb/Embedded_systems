/*
 * LED.c
 *
 *  Created on: Mar 18, 2019
 *      Author: Karim Sherif Aref
 */

#include "LED.h"

/*initialize LEDs*/
void LED_Init(void)
	{
    /* Enable the GPIO port that is used for the on-board LED.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    /* Enable the GPIO pins for the LED (PF2 & PF3)*/
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, BLUE_LED);
	}


void LED_ON(uint8_t color)
    {
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, color);
	}


void LED_OFF(void)
	{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, NULL);
	}

