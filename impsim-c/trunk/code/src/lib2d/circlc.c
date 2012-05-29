/* ------------------------------------------------------------------ */
/* circlc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Draw a circle with a specified radius about the specified 2D
|     coordinates of its center.
|
|     Access:
|       (void) circlc(real x2ctr, real y2ctr, real radius);
|     real x2ctr, i-Horizontal 2D coordinate of circle center.
|     real y2ctr, i-Vertical   2D coordinate of circle center.
|     real radius,i-Radius of the circle in 2D length units.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void circlc(real x2ctr, real y2ctr, real radius)
#else
  void circlc(x2ctr, y2ctr, radius)
  real x2ctr, y2ctr, radius;
#endif
{
# define NINC   16
# define ANGINC (2.0 * PI / NINC)
  int  i;
  real angle, x2, y2;
 
  x2 = x2ctr + radius;
  mova2c(x2, y2ctr);
  angle = 0.0;
  for (i=0; i<NINC; i++) {
    angle += ANGINC;
    x2 = x2ctr + radius * cos(angle);
    y2 = y2ctr + radius * sin(angle);
    drwa2c(x2, y2);
  }
  return;
# undef ANGINC
# undef NINC
}
