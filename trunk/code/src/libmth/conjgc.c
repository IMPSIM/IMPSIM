/* ------------------------------------------------------------------ */
/* conjgc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the complex conjugate of a complex value v.
| 
|     Access:
|       vbar = (complex) conjgc(complex value);
|     complex value,i-The complex value given.
|     complex vbar, o-The complex conjugate value found.
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
  complex conjgc(complex value)
#else
  complex conjgc(value)
  complex value;
#endif
{
  complex vbar;

  vbar.r =   value.r;
  vbar.i = - value.i;
  return(vbar);
}
