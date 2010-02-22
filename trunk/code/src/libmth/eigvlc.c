/* ------------------------------------------------------------------ */
/* eigvlc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute the eigenvalues of a real matrix.
|
|     Access:
|       nerror = (int) eigvlc(real a[], int n, real wr[], real wi[]);
|     real a[n,n],i/o-Real matrix defining the eigenvalue problem.
|     int n,i-Dimension of the eigensystem.
|     real wr[n],o-Array of eigenvalue real parts.
|     real wi[n],o-Array of eigenvalue imaginary parts.
|     int nerror,o-Return flag set non-zero for error.
|
|     Error Conditions:
|       nerror != 0 indicates lack of convergence of the iteration
|     process.  Eigenvalues >= nerror are okay.
|
|     Comments:
|       Note that the matrix a[] is stored in row-major (C) order rather
|     than column-major (Fortran) order.
|       The technique used is the QR transformation method with shifts.
|     The matrix is first reduced to upper Hessenberg form by stabalized
|     elementary similarity transformations.
|       The real matrix a[] is destroyed during calculation of the
|     eigenvalues.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int eigvlc(real a[], int n, real wr[], real wi[])
#else
  int eigvlc(a, n, wr, wi)
  real a[];
  int  n;
  real wr[], wi[];
#endif
{
  int nerror;

  nerror = eigenc(a, n, FALSE, wr, wi, (complex *) NULL);
  return(nerror);
}
