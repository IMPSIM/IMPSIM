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
/* mkhedc-20 Jul 03:08 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Form a data structure for a new half-edge record and form it as
|     the child of a designated perimeter.
|
|     Access:
|       hedge = (Hedge *) mkhedc(Perim *perim, Corner *corner);
|     Perim  *perim, i -Pointer to the parent Perim record.
|     Corner *corner,io-Pointer to the starting Corner of the new Hedge.
|     Hedge  *hedge, o -Pointer to the newly formed Hedge record.
|
|     Error Conditions:
|       If perim  does not point to a valid Perim  record then execution 
|     is aborted.  A message is printed.
|       If corner does not point to a valid Corner record then execution
|     is aborted.  A message is printed.
|
|     Comments:
|       The specified Perim is on the left of the new hedge.
|       There is not yet an Edge for this Hedge, and no mating Hedge;
|     these are set to NULL;
*
*     History:
*     20 Jul 03:JJU-Original.
*     19 Dec 05:JJU-Corner is added as an argument.
*     08 Sep 07:JJU-Error messages printed.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Hedge *mkhedc(Perim *perim, Corner *corner)
#else
  Hedge *mkhedc(perim, corner)
  Perim  *perim;
  Corner *corner;
#endif
{
  Hedge *hedge;

  if (perim->type  != PERIM) {
    echoc();
    textc("*** mkhedc:  Invalid Perim record. ***", TRUE);
    abortc();
  }
  if (corner->type != CORNER) {
    echoc();
    textc("*** mkhedc:  Invalid Corner record. ***", TRUE);
    abortc();
  }
  hedge = (Hedge *) malloc(sizeof(Hedge));   /* Create the new Hedge. */
  hedge->type = HEDGE;
  hedge->nxtHedPrm = hedge;          /* Initialize empty Perim  ring. */
  hedge->nxtHedCnr = hedge;          /* Initialize empty Corner ring. */
  hedge->hedPrm = NULL;
  hedge->hedCnr = NULL;
  hedge->hedEdg = NULL;
  hedge->hedMat = NULL;
  ringbc(perim,  hedge, perim->prmHed);/* Set hedge into perim  ring. */
  ringbc(corner, hedge,corner->cnrHed);/* Set hedge into corner ring. */
  ++perim->prmFac->facSld->nhedgs;       /* Solid->nhedgs = 1, 2, ... */
  return(hedge);
}
