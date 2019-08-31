/*
 * Adc.h
 *
 *  Created on: 29 Aug 2019
 *      Author: Aly
 */

#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_


#include "includes/Std_types.h"
#include "includes/Adc_types.h"
#include "includes/Adc_Cfg.h"
#include  "includes/Firm_Ware.h"
#include  "includes/tm4c123gh6pm.h"
extern const Adc_ConfigType Adc_Config_Container;
extern void Adc_Init(const Adc_ConfigType* ConfigPtr);
extern void Adc_DeInit(void);





#endif /* INCLUDES_ADC_H_ */
