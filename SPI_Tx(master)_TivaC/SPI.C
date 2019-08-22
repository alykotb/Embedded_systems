/*
 SPI.C
   Created on: 19 Aug 2019
       Author: Aly
 */
#include <SPI.h>
#include<stdint.h>


void spi_init(void)
{
    SYSCTL_RCGCSSI_R|=0x1; /*enable clock to SPI module 0*/
    while ((SYSCTL_RCGCSSI_R && 0x1)==0){}/*waiting till clock being enabled to SPI module 0*/
    SYSCTL_RCGCGPIO_R|=0x1;/*clocking port A*/
    while (( SYSCTL_RCGCGPIO_R && 0x1)==0){}/*waiting till clock being enabled for port A*/
    GPIO_PORTA_AFSEL_R|=0x3C;/*configuring pins A 2,3,4,5 for alternate function*/
    GPIO_PORTA_PCTL_R|=0x00222200;/*configuring pins A 2,3,4,5 to work for SSI/SPI*/
    GPIO_PORTA_DEN_R |=0x3C;/*configuring pins A 2,3,4,5 to work as digital pins*/
    SSI0_CR1_R=0x0;/*Master mode*/
    SSI0_CC_R=0x0;/*system clock is the clock source*/
    SSI0_CPSR_R=0x2;/*value of clock pre-scaler*/
    SSI0_CR0_R|=0x7C7;/*8-bit data size, free format frame,SP0=1,SPH=1, 1 MBPS data rate*/
    SSI0_CR1_R|=0x2;/*enabling the SPI*/
}

void spi_write(uint32_t data)
{

    SSI0_DR_R=data;

}


