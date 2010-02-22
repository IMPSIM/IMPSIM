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
/* torqec-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add a new Torque record to the System model.
|
|     Access:
|       (void) torqec(Word trqnam, Word nambdy, Word namptB,
|         Word namptA);
|     Word trqnam,i-Name of the Torque being added.
|     Word nambdy,i-Name of the Body of application.
|     Word namptB,i-Name of the direction Point before the Torque.
|     Word namptA,i-Name of the direction Point after  the Torque.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined Body for nambdy, or
|     Point for namptB or namptA, or that the two are not distinct.  A
|     message is printed; no new Torque is formed.
|       System.nerror = 4 indicates that the Points named by namptB and
|     namptA are not distinct.  A message is printed; no new Torque is
|     formed.
|
|     Comments:
|       Any previously defined Torque with the same name is deleted and
|     replaced; a message is printed.
|       System.level <= 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void torqec(Word trqnam, Word nambdy, Word namptB, Word namptA)
#else
  void torqec(trqnam, nambdy, namptB, namptA)
  Word trqnam, nambdy, namptB, namptA;
#endif
{
  Body   *body, *bdy;
  Point  *pointA, *pointB;
  Torque *torque, *trq;
  Word    nampnt;

/* Locate the two Point records. */
  if (strcmp(namptB, namptA) == 0) {
    echoc();
    textc("*** The two direction points may not be the same. ***",
      TRUE);
    System.nerror = 4;
    return;
  }
  strcpy(nampnt, namptB);
  pointB = NULL;
  pointA = NULL;
  while (pointA == NULL) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (pointA=body->bdyPnt; pointA; pointA=pointA->nxtPnt) {
        if (pointA->master) {
          if (strcmp(pointA->name, nampnt) == 0) break;
        }
      }
      if (pointA) break;
    }
    if (pointA) {
      pointB = pointA;
      pointA = NULL;
      if (pointB) {
        strcpy(nampnt, namptA);
      }
    } else {
      echoc();
      textc("*** There is no point named '", FALSE);
      textc(nampnt, FALSE);
      textc("'. ***", TRUE);
      System.nerror = 3;
      return;
    }
  }

/* Locate the Body record. */
  for (bdy=System.sysBdy; bdy; bdy=bdy->nxtBdy) {
    if (strcmp(bdy->name, nambdy) == 0) break;
  }
  if (bdy == NULL) {
    echoc();
    textc("*** There is no body named '", FALSE);
    textc(nambdy, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
    return;
  }

/* Delete any other Torque record with the same name. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
      if (strcmp(torque->name, trqnam) == 0) {
        xtorqc(torque);
        echoc();
        textc("*** The previous torque named '", FALSE);
        textc(trqnam, FALSE);
        textc("' is redefined. ***", TRUE);
      }
    }
  }

/* Create the new Torque record. */
  torque = (Torque *) malloc(sizeof(Torque));
  torque->type = TORQUE;
  strcpy(torque->name, trqnam);
  torque->nxtTrq = NULL;
  if (bdy->bdyTrq) {         /* Add new Torque to end of linked list. */
    trq = body->bdyTrq;
    while (trq->nxtTrq) trq = trq->nxtTrq;
    trq->nxtTrq = torque;
  } else {
    body->bdyTrq = torque;
  }
  torque->trqPtA = pointA;
  torque->trqPtB = pointB;
  torque->trqBdy = bdy;
  torque->kcolor = kdfgeo;
  ldnanc((void *) &(torque->t));
  if (System.level > 3) System.level = 3;
  return;
}
