/* ------------------------------------------------------------------ */
/* cblbkc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the eigenvectors of a general complex matrix by back trans-
|     forming those of the balanced matrix formed by cbalnc().
|
|     Access:
|       (void) cblbkc(int n, int low, int high, int m, int intger[], 
|         real scale[], complex Z[]);
|     int     n,        i-The order of the general complex matrix.
|     int     low,      i-Index of low  row of balanced H[n,n] after 
|                           cbalnc().
|     int     high,     i-Index of high row of balanced H[n,n] after 
|                           cbalnc().
|     int     m,        i-Number of eigenvectors to be back transformed.
|     int     intger[n],i-Array of permutations  used in chesnc().
|     real    scale[n], i-Array of scale factors used by cbalnc().
|     complex Z[n,n], i/o-The array containing the transformed eigenvec-
|       tors in the first m columns. 
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine is a complex version of balbak(), Numerical Meth-
|     ods, 13, pp.293-304, (1969) by Parlett and Reinsch.  Handbook for 
|     Automatic Computation, vol.II-Linear Algebra, pp.315-326, (1971).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void cblbkc(int n, int low, int high, int m, int intger[], 
    real scale[], complex Z[])
#else
  void cblbkc(n, low, high, m, intger, scale[], Z[])
  int n, low, high, m, intger[];
  real scale[];
  complex Z[];
#endif
{
  int  i, j, k, loc, loc2;
  real s;

  if (low < high) {
    for (i=low; i<=high; i++) {
      s = scale[i];
/* Left-hand eigenvectors are back transformed if the foregoing state-
     ment is replaced by  s = 1.0 / scale[i]; */
      for (j=0; j<m; j++) {
        loc = i * n + j;
        Z[loc].r *= s;
        Z[loc].i *= s;
      }
    }
  }
  for (i=low-1; i>=0; i--) {
    k = intger[i];
    if (k == i) continue;
    for (j=0; j<m; j++) {
      loc  = i * n + j;
      loc2 = k * n + j;
      s         = Z[loc].r;
      Z[loc].r  = Z[loc2].r;
      Z[loc2].r = s;
      s         = Z[loc].i;
      Z[loc].i  = Z[loc2].i;
      Z[loc2].i = s;
    }
  }
  for (i=high+1; i<n; i++) {
    k = intger[i];
    if (k == i) continue;
    for (j=0; j<m; j++) {
      loc  = i * n + j;
      loc2 = k * n + j;
      s         = Z[loc].r;
      Z[loc].r  = Z[loc2].r;
      Z[loc2].r = s;
      s         = Z[loc].i;
      Z[loc].i  = Z[loc2].i;
      Z[loc2].i = s;
    }
  }
  return;
}
