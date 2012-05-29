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
/* sprngc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add a new Spring record to the System model.
|
|     Access:
|       (void) sprngc(Word spgnam, Word namptB, Word namptA);
|     Word spgnam,i-Name of the Spring being added.
|     Word namptB,i-Name of the Point before the Spring.
|     Word namptA,i-Name of the Point after  the Spring.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined Point for namptB or
|     namptA, or that the two are not distinct.  A message is printed;
|     no new Spring is formed.
|
|     Comments:
|       Any previously defined Spring with the same name is deleted and
|     replaced; a message is printed.
|       System.level <= 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void sprngc(Word spgnam, Word namptB, Word namptA)
#else
  void sprngc(spgnam, namptB, namptA)
  Word spgnam, namptB, namptA;
#endif
{
  Body   *body;
  Point  *pointA, *pointB;
  Spring *spring, *spg;
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

/* Delete any other Spring record with the same name. */
  for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
    if (strcmp(spring->name, spgnam) == 0) {
      xspngc(spring);
      echoc();
      textc("*** The previous spring named '", FALSE);
      textc(spgnam, FALSE);
      textc("' is replaced. ***", TRUE);
    }
  }

/* Create the new Spring record. */
  spring = (Spring *) malloc(sizeof(Spring));
  spring->type = SPRING;
  strcpy(spring->name, spgnam);
  spring->nxtSpg = NULL;
  if (System.sysSpg) {       /* Add new Spring to end of linked list. */
    spg = System.sysSpg;
    while (spg->nxtSpg) spg = spg->nxtSpg;
    spg->nxtSpg = spring;
  } else {
    System.sysSpg = spring;
  }
  spring->spgPtA = pointA;
  spring->spgPtB = pointB;
  spring->kcolor = kdfgeo;
  spring->spgVk  = NULL;
  ldnanc((void *) &(spring->k));
  spring->spgVfl = NULL;
  ldnanc((void *) &(spring->freel));
  if (System.level > 3) System.level = 3;
  return;
}
