/*
 * print.h
 *
 *  Created on: 20 Apr 2019
 *      Author: Aly
 */

#ifndef PRINT_PRINT_H_
#define PRINT_PRINT_H_
#include <stdint.h>
#include"ECU_AL/PC_DISPLAY/uartstdio.h"


extern void printnumber(uint8_t data);
extern void printstring(uint8_t* string);


#endif /* PRINT_PRINT_H_ */
