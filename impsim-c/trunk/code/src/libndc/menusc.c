/* ------------------------------------------------------------------ */
/* menusc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       This function preforms the locator call for a pick on a menu
|     generated by calling the drmnuc() routine.  It returns the abso-
|     lute screen coordinates of the locator and the number of the
|     option chosen by the user.
|
|     Access:
|       menus = (int) menusc(real *s, real *t);
|     real *s,o-Absolute horizontal screen coordinate of locator.
|     real *t,o-Absolute veritcal   screen coordinate of locator.
|     int menus,o-Number of the option chosen.
|
|     Error Conditions:
|       If the locator pick is above or below the menu boxes drawn by
|     drmnuc(), the option chosen is returned as zero.
|       If the locator pick is left of the menu boxes, the option chosen
|     is returned as the negative of the menu box picked vertically.
|       For non-interactive use, menusc() returns a value of zero.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       If a header option is picked, then its number + 100 is returned.
|       If a global option is picked, then its number + 200 is returned.
|       Which locator device is read may be controlled by previous calls
|     to locdvc().  The default device is "alpha".
|       If the locator device is set to "alpha", the user is asked to
|     enter data via the keyboard.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  int menusc(real *s, real *t)
#else
  int menusc(s, t)
  real *s, *t;
#endif
{
  int irow, kol, lflag, menus, nrows;
  real deltas, deltat, temp;

  menus = 0;
  if (intact){
    deltas = 0.125;
    deltat = (1.0 + xtrasz) * tsymbl;
    qlocsc(s, t, &lflag);
    temp = (1.0 - *t) / deltat;
    irow = ((int) temp) + 1;
    temp = *s / deltas;
    kol  = ((int) temp) + 1;
    if (kol >= 8) {
      if (irow <= MXGLOBAL) {
        menus = irow + 200;
      } else if (irow <= (menumx + MXGLOBAL)) {
        menus = irow - MXGLOBAL;
      }
    } else {
      nrows = (nhdrs - 1) / 7 + 1;
      if (irow < nrows) {
        khdr = 7 * (irow - 1) + kol;
        menus = khdr + 100;
      } else if ((irow == nrows) && (kol <= ((nhdrs - 1) % 7 + 1))) {
        khdr = 7 * (irow - 1) + kol;
        menus = khdr + 100;
      } else {
        if (irow <= MXGLOBAL) {
          menus = -(irow + 200);
        } else if (irow <= (menumx + MXGLOBAL)) {
          menus = -(irow - MXGLOBAL);
        }
      }
    }
  } else {
    *s = spen;
    *t = tpen;
  }
  return(menus);
}
