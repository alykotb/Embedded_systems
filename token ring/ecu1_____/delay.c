#include "delay.h"
void sysctl_init(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
}

void SimpleDelay(uint32_t seconds)
{   /* Delay cycles for 1 second*/
    static uint32_t ticks = 16000000U/3U ;
    uint32_t delay;

    delay = seconds *  ticks;

    SysCtlDelay (delay);
}






