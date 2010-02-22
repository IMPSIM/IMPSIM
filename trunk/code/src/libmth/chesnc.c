/* ------------------------------------------------------------------ */
/* chesnc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Reduce the submatrix situated in rows and columns low through 
|     high of a general complex matrix H[] into upper Hessenberg form by 
|     stabalized elementary similarity transformations.
|
|     Access:
|       (void) chesnc(int n, int low, int high, complex H[], 
|         int intger[]);
|     int     n,      i  -The order of the complex H[n,n] matrix.
|     int     low,    i  -The index of the low  row of balanced H[n,n].
|     int     high,   i  -The index of the high row of balanced H[n,n].
|     complex H[n,n], i/o-The defining balanced complex matrix on entry; 
|       contains the upper Hessenberg matrix on output.  The multipliers 
|       used in the reduction are stored in the remaining triangles 
|       under the Hessenberg matrix.
|     int     intger[n],o-Array containing information on rows and 
|       columns interchanged in the reduction.  Only elements low 
|       through high are used.
|
|     Error Conditions:
|       None.
|
|     Comments:
|     This routine is a translation of the Algol procedure comhes(),
|       Numerical Methods, 12, pp.349-368, (1968) by Martin and Wilkin-
|       son.  Handbook for Automatic Computation, Vol.II-Linear Algebra, 
|       pp.339-358, (1971).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void chesnc(int n, int low, int high, complex H[], int intger[])
#else
  void chesnc(n, low, high, H, intger)
  int n, low, high;
  complex H[];
  int intger[];
#endif
{
  complex x, y;
  int i, j, k, kl1, loc, loc2;

  for (k=low+1; k<high; k++) {
    kl1 = k - 1;
    x.r = 0.0;
    x.i = 0.0;
    i = k;
    for (j=k; j<=high; j++) {
      loc = j * n + kl1;
      if ((fabs(H[loc].r) + fabs(H[loc].i)) > (fabs(x.r) + fabs(x.i))) {
        x.r = H[loc].r;         /* x = largest element in column k-1. */
        x.i = H[loc].i;
        i = j;               /* i = row where x = H[i,k-1] was found. */
      }
    }
    intger[k] = i;

/* Interchange rows and columns i and k of H[,]. */
    if (i != k) {
      for (j=kl1; j<n; j++) {
        loc  = i * n + j;                         /* Row i, column j. */
        loc2 = k * n + j;                         /* Row k, column j. */
        y.r       = H[loc].r;
        H[loc].r  = H[loc2].r;
        H[loc2].r = y.r;
        y.i       = H[loc].i;
        H[loc].i  = H[loc2].i;
        H[loc2].i = y.i;
      }
      for (j=0; j<=high; j++) {
        loc  = j * n + i;                         /* Row j, column i. */
        loc2 = j * n + k;                         /* Row j, column k. */
        y.r       = H[loc].r;
        H[loc].r  = H[loc2].r;
        H[loc2].r = y.r;
        y.i       = H[loc].i;
        H[loc].i  = H[loc2].i;
        H[loc2].i = y.i;
      }
    }

/* End interchange. */
    if ((x.r != 0.0) || (x.i != 0.0)) {
      for (i=k+1; i<=high; i++) {
        loc = i * n + kl1;
        y.r = H[loc].r;                              /* y = H[i,k-1]. */
        y.i = H[loc].i;
        if ((y.r != 0.0) || (y.i != 0.0)) {
          y = cdivc(y, x);
          H[loc].r = y.r;
          H[loc].i = y.i;
          for (j=k; j<n; j++) {
            loc = i * n + j;                         /* Change row i. */
            H[loc] = clessc(H[loc], cmultc(y, H[k*n+j]));
          }
          for (j=0; j<=high; j++) {
            loc = j * n + k;                      /* Change column k. */
            H[loc] = cplusc(H[loc], cmultc(y, H[j*n+i]));
          }
        }
      }
    }
  }
  return;
}
