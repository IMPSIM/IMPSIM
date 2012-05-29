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
/* dpntc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Store the coordinates of a point attached to a body relative to
|     a specified reference coordinate system.
|
|     Access:
|       (void) dpntc(Word name, Word ref, real r[3]);
|     Word name,i-Name of the point to be located.
|     Word ref,i-Name of the reference coordinate system for r[3] data.
|     real r[3],i-Coordinated data for the point.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined point or ref name.
|
|     Comments:
|       If ref = "abs" or ref = "absolute" then global coordinates are
|     specified for r[3].
|       If ref = "body" then body coordinates are specified for r[3].
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dpntc(Word name, Word ref, real r[3])
#else
  void dpntc(name, ref, r)
  Word name, ref;
  real r[3];
#endif
{
  Axes  *axes;
  Body  *body;
  Joint *joint;
  Point *point, *pnt;
  Word   string;
  int    i, ldone;

/* Locate the master point record with this name. */
  ldone = FALSE;
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (point=body->bdyPnt; point; point=point->nxtPnt) {
      if (point->master) {
        if (strncmp(name, point->name, MAXCHR) == 0) {

/* Locate the designated reference. */
          strcpy(string, ref);
          lcasec(string);
          if (strncmp(string, "body", MAXCHR) == 0) {
            point->local = TRUE;
            for (i=0; i<3; i++) {
              point->coord[i] = r[i];
            }
            point->coord[3] = 1.0;
            ldone = TRUE;
          } else if (strncmp(string, "link", MAXCHR) == 0) {
            point->local = TRUE;
            for (i=0; i<3; i++) {
              point->coord[i] = r[i];
            }
            point->coord[3] = 1.0;
            ldone = TRUE;
          } else if ((strncmp(string, "abs", MAXCHR) == 0)
                  || (strncmp(string, "absolute", MAXCHR) == 0)) {
            point->local = FALSE;
            for (i=0; i<3; i++) {
              point->coord[i] = r[i];
            }
            point->coord[3] = 1.0;
            ldone = TRUE;
          } else {
            for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
              joint = axes->axsJnt;
              if (strncmp(joint->name, ref, MAXCHR) == 0) {

/* Store the point coordinate data. */
                point->local = TRUE;
                mpyxrc(axes->S, r, point->coord);
                point->coord[3] = 1.0;
                ldone = TRUE;
                break;
              }
            }
            if (!ldone) {
              echoc();
              textc("*** There is no joint named '", FALSE);
              textc(ref, FALSE);
              textc("' on body '", FALSE);
              textc(body->name, FALSE);
              textc("' with point '", FALSE);
              textc(name, FALSE);
              textc("'. ***", TRUE);
              System.nerror = 3;
              return;
            }
          }
          if (ldone) break;
        }
      }
    }
    if (ldone) break;
  }

/* Store data for all secondary points of the same name. */
  if (point) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (pnt=body->bdyPnt; pnt; pnt=pnt->nxtPnt) {
        if (strncmp(pnt->name, name, MAXCHR) == 0) {
          if (!(pnt->master)) {
            pnt->local = FALSE;
            ptposc(point, pnt->coord);
            point->coord[3] = 1.0;
          }
        }
      }
    }
  } else {
    echoc();
    textc("*** There is no point named '", FALSE);
    textc(name, FALSE);
    textc("'. ***", TRUE);
  }
  return;
}
