/*
 * CAN_Transmit.h
 *
 *  Created on: May 19, 2019
 *      Author: Karim Sherif Aref
 */


#ifndef CAN_TRANSMIT_H_
#define CAN_TRANSMIT_H_

#include"can_ecu_cfg.h"
#include "MCAL/CAN/CAN.h"
#include "Servicelayer/comm_stack/comm_stack_types.h"
#include "Servicelayer/comm/comm.h"



#define NUM_of_TX_CAN_PDUS 2U
#define NUM_of_RX_CAN_PDUS 3U










extern void ECU_CAN_Transmit(Pdu_paramters_t* CAN_PDU_TX ,uint32_t  Can_SW_ID );

extern void ECU_CAN_Receive(CAN_rx_BUS_Pdu_t* Rx_pdu);

#endif /* CAN_0_TRANSMIT_H_ */
