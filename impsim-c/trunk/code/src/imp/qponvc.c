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
/* qponvc-01 Jan 00:16 Feb 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Determine whether a specified point is in contact with a 
|     specified vertex.
|
|     Access:
|       lflag = (int) qponvc(real pnt[3], Vertex *vertex);
|     real    pnt[3],i-Point to be tested for contact.
|     Vertex *vertex,i-Vertex record to be tested for contact.
|     int     lflag, o-Flag set TRUE if contact is verified.
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
  int qponvc(real pnt[3], Vertex *vertex)
#else
  int qponvc(pnt, vertex)
  real    pnt[3];
  Vertex *vertex;
#endif
{
  int  i, lflag;
  real diff[3];

  lflag = FALSE;
  for (i=0; i<3; i++) {diff[i] = vertex->coord[i] - pnt[i];}
  if (vabsc(3, diff) < zrogeo) lflag = TRUE;
  return (lflag);
}
