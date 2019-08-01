//*

#include <stdbool.h>
#include <stdint.h>
#include "PWM.h"


void
main(void)
{

pwm_init();
pwm_parameters_set(4, 3/4);
pwm_enable();


    while(1)
    {

    }
}
