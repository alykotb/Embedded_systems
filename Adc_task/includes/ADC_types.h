/*
 * ADC_types.h
 *
 *  Created on: 28 Aug 2019
 *      Author: Aly
 */
/*N.B: no clock pre-scaler for this ADC module in TIVA C*/

#ifndef INCLUDES_ADC_TYPES_H_
#define INCLUDES_ADC_TYPES_H_
#include "includes/Platform_Types.h"
#include "includes/Adc_Cfg.h"

typedef uint8 Adc_ChannelType;
typedef uint8 Adc_GroupType;
typedef uint16 Adc_ValueGroupType;;
typedef uint32  Adc_ConversionTimeType;/*permanently 8*/
typedef uint8  Adc_SamplingTimeType;/*permanently 8*/
typedef uint8 Adc_ResolutionType;
typedef uint8 Adc_GroupPriorityType;
typedef uint8 Adc_StreamNumSampleType;
typedef uint8 Adc_HwTriggerTimerType;/*permanently 8*/
typedef uint8 Adc_GroupDefType;
typedef enum
{
    HW_unit0=0x40038000U,
    HW_unit1=0x40039000U

}Adc_HwUnitIdType ;

typedef enum
{
   Init,
   Un_Init
}AdcUnitStateType;
typedef enum
{
    ADC_IDLE,
    ADC_BUSY,
    ADC_COMPLETED,
    ADC_STREAM_COMPLETED
}Adc_StatusType;

typedef enum
{
    ADC_TRIGG_SRC_SW,
    ADC_TRIGG_SRC_HW
}Adc_TriggerSourceType;

typedef enum
{
    ADC_CONV_MODE_ONESHOT,
    ADC_CONV_MODE_CONTINUOUS
}Adc_GroupConvModeType;
typedef enum
{
    ADC_STREAM_BUFFER_LINEAR,
    ADC_STREAM_BUFFER_CIRCULAR
}Adc_StreamBufferModeType;
typedef enum
{
    ADC_ACCESS_MODE_SINGLE,
    ADC_ACCESS_MODE_STREAMING
}Adc_GroupAccessModeType;
typedef enum
{
    ADC_HW_TRIG_RISING_EDGE,
    ADC_HW_TRIG_FALLING_EDGE,
    DC_HW_TRIG_BOTH_EDGES
}Adc_HwTriggerSignalType;
typedef enum
{
    ADC_PRIORITY_NONE,
    ADC_PRIORITY_HW,
    ADC_PRIORITY_HW_SW
}Adc_PriorityImplementationType;
typedef enum
{
    ADC_ALIGN_LEFT,
    ADC_ALIGN_RIGHT
}Adc_ResultAlignmentType;

typedef enum
{
ADC_GROUP_REPL_ABORT_RESTART,
ADC_GROUP_REPL_SUSPEND_RESUME
}Adc_GroupReplacementType;


typedef enum
{
AdcClkSrcPll,
AdcClkSrcPiosc
}Adc_ClockSourceType;

/*added type "vendor specific"*/
typedef enum
{
    ADC_TRIGGER_COMP0=0x1,
    ADC_TRIGGER_COMP1=0x2,
    ADC_TRIGGER_COMP2=0x3,
    ADC_TRIGGER_EXTERNA=0x4,
    ADC_TRIGGER_TIMER=0x5,
    ADC_TRIGGER_PWM0=0x6,
    ADC_TRIGGER_PWM1=0x7,
    ADC_TRIGGER_PWM2=0x8,
    ADC_TRIGGER_PWM3=0x9,
    ADC_TRIGGER_PWM_MOD0=0x0,  // PWM triggers from PWM0
    ADC_TRIGGER_PWM_MOD1=0x10
}Hw_Trig_SourceType;



/*
typedef enum
{


}AdcChannelRefVoltsrcHighType;
typedef enum
{


}AdcChannelRefVoltsrcLow;
*/
typedef struct
{
    Adc_ConversionTimeType AdcChannelConvTime;
    uint8  AdcChannelId;
    boolean  AdcChannelLimitCheck;
    uint64       AdcChannelLowLimit;
    uint8  AdcChannelRangeSelect;
    Adc_ResolutionType AdcChannelResolution;
    Adc_SamplingTimeType AdcChannelSampTime;
}AdcChannelConfigType;

/*added type "vendor specific"*/



typedef struct
{
    Adc_GroupAccessModeType AdcGroupAccessMode;
    Adc_GroupConvModeType   AdcGroupConversionMode;
    Adc_GroupType           AdcGroupId;
    Adc_GroupPriorityType   AdcGroupPriority;
    Adc_GroupReplacementType AdcGroupReplacement;
    Adc_TriggerSourceType    AdcGroupTriggSrc;
    Adc_HwTriggerTimerType   AdcHwTrigTimer;
    Adc_StreamBufferModeType AdcStreamingBufferMode;
    uint8                    AdcStreamingNumSamples;
    Adc_GroupDefType*         AdcGroupDefinition;
    Hw_Trig_SourceType        Hw_Trig_src;

}AdcGroupConfigType;


typedef struct
{
Adc_HwUnitIdType          AdcHwUnitId;
Adc_ClockSourceType       AdcClockSource;
AdcChannelConfigType*     AdcChannel;
AdcGroupConfigType*       AdcGroup;
}AdcHwUnitType;


typedef struct
{


AdcHwUnitType AdcHwUnit[NUM_of_HW_Units];

}AdcConfigSetType;


typedef struct
{

AdcConfigSetType AdcConfigSet;



}Adc_ConfigType;

//typedef struct
//{
//uint8 seq_index;
//uint8 sequencer;
//uint8 step;
//}Channel_To_Sequencer_mappingType;



#endif /* INCLUDES_ADC_TYPES_H_ */
