/* ------------------------------------------------------------------ */
/* csvdc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Perform a singular value decomposition of a complex matrix 
|     H[m,n] in order to determine its rank.
|
|     Access:
|       (void) csvdc(complex H[], int mmax, int nmax, int m, int n, 
|         int np, int nu, int nv, real s, complex U[], complex V[]);
|     complex H[mmax,nmax],i/o-Defining matrix of the current block; the
|       call is offset such that H[0,0] corresponds to the beginning of 
|       the current block.  Only the block H[m,n] is affected by the 
|       call.
|     int mmax, i-Defining row    size of the H[,] matrix.
|     int nmax, i-Defining column size of the H[,] matrix.
|     int m,    i-Number of rows    of H[,] matrix actually in use.
|     int n,    i-Number of columns of H[,] matrix actually in use.
|     int np,   i-Number of columns of H[,] past n.
|     int nu,   i-Zero, n, or m; the number of columns used in U[,].
|     int nv,   i-Zero     or n; the number of columns used in V[,].
|     real s[nmax], o-Array of computed and sorted singular values.
|     complex U[mmax,nmax],o-m by m unitary matrix.
|     complex V[nmax,nmax],o-n by n unitary matrix.
|     
|     Error Conditions:
|       None.
|
|     Comments:
|       csvdc() can also be used to find the least squares solution of
|     minimal length, or to solve a homogeneous set of linear equations.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void csvdc(complex H[], int mmax, int nmax, int m, int n, int np, 
    int nu, int nv, real s[], complex U[], complex V[])
#else
  void csvdc(H, mmax, nmax, m, n, np, nu, nv, s, U, V)
  complex H[], U[], V[];
  int     mmax, nmax, m, n, np, nu, nv;
  real    s[];
#endif
{
  complex ctemp, q, r;
  int     i, j, k, kp1, l, ll1, loc, loc1, lp1;
  real    a, *b, *c, cs, eps, eta, f, g, sn, *t, temp, tol, w, x, y, z;

/* Initialize. */
  b = (real *) calloc(mmax, sizeof(real));
  c = (real *) calloc(nmax, sizeof(real));
  t = (real *) calloc(nmax, sizeof(real));
# ifdef DOUBLE_PREC
    eta = DBL_EPSILON;                 /* Relative machine precision. */
    tol = DBL_MIN / eta;   /* Smallest norm. positive value over eta. */
# else
    eta = FLT_EPSILON;
    tol = FLT_MIN / eta;
# endif
  c[0] = 0.0;                               /* Householder reduction. */
  k    = 0;
