/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:11 Jul 09                                          |
|     (C) Copyright, JJU Research, 1984-2009.                          |
|                                                                      |
|     This material is released under the terms of the                 |
|     GNU General Public License, version 3 (GNU GPLv3).               |
|     The full text of that license is available from the 'IMPSim'     |
|     project site on Google Code.                                     |
|                                                                      |
|     This initial release of 'IMPSim' is equivalent to the            |
|     IMP Integrated Mechanisms Program (IMP-2009) and is released     |
|     with the full approval of JJU Research of Madison, WI.           |
|                                                                      |
* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------ */
/* xaxesc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified axes record.
|
|     Access:
|       (void) xaxesc(Axes *axes);
|     Axes *axes,i-Pointer to the axes record to be deleted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       All records which are dependent on these axes are also deleted.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xaxesc(Axes *axes)
#else
  void xaxesc(axes)
  Axes *axes;
#endif
{
  Axes *axs;
  Body *body;

  if (axes->type == AXES) {
    while (axes->axsJnt) xjntc(axes->axsJnt);
    body = axes->axsBdy;
    if (body) {
      if (body->bdyAxs == axes) {
        axs->nxtAxs = axes->nxtAxs;
      } else {
        axs = body->bdyAxs;
        while (axs) {
          if (axs->nxtAxs == axes) {
            axs->nxtAxs = axes->nxtAxs;
            break;
          } else {
            axs = axs->nxtAxs;
          }
        }
      }
    }
    free(axes);
  }
  return;
}
