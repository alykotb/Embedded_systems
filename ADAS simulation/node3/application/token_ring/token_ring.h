/*
 * token_ring.h
 *
 *  Created on: 24 May 2019
 *      Author: Aly
 */
#include"Servicelayer/comm/comm.h"
#include "MCAL/DIO/LED.h"
#include "MCAL/systick_timer/systick_timer.h"

#ifndef APP_TOKEN_RING_H_
#define APP_TOKEN_RING_H_

#define source_address 3U
#define destination_address 2U

#define token_value         0U
#define data_size           3U

#define token_ring_data {source_address, destination_address,token_value}

extern void receivetoken(void);
extern void pass_token(void);

#endif /* APP_TOKEN_RING_H_ */
