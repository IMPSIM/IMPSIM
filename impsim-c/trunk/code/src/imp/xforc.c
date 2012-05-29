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
/* xforc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Force record.
|
|     Access:
|       (void) xforc(Force *force);
|     Force *force,i-Pointer to the Force record to be deleted.
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
  void xforc(Force *force)
#else
  void xforc(force)
  Force *force;
#endif
{
  Body  *body;
  Force *frc;

  if (force->type == FORCE) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (body->bdyFrc == force) {
        body->bdyFrc = force->nxtFrc;
      } else {
        frc = body->bdyFrc;
        while (frc) {
          if (frc->nxtFrc == force) {
            frc->nxtFrc = force->nxtFrc;
            break;
          } else {
            frc = frc->nxtFrc;
          }
        }
      }
    }
    free(force);
  }
  return;
}
