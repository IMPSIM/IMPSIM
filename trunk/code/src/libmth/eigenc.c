/* ------------------------------------------------------------------ */
/* eigenc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the eigenvalues and eiginvectors of a real matrix.
|
|     Access:
|       nogo = (int) eigenc(real a[], int n, int lgoto, real wr[],
|         real wi[], complex eigvct[]);
|     real    a[n,n],   i/o-Real matrix defining the eigenvalue problem.
|     int     n,          i-Dimension of the eigensystem.
|     int     lgoto,      i-Flag set TRUE if eigenvectors are desired.
|     real    wr[n],      o-Array of eigenvalue real parts.
|     real    wi[n],      o-Array of eigenvalue imaginary parts.
|     complex eigvct[n,n],o-Matrix of eigenvectors.
|     int     nogo,       o-Return flag set non-zero on error.
|
|     Error Conditions:
|       nogo != 0 indicates lack of convergence of the iteration
|     process.  Eigenvalues >= nogo are okay, but no eigenvectors are
|     found.
|
|     Comments:
|       The technique used is the QR transformation method with shifts.
|     The matrix is first reduced to upper Hessenberg form by stabalized
|     elementary similarity transformations.
|       The real matrix a[] is destroyed during calculation of the
|     eigenvalues and eigenvectors.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int eigenc(real a[], int n, int lgoto, real wr[], real wi[],
    complex eigvct[])
#else
  int eigenc(a, n, lgoto, wr, wi, eigvct)
  real    a[];
  int     n, lgoto;
  real    wr[], wi[];
  complex eigvct[];
#endif
{
  complex ca, cb, cc;
  real    anorm, p, q, r, ra, s, sa, save, shift, t, temp, u, v, vi, vr,
          w, x, y, z, zero;
  real   *tr;
  int    *intgr;
  int     i, iter, j, k, km1, l, m, nn, nnm1, nnm2;
# define A(X,Y)             a[(X)*n+(Y)]
# define Eigvct(X,Y)   eigvct[(X)*n+(Y)]
# define Tr(X,Y)           tr[(X)*n+(Y)]
 
/* Acquire space and initialize the similarity transformations. */
  if (lgoto) {
    intgr = (int *)  calloc(n, sizeof(int));
    tr    = (real *) calloc(n * n, sizeof(real));
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        Tr(i, j) = 0.0;
      }
      Tr(i, i) = 1.0;
    }
  }
 
/*  Reduce the matrix to upper Hessenberg form.  */
  for (k=1; k<n-1; k++) {
    km1 = k - 1;
    save = 0.0;
    i = k;
    for (j=k; j<n; j++) {
      if (fabs(A(j, km1)) > fabs(save)) {
        save = A(j, km1);
        i = j;
      }
    }
    if (lgoto) intgr[k] = i;
    if (i != k) {
      for (j=km1; j<n; j++) {
        temp    = A(i, j);
        A(i, j) = A(k, j);
        A(k, j) = temp;
      }
      for (j=0; j<n; j++) {
        temp    = A(j, i);
        A(j, i) = A(j, k);
        A(j, k) = temp;
      }
    }
    if (save) {
      for (i=k+1; i<n; i++) {
        temp = A(i, km1);
        if (temp) {
          temp /= save;
          A(i, km1) = temp;
          for (j=k; j<n; j++) {
            A(i, j) -= temp * A(k, j);
          }
          for (j=0; j<n; j++) {
            A(j, k) += temp * A(j, i);
          }
        }
      }
    }
  }
 
/*  Accumulate the similarity transformations used.  */
  if (lgoto) {
    for (k=n-2; k>0; k--) {
      for (i=k+1; i<n; i++) {
        Tr(i, k) = A(i, k-1);
      }
      i = intgr[k];
      if (i != k) {
        for (j=k; j<n; j++) {
          Tr(k, j) = Tr(i, j);
          Tr(i, j) = 0.0;
        }
        Tr(i, k) = 1.0;
      }
    }
  }
 
