#include "DIO.h"

/*void LED_ON(uint8_t pin);
void LED_OFF(uint8_t pin);
void  GPIOF_Handler(void);
void PORTF_init(void);*/
void  GPIOF_Handler(void);

uint8_t Toggle_flag=0U;


void  GPIOF_Handler(void)
{
    GPIOIntClear(GPIO_PORTF_BASE,SWITCHES);/*clearing the interrupt*/
    Toggle_flag=SET;      /*this flag is set here to let the application now that a switch has been pressed when
                            it comes to check it */
}


void PORTF_init(void)
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
/*the following MISRA errors are tiva_ware dependent initialisation*/

/* Unlock PF0 so we can change it to a GPIO input
Once we have enabled (unlocked) the commit register then re-lock it
to prevent further changes.  PF0 is MUXEED with NMI thus a special case.*/

HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
HWREG(GPIO_PORTF_BASE+ GPIO_O_CR) |= 0x01U;

HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0U;
GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,SWITCHES);/*configuring pins 0 & 4 of the switches to be input pins*/
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE ,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);/*configuring the pins responsible for led_s as output*/
GPIOPadConfigSet(GPIO_PORTF_BASE,SWITCHES,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);/*configuring them as pull up resistors*/
GPIOIntTypeSet(GPIO_PORTF_BASE,SWITCHES,GPIO_FALLING_EDGE); /*generating interrupt on sensing falling edge by any of the switches */
GPIOIntRegister(GPIO_PORTF_BASE,(&GPIOF_Handler));/*calling port_f handler in the startup didn't work so I was forced do use this function
                                                  which causes a MISRA error */
GPIOIntEnable(GPIO_PORTF_BASE,SWITCHES);/*enabling interrupt on our input pins*/
}

void LED_ON(uint8_t pin)
{   /*this API takes the number of the pin of the corresponding led light that is required to glow*/
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED,pin);
}

void LED_OFF(uint8_t pin)
{  /*this API takes the number of the pin of the corresponding led light that is required to be OFF*/
    GPIOPinWrite(GPIO_PORTF_BASE,pin,0U);
}

