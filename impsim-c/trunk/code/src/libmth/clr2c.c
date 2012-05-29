/* ------------------------------------------------------------------ */
/* clr2c-01 Jan 00:22 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Find the eigenvalues and eigenvectors of a complex upper Hessen-
|     berg matrix by the modified LR transformation method.  The eigen-
|     values and eigenvectors of a complex general matrix can also be 
|     found if chesnc() is used to reduce the matrix to upper Hessenberg
|     form.
|
|     Access:
|       ierror = (int) clr2c(int n, int lvects, int low, int high, 
|         int intger[], complex H[], complex W[], complex Z[]);
|     int     n,        i-The order of the eigensystem.
|     int     lvects,   i-A flag telling if the user wants the eigenvec-
|       tors to be found (lvects=TRUE) or not (lvects=FALSE).
|     int     low,      i-Index of low  row of H[n,n] from cbalnc() or 
|       set low = 0.
|     int     high,     i-Index of high row of H[n,n] from cbalnc() or 
|       set high = n - 1.
|     int     intger[n],i-Contains information on the rows and columns 
|       interchanged in the reduction by chesnc(), if performed; only
|       elements low through high are used.  If the eigenvectors of the
|       Hessenberg matrix are desired, set intger[j]=j for the elements.
|     complex H[n,n], i/o-Defining complex upper Hessenberg matrix.  On 
|       entry the lower triangles below the subdiagonal contain the 
|       multipliers which were used in the reduction by chesnc(), if 
|       performed; if the eigenvectors of the Hessenberg matrix are 
|       desired, these elements must be set to zero.  On exit, the 
|       upper Hessenberg portions of H[n,n] matrix have been destroyed.  
|     complex W[n],     o-The eigenvalues found.  
|     complex Z[n,n],   o-The eigenvectors found.  
|     int     ierror,   o-Convergence parameter set by clr2c(); ierror=:
|       0  for normal return;
|       j  if the j-th eigenvalue has not been determined after 30 iter-
|            ations.  If exit has ierr != 0, the eigenvalues W[ierr+1],
|            ...,W[n-1] should be correct but no eigenvectors are found.
|
|     Error Conditions:
|       Lack of convergence is indicated by ierr returned != 0.
|
|     Comments:
|       This routine is a translation of the Algol procedure comlr2(),
|     Numerical Methods, vol.16, pp.181-204, 1970, by Peters and Wilkin-
|     son.  Also in Handbook for Automatic Computation, Vol.II - Linear
|     Algebra, pp.372-395, 1971.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int clr2c(int n, int lvects, int low, int high, int intger[], 
    complex H[], complex W[], complex Z[])
#else
  int clr2c(n, lvects, low, high, intger, H[], W[], Z[])
  int     n, lvects, low, high, intger[];
  complex H[], W[], Z[];
#endif
{
  complex s, t, x, y, z;
  int     i, ierror, il1, iter, j, k, l, loc, loc2, m, nn, nnl1;
  real    epsilon, norm;

/* Initialize. */
# ifdef DOUBLE_PREC
    epsilon = DBL_EPSILON;
# else
    epsilon = FLT_EPSILON;
# endif
  ierror = 0;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      loc = i * n + j;
      Z[loc].r = 0.0;                          /* Eigenvector matrix. */
      Z[loc].i = 0.0;
    }
    Z[i*n+i].r = 1.0;
  }

/* Form accumulated transformations from information left by chesnc. */
  for (i=high-1; i>=low+1; i--) {
    for (k=i+1; k<=high; k++) {
      loc = k * n + i;
      Z[loc].r = H[loc-1].r;
      Z[loc].i = H[loc-1].i;
    }
    j = intger[i];
    if (i != j) {
      for (k=i; k<=high; k++) {
        loc  = i * n + k;
        loc2 = j * n + k;
        Z[loc].r  = Z[loc2].r;
        Z[loc].i  = Z[loc2].i;
        Z[loc2].r = 0.0;
        Z[loc2].i = 0.0;
      }
      Z[j*n+i].r = 1.0;
      Z[j*n+i].i = 0.0;
    }
  }

