
#include <stdint.h>
#include "MCAL/UARTs/UART.h"
#include "application/token_ring/token_ring.h"

int main(void){
    LED_Init();
    UART_Init();
    Timer_Init();
    CAN_Init();
//    pass_token();


while(1)
{


 UART_POLLING();
}

}
