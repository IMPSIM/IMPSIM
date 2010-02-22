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
/* tnumrc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the numerators for the generalized transfer functions.
|
|     Access:
|       (void) tnumrc(complex Eigvct[], real G[], complex Tnumr[]);
|     complex Eigvct[2*nfgc,2*nfgc],i-The matrix of eigenvectors.
|     real    G[3,nfgc],            i-The generalized forces.
|     complex Tnumr[3,nfgc,2*nfgc], o-The transfer function numerators.
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
  void tnumrc(complex Eigvct[], real G[], complex Tnumr[])
#else
  void tnumrc(Eigvct, G, Tnumr)
  real    G[];
  complex Eigvct[], Tnumr[];
#endif
{
  complex save;
  int     i, ijk, il, j, jk, k, l, lk, nfgc, n2;

  nfgc = System.nfgc;
  n2   = nfgc + nfgc;
  for (j=0; j<nfgc; j++) {
    for (k=0; k<n2; k++){
      jk  = (nfgc + j) * n2 + k;
      for (i=0; i<3; i++){
        save.r = 0.0;
        save.i = 0.0;
        for (l=0; l<nfgc; l++){
          il = i * nfgc + l;
          lk = (nfgc + l) * n2 + k;
          save.r += G[il] * Eigvct[lk].r;
          save.i += G[il] * Eigvct[lk].i;
        }
        ijk = i * (nfgc * n2) + j * n2 + k;
        Tnumr[ijk] = cmultc(save, Eigvct[jk]);
      }
    }
  }
  return;
}
