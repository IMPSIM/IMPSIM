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
/* phsphc-01 Jan 00:09 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the joint variable values for a spheric joint from the
|     transformation matrix and test for errors in design position data.
|
|     Access:
|       lflag = (int) phsphc(real Phi[3][4], real phi[4]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     real phi[4],   o-Joint variable values for the spheric joint.
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
*     09 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int phsphc(real Phi[3][4], real phi[4])
#else
  int  phsphc(Phi, phi)
  real Phi[3][4], phi[4];
#endif
{
  int  i, lflag;
  real arg, f00, f11, f22, tr;

  lflag = FALSE;
  tr = Phi[0][0] + Phi[1][1] + Phi[2][2];
  arg = tr + 1.0;
  if (arg < 0.0) {
    phi[3] = 0.0;
  } else {
    phi[3] = 0.5 * sqrt(arg);
  }
  if (phi[3] > System.zero) {
    arg = 1.0 + 2.0 * Phi[0][0] - tr;
    if (arg < 0.0) {
      phi[0] = 0.0;
    } else {
      phi[0] = sign(0.5 * sqrt(arg), (Phi[2][1] - Phi[1][2]));
    }
    arg = 1.0 + 2.0 * Phi[1][1] - tr;
    if (arg < 0.0) {
      phi[1] = 0.0;
    } else {
      phi[1] = sign(0.5 * sqrt(arg), (Phi[0][2] - Phi[2][0]));
    }
    arg = 1.0 + 2.0 * Phi[2][2] - tr;
    if (arg < 0.0) {
      phi[2] = 0.0;
    } else {
      phi[2] = sign(0.5 * sqrt(arg), (Phi[1][0] - Phi[0][1]));
    }
  } else {
    f00 = fabs(Phi[0][0] + 1.0);
    f11 = fabs(Phi[1][1] + 1.0);
    f22 = fabs(Phi[2][2] + 1.0);
    if ((f00 >= f11) && (f00 >= f22)) {
      arg    = 0.5 * (Phi[0][0] + 1.0);
      if (arg < 0.0) {
        phi[0] = 0.0;
      } else {
        phi[0] = sqrt(arg);
      }
      phi[1] = (Phi[0][1] + Phi[1][0]) / (4.0 * phi[0]);
      phi[2] = (Phi[0][2] + Phi[2][0]) / (4.0 * phi[0]);
    } else if (f11 >= f22) {
      arg    = 0.5 * (Phi[1][1] + 1.0);
      if (arg < 0.0) {
        phi[1] = 0.0;
      } else {
        phi[1] = sqrt(arg);
      }
      phi[0] = (Phi[1][0] + Phi[0][1]) / (4.0 * phi[1]);
      phi[2] = (Phi[1][2] + Phi[2][1]) / (4.0 * phi[1]);
    } else {
      arg    = 0.5 * (Phi[2][2] + 1.0);
      if (arg < 0.0) {
        phi[2] = 0.0;
      } else {
        phi[2] = sqrt(arg);
      }
      phi[0] = (Phi[2][0] + Phi[0][2]) / (4.0 * phi[2]);
      phi[1] = (Phi[2][1] + Phi[1][2]) / (4.0 * phi[2]);
    }
  }
  for (i=0; i<3; i++) {
    if (fabs(Phi[i][3]) > System.dtoll) lflag = TRUE;
  }
  return(lflag);
}
