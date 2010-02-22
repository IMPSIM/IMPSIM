/* ------------------------------------------------------------------ */
/* cexpc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the exponential function of a complex value, c = exp(v).
| 
|     Access:
|       c = (complex) cexpc(complex value);
|     complex value,i-The complex value given.
|     complex c,    o-The exponential function value found.
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
  complex cexpc(complex value)
#else
  complex cexpc(value)
  complex value;
#endif
{
  complex c;
  real    factor;

  factor = exp(value.r);
  c.r = factor * cos(value.i);
  c.i = factor * sin(value.i);
  return(c);
}
