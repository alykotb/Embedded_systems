/*
 * SPI.h
 *
 *  Created on: 19 Aug 2019
 *      Author: Aly
 */

#ifndef SPI_H_
#define SPI_H_
#include "stdint.h"
#include<tm4c123gh6pm.h>

void spi_init(void);
void spi_write(uint32_t data);

#endif /* SPI_H_ */
