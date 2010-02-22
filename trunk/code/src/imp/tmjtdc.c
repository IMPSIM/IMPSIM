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
/* tmjtdc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the joint damping effects to the generalized forces for a 
|     motion input transfer function.
|
|     Access:
|       (void) tmjtdc(int ngc, real G[]);
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
  void tmjtdc(int ngc, real G[])
#else
  void tmjtdc(ngc, G)
  int  ngc;
  real G[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int   i, ndep, nfgc, njvar;
  real  rate;

  ndep = System.ndep;
  nfgc = System.nfgc;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      if (!isnanc((void *) &jvar->c)) {
        njvar = jvar->jvrnoS;
        if (njvar < ndep) {
          rate = jvar->c * System.d1[njvar][ngc];
          if (abs(rate) > System.zero) {
            for (i=0; i<nfgc; i++) {
              G[nfgc+i] -= rate * System.d1[njvar][i];
            }
          }
        }
      }
    }
  }
  return;
}
