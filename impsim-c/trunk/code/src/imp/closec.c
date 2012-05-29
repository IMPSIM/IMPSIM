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
/* closec-01 Jan 00:08 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Perform the iterative position analysis on the system geometry.
|
|     Access:
|       (void) closec();
|
|     Error Conditions:
|       System.nerror = 10 indicates that the system geometry will not
|     assemble with the given set of specified generalized positions.
|
|     Comments:
|       The Newton-Raphson iteration method is used to insure that all
|     kinematic loops satisfy the geometric loop closure conditions.
|       Up to System.cn iterations are allowed to achieve the accuracy
|     limits of System.ptola and System.ptoll.  The limits can be reset
|     via the ZERO POSITION command.
|       First kinematic derivatives of the dependent joint variables
|     with respect to the generalized coordinates are also found and
|     stored by this algorithm.
|       System.level = 7 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     22 Mar 03:JJU-Implemented use of itextc function.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void closec()
{
  int   i, irank, j, ngoto, nrows;
  int  *icol, *irow;
  real *E, quality;

/* Initialize. */
  System.qi = 1.0;
  System.ci = 0;
  ngoto     = 2;  /* See ajustc() for interpretation of ngoto values. */
  nrows     = 6 * System.nloops + System.nc;
  vzeroc(F_POSITION);
  vzeroc(F_VELOCITY);
  vzeroc(F_ACCEL);
  vzeroc(F_FORCE);
  if (System.level < 4) abortc();

/* Free any previously stored Jacobian and derivative matrices. */
  if (System.sysJ) free(System.sysJ);
  if (System.d1) {
    for (i=0; i<System.ndep; i++) {
      if (System.d1[i]) free(System.d1[i]);
    }
    free(System.d1);
    System.d1 = NULL;
  }
  if (System.d2) {
    for (i=0; i<System.ndep; i++) {
      if (System.d2[i]) {
        for (j=0; j<System.ndof; j++) {
          if (System.d2[i][j]) free(System.d2[i][j]);
        }
        free(System.d2[i]);
      }
    }
    free(System.d2);
    System.d2 = NULL;
  }

/* Acquire space for the Jacobian and related woking space. */
  System.sysJ = (real *) calloc(nrows * System.njvars, sizeof(real));
  E    = (real *) calloc(nrows, sizeof(real));
  irow = (int *)  calloc(nrows, sizeof(int));
  icol = (int *)  calloc(System.njvars, sizeof(int));

/* Calculate the internal length scaling factor. */
  scalec();

/* Form the joint transformation matrices. */
_ITERATE:
  pmatc();

/* Form the global transformation matrices. */
  tgtojc();

/* Form the derivative operator matrices. */
  dmatc();

/* Form the system geometry Jacobian matrix. */
  jmatc(nrows, System.njvars, System.sysJ, irow, icol);

/* Invert largest non-singular submatrix contained in System.sysJ. */
  irank   = 0;
  quality = 1.0;
  if (nrows > 0) invrtc(System.sysJ, nrows, System.njvars, System.nfree,
    System.fjtol, &irank, &quality, irow, icol);

/* Test for closure. */
  if (ngoto > 2) {
    System.nerror = 10;

/* Form the loop closure errors. */
  } else if (ngoto == 2) {
    if (System.ci < System.cn) {
      ematc(E);

/* Improve the joint variable estimates. */
      ngoto = ajustc(System.sysJ, E, irow, icol, irank);
      System.ci++;
      System.qi = fabs(quality);
      if (ngoto == 1) System.lscale = 1.0;
      if (System.nerror == 0) goto _ITERATE;
    } else {
      System.nerror = 10;
    }

/* Store the first kinematic derivative matrix. */
  } else {
    System.ndep  = irank;
    System.ndof  = System.njvars - System.ndep;
    System.nfgc  = System.ndof - System.nsgc;
    System.level = 6;
    fdervc(System.sysJ, irow, icol);
  }
  if (System.nerror) {
    if ((System.mode != MD_DYN) && (ngoto != 3)) {
      textc("*** The mechanism would not assemble in ", FALSE);
      itextc(System.ci);
      textc(" iterations. ***", TRUE);
    }
    System.level  = 4;
  }
  return;
}
