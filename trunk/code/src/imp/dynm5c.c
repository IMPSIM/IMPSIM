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
/* dynm5c-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the eigenvalue problem for the FGC motions.
|
|     Access:
|       (void) dynm5c(int nfgc, real MDKG[], int irow[], real Dyn[]);
|     int  nfgc,               i-Number of free generalized coords.
|     real MDKG[nfgc,3*nfgc+1],i-Coefficients [M-1|M-1D|M-1K|M-1G].
|     int  irow[nfgc],         i-Row ordering array from invrtc().
|     real Dyn[2*nfgc,2*nfgc], o-Matrix for the eigenvalue problem.
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
  void dynm5c(int nfgc, real MDKG[], int irow[], real Dyn[])
#else
  void dynm5c(nfgc, MDKG, irow, Dyn)
  int  nfgc;
  real MDKG[];
  int  irow[];
  real Dyn[];
#endif
{
  int   i, ii, iii, j, nkol, n2;

  n2   = nfgc + nfgc;
  nkol = nfgc + n2 + 1;
  for (i=0; i<nfgc; i++) {
    ii = (nfgc + i) * n2;
    for (j=0; j<n2; j++) {
      Dyn[ii+j] = 0.0;                             /* Dyn[2][2] = [0] */
    }
    Dyn[ii+i] = 1.0;                               /* Dyn[2][1] = [I] */
  }
  for (i=0; i<nfgc; i++) {
    ii  = irow[i] * n2;
    iii = i * nkol + nfgc;
    for (j=0; j<nfgc; j++) {
      Dyn[ii     +j] = MDKG[iii     +j];       /* Dyn[1][1] = -[M-1D] */
      Dyn[ii+nfgc+j] = MDKG[iii+nfgc+j];       /* Dyn[1][2] = -[M-1K] */
    }
  }
  return;
}
