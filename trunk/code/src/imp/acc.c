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
/* acc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Calculate and store the dependent joint variable accelerations
|     and the body acceleration operators (alpha matrices).
|
|     Access:
|       (void) acc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       System.level = 10 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void acc()
{
  Body  *body, *bdbfr;
  Joint *joint;
  Jvar  *jvar;
  int    i, ic, jv, lchange, ldone, nogo, noJ, nrows;
  real   amax, ddmat[6], d2mat[6], *phi2dot, *rhs, omega[6];

/* Initialize and acquire working space. */
textc("acc 32:", TRUE);
  if (System.level < 9) sdervc();
  if (System.nerror) return;
  vzeroc(F_ACCEL);
  vzeroc(F_FORCE);
textc("acc 39:", TRUE);
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    ldnanc((void *) body->A);
  }
textc("acc 43:", TRUE);
  if (System.nloops > 0) {
    nrows   = 6 * System.nloops + System.nc;
    rhs     = (real *) calloc(nrows,       sizeof(real));
    phi2dot = (real *) calloc(System.ndep, sizeof(real));

/* Form the right-hand column vector. */
    for (i=0; i<nrows; i++) rhs[i] = 0.0;
    ic = 6 * System.nloops;
    amax = 0.0;
    if (System.ndof > 0) {
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        bdbfr = joint->jntAxB->axsBdy;
        for (i=0; i<6; i++) {
          omega[i] = bdbfr->W[i];
          d2mat[i] = 0.0;
        }
textc(joint->name, FALSE);
textc("acc 63:", TRUE);
        for (jv=0; jv<joint->njvars; jv++) {
          noJ  = (joint->orient < 0) ? (joint->njvars-1-jv) : jv;
          jvar = joint->jntJvr;
          while (jvar->jvrnoJ != noJ) jvar = jvar->nxtJvr;
          if (jvar->jvrnoS >= System.ndep) {
            if (jvar->vel != 0.0) {
              amax = max(amax, jvar->vel * jvar->vel);
            }
            if (jvar->acc != 0.0) {
              for (i=0; i<6; i++) d2mat[i] -= jvar->D[i] * jvar->acc;
              amax = max(amax, jvar->acc);
            }
          }
          if (jvar->vel != 0.0) {
            ddmatc(jvar, omega, jvar->vel, ddmat);
            for (i=0; i<6; i++) {
              omega[i] += jvar->D[i] * jvar->vel;
              d2mat[i] -=   ddmat[i] * jvar->vel;
            }
            switch (joint->jtype) {
            case OPEN:
              if (jvar->jvrnoJ < 3) break;
            case SPHERE:
              rhs[ic] -= 2.0 * jvar->vel * jvar->vel;
            }
          }
        }
textc("acc 90:", TRUE);
textc("acc 91:", TRUE);
        fillc(joint->loopflags, d2mat, 1, rhs);
        switch (joint->jtype) {
        case OPEN:
        case SPHERE:
          ic++;
        }
      }
    }

/* Calculate and store the dependent joint variable accelerations. */
    nogo = dsolvc(System.sysJ, rhs, (amax * System.ptola), phi2dot);
itextc(nogo);
textc("acc 100:", TRUE);
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrnoS < System.ndep) {
          jvar->acc = phi2dot[jvar->jvrnoS];
        }
      }
    }
    free(rhs);
    free(phi2dot);
  }

/* Calculate and store the acceleration operator for each body. */
  for (i=0; i<6; i++) System.ground->A[i] = 0.0;
  do {
    lchange = FALSE;
    ldone   = TRUE;
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (isnanc((void *) &body->A[0])) {
        ldone = FALSE;                 /* This A[] matrix is unknown. */
        joint = body->bdyAxs->axsJnt;
        bdbfr = joint->jntAxB->axsBdy;
        if (!isnanc((void *) &bdbfr->A[0])) { /* Is previous A known? */
          lchange = TRUE;           /* Yes; so this A[] can be found. */
          for (i=0; i<6; i++) {
            omega[i]   = bdbfr->W[i];
            body->A[i] = bdbfr->A[i];
          }
          for (jv=0; jv<joint->njvars; jv++) {
            noJ  = (joint->orient < 0) ? (joint->njvars-1-jv) : jv;
            jvar = joint->jntJvr;
            while (jvar->jvrnoJ != noJ) jvar = jvar->nxtJvr;
            if (jvar->acc != 0.0) {            
              for (i=0; i<6; i++) {
                body->A[i] += jvar->D[i] * jvar->acc;
              }
            }
            if (jvar->vel != 0.0) {
              ddmatc(jvar, omega, jvar->vel, ddmat);
              for (i=0; i<6; i++) {
                omega[i]   += jvar->D[i] * jvar->vel;
                body->A[i] +=   ddmat[i] * jvar->vel;
              }
            }
          }
        }
      }
    }
  } while (lchange && !ldone);
  System.level = max(10, System.level);
textc("acc 141:", TRUE);
  return;
}
