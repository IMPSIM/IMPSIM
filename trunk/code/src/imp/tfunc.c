/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:11 Jul 09                                          |
|     (C) Copyright, JJU Research, 1984-2009.                          |
|                                                                      |
|     This material is released under the terms of the                 |
|     GNU General Public License, version 3 (GNU GPLv3).               |
|     The full text of that license is available from the 'IMPSim'     |
|     project site on Google Code.                                     |
|                                                                      |
|     This initial release of 'IMPSim' is equivalent to the            |
|     IMP Integrated Mechanisms Program (IMP-2009) and is released     |
|     with the full approval of JJU Research of Madison, WI.           |
|                                                                      |
* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------ */
/* tfunc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Output the requested transfer functions versus frequency.
|
|     Access:
|       (void) tfunc();
|
|     Error Conditions:
|       If the system has no FGC's then no transfer functions can be
|     found.  An error message is printed.
|       If the system mass matrix is singular, then no transfer func-
|     tions can be found.  An error message is printed.
|       If there is numeric difficulty in extracting the eigenvalues
|     and eigenvectors of the system an error message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void tfunc()
{
  Request *request;
  Word    kindin, namein;
  char    chdvc[8], dsplay[8], locdvc[8];
  complex *Eigvct, *T;
  int     i, ii, *irow, *icol, j, nerr, nfgc, nin, nsq, n2, n3;
  real    detM, *D, *Dyn, *G, *K, *M, *MDK, w0, wf, winc, *wi, *wr;

/* If PAUSE ON is set, pause now. */
  if (qbitc(XQ_PAUSE, (void *) &System.xeqflags)) {
    qdvc(dsplay, chdvc, locdvc);
    if (strcmp(dsplay, "alpha") != 0) waitc();
  }

/* Acquire working space. */
  for (request=System.sysReq; request; request=request->nxtReq) {
    if (request->outtyp == OT_DYN) break;
  }
  nfgc = System.nfgc;
  if (request) {
    if (nfgc <= 0) {
      textc("*** There are no FGC's to respond. ***", TRUE);
      textc("*** Transfer functions cannot be found. ***", TRUE);
      goto _1;
    }
  } else {
    goto _1;
  }
  nsq    = nfgc * nfgc;
  n2     = nfgc + nfgc;
  n3     = n2   + nfgc;
  M      = (real *) calloc(nsq,      sizeof(real));
  D      = (real *) calloc(nsq,      sizeof(real));
  K      = (real *) calloc(nsq,      sizeof(real));
  MDK    = (real *) calloc(nfgc*n3,  sizeof(real));
  Dyn    = (real *) calloc(n2*n2,    sizeof(real));
  wr     = (real *) calloc(n2,       sizeof(real));
  wi     = (real *) calloc(n2,       sizeof(real));
  G      = (real *) calloc(nfgc,     sizeof(real));
  Eigvct = (complex *) calloc(n2*n2, sizeof(complex));
  T      = (complex *) calloc(n3*n2, sizeof(complex));
  irow   = (int *)  calloc(nfgc,     sizeof(int));
  icol   = (int *)  calloc(n3,       sizeof(int));

/* Form the mass, stiffness, and damping force matrices. */
  massc(nfgc, M);
  cmatc(nfgc, D);
  kmatc(nfgc, K);

/* Save copies of the mass, damping, and stiffness matrices. */
  for (i=0; i<nfgc; i++) {
    for (j=0; j<nfgc; j++) {
      MDK[i*n3     +j] = M[i*nfgc+j];
      MDK[i*n3+nfgc+j] = D[i*nfgc+j];
      MDK[i*n3+n2  +j] = K[i*nfgc+j];
    }
  }

/* Invert the mass matrix. */
  invrtc(MDK, nfgc, n3, nfgc, System.dytol, &System.mrank, &detM, irow, 
    icol);
  if (System.mrank != nfgc) {
    textc("*** The mass matrix is singular. ***", TRUE);
    textc("*** Transfer functions cannot be found. ***", TRUE);
    goto _2;
  }

/* Form the normal modes. */
  for (i=0; i<nfgc; i++) {
    ii = nfgc + i;
    for (j=0; j<n2; j++) {
      Dyn[ii*n2+j] = 0.0;
    }
    Dyn[ii*n2+i] = 1.0;
  }
  for (i=0; i<nfgc; i++) {
    ii = irow[i];
    for (j=0; j<nfgc; j++) {
      Dyn[ii*n2     +j] = MDK[i*n3+nfgc+j];
      Dyn[ii*n2+nfgc+j] = MDK[i*n3+n2  +j];
    }
  }
  nerr = eigvec(Dyn, n2, wr, wi, Eigvct);
  if (nerr != 0) {
    textc("*** Normal modes cannot be found. ***", TRUE);
    goto _2;
  }
  mdmasc(M, D, Eigvct);

/* Sequence through the transfer function requests. */
  for (request=System.sysReq; request; request=request->nxtReq) {
    if (request->outtyp == OT_DYN) {
      switch (request->reqtyp) {
      case RQ_PRINT:
      case RQ_STORE:
        strcpy(kindin, request->items[0].data.text);
        strcpy(namein, request->items[1].data.text);
        nin = request->items[2].data.number;
        break;
      case RQ_LIST:
      case RQ_PLOT:
        w0   = request->items[0].data.word;
        wf   = request->items[1].data.word;
        winc = request->items[2].data.word;
        strcpy(kindin, request->items[3].data.text);
        strcpy(namein, request->items[4].data.text);
        nin  = request->items[5].data.number;
        break;
      default:
        continue;
      }

/* Form the generalized force input coefficients. */
      tforc(kindin, namein, nin, G);
      if (System.nerror != 0) {
        textc("*** Request ignored. ***", TRUE);
        System.nerror = 0;
        continue;
      }

/* Form the numerators for the generalized transfer functions. */
      tnumrc(Eigvct, G, T);

/* Output the requested transfer functions. */
      switch (request->reqtyp) {
      case RQ_PRINT:
        wrtfnc(T, wr, wi, kindin, namein, nin, &request->items[3], 
          request->nitems-3);
        break;
      case RQ_LIST:
        lstfnc(T, wr, wi, w0, wf, winc, kindin, namein, nin,
          &request->items[6], request->nitems-6);
        break;
      case RQ_PLOT:
        pltfnc(T, wr, wi, w0, wf, winc, kindin, namein, nin,
          &request->items[6], request->nitems-6);
        break;
      case RQ_STORE:
        sttfnc(T, wr, wi, kindin, namein, nin, &request->items[3], 
          request->nitems-3);
      }
    }
  }
_2:
  free(M);
  free(D);
  free(K);
  free(MDK);
  free(Dyn);
  free(wr);
  free(wi);
  free(G);
  free(Eigvct);
  free(T);
  free(irow);
  free(icol);
_1:
  return;
}
