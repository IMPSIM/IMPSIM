/* ------------------------------------------------------------------ */
/* movagc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Move the pen to absolute grid coordinates (x,y).
|
|     Access:
|       (void) movagc(real x, real y);
|     real x,i-Absolute horizontal grid coordinate.
|     real y,i-Absolute vertical   grid coordinate.
|
|     Error Conditions:
|       Movements outside of the graph window boundaries are permitted
|     and are not clipped.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The grid in which the line is to be drawn must have been pro-
|     duced by a previous call to gridc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void movagc(real x, real y)
#else
  void movagc(x, y)
  real x, y;
#endif
{
  real s, t;
 
  xgtosc(x, y, &s, &t);
  movasc(s, t);
  return;
}
