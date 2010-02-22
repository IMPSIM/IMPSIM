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
/* xbodyc-01 Jan 00:12 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Delete a specified Body record.
|
|     Access:
|       (void) xbodyc(Body *body);
|     Body *body,i-Pointer to the Body record to be deleted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       All records which are dependent on this Body are also deleted.
|       System.level = 0 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xbodyc(Body *body)
#else
  void xbodyc(body)
  Body *body;
#endif
{
  Body  *bdy;

  if (body->type == BODY) {
    if (System.sysBdy == body) {
      System.sysBdy = body->nxtBdy;
    } else {
      bdy = System.sysBdy;
      while (bdy) {
        if (bdy->nxtBdy == body) {
          bdy->nxtBdy = body->nxtBdy;
        } else {
          bdy = bdy->nxtBdy;
        }
      }
    }
    while (body->bdyAxs) xaxesc(body->bdyAxs);
    while (body->bdyPnt) xpntc (body->bdyPnt);
    while (body->bdyFrc) xforc (body->bdyFrc);
    while (body->bdyTrq) xtorqc(body->bdyTrq);
    if (body->bdyMas) xmassc(body->bdyMas);
    while (body->bdySld) xsldc(body->bdySld);
    for (bdy=body; bdy; bdy=bdy->nxtBdy) (bdy->bdyno)--;
    if (System.ground == body) System.ground = NULL;
    System.nbdys--;
    System.level = 0;
    free(body);
  }
  return;
}
