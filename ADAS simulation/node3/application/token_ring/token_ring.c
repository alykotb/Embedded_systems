/*
 * token_ring.c
 *
 *  Created on: 24 May 2019
 *      Author: Aly
 */
#include "token_ring.h"
uint8_t passed_data[data_size]=token_ring_data;
uint8_t token_flag=0;

void receivetoken(void)
{
 token_flag=1;
 LED_ON(GREEN_LED);
 SysTickEnable();
 /*delay by interrupt*/
}
 void pass_token(void)
{
if(token_flag)
{

comm_send(passed_data,pass_token_sw_ID);
LED_OFF();
SysTickDisable();
}
token_flag=0;

}
