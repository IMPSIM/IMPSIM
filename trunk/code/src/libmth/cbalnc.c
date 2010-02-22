/* ------------------------------------------------------------------ */
/* cbalnc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Balance complex matrix H[] into triangular form isolating eigen-
|     values when possible.
|
|     Access:
|       (void) cbalnc(int n, complex H[], int *low, int *high, 
|         real scale[]);
|     int     n,       i-The order of the complex H[n,n] matrix.
|     complex H[n,n],i/o-Defining matrix on entry; contains the balanced 
|                          matrix on output.
|     int     *low,    o-Index of low  balanced row of H[n,n] on exit.
|     int     *high,   o-Index of high balanced row of H[n,n] on exit.
|     real    scale[n],o-Array of permutations and scaling factors used.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine is a translation of the Algol procedure cbalance,
|     which is a complex version of balance, Numerical Methods, 13, pp.
|     293-304, (1969) by Parlett and Reinsch.  Handbook for Automatic 
|     Computation, Vol.II-Linear Algebra, pp.315-326, (1971).
|       Indices *low and *high are two integers such that H[i,j] are 
|     equal to zero if:
|     (1) i>j (H[i,j] is below the diagonal), and (2) j=0,1,...,*low or
|       j=*high,...,n-1.
|       Suppose that the principal submatrix in rows *low through *high
|     has been balanced, that p[j] denotes the index interchanged with j
|     during the permutation step, and that the elements of the diagonal
|     matrix used are denoted by d[j,j].  Then:
|       scale[j] = p[j]    for j=0,1,...,*low
|                = d[j,j]  for j=*low,...,*high
|                = p[j]    for j=*high,...,n-1.
|       The order in which the interchanges are made is n-1 to *high,
|     then 0 to *low.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void cbalnc(int n, complex H[], int *low, int *high, real scale[])
#else
  void cbalnc(n, H, low, high, scale)
  int n;
  complex H[];
  int *low, *high;
  real scale[];
#endif
{
  int  i, j, k, l, lcnvrg, lswap, loc, loc2, m;
  real c, f, g, r, radix, radsqr, s;

/* radix is a machine dependent parameter specifying the base of the
     machine floating point representation. */
  radix  = 2.0;
  radsqr = radix * radix;
  k = 0;
  l = n - 1;
  goto _ROW;

/* In-line procedure for exchange of row (and column) j with m. */
_SWAP:
  scale[m] = j;
  if (j != m) {
    for (i=0; i<=l; i++) {  /* Swap all rows i<=l of columns j and m. */
      loc  = i * n + j;
      loc2 = i * n + m;
      f         = H[loc].r;
      H[loc].r  = H[loc2].r;
      H[loc2].r = f;
      f         = H[loc].i;
      H[loc].i  = H[loc2].i;
      H[loc2].i = f;
    }
    for (i=k; i<n; i++) {   /* Swap all columns i>=k of rows j and m. */
      loc  = j * n + i;
      loc2 = m * n + i;
      f         = H[loc].r;
      H[loc].r  = H[loc2].r;
      H[loc2].r = f;
      f         = H[loc].i;
      H[loc].i  = H[loc2].i;
      H[loc2].i = f;
    }
  }
  if (lswap) {
    k++;
    goto _COLUMN;
  } else {
    if (l == 0) goto _DONE;
    l--;
  }

/* Search out rows with isolated eigenvalues; push them to high rows. */
_ROW:
  for (j=l; j>=0; j--) {             /* Sequence upward through rows. */
    for (i=0; i<=l; i++) {
      if (i == j) continue;
      loc = j * n + i;                /* Note this is row j column i. */
      if ((H[loc].r != 0.0) || (H[loc].i != 0.0)) goto _2;
    }
    m = l;  /* All elements of row j are zero except diagonal H[j,j]. */
    lswap = FALSE;
    goto _SWAP;
_2: continue;
  }

/* Search for columns with isolated eigenvalues and push them left. */
_COLUMN:
  for (j=k; j<=l; j++) {         /* Sequence through columns k<=j<=l. */
    for (i=k; i<=l; i++) {
      if (i == j) continue;
      loc = i * n + j;                /* Note this is row i column j. */
      if ((H[loc].r != 0.0) || (H[loc].i != 0.0)) goto _3;
    }
    m = k;/*All elements of column j are zero except diagonal H[j,j]. */
    lswap = TRUE;
    goto _SWAP;
_3: continue;
  }

/* Now balance the submatrix in rows k throgh l. */
  for (i=k; i<=l; i++) scale[i] = 1.0;
  do {                          /* Iterative loop for norm reduction. */
    lcnvrg = TRUE;
    for (i=k; i<=l; i++) {
      c = 0.0;
      r = 0.0;
      for (j=k; j<=l; j++) {
        if (j != i) {
          loc  = j * n + i;
          loc2 = i * n + j;
          c += (fabs(H[loc].r)  + fabs(H[loc].i));          /* H[j,i] */
          r += (fabs(H[loc2].r) + fabs(H[loc].i));          /* H[i,j] */
        }
      }
      g = r / radix;
      f = 1.0;
      s = c + r;
      while (c < g) {
        f *= radix;
        c *= radsqr;
      }
      g = r * radix;
      while (c >= g) {
        f /= radix;
        c /= radsqr;
      }
      if (((c + r) / f) >= (0.95 * s)) continue;      /* Now balance. */
      g = 1.0 / f;
      scale[i] *= f;
      lcnvrg = FALSE;
      for (j=k; j<n; j++) {
        loc = i * n + j;
        H[loc].r *= g;                                      /* H[i,j] */
        H[loc].i *= g;
      }
      for (j=0; j<=l; j++) {
        loc = j * n + i;
        H[loc].r *= f;                                      /* H[j,i] */
        H[loc].i *= f;
      }
    }
  } while (!lcnvrg);
_DONE:
  *low  = k;
  *high = l;
  return;
}
