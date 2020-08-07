/*
 * CAN.h
 *
 *  Created on: Mar 18, 2019
 *      Author: Karim Sherif Aref
 */

#ifndef CAN_0_H_
#define CAN_0_H_



#include "stdbool.h"
#include <stdint.h>
#include "driverlib/can.h"
#include <stdbool.h>
#include <stdint.h>
#include "../../Servicelayer/comm_stack/comm_stack_types.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "MCAL/DIO/LED.h"
#include "can_cfg.h"
#include "ECU_AL/ECU_CAN/CAN_TRX.H"

#define num_of_tx_objects   2U
#define num_of_rx_objects   3U

#define max_length          8U







extern void CAN_Init(void);
extern void CAN_Send(CAN_tx_BUS_Pdu_t* BUS_PDU, uint8_t Tx_object);
extern void CANIntHandler(void);

#endif /* CAN */
