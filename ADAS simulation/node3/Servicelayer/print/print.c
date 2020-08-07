/*
 * print.c
 *
 *  Created on: 20 Apr 2019
 *      Author: Aly
 */
#include "print.h"
void printnumber(uint8_t data)
{
    UARTprintf("%u\n",data);

}

void printstring(uint8_t* string)
{
    UARTprintf("%s\n",string);

}

