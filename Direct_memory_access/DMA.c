/*
 * DMA.c
 *
 *  Created on: 3 Aug 2019
 *      Author: Aly
 */


#include"stdint.h"
#include"tm4c123gh6pm.h"

uint32_t source[256];
uint32_t destination[256]={0};
uint8_t control_table[1024];

void DMA_init(void)
{
    SYSCTL_RCGCDMA_R|=0x1;/* enabling the clock for DMA module*/
    UDMA_CFG_R|=0x1;/*enabling the DMA controller*/

    UDMA_CTLBASE_R=&control_table[0];/*determining the bas address of the memory block*/

    UDMA_PRIOSET_R&=~(0x40000000);/*configuring channel 30's priority as default priority */
    UDMA_ALTCLR_R|=0x40000000;/*select the primary channel control structure for this transfer*/

      UDMA_USEBURSTSET_R|=0x40000000;
}

void set_control_structure(void)
{

    (*((uint32_t *)(control_table+0x1E0)))=&source[255];/*0x2000010C*/
    (*((uint32_t *)(control_table+0x1E4)))=&destination[255];/*0x2000011C*/
    (*((uint32_t *)(control_table+0x1E8)))=0;



    (*((uint32_t *)(control_table+0x1E8)))|=(0xAA<<24);/*32 bit data size and 32-bit increment*/

    (*((uint32_t *)(control_table+0x1E8)))|=(0x00<<18);/*reserved from 18 to 23 */
    (*((uint32_t *)(control_table+0x1E8)))|=(0x3<<14);/*arbitration after 8 transfers*/
    (*((uint32_t *)(control_table+0x1E8)))|=(255<<4);/*256 words transaction*/
    (*((uint32_t *)(control_table+0x1E8)))|=(2);/*auto mode transfer*/


}
void Enable_DMA(void)
{
    UDMA_ENASET_R|=0x40000000;
}
void TX_REQUEST(void)
{
    UDMA_SWREQ_R|=0x40000000;
}



