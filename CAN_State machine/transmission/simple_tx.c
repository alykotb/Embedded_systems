//*****************************************************************************
//
// simple_tx.c - Example demonstrating simple CAN message transmission.
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
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

//*****************************************************************************
//
//! \addtogroup can_examples_list
//! <h1>Simple CAN TX (simple_tx)</h1>
//!
//! This example shows the basic setup of CAN in order to transmit messages
//! on the CAN bus.  The CAN peripheral is configured to transmit messages
//! with a specific CAN ID.  A message is then transmitted once per second,
//! using a simple delay loop for timing.  The message that is sent is a 4
//! byte message that contains an incrementing pattern.  A CAN interrupt
//! handler is used to confirm message transmission and count the number of
//! messages that have been sent.
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - CAN0 peripheral
//! - GPIO Port B peripheral (for CAN0 pins)
//! - CAN0RX - PB4
//! - CAN0TX - PB5
//!
//! The following UART signals are configured only for displaying console
//! messages for this example.  These are not required for operation of CAN.
//! - GPIO port A peripheral (for UART0 pins)
//! - UART0RX - PA0
//! - UART0TX - PA1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - INT_CAN0 - CANIntHandler
//
//*****************************************************************************

//*****************************************************************************
//
// A counter that keeps track of the number of times the TX interrupt has
// occurred, which should match the number of TX messages that were sent.
//
//*****************************************************************************
volatile uint32_t g_ui32MsgCount = 0;

//*****************************************************************************
//
// A flag to indicate that some transmission error occurred.
//
//*****************************************************************************
volatile bool g_bErrFlag = 0;

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
// This function provides a 1 second delay using a simple polling method.
//
//*****************************************************************************
void
SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}

//*****************************************************************************
//
// This function is the interrupt handler for the CAN peripheral.  It checks
// for the cause of the interrupt, and maintains a count of all messages that
// have been transmitted.
//
//*****************************************************************************
void
CANIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    //
    // If the cause is a controller status interrupt, then get the status
    //
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.  If the
        // CAN peripheral is not connected to a CAN bus with other CAN devices
        // present, then errors will occur and will be indicated in the
        // controller status.
        //
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        //
        // Set a flag to indicate some errors may have occurred.
        //
        g_bErrFlag = 1;
    }

    //
    // Check if the cause is message object 1, which what we are using for
    // sending messages.
    //
    else if(ui32Status == 1)
    {
        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 1, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 1);

        //
        // Increment a counter to keep track of how many messages have been
        // sent.  In a real application this could be used to set flags to
        // indicate when a message is sent.
        //
        g_ui32MsgCount++;

        //
        // Since the message was sent, clear any error flags.
        //
        g_bErrFlag = 0;
    }

    //
    // Otherwise, something unexpected caused the interrupt.  This should
    // never happen.
    //
    else
    {
        //
        // Spurious interrupt handling can go here.
        //
    }
}
//void portf_init()
//       {
//           SYSCTL_RCGCGPIO_R |= 0x20;  // activate port F
//                     // initialize SysTick timer
//         GPIO_PORTF_DIR_R |= 0x0E;   // make PF1, 2 and 3 out
//         GPIO_PORTF_AFSEL_R &= ~0x0E;// disable alt funct on PF1, 2 and 3
//         GPIO_PORTF_DEN_R |= 0x0E;   // enable digital I/O on PF1,2 and 3
//                                     // configure PF1,2 and 3 as GPIO
//         GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF
//       }


uint8_t Int_status;
uint8_t Int_flag;
#define SWITCHES GPIO_PIN_0|GPIO_PIN_4
#define RESET 0U
#define SET 1U
void  GPIOF_Handler(void)
{
    /*portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xBinarySemaphore,&xHigherPriorityTaskWoken);*/
    Int_status=GPIOIntStatus(GPIO_PORTF_BASE , false);
    GPIOIntClear(GPIO_PORTF_BASE,SWITCHES);
    Int_flag=SET;


   /* portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );*/
}
void PORTF_init(void)
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
HWREG(GPIO_PORTF_BASE+ GPIO_O_CR) |= 0x01;
HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,SWITCHES);
GPIOPadConfigSet(GPIO_PORTF_BASE,SWITCHES,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
GPIOIntTypeSet(GPIO_PORTF_BASE,SWITCHES,GPIO_FALLING_EDGE) ;
GPIOIntRegister(GPIO_PORTF_BASE,GPIOF_Handler);
GPIOIntEnable(GPIO_PORTF_BASE,SWITCHES);

}


//*****************************************************************************
//
// Configure the CAN and enter a loop to transmit periodic CAN messages.
//
//*****************************************************************************
int
main(void)
{
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    uint32_t ui32SysClock;
#endif

    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;

    pui8MsgData = (uint8_t *)&ui32MsgData;
    PORTF_init();



#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_OSC)
                                       25000000);
#else
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
#endif


    InitConsole();


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);


    GPIOPinConfigure(GPIO_PE4_CAN0RX);
    GPIOPinConfigure(GPIO_PE5_CAN0TX);


    GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);


    CANInit(CAN0_BASE);

#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
    CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
#else
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
#endif

    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);


    IntEnable(INT_CAN0);



    CANIntRegister(CAN0_BASE,CANIntHandler);
    CANEnable(CAN0_BASE);

    ui32MsgData = 0;
    sCANMessage.ui32MsgID = 1;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;

    while(1)
    {


        if(Int_flag)
        {

           Int_status/=16U;
           if(Int_status==0U||Int_status==1U)
           {
              *pui8MsgData=Int_status;
               CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);
               Int_flag=RESET;
           }else{}

        }else{}
        SimpleDelay();

    }


    return(0);
}
