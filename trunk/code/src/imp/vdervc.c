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
/* vdervc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Calculate and store the virtual derivatives of the dependent
|     joint variables with respect to all possible virtual deformations
|     in a given joint.
|
|     Access:
|       (void) vdervc(Joint *joint);
|     Joint *joint,i-Pointer to the Joint record for the deformations.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If a particular deformation is not possible consistent with the
|     other constraints or generalized coordinates, then the virtual
|     derivatives are set to INDEF.  These signify statically indetermi-
|     nate directions and forces.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void vdervc(Joint *joint)
#else
  void vdervc(joint)
  Joint *joint;
#endif
{
  int   i, n, nogo, nrows;
  real *dphi, D[6], *rhs;

/* Initialize. */
textc("vdervc 39:", TRUE);
  if (System.level < 7) abortc();
  if (System.pd) {
    for (i=0; i<System.ndep; i++) {
      free (System.pd[i]);
    }
    free (System.pd);
  }
  System.pd = (real **) calloc(System.ndep, sizeof(real *));
  for (i=0; i<System.ndep; i++) {
    System.pd[i] = (real *) calloc(6, sizeof(real));
  }
  nrows = 6 * System.nloops + System.nc;
  rhs   = (real *) calloc(nrows,       sizeof(real));
  dphi  = (real *) calloc(System.ndep, sizeof(real));

/* Sequence through all deformations. */
  for (n=0; n<6; n++) {
    for (i=0; i<6; i++) D[i] = 0.0;
    D[(n+3)%6] = -1.0;
    xdxinc(joint->jntAxB->S, D, D);
    xdxinc(joint->jntAxB->axsBdy->T0j, D, D);

/* Form the right-hand side vector for this deformation. */
    if (System.ndep > 0) {
      for (i=0; i<nrows; i++) rhs[i] = 0.0;
      fillc(joint->loopflags, D, 1, rhs);

/* Solve for and store the virtual derivatives. */
      nogo = dsolvc(System.sysJ, rhs, System.fintol, dphi);
      if (nogo) {
        for (i=0; i<System.ndep; i++) {
          ldnanc((void *) &System.pd[i][n]);
        }
      } else {
        for (i=0; i<System.ndep; i++) {
          System.pd[i][n] = dphi[i];
        }
      }
    }
  }
  free (rhs);
  free (dphi);
  return;
}
