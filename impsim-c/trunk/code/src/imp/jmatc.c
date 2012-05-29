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
/* jmatc-01 Jan 00:09 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the system Jacobian matrix.
|
|     Access:
|       (void) jmatc(int nrows, int ncols, real J[], int irow[],
|         int icol[]);
|     int nrows,i-Number of rows in J[] (= 6*System.nloops + System.nc).
|     int ncols,i-Number of columns in J[] (= System.njvars).
|     real J[],o-System Jacobian matrix.
|     int irow[],o-Initial row numbers for J[].
|     int icol[],o-Initial column numbers for J[].
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The entries of this 2-D matrix are stored in a single array.
|     They are stored in row major (C) order rather than column major
|     (FORTRAN) order.
*
*     History:
*     01 Jan 00:JJU-Original.
*     09 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void jmatc(int nrows, int ncols, real *J, int *irow, int *icol)
#else
  void jmatc(nrows, ncols, J, irow, icol)
  int   nrows, ncols;
  real *J;
  int  *irow, *icol;
#endif
{
  Joint *joint;
  Jvar  *jvar;
  int    i, ic;

/* Loop through all joint variable records. */
  ic = 6 * System.nloops;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {

/* Fill the column for this joint variable. */
      for (i=0; i<nrows; i++) {
        J[i*ncols+jvar->jvrnoS] = 0.0;
      }
      fillc(joint->loopflags, jvar->D, ncols, &J[jvar->jvrnoS]);

/* Fill constraint equation for Euler parameters as needed. */
      switch (joint->jtype) {
      case OPEN:
        if (jvar->jvrnoJ < 3) break;
      case SPHERE:
        J[ic*ncols+jvar->jvrnoS] += 2.0 * jvar->pos;
      }
    }

/* Increment count of constraint equations. */
    switch (joint->jtype) {
    case OPEN:            
    case SPHERE:
      ic++;
    }
  }
  return;
}
