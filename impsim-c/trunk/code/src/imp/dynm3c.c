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
/* dynm3c-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set up for taking the dynamic mode time step.
|
|     Access:
|       nerr = (int) dynm3c(real t, complex *Eigvct, complex *W, 
|                     real *MDKG, int nblock, int *bloksz, int *icol);
|     real    t,             i-Time.
|     complex Eigvct[2*nfgc,2*nfgc],i-Matrix of eigen/principal vectors. 
|     complex W[2*nfgc],     i-Eigenvalues.
|     real    MDKG[],        i-Matrix of [M-1|M-1D|M-1K|M-1G].
|     int     nblock,        i-Number of blocks of multiple eigenvalues.
|     int     bloksz[],      i-Sizes of multiple eigenvalue blocks.
|     int     icol[3*nfgc+1],i-Column numbering of MDKG from invrtc().
|     int     nerr,          o-Flag signalling error if nonzero.
|
|     Error Conditions:
|       If the matrix of eigenvectors is singular, return is made with
|     nerr = TRUE (nonzero); a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int dynm3c(real t, complex Eigvct[], complex W[], real MDKG[], 
    int nblock, int bloksz[], int icol[])
#else
  int dynm3c(t, Eigvct, W, MDKG, nblock, bloksz, icol)
  real    t;
  complex Eigvec[], W[];
  real    MDKG[];
  int     nblock, bloksz[], icol[];
#endif
{
  complex *B, *C, *dHp, eWt, *F, *Hp, lamdak, temp, temp2, temp3, *X;
  int     i, index, index0, j, k, nerr, nfgc, nkol, nsquar, n2;
  real    *f, factor, factrl, sum1, sum2, sum3, *x; 
  Joint   *joint;
  Jvar    *jvar;

  nerr   = FALSE;
  nfgc   = System.nfgc;
  n2     = nfgc + nfgc;
  nkol   = n2 + nfgc + 1;
  nsquar = n2 * n2;
  B    = (complex *) calloc (n2+n2,  sizeof(complex));
  C    = (complex *) calloc (nsquar, sizeof(complex));
  dHp  = (complex *) calloc (n2,     sizeof(complex));
  F    = (complex *) calloc (n2,     sizeof(complex));
  Hp   = (complex *) calloc (n2,     sizeof(complex));
  X    = (complex *) calloc (n2,     sizeof(complex));
  f    = (real *)    calloc (n2,     sizeof(real));
  x    = (real *)    calloc (n2,     sizeof(real));
  for(i=0; i<nfgc; i++) {
    x[i]       = 0.0;
    x[i+nfgc]  = 0.0;     
    f[icol[i]] = -MDKG[i*nkol+n2+nfgc];  /* Minus sign from invrtc(). */
    f[i+nfgc]  = 0.0;
  }
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      i = jvar->jvrnoS - System.ndep;
      if ((i >= 0) && (i < nfgc)) {
        x[i] = jvar->vel;                             /* Set up {x0}. */
      }
    }
  }
  for (i=0; i<n2; i++) {   
    for(j=0; j<n2; j++) {
      k = n2 * i + j;
      C[k].r = Eigvct[k].r;       /* Copy complex eigenvector matrix. */
      C[k].i = Eigvct[k].i;
    }
    B[2*i].r   = x[i];                                 /* Set up rhs. */
    B[2*i].i   = 0.0;
    B[2*i+1].r = f[i];
    B[2*i+1].i = 0.0; 
    dHp[i].r   = 0.0;
    dHp[i].i   = 0.0;
    Hp[i].r    = 0.0;
    Hp[i].i    = 0.0;
  }

