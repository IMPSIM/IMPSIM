/* ------------------------------------------------------------------ */
/* clrvlc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Return a color value needed in function torgbc().
|
|     Access:
|       color = (real) clrvlc(real x1, real x2, real xhue);
|     real x1,   i-
|     real x2,   i-
|     real xhue, i-
|     real color,o-
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
#if defined(ANSI)
  real clrvlc(real x1, real x2, real xhue)
#else
  real clrvlc(x1, x2, xhue)
  real x1, x2, xhue;
#endif
{
  real value, xh;
 
  xh = fmod(xhue, 360.0);
  if (xh < 0.0) xh = xh + 360.0;
  if (xh < 60.0) {
    value = x1 + (x2 - x1) * xh / 60.0;
  } else if (xh < 180.0) {
    value = x2;
  } else if (xh < 240.0) {
    value = x1 + (x2 - x1) * (240.0 - xh) / 60.0;
  } else {
    value = x1;
  }
  return(value);
}
