/*
 * ADC.c
 *
 *  Created on: 28 Aug 2019
 *      Author: Aly
 */
#include "includes/Adc.h"

static const AdcGroupConfigType HW_unit0_Groups[Num_HW_Unit0_Groups]=HWunit0Groups;
static const AdcChannelConfigType HW_unit0_Channels [Num_HWunit0Channels]=HWunit0Channels;

const Adc_ConfigType Adc_Config_Container=Adc_Config;

AdcUnitStateType Adc_module_state=Un_Init;

static const uint32 CLK_enable_param[]= Clk;/*case 2 Hw modules size will
be 2 depending on the macro NUM_of_HW_Units*/

const uint8 Num_Of_Groups_per_HWunit[NUM_of_HW_Units]=NumOfGroupsPerHWunit;


const uint8 Num_Of_channels_per_group[]=Channels_per_group;

Adc_StatusType Groups_status[Num_of_all_groups]={ADC_IDLE};

uint8 NO_busy_groups=0;/*this parameter shall be changed by other APIs in case of a group is not
in state ADC_stream_complete or Busy_state */



void Adc_Init(const Adc_ConfigType* ConfigPtr)
{
  uint8 index0,index1,index2;


 if (Adc_module_state==Un_Init)
 {
#if HW_module0
      index2=0;

           SYSCTL_RCC_R&=~(1<<13);/*this shall be done by MCU driver*/
           SysCtlPeripheralEnable(CLK_enable_param[index2]);
           while(!SysCtlPeripheralReady(CLK_enable_param[index2])){};

          ADCClockConfigSet(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                            ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcClockSource,1);
          /* pre-scaler is always equal to 1*/
          if(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcClockSource!=AdcClkSrcPll)
          {
              SYSCTL_RCC_R|=(1<<13);
          }
          else{
              /*MISRA*/
              }

  for(index0=0;index0<size_of_grp_seq_map0;index0++)
   {
        if(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupTriggSrc==ADC_TRIGG_SRC_SW)
        {
         ADCSequenceConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,Grp_to_seq_map0[index0],
                              ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupTriggSrc,
                              ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupPriority);
        }   else{   /*for HW trigger source*/
            ADCSequenceConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                               Grp_to_seq_map0[index0],
                               ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].Hw_Trig_src,
                               ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupPriority);
         }
   }


  for(index0=0;index0<Num_HW_Unit0_Groups;index0++)
  {

    for(index1=0;index1<Num_Of_channels_per_group[index0];index1++)
    {
            Unit0_seq_counters[Grp_to_seq_map0[index0],channel_to_seq_map0[ConfigPtr->AdcConfigSet.
                                AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].seq_index]++;

                if(Unit0_seq_counters[Grp_to_seq_map0[index0],channel_to_seq_map0[ConfigPtr->AdcConfigSet.
                             AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].seq_index]==
                              Unit0_seq_sizes[Grp_to_seq_map0[index0],channel_to_seq_map0[ConfigPtr->AdcConfigSet.
                               AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].seq_index])
                {
                     ADCSequenceStepConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                                  Grp_to_seq_map0[index0],channel_to_seq_map0[ConfigPtr->AdcConfigSet.
                                  AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].step
                                   ,ConfigPtr->AdcConfigSet. AdcHwUnit[index2].AdcGroup[index0].
                                   AdcGroupDefinition[index1] |ADC_CTL_IE|ADC_CTL_END);
                }else{
                        ADCSequenceStepConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                        Grp_to_seq_map0[index0],channel_to_seq_map0[ConfigPtr->AdcConfigSet.
                        AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].step
                        ,ConfigPtr->AdcConfigSet. AdcHwUnit[index2].AdcGroup[index0].
                        AdcGroupDefinition[index1] | ADC_CTL_IE);
                     }
  }
}

