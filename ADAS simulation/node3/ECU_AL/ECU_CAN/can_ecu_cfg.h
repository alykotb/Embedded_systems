/*
 * can_ecu_cfg.h
 *
 *  Created on: 27 May 2019
 *      Author: Aly
 */

#ifndef ECU_AL_CAN_ECU_CFG_H_
#define ECU_AL_CAN_ECU_CFG_H_
#include <stdint.h>

typedef struct
{
          uint32_t SW_ID;
          uint8_t Transmit_object;
          uint32_t TX_BUS_ID;
}TX_SW_to_HW_MAP_t;

typedef struct
{
          uint32_t id_sw;
          uint32_t RX_BUS_ID;
}RX_SW_to_HW_MAP_t;



#endif /* ECU_AL_CAN_ECU_CFG_H_ */
