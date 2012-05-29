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
/* phgerc-01 Jan 00:23 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the joint variable estimate for a gear joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phgerc(real Phi[3][4], real ratio, real *cdist,
|         real phi[3]);
|     real  Phi[3][4],i-Transformation matrix for the joint.
|     real  ratio,    i-Gear ratio for the joint.
|     real *cdist,  i/o-Center to center distance for the joint.
|     real  phi[3],   o-Joint variable estimates for the gear joint.
|     int   lflag,    o-Flag set TRUE for imprecise data.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If *cdist = NaN on entry, then the center to center distance of
|     the gear joint is determined from the transformation.
|       If the distance cdist is less than the tolerance dtoll, then
|     phi[0] is returned as zero; no message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int phgerc(real Phi[3][4], real ratio, real *cdist, real phi[3])
#else
  int  phgerc(Phi, ratio, cdist, phi)
  real Phi[3][4], ratio, *cdist, phi[3];
#endif
{
  int  lflag;
  real cpsi, psi, spsi;

  lflag = FALSE;
  if (isnanc((void *) cdist)){
    *cdist = sqrt (Phi[0][3] * Phi[0][3] + Phi[1][3] * Phi[1][3]);
  }
  phi[1] = sqrt (Phi[0][3] * Phi[0][3] + Phi[1][3] * Phi[1][3]);
  if (fabs(*cdist) < System.dtoll) lflag = TRUE;
  if (lflag){
    phi[0] = 0.0;
  } else {
    phi[0] = atan2(Phi[1][3],  Phi[0][3]);
    phi[1]-= *cdist;
  }
  phi[2] = Phi[2][3];
  if (fabs(Phi[2][2] - 1.0) > System.dtola) lflag = TRUE;
  cpsi = Phi[0][0] + Phi[1][1];
  spsi = Phi[1][0] - Phi[0][1];
  psi  = (1.0 + ratio) * (phi[0]) - atan2(spsi, cpsi);
  psi  = fmod(psi, (2.0 * PI));
  if (fabs(psi) > System.dtola) lflag = TRUE;
  return(lflag);
}
