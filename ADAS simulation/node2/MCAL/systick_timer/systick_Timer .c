/*
 * Timer.c
 *
 *  Created on: May 24, 2019
 *      Author: Karim Sherif Aref
 */
#include "MCAL/systick_Timer/systick_Timer.h"



void SysTickIntHandler(void)
{

	pass_token();

}

void Timer_Init(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
    SysTickPeriodSet(SysCtlClockGet());


    IntMasterEnable();


    SysTickIntEnable();

    SysTickPeriodSet(16000000U);
    SysTickIntEnable();

}
