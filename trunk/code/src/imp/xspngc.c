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
/* xspngc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Spring record.
|
|     Access:
|       (void) xspngc(Spring *spring);
|     Spring *spring,i-Pointer to the Spring record to be deleted.
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
 
#include "libimp.h"
#ifdef ANSI
  void xspngc(Spring *spring)
#else
  void xspngc(spring)
  Spring *spring;
#endif
{
  Spring *spg;

  if (spring->type == SPRING) {
    if (System.sysSpg == spring) {
      System.sysSpg = spring->nxtSpg;
    } else {
      spg = System.sysSpg;
      while (spg) {
        if (spg->nxtSpg == spring) {
          spg->nxtSpg = spring->nxtSpg;
          break;
        } else {
          spg = spg->nxtSpg;
        }
      }
    }
    free(spring);
  }
  return;
}
