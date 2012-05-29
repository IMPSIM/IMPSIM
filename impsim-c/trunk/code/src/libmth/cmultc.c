/* ------------------------------------------------------------------ */
/* cmultc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the product of two complex numbers, c = a * b.
| 
|     Access:
|       c = (complex) cmultc(complex a, complex b);
|     complex a,i-The first  factor of the product.
|     complex b,i-The second factor of the product.
|     complex c,o-The product found.
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
  complex cmultc(complex a, complex b)
#else
  complex cmultc(a, b)
  complex a, b;
#endif
{
  complex c;

  c.r  = a.r * b.r - a.i * b.i;
  c.i  = a.r * b.i + a.i * b.r;
  return(c);
}
