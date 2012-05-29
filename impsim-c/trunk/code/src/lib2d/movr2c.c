/* ------------------------------------------------------------------ */
/* movr2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Move the pen by (dx2, dy2) 2D units from its current location.
|
|     Access:
|       (void) movr2c(real dx2, real dy2);
|     real dx2,i-The relative 2D horizontal increment.
|     real dy2,i-The relative 2D vertical   increment.
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
  void movr2c(real dx2, real dy2)
#else
  void movr2c(dx2, dy2)
  real dx2, dy2;
#endif
{
  real x2, y2;
 
  if (!l2pen){
    xsto2c(spen, tpen, &x2pen, &y2pen);
    l2pen = TRUE;
  }
  x2 = x2pen + dx2;
  y2 = y2pen + dy2;
  mova2c(x2, y2);
  return;
}
