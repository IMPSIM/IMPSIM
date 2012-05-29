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
/* tmgvtc-01 Jan 00:13 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the gravitational effects to the generalized forces for a 
|     motion input transfer function.
|
|     Access:
|       (void) tmgvtc(int ngc, real G[]);
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
  void tmgvtc(int ngc, real G[])
#else
  void tmgvtc(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Body *body;
  int   i;
  real  m, Rbar[3], Vi[3], Vj[3], W[6];

  if (vabsc(3, System.gravty) >= System.zero) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (body->bdyMas) {
        m = body->bdyMas->I[9];
        if (abs(m) >= System.zero) {
          for (i=0; i<3; i++) {
            Rbar[i] = body->bdyMas->I[i+6] / m;
          }
          mpyxrc(body->T0j, Rbar, Rbar);
          wmatc(body, ngc, W);
          mpydrc(W, Rbar, Vj);
          for (i=0; i<System.nfgc; i++) {
            accijc(body, i, ngc, W);
            mpydrc(W, Rbar, Vi);
            G[i] += m * vdotc(3, System.gravty, Vi);
            wmatc(body, i, W);
            vcrosc(W, Vj, Vi);
            G[i] += m * vdotc(3, System.gravty, Vi);
          }
        }
      }
    }
  }
  return;
}
