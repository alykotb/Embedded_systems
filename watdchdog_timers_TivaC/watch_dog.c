/*
 * watch_dog.c
 *
 *  Created on: 9 Aug 2019
 *      Author: Aly
 */
#include <stdint.h>
#include <tm4c123gh6pm.h>

void watch_dog_init(void)
{
    SYSCTL_RCGCWD_R|=0x1;
    while((SYSCTL_RCGCWD_R&&0x1)==0){}

    WATCHDOG0_LOAD_R=16000000-1;/*loaded by counts corresponding to one second*/
    WATCHDOG0_CTL_R=0;/*clearing the control register before writing to it*/
    WATCHDOG0_CTL_R|=0x2;/*enabling system reset*/
    WATCHDOG0_CTL_R|=0x1;/*enabling interrupt*/

//    NVIC_EN0_R|=1<<18;/*enabling NVIC for watch dog timer*/
}
void watch_dog_ISR(void)
{

    WATCHDOG0_ICR_R=0;/*writing any value clears the interrupt*/
}

