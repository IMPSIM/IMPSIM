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
/* phbvlc-01 Jan 00:21 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the joint variable estimates for a bevel gear joint from 
|     the transformation matrix and test for errors in design position
|     data.
|
|     Access:
|       lflag = (int) phbvlc(real Phi[3][4], real conei, real coneo,
|         real phi[2]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     real conei,    i-Half cone angle of the first gear.
|     real coneo,    i-Half cone angle of the second gear.
|     real phi[2],   o-Joint variable estimates of the bevel gear joint.
|     int  lflag,    o-Flag set TRUE for input data error(s).
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
  int phbvlc(real Phi[3][4], real conei, real coneo, real phi[2])
#else
  int phbvlc(Phi, conei, coneo, phi)
  real Phi[3][4], conei, coneo, phi[2];
#endif
{
  int  lflag;

  lflag = FALSE;
  if (fabs(Phi[0][3]) > System.dtoll) lflag = TRUE;
  if (fabs(Phi[1][3]) > System.dtoll) lflag = TRUE;
  if (fabs(Phi[2][3]) > System.dtoll) lflag = TRUE;
  phi[0] = atan2(-Phi[0][2], -Phi[1][2]);
  phi[1] = acos(Phi[2][2]) - conei - coneo;
  return(lflag);
}
