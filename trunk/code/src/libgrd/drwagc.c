/* ------------------------------------------------------------------ */
/* drwagc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Draw a visible line from the current pen location to absolute
|     grid coordinates (x,y).
|
|     Access:
|       (void) drwagc(real x, real y);
|     real x,i-Absolute horizontal grid coordinate of line endpoint.
|     real y,i-Absolute vertical   grid coordinate of line endpoint.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The grid in which the line is to be drawn must have been pro-
|     duced by a previous call to gridc().
|       Drawing outside of the graph window boundaries is permitted and
|     is not clipped.
|       The line segment will be drawn as solid visible, or with the
|     dash pattern defined by the most recent call to dashc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void drwagc(real x, real y)
#else
  void drwagc(x, y)
  real x, y;
#endif
{
  real s, t;
 
  xgtosc(x, y, &s, &t);
  drwasc(s, t);
  return;
}
