/* ------------------------------------------------------------------ */
/* qloc2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Arm the locator device for a single input and return its 2D
|     coordinates.
|
|     Access:
|       (void) qloc2c(real *x2, real *y2, int *lflag);
|     real *x2,   o-Horizontal 2D coordinate of the input location.
|     real *y2,   o-Vertical   2D coordinate of the input location.
|     int  *lflag,o-Logical error flag returned as lflag = TRUE if the
|       location is within the 2D window.
|
|     Error Conditions:
|      For non-interactive execution the current graphic pen location
|    is returned instead.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|      If the locator device is set to "alpha", the user is asked to
|    enter data via the keyboard.
|      Which locator device is read may be controlled by previous calls
|    to locdvc().  The default locator device is "alpha".
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qloc2c(real *x2, real *y2, int *lflag)
#else
  void qloc2c(x2, y2, lflag)
  real *x2, *y2;
  int  *lflag;
#endif
{
  int  iostat;
  real s, t;
 
  *x2 = x2pen;
  *y2 = y2pen;
  if (intact) {
    if ((lcdvc == LT_MOUSE) || (lcdvc == LT_TABLET)) {
      qlocsc(&s, &t, lflag);
      xsto2c(s, t, x2, y2);
    } else {
      if (! l2pen) qpen2c(&x2pen, &y2pen);
      while (TRUE) {
        textc("Enter 2D coordinates (x,y): > ", FALSE);
        if ((iostat = bfinc("/")) == 1) continue;
        if (iostat != 0) break;
        *x2 = relrdc(x2pen, &iostat);
        if (iostat != 0) continue;
        *y2 = relrdc(y2pen, &iostat);
        if (iostat == 0) break;
      }
    }
  }
  *lflag = (*x2 >= x2min) && (*x2 <= x2max) && (*y2 >= y2min)
    && (*y2 <= y2max);
  return;
}
