

/**
 * main.c
 */

#include <stdint.h>
#include "application/token_ring/token_ring.h"
#include "MCAL/uart/uart.h"
#include "driverlib/uart.h"
#include"MCAL/systick_timer/systick_timer.h"


int main(void){
    LED_Init();
    Timer_Init();
    CAN_Init();
    Init_uart();



while(1)
{

}

}
