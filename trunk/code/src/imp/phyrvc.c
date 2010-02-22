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
/* phyrvc-01 Jan 00:05 Dec 05
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the joint variable estimate for a y-pin joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phyrvc(real Phi[3][4], real *phi);
|     real  Phi[3][4],i-Transformation matrix for the joint.
|     real *phi,      o-Joint variable estimate for the y-pin joint.
|     int   lflag,    o-Flag set TRUE for imprecise data.
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
  int phyrvc(real Phi[3][4], real *phi)
#else
  int  phyrvc(Phi, phi)
  real Phi[3][4], *phi;
#endif
{
  int  i, lflag;
  real dx, dz;

  dx = 0.5 * (Phi[0][2] - Phi[2][0]);
  dz = 0.5 * (Phi[0][0] + Phi[2][2]);
  *phi = atan2(dx, dz);
  lflag = FALSE;
  for (i=0; i<3; i++) {
    if (fabs(Phi[i][3]) > System.dtoll) lflag = TRUE;
  }
  if (fabs(Phi[1][1] - 1.0) > System.dtola) lflag = TRUE;
  return(lflag);
}
