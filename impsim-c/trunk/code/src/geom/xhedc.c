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
/* xhedc-23 Jul 03:09 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Delete a specified Hedge record from a solid model.
|
|     Access:
|       (void) xhedc(Hedge *hed);
|     Hedge *hed, i-Pointer to the Hedge record to be deleted.
|
|     Error Conditions:
|       If hed does not point to a valid Hedge record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     20 Jul 03:JJU-Original.
*     09 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xhedc(Hedge *hed)
#else
  void xhedc(hed)
  Hedge *hed;
#endif
{
  Corner *corner;
  Edge   *edge;
  Hedge  *hedge;
  Perim  *perim;

  if (hed->type == HEDGE) {
    perim = hed->hedPrm;                 /* Find Perim of this Hedge. */
    if (hed->nxtHedPrm == hed) {               /* Single Hedge Perim? */
      perim->prmHed = NULL;              /* Perim ring will be empty. */
    } else {
      hedge = perim->prmHed;
      if (hedge) {
        if (hedge == hed) perim->prmHed = hed->nxtHedPrm;/* Skip hed. */
        while (hedge->nxtHedPrm != hed) {
          hedge = hedge->nxtHedPrm;/* Find Hedge before hed in Perim. */
        }
      }
      hedge->nxtHedPrm = hed->nxtHedPrm; /* Bypass hed in Perim ring. */
    }
    perim->nhedgs--;                 /* One less Hedge in this Perim. */
    corner = hed->hedCnr;              /* Find Corner for this Hedge. */
    if (hed->nxtHedCnr == hed) {              /* Single Hedge Corner? */
      corner->cnrHed = NULL;            /* Corner ring will be empty. */
    } else {
      hedge = corner->cnrHed;
      if (hedge) {
        if (hedge == hed) corner->cnrHed = hed->nxtHedCnr;/*Skip hed. */
        while (hedge->nxtHedCnr != hed) {
          hedge = hedge->nxtHedCnr;/*Find Hedge before hed in Corner. */
        }
      }
      hedge->nxtHedCnr = hed->nxtHedCnr;/* Bypass hed in Corner ring. */
    }
    corner->nhedgs--;                /* One less Hedge in the Corner. */
    if (hed->hedMat) hed->hedMat->hedMat = NULL;  /* Disconnect mate. */
    edge = hed->hedEdg;
    if (edge->edgHeL == hed) edge->edgHeL = NULL; /* Disconnect hed   */
    if (edge->edgHeR == hed) edge->edgHeR = NULL; /*   from the edge. */
    perim->prmFac->facSld->nhedgs--; /* One less Hedge in this Solid. */
    free(hed);                                  /* Delete this Hedge. */
  } else {
    echoc();
    textc("*** xhedc:  Invalid Hedge record. ***", TRUE);
    abortc();
  }
  return;
}
