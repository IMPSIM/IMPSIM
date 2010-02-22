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
/* xsldc-23 Jul 03:09 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Delete a specified Solid record and any dependent Face and
|     Vertex records from a solid model.
|
|     Access:
|       (void) xsldc(Solid *sld);
|     Solid *sld, i-Pointer to the Solid record to be deleted.
|
|     Error Conditions:
|       If sld does not point to a valid Solid record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       None.
*
*     History:
*     23 Jul 03:JJU-Original.
*     09 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  void xsldc(Solid *sld)
#else
  void xsldc(sld)
  Solid *sld;
#endif
{
  Body  *body;
  Solid *solid;

  if (sld->type == SOLID) {
    body  = sld->sldBdy;
    solid = body->bdySld;
    if (solid == sld) {
      body->bdySld = sld->nxtSld;
    } else {
      while (solid->nxtSld != sld) {
        if (solid->nxtSld == NULL) {
          echoc();
          textc("*** xsldc:  NULL Solid record. ***", TRUE);
          abortc();
        }
        solid = solid->nxtSld;
      }
      solid->nxtSld = sld->nxtSld;
    }
    while (sld->sldFac)  xfac(sld->sldFac);
    while (sld->sldVtx) xvtxc(sld->sldVtx);
    body->nslds--;
    free(sld);
  } else {
    echoc();
    textc("*** xsldc:  Invalid Solid record. ***", TRUE);
    abortc();
  }
  return;
}
