#include <stdint.h>
#include "tm4c123gh6pm.h"
void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait1ms(uint32_t delay);
void port_initialization();
void Task1();
void Task2();
void Task3();
void scheduler();