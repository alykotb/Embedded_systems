
#include <stdint.h>
#include "MCAL/UARTs/UART.h"
#include "application/token_ring/token_ring.h"
#include "MCAL/systick_timer/systick_timer.h"

int main(void){
    LED_Init();
    UART_Init();
    Timer_Init();
    CAN_Init();


while(1)
{

 Diag_service();

}

}
