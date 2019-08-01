//*****************************************************************************
//
// reload_interrupt.c - Example demonstrating the PWM interrupt.
//
// Copyright (c) 2010-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// This is part of revision 2.1.4.178 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "tm4c123gh6pm.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "PWM.h"

//*****************************************************************************
//
//! \addtogroup pwm_examples_list
//! <h1>PWM Reload Interrupt (reload_interrupt)</h1>
//!
//! This example shows how to setup an interrupt on PWM0.  This example
//! demonstrates how to setup an interrupt on the PWM when the PWM timer is
//! equal to the configurable PWM0LOAD register.
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - GPIO Port B peripheral (for PWM0 pin)
//! - PWM0 - PB6
//!
//! The following UART signals are configured only for displaying console
//! messages for this example.  These are not required for operation of the
//! PWM.
//! - UART0 peripheral
//! - GPIO Port A peripheral (for UART0 pins)
//! - UART0RX - PA0
//! - UART0TX - PA1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - INT_PWM0_0 - PWM0IntHandler
//
//*****************************************************************************

//*****************************************************************************
//
// The variable g_ui32SysClock contains the system clock frequency
//
//*****************************************************************************
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    uint32_t g_ui32SysClock;
#endif

//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

//*****************************************************************************
//
// Prints out 5x "." with a second delay after each print.  This function will
// then backspace, clear the previously printed dots, backspace again so you
// continuously printout on the same line.  The purpose of this function is to
// indicate to the user that the program is running.
//
//*****************************************************************************
void
PrintRunningDots(void)
{
    UARTprintf(". ");
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysCtlDelay(g_ui32SysClock / 3);
#else
    SysCtlDelay(SysCtlClockGet() / 3);
#endif
    UARTprintf(". ");
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysCtlDelay(g_ui32SysClock / 3);
#else
    SysCtlDelay(SysCtlClockGet() / 3);
#endif
    UARTprintf(". ");
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysCtlDelay(g_ui32SysClock / 3);
#else
    SysCtlDelay(SysCtlClockGet() / 3);
#endif
    UARTprintf(". ");
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysCtlDelay(g_ui32SysClock / 3);
#else
    SysCtlDelay(SysCtlClockGet() / 3);
#endif
    UARTprintf(". ");
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysCtlDelay(g_ui32SysClock / 3);
#else
    SysCtlDelay(SysCtlClockGet() / 3);
#endif
    UARTprintf("\b\b\b\b\b\b\b\b\b\b");
    UARTprintf("          ");
    UARTprintf("\b\b\b\b\b\b\b\b\b\b");
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    SysCtlDelay(g_ui32SysClock / 3);
#else
    SysCtlDelay(SysCtlClockGet() / 3);
#endif
}

//*****************************************************************************
//
// The interrupt handler for the for PWM0 interrupts.
//
//*****************************************************************************
void
PWM0IntHandler(void)
{
    //
    // Clear the PWM0 LOAD interrupt flag.  This flag gets set when the PWM
    // counter gets reloaded.
    //
    PWMGenIntClear(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_LOAD);

    //
    // If the duty cycle is less or equal to 75% then add 0.1% to the duty
    // cycle.  Else, reset the duty cycle to 0.1% cycles.  Note that 64 is
    // 0.01% of the period (64000 cycles).
    //
    if((PWMPulseWidthGet(PWM0_BASE, PWM_OUT_0) + 64) <=
       ((PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) * 3) / 4))
    {
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                         PWMPulseWidthGet(PWM0_BASE, PWM_GEN_0) + 64);
    }
    else
    {
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 64);
    }
}

//*****************************************************************************
//
// Configure PWM0 for a load interrupt.  This interrupt will trigger everytime
// the PWM0 counter gets reloaded.  In the interrupt, 0.1% will be added to
// the current duty cycle.  This will continue until a duty cycle of 75% is
// received, then the duty cycle will get reset to 0.1%.
//
//*****************************************************************************

main(void)
{

pwm_init();
pwm_parameters_set(4, 3/4);
pwm_enable();


    while(1)
    {

    }
}
