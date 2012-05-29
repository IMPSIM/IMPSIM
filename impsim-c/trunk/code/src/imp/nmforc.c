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
/* nmforc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine the current force components for a named item.
|
|     Access:
|       (void) nmforc(Word name, enum Rectyp *kind, real frc[], int *n);
|     Word name, i-Name for the item whose forces are sought.
|     enum Rectyp *kind,o-Type of the item found:  JOINT, SPRING, or
|       DAMPER.
|     real frc[],o-Array of force component values.
|     int *n,    o-Number of force components in frc[].
|
|     Error Conditions:
|       If the named item is not found, or if its force values are not
|     defined, then *kind=0 and *n=0 is returned.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void nmforc(Word name, enum Rectyp *kind, real frc[], int *n)
#else
  void nmforc(name, kind, frc, n);
  Word name;
  enum Rectyp *kind;
  real frc[];
  int *n;
#endif
{
  Damper *damper;
  Joint  *joint;
  Spring *spring;

/* Initialize. */
  *n = 0;
  *kind = 0;

/* Process a Joint. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strcmp(joint->name, name) == 0) {
      jtforc(joint, frc);
      *kind = JOINT;
      *n = 6;
      return;
    }
  }

/* Process a Spring. */
  for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
    if (strcmp(spring->name, name) == 0) {
      frc[0] = sgforc(spring);
      *kind = SPRING;
      *n = 1;
      return;
    }
  }

/* Process a Damper. */
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (strcmp(damper->name, name) == 0) {
      frc[0] = dmforc(damper);
      *kind = DAMPER;
      *n = 1;
      return;
    }
  }
  return;
}
