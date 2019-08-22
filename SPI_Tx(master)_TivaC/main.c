

/**
 * main.c
 */
#include "systick_init_header.h"
#include "SPI.h"
#include<tm4c123gh6pm.h>
#include "stdint.h"

 uint8_t char_array[4]={'a','b','c','d',};
 uint8_t i=0;
int main(void)
{
//    uint8_t x;
//    x=0;
//    *(int*)0x2000021e=0;
    spi_init();
    SysTick_Init();
    while(1)
    {
        if(i==4)
        {
            i=0;
        }

        spi_write(char_array[i]);
        i++;
     SysTick_Wait1ms(1000);
    }

	return 0;
}
