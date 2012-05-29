/* ------------------------------------------------------------------ */
/* invrtc-01 JAN 00:14 May 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       For the given real (mxn) matrix a[], determine its rank, its
|     linearly independent rows and columns (basis), and the inverse and
|     determinant of the largest non-singular square submatrix contained
|     in matrix a[].
|
|     Access:
|       (void) invrtc(real a[], int m, int n, int nfree, real zero,
|         int *irank, real *det, int irow[], int icol[]);
|     real  a[m,n],i/o-The matrix to be computed upon.  On entry, the
|       elements of the a[] matrix are assumed present here and stored
|       in row-major order in m rows and n columns.  On exit, this array
|       contains the basis vectors.
|     int   m,    i-The number of rows    in the matrix a[].
|     int   n,    i-The number of columns in the matrix a[].
|     int   nfree,i-The maximum number of columns allowed for inter-
|       change during pivoting operations.
|     real  zero, i-A small tolerance value used in determining when
|       round-off size real values are to be considered negligible.
|     int  *irank,o-The number of linearly independent vectors found to
|       span the space; the rank of matrix a[].
|     real *det,  o-The determinant of the largest non-singular sub-
|       matrix found within the matrix a[].
|     int   irow[m],o-On return, this array contains the reordered row
|       numbers (0,1,...,m-1) of the original matrix a[].
|     int   icol[n],o-On return, this array contains the reordered 
|       column numbers (0,1,...,n-1) of the original matrix a[].
|
|     Error Conditions:
|       If m <= 0, or nfree <= 0, or nfree > n, or zero < 0.0, then no
|     calculations are performed and return is made with *irank=-1.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void invrtc(real a[], int m, int n, int nfree, real zero, int *irank,
    real *det, int irow[], int icol[])
#else
  void invrtc(a, m, n, nfree, zero, irank, det, irow, icol)
  real a[], zero, *det;
  int  m, n, nfree, *irank, irow[], icol[];
#endif
{
  int  i, ir, ic, itemp, j, k, last, ncol;
  real piv, save, tol, temp;
 
/* Test the arguments and return with *irank=-1 for formal errors. */
  *det   = 0.0;
  *irank = 0;
  if (m <= 0)     *irank = -1;
  if (nfree <= 0) *irank = -1;
  if (n < nfree)  *irank = -1;
  if (zero < 0.0) *irank = -1;

/* Initialize the row and column number vectors. */
  for (i=0; i<m; i++) {
    irow[i] = i;
  }
  for (j=0; j<n; j++) {
    icol[j] = j;
  }
  if (*irank < 0) return;

/* Search for the first pivot element; set up the internal tolerance. */
  *det = 1.0;
  piv = 0.0;
  for (i=0; i<m; i++) {
    for (j=0; j<nfree; j++) {
      if (fabs(a[i*n+j]) > fabs(piv)) {
        piv = a[i*n+j];
        ir  = i;
        ic  = j;
      }
    }
  }
  if (fabs(piv) < zero) return;
  tol = fabs(zero * piv);

/* Start the elimination loop. */
  for (ncol=0; ncol<nfree; ncol++) {
    if (fabs(piv) <= tol) break;
    (*irank)++;
 
/* Interchange rows if necessary. */
    if (ir >= *irank) {
      *det = -(*det);
      for (j=0; j<n; j++) {
        temp              = a[ir*n+j];
        a[ir*n+j]         = a[(*irank-1)*n+j];
        a[(*irank-1)*n+j] = temp;
      }
      itemp          = irow[ir];
      irow[ir]       = irow[*irank-1];
      irow[*irank-1] = itemp;
    }

/* Interchange columns if necessary. */
    if (ic >= *irank) {
      *det = -(*det);
      for (i=0; i<m; i++) {
        temp              = a[i*n+ic];
        a[i*n+ic]         = a[i*n+(*irank-1)];
        a[i*n+(*irank-1)] = temp;
      }
      itemp          = icol[ic];
      icol[ic]       = icol[*irank-1];
      icol[*irank-1] = itemp;
    }
 
/* Test for the last row. */
    if (*irank >= m) break;

/* Transform the current submatrix and search for the next pivot. */
    temp = piv;
    piv  = 0.0;
    for (i=*irank; i<m; i++) {
      save = a[i*n+(*irank-1)] / temp;
      a[i*n+(*irank-1)] = save;
      for (j=*irank; j<n; j++) {
        a[i*n+j] -= save * a[(*irank-1)*n+j];
        if ((j < nfree) && (fabs(a[i*n+j]) > fabs(piv))) {
          piv = a[i*n+j];
          ir  = i;
          ic  = j;
        }
      }
    }
  }
  if (*irank <= 0) return;

/* Invert the upper triangular matrix. */
  for (i=0; i<*irank; i++) {
    *det *= a[i*n+i];
    a[i*n+i] = 1.0 / a[i*n+i];
    for (j=i+1; j<n; j++) {
      save = 0.0;
      last = min(j, *irank);
      for (k=i; k<last; k++) {
        save += a[i*n+k] * a[k*n+j];
      }
      if (j < *irank) save /= a[j*n+j];
      a[i*n+j] = -save;
    }
  }

/* Invert the lower triangular matrix. */
  for (i=1; i<m; i++) {
    last = min(i, *irank);
    for (j=0; j<last; j++) {
      save = a[i*n+j];
      for (k=j+1; k<last; k++) {
        save += a[i*n+k] * a[k*n+j];
      }
      a[i*n+j] = -save;
    }
  }

/* Multiply the two inverses. */
  for (i=0; i<*irank; i++) {
    for (j=0; j<*irank-1; j++) {
      if (i > j) {
        save = 0.0;
        ir   = i;
      } else {
        save = a[i*n+j];
        ir   = j + 1;
      }
      for (k=ir; k<*irank; k++) {
        save += a[i*n+k] * a[k*n+j];
      }
      a[i*n+j] = save;
    }
  }
  return;
}
