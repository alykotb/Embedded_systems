/*
 * CAN.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Karim Sherif Aref
 */

#ifndef CAN_0_H_
#define CAN_0_H_
#include "can_cfg.h"
#include "ECU_AL/ECU_CAN/CAN_TRX.h"
#pragma CHECK_MISRA("none")

#include "stdbool.h"
#include <stdint.h>
#include "driverlib/can.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"

#pragma RESET_MISRA("all")


#define num_of_tx_objects   3U
#define num_of_rx_objects   2U
#define max_length          8U








extern void CAN_Init(void);
extern void CAN_Send(CAN_tx_BUS_Pdu_t* BUS_PDU, uint8_t Tx_object);
extern void CANIntHandler(void);

#endif /* CAN */
