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
/* prgdc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the transformation matrix for a rigid joint.
|
|     Access:
|       (void) prgdc(real Phi[3][4]);
|     real Phi[3][4],o-Transformation matrix for the joint.
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
  void prgdc(real Phi[3][4])
#else
  void prgdc(Phi)
  real Phi[3][4];
#endif
{
  int i, j;
  
  for (i=0; i<3; i++){
    for (j=0; j<4; j++){
      Phi[i][j] = 0.0;
    }
    Phi[i][i] = 1.0;
  }
  return;
}
