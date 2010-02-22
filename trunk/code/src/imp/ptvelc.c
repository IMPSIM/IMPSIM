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
/* ptvelc-01 Jan 00:12 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Find the absolute position and velocity of a point.
|
|     Access:
|       (void) ptvelc(Point *point, real pos[3], real vel[3]);
|     Point *point,i-Pointer to the Point record.
|     real pos[3],o-Absolute position coordinates of the point.
|     real vel[3],o-Absolute velocity components for the point.
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
  void ptvelc(Point *point, real pos[3], real vel[3])
#else
  void ptvelc(point, pos, vel)
  Point *point;
  real   pos[3], vel[3];
#endif
{
  Body *body;

  ptposc(point, pos);
  if (System.level < 8) velc();
  if (System.nerror == 0) {
    body = point->pntBdy;
    mpydrc(body->W, pos, vel);
  } else {
    ldnanc((void *) &vel[0]);
  }
  return;
}
