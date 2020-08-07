#pragma CHECK_MISRA("none")
#include <stdint.h>
#include "UART.h"
#include "tm4c123gh6pm.h"


uint8_t string[19U];
uint8_t letter[2U];
uint8_t data;

void UART_Init(void){
  SYSCTL_RCGCUART_R |= 0x01;
  SYSCTL_RCGCGPIO_R |= 0x01;
  while((SYSCTL_PRGPIO_R&0x01) == 0){};
  UART0_CTL_R &= ~UART_CTL_UARTEN;
  UART0_IBRD_R = 8;
  UART0_FBRD_R = 44;

  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;
  GPIO_PORTA_AFSEL_R |= 0x03;
  GPIO_PORTA_DEN_R |= 0x03;

  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;
}


char UART_InChar(void){
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((char)(UART0_DR_R&0xFF));
}

void UART_OutChar(char character){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = character;
}


#pragma RESET_MISRA("all")












