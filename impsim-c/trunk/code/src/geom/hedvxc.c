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
/* hedvxc-18 Jan 04:07 Sep 07
|     (C)Copyright, JJU Research, 2004-2007.
|
|     Description:
|       Given an Hedge record, return pointers to the Vertex before and
|     Vertex after this Hedge within its Perim ring.
|
|     Access:
|       (void) hedvxc(Hedge *hedge, Vertex **vxB, Vertex **vxA);
|     Hedge   *hedge,i-Hedge record to be investigated.
|     Vertex **vxB,  o-Pointer to the Vertex before the given Hedge.
|     Vertex **vxA,  o-Pointer to the Vertex after  the given Hedge.
|
|     Error Conditions:
|       If hedge does not point to a valid Hedge record then execution 
|     is aborted.  A message is printed.
|
|     Comments:
|       An example application might read as follows:
|         #include libgeo.h
|         Hedge   *hedge;
|         Vertex  *vxB, *vxA;
|
|         hedvxc(hedge, &vxB, &vxA);
*
*     History:
*     18 Jan 04:JJU-Original.
*     07 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void hedvxc(Hedge *hedge, Vertex **vxB, Vertex **vxA)
#else
  void hedvxc(hedge, vxB, vxA);
  Hedge  *hedge;
  Vertex **vxB, **vxA;
#endif
{
  if (hedge->type == HEDGE) {
    vxB = &(hedge->hedCnr->cnrVtx);
    vxA = &(hedge->hedMat->hedCnr->cnrVtx);
  } else {
    echoc();
    textc("*** hedvxc: Invalid Hedge record. ***", TRUE);
    abortc();
  }
  return;
}
