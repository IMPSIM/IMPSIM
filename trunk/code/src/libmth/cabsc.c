/* ------------------------------------------------------------------ */
/* cabsc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the absolute value of a complex number.
| 
|     Access:
|       size = (real) cabsc(complex value);
|     complex value,i-The complex term given.
|     real    size, o-The absolute value found.
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
  real cabsc(complex value)
#else
  real cabsc(a)
  complex a;
#endif
{
  real size;

  size = sqrt(value.r * value.r + value.i * value.i);
  return(size);
}
