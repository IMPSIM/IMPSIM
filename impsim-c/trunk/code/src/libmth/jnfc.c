/* ------------------------------------------------------------------ */
/* jnfc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the eigenvalues and, optionally, the eigenvectors of a 
|     complex matrix after reducing the matrix to Jordan normal form.
|
|     Access:
|       ierr = (int) jnfc(int n, int istep, real ein, real tol, 
|         complex H[], complex Z[], complex W[], real supdiag[], 
|         int next[], int mult[], int ndef[], int ndfloc[], int *nblock, 
|         real delnrm[], real sm[]);
|     int  n,        i  -The order of the eigensystem.
|     int  istep,    i  -Requests return from jnfc() after step number 
|       istep (istep = 1,2,...,7); different choices give reduction to:
|         1  Upper triangular form;
|         2  Upper triangular form with the eigenvalues sorted such that
|              close eigenvalues appear in adjacent positions;
|         3  In addition to 2, grouping of close eigenvalues into blocks
|              corresponding to multiple eigenvalues;
|         4  Block diagonal upper triangular form;
|         5  Block diagonal upper triangular form and the invariant sub-
|              spaces corresponding to the diagonal blocks have unitary
|              bases;
|         6  The structure of each diagonal block is determined.
|         7  Full reduction to Jordan normal form.
|     real ein,      i  -A tolerance parameter corresponding to pertur-
|       bations of H[n,n]; used in the grouping of multiple eigenvalues.
|     real tol,      i  -A tolerance parameter used in the construction 
|       of the nilpotent matrices [used in cdeflc()].
|     complex H[n,n],i/o-Defining matrix on entry; destroyed on output.
|     complex Z[n,n],o  -The accumulated transformations from steps 1 to
|       7 of the algorithm.  If istep >= 7, Z contains the eigenvectors
|       and the principal vectors.
|     complex W[n],  o  -The eigenvalues found.  If 1 <= istep <= 5 W[] 
|       are computed by clr2c(). If istep >= 6 W[] contain the main 
|       diagonal elements of the Jordan matrix.
|     real supdiag[n],o -The superdiagonal elements of the Jordan matrix 
|       (the coupling elements) if istep >= 7.
|     int  next[n],  o  -The column indices of supdiag[]; next[i] = j 
|       implies that the vector with coupling element supdiag[i] is 
|       placed in column j of Z[] (if istep >= 7).
|     int  mult[n],  o  -Indicates the multiplicities of multiple eigen-
|       values (if istep >= 3).  mult[i+1]-mult[i] = multiplicity of 
|       eigenvalue i for i=0,1,2,...<*nblock.
|     int  ndef[n],  o  -Indicates the structure of H[] (if istep >= 6).
|     int  ndfloc[n],o  -Contains pointer references.  ndfloc[i] = j 
|       means that information about the structure of multiple eigen-
|       value i starts in position j of ndef[] (if istep >= 6).
|     int  *nblock,  o  -The number of multiple eigenvalues (if istep 
|       >= 3).
|     real delnrm[n],o  -Contains information about deleted elements 
|       during the processes of finding nilpotent matrices; delnrm[i] = 
|       euclidean norm of the deleted part of block i for i=0,1,2,... < 
|       *nblock (if istep >= 6).
|     real sm[n],    o  -Contains estimates of the spectral projectors 
|       corresponding to different multiple eigenvalues (if istep >= 4).
|     int  ierr,     o  -A convergence parameter set by clr2c(); ierr= 0 
|       for normal return; ierr = j  if the j-th eigenvalue has not been 
|       determined after 30 iterations.  If exit has ierr != 0, none of 
|       the output parameters contain meaningful results (if istep>=1).
|
|     Error Conditions:
|       Lack of convergence is indicated by ierr returned != 0.
|
|     Comments:
|       The technique used is the QR transformation method with shifts.
|     The matrix is first reduced to upper Hessenberg form by stabalized
|     elementary similarity transformations.
|       The complex matrix H[] is destroyed during calculation of the
|     eigenvalues and eigenvectors.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int jnfc(int n, int istep, real ein, real tol, complex H[], 
    complex Z[], complex W[], real supdiag[], int next[], int mult[], 
    int ndef[], int ndfloc[], int *nblock, real delnrm[], real sm[])
#else
  int jnfc(n, istep, ein, tol, H, Z, W, supdiag, next, mult, ndef, 
    ndfloc, nblock, delnrm,  sm)
  int n, istep
  real ein, tol;
  complex H[], Z[], W[];
  real supdiag[];
  int next[], mult[], ndef[], ndfloc[], *nblock;
  real delnrm[], sm[];
#endif
{
  complex Hik, Hj, Hjl, Hjp1l, Hlj, Hljp1, m, my, ny, sl, wmlt, Wm, 
          *Wmlt, x, Zj;
  int     high, i, i1, i2, ib, id, idef, ierr, im, *intger, ip, j, j1, 
          j2, j3, k, k5, kb, kp, kprim, l, l1, loc, low, lvects, nd, 
          ndf, ne, nf, nf1, nkf, nks, nrf, nrs, ns, nss;
  real    b, c1, c2, denom, dist, dist2, *dt, einfnorm, fnorm, ksi, 
          *radi, *radr, rgavg, rgmax, rgmin, rsum, tolfnorm, t1, t2;

  if (n <= 1) return(0);

/* Acquire working space. */
  intger = (int *)     calloc(n, sizeof(int));
  dt     = (real *)    calloc(n, sizeof(real));
  radr   = (real *)    calloc(n, sizeof(real));
  radi   = (real *)    calloc(n, sizeof(real));
  Wmlt   = (complex *) calloc(n, sizeof(complex));

