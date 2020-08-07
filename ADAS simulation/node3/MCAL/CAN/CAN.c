/*
 * CAN.c
 *
 *  Created on: May31, 2019
 *      Author: alykotb
 */


#include "CAN.h"



CAN_tx_object_t tx_objects[num_of_tx_objects]={\
                                               {\
                                                  .mail_box=1U,\
                                                  .controller=CAN0_BASE,\
                                               },\
                                               {\
                                                .mail_box=2U,\
                                                .controller=CAN0_BASE,\
                                               }\
                                           }; /*array of structures containing configuration of mail_boxes
                                                         used and they are mapped to the upper layer
                                                         to send each message on certain mailbox*/

CAN_rx_object_t rx_objects[num_of_rx_objects]=  {\
                                                 {\
                                                        .filter=0x3U,\
                                                        .mask=0xFFFFU,\
                                                        .rx_mail_box=3U,\
                                                        .Controller=CAN0_BASE,\
                                                 },\
                                                 {\
                                                     .filter=0x0U,\
                                                     .mask=0xFFFFU,\
                                                     .rx_mail_box=4U,\
                                                     .Controller=CAN0_BASE,\
                                                 },\
                                                  {\
                                                     .filter=0x5U,\
                                                     .mask=0xFFFFU,\
                                                     .rx_mail_box=5U,\
                                                     .Controller=CAN0_BASE,\
                                                 }\
                                             };/*array of structures containing configuration of mail_boxes
                                                         used and they are mapped to the upper layer
                                                         to receive each message on certain mailbox*/
uint8_t buffer[8U];
/**********************************************
Function Name:void CANIntHandler(void)
Inputs:NA
Outputs:NA
Re-entrancy:reentrant
synchronous:asycnronous
Description:This is the interrupt handler of can controller_0 it handles an interrupt occurs on the controller
 ********************************************/
void CANIntHandler(void)
{

    uint32_t Status;/*declaring a variable to/declaring a variable from the struct type*/
    tCANMsgObject received_CANMessage;/*declaring a variable from the struct type to be passed to tiva-ware function to get
                                        parameters of received frame*/
    CAN_rx_BUS_Pdu_t RX_pdu;/*declaring a variable from the struct type to be passed to upper layer API containing
                              necessary data about received frame*/

    received_CANMessage.pui8MsgData=buffer;/* letting the dataptr of the struct to point to a certain location
                                              in the memory to fill in it received data*/

    Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);/*declaring a variable from the struct type*/


    if(Status == CAN_INT_INTID_STATUS)/*if there is an error go here*/
    {

        Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        CANIntClear(CAN0_BASE,CAN_INT_INTID_STATUS );/*clearing the interrupt*/
    }
    else if((Status>= 0x01U)&&(Status<= 0x20U))

    {

        CANIntClear(CAN0_BASE,Status);/*clearing the interrupt*/
        CANMessageGet(CAN0_BASE,Status, &received_CANMessage,MSG_OBJ_TYPE_RX);/*get parameters of received frame using tiva-ware*/
        RX_pdu.bUS_ID=received_CANMessage.ui32MsgID;
        RX_pdu.pdu_rx_data=received_CANMessage.pui8MsgData;
        ECU_CAN_Receive(&RX_pdu);/*passing the BUS_ID received and data received to upper layer*/
    }
    else
    {
       /*MISRA*/

    }
}
/**********************************************
Function Name  :void CAN_Send(CAN_tx_BUS_Pdu_t* BUS_PDU, uint8_t Tx_object)
Inputs:1-BUS_PDU : it as a data structure containing parameters of message to be transmitted
         2-Tx_object: number of object in the array of transmit objects declared above to determine on which mail_box and

Outputs:no returns
Re-entrancy:re-entrant
synchronous:asynchronous
Description:this function passes the parameters of the message to transmitted to the hardware to make the data-frame
 *******************************************/



void CAN_Send(CAN_tx_BUS_Pdu_t* BUS_PDU, uint8_t Tx_object)
{
    tCANMsgObject Can_Message;
    uint32_t Ctrl;

    Can_Message.ui32MsgID = BUS_PDU->BUS_ID;
    Can_Message.ui32MsgLen = BUS_PDU->length;/*length of message to be transmitted*/
    Can_Message.pui8MsgData =BUS_PDU->pdu_tx_data;/*pointig to data to be transmitted*/
    Can_Message.ui32Flags = MSG_OBJ_TX_INT_ENABLE;/*enable an interrupt when transmission succeeds*/
     Ctrl=tx_objects[Tx_object].controller;

    CANMessageSet(Ctrl,tx_objects[Tx_object].mail_box,&Can_Message, MSG_OBJ_TYPE_TX);/*passing message frame to mailbox to be sent*/
}
/***********************************************
Function Name : void CAN_Init(void)
Inputs:NA
Outputs:NA
Re-entrancy:RE-entrant
synchronous:asynchronouse
Description:this function performs required initialisation for controller 0 to be used by software
 *******************************************/


void CAN_Init(void)
{
    uint8_t index0;
    tCANMsgObject reception_Message;
    uint32_t ctrl;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);/*enabling clock for GPIO port used BY can controller*/

     GPIOPinConfigure(GPIO_PB4_CAN0RX);
     GPIOPinConfigure(GPIO_PB5_CAN0TX); /*port e 4 and 5 pins are used as tx and rx for can*/


     GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);


     SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);/*enabling clock for can controller*/


     CANInit(CAN0_BASE);/*resetting all previous configurations of hardware objects*/



     CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000U);/* setting baud_rate to 500000*/

     CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);



      IntEnable(INT_CAN0);  /*Enable the CAN interrupt on the processor (NVIC).*/
      CANIntRegister(CAN0_BASE,(&CANIntHandler));
      CANEnable(CAN0_BASE); /*Enable the CAN for operation.*/


     for(index0=0U;index0<num_of_rx_objects;index0++)/*configuring receive objects*/

         {
           reception_Message.ui32MsgID =rx_objects[index0].filter; /*initia_lization of the id received by message object 1*/
           reception_Message.ui32MsgIDMask =rx_objects[index0].mask  ;
           reception_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE;/*to generate an interrupt when reception occurs on this mail_box*/
           reception_Message.ui32MsgLen =max_length;/*giving the message the maximum length and the software knows what
                                                       length is needed from each message*/
           ctrl=rx_objects[index0].Controller;
           CANMessageSet(ctrl, rx_objects[index0].rx_mail_box, &reception_Message, MSG_OBJ_TYPE_RX);
                                                                                                     /*setting parameters of the mail_ebox
                                                                                                      going to be used to receive a message*/

         }

}

