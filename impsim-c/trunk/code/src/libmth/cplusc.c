/* ------------------------------------------------------------------ */
/* cplusc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the sum of two complex numbers, c = a + b.
| 
|     Access:
|       c = (complex) cplusc(complex a, complex b);
|     complex a,i-The first  term of the sum.
|     complex b,i-The second term of the sum.
|     complex c,o-The sum found.
| 
|     Error Conditions:
|       None.
| 
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  complex cplusc(complex a, complex b)
#else
  complex cplusc(a, b)
  complex a, b;
#endif
{
  complex c;

  c.r  = a.r + b.r;
  c.i  = a.i + b.i;
  return(c);
}