/* Solve [C]{B'} = {B} */
  nerr = cgausc(C, n2, B, 2);
  if (nerr) {
    echoc();
    textc("*** Eigenvector matrix is singular. ***", TRUE);
    goto DONE;
  }
  for(i=0; i<n2; i++) {
    X[i].r = B[2*i].r; 
    X[i].i = B[2*i].i; 
    F[i].r = B[2*i+1].r; 
    F[i].i = B[2*i+1].i; 
  }
  for (i=0; i<nblock; i++) {                     /* Calculate [H]{x}. */
    index0 = (i==0) ? 0 : index0 + bloksz[i-1];
    temp3.r = W[index0].r * t;
    temp3.i = W[index0].i * t;
    eWt = cexpc(temp3);                                    /* exp(Wt) */
    for (j=0,index=index0; j<bloksz[i]; j++,index++) {
      temp.r = 0.0;
      temp.i = 0.0;
      for (k= 0; k<bloksz[i]; k++) { 
        factrl = (k==0) ? 1 : factrl * k;
        factor = pow(t, k) / factrl;                      /* t^k/(k)! */
        temp.r += X[index+k].r * factor;           
        temp.i += X[index+k].i * factor;
      }
      Hp[index] = cmultc(eWt, temp);
    }

/* Calculate [H**]{f}. */
    if (cabsc(W[index0]) > System.zero) {                   /* W != 0 */

/* Calculate [J-1]{f}. */
      for (j=0,index=index0; j<bloksz[i]; j++,index++) {
        temp.r = 0.0;
        temp.i = 0.0;
        lamdak.r = -1.0;          
        lamdak.i =  0.0;
        for (k=0; k<bloksz[i]; k++) {
          temp3.r = -W[index0].r;
          temp3.i = -W[index0].i;
          lamdak  = cdivc(lamdak, temp3);           /* (-1)^k/(W^k+1) */
          temp2   = cmultc(lamdak, F[index+k]);
          temp.r += temp2.r; 
          temp.i += temp2.i;
        } 
        F[index].r = temp.r;                   /* {f}(now) = [J-1]{f} */
        F[index].i = temp.i;
      }

/* Calculate [H-I][J-1]{f}. */
      temp3.r = W[index0].r * t;
      temp3.i = W[index0].i * t;
      eWt = cexpc(temp3);                                  /* exp(Wt) */
      for (j=0,index=index0; j<bloksz[i]; j++,index++) {
        temp.r = 0.0;
        temp.i = 0.0;
        for (k=0; k<bloksz[i]; k++) {
          factrl = (k==0) ? 1 : factrl * k;
          factor = pow(t, k) / factrl;                    /* t^k/(k)! */
          temp2.r = eWt.r * factor;     
          temp2.i = eWt.i * factor;                              /* H */
          if (k==0)  temp2.r -= 1.0;                         /* H - I */
          temp2 = cmultc(temp2, F[index+k]);
          temp.r += temp2.r;        
          temp.i += temp2.i;        
        } 
        Hp[index].r += temp.r;            
        Hp[index].i += temp.i;
      }      

/* Calculate [H*]{f}. */
    } else {                                          /* lamda == 0.0 */
      for (j=0,index=index0; j<bloksz[i]; j++,index++) {
        temp.r = 0.0;
        temp.i = 0.0;
        for (k=0; k<bloksz[i]; k++) {
          factrl = (k==0) ? 1 : factrl * (k + 1);
          factor = pow(t, k + 1) / factrl;
          temp.r += factor * F[index+k].r;
          temp.i += factor * F[index+k].i;
        } 
        Hp[index].r += temp.r;
        Hp[index].i += temp.i;
      }      
    }
  
/* Calculate d[H]{x}. */
    temp3.r = W[index0].r * t;
    temp3.i = W[index0].i * t;
    eWt = cexpc(temp3);                                    /* exp(Wt) */
    for (j=0,index=index0; j<bloksz[i]; j++,index++) {
      temp.r = 0.0;
      temp.i = 0.0;
      for (k= 0; k<bloksz[i]; k++) { 
        factrl = (k==0) ? 1 : factrl * k;
        temp2.r = W[index0].r * pow(t, k) / factrl;
        temp2.i = W[index0].i * pow(t, k) / factrl;
        if (k != 0) temp2.r += pow(t, k - 1) / factrl / k;
        temp2 = cmultc(temp2, X[index+k]);
        temp.r +=  temp2.r;           
        temp.i +=  temp2.i;
      }
      dHp[index] = cmultc(eWt, temp);
    }

/* Calculate d[H**]{f}. */
    if (cabsc(W[index0]) > System.zero) {                 /* W != 0.0 */

/* Calculate d[H][J-1]{f}. */
      temp3.r = W[index0].r * t;
      temp3.i = W[index0].i * t;
      eWt = cexpc(temp3);                                  /* exp(Wt) */
      for (j=0,index=index0; j<bloksz[i]; j++,index++) {
        temp.r = 0.0;
        temp.i = 0.0;
        for (k=0; k<bloksz[i]; k++) { 
          factrl = (k==0) ? 1 : factrl * k;
          temp2.r = W[index0].r * pow(t, k) / factrl;
          temp2.i = W[index0].i * pow(t, k) / factrl;
          if (k != 0) temp2.r += pow(t, k - 1) / factrl / k;
          temp2   = cmultc(temp2, F[index+k]);
          temp.r +=  temp2.r;           
          temp.i +=  temp2.i;
        }
        temp2 = cmultc(eWt, temp);
        dHp[index].r += temp2.r;
        dHp[index].i += temp2.i;
      }
    } else {                                          /* lamda == 0.0 */

/* Calculate d[H*]{f}. */
      for (j=0,index=index0; j<bloksz[i]; j++,index++) {
        temp.r = 0.0;
        temp.i = 0.0;
        for (k=0; k<bloksz[i]; k++) {
          factrl = (k==0) ? 1 : factrl * k;
          factor = pow(t, k) / factrl;
          temp.r += factor * F[index+k].r;
          temp.i += factor * F[index+k].i;
        } 
        dHp[index].r += temp.r;
        dHp[index].i += temp.i;
      }      
    }
  }

/* Calculate {dx.., dx., and  dx}. */
  for (i=0; i<nfgc; i++) {
    k = nfgc + i;
    sum1 = 0.0;
    for (j=0; j<n2; j++) {
      temp = cmultc(Eigvct[k*n2+j], Hp[j]);
      sum1 += temp.r;
    }
    sum2 = 0.0;
    for (j=0; j<n2; j++) {
      temp = cmultc(Eigvct[i*n2+j], Hp[j]);
      sum2 += temp.r;
    }
    sum3 = 0.0;
    for (j=0; j<n2; j++) {
      temp = cmultc(Eigvct[i*n2+j], dHp[j]);
      sum3 += temp.r;
    }
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrnoS == System.ndep + i) {
          jvar->pos += sum1;
          jvar->vel  = sum2;
          jvar->acc  = sum3;
/*  printf("new pos = %g\n", jvar->pos);
    printf("new vel = %g\n", jvar->vel);
    printf("new acc = %g\n", jvar->acc);*/
        }
      }
    }
  }
DONE:
  free(B);   
  free(C);
  free(dHp); 
  free(F);
  free(Hp);   
  free(X);    
  free(f);
  free(x);     
  return(nerr);
}
