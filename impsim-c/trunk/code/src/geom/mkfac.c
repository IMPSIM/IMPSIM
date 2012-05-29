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
/* mkfac-20 Jul 03:21 Jan 09
|     (C)Copyright, JJU Research, 2003-2009.
|
|     Description:
|       Form a data structure for a new Face record as the child of a
|     designated Solid.
|
|     Access:
|       face = (Face *) mkfac(Solid *solid);
|     Solid *solid, i-Pointer to the parent Solid record.
|     Face  *face,  o-Pointer to the newly formed Face record.
|
|     Error Conditions:
|       If solid does not point to a valid Solid record then execution 
|     is aborted.  A message is printed.
|
|     Comments:
|       The new Face is added to the end of the list of faces of the
|     designated Solid.  There is not yet a perimeter on this Face.  The 
|     new Face data are set to undefined.
*
*     History:
*     20 Jul 03:JJU-Original.
*     08 Sep 07:JJU-Error message added.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Face *mkfac(Solid *solid)
#else
  Face *mkfac(solid)
  Solid *solid;
#endif
{
# include "..\libcad\colorc.h";
  Face *face, *facptr;

  if (solid->type == SOLID) {
    face = (Face *) malloc(sizeof(Face));
    face->type   = FACE;
    facptr = solid->sldFac;
    if (facptr) {
      while (facptr->nxtFac) facptr = facptr->nxtFac;
      facptr->nxtFac = face;
    } else {
      solid->sldFac = face;
    }
    face->nxtFac = NULL;
    face->facSld = solid;
    face->facPrm = NULL;
    face->nprms  = 0;
    face->facno  = ++solid->nfaces;/*Face->facno=1,2,...,Solid->nfaces*/
    face->kcolor = kdfgeo;
    ldnanc((void *) &(face->area));
    ldnanc((void *) &(face->faceq[0]));
    ldnanc((void *) &(face->faceq[1]));
    ldnanc((void *) &(face->faceq[2]));
    ldnanc((void *) &(face->faceq[3]));
    face->coeff  = 1.0;
  } else {
    echoc();
    textc("*** mkfac:  Invalid Solid record. ***", TRUE);
    abortc();
  }
  return(face);
}
