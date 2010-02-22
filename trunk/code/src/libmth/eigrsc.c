/* ------------------------------------------------------------------ */
/* eigrsc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Compute eigenvalues and eigenvectors of a real symmetric matrix.
|
|     Access:
|       (void) eigrsc(real a[], int n, real eigvct[]);
|     real a[n,n],i/o-Real symmetric matrix for which the eigensystem is
|       to be solved.  The eigenvalues are returned in the diagonal
|       entries a[i,i] in descending order.
|     int n,i-Order of matrices a[] and eigvct[].
|     real eigvct[n,n],o-Matrix of eigenvectors, returned as rows in the
|       same sequence as the eigenvalues.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The a[] matrix must be real and symmetric on entry.
|       The a[] matrix is destroyed during computations.
|       The diagonalization method originated with Jacobi and was adap-
|     ted by Von Neumann for large computers as found in "Mathematical
|     Methods for Digital Computers", edited by A. Ralston and H.S.
|     Wilf, John Wiley and Sons, New York, 1962, chapter 7.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void eigrsc(real a[], int n, real eigvct[])
#else
  void eigrsc(a, n, eigvct)
  real a[], eigvct[];
  int  n;
#endif
{
  real anorm, anormx, cosx, cosx2, sinx, sinx2, sincs, temp, thrhld, x,
    y;
  int i, j, k, lflag;
 
/* Generate the identity matrix. */
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      eigvct[i*n+j] = 0.0;
    }
    eigvct[i*n+i] = 1.0;
  }
 
/* Compute initial and final norms (anorm and anormx). */
  anorm = 0.0;
  for (i=0; i<n; i++) {
    for (j=0; j<i; j++) {
      anorm += a[i*n+j] * a[i*n+j];
    }
  }
  if (anorm <=  0.0) goto _2;
  anorm  = sqrt(2.0 * anorm);
  anormx = anorm * ZERO / n;
 
/* Initialize indicators and compute threshold. */
  lflag  = FALSE;
  thrhld = anorm;
_4:
  thrhld = thrhld / n;
 
/* Loop through off-diagonal elements. */
_3:
  for (i=0; i<n-1; i++) {
    for (j=i+1; j<n; j++) {
      if (fabs(a[j*n+i]) >= thrhld) {
        lflag = TRUE;
 
/* Compute sin and cos. */
        x = 0.5 * (a[i*n+i] - a[j*n+j]);
        y = -a[j*n+i] / sqrt(a[j*n+i] * a[j*n+i] + x * x);
        if (x < 0.0) y = -y;
        sinx  = y / sqrt(2.0 * (1.0 + (sqrt(1.0 - y * y))));
        sinx2 = sinx * sinx;
        cosx  = sqrt(1.0 - sinx2);
        cosx2 = cosx * cosx;
        sincs = sinx * cosx;
 
/* Rotate rows i and j. */
        for (k=0; k<n; k++) {
          if (k != i && k != j) {
            temp     = a[i*n+k] * cosx - a[j*n+k] * sinx;
            a[j*n+k] = a[i*n+k] * sinx + a[j*n+k] * cosx;
            a[i*n+k] = temp;
          }
          temp          = eigvct[i*n+k] * cosx - eigvct[j*n+k] * sinx;
          eigvct[j*n+k] = eigvct[i*n+k] * sinx + eigvct[j*n+k] * cosx;
          eigvct[i*n+k] = temp;
        }
        temp     = 2.0 * a[j*n+i] * sincs;
        y        = a[i*n+i] * cosx2 + a[j*n+j] * sinx2 - temp;
        x        = a[i*n+i] * sinx2 + a[j*n+j] * cosx2 + temp;
        a[j*n+i] = (a[i*n+i] - a[j*n+j]) * sincs 
                 + a[j*n+i] * (cosx2 - sinx2);
        a[i*n+i] = y;
        a[j*n+j] = x;
      }
    }
  }
  if (lflag) {
    lflag = FALSE;
    goto _3;
  }
 
/* Compare threshold with final norm. */
  if (thrhld > anormx) goto _4;
 
/* Sort eigenvalues and eigenvectors. */
_2:
  for (i=0; i<n; i++) {
    for (j=i+1; j<n; j++) {
      if (a[j*n+j] > a[i*n+i]) {
        temp     = a[i*n+i];
        a[i*n+i] = a[j*n+j];
        a[j*n+j] = temp;
        for (k=0; k<n; k++) {
          temp          = eigvct[i*n+k];
          eigvct[i*n+k] = eigvct[j*n+k];
          eigvct[j*n+k] = temp;
        }
      }
    }
  }
  return;
}
