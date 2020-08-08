#include "systick_init_header.h"

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               // 1) disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // 2) enable SysTick with core clock
}
// The delay parameter is in units of the 16 MHz bus clock
void SysTick_Wait(uint32_t delay){ 
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}

void SysTick_Wait1ms(uint32_t delay){
  uint32_t i;
  for(i=0; i<delay; i++){
    SysTick_Wait(16000);  // wait 1ms
  }
}
void portf_init()
{
	SYSCTL_RCGCGPIO_R |= 0x20;  // activate port F
  SysTick_Init();             // initialize SysTick timer
  GPIO_PORTF_DIR_R |= 0x0E;   // make PF1, 2 and 3 out
  GPIO_PORTF_AFSEL_R &= ~0x0E;// disable alt funct on PF1, 2 and 3
  GPIO_PORTF_DEN_R |= 0x0E;   // enable digital I/O on PF1,2 and 3
                              // configure PF1,2 and 3 as GPIO
  GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF
}
void Task1()
{
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x02;
}
void Task2()
{
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x04;
}
void Task3()
{
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R ^0x08;
}
