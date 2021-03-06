/*
 * diagnostic.h
 *
 *  Created on: 1 Jun 2019
 *      Author: Aly
 */

#ifndef APPLICATION_DIAGNOSTIC_DIAGNOSTIC_H_
#define APPLICATION_DIAGNOSTIC_DIAGNOSTIC_H_

#include "Servicelayer/comm/comm.h"
#include "ECU_AL/pc_uart/pc_uart.h"
#include <stdint.h>
#define len 3U
#define num_of_ecus 2U
#define destinations {2U,3U}
#define char_1 0U
#define char_2 1U
#define char_3 2U
#define char_4 3U
#define byte_1 0U
#define byte_2 1U
#define byte_3 2U
#define size1  4U
#define size2  1U

#define Read_fault 0x19U
#define Clear_fault 0x14U
#define Read_data   0x22U
#define Write_data  0x2EU
#define source_address 1U




extern void Diag_response(uint8_t* data_in);
extern void Diag_service(void);


#endif /* APPLICATION_DIAGNOSTIC_DIAGNOSTIC_H_ */
