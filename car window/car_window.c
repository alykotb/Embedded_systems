#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "driverlib/pwm.h"
#include "priorities.h"

 int z;
int zprev ;
int  znext;
extern uint32_t y;
uint32_t touch0,touch1,touch2,touch3,touch4,touch5;
extern uint32_t	sensval; 
extern xSemaphoreHandle xBinarySemaphore;
extern xSemaphoreHandle xBinarySemaphore1;
extern xQueueHandle myQueue;

	
 void windoworder(void *pvparameters){
	 uint32_t x;
	 y=0;
	 int temp;
	 
		xSemaphoreTake( xBinarySemaphore, 0 );
	    while(1)
 {
	 	xSemaphoreTake( xBinarySemaphore,portMAX_DELAY );
		
		 x=y;
	 int s;
	 
	 
s=x&0x40;
	 if (s==0x40)			//case of lock cancel passenger orders//
	{
		
      temp=x&0x8F;
			x=temp;
	;}
	int z;
			z=x;
if (x==0x5 || x==0x11){		
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,1);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,1);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);	
		/*driverup,passengerup*/
	}
else if(x==0x9 || x==0x21 ){ 
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,1);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);		/*driverup,passengerdown*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,1);}	
	/*ROM_PWMGenEnable(PWM0_BASE,PWM_GEN_0);
	ROM_PWMGenEnable(PWM0_BASE,PWM_GEN_1);*/ 
else if (x==0x6 || x==0x12 ) {
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,1);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,1);		/*driverdown,passengerup*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_3,0);	
	}
else if (x==0xA || x==0x22 ) {
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,1);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);		/*driverdown,passengerdown*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_3,1);	
	}
else if (x==0x1) {
	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,1);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);		/*driverup,passengeroff*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,0);	
}
	
else if (x==0x2) {
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,1);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);		/*driverdwon,passengeroff*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_3,0);	}
	
else if (x==0x4 ||x==0x10) {
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,0);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,1);		/*driveroff,passengerup*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_3,0);	}
else if (x==0x24) {
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,0);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,1);		/*driveroff,passengerup*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_3,0);	}
	
else if  (x==0x8 ||x==0x20) {
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,0);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);		/*driveroff,passengerdown*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_3,1);	
}
else if  (x==0x18 ) {
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_0,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,0);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);		/*driveroff,passengerdown*/
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_3,1);}
else {
ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);	
	ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);		
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,0);
}}}
 
 void onetouch(void *pvparamters){
 	
	 zprev=0;
	 
	 int t; int t1,t2,t3;
	    while(1)
 {
		xSemaphoreTake( xBinarySemaphore1,portMAX_DELAY );
	
	 z=y;
	 t=z&0x40;
	 if(t==1) //case of lock cancel passenger window orders//
	 { z&=~(0x30); }
		
vTaskDelay(500/portTICK_RATE_MS);
	
	 znext=y ;
	t1=zprev&0x1;
	 t2=z&0x1;
	t3=znext&0x1;
	 
		if(t1==0)
			{ if  (t2==1){
				if(t3==0){
			
				
				ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,1);}
			else{} }
			else {}
			}
		 t1=zprev&0x2;
	 t2=z&0x2;
	t3=znext&0x2;
			if(t1==0)
			{ if  (t2==1){
				if(t3==0){
			ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,1);}}}
	

			t1=zprev&0x4;
	 t2=z&0x4;
	t3=znext&0x4;

			 if(t1==0) {if(t2==1) { if(t3==0){
			ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,1);}}}
		 		 
			t1=zprev &0x8;
	 t2=z&0x8;
	t3=znext&0x8;
			
		 if(t1==0){if(t2==1) {if(t3==0){
			 ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,1);}}}
		 		 
			 t1=zprev&0x10;
	 t2=z&0x10;
	t3=znext&0x10;
			  
			  if(t1==0) {if(t2==1) {if(t3==0){
			  ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,1);}}}
			
				t1=zprev&0x20;
	 t2=z&0x20;
	t3=znext&0x20;
				
				if(t1==0) {if (t2==1) {if(t3==0){
		ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,1)	;}}}
	
	}
	z=zprev;
			

 }
			 
			 void limit_switches(void *pvparameters){
				    while(1)

				 {					 
																																					
		if(sensval==0x1)
{ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);}
		 else if(sensval==0x2)
{ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,0);}
	else if(sensval==0x4)
{ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);}
	else if(sensval==0x8)
{ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,0);}
else if(sensval==0x5)
{ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
	 ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);}
else if(sensval==0x9)
{ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0);
	 ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,0);}

else if(sensval==0xA){ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,0);
	 ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,0);}
else if(sensval==0x6){ ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_1,0);
	 ROM_GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0);}
else{} 
}
	}


																										
																																 
				 
		
	 
	 
	 


	