/* Initialize. */
  for (i=0; i<n; i++) {
    supdiag[i]= 0.0;
    next[i]   = 0;
    mult[i]   = 0;
    ndef[i]   = 0;
    ndfloc[i] = 0;
    intger[i] = 0;
  }

/* Step 1:
   Transform the matrix H[n,n] into triangular form by using the Eispack
     routines CBAL, COMHES, COMLR2, and CBABK2. */
  cbalnc(n, H, &low, &high, radi);  /*First, balance the H[,] matrix. */

/* Find einfnorm and tolfnorm from Frobenius norm of the H[,] matrix. */
  fnorm = 0.0;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      loc = i*n+j;
      fnorm += H[loc].r * H[loc].r + H[loc].i * H[loc].i;
    }
  }
  fnorm    = sqrt(fnorm);
  einfnorm = ein * fnorm;
  tolfnorm = tol * fnorm;

/* Transform to upper Hessenberg form. */
  chesnc(n, low, high, H, intger);

/* Transform to upper triangular form. */
/* Note: A new parameter (lvects) has been added to clr2c().  lvects == 
     FALSE implies that the eigenvectors need not be computed, i.e., 
     that there is no backsubstitution and the user gets the transforma-
     tions made during the LR-process in the matrices Z.  This change 
     consists of one extra statement in the code of clr2c():
             if (lvects == FALSE) goto _1001;
     is placed directly after the statement
       _680: if (n == 1) goto _1001; */
  lvects = FALSE;
  ierr = clr2c(n, lvects, low, high, intger, H, W, Z);
  if (ierr) return(ierr);

/* Transform the vectors so that Z contains the transformations which
     transformed H to upper triangular form. */
  cblbkc(n, low, high, n, intger, radi, Z);
  if (istep == 1) return(ierr);

