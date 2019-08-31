/*
 * Std_Types.h
 *
 *  Created on: 28 Aug 2019
 *      Author: Aly
 */

#ifndef INCLUDES_STD_TYPES_H_
#define INCLUDES_STD_TYPES_H_
#include"includes/compiler.h"
#include<includes/Platform_Types.h>

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK 0x0U
typedef unsigned char StatusType; /* OSEK compliance */
#endif
#define  E_NOT_OK 0x1U

typedef uint8 Std_ReturnType;







#endif /* INCLUDES_STD_TYPES_H_ */
