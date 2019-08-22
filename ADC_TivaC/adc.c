/*
 * adc.c
 *
 *  Created on: 17 Jul 2019
 *      Author: Aly
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "tm4c123gh6pm.h"
void temp_sensor_init(void)
{
    SYSCTL_RCGCADC_R|=0x1U;
    SysCtlClockSet(SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                     SYSCTL_XTAL_16MHZ);
    ADC0_ACTSS_R&=~(0X8U);
    ADC0_EMUX_R&=~(0xF000);
    ADC0_SSCTL3_R&=~(0xFU);/*END*/
    ADC0_SSCTL3_R|=0xEU;
    ADC0_PSSI_R&=~(0x80000000);
    ADC0_SSPRI_R&=~(0x3000);
    ADC0_ACTSS_R|=0x8U;
}


