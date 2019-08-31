/*
 * Compiler.h
 *
 *  Created on: 31 Aug 2019
 *      Author: Aly
 */
#include "limits.h"
#ifndef INCLUDES_COMPILER_H_
#define INCLUDES_COMPILER_H_

#ifndef _LIMITS_H_
#define _LIMITS_H_

#pragma diag_push
#pragma CHECK_MISRA("-20.1") /* standard headers must define standard names */

/*---------------------------------------------------------------------------*/
/* A header file conforming to ARM CLIB ABI (GENC-003539), should            */
/* define _AEABI_PORTABLE when _AEABI_PORTABILITY_LEVEL is defined.          */
/*---------------------------------------------------------------------------*/
#if defined(_AEABI_PORTABILITY_LEVEL) && !defined(_AEABI_PORTABLE)
#define _AEABI_PORTABLE
#endif

/*---------------------------------------------------------------------------*/
/* The macro definition that guards CLIB ABI (GENC-003539) requirements.     */
/*---------------------------------------------------------------------------*/
#if defined(__TMS470__) && defined(__TI_EABI_SUPPORT__)
#define _AEABI_PORTABILITY_CHECK (defined(__TMS470__) && \
                                  defined(__TI_EABI_SUPPORT__) && \
                                  defined(_AEABI_PORTABILITY_LEVEL) && \
                                  _AEABI_PORTABILITY_LEVEL != 0)
#else
#define _AEABI_PORTABILITY_CHECK 0
#endif

#define CHAR_BIT                 8       /* NUMBER OF BITS IN TYPE CHAR      */
#define SCHAR_MIN    (-SCHAR_MAX-1)      /* MIN VALUE FOR SIGNED CHAR        */
#define SCHAR_MAX              127       /* MAX VALUE FOR SIGNED CHAR        */
#define UCHAR_MAX              255       /* MAX VALUE FOR UNSIGNED CHAR      */

#if (!defined(__TMS320C2000__) && \
    !(defined(__TMS320C6X__) && !defined(__C6X_MIGRATION__))) && \
    defined(__unsigned_chars__)
#define CHAR_MIN                 0       /* MIN VALUE FOR CHAR               */
#define CHAR_MAX        (UCHAR_MAX)      /* MAX VALUE FOR CHAR               */
#else
#define CHAR_MIN        (SCHAR_MIN)      /* MIN VALUE FOR PLAIN CHAR         */
#define CHAR_MAX        (SCHAR_MAX)      /* MAX VALUE FOR PLAIN CHAR         */
#endif /* __CHAR_UNSIGNED__ */

#if defined(_AEABI_PORTABILITY_CHECK) && _AEABI_PORTABILITY_CHECK > 0
  #if defined(__cplusplus)
  extern "C" namespace std {
  #endif
      extern const int __aeabi_MB_LEN_MAX;
  #if defined(__cplusplus)
  }
  #endif
  #define MB_LEN_MAX (__aeabi_MB_LEN_MAX)
#else
#define MB_LEN_MAX               8       /* MAX # BYTES IN MULTI-BYTE        */
#endif

#define SHRT_MIN      (-SHRT_MAX-1)      /* MIN VALUE FOR SHORT              */
#define SHRT_MAX             32767       /* MAX VALUE FOR SHORT              */
#define USHRT_MAX            65535       /* MAX VALUE FOR UNSIGNED SHORT     */

#define INT_MIN         (-INT_MAX-1)     /* MIN VALUE FOR INT                */
#define INT_MAX         2147483647       /* MAX VALUE FOR INT                */
#define UINT_MAX        4294967295U      /* MAX VALUE FOR UNSIGNED INT       */

#define LONG_MIN        (-LONG_MAX-1)    /* MIN VALUE FOR LONG               */
#define LONG_MAX         2147483647      /* MAX VALUE FOR LONG               */
#define ULONG_MAX       4294967295U      /* MAX VALUE FOR UNSIGNED LONG      */


