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
/* gfdync-01 Jan 00:15 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Add the effects of the moving masses to the current vector of
|     generalized forces.
|
|     Access:
|       (void) gfdync(int nfgc, real G[]);
|     int nfgc,      i-Number of free generalized coordinates.
|     real G[nfgc],i/o-Generalized forces of the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total of all
|     generalized forces.  It assumes that G[] is initialized elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void gfdync(int nfgc, real G[])
#else
  void gfdync(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Body  *body;
  Joint *jointj, *jointk;
  Jvar  *jvarj, *jvark;
  int    i, j, k;
  real   A[6], *phi2dot, velsq, W[6], WW[3][4], xJx[4][4];

/* Form the second derivatives for aldync(). */
  phi2dot = (real *) calloc(System.njvars, sizeof(real));
  for (i=0; i<System.njvars; i++) phi2dot[i] = 0.0;
  for (jointj=System.sysJnt; jointj; jointj=jointj->nxtJnt) {
    for (jvarj=jointj->jntJvr; jvarj; jvarj=jvarj->nxtJvr) {
      j = jvarj->jvrnoS - System.ndep;
      if (j >= 0) {
        if(jvarj->vel != 0.0) {
          for (jointk=System.sysJnt; jointk; jointk=jointk->nxtJnt) {
            for (jvark=jointk->jntJvr; jvark; jvark=jvark->nxtJvr) {
              k = jvark->jvrnoS - System.ndep;
              if (k >= 0) {
                if(jvark->vel != 0.0) {
                  velsq = jvarj->vel * jvark->vel;
                  for (i=0; i<System.ndep; i++) {
                    phi2dot[i] += System.d2[i][j][k] * velsq;
                  }
                }
              }
            }
          }
        }
      }
      if (j >= nfgc) {
        if(jvarj->acc != 0.0) {
          for (i=0; i<System.ndep; i++) {
            phi2dot[i] += System.d1[i][j] * jvarj->acc;
          }
          phi2dot[System.ndep+j] += jvarj->acc;
        }
      }
    }
  }

/* Loop through all bodies having mass. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (body->bdyMas) {
      xjxtrc(body->T0j, body->bdyMas->I, xJx);
      mpyddc(body->W, body->W, WW);
      aldync(body, phi2dot, A);
      WW[0][1] -= A[2];
      WW[0][2] += A[1];
      WW[0][3] += A[3];
      WW[1][0] += A[2];
      WW[1][2] -= A[0];
      WW[1][3] += A[4];
      WW[2][0] -= A[1];
      WW[2][1] += A[0];
      WW[2][3] += A[5];

/* Add contributions to the generalized forces. */
      for (j=0; j<nfgc; j++) {
        wmatc(body, j, W);
        G[j] -= trwjwc(W, xJx, WW);
      }
    }
  }
  free (phi2dot);
  return;
}
