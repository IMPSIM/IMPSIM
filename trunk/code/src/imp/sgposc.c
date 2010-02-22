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
/* sgposc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the position difference vector for a spring.
|
|     Access:
|       (void) sgposc(Spring *spring, real pos[3]);
|     Spring *spring,i-Pointer to the Spring record.
|     real    pos[3],o-Coordinates of the position difference vector.
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
  void sgposc(Spring *spring, real pos[3])
#else
  void sgposc(spring, pos)
  Spring *spring;
  real    pos[3];
#endif
{
  int  i;
  real posA[3], posB[3];

  ptposc(spring->spgPtA, posA);
  ptposc(spring->spgPtB, posB);
  for (i=0; i<3; i++) pos[i] = posA[i] - posB[i];
  return;
}
