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
/* forcec-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add a new Force record to the System model.
|
|     Access:
|       (void) forcec(Word namfrc, Word namept, Word namptB,
|         Word namptA);
|     Word namfrc,i-Name of the Force being added.
|     Word namept,i-Name of the Point of application.
|     Word namptB,i-Name of the direction Point before the Force.
|     Word namptA,i-Name of the direction Point after  the Force.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined Point for namept, or
|     namptB, or namptA are not defined.  A message is printed; no new
|     Force is formed.
|       System.nerror = 4 indicates that the Points named by namptB and
|     namptA are not distinct.  A message is printed; no new Force is
|     formed.
|
|     Comments:
|       Any previously defined Force with the same name is deleted and
|     replaced; a message is printed.
|       System.level <= 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void forcec(Word namfrc, Word namept, Word namptB, Word namptA)
#else
  void forcec(namfrc, namept, namptB, namptA)
  Word namfrc, namept, namptB, namptA;
#endif
{
  Body  *body,  *bdy;
  Point *point, *pointA, *pointB;
  Force *force, *frc;
  Word   nampt;

/* Locate the three Point records and the Body record. */
  if (strcmp(namptB, namptA) == 0) {
    echoc();
    textc("*** The two force direction points may not be the same. ***",
      TRUE);
    System.nerror = 4;
    return;
  }
  strcpy(nampt, namptB);
  pointB = NULL;
  pointA = NULL;
  point  = NULL;
  while (point == NULL) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (point=body->bdyPnt; point; point=point->nxtPnt) {
        if (point->master) {
          if (strcmp(point->name, nampt) == 0) break;
        }
      }
      if (point) break;
    }
    if (point) {
      if (pointB) {
        break;
      } else {
        pointB = pointA;
        pointA = point;
        point  = NULL;
        if (pointB) {
          strcpy(nampt, namept);
        } else {
          strcpy(nampt, namptA);
        }
      }
    } else {
      echoc();
      textc("*** There is no point named '", FALSE);
      textc(nampt, FALSE);
      textc("'. ***", TRUE);
      System.nerror = 3;
      return;
    }
  }

/* Delete any other Force record with the same name. */
  for (bdy=System.sysBdy; bdy; bdy=bdy->nxtBdy) {
    for (force=bdy->bdyFrc; force; force=force->nxtFrc) {
      if (strcmp(force->name, namfrc) == 0) {
        xforc(force);
        echoc();
        textc("*** The previous force named '", FALSE);
        textc(namfrc, FALSE);
        textc("' is redefined. ***", TRUE);
      }
    }
  }

/* Create the new Force record. */
  force = (Force *) malloc(sizeof(Force));
  force->type = FORCE;
  strcpy(force->name, namfrc);
  force->nxtFrc = NULL;
  if (body->bdyFrc) {         /* Add new Force to end of linked list. */
    frc = body->bdyFrc;
    while (frc->nxtFrc) frc = frc->nxtFrc;
    frc->nxtFrc = force;
  } else {
    body->bdyFrc = force;
  }
  force->frcPtA = pointA;
  force->frcPtB = pointB;
  force->frcPtC = point;
  force->kcolor = kdfgeo;
  force->frcVf  = NULL;
  ldnanc((void *) &(force->f));
  if (System.level > 3) System.level = 3;
  return;
}
