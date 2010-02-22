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
/* eqjstc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Adjust the joint variables for one step of the equilibrium
|     search.
|
|     Access:
|       lflag = (int) eqjstc(int nfgc, real KinvG[], real G[],
|         int icol[]);
|     int  nfgc,   i-Number of free generalized coordinates.
|     real KinvG[],i-The nfgc+1 column of this matrix holds the changes
|       for the FGC variables predicted by invrtc() on K[] x = G.
|     real G[],    i-Generalized unbalanced forces on the FGC's.
|     int  icol[], i-Rearranged column numbers from invrtc() on K[].
|     int  lflag,  o-Logical result ofequilibrium search convergence.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If the system is near to stable equilibrium then the Newton-
|     Raphson method is used because of its rapid convergence; if the
|     system approaches unstable equilibrium, however, this step is
|     taken by a gradient search method.
|       lflag = TRUE is returned if all FGC joint variable changes are
|     smaller than System.etola and System.etoll; these may be modified
|     by a ZERO EQUILIBRIUM command.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int eqjstc(int nfgc, real KinvG[], real G[], int icol[])
#else
  int eqjstc(nfgc, KinvG, G, icol)
  int  nfgc;
  real KinvG[], G[];
  int  icol[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, j, kcol, lflag, m;
  real   delta, denrgy, size, tol; 

/* Test for stable or unstable equilibrium. */
  lflag = TRUE;
  kcol  = nfgc + 1;
  size  = vabsc(nfgc, G);
  if (size > System.zero) {
    size = min(1.0, 1.0 / size);
    denrgy = 0.0;
    for (i=0; i<System.krank; i++) {
      denrgy += KinvG[i * kcol + nfgc] * G[icol[i]];
    }

/* Switch to gradient search for unstable or neutral FGC's. */
    m = System.krank;
    if (denrgy > 0.0) m = 0;     /* Remember invrtc() leaves -[KinvG] */
    for (i=m; i<nfgc; i++) {
      KinvG[i * kcol + nfgc] = -size * G[icol[i]];
    }

/* Scale step size, if necessary, to avoid large geometry change. */
    size = 0.0;
    for (i=0; i<nfgc; i++) {
      j = i * kcol + nfgc;
      size += KinvG[j] * KinvG[j];
    }
    if (size > 1.0) {
      size = 1.0 / sqrt(size);
      for (i=0; i<nfgc; i++) {
        KinvG[i * kcol + nfgc] *= size;
      }
    }

/* Increment the FGC joint variable values. */
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        j = jvar->jvrnoS - System.ndep;
        if ((j >= 0) && (j < nfgc)) {
          for (i=0; i<nfgc; i++) {
            if (icol[i] == j) break;
          }
          delta = -KinvG[i * kcol + nfgc];
          if (jvar->jvrtyp == JV_ANGULAR) {
            tol = System.etola;
          } else {
            tol = System.etoll;
          }
          if (fabs(delta) > tol) lflag = FALSE;
          jvar->pos += delta;
        }
      }
    }

/* Increment the dependent joint variables to match. */
    adjstc();
  }
  return(lflag);
}
