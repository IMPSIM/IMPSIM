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
/* imvelc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine adjusted FGC velocities resulting from an impact at a 
|     specified contact.
|
|     Access:
|       (void) imvelc(Contact *cntact, enum Imptyp tangmode, 
|         enum Imptyp mommode, enum Imptyp torsmode, real *fgcvel);
|     Contact     *cntact, i-Contact record specified for impact.
|     enum Imptyp tangmode,i-Flag for type of tangential impulse model.
|     enum Imptyp mommode, i-Flag for type of moment     impulse model.
|     enum Imptyp torsmode,i-Flag for type of torsional  impulse model.
|     real        fgcvel[],o-Calculated set of new FGC velocities.
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
 
#include "libimp.h"
#ifdef ANSI
  void imvelc(Contact *cntact, enum Imptyp tangmode, 
    enum Imptyp mommode, enum Imptyp torsmode, real *fgcvel)
#else
  void imvelc(cntact, tangmode, mommode, torsmode, fgcvel)
  Contact     *cntact;
  enum Imptyp tangmode, mommode, torsmode;
  real        *fgcvel;
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, *icol, irank, *irow, j, nfgc, nkols, nrows;
  real  *A, *B, C[3], D[3], det, *phivel, sum[3], *tmp, WA[6], WB[6], 
	  WBA[6];

/* Acquire working space. */
  nfgc   = System.nfgc;
  nrows  = nfgc + 5;
  nkols  = nfgc + 6;
  A      = (real *) calloc(nrows * nkols, sizeof(real));
  irow   = (int *)  calloc(nrows,         sizeof(int));
  icol   = (int *)  calloc(nkols,         sizeof(int));
  B      = (real *) calloc(nrows * nfgc,  sizeof(real));
  phivel = (real *) calloc(System.ndof,   sizeof(real));
  tmp    = (real *) calloc(nfgc+5,        sizeof (real));

/* Initialize A[,]. */
  for (i=0; i<nrows; i++) {
    for (j=0; j<nkols; j++) {
      A[i*nkols+j] = 0.0;
    }
  }

/* Fill in the A[,] and B[,] matrices. */
  massc(nfgc, B);
  for (i=0; i<nfgc; i++) {
    for (j=0; j<nfgc; j++) {
      A[i*nkols+j] = B[i*nfgc+j];
    }
  }

/* Collect starting FGC and SGC velocities. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      i = jvar->jvrnoS - System.ndep;
      if (i >= 0) phivel[i] = jvar->vel;
    }
  }

/* Find the C[] and D[] vectors. */
  for (i=0; i<nfgc; i++) {
    wmatc(cntact->cnSldA->sldBdy, i, WA);
    wmatc(cntact->cnSldB->sldBdy, i, WB);
    for (j=0; j<6; j++) {
      WBA[j] = WB[j] - WA[j];
    }
    mpydrc(WBA, cntact->cnpoint, C);
    D[0] = cntact->cnSldB->sldBdy->T0j[1][1] * WB[0]
         - cntact->cnSldB->sldBdy->T0j[0][1] * WB[1]
         - cntact->cnSldA->sldBdy->T0j[1][1] * WA[0]
         + cntact->cnSldA->sldBdy->T0j[0][1] * WA[1];
    D[1] = cntact->cnSldB->sldBdy->T0j[2][2] * WB[1]
         - cntact->cnSldB->sldBdy->T0j[1][2] * WB[2]
         - cntact->cnSldA->sldBdy->T0j[2][2] * WA[1]
         + cntact->cnSldA->sldBdy->T0j[1][2] * WA[2];
    D[2] = cntact->cnSldB->sldBdy->T0j[0][0] * WB[2]
         - cntact->cnSldB->sldBdy->T0j[2][0] * WB[0]
         - cntact->cnSldA->sldBdy->T0j[0][0] * WA[2]
         + cntact->cnSldA->sldBdy->T0j[2][0] * WA[0];

/* Entries for normal impulse. */
    A[nfgc*nkols+i] = A[i*nkols+nfgc] = vdotc(3, C, cntact->cnnormal);
    B[nfgc*nfgc+i] = -A[i*nkols+nfgc] * cntact->rest_n;

/* Entries for tangential impulse. */
    if (tangmode) {
      A[i*nkols+nfgc+1] = vdotc(3, C, cntact->cntangnt);
    }
    if (tangmode == IM_FRIC) {
      A[(nfgc+1)*nkols+i] = B[(nfgc+1)*nfgc+i] = 0.0;
    } else if (tangmode == IM_REST) {
      A[(nfgc+1)*nkols+i] = A[i*nkols+nfgc+1];
      B[(nfgc+1)*nfgc+i] = -A[i*nkols+nfgc+1] * cntact->rest_t;
    }

/* Entries for moment impulse. */
    if (mommode) {
      A[(nfgc+2)*nkols+i] = A[i*nkols+nfgc+2] 
                          = vdotc(3, D, cntact->cntangnt);
      B[(nfgc+2)*nkols+i] = -A[i*nkols+nfgc+2] * cntact->rest_m;
      A[(nfgc+3)*nkols+i] = A[i*nkols+nfgc+3] 
                          = vdotc(3, D, cntact->cnbinorm);
      B[(nfgc+3)*nkols+i] = -A[i*nkols+nfgc+3] * cntact->rest_m;
    }

/* Entries for torsional impulse. */
    if (torsmode) {
      A[i*nkols+nfgc+4] = vdotc(3, D, cntact->cnnormal);
    }
    if (torsmode == IM_FRIC) {
      A[(nfgc+4)*nkols+i] = B[(nfgc+4)*nfgc+i] = 0.0;
    } else if (tangmode == IM_REST) {
      A[(nfgc+4)*nkols+i] = A[i*nkols+nfgc+4];
      B[(nfgc+4)*nfgc+i] = -A[i*nkols+nfgc+4] * cntact->rest_mn;
    }
  }

