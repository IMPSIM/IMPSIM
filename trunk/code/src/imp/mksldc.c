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
/* mksldc-20 Jul 03:29 Jul 09
|     (C)Copyright, JJU Research, 2003-2009.
|
|     Description:
|       Form a data structure for a new Solid record as the child of a
|     designated Body.
|
|     Access:
|       solid = (Solid *) mksldc(Body *body);
|     Body  *body, i-Pointer to the parent Body record.
|     Solid *solid,o-Pointer to the newly formed Solid record.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The new Solid is added to the end of the list of solids of the
|     designated Body.  If *body does not point to a valid Body record
|     then the new Solid is created as an orphan, without a parent Body.
|     The number of an orphan Solid is set to NaN.
|       There are not yet any Face, Edge, or Vertex records in the new
|     Solid.
*
*     History:
*     20 Jul 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  Solid *mksldc(Body *body)
#else
  Solid *mksldc(body)
  Body  *body;
#endif
{
  Solid *solid, *sldptr;
  int    i;

  solid = (Solid *) malloc(sizeof(Solid));
  solid->type = SOLID;
  solid->nxtSld = NULL;
  if (body->type == BODY) {
    sldptr = body->bdySld;
    if (sldptr) {
      while (sldptr->nxtSld) sldptr = sldptr->nxtSld;
      sldptr->nxtSld = solid;
    } else {
      body->bdySld = solid;
    }
    solid->sldno  = ++body->nslds;/* Solid->sldno=1,2,...,body->nslds */
  } else {
    sldptr = System.sysSld;
    if (sldptr) {
      while (sldptr->nxtSld) sldptr = sldptr->nxtSld;
      sldptr->nxtSld = solid;
    } else {
      System.sysSld = solid;
    }
    ldnanc((void *) &(solid->sldno));
  }
  solid->sldBdy = body;
  solid->sldFac = NULL;
  solid->sldEdg = NULL;
  solid->sldVtx = NULL;
  solid->name[0]= '\0';
  solid->kcolor = kdfgeo;
  solid->nfaces = 0;
  solid->nprms  = 0;
  solid->nhedgs = 0;
  solid->nedges = 0;
  solid->ncnrs  = 0;
  solid->nvrtxs = 0;
  solid->kdimen = UNKNOWN;
  for (i=0; i<6; i++) {
    ldnanc((void *) &(solid->screw[i]));
  }
  ldnanc((void *) &(solid->area));
  ldnanc((void *) &(solid->volume));
  for (i=0; i<3; i++) {
    ldnanc((void *) &(solid->cg[i]));
    ldnanc((void *) &(solid->smin_coord[i]));
    ldnanc((void *) &(solid->smax_coord[i]));
    ldnanc((void *) &(solid->bs_ctr[i]));
  }
  ldnanc((void *) &(solid->bs_rad));
  return(solid);
}
