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
/* ringac-27 Dec 05:08 Sep 07
|     (C)Copyright, JJU Research, 2005-2007.
|
|     Description:
|       Place a Hedge record into a closed ring of Hedge records which
|     starts from a Corner->cnrHed or a Perim->prmHed, immediately
|     following a specified member of the ring, *hedbfr.
|
|     Access:
|       (void) ringac(void *parent, Hedge *hedge, Hedge *hedbfr);
|     void  * parent, i-Pointer to the parent Corner or Perim record.
|     Hedge * hedge,  i-Pointer to the Hedge record to be entered.
|     Hedge * hedbfr, i-Pointer to the Hedge record to be followed.
|
|     Error Conditions:
|       If parent does not point to a valid Corner or Perim record then
|     execution is aborted.  A message is printed.
|
|     Comments:
|       If *hedbfr is NULL, this indicates that the ring starting in the
|     parent record is initially empty.  In this case, parent ends 
|     pointing to hedge which points to itself as a closed ring.
*
*     History:
*     27 Dec 05:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void ringac(void *parent, Hedge *hedge, Hedge *hedbfr)
#else
  void ringac(parent, hedge, hedbfr)
  void  *parent;
  Hedge *hedge, *hedbfr;
#endif
{
  Corner *corner;
  Hedge  *hed;
  Perim  *perim;

  if (((Corner *) parent)->type == CORNER) {
    hed = hedge;      /* Remove *hedge from any previous Corner ring. */
    if (hed->nxtHedCnr) {
      while (hed->nxtHedCnr != hedge) hed = hed->nxtHedCnr;
      if (hed != hedge) {
        hed->nxtHedCnr = hedge->nxtHedCnr;
        --hedge->hedCnr->nhedgs;
      }
    }
    corner = (Corner *) parent;
    if (hedbfr) {    /* Add hedge after hedbfr in ring around corner. */
      hedge->nxtHedCnr  = hedbfr->nxtHedCnr;
      hedbfr->nxtHedCnr = hedge;
    } else {                /* Add hedge in empty ring around corner. */
      corner->cnrHed    = hedge;
      hedge->nxtHedCnr  = hedge;
    }
    hedge->hedCnr = corner;
    ++corner->nhedgs;

  } else if (((Perim *) parent)->type == PERIM) {
    hed = hedge;       /* Remove *hedge from any previous Perim ring. */
    if (hed->nxtHedPrm) {
      while (hed->nxtHedPrm != hedge) hed = hed->nxtHedPrm;
      if (hed != hedge) {
        hed->nxtHedPrm = hedge->nxtHedPrm;
        --hedge->hedPrm->nhedgs;
      }
    }
    perim = (Perim *) parent;
    if (hedbfr) {     /* Add hedge after hedbfr in ring around perim. */
      hedge->nxtHedPrm  = hedbfr->nxtHedPrm;
      hedbfr->nxtHedPrm = hedge;
    } else {                 /* Add hedge to empty ring around perim. */
      perim->prmHed     = hedge;
      hedge->nxtHedPrm  = hedge;
    }
    hedge->hedPrm = perim;
    ++perim->nhedgs;
  } else {
    echoc();
    textc("*** ringac:  Invalid parent record. ***", TRUE);
    abortc();
  }
  return;
}
