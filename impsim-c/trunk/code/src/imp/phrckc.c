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
/* phrckc-01 Jan 00:23 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the joint variable estimates for a rack joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phrckc(real Phi[3][4], real *radius, helix,
|         real phi[3]);
|     real  Phi[3][4],i-Transformation matrix for the joint.
|     real *radius, i/o-Radius of the pinion for the joint.
|     real  helix,    i-Helix angle of the pinion for the joint.
|     real  phi[3],   o-Joint variable estimates for the rack joint.
|     int   lflag,    o-Flag set TRUE for imprecise data.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If *radius = NaN on entry, then the radius of the pinion of the
|     rack joint is also determined from the transformation.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int phrckc(real Phi[3][4], real *radius, real helix, real phi[3])
#else
  int  phrckc(Phi, radius, helix, phi)
  real Phi[3][4], *radius, helix, phi[3];
#endif
{
  int  lflag;

  phi[0] = Phi[0][3];
  if (isnanc((void *) radius)) *radius = Phi[1][3];
  phi[1] = Phi[1][3] - *radius;
  phi[2] = Phi[2][3];
  lflag = FALSE;
  if (fabs(Phi[2][2] - 1.0) > System.dtola) lflag = TRUE;
  return(lflag);
}
