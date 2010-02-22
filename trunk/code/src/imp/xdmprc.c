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
/* xdmprc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Damper record.
|
|     Access:
|       (void) xdmprc(Damper *damper);
|     Damper *damper,i-Pointer to the Damper record to be deleted.
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
  void xdmprc(Damper *damper)
#else
  void xdmprc(damper)
  Damper *damper;
#endif
{
  Damper *dmp;

  if (damper->type == DAMPER) {
    if (System.sysDmp == damper) {
      System.sysDmp = damper->nxtDmp;
    } else {
      dmp = System.sysDmp;
      while (dmp) {
        if (dmp->nxtDmp == damper) {
          dmp->nxtDmp = damper->nxtDmp;
          break;
        } else {
          dmp = dmp->nxtDmp;
        }
      }
    }
    free(damper);
  }
  return;
}
