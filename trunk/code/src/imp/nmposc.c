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
/* nmposc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine the current position values for a named item.
|
|     Access:
|       (void) nmposc(Word name, enum Rectyp *kind, real pos[], int *n);
|     Word name, i-Name for the item whose position is sought.
|     enum Rectyp *kind,o-Type of the item found:  BODY, JOINT, POINT,
|       SPRING, or DAMPER.
|     real pos[],o-Array of position component values.
|     int *n,    o-Number of position components in pos[].
|
|     Error Conditions:
|       If the named item is not found, or if its position values are
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
  void nmposc(Word name, enum Rectyp *kind, real pos[], int *n)
#else
  void nmposc(name, kind, pos, n);
  Word name;
  enum Rectyp *kind;
  real pos[];
  int *n;
#endif
{
  Body   *body;
  Damper *damper;
  Joint  *joint;
  Point  *point;
  Spring *spring;
  int     i, j, k;

/* Initialize. */
  *n = 0;
  *kind = 0;

/* Process a Body. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strcmp(body->name, name) == 0) {
      k = 0;
      for (i=0; i<3; i++) {
        for (j=0; j<4; j++) {
          pos[k] = body->T0j[i][j];
          k++;
        }
      }
      *kind = BODY;
      *n = k;
      return;
    }
  }

/* Process a Joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      jtposc(joint, pos, n);
      *kind = JOINT;
      return;
    }
  }

/* Process a Point. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (point=body->bdyPnt; point; point=point->nxtPnt) {
      if (point->master) {
        if (strcmp(point->name, name) == 0) {
          ptposc(point, pos);
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
      sgposc(spring, pos);
      *kind = SPRING;
      *n = 3;
      return;
    }
  }

/* Process a Damper. */
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (strcmp(damper->name, name) == 0) {
      dmposc(damper, pos);
      *kind = DAMPER;
      *n = 3;
      return;
    }
  }
  return;
}
