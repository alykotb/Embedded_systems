/*
 * Adc_Cfg.h
 *
 *  Created on: 28 Aug 2019
 *      Author: Aly
 */

#ifndef INCLUDES_Adc_Cfg_H_
#define INCLUDES_Adc_Cfg_H_


#define HW_module0   1
#define HW_module1   0

#define NUM_of_HW_Units 1U
#define Num_HW_Unit0_Groups 2U
#define Num_of_all_groups   2U
#define Num_HWunit0Channels 3U
#define Num_of_all_Channels 3U
#define size_of_grp_seq_map0 2U
#define Num_of_seq_uint0     2U

#define Clk\
{0xf0003800};

#define NumOfGroupsPerHWunit\
{2U};

#define Channels_per_group\
{2,1};

#define Group_seq_map0\
{2,3};



#define CH_Seq_Map0\
{\
    {\
      .seq_index=0,\
      .sequencer=2,\
      .step=0,\
    },\
    {\
        .seq_index=0,\
        .sequencer=2,\
        .step=1,\
    },\
    {\
        .seq_index=1,\
        .sequencer=3,\
        .step=0,\
    },\
};


#define Adc_Config\
{.AdcConfigSet.AdcHwUnit=\
   {\
    {\
      .AdcHwUnitId=HW_unit0,\
      .AdcClockSource=AdcClkSrcPiosc,\
      .AdcChannel=HW_unit0_Channels,\
      .AdcGroup=HW_unit0_Groups,\
    }\
   }\
};


#define  HWunit0Groups\
{\
        {\
           .AdcGroupAccessMode=ADC_ACCESS_MODE_STREAMING,\
           .AdcGroupConversionMode=ADC_CONV_MODE_CONTINUOUS,\
           .AdcGroupId=2U,\
           .AdcGroupPriority=0U,\
           .AdcGroupReplacement=ADC_GROUP_REPL_ABORT_RESTART,\
           .AdcGroupTriggSrc=ADC_TRIGG_SRC_SW,\
           .AdcStreamingBufferMode=ADC_STREAM_BUFFER_LINEAR,\
           .AdcStreamingNumSamples=2U,\
           .AdcGroupDefinition=group0_channels,\
        },\
        {\
           .AdcGroupAccessMode= ADC_ACCESS_MODE_SINGLE,\
           .AdcGroupConversionMode=ADC_CONV_MODE_ONESHOT,\
           .AdcGroupId=3U,\
           .AdcGroupPriority=1U,\
           .AdcGroupReplacement=ADC_GROUP_REPL_ABORT_RESTART,\
           .AdcGroupTriggSrc=ADC_TRIGG_SRC_SW,\
           .AdcStreamingBufferMode=ADC_STREAM_BUFFER_LINEAR,\
           .AdcStreamingNumSamples=1U,\
           .AdcGroupDefinition=group1_channels,\
        },\
};

#define HWunit0Channels\
{\
        {\
         .AdcChannelConvTime=0U,\
         .AdcChannelId=0U,\
         .AdcChannelRangeSelect=0U,\
         .AdcChannelResolution=12U,\
         .AdcChannelSampTime=0U,\
        },\
        {\
            .AdcChannelConvTime=0U,\
            .AdcChannelId=1U,\
            .AdcChannelRangeSelect=0U,\
            .AdcChannelResolution=12U,\
            .AdcChannelSampTime=0U,\
        },\
        {\
           .AdcChannelConvTime=0U,\
           .AdcChannelId=2U,\
           .AdcChannelRangeSelect=0U,\
           .AdcChannelResolution=12U,\
           .AdcChannelSampTime=0U,\
         },\
};

typedef struct
{
uint8 seq_index;
uint8 sequencer;
uint8 step;
}Channel_To_Sequencer_mappingType;

extern const Channel_To_Sequencer_mappingType channel_to_seq_map0[];
extern const uint8 group0_channels[];
extern const uint8 group1_channels[];
extern const uint8 Grp_to_seq_map0[];
extern uint8 Unit0_seq_counters[Num_of_seq_uint0];
extern const uint8 Unit0_seq_sizes[2];


#endif /* INCLUDES_ADC_CFG_H_ */