/* Fill in A22 submatrix. */
  if (tangmode == IM_FRIC) {
    A[(nfgc+1)*nkols+nfgc+1] = 1.0;
    A[(nfgc+1)*nkols+nfgc]   = -cntact->mu;
  }
  if (torsmode == IM_FRIC) {
    A[(nfgc+4)*nkols+nfgc+4] = 1.0;
    for (i=0; i<3; i++) sum[i] = 0.0;
    for (i=0; i<System.ndof; i++) {
      wmatc(cntact->cnSldA->sldBdy, i, WA);
      wmatc(cntact->cnSldB->sldBdy, i, WB);
      for (j=0; j<6; j++) {
	WBA[j] = WB[j] - WA[j];
      }
      mpydrc(WBA, cntact->cnpoint, C);
      D[0] = cntact->cnSldB->sldBdy->T0j[1][1] * WB[0]
           - cntact->cnSldB->sldBdy->T0j[0][1] * WB[1]
           - cntact->cnSldA->sldBdy->T0j[1][1] * WA[0]
           + cntact->cnSldA->sldBdy->T0j[0][1] * WA[1];
      D[1] = cntact->cnSldB->sldBdy->T0j[2][2] * WB[1]
           - cntact->cnSldB->sldBdy->T0j[1][2] * WB[2]
           - cntact->cnSldA->sldBdy->T0j[2][2] * WA[1]
           + cntact->cnSldA->sldBdy->T0j[1][2] * WA[2];
      D[2] = cntact->cnSldB->sldBdy->T0j[0][0] * WB[2]
           - cntact->cnSldB->sldBdy->T0j[2][0] * WB[0]
           - cntact->cnSldA->sldBdy->T0j[0][0] * WA[2]
           + cntact->cnSldA->sldBdy->T0j[2][0] * WA[0];
      for (j=0; j<3; j++) sum[j] += D[j] * phivel[i];
    }
    if (vdotc(3, sum, cntact->cnnormal) < 0.0) {
      A[(nfgc+4)*nkols+nfgc] = - cntact->mu * cntact->Rp;
    } else {
      A[(nfgc+4)*nkols+nfgc] =   cntact->mu * cntact->Rp;
    }
  }

/* Set up the right hand side of the equations. */
  for (i=0; i<nfgc+5; i++) {
    for (j=0; j<nfgc; j++) {
      A[i*nkols+nfgc+5] -= B[i*nfgc+j] * phivel[j];
    }
  }

/* Add the effects of SGC's. */
  for (i=nfgc; i<System.ndof; i++) {
    wmatc(cntact->cnSldA->sldBdy, i, WA);
    wmatc(cntact->cnSldB->sldBdy, i, WB);
    for (j=0; j<6; j++) {
      WBA[j] = WB[j] - WA[j];
    }
    mpydrc(WBA, cntact->cnpoint, C);
    D[0] = cntact->cnSldB->sldBdy->T0j[1][1] * WB[0]
         - cntact->cnSldB->sldBdy->T0j[0][1] * WB[1]
         - cntact->cnSldA->sldBdy->T0j[1][1] * WA[0]
         + cntact->cnSldA->sldBdy->T0j[0][1] * WA[1];
    D[1] = cntact->cnSldB->sldBdy->T0j[2][2] * WB[1]
         - cntact->cnSldB->sldBdy->T0j[1][2] * WB[2]
         - cntact->cnSldA->sldBdy->T0j[2][2] * WA[1]
         + cntact->cnSldA->sldBdy->T0j[1][2] * WA[2];
    D[2] = cntact->cnSldB->sldBdy->T0j[0][0] * WB[2]
         - cntact->cnSldB->sldBdy->T0j[2][0] * WB[0]
         - cntact->cnSldA->sldBdy->T0j[0][0] * WA[2]
         + cntact->cnSldA->sldBdy->T0j[2][0] * WA[0];
    A[nfgc*nkols+nfgc+5] += (cntact->rest_n + 1.0) 
      * vdotc(3, C, cntact->cnnormal) * phivel[i];
    if (tangmode == IM_REST) {
      A[(nfgc+1)*nkols+nfgc+5] += (cntact->rest_t + 1.0)
        * vdotc(3, C, cntact->cntangnt) * phivel[i];
    }
    if (mommode) {
      A[(nfgc+2)*nkols+nfgc+5] += (cntact->rest_m + 1.0)
        * vdotc(3, D, cntact->cntangnt) * phivel[i];
      A[(nfgc+3)*nkols+nfgc+5] += (cntact->rest_m + 1.0)
        * vdotc(3, D, cntact->cnbinorm) * phivel[i];
    }
    if (torsmode == IM_REST) {
      A[(nfgc+4)*nkols+nfgc+5] += (cntact->rest_mn + 1.0)
        * vdotc(3, D, cntact->cnnormal) * phivel[i];
    }
  }
  for (i=0; i<nfgc+5; i++) tmp[i] = -A[i*nkols+nfgc+5];

/* Solve the equations using invrtc(). */
  invrtc(A, nfgc+5, nfgc+6, nfgc+5, 0.000001, &irank, &det, irow, icol);

/* Find the modified FGC velocities. */
  for (i=0; i<irank; i++) {
    fgcvel[icol[i]] = 0.0;
    for (j=0; j<irank; j++) {
      fgcvel[icol[i]] += A[i*nkols+j] * tmp[irow[j]];
    }
  }
  free (tmp);
  free (phivel);
  free (B);
  free (A);
  free (irow);
  free (icol);
  return;
}
