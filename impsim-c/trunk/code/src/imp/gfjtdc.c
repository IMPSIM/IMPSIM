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
/* gfjtdc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of joint damping to the current vector of gener-
|     alized forces.
|
|     Access:
|       (void) gfjtdc(int nfgc, real G[]);
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
  void gfjtdc(int nfgc, real G[])
#else
  void gfjtdc(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Joint *joint, *jnt;
  Jvar  *jvar, *jvr;
  int    i, ndf, njvar;
  real   fdamp, vel;

/* Initialize. */
  if (System.mode == MD_STAT) return;
  if (System.level < 8) velc();
  if (System.nerror) return;
  if (nfgc > 0) {

/* Loop through all joint variables having damping. */
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (!isnanc((void *) &jvar->c)) {
          if (jvar->c != 0.0) {

/* Find the damping force in this joint variable. */
            njvar = jvar->jvrnoS;
            if (njvar >= System.ndep + nfgc) {
              vel = jvar->vel;
            } else if (njvar < System.ndep) {
              vel = 0.0;
              for (jnt=System.sysJnt; jnt; jnt=jnt->nxtJnt) {
                for (jvr=jnt->jntJvr; jvr; jvr=jvr->nxtJvr) {
                  ndf = jvr->jvrnoS - System.ndep;
                  if (ndf >= nfgc) {
                    vel += System.d1[njvar][ndf] * jvr->vel;
                  }
                }
              }
            }
            fdamp = -jvar->c * vel;

/* Add the effects to the generalized coordinates. */
            if (fdamp != 0.0) {
              if (njvar >= System.ndep) {
                ndf = njvar - System.ndep;
                if (ndf < nfgc) G[ndf] += fdamp;
              } else {
                for (i=0; i<nfgc; i++) {
                  G[i] += System.d1[njvar][i] * fdamp;
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}
