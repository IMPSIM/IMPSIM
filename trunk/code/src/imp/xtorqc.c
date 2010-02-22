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
/* xtorqc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Torque record.
|
|     Access:
|       (void) xtorqc(Torque *torque);
|     Torque *torque,i-Pointer to the Torque record to be deleted.
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
  void xtorqc(Torque *torque)
#else
  void xtorqc(torque)
  Torque *torque;
#endif
{
  Body   *body;
  Torque *trq;

  if (torque->type == TORQUE) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (body->bdyTrq == torque) {
        body->bdyTrq = torque->nxtTrq;
      } else {
        trq=body->bdyTrq;
        while (trq) {
          if (trq->nxtTrq == torque) {
            trq->nxtTrq = torque->nxtTrq;
            break;
          } else {
            trq = trq->nxtTrq;
          }
        }
      }
    }
    free(torque);
  }
  return;
}