/* Step 2:
   Sort the diagonal elements of the triangular matrix so that the 
     multiple eigenvalues appear in adjacent positions. */
  for (k=n-1; k>0; k--) {             /* Index for actual eigenvalue. */
    loc  = k*n+k;
    dist = cabsc(clessc(H[loc], H[loc-n-1]));
    kprim = k;
    for (j1=0; j1<k-1; j1++) {
      j = k - j1 - 2;
      dist2 = cabsc(clessc(H[j*n+j], H[loc]));
      if (dist2 < dist) {
        kprim = j;
        dist = dist2;
      }
    }
    if (kprim == k) continue;
    for (j=kprim; j<=k-2; j++) {

/* Change places of diagonal elements H[j,j] and H[j+1,j+1] with a 
     unitary transformation. */
      loc          = j*n+j;
      ksi          = cabsc(cplusc(clessc(H[loc+n+1],H[loc]), H[loc+1]));
      my.r         = H[loc+1].r / ksi;
      my.i         = H[loc+1].i / ksi;
      ny           = clessc(H[loc+n+1], H[loc]);
      ny.r        /= ksi;
      ny.i        /= ksi;
      sl.r         = H[loc].r;
      sl.i         = H[loc].i;
      H[loc].r     = H[loc+n+1].r;
      H[loc].i     = H[loc+n+1].i;
      H[loc+n+1].r = sl.r;
      H[loc+n+1].i = sl.i;
      H[loc+1].i   = -H[loc+1].i;
      for (l=0; l<j-1; l++) {
        loc        =  l*n+j;
        Hlj.r      =  H[loc].r;
        Hlj.i      =  H[loc].i;
        Hljp1.r    =  H[loc+1].r;
        Hljp1.i    =  H[loc+1].i;
        H[loc].r   =  my.r*Hlj.r-my.i*Hlj.i+ny.r*Hljp1.r-ny.i*Hljp1.i;
        H[loc].i   =  my.r*Hlj.i+my.i*Hlj.r+ny.r*Hljp1.i+ny.i*Hljp1.r;
        H[loc+1].r = -ny.r*Hlj.r-ny.i*Hlj.i+my.r*Hljp1.r+my.i*Hljp1.i;
        H[loc+1].r = -ny.r*Hlj.i+ny.i*Hlj.r+my.r*Hljp1.i-my.i*Hljp1.r;
      }
      for (l=0; l<n; l++) {                 /* Accumulate transforms. */
        loc        =  l*n+j;
        Hlj.r      =  Z[loc].r;
        Hlj.i      =  Z[loc].i;
        Hljp1.r    =  Z[loc+1].r;
        Hljp1.i    =  Z[loc+1].i;
        Z[loc].r   =  my.r*Hlj.r-my.i*Hlj.i+ny.r*Hljp1.r-ny.i*Hljp1.i;
        Z[loc].i   =  my.r*Hlj.i+my.i*Hlj.r+ny.r*Hljp1.i+ny.i*Hljp1.r;
        Z[loc+1].r = -ny.r*Hlj.r-ny.i*Hlj.i+my.r*Hljp1.r+my.i*Hljp1.i;
        Z[loc+1].r = -ny.r*Hlj.i+ny.i*Hlj.r+my.r*Hljp1.i-my.i*Hljp1.r;
      }
      for (l=j+1; l<n; l++) {
        loc        =  j*n+l;
        Hjl.r      =  H[loc].r;
        Hjl.i      =  H[loc].i;
        Hjp1l.r    =  H[loc+n].r;
        Hjp1l.i    =  H[loc+n].i;
        H[loc].r   =  my.r*Hjl.r+my.i*Hjl.i+ny.r*Hjp1l.r+ny.i*Hjp1l.i;
        H[loc].i   =  my.r*Hjl.i-my.i*Hjl.r+ny.r*Hjp1l.i-ny.i*Hjp1l.r;
        H[loc+n].r = -ny.r*Hjl.r+ny.i*Hjl.i+my.r*Hjp1l.r-my.i*Hjp1l.i;
        H[loc+n].r = -ny.r*Hjl.i-ny.i*Hjl.r+my.r*Hjp1l.i+my.i*Hjp1l.r;
      }
    }
  }
  if (istep == 2) goto _done;

/* Step 3.
   Use the Gershgorin circles constructed for diagonal similarity trans-
     formations of the matrix to decide which of the eigenvalue approxi-
     mations from groups corresponding to multiple eigenvalues. */
  ns = n;
  ib = 0;
