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
/* ematc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the right-hand side of the iterative loop closure equation.
|
|     Access:
|       (void) ematc(real E[]);
|     real E[6*System.nloops+System.nc],o-Loop closure error vector.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void ematc(real E[])
#else
  void ematc(E)
  real E[];
#endif
{
  Axes  *axes, *oldaxes;
  Body  *body, *lastbody;
  Joint *joint;
  Jvar  *jvar;
  int    i, j, k, loop;
  long   mask;
  real   Sinv[3][4], xform[3][4];

/* Initialize. */
  loop = 0;
  mask = 1;
  while (loop < System.nloops) {

/* Trace a loop. */
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (body->loopflags & mask) break;   /* Find a body in the loop.*/
    }
    if (body == NULL) abortc();
    for (i=0; i<3; i++) {
      for (j=0; j<4; j++) {
        xform[i][j] = body->T0j[i][j];    /* Copy the T0j xformation. */
      }
    }
    lastbody = body;
    oldaxes  = NULL;
    do {
      for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
        if (axes == oldaxes) continue;  /* Avoid retracing same path. */
        if ((axes->loopflags & mask) == 0) continue; /* Stay in loop. */
        joint = axes->axsJnt;              /* Find an adjacent joint  */
        if ((joint->loopflags & mask) == 0) continue;/* in this loop  */
        if (joint->jntAxB == axes) break;/* where joint follows body. */
      }
      if (axes == NULL) abortc();
      mpyxxc(xform, axes->S, xform);/* Transform to before the joint  */
      mpyxxc(xform, joint->Phi, xform);       /* then past the joint  */
      axes = joint->jntAxA;
      invxc(axes->S, Sinv);
      mpyxxc(xform, Sinv, xform);      /* then to the next body axes. */
      body = axes->axsBdy;
      oldaxes = axes;
    } while (body != lastbody);
    invxc(xform, xform);            /* From T0j of lastbody find Tj0. */
    mpyxxc(body->T0j, xform, xform);   /* Now find T00 for this loop. */

/* Fill in loop closure error for this loop. */
    k = 6 * loop;
    E[k  ] = xform[0][3] / System.lscale;
    E[k+1] = xform[1][3] / System.lscale;
    E[k+2] = xform[2][3] / System.lscale;
    E[k+3] = xform[2][1] + xform[2][2] + xform[1][1] - 2.0;
    E[k+4] = xform[0][2] + xform[0][0] + xform[2][2] - 2.0;
    E[k+5] = xform[1][0] + xform[1][1] + xform[0][0] - 2.0;
    loop++;
    mask <<= 1;
  }

/* Fill in constraint equation values for Euler parameters. */
  k = 6 * System.nloops;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (joint->jtype == SPHERE || joint->jtype == OPEN) {
      E[k] = 1.0;
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (joint->jtype == SPHERE || jvar->jvrnoJ > 2) {
          E[k] -= jvar->pos * jvar->pos;
        }
      }
      k++;
    }
  }
  return;
}
