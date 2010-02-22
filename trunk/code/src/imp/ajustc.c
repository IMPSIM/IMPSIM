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
/* ajustc-01 Jan 00:22 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Apply corrections to the joint variables as part of the itera-
|     tive loop closure.
|
|     Access:
|       ngoto = (int) ajustc(real Jinv[], real E[], int irow[],
|         int icol[], int irank);
|     real Jinv[],i-Inverse of the Jacobian matrix in the rearranged
|       order left by invrtc().
|     real E[],   i-column of error constants in original row order.
|     int irow[], i-Rearranged row numbers left by invrtc().
|     int icol[], i-Rearranged column numbers left by invrtc().
|     int irank,  i-Rank already found for the Jacobian matrix.
|     int ngoto,  o-Flag indicating the state on exit of convergence of
|                   the iteration process at the end of this iteration:
|       ngoto=1 if the system is closed;
|       ngoto=2 if the system is not yet closed, but is converging;
|       ngoto=3 if the iteration process is diverging;
|       ngoto=4 if iteration converged but loops are still not closed.
|       ngoto=5 if iteration converged but constraints are not met.
|
|     Error Conditions:
|       When ngoto == 3 is returned, System.nerror gives the number of
|     the last divergent joint variable found.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     23 Mar 03:JJU-Implemented iexprt expertise level flag.
*     12 Mar 09:JJU-Implemented Euler parametrs.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int ajustc(real Jinv[], real E[], int irow[], int icol[], int irank)
#else
  int ajustc(Jinv, E, irow, icol, irank)
  real Jinv[], E[];
  int  irow[], icol[], irank;
#endif
{
  extern int  iexprt;            /* Expected level of user expertise. */
  Joint *joint;
  Jvar  *jvar;
  char  *direc[6] = {"X", "Y", "Z", "YZ", "ZX", "XY"};
  char   string[64];
  int    i, ic, idir, j, ngoto, njvar;
  real   delta, test, tol;

/* Loop through the correction terms. */
  if (iexprt >= 5) {
    textc("Iteration ", FALSE);
    itextc(System.ci);
    textc(" data from ajustc:", TRUE);
  }
  ngoto = 1;
  for (i=0; i<irank; i++) {

/* Form the correction term value. */
    delta = 0.0;
    for (j=0; j<irank; j++) {
      delta += Jinv[i*System.njvars+j] * E[irow[j]];
    }

/* Test for convergence of a dependent joint variable. */
    njvar = icol[i];
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        if (jvar->jvrnoS == njvar) {
          if (jvar->jvrtyp == JV_LINEAR) {
            tol = System.ptoll;
            delta *= System.lscale;
          } else if (jvar->jvrtyp == JV_ANGULAR) {
            tol = System.ptola;
          } else {
            tol = System.ptoll;
          }
          test = fabs(delta);
          if (test > tol) ngoto = max(2, ngoto);

/* Test for divergence of a joint variable. */
          if (test > PI) {
            if (ngoto != 3) {
              textc("*** These joint variables diverged: ***", TRUE);
              ngoto = 3;
            }
            System.nerror = njvar;
            sprintf(string, "  joint %-4s,%2i delta = %12.3e", 
              joint->name,jvar->jvrnoJ+1, delta);
            textc(string, TRUE);

/* Add a joint variable correction. */
          } else {
            if (iexprt >= 5) {
              sprintf(string, "  joint %-4s,%2i delta = %12.3e", 
                joint->name, jvar->jvrnoJ+1, delta);
              textc(string, FALSE);
              if (test > tol) {
                textc(" > ", FALSE);
              } else {
                textc(" < ", FALSE);
              }
              sprintf(string,
               "tol=%12.3e, ngoto=%2i", tol, ngoto);
              textc(string, TRUE);
            }
            jvar->pos += delta;
          }
          break;
        }
      }
      if (jvar) break;
    }
  }

/* Once converged, test for closure of all loops and constraints. */
  if (ngoto <= 1) {
    for (i=irank; i<6*System.nloops+System.nc; i++) {
      delta = 0.0;
      for (j=0; j<irank; j++) {
        delta += Jinv[i*System.njvars+j] * E[irow[j]];
      }
      ic = irow[i] - 6 * System.nloops;
      if (ic < 0) {
        idir = irow[i] % 6;
        if (idir < 3) {
          tol = System.dtoll;
          if (tol < System.ptoll) tol = System.ptoll;
          delta *= System.lscale;
        } else {
          tol = System.dtola;
          if (tol < System.ptola) tol = System.ptola;
        }
        if (fabs(delta) > tol) {
          ngoto = 4;
          textc("*** Loop ", FALSE);
          itextc(irow[i] / 6 + 1);
          textc(" is inaccurate by ", FALSE);
          gtextc(delta);
          textc(" > ", FALSE);
          gtextc(tol);
          textc(" in the ", FALSE);
          textc(direc[idir], FALSE);
          textc(" direction. ***", TRUE);
        }
      } else {
        if (fabs(delta) > System.ptoll) {
          ngoto = 5;
          textc("*** Euler constraint ", FALSE);
          itextc(ic);
          textc(" is inaccurate by ", FALSE);
          gtextc(delta);
          textc(" > ", FALSE);
          gtextc(System.ptoll);
          textc(" ***", TRUE);
        }
      }
    }
  }
  return(ngoto);
}
