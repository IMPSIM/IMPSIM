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
/* phujtc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the joint variable estimates for a universal joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phsphc(real Phi[3][4], real phi[2]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     real phi[2],   o-Joint variable estimates for the universal joint.
|     int  lflag,    o-Flag set TRUE for imprecise data.
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
  int phujtc(real Phi[3][4], real phi[2])
#else
  int  phujtc(Phi, phi)
  real Phi[4][3], phi[2];
#endif
{
  int i, lflag;

  phi[0] = atan2(Phi[0][2], -Phi[1][2]);
  phi[1] = atan2(Phi[2][0],  Phi[2][1]);
  lflag  = FALSE;
  for (i=0; i<3; i++) {
    if (fabs(Phi[i][3]) > System.dtoll) lflag = TRUE;
  }
  if (fabs(Phi[2][2]) > System.dtola) lflag = TRUE;
  return(lflag);
}
