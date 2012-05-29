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
/* bformc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Diagonalize the first-order modal stiffness matrix through the
|     use of the orthogonality of the eigenvectors with respect to the
|     stiffness matrix and return its rank.
|
|     Access:
|       k1rank = (int) bformc(int nfgc, real M[], real K[],
|         complex Eigvct[], complex Bstar[]);
|     int  nfgc,                    i-Number of free generalized coords.
|     real M[nfgc,nfgc],            i-The 2nd order system mass matrix.
|     real K[nfgc,nfgc],            i-The 2nd order stiffness matrix.
|     complex Eigvct[2*nfgc,2*nfgc],i-The matrix of eigenvectors.
|     complex Bstar[2*nfgc],        o-The 1st order modal stiffnesses.
|     int Brank,                    o-Rank of 1st order stiffness matrix.
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
  int bformc(int nfgc, real M[], real K[], complex Eigvct[],
    complex Bstar[])
#else
  int bformc(nfgc, M, K, Eigvct, Bstar)
  int     nfgc;
  real    M[], K[];
  complex Eigvct[], Bstar[];
#endif
{
  complex *work;
  int      i, ii, j, jj, k, Brank, n2;

/* Postmultiply the 1st order stiffness matrix by the eigenvectors. */
  n2 = 2 * nfgc;
  work  = calloc(n2, sizeof(complex));      /* Acquire working space. */
  Brank = n2;
  for (k=0; k<n2; k++){
    for (i=0; i<nfgc; i++){
      ii = nfgc + i;
      work[ i] = cmplxc(0.0, 0.0);
      work[ii] = cmplxc(0.0, 0.0);
      for (j=0; j<nfgc; j++){
        jj = nfgc + j;
        work[ i].r -= M[i*nfgc+j] * Eigvct[ j*n2+k].r;/* [-M*Eig top] */
        work[ i].i -= M[i*nfgc+j] * Eigvct[ j*n2+k].i;
        work[ii].r += K[i*nfgc+j] * Eigvct[jj*n2+k].r; /* [K*Eig low] */
        work[ii].i += K[i*nfgc+j] * Eigvct[jj*n2+k].i;
      }
    }

/* Premultiply by the transposed eigenvector matrix. */
    Bstar[k] = cmplxc(0.0, 0.0);
    for (i=0; i<n2; i++){
      Bstar[k] = cplusc(Bstar[k], cmultc(Eigvct[i*n2+k], work[i]));
    }

/* Check to see if a diagonal term is near zero. */
/* *** This signifies a singular stiffness matrix. *** */
    if (cabsc(Bstar[k]) < System.fktol){
      Bstar[k] = cmplxc(1.0 / System.fktol, 0.0);
      Brank--;
    }
  }
  free(work);
  return(Brank);
}
