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
/* ptacc-01 Jan 00:12 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Find the absolute position, velocity, and acceleration of a
|     point.
|
|     Access:
|       (void) ptacc(Point *point, real pos[3], real vel[3],
|         real Acc[3]);
|     Point *point,i-Pointer to the Point record.
|     real pos[3],o-Absolute position coordinates of the point.
|     real vel[3],o-Absolute velocity components for the point.
|     real Acc[3],o-Absolute acceleration components for the point.
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
  void ptacc(Point *point, real pos[3], real vel[3], real Acc[3])
#else
  void ptacc(point, pos, vel, Acc)
  Point *point;
  real   pos[3], vel[3], Acc[3];
#endif
{
  Body *body;
  int   i;
  real  temp[3];

  ptvelc(point, pos, vel);
  if (System.level < 10) acc();
  if (System.nerror == 0) {
    body = point->pntBdy;
    vcrosc(body->W, vel, Acc);
    mpydrc(body->A, pos, temp);
    for (i=0; i<3; i++) Acc[i] += temp[i];
  } else {
    ldnanc((void *) &Acc[0]);
  }
  return;
}
