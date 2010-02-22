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
/* sdervc-01 Jan 00:14 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Calculate and store the second derivatives of the dependent
|     joint variables with respect to the generalized coordinates.
|
|     Access:
|       (void) sdervc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       System.level = 9 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void sdervc()
{
  Body  *bdbfr;
  Joint *joint;
  Jvar  *jvar;
  int    i, ic, j, jv, k, nogo, noJ, nrows;
  real   ampyj, ampyk, ddmat[6], d2mat[6], *phi2d, *rhs, wmat[6];

/* Acquire and initialize space. */
textc("sdervc 32:", TRUE);
  if (System.level >= 9) return;
  if (System.level < 8) velc();
  if (System.nerror) return;
  if ((System.nloops > 0) && (System.ndof > 0)) {
    System.d2 = (real ***) calloc(System.ndep, sizeof(real **));
    for (i=0; i<System.ndep; i++) {
      System.d2[i] = (real **) calloc(System.ndof, sizeof(real *));
      for (j=0; j<System.ndof; j++) {
        System.d2[i][j] = (real *) calloc(System.ndof, sizeof(real));
      }
    }
    nrows = 6 * System.nloops + System.nc;
    rhs   = (real *) calloc(nrows,       sizeof(real));
    phi2d = (real *) calloc(System.ndep, sizeof(real));

/* Form each right-hand column vector. */
    for (j=0; j<System.ndof; j++) {
      for (k=0; k<System.ndof; k++) {
        for (i=0; i<nrows; i++) rhs[i] = 0.0;
        ic = 6 * System.nloops;
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          bdbfr = joint->jntAxB->axsBdy;
          wmatc(bdbfr, k, wmat);
          for (jv=0; jv<joint->njvars; jv++) {
            jvar = joint->jntJvr;
            noJ  = (joint->orient < 0) ? (joint->njvars-1-jv) : jv;
            while (jvar->jvrnoJ != noJ) jvar = jvar->nxtJvr;
            if (jvar->jvrnoS < System.ndep) {
              ampyj = System.d1[jvar->jvrnoS][j];
              ampyk = System.d1[jvar->jvrnoS][k];
            } else {
              ampyj = (jvar->jvrnoS == System.ndep + j) ? 1.0 : 0.0;
              ampyk = (jvar->jvrnoS == System.ndep + k) ? 1.0 : 0.0;
            }
            if (ampyj != 0.0) {
              ddmatc(jvar, wmat, k, ddmat);
              for (i=0; i<6; i++) {
                d2mat[i] = -ddmat[i] * ampyj;
              }
              fillc(joint->loopflags, d2mat, 1, rhs);
            }
            switch (joint->jtype) {
            case OPEN:
              if (jvar->jvrnoJ < 3) break;
            case SPHERE:
              rhs[ic] -= 2.0 * ampyj * ampyk;
            }
            if (ampyk != 0.0) {
              for (i=0; i<6; i++) wmat[i] += jvar->D[i] * ampyk;
            }
          }
          if ((joint->jtype == SPHERE) || (joint->jtype == OPEN)) ic++;
        }
     
/* Calculate and store the dependent joint variable 2nd derivatives. */
        nogo = dsolvc(System.sysJ, rhs, System.ptola, phi2d);
        for (i=0; i<System.ndep; i++) {
          System.d2[i][j][k] = phi2d[i];
          System.d2[i][k][j] = phi2d[i];
        }
      }
    }
    free(rhs);
    free(phi2d);
  }
  System.level = max(9, System.level);
  return;
}
