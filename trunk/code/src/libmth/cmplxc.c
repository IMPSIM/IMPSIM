/* ------------------------------------------------------------------ */
/* cmplxc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form a complex number from its real and imaginary components.
| 
|     Access:
|       c = (complex) cmplxc(real creal, real cimag);
|     real creal,i-The real component.
|     real cimag,i-The imaginary component.
|     complex c,o-The complex value formed.
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
  complex cmplxc(real creal, real cimag)
#else
  complex cmplxc(creal, cimag)
  real creal, cimag;
#endif
{
  complex c;

  c.r  = creal;
  c.i  = cimag;
  return(c);
}
