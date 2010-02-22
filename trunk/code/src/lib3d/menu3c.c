/* ------------------------------------------------------------------ */
/* menu3c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Preform the locator call for a pick on a menu generated by call-
|     ing the drmnuc() routine.  Return the absolute 3D coordinates of
|     the locator and the number of the option chosen by the user.  If a
|     header option is picked, then its number + 100 is returned.  If a
|     global option is picked, then its number + 200 is returned.
|
|     Access:
|       nchosn = (int) menu3c(real *x, real *y, real *z, real *w);
|     real *x,   o-The 3D x-coordinate of the locator.
|     real *y,   o-The 3D y-coordinate of the locator.
|     real *z,   o-The 3D z-coordinate of the locator.
|     real *w,   o-The 3D homogeneous coordinate of the locator.
|     int nchosn,o-Number of the option chosen.
|
|     Error Conditions:
|       If the locator pick is above or below the menu boxes drawn by
|     drmnuc(), the option chosen is returned as zero.
|       For non-interactive use, menu3u returns a value of zero.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Which locator device is read may be controlled by previous calls
|     to locdvc().  The default device is "alpha".
|       If the locator device is set to "alpha", the user is asked to
|     enter data via the keyboard.
|       If the locator pick is left of the menu boxes, the option chosen
|     is returned as the negative of the menu box picked vertically.
|       The location returned gets its 3D definition from an assumption
|     that it lies in the plane of the page and screen coordinate sys-
|     tems.  Note that this may not coincide with the user's intent when
|     locating on a 3D image drawn on the screen.  Note also that, with
|     a perspective view set by prspc(), even the x- and y-equivalent 2D
|     coordinates of the perceived and input locations differ unless
|     they lie in the plane of the screen.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int menu3c(real *x, real *y, real *z, real *w)
#else
  int menu3c(x, y, z, w)
  real *x, *y, *z, *w;
#endif
{
  int  menu3;
  real x2, y2;
 
  menu3 = menu2c(&x2, &y2);
  x2to3c(x2, y2, 0.0, 1.0, x, y, z, w);
  return(menu3);
}
