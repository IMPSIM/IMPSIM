/* ------------------------------------------------------------------ */
/* clessc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the difference between two complex numbers, c = a - b.
| 
|     Access:
|       c = (complex) clessc(complex a, complex b);
|     complex a,i-The first  term of the difference.
|     complex b,i-The second term of the difference.
|     complex c,o-The difference found.
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
  complex clessc(complex a, complex b)
#else
  complex clessc(a, b)
  complex a, b;
#endif
{
  complex c;

  c.r  = a.r - b.r;
  c.i  = a.i - b.i;
  return(c);
}
