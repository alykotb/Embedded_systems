/*
 * P_W_M .C5535*
 *
 *  Created on: 31 Jul 2019
 *      Author: Aly
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"

void pwm_init(void)
{
    SYSCTL_RCGC0_R|=0x100000;/*enabling the clock for PWM module*/
    /*SYSCTL_RCC_R|=0x420000*//*using clock divisor if needed*/
    SYSCTL_RCGC2_R|=0x2;/*enabling clock for port B to  use PB6 as PWM pin*/
    PWM0_0_CTL_R&=~0x1;   /*disable  output for pwm0 to be initialised*/
    GPIO_PORTB_DEN_R|=0x40;/*PB6 as digital pin*/
    GPIO_PORTB_AFSEL_R|=0x40; /*choosing alternate function for PB6 */
    GPIO_PORTB_PCTL_R|=0x04000000;/*selecting the PWM function for PB6 as alternate function*/
    PWM0_0_CTL_R&=~0x2;/*configuring the counting mode to count down mode and enabling generator 0 to be clocked*/
    PWM0_0_GENA_R|=0x8C;/*drive low at action zero and drive high at cmpA match on counting down*/
    PWM0_0_CTL_R|=0x1;


}
void pwm_parameters_set(uint16_t period_in_ms,float duty_cycle)
{

    PWM0_0_LOAD_R=((period_in_ms*1000000)/62.5)-1;/*assigning the value of counts corresponding to periodic time*/
    PWM0_0_CMPA_R=(((period_in_ms*1000000)/62.5)-1)*(1-duty_cycle);/*setting the duty cycle of PWM */
}
void pwm_disable(void)
{
    PWM0_ENABLE_R&=~(0x1);
}
void pwm_enable(void)
{
    PWM0_ENABLE_R|=0x1;
}
