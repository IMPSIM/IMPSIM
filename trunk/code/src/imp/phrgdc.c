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
/* phrgdc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       From the transformation matrix for a rigid joint and test for
|     errors in design position data.
|
|     Access:
|       lflag = (int) phrgdc(real Phi[3][4]);
|     real Phi[3][4],i-Transformation matrix for the joint.
|     int  lflag,o-Flag set TRUE for imprecise data.
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
  int phrgdc(real Phi[3][4])
#else
  int phrgdc(Phi)
  real Phi[3][4];
#endif
{
  int i, lflag;

  lflag = FALSE;
  for (i=0; i<3; i++) {
    if (fabs(Phi[i][3]) > System.dtoll) lflag = TRUE;
    if (fabs(Phi[i][i] - 1.0) > System.dtola) lflag = TRUE;
  }
  return(lflag);
}
