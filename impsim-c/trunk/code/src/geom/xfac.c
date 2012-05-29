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
/* xfac-23 Jul 03:09 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Delete a specified Face record and any dependent Perim records
|     from a solid model.
|
|     Access:
|       (void) xfac(Face *fac);
|     Face *fac, i-Pointer to the Face record to be deleted.
|
|     Error Conditions:
|       If fac does not point to a valid Face record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     23 Jul 03:JJU-Original.
*     08 Sep 07:JJU-Added error messages.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xfac(Face *fac)
#else
  void xfac(fac)
  Face *fac;
#endif
{
  Face *facptr;

  if (fac->type == FACE) {
    facptr = fac->facSld->sldFac;
    if (facptr == fac) {
      fac->facSld->sldFac = fac->nxtFac;
    } else {
      while (facptr->nxtFac != fac) {
        if (facptr->nxtFac == NULL) {
          echoc();
          textc("*** xfac:  NULL Face pointer. ***", TRUE);
          abortc();
        }
        facptr = facptr->nxtFac;
      }
      facptr->nxtFac = fac->nxtFac;
    }
    while (fac->facPrm) xprmc(fac->facPrm);
    fac->facSld->nfaces--;
    free(fac);
  } else {
    echoc();
    textc("*** xfac:  Invalid Face record. ***", TRUE);
    abortc();
  }
  return;
}
