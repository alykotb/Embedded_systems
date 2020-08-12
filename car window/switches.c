#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "drivers/buttons.h"
#include "driverlib/pwm.h"
#define  PINS0_6   0x7F 
#define  PINS0_3   0xF
#define PINS4_7    0xF0
void switches_init(void){
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	 GPIOIntDisable(GPIO_PORTB_BASE,PINS0_6); //* pin 6 is for the lock switch*//
	 ROM_GPIODirModeSet(GPIO_PORTB_BASE,PINS0_6,GPIO_DIR_MODE_IN);
	ROM_GPIOIntTypeSet(GPIO_PORTB_BASE,PINS0_6,GPIO_RISING_EDGE);
	ROM_GPIODirModeSet(GPIO_PORTB_BASE,PINS4_7 ,GPIO_DIR_MODE_OUT);
		GPIOIntEnable(GPIO_PORTB_BASE,PINS0_6);
}
void pwm0_init(void){
	 ROM_PWMGenDisable (PWM1_BASE,PWM_GEN_1);
	SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinConfigure(GPIO_PA7_M1PWM3);
										SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
										GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_7);
										PWMGenConfigure(PWM1_BASE, PWM_GEN_1,  PWM_GEN_MODE_DOWN   |PWM_GEN_MODE_NO_SYNC);
										 //driver window-pwm0//			
										ROM_PWMGenPeriodSet(PWM1_BASE,PWM_OUT_3,64000);
										ROM_PWMPulseWidthSet (PWM1_BASE,PWM_OUT_3,PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1) / 4);
									PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
										

}
	void pwm1_init(void){
		ROM_PWMGenDisable (PWM1_BASE,PWM_GEN_2);
		SysCtlPWMClockSet(SYSCTL_PWMDIV_2);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
		  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinConfigure(GPIO_PF0_M1PWM4);
			GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
			PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN  |PWM_GEN_MODE_NO_SYNC);
			//passenger window-pwm1//		
			ROM_PWMGenPeriodSet(PWM1_BASE,PWM_OUT_4,64000);
			ROM_PWMPulseWidthSet (PWM1_BASE,PWM_OUT_4,PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 4);
			PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, true);
			
	}
			void sensorsinit(void){
				  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
					GPIOIntDisable(GPIO_PORTD_BASE,PINS0_3);
						ROM_GPIODirModeSet(GPIO_PORTD_BASE,PINS0_3,GPIO_DIR_MODE_IN);
				ROM_GPIOIntTypeSet(GPIO_PORTD_BASE,PINS0_3 ,GPIO_RISING_EDGE);
					GPIOIntEnable(GPIO_PORTD_BASE,PINS0_3);
			}
				