_4:
  nf = 0;
  ne = ns;
  nd = ne - 1;
  mult[ib] = ne;
  while (ns >= 1) {
_2: wmlt.r = 0.0;
    wmlt.i = 0.0;
    for (k=nd; k<ne; k++) {
      loc = k * n + k;
      wmlt.r += H[loc].r;
      wmlt.i += H[loc].i;
    }
    denom = 1.0 / (real) (ne - nd);
    wmlt.r *= denom;
    wmlt.i *= denom;
    while (nd > nf) {
      rgmax = 0.0;
      for (k=nd; k<ne; k++) {
        rgmax = max(rgmax, cabsc(clessc(H[k*n+k], wmlt)));
      }
      rgmin = cabsc(clessc(H[nd*n+nd], wmlt));
      for (k=nf; k<(nd-1); k++) {
        rgmin = min(rgmin, cabsc(clessc(H[k*n+k], wmlt)));
      }
      for (k=ne; k<n; k++) {
        rgmin = min(rgmin, cabsc(clessc(H[k*n+k], wmlt)));
      }
      rgavg = 0.5 * (rgmax + rgmin);
      for (k=0; k<n; k++) {
        radi[k] = abs(cabsc(clessc(H[k*n+k], wmlt)) - rgavg);
      }

/* With the above we have fixed the circle with the radius rgmax, and 
     drawn circles around every eigenvalue which touches at the half 
     distance 0.5*(rgmax+rgmin).  These radii are stored in the vector 
     radi[k].  Next we compute dt[k], equal to the diagonal similarity
     transformation, and investigate if we have managed to isolate the 
     last m eigenvlaues. */
      k = n - 1;
_3:   rsum = 0.0;
      for (i=k; i<n; i++) {
        rsum += cabsc(H[k*n+i]) / dt[i];
      }
      dt[k] = radi[k] / (rsum + einfnorm);
      if (dt[k] < 1.0) {
        nd--;
        goto _2;
      } else {
        k--;
        if (k < nf) break;
        goto _3;
      }
    }
    Wmlt[ib].r = wmlt.r;  /* Store a multiple eigenvalue in Wmlt[ib]. */
    Wmlt[ib].i = wmlt.i;
    ib++;
    ns = nd;
    goto _4;
  }
  *nblock = ib + 1;
  j = *nblock - 1;
  for (i=0; i<(ib/2); i++) {
    k = mult[j];
    mult[j] = mult[i];
    mult[i] = k;
    if (i != j) {
      Wm.r = Wmlt[j].r;
      Wm.i = Wmlt[j].i;
      Wmlt[j].r = Wmlt[i].r;
      Wmlt[j].i = Wmlt[i].i;
      Wmlt[i].r = Wm.r;
      Wmlt[i].i = Wm.i;
      j--;
    }
  }
  mult[0] = 0;

/* Now call the user written routine decisc, which possibly changes the 
     grouping and/or the values of the multiple eigenvalues. */
  decisc(n, *nblock, mult, Wmlt, H);
  if (istep == 3) goto _done;


