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
/* xprmc-23 Jul 03:21 Jan 09
|     (C)Copyright, JJU Research, 2003-2009.
|
|     Description:
|       Delete a specified Perim record and any dependent Hedge records
|     from a solid model.
|
|     Access:
|       (void) xprmc(Perim *perim);
|     Perim *perim, i-Pointer to the Perim record to be deleted.
|
|     Error Conditions:
|       If perim does not point to a valid Perim record then execution 
|     is aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     23 Jul 03:JJU-Original.
*     09 Sep 07:JJU-Printed error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xprmc(Perim *perim)
#else
  void xprmc(perim)
  Perim *perim;
#endif
{
  Face  *face;
  Perim *prm;

  if (perim->type == PERIM) {
    face = perim->prmFac;
    prm  = face->facPrm;
    if (prm == perim) {  /* Check if this is the first Perim on face. */
      face->facPrm = prm->nxtPrm;   /* Make face point to next Perim. */
    } else {
      while (prm->nxtPrm != perim) { 
        if (prm->nxtPrm == NULL) {
          echoc();
          textc("*** xprmc:  NULL Perim pointer. ***", TRUE);
          abortc();
        }
        prm = prm->nxtPrm;       /* Find the Perim pointing to perim. */
      }
      prm->nxtPrm = perim->nxtPrm;/*Bypass in list of Perims on Face. */
    }
    while (perim->prmHed)xhedc(perim->prmHed);/*Delete Hedgs of perim.*/
    face->nprms--;                /* Reduce count of Perims on  Face. */
    perim->prmFac->facSld->nprms--;/*Reduce count of Perims in Solid. */
    free(perim);
  } else {
    echoc();
    textc("*** xprmc:  Invalid Perim record. ***", TRUE);
    abortc();
  }
  return;
}
