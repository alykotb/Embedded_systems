/*
 * token_ring.c
 *
 *  Created on: 24 May 2019
 *      Author: Aly
 */
#include "token_ring.h"
uint8_t passed_data[data_size]=token_ring_data;
uint8_t token_flag=0U;

/***********************************************
Function Name : void receivetoken(void)
Inputs:NA
Outputs:NA
Re-entrancy:REENTRANT
synchronous:Asynch
Description:this function is called when a token is received and it lights green led
and delays the token application for when second

********************************************/

void receivetoken(void)
{
 token_flag=1U;/*sets the token flag*/
 LED_ON(GREEN_LED);
 SysTickEnable();/*we called the MCAL here because we have no OS*/

 /*delay by interrupt*/

}
/***********************************************
Function Name : void pass_token(void)
Inputs:NA
Outputs:NA
Re-entrancy:reentrant
synchronous:Asynch
Description:this function is used to pass token after delay one second from receiving it
 ********************************************/
 void pass_token(void)
{
if(token_flag)/*checks that token is received*/
{

comm_send(passed_data,pass_token_sw_ID);
LED_OFF();

SysTickDisable();/*disables the timer as it is enabled to generate an interrupt after one second
                  when token is received again*/
}
else{
        /*MISRA*/
     }
token_flag=0U;/*resets token flag again*/

}
