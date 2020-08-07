/*
 * CAN_0_Transmit.c
 *
 *  Created on: May 19, 2019
 *      Author: Karim Sherif Aref
 */


#include "CAN_TRX.h"

TX_SW_to_HW_MAP_t Tx_MAP[NUM_of_TX_CAN_PDUS]=  {\
                                                {\
                                                  .SW_ID=0U,\
                                                  .Transmit_object=0U,\
                                                  .TX_BUS_ID=1U,\
                                                },\
                                                  {\
                                                      .SW_ID=1U,\
                                                      .Transmit_object=1U,\
                                                      .TX_BUS_ID=6U,\
                                                  }\
                                             };/*array of structures each contains parameters of tx_mapping between comm_service and MCAL*/
RX_SW_to_HW_MAP_t Rx_MAP[NUM_of_RX_CAN_PDUS]=  {\
                                                {\
                                                  .RX_BUS_ID=3U,\
                                                  .id_sw=0U,\
                                                },\
                                                  {\
                                                    .RX_BUS_ID=0U,\
                                                    .id_sw=2U,\
                                                  },\
                                                  {\
                                                    .RX_BUS_ID=5U,\
                                                    .id_sw=1U,\
                                                  }\
                                             };/*array of structures each contains parameters of rx_mapping between comm_service and MCAL*/

/**********************************************
Function Name : ECU_CAN_Transmit(Pdu_paramters_t* CAN_PDU_TX ,uint32_t Can_SW_ID )
Inputs: 1-CAN_PDU_TX: structure passed from upper layer contains pointer to data to be sent and length
          2-Can_SW_ID: which is used for mapping the id of software with can_bus id

Outputs:no returns
Re-entrancy:reentrant
synchronous:Asynch
Description:This function detects which transmit object is going to be used in the lower layer which a sw_object
 containing mail_box and controller used for this message and this function uses the sw_id to detect the bus_ID
 and transmit_object of the message by looping on the above tx_map array
 *******************************************/
void ECU_CAN_Transmit(Pdu_paramters_t* CAN_PDU_TX ,uint32_t Can_SW_ID )
{
 uint8_t   index1;
 CAN_tx_BUS_Pdu_t message;/*variable from struct to be passed to MCAL containing len,data,ID*/
 for(index1=0U;index1<NUM_of_TX_CAN_PDUS;index1++)/*looping on array ot tx_map to get the parameters
                                                   needed to be passed to lower layer for this tx_message*/

    {
     if(Tx_MAP[index1].SW_ID==Can_SW_ID)
     {
        break;
     }else{}

    }

message.pdu_tx_data = CAN_PDU_TX->Data;
message.length= CAN_PDU_TX->Length;
message.BUS_ID =Tx_MAP[index1].TX_BUS_ID;

CAN_Send(&message,Tx_MAP[index1].Transmit_object);
}



/**********************************************
Function Name :void  ECU_CAN_Receive(CAN_rx_BUS_Pdu_t*  Rx_pdu)
Inputs:1-Rx_pdu :structure contains data received and its bus ID
Outputs:no returns
Re-entrancy:reentrant
synchronous:Asynch
Description:this function is called by the lower layer when a message is received then it used the bus-id to
to detect from the mapping configuration which sw-id uses this bus id to pass the message to the comm_service
to be passed correctly to the application or service needing this message
 *******************************************/
void  ECU_CAN_Receive(CAN_rx_BUS_Pdu_t*  Rx_pdu)
{
     uint8_t index2;
	for(index2=0U;index2<NUM_of_RX_CAN_PDUS;index2++)
	{
	    if(Rx_pdu->bUS_ID==Rx_MAP[index2].RX_BUS_ID)/*looping on rx_map array to detect the sw_id of the message*/

	    {
	        comm_receive(Rx_pdu->pdu_rx_data,Rx_MAP[index2].id_sw);/*calling the comm_service layer to pass the received data
	                                                                and sw_id*/
	        break;
	    }
	    else{
	         /*MISRA*/
	        }
}
}
