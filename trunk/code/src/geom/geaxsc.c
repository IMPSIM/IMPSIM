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
/* geaxsc-29 Jun 04:16 Jul 09
|     (C)Copyright, JJU Research, 2004-2009
|
|     Description:
|       Define a set of coordinate Axes attached to a given Body.
|
|     Access:
|       axes = (Axes *) geaxsc(Body *body, Name *name, real x0,
|         real y0, real z0, real thx, real thy, real thz);
|     Body *body,       i-The Body to obtain the new Axes.
|     Name *name,       i-The name for the new Axes.
|     real  x0,y0,z0,   i-The Body coordinates of the Axes origin.
|     real  thx,thy,thz,i-Axes rotation angles about Body axes.
|     Axes *axes,       o-Pointer to the newly formed Axes record.
|         
|
|     Error Conditions:
|       If body does not point to a valid Body record then execution
|     is aborted.  A message is printed.
|
|     Comments:
|       The new Axes record is added to the end of the list of Axes for 
|     the designated Body.
*
*     History:
*     29 Jun 04:JJU-Original.
*     07 Sep 07:JJU-Added error message.
*     16 Jul 09:JJU-Renamed from axesc to avoid conflict with IMP.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Axes *geaxsc(Body *body, Name *name, real x0, real y0, real z0,
    real thx, real thy, real thz)
#else
  Axes *geaxsc(body, name, x0, y0, z0, thx, thy, thz)
  Body *body;
  Name *name;
  real  x0, y0, z0, thx, thy, thz;
#endif
{
  Axes *axes, *axs;
  char quest[2];
  int  nogo;
  real cthx, cthy, cthz, sthx, sthy, sthz;

  if (body->type == BODY) {
    axes = body->bdyAxs;
    while (axes) {
      if (strcmp(name, axes->name) == 0) {
        do {
          echoc();
          textc("Axes '", FALSE);
          textc(name, FALSE);
          textc("' already exist.  ", FALSE);
          if (qiactc()) {
            textc("Change their data?  Y/N [N]: > ", FALSE);
            nogo = bfinc("n");
          } else {
            goto _RETURN;
          }
        } while (nogo);
        alprdc("n", quest);
        lcasec(quest);
        quest[1] = '\0';
        if (strcmp(quest, "y") == 0) {
          goto _CHANGE;
        } else {
          goto _RETURN;
        }
      }
      axes = axes->nxtAxs;
    }
    axes = (Axes *) malloc(sizeof(Axes));  /* Create new Axes record. */
    axes->type   = AXES;
    axes->nxtAxs = NULL;
    axs = body->bdyAxs;
    if (axs) {
      while (axs->nxtAxs) axs = axs->nxtAxs;
      axs->nxtAxs  = axes;
    } else {
      body->bdyAxs = axes;
    }
    axes->axsBdy = body;
    strcpy(axes->name, name);
    axes->kcolor = kdfgeo;
_CHANGE:
    cthx = cos(thx);
    sthx = sin(thx);
    cthy = cos(thy);
    sthy = sin(thy);
    cthz = cos(thz);
    sthz = sin(thz);
    axes->S[0][0] = cthy * cthz;
    axes->S[0][1] =-cthy * sthz;
    axes->S[0][2] = sthy;
    axes->S[0][3] = x0;
    axes->S[1][0] = cthx * sthz + sthx * sthy * cthz;
    axes->S[1][1] = cthx * cthz - sthx * sthy * sthz;
    axes->S[1][2] =-sthx * cthy;
    axes->S[1][3] = y0;
    axes->S[2][0] = sthx * sthz - cthx * sthy * cthz;
    axes->S[2][1] = sthx * cthz + cthx * sthy * sthz;
    axes->S[2][2] = cthx * cthy;
    axes->S[2][3] = z0;
    lsaved = FALSE;
    ldraw  = TRUE;
  } else {
    echoc();
    textc("*** geaxsc: Invalid Body record. ***", TRUE);
    abortc();
  }
_RETURN:
  return(axes);
}
