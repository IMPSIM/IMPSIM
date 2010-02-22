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
/* phcylc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the joint variable estimates for a cylinder joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phcylc(real Phi[3][4], real phi[2]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     real phi[2],   o-Joint variable estimates for the cylinder joint.
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
  int phcylc(real Phi[3][4], real phi[2])
#else
  int  phcylc(Phi, phi)
  real Phi[3][4], phi[2];
#endif
{
  int  i, lflag;

  phi[0] = atan2(Phi[1][0] - Phi[0][1], Phi[0][0] + Phi[1][1]);
  phi[1] = Phi[2][3];
  lflag  = FALSE;
  for (i=0; i<2; i++) {
    if (fabs(Phi[i][3]) > System.dtoll) lflag = TRUE;
  }
  if (fabs(Phi[2][2] - 1.0) > System.dtola) lflag = TRUE;
  return(lflag);
}
