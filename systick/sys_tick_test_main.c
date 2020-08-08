#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick_init_header.h"

int main(void){
 port_initialization();
	SysTick_Init();  
  while(1){
    scheduler();    
	}
}
