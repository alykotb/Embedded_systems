/*
 * pc_uart.c
 *
 *  Created on: 2 Jun 2019
 *      Author: Aly
 */
#include"ECU_AL/pc_uart/pc_uart.h"




void UART_OutString(uint8_t *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}

void UART_InString(char *bufPt, uint16_t max) {
int32_t lenght=0;
char character;
  character = UART_InChar();
  while(character != CR){
    if(character == BS){
      if(lenght){
        bufPt--;
        lenght--;
        UART_OutChar(BS);
      }
    }
    else if(lenght < max){
      *bufPt = character;
      bufPt++;
      lenght++;
      UART_OutChar(character);
    }else{}

    character = UART_InChar();
  }
  *bufPt = character;
}