#endif
#if HW_module1
index2=1;
SYSCTL_RCC_R&=~(1<<13);/*this shall be done by MCU driver*/
        SysCtlPeripheralEnable(CLK_enable_param[index2]);
        while(!SysCtlPeripheralReady(CLK_enable_param[index2])){};

       ADCClockConfigSet(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                         ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcClockSource,1);
       if(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcClockSource==AdcClkSrcPll)
       {

       }
       else{
           SYSCTL_RCC_R|=(1<<13);
           }
   for(index0=0;index0<size_of_grp_seq_map1;index0++)
   {
     if(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupTriggSrc==ADC_TRIGG_SRC_SW)
     {
      ADCSequenceConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,Grp_to_seq_map1[index0],
                           ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupTriggSrc,
                           ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupPriority);

     }
     else{   /*for HW trigger source*/
             ADCSequenceConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                                Grp_to_seq_map1[index0],
                                ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].Hw_Trig_src,
                                ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcGroup[index0].AdcGroupPriority);

        }
   }
   for(index0=0;index0<Num_HW_Unit1_Groups;index0++)
   {
     for(index1=0;index1<Num_Of_channels_per_group[index1];index1++)
     {
                     Unit1_seq_counters[Grp_to_seq_map1[index0],channel_to_seq_map1[ConfigPtr->AdcConfigSet.
                                         AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].seq_index]++;
             if(Unit0_seq_counters[Grp_to_seq_map1[index0],channel_to_seq_map1[ConfigPtr->AdcConfigSet.
                          AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].seq_index]==
                        Unit1_seq_sizes[Grp_to_seq_map1[index0],channel_to_seq_map1[ConfigPtr->AdcConfigSet.
                        AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].seq_index])
             {
                  ADCSequenceStepConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                               Grp_to_seq_map1[index0],channel_to_seq_map1[ConfigPtr->AdcConfigSet.
                               AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].step
                                ,ConfigPtr->AdcConfigSet. AdcHwUnit[index2].AdcGroup[index0].
                                AdcGroupDefinition[index1] |ADC_CTL_IE|ADC_CTL_END);
             }else{
                     ADCSequenceStepConfigure(ConfigPtr->AdcConfigSet.AdcHwUnit[index2].AdcHwUnitId,
                     Grp_to_seq_map1[index0],channel_to_seq_map1[ConfigPtr->AdcConfigSet.
                     AdcHwUnit[index2].AdcGroup[index0].AdcGroupDefinition[index1]].step
                     ,ConfigPtr->AdcConfigSet. AdcHwUnit[index2].AdcGroup[index0].
                     AdcGroupDefinition[index1] | ADC_CTL_IE);

                  }

         }
    }
#endif
   Adc_module_state=Init;

 }
   else{
                /*error detection shall occure here*/


       }
}
#if AdcDeInitApi
void Adc_DeInit(void)
{
    if(Adc_module_state==Un_Init)
    {
        /*error shall be detected here*/
    }else
    {
    if(NO_busy_groups!=0)
        {

            /*error shall be detected here*/
        }
    else{
        uint8 index3;
#if ADC_HW0_INt
        ADCIntDisable(Adc_Config_Container.AdcConfigSet.AdcHwUnit[0].AdcHwUnitId, 1|2|3);
#endif
#if ADC_HW1_INt
        ADCIntDisable(Adc_Config_Container.AdcConfigSet.AdcHwUnit[1].AdcHwUnitId, 1|2|3);
#endif
            for(index3=0;index3<NUM_of_HW_Units;index3++)
            {   /*the following line disables all sequencers*/
                (*((volatile unsigned long *)Adc_Config_Container.AdcConfigSet.AdcHwUnit[index3].AdcHwUnitId))=0;
                  SysCtlPeripheralDisable(CLK_enable_param[index3]);
            }

            Adc_module_state=Un_Init;
            for(index3=0;index3<Num_of_all_groups;index3++)
            {
                 Groups_status[index3]=ADC_IDLE;
            }
          }
 }
}
#endif
