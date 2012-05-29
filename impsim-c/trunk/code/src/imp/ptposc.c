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
/* ptposc-01 Jan 00:14 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Find the absolute position coordinates of a Point.
|
|     Access:
|       (void) ptposc(Point *point, real pos[3]);
|     Point *point,i-Pointer to the Point record.
|     real pos[3], o-Absolute coordinates of the Point.
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
  void ptposc(Point *point, real pos[3])
#else
  void ptposc(point, pos)
  Point *point;
  real   pos[3];
#endif
{
  int i;

  if (point->local) {
    mpyxrc(point->pntBdy->T0j, point->coord, pos);
  } else {
    for (i=0; i<3; i++) {
      pos[i] = point->coord[i];
    }
  }
  return;
}
