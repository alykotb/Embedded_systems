/*
 * comm.h
 *
 *  Created on: 19 Apr 2019
 *      Author: Aly
 */

#ifndef COMM_COMM_H_
#define COMM_COMM_H_
#include <stdint.h>
#include "ECU_AL/ECU_CAN/CAN_TRX.H"
#include "application/token_ring/token_ring.h"
#include "application/ADAS/ADAS.h"
#include "Servicelayer/diagnostic_manager/diagnostic.h"
#include "application/token_ring/token_ring.h"

#define pass_token_sw_ID 0U
#define ADAS_sw_ID 2U
#define Diagnostic_sw_ID 1U

#define num_of_tx_messages        2U

#define pass_token_data_length 3U
#define Diagnostic_data_length    2U



#define TX_PDUs_len       {pass_token_data_length, Diagnostic_data_length}


extern void comm_send(uint8_t *tx_data, uint32_t sw_id );
extern void comm_receive(uint8_t *rx_data ,uint32_t rx_SW_ID );

#endif /* COMM_COMM_H_ */
