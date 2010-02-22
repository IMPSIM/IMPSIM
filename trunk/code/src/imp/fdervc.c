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
/* fdervc-01 Jan 00:12 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Store the first derivatives of the joint variables with respect
|     to the generalized coordinates.
|
|     Access:
|       (void) fdervc(real Jinv[], int irow[], int icol[]);
|     real Jinv[],i-Inverse of the Jacobian matrix in the rearranged
|       order left by invrtc().
|     int irow[], i-Rearranged row numbers left by invrtc().
|     int icol[], i-Rearranged column numbers left by invrtc().
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The first kinematic derivatives are already calculated and are
|     currently stored as the final columns of the Jinv[] matrix.  This
|     routine copies them.  It then renumbers the Jvar records into the
|     order defined by icol[] and copies the irow[] values into the
|     System.ndep column of Jinv[] for later use.
|       System.level = 7 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void fdervc(real Jinv[], int irow[], int icol[])
#else
  void fdervc(Jinv, irow, icol)
  real Jinv[];
  int  irow[], icol[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int i, j, k;

/* Acquire space for the first kinematic derivatives. */
  if (System.level >= 7) return;
  if (System.level < 6) abortc();
  System.d1 = (real **) calloc(System.ndep, sizeof(real *));
  for (i=0; i<System.ndep; i++) {
    System.d1[i] = (real *) calloc(System.ndof, sizeof(real));
  }

/* Store the first derivatives. */
  k = System.ndep;
  for (i=0; i<System.ndep; i++) {
    for (j=0; j<System.ndof; j++) {
      System.d1[i][j] = Jinv[k+j];
    }
    k += System.njvars;
  }

/* Rearrange the joint variable numbering to match Jinv columns. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      for (i=0; i<System.njvars; i++) {
        if (icol[i] == jvar->jvrnoS) {
          jvar->jvrnoS = i;
          break;
        }
      }
    }
  }

/* Store the Jinv row numbers. */
  k = System.ndep;
  for (i=0; i<6*System.nloops+System.nc; i++) {
    Jinv[k] = (real) irow[i];
    k += System.njvars;
  }
  System.level = 7;
  return;
}
