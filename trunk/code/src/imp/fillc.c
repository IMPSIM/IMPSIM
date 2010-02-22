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
/* fillc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Add the contribution of a given derivative operator to the
|     proper rows of a column of a matrix per the loop indicating
|     marker.
|
|     Access:
|       (void) fillc(long loopflags, real dmat[6], int ncols,
|         real matrix[]);
|     long loopflags,i-Packed bits representing loops to be filled.
|     real dmat[6],  i-The derivative operator used for this filling.
|     int  ncols,    i-The number of columns in matrix[].
|     real matrix[], i/o-The columns of the matrix.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine only adds the contribution of dmat[6] to the proper
|     elements of the first column of matrix[].  It expects the matrix[]
|     to be initialized before entry and this routine to be called with
|     a pointer to the top of the correct column of matrix[].
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void fillc(long loopflags, real dmat[6], int ncols, real matrix[])
#else
  void fillc(loopflags, dmat, ncols, matrix)
  long loopflags;
  real dmat[6];
  int  ncols;
  real matrix[];
#endif
{
  int  i, nrow;
  long mark;

  nrow = 0;
  mark = loopflags;
  while (mark != 0) {
    if ((mark % 2) > 0) {
      for (i=0; i<6; i++) {
        matrix[(nrow+i)*ncols] += dmat[i];
      }
    }
    nrow += 6;
    mark /= 2;
  }
  return;
}
