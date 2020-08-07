#include"ECU_AL/Distance_sensor/Dist_sensor.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"

#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

#define UART_FR_TXFF            0x00000020
#define UART_FR_RXFE            0x00000010
#define UART_LCRH_WLEN_8        0x00000060
#define UART_LCRH_FEN           0x00000010
#define UART_CTL_UARTEN         0x00000001


extern void UART_Init(void);


extern char UART_InChar(void);


extern void UART_OutChar(char data);


extern void UART_OutString(char *pt);


extern uint32_t UART_InUDec(void);


extern void UART_OutUDec(uint32_t n);

uint32_t UART_InUHex(void);


extern void UART_OutUHex(uint32_t number);


extern void UART_InString(char *bufPt, uint16_t max);
extern void UART_POLLING(void);