#define LLONG_MIN         (-LLONG_MAX-1) /* MIN VALUE FOR LONG LONG          */
#define LLONG_MAX    9223372036854775807 /* MAX VALUE FOR LONG LONG          */
#define ULLONG_MAX 18446744073709551615U /* MAX VALUE FOR UNSIGNED LONG LONG */

#pragma diag_pop

#endif /* #ifndef _LIMITS_H_ */

#pragma diag_push

/* using declarations must occur outside header guard to support including both
   C and C++-wrapped version of header; see _CPP_STYLE_HEADER check */
/* this code is for C++ mode only and thus also not relevant for MISRA */
#pragma CHECK_MISRA("-19.15")

#if defined(__TMS470__) && defined(__TI_EABI_SUPPORT__) && \
    defined(_AEABI_PORTABILITY_LEVEL) && _AEABI_PORTABILITY_LEVEL > 0
  #if defined(__cplusplus) && !defined(__INCLUDED_FROM_CLIMITS)
      using std::__aeabi_MB_LEN_MAX;
  #endif
#endif

#pragma diag_pop
#ifndef _FLOAT_H_
#define _FLOAT_H_

#pragma diag_push
#pragma CHECK_MISRA("-20.1") /* standard headers must define standard names */

#define FLT_RADIX                         2   /* RADIX OF EXPONENT         */
#define FLT_ROUNDS                        1   /* ROUND TO NEAREST          */
#define FLT_EVAL_METHOD                 (-1)  /* INDETERMINABLE            */

#define FLT_DIG                           6   /* DECIMAL PRECISION         */
#define FLT_MANT_DIG                     24   /* BITS IN MANTISSA          */
#define FLT_MIN_EXP                   (-125)  /* SMALLEST EXPONENT         */
#define FLT_MAX_EXP                     128   /* LARGEST EXPONENT          */
#define FLT_MIN_10_EXP                 (-37)  /* MIN POWER OF 10           */
#define FLT_MAX_10_EXP                   38   /* MAX POWER OF 10           */
#define FLT_EPSILON         1.192092896E-07F  /* SMALLEST X WHERE 1+X != 1 */
#define FLT_MIN             1.175494351E-38F  /* SMALLEST POSITIVE VALUE   */
#define FLT_MAX             3.402823466E+38F  /* LARGEST POSITIVE VALUE    */


#define DBL_DIG                          15   /* DECIMAL PRECISION         */
#define DBL_MANT_DIG                     53   /* BITS IN MANTISSA          */
#define DBL_MIN_EXP                  (-1021)  /* SMALLEST EXPONENT         */
#define DBL_MAX_EXP                    1024   /* LARGEST EXPONENT          */
#define DBL_MIN_10_EXP                (-307)  /* MIN POWER OF 10           */
#define DBL_MAX_10_EXP                  308   /* MAX POWER OF 10           */
#define DBL_EPSILON  2.2204460492503131E-16   /* SMALLEST X WHERE 1+X != 1 */
#define DBL_MIN     2.2250738585072014E-308   /* SMALLEST POSITIVE VALUE   */
#define DBL_MAX     1.7976931348623157E+308   /* LARGEST POSITIVE VALUE    */



#define LDBL_DIG                         15   /* DECIMAL PRECISION         */
#define LDBL_MANT_DIG                    53   /* BITS IN MANTISSA          */
#define LDBL_MIN_EXP                 (-1021)  /* SMALLEST EXPONENT         */
#define LDBL_MAX_EXP                   1024   /* LARGEST EXPONENT          */
#define LDBL_MIN_10_EXP               (-307)  /* MIN POWER OF 10           */
#define LDBL_MAX_10_EXP                 308   /* MAX POWER OF 10           */
#define LDBL_EPSILON 2.2204460492503131E-16L  /* SMALLEST X WHERE 1+X != 1 */
#define LDBL_MIN    2.2250738585072014E-308L  /* SMALLEST POSITIVE VALUE   */
#define LDBL_MAX    1.7976931348623157E+308L  /* LARGEST POSITIVE VALUE    */


#pragma diag_pop

#endif /* _FLOAT_H_ */



#endif /* INCLUDES_COMPILER_H_ */
