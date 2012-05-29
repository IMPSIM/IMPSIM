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
/* nmvelc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine the current velocity values for a named item.
|
|     Access:
|       (void) nmvelc(Word name, enum Rectyp *kind, real vel[], int *n);
|     Word name, i-Name for the item whose velocity is sought.
|     enum Rectyp *kind,o-Type of the item found:  BODY, JOINT, POINT,
|       SPRING, or DAMPER.
|     real vel[],o-Array of velocity component values.
|     int *n,    o-Number of velocity components in vel[].
|
|     Error Conditions:
|       If the named item is not found, or if its velocity values are
|     not defined, then *kind=0 and *n=0 is returned.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void nmvelc(Word name, enum Rectyp *kind, real vel[], int *n)
#else
  void nmvelc(name, kind, vel, n);
  Word name;
  enum Rectyp *kind;
  real vel[];
  int *n;
#endif
{
  Body   *body;
  Damper *damper;
  Joint  *joint;
  Point  *point;
  Spring *spring;
  int     i;
  real    pos[3];

/* Initialize. */
  *n = 0;
  *kind = 0;
  if (System.level < 8) velc();
  if (System.nerror != 0) return;

/* Process a Body. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strcmp(body->name, name) == 0) {
      for (i=0; i<6; i++) {
        vel[i] = body->W[i];
      }
      *kind = BODY;
      *n = 6;
      return;
    }
  }

/* Process a Joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      jtvelc(joint, vel, n);
      *kind = JOINT;
      return;
    }
  }

/* Process a Point. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (point=body->bdyPnt; point; point=point->nxtPnt) {
      if (point->master) {
        if (strcmp(point->name, name) == 0) {
          ptvelc(point, pos, vel);
          *kind = POINT;
          *n = 3;
          return;
        }
      }
    }
  }

/* Process a Spring. */
  for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
    if (strcmp(spring->name, name) == 0) {
      sgvelc(spring, vel);
      *kind = SPRING;
      *n = 3;
      return;
    }
  }

/* Process a Damper. */
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (strcmp(damper->name, name) == 0) {
      dmvelc(damper, vel);
      *kind = DAMPER;
      *n = 3;
      return;
    }
  }
  return;
}
