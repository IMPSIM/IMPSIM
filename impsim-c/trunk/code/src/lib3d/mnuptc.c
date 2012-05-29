/* ------------------------------------------------------------------ */
/* mnuptc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Get a menu selection or 3D coordinate data from the user.
|
|     Access:
|       menupt = (int) mnuptc(real *x, real *y, real *z);
|     real *x,   o-3D x-coordinate of the locator point selected.
|     real *y,   o-3D y-coordinate of the locator point selected.
|     real *z,   o-3D z-coordinate of the locator point selected.
|     int menupt,o-Number identifying the menu option picked.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The menu must have been drawn by a previous call to drmnuc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int mnuptc(real *x, real *y, real *z)
#else
  int mnuptc(x, y, z)
  real *x, *y, *z;
#endif
{
  char answer[2], string[8];
  int  iostat, mnupk;
  real temp, w, w2, x2, y2, z2, w3, x3, y3, z3;
 
/* Set the menu pick option to zero for default. */
  mnupk = 0;
  qpen2c(&x2, &y2);
  z2 = 0.0;
 
/* Keyboard input.  Menu selection or coordinate data. */
  if ((dspdvc == DT_ALPHA) || (lcdvc == DT_ALPHA)) {
    do {
      textc("Menu selection, y,n, [n]: > ", FALSE);
      iostat = bfinc("n");
      if (iostat == 2) goto _1;
    } while (iostat != 0);
    alprdc("n", string);
    strncpy(answer, string, 1);
    answer[1] = '\0';
    if (answer[0] == 'y' || answer[0] == 'Y') {
      do {
        mnupk = menuac();
      } while ((mnupk <= 0) || (mnupk > menumx));
 
/* Keyboard input of coordinate data. */
    } else {
      qpen3c(&x3, &y3, &z3, &w3);
      do {
        textc("Enter 3D coordinate data (x,y,z): > ", FALSE);
        iostat = bfinc("?");
        if (iostat == 2) goto _1;
        if (iostat != 0) continue;
        temp = x3 / w3;
        *x = relrdc(temp, &iostat);
        if (iostat != 0) continue;
        temp = y3 / w3;
        *y = relrdc(temp, &iostat);
        if (iostat != 0) continue;
        temp = z3 / w3;
        *z = relrdc(temp, &iostat);
        if (iostat != 0) continue;
        break;
      } while(TRUE);
      x3to2c(*x, *y, *z, 1.0, &x2, &y2, &z2, &w2);
      x2 /= w2;
      y2 /= w2;
      z2 /= w2;
    }
 
/* Locator input.  Menu selection or coordinate data. */
  } else {
    mnupk = menu2c(&x2, &y2);
  }
_1:
  x2to3c(x2, y2, z2, 1.0, x, y, z, &w);
  if (fabs(w) < ZERO) w = sign(ZERO, w);
  *x /= w;
  *y /= w;
  *z /= w;
  return(mnupk);
}
