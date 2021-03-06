/* ------------------------------------------------------------------ */
/* menu2c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       This function preforms the locator call for a pick on a menu
|     generated by calling the drmnuc() routine.  It returns the abso-
|     lute 2D coordinates of the locator and the number of the option
|     chosen by the user.  If a header option is picked, then its number
|     + 100 is returned.
|
|     Access:
|       nchosn = (int) menu2c(real *x2, real *y2)
|     real *x2,  o-Absolute horizontal 2D coordinate of locator.
|     real *y2,  o-Absolute veritcal   2D coordinate of locator.
|     int nchosn,o-Number of the option (or header + 100) chosen.
|
|     Error Conditions:
|       If the locator pick is above or below the menu boxes drawn by
|     drmnuc(), the option chosen is returned as zero.
|       For non-interactive use, menu2c() returns a value of zero.
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
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int menu2c(real *x2, real *y2)
#else
  int menu2c(x2, y2)
  real *x2, *y2;
#endif
{
  int  menu2;
  real s, t;
 
  menu2 = menusc(&s, &t);
  xsto2c(s, t, x2, y2);
  return(menu2);
}
