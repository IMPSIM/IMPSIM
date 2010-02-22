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
/* dynm1c-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form and store the corrected FGC accelerations from the second
|     order equations of motion.
|
|     Access:
|       (void) dynm1c(int nfgc, real MDKG[], int icol[]);
|     int  nfgc,  i-Number of free generalized coordinates.
|     real MDKG[],i-Coefficients [M-1|M-1D|M-1K|M-1G] after invrtc();
|     int  icol[],i-Column order indices from invrtc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       System.level <=9 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dynm1c(int nfgc, real MDKG[], int icol[])
#else
  void dynm1c(nfgc, MDKG, icol)
  int  nfgc;
  real MDKG[];
  int  icol[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, ngc, nkol, n3;

/* Find {acc} = {M-1G} - [M-1D]{vel} for generalized accelerations. */
/* Note that [M-1K]{x} is ignored since {x} == 0 for this position. */
  n3 = 3 * nfgc;
  nkol = n3 + 1;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      ngc = jvar->jvrnoS - System.ndep;
      if ((ngc >= 0) && (ngc < nfgc)) {
        if (jvar->vel != 0.0) {
          for (i=0; i<nfgc; i++) {
            MDKG[i*nkol+n3] -= MDKG[i*nkol+nfgc+ngc] * jvar->vel;
          }
        }
      }
    }
  }

/* Store new generalized accelerations in jvar records. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      ngc = jvar->jvrnoS - System.ndep;
      if ((ngc >= 0) && (ngc < nfgc)) {
        for (i=0; i<nfgc; i++) {
          if (ngc == icol[i]) {
            jvar->acc = -MDKG[i*nkol+n3];/* Minus sign from invrtc(). */
            break;
          }
        }
      }
    }
  }
  System.level = min(9, System.level);
  return;
}
