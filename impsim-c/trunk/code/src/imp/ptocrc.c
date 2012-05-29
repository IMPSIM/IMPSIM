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
/* ptocrc-01 Jan 00:16 Feb 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Test a specified set of point coordinates and add to the set 
|     already stored in a Contact Region if the new point unique.
|
|     Access:
|       lflag = (int) ptocrc(real pnt[3], real ptcrc[][3], int *nptcrc);
|     real  pnt[3],      i-Point coordinates to be tested.
|     real  ptcrc[][3],i/o-Array  of points in contact region.
|     int  *npton,     i/o-Number of points in ptcrc[][3] array.
|     int   lflag,       o-Flag returned TRUE if pnt is added to array.
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
  int ptocrc(real pnt[3], real ptcrc[][3], int *nptcrc)
#else
  int ptocrc(pnt, ptcrc, nptcrc)
  real  pnt[3];
  real  ptcrc[][3];
  int  *nptcrc;
#endif
{
  int   i, j, lflag;
  real  diff[3];

  lflag = FALSE;
  for (i=0; i<*nptcrc; i++) {       /* Test the point for uniqueness. */
    for (j=0; j<3; j++) {diff[j] = ptcrc[i][j] - pnt[j];}
    if (vabsc(3, diff) < zrogeo) goto DONE;
  }
  lflag = TRUE;
  (*nptcrc)++;                     /* Add the new point to the array. */
  for (j=0; j<3; j++) {ptcrc[*nptcrc][j] = pnt[j];} 
DONE: ;
  return (lflag);
}
