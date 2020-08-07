#include "CAN.h"

/*remove unwanted includes*/

void CANIntHandler(void);

tCANMsgObject g_sCANMsgObject1;
tCANMsgObject g_sCANMsgObject2;
uint8_t g_pui8Msg1[8U];
uint8_t g_pui8Msg2[8U];
/*we may make array containing data ext_erns here from app.c */

bool message_received=not_received;

/*if it is  without U suffix it will be implicit type conversion so it is INITIALIZED by a MACRON
to prevent implicit conversion*/



/*In this file I used U suffix with all values assigned to all unsigned types to prevent implicit conversion "MISRA" */

void CANIntHandler(void)
{
    uint32_t Status;
    /* the following API reads the can interrupt register*/
    Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    if(Status == CAN_INT_INTID_STATUS)
    {

        Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        /*it goes here if the interrupt is due to an error to it helps only to detect there is an error
          during debugging*/
    }
    else if(Status==object1)
    {
       /*if an interrupt is caused by message object 1 which is used in transmission so
        interrupt is due to successful transmission */

        CANIntClear(CAN0_BASE, object1);
    }
    else if(Status==object2)
    {
        /*if an interrupt is caused by message object 2 which is used in reception so
          interrupt is due to successful reception */
        CANIntClear(CAN0_BASE, object2);
        message_received=received;
    }
    else
    {
      /*MISRA*/
    }
}


void CAN_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);/*enabling clock for GPIO port used BY can controller*/

     GPIOPinConfigure(GPIO_PB4_CAN0RX);
     GPIOPinConfigure(GPIO_PB5_CAN0TX);


     GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);


     SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);/*enabling clock for can controller*/


     CANInit(CAN0_BASE);/*resetting all previous configurations of hardware objects*/



     CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000U);/* setting baud_rate to 500000*/

      CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);



      IntEnable(INT_CAN0);  /*Enable the CAN interrupt on the processor (NVIC).*/
      CANIntRegister(CAN0_BASE,(&CANIntHandler));
      CANEnable(CAN0_BASE); /*Enable the CAN for operation.*/

     g_sCANMsgObject1.ui32MsgID = ecu3_address ;/*initialisation of the id sent by message object 1*/
     g_sCANMsgObject1.ui32MsgIDMask = filter_mask;
     g_sCANMsgObject1.ui32Flags = MSG_OBJ_TX_INT_ENABLE;/*enabling interrupt for this object*/
     g_sCANMsgObject1.ui32MsgLen = sizeof(g_pui8Msg1);/*defining length of the message object*/
     g_sCANMsgObject1.pui8MsgData = g_pui8Msg1;/*letting data pointer of object   g_sCANMsgObject1 to  point to
                                                 array g_pui8Msg1 to take data from it */


     g_sCANMsgObject2.ui32MsgID =ecu2_address ; /*initia_lization of the id received by message object 1*/
     g_sCANMsgObject2.ui32MsgIDMask = filter_mask;/*letting the object to drop any frame with a different ID by taking all bits in
                                                 in consideration during filtering */
     g_sCANMsgObject2.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
     g_sCANMsgObject2.ui32MsgLen = max_size ;/*letting the message to receive maximum number of bytes*/

     /*now passing the structure of the message object parameters by reference to configure the 2nd message object*/
     CANMessageSet(CAN0_BASE, object2, &g_sCANMsgObject2, MSG_OBJ_TYPE_RX);
}
