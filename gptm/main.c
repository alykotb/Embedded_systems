/*
 * main.c
 *
 *  Created on: 11 Jul 2019
 *      Author: Aly
 */
int main(void)
{
    float result;
portb_init();
gptm0_init();

    while(1){

                 result= calc_frequency();
             }
return 0;
}

