/* ------------------------------------------------------------------ */
/* cdeflc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Perform a complex singular value decomposition of a block in 
|     order to determine its rank.
|
|     Access:
|       ndef = (int) cdeflc(int n, int kb, complex H[], complex Z[], 
|         real tolfnm, int id, real c1, real c2, real *delnrm);
|     int n,i-The order of the original complex H[n,n] matrix.
|     int kb,i-The dimension of the current block H[,] as called.
|     complex H[n,n],i/o-Defining matrix of the current block; the call
|       is offset such that H[0,0] corresponds to the beginning of the
|       current block.  Only the block H[kb,kb] is affected by the call.
|     complex Z[n,n],i/o-The transformation matrix accumulated during
|       the rank determination process.
|     real tolfnm,i-Tolerance parameter used in the determination of the
|       rank of the actual block (tolfnm = tol * the Frobenius norm of
|       the balanced matrix from cbalnc(); the tolfnm parameter is found
|       by the calling program.
|     int id,i-
|     real c1,c2,i-Tolerance gap is c2/c1 in the deflation process (the
|       parameters are given the values c1 = 1.0, c2 = 1000.0 by jnfc().
|     real delnrm,o-The sum of squared deleted singular values.
|     int ndef,o-The number of deflation steps found, i.e., the number
|       of singular values interpretted as zeroes.
|     
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int cdeflc(int n, int kb, complex H[], complex Z[], real tolfnm, 
    int id, real c1, real c2, real *delnrm)
#else
  int cdeflc(n, kb, H, Z, tolfnm, id, c1, c2, delnrm)
  int n, kb, id;
  complex H[], Z[];
  real tolfnm, c1, c2, *delnrm;
#endif
{
  complex *h, hij, *u, *v, zij;
  int     i, j, jd, k, loc, ndef, nsq;
  real    *s, t1, t2;

/* Aquire working space. */
  nsq = n * n;
  h = (complex *) calloc(nsq, sizeof(complex));
  s = (real *)    calloc(n,   sizeof(real));
  u = (complex *) calloc(nsq, sizeof(complex));
  v = (complex *) calloc(nsq, sizeof(complex));

/* csvdc is CACM algorithm 358 with one change; the singular values are 
   sorted in increasing instead of decreasing order. */
  for (i=0; i<kb; i++) {
    for (j=0; j<kb; j++) {
      loc = i * n + j;
      h[loc].r = H[loc].r;
      h[loc].i = H[loc].i;
    }
  }
  csvdc(h, n, n, kb, kb, 0, kb, kb, s, u, v);

/* Print the singular values to get the theoretical coupling element. */
/*printf("/n Singular values:         ");
  for (i=0; i<kb; i++) {
    printf(" %#12.5f", s[i]);
    if (i % 3 == 1) printf("/n");
  }*/

/* Determine the number of deflation steps, ndef = number of singular
   values interpretted equal to zero. */
  t1 = c1 * tolfnm;
  t2 = c2 * tolfnm;
  for (i=0; i<kb; i++) {
    if (fabs(s[i]) >= t1) goto _2;
  }
  ndef = kb;
  for (i=0; i<kb; i++) {
    *delnrm += s[i] * s[i];
  }
  goto _1;
_2:;
  if (fabs(s[i]) <= t2) {
    if(i < kb) {
      i++;
      goto _2;
    }
  }
  ndef = i - 1;
  if (ndef == 0) ndef = 1;
  for (i=0; i<ndef; i++) {
    *delnrm += s[i] * s[i];
  }

/* Overwrite H[] with v[](trans, conjg) * u[] * diag(s[]). */
  for (i=0; i<kb; i++) {
    for (j=0; j<kb; j++) {
      hij.r = 0.0;
      hij.i = 0.0;
      for (k=0; k<kb; k++) {
        loc = k * n;
        hij = cplusc(hij, cmultc(conjgc(v[loc+i]), u[loc+j]));
      }
      loc = i * n + j;
      H[loc].r = hij.r * s[j];
      H[loc].i = hij.i * s[j];
    }
  }

/* Multiply columns nf,...,nf+id with v(trans, conjg) from the left. */
  for (j=0; j<id; j++) {
    jd = j - id;
    for (i=0; i<kb; i++) {
      hij.r = 0.0;
      hij.i = 0.0;
      for (k=0; k<kb; k++) {
        loc = k * n;
        hij = cplusc(hij, cmultc(conjgc(v[loc+i]), H[loc+jd]));
      }
      h[i].r = hij.r;
      h[i].i = hij.i;
    }
    for (i=0; i<kb; i++) {
      loc = i * n + jd;
      H[loc].r = h[i].r;
      H[loc].i = h[i].i;
    }
  }

/* Finish the similarity transformation and accumulate transforms. */
  for (i=0; i<n; i++) {
    jd = i - id;
    for (j=0; j<kb; j++) {
      hij.r = 0.0;
      hij.i = 0.0;
      zij.r = 0.0;
      zij.i = 0.0;
      for (k=0; k<kb; k++) {
        if (id <= 0) hij = cplusc(hij, cmultc(H[jd*n+k], v[k*n+j]));
        zij = cplusc(zij, cmultc(Z[i*n+k], v[k*n+j]));
      }
      if (jd <= 0) {
        h[j].r = hij.r;
        h[j].i = hij.i;
      }
      u[j].r = zij.r;
      u[j].i = zij.i;
    }
    for (j=0; j<kb; j++) {
      if (jd <= 0) {
        loc = jd * n + j;
        H[loc].r = h[j].r;
        H[loc].i = h[j].i;
      }
      loc = i * n + j;
      Z[loc].r = u[j].r;
      Z[loc].i = u[j].i;
    }
  }

/* Return working space. */
_1:;
  free (v);
  free (u);
  free (s);
  free (h);
  return(ndef);
}
