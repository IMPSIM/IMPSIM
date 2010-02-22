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
/* pntsc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Add one or more points to a specified body of the system model.
|
|     Access:
|       (void) pntsc(Word bdname, Token names[], int n);
|     Word bdname,i-Name of the body to which the points are attached.
|     Token names[n],i-Array of names of the points to be added.
|     int n,i-Count of the number of points named in the names array.
|
|     Error Conditions:
|       System.nerror = 3 indicates that body bdname is undefined.  A
|     diagnostic message is printed and return is made with no further
|     action.
|
|     Comments:
|       Multiple points may coexist with identical names, either on the
|     same body or on different bodies.  The first one created is taken
|     as the master and others are marked as copies.  All copies are
|     placed coincident with the master point at the design position.
|       System.level <= 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void pntsc(Word bdname, Token names[], int n)
#else
  void pntsc(bdname, names, n)
  Word  bdname;
  Token names[];
  int   n;
#endif
{
  Body  *body, *bdy;
  Point *point, *pnt;
  int    i;

  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strcmp(body->name, bdname) == 0) break;
  }
  if (body == NULL) {
    echoc();
    textc("*** There is no body named '", FALSE);
    textc(bdname, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
    return;
  }
  if (System.level > 3) System.level = 3;
  for (i=0; i<n; i++) {
    point = (Point *) malloc(sizeof(Point));
    point->type   = POINT;
    strcpy(point->name, names[i].data.text);
    point->nxtPnt = NULL;
    if (body->bdyPnt) {         /* Add new Point to end of linked list. */
      pnt = body->bdyPnt;
      while (pnt->nxtPnt) pnt = pnt->nxtPnt;
      pnt->nxtPnt = point;
    } else {
      body->bdyPnt = point;
    }
    point->pntBdy = body;
    point->local  = FALSE;
    point->master = TRUE;
    if (i == 0) {
      point->kcolor = -kdfgeo;
    } else {
      point->kcolor =  kdfgeo;
    }
    point->coord[0] = 0.0;
    point->coord[1] = 0.0;
    point->coord[2] = 0.0;
    point->coord[3] = 1.0;
    for (bdy=System.sysBdy; bdy; bdy=bdy->nxtBdy) {
      for (pnt=bdy->bdyPnt; pnt; pnt=pnt->nxtPnt) {
        if (strcmp(pnt->name, point->name) == 0) {
          if (pnt->master) {
            if (pnt != point) {
              point->master = FALSE;
              ptposc(pnt, point->coord);
            }
          }
        }
      }
    }
  }
  return;
}
