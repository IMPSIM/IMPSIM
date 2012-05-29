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
/* pointc-29 Jun 04:08 Sep 07
|     (C)Copyright, JJU Research, 2004-2007.
|
|     Description:
|       Define a Point attached to a given Body.
|
|     Access:
|       point = (Point *) pointc(Body *body, Name *name, real x0,
|         real y0, real z0);
|     Body  *body  ,  i-The Body to obtain the new Point.
|     Name  *name,    i-The name for the new Point.
|     real   x0,y0,z0,i-The Body coordinates of the new Point.
|     Point *point,   o-Pointer to the newly formed Point record.
|         
|
|     Error Conditions:
|       If body does not point to a valid Body record then execution is
|     aborted.  A message is printed.
|
|     Comments:
|       The new Point is added to the end of the list of Points for the
|     designated Body.
|       If a Point with the given name already exists the user is asked
|     whether the intent is to change its location data.
*
*     History:
*     29 Jun 04:JJU-Original.
*     08 Sep 07:JJU-Added error message.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Point *pointc(Body *body, Name *name, real x0, real y0, real z0)
#else
  Point *pointc(body, name, x0, y0, z0)
  Body *body;
  Name *name;
  real  x0, y0, z0;
#endif
{
  Point *point, *pnt;
  char  quest[2];
  int   nogo;

  if (body->type == BODY) {
    point = body->bdyPnt;
    while (point) {
      if (point->master) {
        if (strcmp(name, point->name) == 0) {
          if (qiactc()) {
            do {
              textc("Point '", FALSE);
              textc(name, FALSE);
              textc("' already exists.  Change its data?  Y/N [N]: > ",
                FALSE);
              nogo = bfinc("n");
            } while (nogo);
            alprdc("n", quest);
            lcasec(quest);
            quest[1] = '\0';
          } else {
            strcpy(quest, "n");
          }
          if (strcmp(quest, "y") == 0) {
            goto _CHANGE;
          } else {
            goto _RETURN;
          }
        }
      }
      point = point->nxtPnt;
    }
    point = (Point *) malloc(sizeof(Point));
    point->type = POINT;
    point->nxtPnt = NULL;
    pnt = body->bdyPnt;
    if (pnt) {
      while (pnt->nxtPnt) pnt = pnt->nxtPnt;
      pnt->nxtPnt  = point;
    } else {
      body->bdyPnt = point;
    }
    point->pntBdy = body;
    strcpy(point->name, name);
    point->master = TRUE;
    point->local  = TRUE;
    point->kcolor = kdfgeo;
_CHANGE:
    point->coord[0] = x0;
    point->coord[1] = y0;
    point->coord[2] = z0;
    point->coord[3] = 1.0;
    lsaved = FALSE;
    ldraw  = TRUE;
  } else {
    echoc();
    textc("*** pointc:  Invalid Body record. ***", TRUE);
    abortc();
  }
_RETURN:
  return(point);
}
