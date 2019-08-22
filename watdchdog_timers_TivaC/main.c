
/*
  main.c
 */
#include "watch_dog.h"
#include <stdint.h>
#include <tm4c123gh6pm.h>
 const int x=3;
 int (*func_ptr)(void);

 int* func(void)
 {
     return 0;
 }

 void func1(void)
 {
     *func();
     return;
 }
 int (*array_ptr)[5];

 int (*func_array[])();/*array of pointers to function*/
 int (*func_ptr_array())[];/*function returning pointer to array*/

int main(void)
{



    char array[5]={1,2,3,4,5};
    char *ptr;
    int x;
    int i;
    ptr=array;
    x=7;
    i=1;
    array[i--]=x;



    watch_dog_init();
    while(1)
    {
        GPIO_PORTA_DIR_R=1;

        /*trying to write in a register for a peripheral that clock is not gated to
                            so here software fails then, interrupt is not cleared  for watch dog timer
                            and hence reset occurs*/
    }
}
