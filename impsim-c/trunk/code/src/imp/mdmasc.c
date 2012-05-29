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
/* mdmasc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Calculate the modal masses and normalize the eigenvectors.
|
|     Access:
|       (void) mdmasc(real M[], real D[], complex Eigvct[]);
|     real M[nfgc,nfgc],i-The second order system mass matrix.
|     real D[nfgc,nfgc],i-The second order system damping matrix.
|     complex Eigvct[2*nfgc,2*nfgc],i/o-The matrix of eigenvectors.
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
  void mdmasc(real M[], real D[], complex Eigvct[])
#else
  void mdmasc(M, D, Eigvct)
  real   M[], D[];
  complex Eigvct[];
#endif
{
  complex mdmass, save1, save2, temp, temp1, temp2;
  int i, j, jk, k, ki, nfgc, n2;
  
  nfgc = System.nfgc;
  n2 = nfgc + nfgc;
  for (i=0; i<n2; i++){
    save1 = cmplxc(0.0, 0.0);
    save2 = cmplxc(0.0, 0.0);
    for (j=0; j<nfgc; j++){
      temp1 = cmplxc(0.0, 0.0);
      temp2 = cmplxc(0.0, 0.0);
      for (k=0; k<nfgc; k++){
        ki = (nfgc + k) * n2 + i;
        jk = j * nfgc + k;
        temp1.r += M[jk] * Eigvct[ki].r;
        temp1.i += M[jk] * Eigvct[ki].i;
        temp2.r += D[jk] * Eigvct[ki].r;
        temp2.i += D[jk] * Eigvct[ki].i;
      }
      temp = cmultc(temp1, Eigvct[j*n2+i]);
      save1.r += temp.r;
      save1.i += temp.i;
      temp = cmultc(temp2, Eigvct[(nfgc+j)*n2+i]);
      save2.r += temp.r;
      save2.i += temp.i;
    }
    mdmass.r = 2.0 * save1.r + save2.r;
    mdmass.i = 2.0 * save1.i + save2.i;
    if (cabsc(mdmass) < System.dytol) mdmass = cmplxc(System.dytol,0.0);
    temp = cdivc(cmplxc(1.0, 0.0), csqrtc(mdmass));
    for (k=0; k<n2; k++){
      ki = k * n2 + i;
      Eigvct[ki] = cmultc(Eigvct[ki], temp);
    }
  }
  return;
}
