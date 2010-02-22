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
/* mkprmc-09 Nov 03:21 Jan 09
|     (C)Copyright, JJU Research, 2003-2009.
|
|     Description:
|       Form a data structure for a new Perim record as the child of a
|     designated face.
|
|     Access:
|       perim = (Perim *) mkprmc(Face *face);
|     Face  * face,  i-Pointer to the parent Face record.
|     Perim * perim, o-Pointer to the newly formed Perim record.
|
|     Error Conditions:
|       If face does not point to a valid Face record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       The new Perim is added to the end of the list of Perims on the
|     designated Face.  There are not yet any Hedges in this Perim.
*
*     History:
*     20 Jul 03:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Perim *mkprmc(Face *face)
#else
  Perim *mkprmc(face)
  Face *face;
#endif
{
  Perim *perim, *prmptr;

  if (face->type == FACE) {
    perim = (Perim *) malloc(sizeof(Perim));
    perim->type = PERIM;
    prmptr = face->facPrm;
    if (prmptr) {
      while (prmptr->nxtPrm) prmptr = prmptr->nxtPrm;
      prmptr->nxtPrm = perim;
    } else {
      face->facPrm = perim;
    }
    perim->nxtPrm = NULL;
    perim->prmFac = face;
    perim->prmHed = NULL;
    perim->nhedgs = 0;
    ldnanc((void *) &(perim->area));
    ++face->nprms;                        /*  Face->nprms = 1, 2, ... */
    ++face->facSld->nprms;                /* Solid->nprms = 1, 2, ... */
  } else {
    echoc();
    textc("*** mkprmc:  Invalid Face record. ***", TRUE);
    abortc();
  }
  return(perim);
}
