/*
 * comm.c
 *
 *  Created on: 19 Apr 2019
 *      Author: Aly
 */
#include "Servicelayer/comm/comm.h"



Pdu_paramters_t PDU_TX;/*structure which contains data to be transmitted and its length*/

uint8_t Transmit_PDUs_length[num_of_tx_message]=TX_PDUs_len;/*array for the length of each message (no. of bytes)*/

/**********************************************
Function Name :
Inputs:1-tx_data:pointer to data to be sent
         2-sw_id: to know which app is sending the message
Outputs:no returns
Reentrancy:reentrant
synchronous:asynchronous
Description:this function sends the data and sw_id  to be transmitted*/
 /********************************************/

void comm_send(uint8_t *tx_data, uint32_t sw_id )
{
PDU_TX.Data=tx_data;
PDU_TX.Length=Transmit_PDUs_length[sw_id];

ECU_CAN_Transmit(&PDU_TX,sw_id);/*calling the Api of ECU_AL*/
}

/**********************************************
Function Name : void comm_receive(uint8_t *rx_data ,uint32_t rx_SW_ID )
Inputs:1-rx_data:pointer to data of received message
         2-rx_SW_ID: to detect message of which application
Outputs:no returns
Re-entrancy:reentrant
synchronous:Asynch
Description:It is called by lower layer and it passes the data to the required application depending on sw id
*******************************************/



void comm_receive(uint8_t *rx_data ,uint32_t rx_SW_ID )

{
    if(rx_SW_ID == pass_token_sw_ID)/*sequence of if conditions to detect which app or service needs the message*/
    {
        receivetoken();
    }
    else if(rx_SW_ID ==Diagnostic_sw_ID)
    {
        Diag_service(rx_data);
    }
    else{/*MISRA*/}

}


