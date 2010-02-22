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
/* tmdync-01 Jan 00:15 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Add the inertial effects of a joint motion input to the genera-
|     lized forces for a transfer function.
|
|     Access:
|       (void) tmdync(int ngc, real G[]);
|     int  ngc,      i-number for the input motion coordinate.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This function assumes that the G[] array has been initialized 
|     before entry and that other effects are added elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void tmdync(int ngc, real G[])
#else
  void tmdync(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Body *body;
  int  i;
  real W[6], A[3][4], xjxtr[4][4];

  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (body->bdyMas) {
      xjxtrc(body->T0j, body->bdyMas->I, xjxtr);
      wmatc(body, ngc, W);
      A[0][0] =  0.0;
      A[0][1] = -W[5];
      A[0][2] =  W[4];
      A[0][3] =  W[0];
      A[1][0] =  W[5];
      A[1][1] =  0.0;
      A[1][2] = -W[3];
      A[1][3] =  W[1];
      A[2][0] = -W[4];
      A[2][1] =  W[3];
      A[2][2] =  0.0;
      A[2][3] =  W[2];
      for (i=0; i<System.nfgc; i++) {
        wmatc(body, i, W);
        G[2*System.nfgc+i] -= trwjwc(W, xjxtr, A);
      }
    }
  }
  return;
}
