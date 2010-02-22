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
/* mpydrc-01 Jan 00:15 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Multiply a derivative operator D by a homogeneous coordinate
|     position vector r, and store the result in the vector Dr = D * r.
|
|     Access:
|       (void) mpydrc(real D[6], real r[3], real Dr[3]);
|     real D[6], i-The derivative operator.
|     real r[3], i-The coordinates of the given position vector;
|       stored with the last coordinate implied as 1.0.
|     real Dr[3],o-The components of the product vector, stored in
|       homogeneous form with the last component implied as 0.0.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If desired, the product vector Dr may overwrite the given posi-
|     tion vector r as follows: mpydrc(D, r, r).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void mpydrc(real D[6], real r[3], real Dr[3])
#else
  void mpydrc(D, r, Dr)
  real D[6], r[3], Dr[3];
#endif
{
  int j;

  vcrosc(&D[3], r, Dr);
  for (j=0; j<3; j++){
    Dr[j] += D[j];
  }
  return;
}
