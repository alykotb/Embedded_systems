

/**
 * main.c
 */
#include "stdint.h"
#include"tm4c123gh6pm.h"
#include "DMA.h"

extern uint32_t source[256];
extern uint32_t destination[256];

void main(void)
{
    uint16_t i;
    uint8_t x=0;
    x|=2;


    for(i=0;i<256;i++)
    {
        source[i]=i;

    }

    DMA_init();
    Enable_DMA();
    set_control_structure();
    TX_REQUEST();
    while(UDMA_ENASET_R && 0x40000000!=0){


              }

    while(1){

        for(i=0;i<256;i++)
           {
               source[i]++;

           }

        Enable_DMA();
        set_control_structure();
        TX_REQUEST();


        while(UDMA_ENASET_R && 0x40000000!=0){


           }
    }
//	return 0;
}