_2:;
  kp1  = k + 1;
  z = 0.0;
  for (i=k; i<m; i++) {     /* Elimination of H[i,k] for i=k+1,...,m. */
    loc = i * nmax + k;
    z += H[loc].r * H[loc].r + H[loc].i * H[loc].i;
  }
  b[k] = 0.0;
  while (z > tol) {
    z    = sqrt(z);
    b[k] = z;
    loc  = k * nmax + k;
    w    = cabsc(H[loc]);
    if (w == 0.0) {
      q.r = 1.0;
      q.i = 0.0;
    } else {
      q.r = H[loc].r / w;
      q.i = H[loc].i / w;
    }
    temp = z + w;
    H[loc].r = q.r * temp;
    H[loc].i = q.i * temp;
    if (k == n+np) continue;
    for (j=kp1; j<n+np; j++) {
      q.r = 0.0;
      q.i = 0.0;
      for (i=k; i<m; i++) {
        loc1 = i * nmax;
        q = cplusc(q, cmultc(conjgc(H[loc1+k]), H[loc1+j]));
      }
      temp = 1.0 / (z * (z + w));
      q.r *= temp;
      q.i *= temp;
      for (i=k; i<m; i++) {
        loc1 = i * nmax;
        H[loc1+j] = clessc(H[loc1+j], cmultc(q, H[loc1+k]));
      }
    }
    temp  = -1.0 / cabsc(H[loc]);            /* Phase transformation. */
    q = conjgc(H[loc]);
    q.r *= temp;
    q.i *= temp;
    for (j=kp1; j<n+np; j++) {
      loc1 = k * nmax + j;
      H[loc1] = cmultc(q, H[loc1]);
    }
  }
  while (k < n) {           /* Elimination of H{k,j] for j=k+2,...,n. */
    z = 0.0;
    for (j=kp1; j<n; j++) {
      loc = k * nmax + j;
      z += H[loc].r * H[loc].r + H[loc].i * H[loc].i;
    }
    c[kp1] = 0.0;
    if (z > tol) {
      z = sqrt(z);
      c[kp1] = z;
      loc = k * nmax + kp1;
      w = cabsc(H[loc]);
      if (w == 0.0) {
        q.r = 1.0;
        q.i = 0.0;
      } else {
        q.r = H[loc].r / w;
        q.i = H[loc].i / w;
      }
      temp     = z + w;
      H[loc].r = q.r * temp;
      H[loc].i = q.i * temp;
      for (i=kp1; i<m; i++) {
        q.r = 0.0;
        q.i = 0.0;
        for (j=kp1; j<n; j++) {
          q = cplusc(q, cmultc(conjgc(H[k*nmax+j]), H[i*nmax+j]));
        }
        temp = 1.0 / (z * (z + w));
        q.r *= temp;
        q.i *= temp;
        for (j=kp1; j<n; j++) {
          loc1 = i * nmax + j;
          H[loc1] = clessc(H[loc1], cmultc(q, H[k*nmax+j]));
        }
      }
      temp  = -cabsc(H[loc]);                /* Phase transformation. */
      ctemp = conjgc(H[loc]);
      ctemp.r /= temp;
      ctemp.i /= temp;
      for (i=kp1; i<m; i++) {
        loc1 = i * nmax + kp1;
        H[loc1] = cmultc(H[loc1], q);
      }
    }
    k = kp1;
    goto _2;
  }
  eps = 0.0;                    /* Tolerance for negligible elements. */
  for (k=0; k<n; k++) {
    s[k] = b[k];
    t[k] = c[k];
    eps = max(eps, (s[k] + t[k]));
  }
  eps *= eta;
  for (j=0; j<nu; j++) {            /* Initialization of U[] and V[]. */
    for (i=0; i<m; i++) {
      loc = i * nmax +j;
      U[loc].r = 0.0;
      U[loc].i = 0.0;
    }
    U[j*nmax+j].r = 1.0;
  }
  for (j=0; j<nv; j++) {
    for (i=0; i<n; i++) {
      loc = i * nmax +j;
      V[loc].r = 0.0;
      V[loc].i = 0.0;
    }
    V[j*nmax+j].r = 1.0;
  }
  for (k=n-1; k>=0; k--) {                     /* QR Diagonalization. */
    for (l=k-1; l>=0; l--) {                     /* Test for a split. */
      if (fabs(t[l])   <= eps) goto _3;
      if (fabs(s[l-1]) <= eps) break;
    }
    if (l) break;
    cs = 0.0;                                        /* Cancellation. */
    sn = 1.0;
    ll1 = l - 1;
    for (i=l; i<=k; i++) {
      f = sn * t[i];
      t[i] *= cs;
      if (fabs(f) <= eps) break;
      a = s[i];
      w = sqrt(f * f + a * a);
      s[i] = w;
      cs =  a / w;
      sn = -f / w;
      if (nu) {
        for (j=0; j<m; j++) {
          loc = j * nmax;
          x = U[loc+ll1].r;
          y = U[loc+i].r;
          U[loc+ll1].r = x * cs + y * sn;
          U[loc+ll1].i = 0.0;
          U[loc+i].r   = y * cs - x * sn;
          U[loc+i].i   = 0.0;
        }
      }
      for (j=n; j<n+np; j++) {
        loc = ll1 * nmax + j;
        q.r = H[loc].r;
        q.i = H[loc].i;
        loc1= i * nmax + j;
        r.r = H[loc1].r;
        r.i = H[loc1].i;
        H[loc]  = cplusc(cmultc(q, cmplxc(cs, 0.0)), 
                         cmultc(r, cmplxc(sn, 0.0)));
        H[loc1] = clessc(cmultc(r, cmplxc(cs, 0.0)),
                         cmultc(q, cmplxc(sn, 0.0)));
      }
    }
_3: w = s[k];                                /* Test for convergence. */
    if (l != k) {
      x = s[l];                                      /* Origin shift. */
      y = s[k-1];
      g = t[k-1];
      a = t[k];
      f = ((y - w) * (y + w) + (g - a) * (g + a)) / (2.0 * a * y);
      g = sqrt(f * f + 1.0);
      if (f < 0.0) g = -g;
      f = ((x - w) * (x + w) + (y / (f + g) - a) * a) / x;
      cs = 1.0;                                           /* QR step. */
      sn = 1.0;
      lp1 = l + 1;
      for (i=lp1; i<=k; i++) {
        g = t[i];
        y = s[i];
        a = sn * g;
        g = cs * g;
        w = sqrt(a * a + f * f);
        t[i-1] = w;
        cs = f / w;
        sn = a / w;
        f = x * cs + g * sn;
        g = g * cs - x * sn;
        a = y * sn;
        y = y * cs;
        if (nv) {
          for (j=0; j<n; j++) {
            loc = j * nmax + i - 1;
            x = V[loc].r;
            w = V[loc+1].r;
            V[loc].r   = x * cs + w * sn;
            V[loc].i   = 0.0;
            V[loc+1].r = w * cs - x * sn;
            V[loc+1].i = 0.0;
          }
        }
        w = sqrt(a * a + f * f);
        s[i-1] = w;
        cs = f / w;
        sn = a / w;
        f  = cs * g + sn * y;
        x  = cs * y - sn * g;
        if (nu) {
          for (j=0; j<m; j++) {
            loc = j * nmax + i - 1;
            x = U[loc].r;
            w = U[loc+1].r;
            U[loc].r   = y * cs + w * sn;
            U[loc].i   = 0.0;
            U[loc+1].r = w * cs - y * sn;
            U[loc+1].i = 0.0;
          }
        }
        for (j=n; j<n+np; j++) {
          loc = (i - 1) * nmax + j;
          q.r = H[loc].r;
          q.i = H[loc].i;
          r.r = H[loc+nmax].r;
          r.i = H[loc+nmax].i;
          H[loc]      = cplusc(cmultc(q, cmplxc(cs, 0.0)),
                               cmultc(r, cmplxc(sn, 0.0)));
          H[loc+nmax] = clessc(cmultc(r, cmplxc(cs, 0.0)),
                               cmultc(q, cmplxc(sn, 0.0)));
        }
      }
      t[l] = 0.0;
      t[k] = f;
      s[k] = x;
      continue;
    }
    if (w < 0.0) {                                    /* Convergence. */
      s[k] = -w;
      if (nv) {
        for (j=0; j<n; j++) {
          loc = j * nmax + k;
          V[loc].r = -V[loc].r;
          V[loc].i = -V[loc].i;
        }
      }
    }
  }
  for (k=0; k<n; k++) {                      /* Sort singular values. */
    g = s[k];
    j = k;
    for (i=k; i<n; i++) {
      if (s[i] < g) {
        g = s[i];
        j = i;
      }
    }
    if (j != k) {
      s[j] = s[k];
      s[k] = g;
      if (nv) {
        for (i=0; i<n; i++) {
          loc = i * nmax;
          q.r        = V[loc+j].r;
          q.i        = V[loc+j].i;
          V[loc+j].r = V[loc+k].r;
          V[loc+j].i = V[loc+k].i;
          V[loc+k].r = q.r;
          V[loc+k].i = q.i;
        }
      }
      if (nu) {
        for (i=0; i<m; i++) {
          loc = i * nmax;
          q.r        = U[loc+j].r;
          q.i        = U[loc+j].i;
          U[loc+j].r = U[loc+k].r;
          U[loc+j].i = U[loc+k].i;
          U[loc+k].r = q.r;
          U[loc+k].i = q.i;
        }
      }
      for (i=n; i<n+np; i++) {
        q.r        = H[j*nmax+i].r;
        q.i        = H[j*nmax+i].i;
        H[j*nmax+i].r = H[k*nmax+i].r;
        H[j*nmax+i].i = H[k*nmax+i].i;
        H[k*nmax+i].r = q.r;
        H[k*nmax+i].i = q.i;
      }
    }
  }
  if (nu) {                                   /* Back transformation. */
    for (k=n-1; k>=0; k--) {
      if (b[k] != 0.0) {
        loc = k * nmax + k;
        temp = cabsc(H[loc]);
        q.r = -H[loc].r / temp;
        q.i = -H[loc].i / temp;
        for (j=0; j<nu; j++) {
          loc = k * nmax + j;
          U[loc] = cmultc(q, U[loc]);
        }
        for (j=0; j<nu; j++) {
          q.r = 0.0;
          q.i = 0.0;
          for (i=k; i<m; i++) {
            q = cplusc(q, conjgc(cmultc(H[i*nmax+k], U[i*nmax+j])));
          }
          temp = cabsc(H[k*nmax+k]) * b[k];
          q.r /= temp;
          q.i /= temp;
          for (i=k; i<m; i++) {
            loc = i * nmax;
            U[loc+j] = clessc(U[loc+j], cmultc(q, H[loc+k]));
          }
        }
      }
    }
  }
  if (nv) {
    for (k=n-2; k>=0; k--) {
      kp1 = k + 1;
      if (c[kp1] != 0.0) {
        loc = k * nmax + kp1;
        temp = -1.0 / cabsc(H[loc]);
        q = conjgc(H[loc]);
        q.r *= temp;
        q.i *= temp;
        for (j=0; j<nv; j++) {
          loc = kp1 * nmax + j;
          V[loc] = cmultc(q, V[loc]);
        }
        for (j=0; j<nv; j++) {
          q.r = 0.0;
          q.i = 0.0;
          for (i=k; i<n; i++) {
            q = cplusc(q, cmultc(H[k*nmax+i], V[i*nmax+j]));
          }
          temp = 1.0 / (cabsc(H[k*nmax+kp1]) * c[kp1]);
          q.r *= temp;
          q.i *= temp;
          for (i=k; i<n; i++) {
            loc = i * nmax + j;
            V[loc] = clessc(V[loc], cmultc(q, conjgc(H[k*nmax+i])));
          }
        }
      }
    }
  }
  free(t);
  free(c);
  free(b);
  return;
}
