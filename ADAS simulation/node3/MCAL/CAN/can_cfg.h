#ifndef CAN_cfg_0_H_
#define CAN_cfg_0_H_

#include "stdbool.h"
#include <stdint.h>







typedef struct
{
         uint32_t mail_box;
         uint32_t   controller;
} CAN_tx_object_t;

typedef struct
{
         uint32_t filter;
         uint32_t mask;
         uint32_t rx_mail_box;
         uint32_t   Controller;
} CAN_rx_object_t;

typedef struct
{
         uint8_t*           pdu_tx_data;
         uint8_t           length;
         uint32_t           BUS_ID;
} CAN_tx_BUS_Pdu_t;

typedef struct
{
         uint8_t*           pdu_rx_data;
         uint32_t           bUS_ID;
} CAN_rx_BUS_Pdu_t;

#endif