/* Step 4.
   Eliminate the elements above the main diagonal and outside the blocks
   corresponding to multiple eigenvalues.  The process is carried out in
   rows working upwards and in columns working from left to right.  We
   compute the blocks M[k,j] and Inv(M[k,j]) (see the algorithm) in 
   order to estimate the spectral projectors sm[k] for eigenvalue k, k =
   0,1,2,...<*nblock.  The Inv(M[k,j]) blocks are stored in the corres-
   ponding eliminated blocks of H[]. */
  for (i=0; i<*nblock; i++) {
    sm[i] = 0.0;
    dt[i] = 0.0;
  }
  l1 = *nblock + 1;
  for (j2=0; j2<*nblock; j2++) {
    ib = *nblock - 1 - j2;
    ns = mult[ib];
    if (ns < 1) goto _5;
    for (i2=mult[ib]; i2<ns; i2++) {
      k5 = 0;
      i  = ns - i2 + mult[ib];
      for (k=ns; k<n; k++) {
        radr[k] = 0.0;
        radi[k] = 0.0;
      }
      for (k=ns; k<n; k++) {
        m = cdivc(H[i*n+k], clessc(H[k*n+k], H[i*n+i]));
        for (j=0; j<i-1; j++) {
          x = cplusc(H[j*n+k], cmultc(H[j*n+i], m));
          H[j*n+k].r = x.r;
          H[j*n+k].i = x.i;
        }
        if (k > mult[l1]) {
          l1++;
          k5++;
        }
        nss = mult[l1];
        for (j=k; j<nss; j++) {
          x = clessc(H[i*n+j], cmultc(H[k*n+j], m));
          H[i*n+j].r = x.r;
          H[i*n+j].i = x.i;
        }
        for (j=0; j<n; j++) {           /* Accumulate the transforms. */
          x = cplusc(Z[j*n+k], cmultc(Z[j*n+i], m));
          Z[j*n+k].r = x.r;
          Z[j*n+k].i = x.i;
        }
        H[i*n+k] = clessc(cmplxc(radr[k], radi[k]), m);
        for (l=nss; l<n; l++) {
          x = cmultc(m, H[k*n+l]);
          radr[l] -= x.r;
          radi[l] -= x.i;
        }
        sm[l1-1] += cabsc(m);
        dt[ib] += cabsc(H[i*n+k]);
      }
      l1 -= k5;
    }
    l1--;
  }
_5:
  for (i=0; i<*nblock; i++) {
    sm[i] = (1.0 + sqrt(sm[i])) * (1.0 + sqrt(dt[i]));
  }

/* Zero the elements beyond the main diagonal.  This is done because the
     algorithms which compute the nilpotent matrix of a diagonal block
     work on the whole block which is assumed to be upper triangular. */
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      if (i > j) {
        loc = i * n + j;
        H[loc].r = 0.0;
        H[loc].i = 0.0;
      }
    }
  }
  if (istep == 4) goto _done;

/* Step 5.
   Orthonormalize the vectors corresponding to a multiple eigenvalue (1,
     2,...,*nblock) by the modified Gramm Schmidt process.  The vectors
     are updated and stored in Z[,]. */
  ns = 0;
  for (ib=0; ib<*nblock; ib++) {
    nf = ns - 1;
    ns = mult[ib];
    for (k=nf+1; k<ns; k++) {
      rsum = 0.0;
      for (i=0; i<n; i++) {
        loc = i * n + k;
        rsum += Z[loc].r * Z[loc].r + Z[loc].i * Z[loc].i;
      }
      rsum = sqrt(rsum);
      W[1].r = rsum;
      W[1].i = 0.0;
      for (i=0; i<n; i++) {
        loc = i * n + k;
        Z[loc].r /= rsum;
        Z[loc].i /= rsum;
      }
      for (j=k+1; j<ns; j++) {
        x.r = 0.0;
        x.i = 0.0;
        for (i=0; i<n; i++) {
         x = cplusc(x, cmultc(Z[i*n+k], Z[i*n+j]));
        }
        l = j - k;
        W[l].r = x.r;
        W[l].i = x.i;
        for (i=0; i<n; i++) {
          loc = i * n + j;
          Z[loc] = clessc(Z[loc], cmultc(W[l], Z[i*n+k]));
        }
      }
      for (i=k; i<ns; i++) {
        x.r = 0.0;
        x.i = 0.0;
        for (j=k; j<i; j++) {
          l = j - k;
          x = cplusc(x, cmultc(W[l], H[j*n+i]));
        }
        H[k*n+i].r = x.r;
        H[k*n+i].i = x.i;
      }
      for (j=k+1; j<ns; j++) {
        l = j - k;
        x = cmultc(W[l], H[i*n+k]);
        x.r /= rsum;
        x.i /= rsum;
        loc = i * n + j;
        H[loc] = clessc(H[loc], x);
      }
      loc = i * n + k;
      H[loc].r /= rsum;
      H[loc].i /= rsum;
    }
  }
  if (istep == 5) goto _done;

