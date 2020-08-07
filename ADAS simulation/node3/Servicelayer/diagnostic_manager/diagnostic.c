/*
 * diagnostic.c
 *
 *  Created on: 2 Jun 2019
 *      Author: Aly
// */


#include "diagnostic.h"
uint8_t response[len];


void Diag_service(uint8_t* data)
{
    if(data[byte_2]==Read_fault)
    {
        response[byte_1]=destination;
        response[byte_1]|=source_address<<4;
        response[byte_2]=error;
        comm_send(response,Diagnostic_sw_ID);
    }
    else if(data[byte_2]==Read_data)
    {
               response[byte_1]=destination;
               response[byte_1]|=source_address<<4;
               response[byte_2]=reading[data[byte_3]];
               comm_send(response,Diagnostic_sw_ID);

    }

else if(data[byte_2]==Clear_fault)
    {
      error=0;

    }
else if(data[byte_2]==Write_data )
{
  reading[byte_1]=data[byte_3];

}

else
{
    /*MISRA*/
}

}
