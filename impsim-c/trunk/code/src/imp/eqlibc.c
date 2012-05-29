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
/* eqlibc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Search for a position of stable static equilibrium.
|
|     Access:
|       (void) eqlibc();
|
|     Error Conditions:
|       System.nerror = 10 indicates that the equilibrium search failed.
|
|     Comments:
|       A warning message is printed if any of the free generalized
|     coordinates are found to be in neutral equilibrium.
|       System.level = 7 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     22 Mar 03:JJU-Implemented use of itextc function.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void eqlibc()
{
  int   i, *icol, *irow, j, kcol, lflag, negc;
  real *G, *K, kdet, *KinvG;

/* Acquire working space. */
  System.ei = 0;
_3:
  negc  = System.nfree - System.ndep;
  kcol  = System.nfgc + 1;
  K     = (real *) calloc(System.nfgc*System.nfgc, sizeof(real));
  G     = (real *) calloc(System.nfgc,             sizeof(real));
  KinvG = (real *) calloc(System.nfgc*kcol,        sizeof(real));
  irow  = (int *)  calloc(System.nfgc,             sizeof(int));
  icol  = (int *)  calloc(kcol,                    sizeof(int));

/* Form the stiffness matrix. */
_4:
  System.ei++;
  ksetc();
  if (System.nerror == 0) {
    kmatc(System.nfgc, K);

/* Form the generalized unbalanced forces. */
    fsetc();
    if (System.nerror == 0) {
      gforc(System.nfgc, G);

/* Form the augmented matrix [K|G] for invrtc. */
      for (i=0; i<System.nfgc; i++) {
        for (j=0; j<System.nfgc; j++) {
          KinvG[i*kcol+j] = K[i*System.nfgc+j];
        }
        KinvG[i*kcol+System.nfgc] = G[i];
      }

/* Form the corrections to the generalized coordinates. */
      invrtc(KinvG, System.nfgc, kcol, negc, System.fktol, 
        &System.krank, &kdet, irow, icol);
      System.krank = max(0, System.krank);

/* Add corrections to the joint variables. */
      lflag = eqjstc(System.nfgc, KinvG, G, icol);

/* Assemble the mechanism at the new position. */
      closec();
      if (System.nerror == 0) {
        if (!lflag) {
          if (System.nfgc != negc) {
            if (K)     free (K);
            if (G)     free (G);
            if (KinvG) free (KinvG);
            if (irow)  free (irow);
            if (icol)  free (icol);
            goto _3;
          }
          if (System.ei < System.en) goto _4;
          textc("*** Static equilibrium not found after ", FALSE);
          itextc(System.ei);
          textc(" steps. ***", TRUE);
          System.nerror = 10;
        }
      }
      if (System.krank < System.nfgc) {
        textc("*** Warning:  ", FALSE);
        itextc(System.nfgc - System.krank);
        textc(" FGC's are in neutral equilibrium. ***", TRUE);
      }
    }
  }

/* Free working space. */
  if (K)     free (K);
  if (G)     free (G);
  if (KinvG) free (KinvG);
  if (irow)  free (irow);
  if (icol)  free (icol);
  return;
}
