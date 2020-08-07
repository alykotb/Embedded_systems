/*
 * app_execution.c
 *
 *  Created on: 19 Apr 2019
 *      Author: Aly
 */
#include <application/ADAS/ADAS.h>

uint8_t error=0U;
 uint8_t reading[lenght]={0U,0U};

void  app_exec(uint8_t Range)
{
  static  uint8_t state;
  Float_32 distance_value=0;
  Float_32  decimal_val=0;
  uint8_t final_value=init;
  static struct  StateMachine* current_state=&ADAS_states[maintain];
  static uint8_t array[2U];
  decimal_val=(Float_32)Range;
  distance_value=(Float_32) ((conversion_number*decimal_val)-bias);
  final_value=(uint8_t)distance_value;

    if((Range > (uint8_t)UpperRangeLimit) || (Range < (uint8_t)LowerRangeLimit))
    {
    state =0U;

    }
    else
    {
        if(Range >= (uint8_t)Maintain_Lower_Range)
        {
            state=4U;
        }
        else{
             state= (uint8_t) (Range/(uint8_t)Convert_value);
             state--;
           }
    }

    current_state=current_state->possible_next_states[state];
    current_state->range=final_value;
    array[Distance]=current_state->range;
    array[control_command]=current_state->command;
    comm_send(array,ADAS_sw_ID);
}