/*  Search for eigenvalues.  */
  zero  = 2.3841858e-7;              /* Default tolerance = 2.0^(-22) */
  anorm = 0.0;
  for (i=0; i<n; i++) {
    for (j=max(i-1,0); j<n; j++) {
      anorm += fabs(A(i, j));
    }
  }
  nn = n;
  shift = 0.0;
  while (nn > 0) {
    iter = 0;
    nnm1 = nn - 1;
    nnm2 = nnm1 - 1;
 
/*  Search for a single small subdiagonal element.  */
    while (TRUE) {
      for (l=nnm1; l>0; l--) {
        s = fabs(A(l-1, l-1)) + fabs(A(l, l));
        if (s == 0.0) s = anorm;
        if (fabs(A(l, l-1)) + s == s) goto _2;
      }
      l=0;
_2:   x = A(nnm1, nnm1);
      if (l == nnm1) goto _3;                      /* One root found. */
      y = A(nnm2, nnm2);
      w = A(nnm1, nnm2) * A(nnm2, nnm1);
      if (l == nnm2) goto _4;                     /* Two roots found. */
      if (iter >= 30) {                   /* No roots found; iterate. */
        if (lgoto) {
          free(intgr);
          free(tr);
        }
        return(nn + 1);         /* Error return; too many iterations. */
      }
      if (iter == 10 || iter == 20) {   /* Form an exceptional shift. */
        shift += x;
        for (i=0; i<nn; i++) A(i,i) -= x;
        s = fabs(A(nnm1, nnm2)) + fabs(A(nnm2, nnm2-1));
        x = 0.75 * s;
        y = x;
        w = -0.4375 * s * s;
      }
      iter++;
 
/*  Search for two consecutive small subdiagonal elements.  */
      for (m=nnm2-1; m>=l; m--) {
        z = A(m, m);
        r = x - z;
        s = y - z;
        p = (r * s - w) / A(m+1, m) + A(m, m+1);
        q = A(m+1, m+1) - z - r - s;
        r = A(m+2, m+1);
        s = fabs(p) + fabs(q) + fabs(r);
        p /= s;
        q /= s;
        r /= s;
        if (m == l) goto _5;
        u = fabs(A(m, m-1)) * (fabs(q) + fabs(r));
        v = fabs(p) * (fabs(A(m-1, m-1)) + fabs(z) + fabs(A(m+1, m+1)));
        if (u + v == v) goto _5;
      }
      m = nn-2 - 1;
_5:   for (i=m+2; i<nn; i++) {
        A(i, i-2) = 0.0;
        if (i != m+2) A(i, i-3) = 0.0;
      }
 
/*  Double QR step on rows l to nn and columns m to nn.  */
      for (k=m; k<nnm1; k++) {
        if (k > m) {
          p = A(k, k-1);                /* Set up Householder vector. */
          q = A(k+1, k-1);
          r = 0.0;
          if (k < nnm2) r = A(k+2, k-1);
          x = fabs(p) + fabs(q) + fabs(r);
          if (x == 0.0) continue;
          p /= x;          /* Scale to prevent overflow or underflow. */
          q /= x;
          r /= x;
        }
        s = sign(sqrt(p * p + q * q + r * r), p);
        if (k == m) {
          if (l != m) A(k, k-1) = -A(k, k-1);
        } else {
          A(k, k-1) = -s * x;
        }
        p += s;
        if (s) {
          x = p / s;
          y = q / s;
          z = r / s;
        }
        q /= p;
        r /= p;
 
/*  Row modification.  */
        for (j=k; j<n; j++) {
          p = A(k, j) + q * A(k+1, j);
          if (k < nnm2) {
            p         += r * A(k+2, j);
            A(k+2, j) -= p * z;
          }
          A(k+1, j) -= p * y;
          A(k,   j) -= p * x;
        }
 
/*  Column modification.  */
        j = min(nn, k+4);
        for (i=0; i<j; i++) {
          p = x * A(i, k) + y * A(i, k+1);
          if (k < nnm2) {
            p         += z * A(i, k+2);
            A(i, k+2) -= p * r;
          }
          A(i, k+1) -= p * q;
          A(i, k)   -= p;
        }
 
/*  Accumulate the transformations.  */
        if (lgoto) {
          for (i=0; i<n; i++) {
            p = x * Tr(i, k) + y * Tr(i, k+1);
            if (k < nnm2) {
              p          += z * Tr(i, k+2);
              Tr(i, k+2) -= p * r;
            }
            Tr(i, k+1) -= p * q;
            Tr(i, k)   -= p;
          }
        }
      }
    }
 
/*  One root has been found.  */
_3: A(nnm1, nnm1) = x + shift;
    wr[nnm1] = A(nnm1, nnm1);
    wi[nnm1] = 0.0;
    nn = nnm1;
    continue;
 
/*  Two roots have been isolated.  */
_4: p = 0.5 * (y - x);
    q = p * p + w;
    z = sqrt(fabs(q));
    A(nnm1, nnm1) = x + shift;
    x = A(nnm1, nnm1);
    A(nnm2, nnm2) = y + shift;
 
/*  A pair of real roots has been found.  */
    if (q >= 0.0) {
      z = p + sign(z, p);
      wr[nnm2] = x + z;
      wi[nnm2] = 0.0;
      wr[nnm1] = wr[nnm2];
      if (z) wr[nnm1] = x - w / z;
      wi[nnm1] = 0.0;
      x = A(nnm1, nnm2);
      s = fabs(x) + fabs(z);
      p = x / s;
      q = z / s;
      r = sqrt(p * p + q * q);
      p /= r;
      q /= r;
 
/*  Row modification.  */
      for (j=nnm2; j<n; j++) {
        z = A(nnm2, j);
        A(nnm2, j) = p * A(nnm1, j) + q * z;
        A(nnm1, j) = q * A(nnm1, j) - p * z;
      }
 
/*  Column modification.  */
      for (i=0; i<nn; i++) {
        z = A(i, nnm2);
        A(i, nnm2) = p * A(i, nnm1) + q * z;
        A(i, nnm1) = q * A(i, nnm1) - p * z;
      }
 
/*  Accumulate transformations.  */
      if (lgoto) {
        for (i=0; i<n; i++) {
          z = Tr(i, nnm2);
          Tr(i, nnm2) = p * Tr(i, nnm1) + q * z;
          Tr(i, nnm1) = q * Tr(i, nnm1) - p * z;
        }
      }
 
/*  A complex conjugate pair of roots has been found.  */
    } else {
      wr[nnm2] = x + p;
      wi[nnm2] = z;
      wr[nnm1] = wr[nnm2];
      wi[nnm1] = -z;
    }
    nn = nnm2;
  }
 
