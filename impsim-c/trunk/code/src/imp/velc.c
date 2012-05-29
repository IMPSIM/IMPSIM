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
/* velc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Calculate and store the dependent joint variable velocities and
|     the body velocity operators (omega matrices).
|
|     Access:
|       (void) velc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       System.level = 8 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void velc()
{
  Body  *body, *bdybfr;
  Joint *joint;
  Jvar  *jvar;
  int    change, done, i, nogo, nrows;
  real  *phidot, psidot, *rhs, vmax, wmat[6];

/* Initialize and acquire working space. */
textc("velc 32:", TRUE);
  if (System.level < 7) abortc();
  vzeroc(F_VELOCITY);
  vzeroc(F_ACCEL);
  vzeroc(F_FORCE);
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    ldnanc((void *) body->W);
  }
  nrows  = 6 * System.nloops + System.nc;
  rhs    = (real *) calloc(nrows,       sizeof(real));
  phidot = (real *) calloc(System.ndep, sizeof(real));

/* Form the right-hand column vector. */
  for (i=0; i<nrows; i++) rhs[i] = 0.0;
  vmax = 0.0;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (jvar->jvrnoS >= System.ndep) {
        psidot = jvar->vel;
        if (psidot != 0.0) {
          vmax = max(psidot, vmax);
          for (i=0; i<6; i++) {
            wmat[i] = -(jvar->D[i] * psidot);
          }
          fillc(joint->loopflags, wmat, 1, rhs);
        }
      }
    }
  }

/* Calculate and store the dependent joint variable velocities. */
  nogo = dsolvc(System.sysJ, rhs, (vmax * System.ptola), phidot);
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (jvar->jvrnoS < System.ndep) {
        jvar->vel = phidot[jvar->jvrnoS];
      }
    }
  }
  free(rhs);
  free(phidot);

/* Calculate and store the velocity operator for each body. */
  for (i=0; i<6; i++) System.ground->W[i] = 0.0;
  do {
    change = FALSE;
    done   = TRUE;
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (isnanc((void *) &body->W[0])) {    /* This body is unknown. */
        done   = FALSE;     /* At least one body is not yet finished. */
        joint  = body->bdyAxs->axsJnt;
        bdybfr = joint->jntAxB->axsBdy;       
        if (isnanc((void *) &bdybfr->W[0])) { /* Check previous body. */
          change = TRUE;           /* Signal that something is found. */
          for (i=0; i<6; i++) {
            body->W[i] = bdybfr->W[i];
          }
          for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
            if (jvar->vel != 0.0) {
              for (i=0; i<6; i++) {
                body->W[i] += jvar->vel * jvar->D[i];
              }
            }
          }
        }
      }
    }
  } while (change && !done);
  if (done) System.level = max(8, System.level);
  return;
}
