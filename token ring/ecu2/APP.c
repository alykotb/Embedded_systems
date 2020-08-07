#include "delay.h"
#include "CAN.h"
#include "DIO.h"
#include "APP.h"

uint8_t ID[num_of_IDs]={ecu3_address,ecu1_address};


void APP(void)
{

    uint8_t address;

    g_pui8Msg1[1U]=ecu2_address;      /*the id of receive object of this ECU
                                        is considered our source address here*/




    for(;;)
      {  /*normal state*/
          if(message_received)
          {
                g_sCANMsgObject2.pui8MsgData = g_pui8Msg2;/*letting the data pointer of the structure g_sCANMsgObject2
                                                            to point to the array g_pui8Ms is  and fill the data field in it
                                                            when it is passed by reference to the API can_message_get*/

                CANMessageGet(CAN0_BASE,  object2 , &g_sCANMsgObject2, 0U);/*getting contents of received message*/
                g_pui8Msg1[0U]=g_pui8Msg2[0U]; /*received_token*/
                g_sCANMsgObject1.ui32MsgID=ID[g_pui8Msg2[0U]];  /*the index of element on id array is as the number of the token 0
                                                                  or 1 to toggle direction*/
                address=ID[g_pui8Msg2[0U]];/*the id is the destination address as it
                                                            will be received only by one node*/

                LED_ON(BLUE_LED);
                if(Toggle_flag)
                {
                   g_sCANMsgObject1.ui32MsgID=ID[g_pui8Msg2[0U]^direction2_token];/*if switch is pressed ID is toggled*/
                   address=ID[g_pui8Msg2[0U]^direction2_token];
                   g_pui8Msg1[0U]^=1U; /*toggle the token to inform next ECU to inverse direction*/
                   Toggle_flag=RESET;
                }else{
                         /*MISRA*/
                      }
                g_pui8Msg1[2U]=address;/*the id is the destination address as it
                                                            will be received only by one node*/
                SimpleDelay(second);
                CANMessageSet(CAN0_BASE, object1, &g_sCANMsgObject1, MSG_OBJ_TYPE_TX);/*requesting transmission*/
                LED_OFF(BLUE_LED);
                message_received=not_received;/*assigning it not received which is a zero MACRON  as to not come here again
                                               except when a message is got*/
              }else{
                      /*MISRA */
                   }
      }
}







