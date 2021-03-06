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
/* dmposc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the position difference vector for a damper.
|
|     Access:
|       (void) dmposc(Damper *damper, real pos[3]);
|     Damper *damper,i-Pointer to the Damper record.
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
  void dmposc(Damper *damper, real pos[3])
#else
  void dmposc(damper, pos)
  Damper *damper;
  real    pos[3];
#endif
{
  int  i;
  real posA[3], posB[3];

  ptposc(damper->dmpPtA, posA);
  ptposc(damper->dmpPtB, posB);
  for (i=0; i<3; i++) pos[i] = posA[i] - posB[i];
  return;
}
