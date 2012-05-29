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
/* sgacc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the acceleration difference vector for a spring.
|
|     Access:
|       (void) sgacc(Spring *spring, real acc[3]);
|     Spring *spring,i-Pointer to the Spring record.
|     real acc[3],o-Coordinates of the acceleration difference vector.
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
  void sgacc(Spring *spring, real acc[3])
#else
  void sgacc(spring, acc)
  Spring *spring;
  real    acc[3];
#endif
{
  int  i;
  real accA[3], accB[3], posA[3], posB[3], velA[3], velB[3];

  ptacc(spring->spgPtA, posA, velA, accA);
  ptacc(spring->spgPtB, posB, velB, accB);
  for (i=0; i<3; i++) acc[i] = accA[i] - accB[i];
  return;
}
