#include "delay.h"
#include "CAN.h"
#include "DIO.h"
#include "APP.h"
int main(void);

main(void)
{
sysctl_init();
CAN_Init();
PORTF_init();

APP();



    return(0);
}
