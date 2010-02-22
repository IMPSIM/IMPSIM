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
/* damprc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add a new Damper record to the System model.
|
|     Access:
|       (void) damprc(Word dmpnam, Word namptB, Word namptA);
|     Word dmpnam,i-Name of the Damper being added.
|     Word namptB,i-Name of the Point before the Damper.
|     Word namptA,i-Name of the Point after  the Damper.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined Point for namptB or
|     namptA, or that the two are not distinct.  A message is printed;
|     no new Damper is formed.
|
|     Comments:
|       Any previously defined Damper with the same name is deleted and
|     replaced; a message is printed.
|       System.level <= 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void damprc(Word dmpnam, Word namptB, Word namptA)
#else
  void damprc(dmpnam, namptB, namptA)
  Word dmpnam, namptB, namptA;
#endif
{
  Body   *body;
  Damper *damper, *dmp;
  Point  *pointA, *pointB;
  Word    namept;

/* Locate the two Point records. */
  if (strcmp(namptB, namptA) == 0) {
    echoc();
    textc("*** The two endpoints may not be the same. ***", TRUE);
    System.nerror = 3;
    return;
  }
  strcpy(namept, namptB);
  pointB = NULL;
  pointA = NULL;
  while (pointA == NULL) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (pointA=body->bdyPnt; pointA; pointA=pointA->nxtPnt) {
        if (pointA->master) {
          if (strcmp(pointA->name, namept) == 0) break;
        }
      }
      if (pointA) break;
    }
    if (pointA) {
      if (pointB) {
        break;
      } else {
        pointB = pointA;
        pointA = NULL;
        strcpy(namept, namptA);
      }
    } else {
      echoc();
      textc("*** There is no point named '", FALSE);
      textc(namept, FALSE);
      textc("'. ***", TRUE);
      System.nerror = 3;
      return;
    }
  }

/* Delete any other Damper record with the same name. */
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (strcmp(damper->name, dmpnam) == 0) {
      xdmprc(damper);
      echoc();
      textc("*** The previous damper named '", FALSE);
      textc(dmpnam, FALSE);
      textc("' is replaced. ***", TRUE);
    }
  }

/* Create the new Damper record. */
  damper = (Damper *) malloc(sizeof(Damper));
  damper->type = DAMPER;
  strcpy(damper->name, dmpnam);
  damper->nxtDmp = NULL;
  if (System.sysDmp) {       /* Add new Damper to end of linked list. */
    dmp = System.sysDmp;
    while (dmp->nxtDmp) dmp = dmp->nxtDmp;
    dmp->nxtDmp = damper;
  } else {
    System.sysDmp = damper;
  }
  damper->dmpPtA = pointA;
  damper->dmpPtB = pointB;
  damper->kcolor = kdfgeo;
  damper->dmpVc  = NULL;
  ldnanc((void *) &(damper->c));
  ldnanc((void *) &(damper->ol));
  if (System.level > 3) System.level = 3;
  return;
}
