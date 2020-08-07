/*
 * STM.h
 *
 *  Created on: 18 Apr 2019
 *      Author: Aly
 */
#ifndef APPLICATION_STM_STM_H_
#define APPLICATION_STM_STM_H_

#include <stdint.h>


#define NUM_of_states  5U
#define maintain       4U
#define dec_spead      3U
#define brake          2U
#define fire_air_bag   1U
#define error_handle   0U

struct StateMachine
{
uint8_t command;
uint8_t range;
struct StateMachine* possible_next_states [NUM_of_states];
};

extern struct StateMachine ADAS_states[NUM_of_states];

#endif

