/* ------------------------------------------------------------------ */
/* qloc3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Arm the locator device for a single location and return its 3D
|     coordinates.
|
|     Access:
|       (void) qloc3c(real *x, real *y, real *z, real *w, int *lflag);
|     real *x,o-The 3D x-coordinate of the location chosen.
|     real *y,o-The 3D y-coordinate of the location chosen.
|     real *z,o-The 3D z-coordinate of the location chosen.
|     real *w,o-The 3D homogeneous coordinate of the location chosen.
|     int  *lflag,o-Logical error flag returned as TRUE if the location
|       is within the 2D window.
|
|     Error Conditions:
|      For non-interactive execution the current graphic pen location
|    is returned instead.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|      Which locator device is read may be controlled by previous calls
|    to locdvc().  The default locator device is "alpha".
|      If the locator device is set to "alpha", the user is asked to
|    enter data via the keyboard.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qloc3c(real *x, real *y, real *z, real *w, int *lflag)
#else
  void qloc3c(x, y, z, w, lflag)
  real *x, *y, *z, *w;
  int *lflag;
#endif
{
  int  iostat;
  real temp, w2, x2, y2, z2;
 
  if (intact && (lcdvc != LT_ALPHA)) {
    qloc2c(&x2, &y2, lflag);
    x2to3c(x2, y2, 0.0, 1.0, x, y, z, w);
  } else {
    if (! l3pen) qpen3c(&x3pen, &y3pen, &z3pen, &w3pen);
    *x = x3pen / w3pen;
    *y = y3pen / w3pen;
    *z = z3pen / w3pen;
    *w = 1.0;
    if (intact) {
      do {
        textc("Enter 3D coordinate data (x,y,z): > ", FALSE);
        iostat = bfinc("/");
        if (iostat == 2) break;
        if (iostat != 0) continue;
        temp = x3pen / w3pen;
        *x = relrdc(temp, &iostat);
        if (iostat != 0) continue;
        temp = y3pen / w3pen;
        *y = relrdc(temp, &iostat);
        if (iostat != 0) continue;
        temp = z3pen / w3pen;
        *z = relrdc(temp, &iostat);
        if (iostat != 0) continue;
        break;
      } while(TRUE);
    }
  }
  x3to2c(*x, *y, *z, *w, &x2, &y2, &z2, &w2);
  x2 /= w2;
  y2 /= w2;
  *lflag = (x2 >= x2min) && (x2 <= x2max) && (y2 >= y2min)
    && (y2 <= y2max);
  return;
}
