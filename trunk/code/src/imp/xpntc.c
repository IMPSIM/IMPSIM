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
/* xpntc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Point record and all dependendent information
|     from the System model.
|
|     Access:
|       (void) xpntc(Point *point);
|     Point *point,i-Pointer to the Point record to be deleted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Any points, springs, dampers, forces, or torques which are
|     associated with the specified point are also deleted.
|       All other master or subordinate copies of the point and their
|     dependent information are also deleted.
|       System.level <= 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xpntc(Point *point)
#else
  void xpntc(point)
  Point *point;
#endif
{
  Body   *body;
  Damper *damper;
  Force  *force;
  Point  *pnt;
  Spring *spring;
  Torque *torque;
  Word    name;
  int     repeat;

/* Ensure this is a Point record. */
  if (point->type == POINT) {
    strcpy(name, point->name);

/* Delete any Springs which are attached to this Point. */
    repeat = TRUE;
    while (repeat) {
      repeat = FALSE;
      for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
        if (strncmp(spring->spgPtB->name, name, MAXCHR) == 0) {
          repeat = TRUE;
          xspngc(spring);
          break;
        } else if (strncmp(spring->spgPtA->name, name, MAXCHR) == 0) {
          repeat = TRUE;
          xspngc(spring);
          break;
        }
      }
    }

/* Delete any Dampers which are attached to this Point. */
    repeat = TRUE;
    while (repeat) {
      repeat = FALSE;
      for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
        if (strncmp(damper->dmpPtB->name, name, MAXCHR) == 0) {
          repeat = TRUE;
          xdmprc(damper);
          break;
        } else if (strncmp(damper->dmpPtA->name, name, MAXCHR) == 0) {
          repeat = TRUE;
          xdmprc(damper);
          break;
        }
      }
    }

/* Delete any Forces which are attached to this Point. */
    repeat = TRUE;
    while (repeat) {
      repeat = FALSE;
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        for (force=body->bdyFrc; force; force=force->nxtFrc) {
          if (strncmp(force->frcPtB->name, name, MAXCHR) == 0) {
            repeat = TRUE;
            xforc(force);
            break;
          } else if (strncmp(force->frcPtA->name, name, MAXCHR) == 0) {
            repeat = TRUE;
            xforc(force);
            break;
          } else if (strncmp(force->frcPtC->name, name, MAXCHR) == 0) {
            repeat = TRUE;
            xforc(force);
            break;
          }
        }
        if (force) break;
      }
    }

/* Delete any Torques which are attached to this Point. */
    repeat = TRUE;
    while (repeat) {
      repeat = FALSE;
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
          if (strncmp(torque->trqPtB->name, name, MAXCHR) == 0) {
            repeat = TRUE;
            xtorqc(torque);
            break;
          } else if (strncmp(torque->trqPtA->name, name, MAXCHR) == 0) {
            repeat = TRUE;
            xtorqc(torque);
            break;
          }
        }
        if (torque) break;
      }
    }

/* Cycle through all points deleting those with the same name. */
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (body->bdyPnt) {
        for (pnt=body->bdyPnt; pnt; pnt=pnt->nxtPnt) {
          if (pnt->nxtPnt) {
            if (strncmp(pnt->nxtPnt->name, name, MAXCHR) == 0) {
              pnt->nxtPnt = pnt->nxtPnt->nxtPnt;
              free(pnt->nxtPnt);
            }
          } else if (strncmp(pnt->name, name, MAXCHR) == 0) {
            body->bdyPnt = NULL;
            free(pnt);
            break;
          }
        }
      }
    }
    if (System.level > 3) System.level = 3;
  }
  return;
}