/* Step 6.
   For each diagonal block corresponding to a multiple eigenvalue, find
     a nilpotent matrix, i.e., determine the structure of the block. Use
     RQ decompositions or CSVD decompositions (see algorithm).  Note the
     structure in ndef[]. */
  idef = 0;
  ndef[0] = 0;

/* Tolerance gap is c2/c1 in the deflation process. */
  c1 = 1.0;
  c2 = 1000.0;
  ns = -1;
  for (ib=0; ib<*nblock; ib++) {
    id = 0;
    nf = ns;
    ns = mult[ib+1];
    delnrm[ib] = 0.0;
    ndfloc[ib] = idef;
    Wm.r = Wmlt[ib].r;
    Wm.i = Wmlt[ib].i;
    for (i=nf+1; i<ns; i++) {
      loc = i * n + i;
      H[loc] = clessc(H[loc], Wm);
    }
    ndf = 1;
    if (nf == ns - 1) goto _6;
_8: if (nf > ns - 1) goto _7;
    kb  = ns - nf;
    ndf = cdeflc(n, kb, &H[nf*n+nf], &Z[nf], tolfnorm, id, c1, c2,
      &delnrm[ib]);
_6: id += ndf;
    nf += ndf;
    idef++;
    ndef[idef] = nf + 1;
    goto _8;
_7: for (i=nf+1; i<ns; i++) {
      loc = i * n + i;
      H[loc] = clessc(H[loc], Wm);
    }
    delnrm[ib] = sqrt(delnrm[ib]);
  }
  if (istep == 6) goto _done;

