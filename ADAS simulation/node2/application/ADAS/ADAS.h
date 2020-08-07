/*
 * app_execution.h
 *
 *  Created on: 19 Apr 2019
 *      Author: Aly
 */

#ifndef APPLICATION_ADAS_ADAS_H_
#define APPLICATION_ADAS_ADAS_H_
#include "application/STM/STM.h"
#include"Servicelayer/comm/comm.h"
#pragma CHECK_MISRA("none")

#include <stdint.h>
#include <stdlib.h>

#pragma RESET_MISRA("all")


#define conversion_number       0.75
#define bias                    7.5
#define UpperRangeLimit         90
#define LowerRangeLimit         25
#define Maintain_Lower_Range    50
#define Convert_value           10
#define Distance 0U
#define control_command 1U
#define lenght 2U
#define init 0U
typedef float Float_32;

extern uint8_t error;
extern uint8_t reading[lenght];


extern void app_exec(uint8_t Range);



#endif /* APPLICATION_ADAS_ADAS_H_ */
