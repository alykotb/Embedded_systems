/*
 * PWM.h
 *
 *  Created on: 1 Aug 2019
 *      Author: Aly
 */

#ifndef PWM_H_
#define PWM_H_

extern void pwm_init(void);
extern void pwm_parameters_set(uint16_t period_in_ms,float duty_cycle);
extern void pwm_disable(void);
extern void pwm_enable(void);

#endif /* PWM_H_ */
