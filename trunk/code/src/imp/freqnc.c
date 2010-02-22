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
/* freqnc-01 Jan 00:22 Mar 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Compute and print the dynamic characteristics of the system.
|
|     Access:
|       void freqnc()
|
|     Error Conditions:
|       If there are no FGC's to respond, then no natural frequencies
|     can be found; a message is printed.
|       If the mass matrix is singular, then only a reduced number of
|     natural frequencies can be found; a message is printed.
|
|     Comments:
|       The number of eigenvalues is equal to twice the number of FGC's;
|     there are this many natural frequency pairs.
*
*     History:
*     01 Jan 00:JJU-Original.
*     22 Mar 03:JJU-Implemented use of itextc function.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
  void freqnc()
{
  char string[16];
  int  i, *irow, *icol, j, nfsq, nf2, nf3, nogo;
  real detm, *Dyn, *matrix, *MDKG, omegad, omegan, *wr, *wi, zeta;

/* Print headings. */
  textc("", TRUE);
  textc("Dynamic Characteristics:", TRUE);
  textc("                    Natural        Damping", FALSE);
  textc("         Damped          Decay", TRUE);
  textc("                  Frequency          Ratio", FALSE);
  textc("      Frequency           Rate", TRUE);
  textc("                    rad/sec            ---", FALSE);
  textc("        rad/sec          1/sec", TRUE);

/* Test for no free FGC's. */
  if (System.nfgc <= 0) {
    textc("*** Error:  There are no FGC's defined. ***", TRUE);
    return;
  }

/* Acquire working space. */
  nf2  = System.nfgc + System.nfgc;
  nf3  = System.nfgc + nf2 + 1;
  nfsq = System.nfgc * System.nfgc;
  free (matrix);
  matrix = (real *) calloc(nfsq, sizeof(real));
  free (MDKG);
  MDKG = (real *) calloc(nf3 * System.nfgc, sizeof(real));
  free (Dyn);
  Dyn = (real *) calloc(nf2 * nf2, sizeof(real));
  free (irow);
  irow = (int *) calloc(System.nfgc, sizeof(int));
  free (icol);
  icol = (int *) calloc(nf3, sizeof(int));
  free (wr);
  wr = (real *) calloc(nf2, sizeof(real));
  free (wi);
  wi = (real *) calloc(nf2, sizeof(real));

/* Form the mass, damping, and stiffness matrices. */
  massc(System.nfgc, matrix);
  for (i=0; i<System.nfgc; i++) {
    for (j=0; j<System.nfgc; j++) {
      MDKG[i*nf3+j] = matrix[i*System.nfgc+j];
    }
  }
  cmatc(System.nfgc, matrix);
  for (i=0; i<System.nfgc; i++) {
    for (j=0; j<System.nfgc; j++) {
      MDKG[i*nf3+System.nfgc+j] = matrix[i*System.nfgc+j];
    }
  }
  kmatc(System.nfgc, matrix);
  for (i=0; i<System.nfgc; i++) {
    for (j=0; j<System.nfgc; j++) {
      MDKG[i*nf3+nf2+j] = matrix[i*System.nfgc+j];
    }
  }

/* Find the eigenvalues of the system. */
  invrtc(MDKG, System.nfgc, nf3, System.nfgc, System.dytol,
    &System.mrank, &detm, irow, icol);
  if (System.mrank != System.nfgc) {
    textc("*** Error:  The mass matrix is singular. ***", TRUE);
    textc("*** Only ", FALSE);
    itextc(System.mrank);
    textc(" FGC's exhibit inertia. ***", TRUE);
  } else {
    dynm5c(System.nfgc, MDKG, icol, Dyn);
    nogo = eigvlc(Dyn, nf2, wr, wi);
    if (nogo) {
      textc("*** Error: ", FALSE);
      itextc(nogo);
      textc(" eigenvalues were not found. ***", TRUE);
    }

/* Print results. */
    for (i=nogo; i<nf2; i++) {
      if (wi[i] > 0.0) {
        omegad = wi[i];
        omegan = sqrt(wr[i] * wr[i] + wi[i] * wi[i]);
        zeta   = -wr[i] / omegan;
        textc("            ", FALSE);
        sprintf(string, "%#15.4f", omegan);
        textc(string, FALSE);
        sprintf(string, "%#15.4f", zeta);
        textc(string, FALSE);
        sprintf(string, "%#15.4f", omegad);
        textc(string, FALSE);
        sprintf(string, "%#15.4f", wr[i]);
        textc(string, TRUE);
      } else if (wi[i] == 0.0) {
        textc(
          "                                                         ",
          FALSE);
        sprintf(string, "%#15.4f", wr[i]);
        textc(string, TRUE);
      }
    }
  }
  free (matrix);
  free (MDKG);
  free (Dyn);
  free (irow);
  free (icol);
  free (wr);
  free (wi);
  return;
}
