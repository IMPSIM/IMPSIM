/* ------------------------------------------------------------------ */
/* csqrtc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the square root of a complex number, value.
| 
|     Access:
|       root = (complex) csqrtc(complex value);
|     complex value,i-The complex number whose root is sought.
|     complex root, o-The square root found.
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
  complex csqrtc(complex value)
#else
  complex csqrtc(value)
  complex value;
#endif
{
  complex root;
  real    angle, size;

  angle  = 0.5 * atan2(value.i, value.r);
  size   = sqrt(value.r * value.r + value.i * value.i);
  root.r = size * cos(angle);
  root.i = size * sin(angle);
  return(root);
}