/*  Calculate the corresponding eigenvectors.  */
  if (lgoto) {
    for (nn=n; nn>0; nn--) {
      if (anorm == 0.0) break;
      nnm1 = nn - 1;
      nnm2 = nnm1 - 1;
      p = wr[nnm1];
      q = wi[nnm1];
 
/*  Calculate the eigenvector for a real eigenvalue.  */
      if (q == 0.0) {
        m = nn;
        A(nnm1, nnm1) = 1.0;
        for (i=nnm2; i>=0; i--) {
          w = A(i, i) - p;
          r = A(i, nnm1);
          for (j=m-1; j<nnm1; j++) {
            r += A(i, j) * A(j, nnm1);
          }
          if (wi[i] < 0.0) {
            z = w;
            s = r;
          } else if (wi[i] == 0.0) {
            m = i + 1;
            t = w;
            if (t == 0.0) t = zero * anorm;
            A(i, nnm1) = -r / t;
          } else {
            m = i + 1;
            x = A(i, m);
            y = A(m, i);
            q = wr[i] - p;
            q = q * q + wi[i] * wi[i];
            t = (x * s - z * r) / q;
            A(i, nnm1) = t;
            if (fabs(x) > fabs(z)) {
              A(m, nnm1) = -(r + w * t) / x;
            } else {
              A(m, nnm1) = -(s + y * t) / z;
            }
          }
        }
        for (i=n-1; i>=0; i--) {
          z = 0.0;
          for (j=0; j<nn; j++) {
            z += Tr(i, j) * A(j, nnm1);
          }
          Tr(i, nnm1) = z;
          Eigvct(i, nnm1) = cmplxc(z, 0.0);
        }
 
/*  Calculate the eigenvectors for a complex pair of roots.  */
      } else if (q < 0.0) {
        m    = nnm1;
        nnm2 = nnm1 - 1;
        if (fabs(A(nnm1, nnm2)) > fabs(A(nnm2, nnm1))) {
          A(nnm2, nnm2) =                   q  / A(nnm1, nnm2);
          A(nnm2, nnm1) = -(A(nnm1, nnm1) - p) / A(nnm1, nnm2);
        } else {
          ca = cmplxc(0.0, -A(nnm2, nnm1));
          cb = cmplxc((A(nnm2, nnm2) - p), q);
          cc = cdivc(ca, cb);
          A(nnm2, nnm2) = cc.r;
          A(nnm2, nnm1) = cc.i;
        }
        A(nnm1, nnm2) = 0.0;
        A(nnm1, nnm1) = 1.0;
        for (i=nnm2-1; i>=0; i--) {
          w  = A(i, i) - p;
          ra = 0.0;
          sa = A(i, nnm1);
          for (j=m-1; j<nnm1; j++) {
            ra += A(i, j) * A(j, nnm2);
            sa += A(i, j) * A(j, nnm1);
          }
          if (wi[i] < 0.0) {
            z = w;
            r = ra;
            s = sa;
          } else if (wi[i] == 0.0) {
            m = i + 1;
            ca = cmplxc(-ra, -sa);
            cb = cmplxc(w, q);
            cc = cdivc(ca, cb);
            A(i, nnm2) = cc.r;
            A(i, nnm1) = cc.i;
          } else {
            m = i + 1;
            x = A(i, m);
            y = A(m, i);
            vr = wr[i] - p;
            vi = 2.0 * vr * q;
            vr = vr * vr + wi[i] * wi[i] - q * q;
            if (vr == 0.0 && vi == 0.0) vr = zero * anorm
              * (fabs(w) + fabs(q) + fabs(x) + fabs(y) + fabs(z));
            ca = cmplxc((x * r - z * ra + q * sa), 
                        (x * s - z * sa - q * ra));
            cb = cmplxc(vr, vi);
            cc = cdivc(ca, cb);
            A(i, nnm2) = cc.r;
            A(i, nnm1) = cc.i;
            if (fabs(x) > (fabs(z) + fabs(q))) {
              A(m, nnm2) = -(ra + w * A(i, nnm2) - q * A(i, nnm1)) / x;
              A(m, nnm1) = -(sa + w * A(i, nnm1) + q * A(i, nnm2)) / x;
            } else {
              ca = cmplxc((-r - y * A(i, nnm2)), (-s - y * A(i, nnm1)));
              cb = cmplxc(z, q);
              cc = cdivc(ca, cb);
              A(m, nnm2) = cc.r;
              A(m, nnm1) = cc.i;
            }
          }
        }
        for (j=nnm1; j>=nnm2; j--) {
          for (i=0; i<n; i++) {
            z = 0.0;
            for (k=0; k<=j; k++) {
              z += Tr(i, k) * A(k, j);
            }
            Tr(i, j) = z;
          }
        }
        for (i=0; i<n; i++) {
          Eigvct(i, nnm1) = cmplxc(Tr(i, nnm2), -Tr(i, nnm1));
        }
        for (i=0; i<n; i++) {
          Eigvct(i, nnm2).r =  Eigvct(i, nnm1).r;
          Eigvct(i, nnm2).i = -Eigvct(i, nnm1).i;
        }
      }
    }
    free(intgr);
    free(tr);
  }
  return(0);
# undef Tr
# undef Eigvct
# undef A
}
