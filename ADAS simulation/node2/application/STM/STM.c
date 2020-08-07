/*
 * STM.c
 *
 *  Created on: 18 Apr 2019
 *      Author: Aly
 */
#include "STM.h"


struct StateMachine ADAS_states[NUM_of_states]=
{
 {.command=error_handle,.range=0U,.possible_next_states={&ADAS_states[error_handle],&ADAS_states[fire_air_bag],&ADAS_states[brake],&ADAS_states[dec_spead],&ADAS_states[maintain]}},
 {.command=fire_air_bag,.range=0U,.possible_next_states={&ADAS_states[fire_air_bag]}},
 {.command=brake,.range=0U,.possible_next_states={&ADAS_states[error_handle],&ADAS_states[fire_air_bag],&ADAS_states[brake],&ADAS_states[dec_spead],&ADAS_states[maintain]}},
 {.command=dec_spead,.range=0U,.possible_next_states={&ADAS_states[error_handle],&ADAS_states[fire_air_bag],&ADAS_states[brake],&ADAS_states[dec_spead],&ADAS_states[maintain]}},
 {.command=maintain,.range=0U,.possible_next_states={&ADAS_states[error_handle],&ADAS_states[fire_air_bag],&ADAS_states[brake],&ADAS_states[dec_spead],&ADAS_states[maintain]}},
};



