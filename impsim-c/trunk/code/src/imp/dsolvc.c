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
/* dsolvc-01 Jan 00:10 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Solve for a set of derivatives of the dependent joint variables
|     using an already calculated Jacobian inverse and column of
|     constants.
|
|     Access:
|       nogo = (int) dsolvc(real Jinv[], real c[], real tol, real dq[]);
|     real Jinv[6*nloops,njvars],i-Precalculated inverse Jacobian.
|     real c[6*nloops+nc],i-Precalculated column of constants.
|     real tol,           i-Tolerance for trivial equation tests.
|     real dq[ndep],      o-Resulting joint variable derivatives.
|     int  nogo,          o-Integer flag set TRUE for error in solution.
|
|     Error Conditions:
|       Any redundant (cross-check) equations must be satisfied within
|     the tolerance tol or the nogo error flag is returned as TRUE, 
|     signalling indeterminate derivatives.  These occur when otherwise
|     trivial equations are not balanced between their right- and left-
|     hand sides.
|
|     Comments:
|       Note that Jinv[] is stored in a singly dimensioned array in row-
|     major (C) order.  Also, it is stored in the rearranged order left
|     by the invrtc() function.  The jvar records have been renumbered
|     to reflect this new order, and the original row numbers are stored
|     in column ndep+1 of Jinv[], i.e., Jinv[i,ndep].
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int dsolvc(real Jinv[], real c[], real tol, real dq[])
#else
  int dsolvc(Jinv, c, tol, dq)
  real Jinv[], c[], tol, dq[];
#endif
{
  int  i, j, k, nogo, nrows;
  real save;

  nogo = FALSE;
  nrows = 6 * System.nloops + System.nc;
  for (i=0; i<nrows; i++) {
    save = 0.0;
    for (j=0; j<System.ndep; j++) {
      k = nint(Jinv[j * System.njvars + System.ndep]);
      save += Jinv[i * System.njvars + j] * c[k];
    }
    if (i < System.ndep) {
      dq[i] = save;
    } else {
      k = nint(Jinv[i * System.njvars + System.ndep]);
      save += c[k];
      if (fabs(save) > tol) {
gtextc(save);
gtextc(tol);
textc("dsolvc 62:", TRUE);
        nogo = TRUE;
      }
    }
  }
  return(nogo);
}
