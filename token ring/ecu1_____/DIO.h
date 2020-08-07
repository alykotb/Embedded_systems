#ifndef DIO_H_
#define DIO_H_

#pragma diag_push

#pragma CHECK_MISRA("none")

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
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"


#pragma RESET_MISRA("all")

#define RESET                0x0U
#define SET                  0x01U
#define RED_LED              0x02U
#define BLUE_LED             0x04U
#define GREEN_LED            0x08U
#define SWITCHES             0x11U
extern uint8_t Toggle_flag;
extern void LED_ON(uint8_t pin);
extern void LED_OFF(uint8_t pin);
extern void PORTF_init(void);
#endif

