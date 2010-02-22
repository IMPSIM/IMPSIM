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
/* tmjtsc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Add the joint stiffness effects to the generalized forces for a 
|     motion input transfer function.
|
|     Access:
|       (void) tmjtsc(int ngc, real G[]);
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
  void tmjtsc(int ngc, real G[])
#else
  void tmjtsc(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int   i, ndep, nfgc, njvar;
  real  rate;

  if (System.level < 9) {
    sdervc();
    if (System.nerror) goto _1;
  }
  ndep = System.ndep;
  nfgc = System.nfgc;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (!isnanc((void *) &jvar->k)) {
        njvar = jvar->jvrnoS;
        if (njvar < ndep) {
          rate = jvar->k * (jvar->pos - jvar->freepos);
          if (abs(rate) > System.zero) {
            for (i=0; i<nfgc; i++) {
              G[i] -= rate * System.d2[njvar][ngc][i];
            }
          }
          rate = jvar->k * System.d1[njvar][ngc];
          if (abs(rate) > System.zero) {
            for (i=0; i<nfgc; i++) {
              G[i] -= rate * System.d1[njvar][i];
            }
          }
        }
      }
    }
  }
_1:
  return;
}
