/*
 * diagnostic.c
 *
 *  Created on: 2 Jun 2019
 *      Author: Aly
 */


#include "diagnostic.h"
uint8_t service[len];
uint8_t ecu_select[num_of_ecus]={Diagnostic1_sw_ID,Diagnostic2_sw_ID};
uint8_t ecu_adresses[num_of_ecus]=destinations;/*contains destination addresses of ecu 2 and 3*/
char data[8U];
char string1[size2];
uint8_t* command[6U]={"no_reading","error","fire_air_bag","brake","dec.spead","maintain"};/*array of pointers to strings which are control
                                                                                           commands of adas system*/

/***********************************************/
/*Function Name :void Diag_service(void)
/*Inputs:NA
/*Outputs:NA
/*Re-entrancy:non-reentrant
/*synchronous:Sycnh
/*Description:This function s called continuously in the main to tak in user diagnostic request */
 /********************************************/



void Diag_service(void)
{
    UART_OutString("Service: ");
     UART_InString(data,19U);
     UART_OutString("ECU: ");
     UART_InString(string1,19U);
     data[char_4]=string1[char_1];
     if(data[char_2]=='d')
     {
         UART_OutString("ID: ");
         UART_InString(string1,19U);
         data[char_3]=string1[char_1]-48U;
     }
     else{
          /*MISRA*/
         }

if ((data[char_1] =='r')&&(data[char_2]=='d'))/*read data*/
        {
              uint8_t x3;
              x3=ecu_adresses[data[char_4]-48U-2U];
              service[byte_1]=x3;
              service[byte_1]|=source_address<<4;
              service[byte_2]=Read_data;
              service[byte_3]=data[char_3];
            comm_send(service,ecu_select[data[char_4]-48U-2U]);

        }
else if((data[char_1]=='r')&&(data[char_2]=='f'))/*read fault*/
        {
           uint8_t x4;

              x4=ecu_adresses[data[char_4]-48U-2U];
              service[byte_1]=x4;
              service[byte_1]|=source_address<<4;
              service[byte_2]=Read_fault;
             comm_send(service,ecu_select[data[char_4]-48U-2U]);

        }
else if(data[char_1]=='c')/*clear fault*/
        {        uint8_t x1;

        x1=ecu_adresses[data[char_4]-48U-2U];
        service[byte_1]=x1;
        service[byte_1]|=source_address<<4;
        service[byte_2]=Clear_fault;
                comm_send(service,ecu_select[data[char_4]-48U-2U]);

        }
else if ((data[char_1]=='w'))/*write data*/
    {
             uint8_t x2;

             x2=ecu_adresses[data[char_4]-48U-2U];
             service[byte_1]=x2;
             service[byte_1]|=source_address<<4;
             service[byte_2]=Write_data;
             comm_send(service,ecu_select[data[char_4]-48U-2U]);

    }
else{
    /*MISRA*/
}

}
/***********************************************/
/*Function Name :void Diag_response(uint8_t* data_in)
/*Inputs:data_in:pointer to data contains diagnostic response
/*Outputs:no returns
/*Re-entrancy:non-reentrant
/*synchronous:asynch
/*Description:it receives response of diagnosis and outputs them to user*/
 /********************************************/
void Diag_response(uint8_t* data_in)
{
    uint8_t* charptr;
    uint8_t number;
    UART_OutString("response:");
    if(data[char_2]=='d')
    {
        if(data[char_3]==1U)/*it comes from ecu2*/
        {
          /*print char of command*/
            /*if(data_in[char_2]==10U)
            {
                charptr=command[0U];
                         UART_OutString(charptr);
            }else{*/
            charptr=command[data_in[char_2]+1U];
            UART_OutString(charptr);

        }else if(data[char_3]==0U)
        {

            if (data_in[char_2]>=10)
            {
               number=(data_in[char_2]/10)+48U;
               charptr=&number;
               UART_OutString(charptr);
               number=(data_in[char_2]%10)+48U;
               UART_OutString(charptr);
            }else{
                      number=(data_in[char_2]%10)+48U;
                      charptr=&number;
                      UART_OutString(charptr);
                 }
        }else{/*MISRA*/}
    }
    else{
               data_in[char_2]=data_in[char_2]+48U;
               charptr=&data_in[char_2];
               UART_OutString(charptr);
    }
}
