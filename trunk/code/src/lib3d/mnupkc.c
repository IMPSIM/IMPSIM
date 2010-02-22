/* ------------------------------------------------------------------ */
/* mnupkc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Allow the user to choose a menu selection.
|
|     Access:
|       menupk = (int) mnupkc();
|     int menupk,o-Number identifying the menu option picked.
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
int mnupkc()
{
  int  mnupk;
  real x, y, z, w;
 
  while (TRUE) {
    mnupk = 0;
    if ((dspdvc == DT_ALPHA) || (chdvc == CT_ALPHA)) {
      mnupk = menuac();                            /* Keyboard input. */
    } else {
      mnupk = menu3c(&x, &y, &z, &w);               /* Locator input. */
      mnupk = abs(mnupk);
    }
    if ((mnupk > 0) && (mnupk <= menumx)) { /* Test for a valid pick. */
      break;
    } else if ((mnupk > 100) && (mnupk <= 100 + nhdrs)) {
      break;
    } else if ((mnupk > 200) && (mnupk <= (200 + MXGLOBAL))) {
      break;
    } else {
      textc("Error:  Invalid menu choice.  Try again.", TRUE);
    }
  }
  return(mnupk);
}
