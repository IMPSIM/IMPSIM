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
/* phsltc-01 Jan 00:25 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the joint variable estimates for a slot joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phsltc(real Phi[3][4], real phi[3]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     real phi[3],   o-Joint variable estimates for the slot joint.
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
  int phsltc(real Phi[3][4], real phi[3])
#else
  int  phsltc(Phi, phi)
  real Phi[4][3], phi[3];
#endif
{
  int  lflag;
  real cphi1, sphi1;

  phi[0] = Phi[0][3];
  cphi1  = 0.5 * (Phi[0][0] + Phi[1][1]);
  sphi1  = 0.5 * (Phi[1][0] - Phi[0][1]);
  phi[1] = atan2(sphi1, cphi1);
  phi[2] = Phi[2][3];
  lflag  = FALSE;
  if (fabs(Phi[2][2] - 1.0) > System.dtola) lflag = TRUE;
  return(lflag);
}
