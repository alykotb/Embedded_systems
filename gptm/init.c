#include <stdint.h>
#include "tm4c123gh6pm.h"

void portb_init(){
  	GPIO_PORTB_LOCK_R  =0x4c4f434b;
	
	GPIO_PORTB_CR_R=0x40;
	SYSCTL_RCGCGPIO_R=0x02;
	GPIO_PORTB_AFSEL_R=0x40; 
	GPIO_PORTB_DEN_R =0x40;
	GPIO_PORTB_PCTL_R &=~0xF000000;
	GPIO_PORTB_PCTL_R =0x7000000;
	
	
}
void gptm0_init(){
	 SYSCTL_RCGCTIMER_R &=~0x01;
	TIMER0_CTL_R &=~0x01;
	TIMER0_CFG_R=0x0;
	TIMER0_TAMR_R=0X17;
	TIMER0_CTL_R&=~0x0C;
	TIMER0_CTL_R |=0x01;
}
float power (float x, int y){
	float z=1; float result;
while(y!=0){
	z=z*x;
	y++;
 result=z;}
return (1/result);}
float calc_frequency(){
				int lastedge; int thisedge; float freq;
	
	while (( TIMER0_RIS_R & 4)==0){}
		lastedge=TIMER0_TAR_R;
		TIMER0_ICR_R |=0x4;
		while ( (TIMER0_RIS_R & 4) ==0){}
			thisedge=TIMER0_TAR_R;
			TIMER0_ICR_R |=0x4;
			freq=1/((thisedge-lastedge)*62.5*(power(10,-9)));
			return freq;
}
void gptm1_init(){
	 SYSCTL_RCGCTIMER_R &=~0x02;
	TIMER1_CTL_R &=~0x01;
		TIMER1_CFG_R=0x0;
	TIMER1_TAILR_R=(0xFFFFFFFF/0X06);
	TIMER1_TAMR_R=18;
		TIMER1_CTL_R |=0x01; }
void portA_init(){
	SYSCTL_RCGCGPIO_R|=0x01;
	GPIO_PORTA_AFSEL_R&=~0x01; 
	GPIO_PORTA_DEN_R |=0X01;
}
void sqr_wave(){
	while ((TIMER1_RIS_R & 1) ==0){}
		GPIO_PORTA_DATA_R^=1;
		
	}
	
	
	
