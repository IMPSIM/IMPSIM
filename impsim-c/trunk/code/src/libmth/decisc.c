/* ------------------------------------------------------------------ */
/* decisc-01 Jan 00:20 Sep 2006
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       This user-written routine allows the user to change the grouping
|     and/or the values of multiple eigenvalues.
|
|     Access:
|       (void) decisc(int n, int nblock, int mult[], complex Wmlt[], 
|         complex H[]);
|     int     n,      i-The order of the complex H[n,n] matrix.
|     int     nblock, i-The number of multiple eigenvalues.
|     int     mult[n],i-The multiplicity of the multiple eigenvalues.
|       mult[i+1] - mult[i] = multiplicity of eigenvalue i for block 
|       i = 0, ..., nblock.
|     complex Wmlt[n],i-The multiple eigenvalues.
|     complex H[n,n], i-The upper triangular matrix resulting from steps
|       1-3 of the algorithm; the user must not change H[].
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine is a translation of the Algol procedure cbalance,
|     which is a complex version of balance, Numerical Methods, 13,
|     pp.293-304, (1969) by Parlett and Reinsch.  Handbook for Automatic
|     Computation, Vol.II-Linear Algebra, pp.315-326, (1971).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void decisc(int n, int nblock, int mult[], complex Wmlt[],complex H[])
#else
  void decisc(n, nblock, mult, Wmlt, H)
  int n, nblock, mult[];
  complex Wmlt[], H[];
#endif
{
/*int k, loc, mlt;*/

/*printf("/n/n The following output (A, B, and C) are printed by the");
  printf(" user written/n"); 
  printf(" routine decisc().  See section 2 of the algorithm./n");*/

/*printf("/n A:  Enter decisc() with eigenvalues computed by clr2c()"); 
  printf(" in step 1 of/n"); 
  printf("     the algorithm:/n");
  for (k=0; k<n; k++) {
    loc = k * n + k;
    printf(" (%#10.5f, %#10.5f)", H[loc].r, H[loc].i);
    if (k % 3 == 2) printf("/n");
  }*/

/*printf("/n B:  Groupings of the eigenvalues computed by step 3 of");
  printf(" the algorithm:/n");
  for (k=0; k<nblock; k++) {
    mlt = mult[k+1] - mult[k];
    printf("  divide at %4i, mlt.=%4i, center=(%#10.5f, %#10.5f)/n",
      mult[k+1], mlt, Wmlt[k].r, Wmlt[k].i);
  }*/

/*printf("/n C:  The structure of each multiple eigenvalue is found");
  printf(" in step 6 of\n"); 
  printf("     the algorithm.  For that reason, rdefl() successively"); 
  printf(" computes\n");
  printf("     singular value decompositions (see also the comments");
  printf(" in rdefl()\n"); 
  printf("     and in step 6 of the algorithm); cdeflc() prints the"); 
  printf(" results below:\n");*/
  return;
}
