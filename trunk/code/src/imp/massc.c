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
/* massc-01 Jan 00:13 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form the dynamic mass matrix of the second order system.
|
|     Access:
|       (void) massc(int nfgc, real M[]);
|     int nfgc,         i-Number of free generalized coordinates.
|     real M[nfgc,nfgc],o-Second order mass matrix of the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void massc(int nfgc, real M[])
#else
  void massc(nfgc, M)
  int  nfgc;
  real M[];
#endif
{
  Body *body;
  Mass *mass;
  int   i, j;
  real  Wi[6], Wj[6], W[3][4], xjx[4][4];

  for (i=0; i<nfgc; i++) {
    for (j=0; j<=i; j++) {
      M[i*nfgc+j] = 0.0;
    }
  }
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    mass = body->bdyMas;
    if (mass) {
      xjxtrc(body->T0j, mass->I, xjx);
      for (i=0; i<nfgc; i++) {
        wmatc(body, i, Wi);
        W[0][0] =  0.0;
        W[0][1] = -Wi[2];
        W[0][2] =  Wi[1];
        W[0][3] =  Wi[3];
        W[1][0] =  Wi[2];
        W[1][1] =  0.0;
        W[1][2] = -Wi[0];
        W[1][3] =  Wi[4];
        W[2][0] = -Wi[1];
        W[2][1] =  Wi[0];
        W[2][2] =  0.0;
        W[2][3] =  Wi[5];
        for (j=0; j<=i; j++) {
          wmatc(body, j, Wj);
          M[i*nfgc+j] += trwjwc(Wj, xjx, W);
        }
      }
    }
  }
  for (i=0; i<nfgc; i++) {
    for (j=0; j<i; j++) {
      M[j*nfgc+i] = M[i*nfgc+j];
    }
  }
  return;
}
