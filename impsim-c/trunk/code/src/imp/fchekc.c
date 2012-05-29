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
/* fchekc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Calculate the unexplained forces in the system as evaluated by 
|     the equations of motion.
|
|     Access:
|       (void) fchekc(int nfgc, real M[], real D[], real G[],
|         real *dforce, real *percnt);
|     int   nfgc,        i-The number of free generalized coordinates.
|     real  M[nfgc,nfgc],i-System mass matrix.
|     real  D[nfgc,nfgc],i-System damping matrix.
|     real  G[nfgc],     i-System generalized force vector.
|     real *dforce,      o-Size of largest generalized force imbalance.
|     real *percnt,      o-Largest force imbalance expressed as percent.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The assumption here is that any difference between the general-
|     ized forces calculated and those found on the left side of the
|     equations of motion can only be explained by errors stemming from
|     linearizing the equations of motion.  Thus *dforce and *percnt are
|     returned as a measure of this discrepency so that they can be used 
|     to adjust the variable timestep. 
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void fchekc(int nfgc, real M[], real D[], real G[], real *dforce,
    real *percnt)
#else
  void fchekc(nfgc, M, D, G, dforce, percnt)
  int  nfgc;
  real M[], D[], G[], *dforce, *percnt;
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, ii, j;
  real   dG, Gi, Gsize;

  *dforce = 0.0;
  *percnt = 0.0;
  Gsize = vabsc(nfgc, G);
  for (i=0; i<nfgc; i++) {
    ii = i * nfgc;
    Gi = 0.0;
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        j = jvar->jvrnoS - System.ndep;
        if (j >= 0) {
          if (j < nfgc) {
            Gi += M[ii+j] * jvar->acc + D[ii+j] * jvar->vel;
          }
        }
      }
    }
    dG = fabs(G[i] - Gi);
    if (dG > *dforce) {
      *dforce = dG;
      *percnt = dG / Gsize;
    }
  }
  return;
}