/* Step 7.
   For each diagonal block corresponding to a multiple eigenvalue, 
     compute the coupling elements of the principal chains.  This is 
     done by stabilized elimination matrices; (see the algorithm). */
  ns = 0;
  for (i1=0; i1<*nblock; i1++) {
    nf = ns;
    ns = mult[i1+1];
    if (nf >= ns - 1) continue;
    Wm.r = Wmlt[i1].r;
    Wm.i = Wmlt[i1].i;
    for (i=nf; i<ns; i++) {
      loc = i * n + i;
      H[loc] = clessc(H[loc], Wm);
    }
    nkf = ns;
    j1 = ndfloc[i1+1];
    if (j1 <= 0) j1 = idef;
    nf1 = ndfloc[i1];
    j1 -= nf1 + 1;  /* j1=number of T[k,k+1] blocks; (see algorithm). */
    for (j2=0; j2<j1; j2++) {
      j3  = j1 - j2 + nf1;
      nrs = ndef[j3] - 1;
      nrf = ndef[j3-1];
      nks = nkf;
      nkf = nrs;
      ip  = nrs;
      for (k=nkf; k<nks; k++) {   /* Pass one of elimination process. */

/* Find the maximum of abs(H[i,kp].r+H[i,kp].i) where i=nrf,...,ip-1. */
        kp = nks - k + nkf;
        im = ip;
        loc = ip * n + kp;
        x.r = H[loc].r;
        x.i = H[loc].i;
        for (i=nrf; i<ip; i++) {
          loc = i * n + kp;
          if ((abs(H[loc].r)+abs(H[loc].i)) > (abs(x.r)+abs(x.i))) {
            x.r = H[loc].r;
            x.i = H[loc].i;
            im  = i;
          }
        }
        if (im != ip) {
          for (j=nkf; j<kp; j++) {     /* Interchange rows ip and im. */
            loc = ip * n + j;
            x.r = H[loc].r;
            x.i = H[loc].i;
            H[loc].r = H[im*n+j].r;
            H[loc].i = H[im*n+j].i;
            H[im*n+j].r = x.r;
            H[im*n+j].i = x.i;
          }
          for (j=0; j<n; j++) {     /* Interchange columns ip and im. */
            if ((j >= nf) && (j < nrf-1)) {
              loc = j * n + ip;
              x.r = H[loc].r;
              x.i = H[loc].i;
              H[loc].r = H[j*n+im].r;
              H[loc].i = H[j*n+im].i;
              H[j*n+im].r = x.r;
              H[j*n+im].i = x.i;
            }
            loc = j * n + ip;
            x.r = Z[loc].r;
            x.i = Z[loc].i;
            Z[loc].r = Z[j*n+im].r;
            Z[loc].i = Z[j*n+im].i;
            Z[j*n+im].r = x.r;
            Z[j*n+im].i = x.i;
          }
        }

/* Eliminate elements H[j,kp] j=nf,...,ip-1; pivot element H[ip,kp]. */
        loc = ip * n + kp;
        for (l=nkf; l<kp; l++) {
          for (j=nf; j<ip-1; j++) {
            m = cmultc(H[ip*n+l], cdivc(H[j*n+kp], H[loc]));
            H[j*n+l] = clessc(H[j*n+l], m);
          }
        }

/* Complete similarity transformation and accumulate transforms. */
        for (j=0; j<n; j++) {
          loc = j * n + ip;
          Hj.r = H[loc].r;
          Hj.i = H[loc].i;
          Zj.r = Z[loc].r;
          Zj.i = Z[loc].i;
          for (l=nf; l<ip-1; l++) {
            m = cdivc(H[l*n+kp], H[ip*n+kp]);
            if ((j >= nf) && (j < nrf-1)) {
              Hj = cplusc(Hj, cmultc(m, H[j*n+l]));
            }
            Zj = cplusc(Zj, cmultc(m, Z[j*n+l]));
          }
          if ((j >= nf) && (j < nrf-1)) {
            H[loc].r = Hj.r;
            H[loc].i = Hj.i;
          }
          Z[loc].r = Zj.r;
          Z[loc].i = Zj.i;
        }
        ip--;
      }                                 /* This is the end of pass 1. */
      for (kp=nkf; kp<nks; kp++) {  /* Pass 2 in elimination process. */
        ip++;

/* Eliminate the elements H[j,kp] for j=ip+1,...,nrs. */

/* Complete the similarity transformation and accumulate transforms. */
        loc = ip * n + kp;
        Hik.r = H[loc].r;
        Hik.i = H[loc].i;
        b = cabsc(Hik);
        t1 =  Hik.r / b;
        t2 = -Hik.i / b;
        for (j=0; j<n; j++) {
          loc = j * n + ip;
          Hj.r = H[loc].r;
          Hj.i = H[loc].i;
          Zj.r = Z[loc].r;
          Zj.i = Z[loc].i;
          for (l=ip; l<nrs; l++) {
            m = cdivc(H[l*n+kp], H[ip*n+kp]);
            if ((j >= nf) && (j < nrf-1)) {
              Hj = cplusc(Hj, cmultc(m, H[j*n+l]));
            }
            Zj = cplusc(Zj, cmultc(m, Z[j*n+l]));
          }
          m.r = t1;
          m.i = t2;
          if ((j >= nf) && (j < nrf-1)) {
            Hj = cdivc(Hj, m);
            H[loc].r = Hj.r;
            H[loc].i = Hj.i;
          }
          Zj = cdivc(Zj, m);
          Z[loc].r = Zj.r;
          Z[loc].i = Zj.i;
        }
        loc = ip * n + kp;
        m.r = t1;
        m.i = t2;
        H[loc] = cmultc(Hik, m);
        next[ip] = kp;
        supdiag[ip] = H[loc].r;
      }                                 /* This is the end of pass 2. */
    }                                        /* A new T[k,k+1] block. */
    for (i=nf; i<ns; i++) {
      loc = i * n + i;
      H[loc].r += Wm.r;
      H[loc].i += Wm.i;
    }
  }
_done:
  for (i=0; i<n; i++) {
    loc = i * n + i;
    W[i].r = H[loc].r;
    W[i].i = H[loc].i;
  }
  return(ierr);
}
