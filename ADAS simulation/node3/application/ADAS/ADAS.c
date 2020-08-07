/*
 * app.c
 *
 *  Created on: 20 Apr 2019
 *      Author: Aly
 */



#include "application/ADAS/ADAS.h"
uint8_t* command[5U]={"error","fire_air_bag","brake","dec.spead","maintain"};
uint8_t error=0;
uint8_t reading[lenght]={0,0};

void app(uint8_t * data)
{
        reading[0U]=data[0U];
        reading[1U]=data[1U];
        if(data[1U]==0U)
        {
            error++;
        }else
        {
            /*MISRA*/
        }

    printstring("distance");
	printnumber(data[0U]);
	 printstring("command");
printstring(command[data[1U]]);
}


