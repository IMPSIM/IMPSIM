/* ------------------------------------------------------------------ */
/* cdivc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the quotient of two complex numbers, c = a / b.
| 
|     Access:
|       c = (complex) cdivc(complex a, complex b);
|     complex a,i-The numerator   to be used.
|     complex b,i-The denominator to be used.
|     complex c,o-The quotient found.
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
  complex cdivc(complex a, complex b)
#else
  complex cdivc(a, b)
  complex a, b;
#endif
{
  complex c;
  real    denom;

  denom =  b.r * b.r + b.i * b.i;
  c.r   = (a.r * b.r + a.i * b.i) / denom;
  c.i   = (a.i * b.r - a.r * b.i) / denom;
  return(c);
}
