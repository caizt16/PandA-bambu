/**
 * Porting of the libm library to the PandA framework
 * starting from the original FDLIBM 5.3 (Freely Distributable LIBM) developed by SUN
 * plus the newlib version 1.19 from RedHat and plus uClibc version 0.9.32.1 developed by Erik Andersen.
 * The author of this port is Fabrizio Ferrandi from Politecnico di Milano.
 * The porting fall under the LGPL v2.1, see the files COPYING.LIB and COPYING.LIBM_PANDA in this directory.
 * Date: September, 11 2013.
 */
/* sf_floor.c -- float version of s_floor.c.
 * Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

/*
 * floorf(x)
 * Return x rounded toward -inf to integral value
 * Method:
 *	Bit twiddling.
 * Exception:
 *	Inexact flag raised if x not equal to floorf(x).
 */

#include "math_privatef.h"

static const float huge = 1.0e30;

long int lfloorf(float x)
{
   int i0, j0;
   unsigned i, ix;
   GET_FLOAT_WORD(i0, x);
   ix = (i0 & 0x7fffffff);
   j0 = (ix >> 23) - 0x7f;
   if(j0 < 23)
   {
      if(j0 < 0)
      { /* raise inexact if x != 0 */
         if(huge + x > (float)0.0)
         { /* return 0*sign(x) if |x|<1 */
            if(i0 >= 0)
            {
               i0 = 0;
            }
            else if(!FLT_UWORD_IS_ZERO(ix))
            {
               i0 = 0xbf800000;
            }
         }
      }
      else
      {
         i = (0x007fffff) >> j0;
         if((i0 & i) == 0)
            return x; /* x is integral */
         if(huge + x > (float)0.0)
         { /* raise inexact flag */
            if(i0 < 0)
               i0 += (0x00800000) >> j0;
            i0 &= (~i);
         }
      }
   }
   else
   {
      if(!FLT_UWORD_IS_FINITE(ix))
         return x; /* inf or NaN */
      else
         return x; /* x is integral */
   }
   SET_FLOAT_WORD(x, i0);
   return (long int)x;
}

#ifdef _DOUBLE_IS_32BITS

long int lfloor(double x)
{
   return lfloorf((float)x);
}

#endif /* defined(_DOUBLE_IS_32BITS) */
