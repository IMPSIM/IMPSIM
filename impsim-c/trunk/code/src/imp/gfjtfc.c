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
/* gfjtfc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of joint forces to the current values of the
|     generalized forces.
|
|     Access:
|       (void) gfjtfc(int nfgc, real G[]);
|     int  nfgc,     i-Number of free generalized coordinates.
|     real G[nfgc],i/o-Generalized forces on the system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds incremental changes to the total stiff-
|     ness matrix.  It assumes that K[] is initialized before entry.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void gfjtfc(int nfgc, real G[])
#else
  void gfjtfc(nfgc, G);
  int  nfgc;
  real G[];
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, njvar;

  if (System.level < 8) velc();
  if (System.nerror == 0) {
    if (nfgc > 0) {
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          njvar = jvar->jvrnoS;
          if (!isnanc((void *) &jvar->force)) {
            if (jvar->force != 0.0) {
              if (njvar < System.ndep) {
                for (i=0; i<nfgc; i++) {
                  G[i] += System.d1[njvar][i] * jvar->force;
                }
              } else {
                i = njvar - System.ndep;
                if ((i >= 0) && (i < nfgc)) G[i] += jvar->force;
              }
            }
          }
        }
      }
    }
  }
  return;
}
