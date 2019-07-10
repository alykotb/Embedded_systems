#include "systick_init_header.h"


int main()
{
	port_initialization();
	SysTick_Init();
	while (1)
	{
		scheduler();
	}
}