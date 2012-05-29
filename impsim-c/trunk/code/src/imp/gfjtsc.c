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
/* gfjtsc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of joint springs to the current values of the
|     generalized forces.
|
|     Access:
|       (void) gfjtsc(int nfgc, real G[]);
|     int  nfgc,     i-Number of free generalized coordinates.
|     real G[nfgc],i/o-Generalized forces on the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total general-
|     ized forces.  It assumes that G[] is initialized before entry.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void gfjtsc(int nfgc, real G[])
#else
  void gfjtsc(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, j, njvar;
  real   f;

  if (nfgc > 0) {
    if (System.level < 8) velc();
    if (System.nerror == 0) {
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          njvar = jvar->jvrnoS;
          if (!isnanc((void *) &jvar->k)) {
            f = jvar->k * (jvar->pos - jvar->freepos);
            if (f != 0.0) {
              j = njvar - System.ndep;
              if (njvar < System.ndep) {
                for (i=0; i<nfgc; i++) {
                  G[i] -= System.d1[njvar][i] * f;
                }
              } else if (j < nfgc) {
                G[j] -= f;
              }
            }
          }
        }
      }
    }
  }
  return;
}
