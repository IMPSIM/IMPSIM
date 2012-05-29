/* ------------------------------------------------------------------ */
/* cgausc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Solve a set of complex equations by Gauss-Jordan elimination
|     with full pivoting.
|
|     Access:
|       nerror = (int) cgausc(complex A[], int n, complex C[], int m);
|     complex A[n,n],i/o-Matrix of complex coefficients on entry;
|                          contains Inv(A[,]) on exit.
|     int     n,     i  -Size of the set of equations.
|     complex C[n,m],i/o-Matrix of right-hand sides on entry; contains
|                          solution vectors for euations on exit.
|     int     m,     i  -Number of columns in right-hand side.
|     int     nerr,  o  -Flag signaling error in solution if nonzero.
|
|     Error Conditions:
|       Singular equations are shown by nonzero value of nerr.
|
|     Comments:
|       The method is Gauss-Jordan elimination with full pivoting.  The
|     code is adapted from that shown in Numerical Recipes, W.H.Press
|     et.al., Cambridge University Press, 1986, pp.28-29, but has been
|     adapted to complex arithmetic.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int cgausc(complex A[], int n, complex C[], int m)
#else
  int cgausc(A, n, C, m)
  complex A[];
  int     n;
  complex C[];
  int     m;
#endif
{
  complex temp;
  int     i, icol, *indexc, *indexr, *ipivot, irow, j, k, loc, loc2, 
            nerr;
  real    big;

/* Initialize. */
  nerr = 0;
  ipivot = (int *) calloc(n, sizeof(int));
  indexc = (int *) calloc(n, sizeof(int));
  indexr = (int *) calloc(n, sizeof(int));
  for (i=0; i<n; i++) {ipivot[i] = 0;}

/* Loop over all columns to be reduced. */
  for (i=0; i<n; i++) {
    big = 0.0;
    for (j=0; j<n; j++) {
      if (ipivot[j] != 1) {
        for (k=0; k<n; k++) {
          if (ipivot[k] == 0) {
            loc = j * n + k;
            if (cabsc(A[loc]) >= big) {
              big = cabsc(A[loc]);
              irow = j;
              icol = k;
            }
          } else if (ipivot[k] > 1) {
            nerr = TRUE;
            goto DONE;
          }
        }
      }
    }
    ipivot[icol]++;

/* Put pivot element on the diagonal. */
    if (irow != icol) {                /* Interchange rows if needed. */
      for (k=0; k<n; k++) {
        loc  = irow * n + k;
        loc2 = icol * n + k;
        temp.r    = A[loc].r;
        temp.i    = A[loc].i;
        A[loc].r  = A[loc2].r;
        A[loc].i  = A[loc2].i;
        A[loc2].r = temp.r;
        A[loc2].i = temp.i;
      }
      for (k=0; k<m; k++) {
        loc  = irow * m + k;
        loc2 = icol * m + k;
        temp.r    = C[loc].r;
        temp.i    = C[loc].i;
        C[loc].r  = C[loc2].r;
        C[loc].i  = C[loc2].i;
        C[loc2].r = temp.r;
        C[loc2].i = temp.i;
      }
    }
    indexr[i] = irow;
    indexc[i] = icol;

/* Now we divide the pivot row by the pivot element. */
    loc = icol * n + icol;
    if (cabsc(A[loc]) == 0.0) {       /* Test pivot element for zero. */
      nerr = TRUE;
      goto DONE;
    }
    temp = cdivc(cmplxc(1.0, 0.0), A[loc]);  /* Invert pivot element. */
    A[loc].r = 1.0;
    A[loc].i = 0.0;
    for (k=0; k<n; k++) {
      loc = icol * n + k;
      A[loc] = cmultc(A[loc], temp);
    }
    for (k=0; k<m; k++) {
      loc = icol * m + k;
      C[loc] = cmultc(C[loc], temp);
    }

/* Next we reduce the rows to zero, except for the pivot row. */
    for (j=0; j<n; j++) {
      if (j != icol) {                   /* Skip the pivot row, icol. */
        loc = j * n + icol;
        temp.r   = A[loc].r;
        temp.i   = A[loc].i;
        A[loc].r = 0.0;
        A[loc].i = 0.0;
        for (k=0; k<n; k++) {
          loc = j * n + k;
          A[loc] = clessc(A[loc], cmultc(A[icol*n+k], temp));
        }
        for (k=0; k<m; k++) {
          loc = j * m + k;
          C[loc] = clessc(C[loc], cmultc(C[icol*m+k], temp));
        }
      }
    }
  }

/* Finally we rearrange the solutions per the column changes. */
  for (k=n-1; k>=0; k--) {
    if (indexr[k] != indexc[k]) {
      for (j=0; j<n; j++) {
        loc  = j * n + indexr[k];
        loc2 = j * n + indexc[k];
        temp.r    = A[loc].r;
        temp.i    = A[loc].i;
        A[loc].r  = A[loc2].r;
        A[loc].i  = A[loc2].i;
        A[loc2].r = temp.r;
        A[loc2].i = temp.i;
      }
    }
  }
DONE:
  free (ipivot);
  free (indexc);
  free (indexr);
  return(nerr);
}
