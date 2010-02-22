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
/* mrgfac-01 Jan 00:08 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       If possible, this routine merges two Perims indicated by
|     pointers perim1 and perim2.
|
|     Access:
|       lmerge = (int) mrgfac(perim1, perim2);
|     Perim *perim1,i-Pointer to first  Perim record.
|     Perim *perim2,i-Pointer to second Perim record.
|     int    lmerge,o-Flag set TRUE if the perims were merged.
|
|     Error Conditions:
|       If perim1 and perim2 are not valid Perim records, or if they are
|     not Perims of the same Solid, then execution is aborted. A message
|     is printed.
|
|     Comments:
|       If the cross product of the two unit Face normals is greater
|     than zrogeo, the two perims are not in parallel planes and are not
|     merged.
|       If merging takes place, on exit perim1 points to the new merged
|     Perim.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  int mrgfac(Perim *perim1, Perim *perim2)
#else
  int mrgfac(perim1, perim2)
  Perim *perim1, *perim2;
#endif
{
  Hedge *hed, *hed1, *hed2;
  int    lmerge, lshare;
  real   V[3];

/* Check for valid Perim pointers. */
  if ((perim1->type != PERIM) || (perim2->type != PERIM)) {
    echoc();
    textc("*** mrgfac: Invalid Perim pointer. ***", TRUE);
    abortc();
  } else if (perim1->prmFac->facSld != perim2->prmFac->facSld) {
    echoc();
    textc("*** mrgfac: Perims from different Solids. ***", TRUE);
    abortc();
  } else {
    lmerge = FALSE;
  }

/* If Perim pointers are identical, return without action. */
  if (perim1 == perim2) goto _DONE;

/* Check for parallel Face normals; if not, return. */
  vcrosc(perim1->prmFac->faceq, perim2->prmFac->faceq, V);
  if (vabsc(3, V) > zrogeo) goto _DONE;

/* Delete any shared edges, if any and merge hedge lists. */
  lshare = FALSE;
_AGAIN:
  hed1 = perim1->prmHed;
  do {
    hed2 = mate(hed1);
    if ((hed2->hedPrm == perim2) || (hed2->hedPrm == perim1)) {
      lshare = TRUE;
      hed = hed1;
      while (hed->nxtHedPrm != hed1) hed = hed->nxtHedPrm;
      hed->nxtHedPrm = hed2->nxtHedPrm;
      hed = hed2;
      while (hed->nxtHedPrm != hed2) hed = hed->nxtHedPrm;
      hed->nxtHedPrm = hed1->nxtHedPrm;
      hed1->nxtHedPrm = hed2;
      hed2->nxtHedPrm = hed1;
      xedgc(hed1->hedEdg);
      xhedc(hed2);
      xhedc(hed1);
      goto _AGAIN;
    }
    hed1 = hed1->nxtHedPrm;
  } while (hed1 != perim1->prmHed);
  hed2 = perim2->prmHed;
  do {
    hed1 = mate(hed2);
    if ((hed1->hedPrm == perim2) || (hed1->hedPrm == perim1)) {
      lshare = TRUE;
      hed = hed2;
      while (hed->nxtHedPrm != hed2) hed = hed->nxtHedPrm;
      hed->nxtHedPrm = hed1->nxtHedPrm;
      hed = hed1;
      while (hed->nxtHedPrm != hed1) hed = hed->nxtHedPrm;
      hed->nxtHedPrm = hed2->nxtHedPrm;
      hed1->nxtHedPrm = hed1;
      hed2->nxtHedPrm = hed2;
      xedgc(hed2->hedEdg);
      xhedc(hed1);
      xhedc(hed2);
      goto _AGAIN;
    }
    hed2 = hed2->nxtHedPrm;
  } while (hed2 != perim2->prmHed);
  if (!lshare) goto _DONE;

/* Merge all hedges from perim2 into perim1 and delete perim2. */
  hed2 = perim2->prmHed;
  do {
    hed2->hedPrm = perim1;
    hed2 = hed2->nxtHedPrm;
  } while (hed2 != perim2->prmHed);
  xprmc(perim2);
  lmerge = TRUE;
_DONE:
  return(lmerge);
}
