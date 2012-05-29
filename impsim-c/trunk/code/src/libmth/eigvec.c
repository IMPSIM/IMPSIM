/* ------------------------------------------------------------------ */
/* eigvec-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute eigenvalues and eigenvectors of a real matrix.
|
|     Access:
|       nogo = (int) eigvec(real a[], int n, real wr[], real wi[],
|         complex eigvct[])
|     real a[n,n],i/o-Real matrix defining the eigenvalue problem.
|     int n,i-Dimension of the eigensystem.
|     real wr[n],o-Array of eigenvalue real parts.
|     real wi[n],o-Array of eigenvalue imaginary parts.
|     complex eigvct[n,n],o-Matrix of eigenvectors.
|     int nogo,o-Return flag set non-zero for error.
|
|     Error Conditions:
|       nogo != 0 indicates lack of convergence of the iteration
|     process.  Eigenvalues => nogo are okay, but no eigenvectors are
|     found.
|
|     Comments:
|       The technique used is the QR transformation method with shifts.
|     The matrix is first reduced to upper Hessenberg form by stabalized
|     elementary similarity transformations.
|       The real matrix a[] is destroyed during calculation of the
|     eigenvalues and eigenvectors.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int eigvec(real a[], int n, real wr[], real wi[], complex eigvct[])
#else
  int eigvec(a, n, wr, wi, eigvct)
  real    a[];
  int     n;
  real    wr[], wi[];
  complex eigvct[];
#endif
{
  int nogo;

  nogo = eigenc(a, n, TRUE, wr, wi, eigvct);
  return(nogo);
}
