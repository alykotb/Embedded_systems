#ifndef CAN_H_
#define CAN_H_
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
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

#pragma RESET_MISRA("all")

#define not_received 0U
#define received 1U
#define ecu1_address    0x01U
#define ecu2_address    0x02U
#define ecu3_address    0x03U
#define object1         0x01U
#define object2         0x02U
#define filter_mask     0xfffffU
#define max_size        8U
extern tCANMsgObject g_sCANMsgObject1;
extern tCANMsgObject g_sCANMsgObject2;
extern uint8_t g_pui8Msg1[8];
extern uint8_t g_pui8Msg2[8];
extern  bool message_received;
void CAN_Init(void);
#endif





















