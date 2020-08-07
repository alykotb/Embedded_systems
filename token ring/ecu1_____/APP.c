#include "delay.h"
#include "CAN.h"
#include "DIO.h"
#include "APP.h"

uint8_t ID[num_of_IDs]={ ecu2_address , ecu3_address };


void APP(void)
{
    uint8_t address=ecu2_address;/*initialisation with ID received by ECU 2*/
    g_pui8Msg1[0U]=direction1_token ;/*initialisation of token by direction 1 */

    g_pui8Msg1[1U]=ecu1_address;  /*the id of receive object of this ECU
                          is considered our source address here*/

    SimpleDelay(delay*second);/*start_up state*/
    CANMessageSet(CAN0_BASE, object1 , &g_sCANMsgObject1, MSG_OBJ_TYPE_TX);/*requesting transmission of message object 1
                                                                            to trigger the token ring*/


    for(;;)
      {  /*normal state*/
          if(message_received)
          {
                g_sCANMsgObject2.pui8MsgData = g_pui8Msg2; /*let the data pointer member of the structure
                                                           g_sCANMsgObject2 to point on the g_pui8Msg2 array
                                                           to write in it the data field of the received message*/

                CANMessageGet(CAN0_BASE, object2 , &g_sCANMsgObject2, 0U);/*getting contents of received message*/
                g_pui8Msg1[0U]=g_pui8Msg2[0U]; /*received_token*/
                g_sCANMsgObject1.ui32MsgID=ID[g_pui8Msg2[0U]];/*the index of element on id array is as the number of the token 0
                                                                  or 1 to toggle direction*/

                LED_ON(BLUE_LED);/*turning the blue led on by passing Blue_LED mask to the function*/

                if(Toggle_flag)/*check if a switch is pressed*/
                {
                   g_sCANMsgObject1.ui32MsgID=ID[g_pui8Msg2[0U]^ direction2_token];/*if switch is pressed ID is toggled*/

                   address=ID[g_pui8Msg2[0U]^ direction2_token];

                   g_pui8Msg1[0U]^= direction2_token; /*toggle the token to inform next ECU to inverse direction*/

                   Toggle_flag=RESET;/*assigning zero to the flag as to not go here again unless
                                       the key is pressed again*/
                }else{
                         /*MISRA*/
                      }
                g_pui8Msg1[2U]=address;/*the id is the destination address as it
                                                            will be received only by one node*/
                SimpleDelay(second);
                CANMessageSet(CAN0_BASE, object1 , &g_sCANMsgObject1, MSG_OBJ_TYPE_TX);/*requesting transmission*/
                LED_OFF(BLUE_LED);/*turning the blue led off by passing Blue_LED mask to the function*/
                message_received=not_received;/*assigning it not received which is a zero MACRON  as to not come here again
                                               except when a message is got*/
              }else{
                      /*MISRA */
                   }
      }
}







