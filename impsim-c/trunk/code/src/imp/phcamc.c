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
/* phcamc-01 Jan 00:28 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the joint variable estimates for a cam joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phcamc(real Phi[3][4], real phi[3]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     real phi[3],   o-Joint variable estimates for the cam joint.
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
  int phcamc(real Phi[3][4], real phi[3])
#else
  int  phcamc(Phi, phi)
  real Phi[3][4], phi[3];
#endif
{
  int  lflag = FALSE;

  lflag  = FALSE;
  phi[0] = 0.0;
  phi[1] = sqrt(Phi[0][3] * Phi[0][3] + Phi[1][3] * Phi[1][3]);
  if (fabs(Phi[2][2] - 1.0) > System.dtola) lflag = TRUE;
  phi[2] = Phi[2][3];
  return(lflag);
}
