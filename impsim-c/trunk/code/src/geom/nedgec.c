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
/* nedgec-28 May 04:08 Sep 07
|     (C)Copyright, JJU Research, 2004-2007.
|
|     Description:
|       Return the number of a specified Edge record within a Solid.
|
|     Access:
|       n = (int) nedgec(Edge *edge);
|     Edge *edge, i-Pointer to the Edge record.
|     int  n,     o-Number returned for the specified edge.  
|
|     Error Conditions:
|       If *edge does not point to a valid Edge record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     28 May 04:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  int nedgec(Edge *edge)
#else
  int nedgec(edge)
  Edge  *edge;
#endif
{
  Edge   *edg;
  Solid  *solid;
  int     n;

  if (edge->type == EDGE) {
    solid = edge->edgSld;
    n = 1;
    edg = solid->sldEdg;
    while (edg != edge) {
      edg = edg->nxtEdg;
      n++;
    }
  } else {
    echoc();
    textc("*** nedgec:  Invalid Edge record. ***", TRUE);
    abortc();
  }
  return(n);
}
