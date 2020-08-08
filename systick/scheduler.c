#include "systick_init_header.h"

void scheduler()
{
	Task1();
	Task2();
	Task3();
	SysTick_Wait1ms(1000);
	Task1();
	SysTick_Wait1ms(1000);
	Task1();
	Task2();
	SysTick_Wait1ms(1000);
	Task1();
	SysTick_Wait1ms(1000);

	
}