/* Store roots isolated by cbalnc(). */
  for (i=0; i<n; i++) {
    if ((i < low) || (i > high)) {
      loc = i * n + i;
      W[i].r = H[loc].r;
      W[i].i = H[loc].i;
    }
  }
  nn = high;
  t.r = 0.0;
  t.i = 0.0;

/* Search for the next eigenvalue. */
  while (nn >= low) {
    iter = 0;
    nnl1 = nn - 1;
_NEXT:
    for (l=nn; l>=low; l--) { /* Look for small sub-diagonal element. */
      if (l == low) break;
      loc  =  l      * n +  l;
      loc2 = (l - 1) * n + (l - 1);
      if ((fabs(H[loc-1].r) + fabs(H[loc-1].i)) <= epsilon * 
       (fabs(H[loc2].r) + fabs(H[loc2].i) + fabs(H[loc].r) + 
        fabs(H[loc].i))) break;
    }
    if (l == nn) {
      goto _FOUND;
    } else if (iter == 30) {
      ierror = nn;             /* No convergence after 30 iterations. */
      goto _END;
    } else if ((iter == 10) || (iter == 20)) {
      loc  = nn   * n + nnl1;
      loc2 = nnl1 * n + nn - 2;
      s.r = fabs(H[loc].r) + fabs(H[loc2].r);   /* Exceptional shift. */
      s.i = fabs(H[loc].i) + fabs(H[loc2].i);
    } else {
      loc  = nn   * n + nn;
      loc2 = nnl1 * n + nn;
      s.r = H[loc].r;                                /* Normal shift. */
      s.i = H[loc].i;
      x   = cmultc(H[loc2], H[loc-1]);
      if ((x.r != 0.0) || (x.i != 0.0)) {
        y.r = 0.5 * (H[loc2-1].r - s.r);
        y.i = 0.5 * (H[loc2-1].i - s.i);
        z = csqrtc(cmplxc((y.r*y.r-y.i*y.i+x.r), (2.0*y.r*y.i+x.i)));
        if ((y.r * z.r + y.i * z.i) < 0.0) {
          z.r = -z.r;
          z.i = -z.i;
        }
        x = cdivc(x, cplusc(y, z));
        s.r -= x.r;
        s.i -= x.i;
      }
    }
    for (i=low; i<=nn; i++) {
      loc = i * n + i;
      H[loc].r -= s.r;
      H[loc].i -= s.i;
    }
    t.r += s.r;
    t.i += s.i;
    iter++;

/* Look for two consecutive small sub-diagonal elements. */
    loc  = nn   * n + nn;
    loc2 = nnl1 * n + nnl1;
    x.r = fabs(H[loc2].r)  + fabs(H[loc2].i);
    y.r = fabs(H[loc-1].r) + fabs(H[loc-1].i);
    z.r = fabs(H[loc].r)   + fabs(H[loc].i);
    for (m=nnl1; m>=l; m--) {
      if (m == l ) break;
      loc  =  m      * n +  m - 1;
      loc2 = (m - 1) * n + (m - 1);
      y.i = y.r;
      y.r = fabs(H[loc].r) + fabs(H[loc].i);
      x.i = z.r;
      z.r = x.r;
      x.r = fabs(H[loc2].r) + fabs(H[loc2].i);
      if (y.r <= (epsilon * (z.r / y.i) * (z.r + x.r + x.i))) break;
    }

/* Triangular decomposition; H[] = L[] R[]. */
    for (i=m+1; i<=nn; i++) {
      il1 = i - 1;
      loc  = i   * n + il1;
      loc2 = il1 * n + il1;
      x.r = H[loc2].r;
      x.i = H[loc2].i;
      y.r = H[loc].r;
      y.i = H[loc].i;
      if ((fabs(x.r) + fabs(x.i)) < (fabs(y.r) + fabs(y.i))) {
        for (j=il1; j<n; j++) { /* Interchange rows i and i-1 of H[]. */
          loc  = i   * n + j;
          loc2 = il1 * n + j;
          z.r       = H[loc2].r;
          H[loc2].r = H[loc].r;
          H[loc].r  = z.r;
          z.i       = H[loc2].i;
          H[loc2].i = H[loc].i;
          H[loc].i  = z.i;
        }
        z = cdivc(x, y);
        W[i].r =  1.0;
      } else {
        z = cdivc(y, x);
        W[i].r = -1.0;
      }
      loc = i * n + il1;
      H[loc].r = z.r;
      H[loc].i = z.i;
      for (j=i; j<n; j++) {
        loc = i * n + j;
        H[loc] = clessc(H[loc], cmultc(z, H[il1*n+j]));
      }
    }

    for (j=m+1; j<=nn; j++) {             /* Composition R * L = H[]. */
      loc = j * n + j - 1;
      x.r      = H[loc].r;
      x.i      = H[loc].i;
      H[loc].r = 0.0;
      H[loc].i = 0.0;
      if (W[j].r > 0.0) {/* Interchange columns of H and Z if needed. */
        for (i=0; i<=j; i++) {
          loc = i * n + j;
          z.r        = H[loc-1].r;
          H[loc-1].r = H[loc].r;
          H[loc].r   = z.r;
          z.i        = H[loc-1].i;
          H[loc-1].i = H[loc].i;
          H[loc].i   = z.i;
        }
        for (i=low; i<=high; i++) {
          loc = i * n + j;
          z.r        = Z[loc-1].r;
          Z[loc-1].r = Z[loc].r;
          Z[loc].r   = z.r;
          z.i        = Z[loc-1].i;
          Z[loc-1].i = Z[loc].i;
          Z[loc].i   = z.i;
        }
      }
      for (i=0; i<=j; i++) {
        loc = i * n + j;
        H[loc-1] = cplusc(H[loc-1], cmultc(x, H[loc]));
      }
      for (i=low; i<=high; i++) {      /* Accumulate transformations. */
        loc = i * n + j;
        Z[loc-1] = cplusc(Z[loc-1], cmultc(x, Z[loc]));
      }
    }
    goto _NEXT;

_FOUND:                                       /* A single root found. */
    loc = nn * n + nn;
    H[loc].r += t.r;
    W[nn].r   = H[loc].r;
    H[loc].i += t.i;
    W[nn].i   = H[loc].i;
    nn = nnl1;
  }
  if (n == 1) goto _END;                          /* All roots found. */
  if (!lvects) goto _END;
  norm = 0.0;
  for (i=0; i<n; i++) {
    for (j=i; j<n; j++) {
      loc = i * n + j;
      norm += (fabs(H[loc].r) + fabs(H[loc].i));
    }
  }

  for (nn=n-1; nn>0; nn--) {/* Find vectors of upper triangular form. */
    nnl1 = nn - 1;
    x.r = W[nn].r;
    x.i = W[nn].i;
    for (i=nnl1; i>=0; i--) {
      loc = i * n + nn;
      z.r = H[loc].r;
      z.i = H[loc].i;
      if (i != nnl1) {
        for (j=i+1; j<=nnl1; j++) {
          loc  = i * n + j;
          loc2 = j * n + nn;
          z = cplusc(z, cmultc(H[loc], H[loc2]));
        }
      }
      y.r = x.r - W[i].r;
      y.i = x.i - W[i].i;
      if ((y.r == 0.0) && (y.i == 0.0)) y.r = epsilon * norm;
      z = cdivc(z, y);
      loc = i * n + nn;
      H[loc].r = z.r;
      H[loc].i = z.i;
    }
  }

  for (i=0; i<n; i++) {                      /* End backsubstitution. */
    if ((i < low) || (i > high)) { /* Find vectors of isolated roots. */
      for (j=i+1; j<n; j++) {
        loc = i * j + j;
        Z[loc].r = H[loc].r;
        Z[loc].i = H[loc].i;
      }
    }
  }

  for (j=n; j>low; j--) {    /* Find vectors of original full matrix. */
    m = min((j - 1), high);
    for (i=low; i<=high; i++) {
      loc = i * n + j;
      z.r = Z[loc].r;
      z.i = Z[loc].i;
      for (k=low; k<=m; k++) {
        loc2 = k * n + j;
        z = cplusc(z, cmultc(Z[loc-j+k], H[loc2]));
      }
      Z[loc].r = z.r;
      Z[loc].i = z.i;
    }
  }
_END:
  return(ierror);
}
