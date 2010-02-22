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
/* contac-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Add a Contact record between two specified Solid shapes to the
|     system model.
|
|     Access:
|       (void) contac(Word cntnam, Word sldbfr, Word sldaft);
|     Word cntnam,i-Name of the new Contact.
|     Word sldbfr,i-Name of the Solid preceeding the new Contact.
|     Word sldaft,i-Name of the Solid following  the new Contact.
|
|     Error Conditions:
|       System.nerror = 3 indicates that either sldbfr or sldaft is
|     undefined.  A diagnostic message is printed and return is made
|     with no new Contact record formed.
|       System.nerror = 5 indicates that sldbfr and sldaft both refer to
|     solids of the same Body.  A message is printed and return is made
|     with no new Contact record formed.
|
|     Comments:
|       If cntnam refers to a Contact which already exists, the former
|     Contact is deleted and a new Contact is formed.  Any former data
|     are lost.  A message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void contac(Word cntnam, Word sldbfr, Word sldaft)
#else
  void contac(cntnam, sldbfr, sldaft)
  Word cntnam, sldbfr, sldaft;
#endif
{
  Body    *bodyA,  *bodyB;
  Contact *contct, *cnt;
  Solid   *solidA, *solidB;
  Word     sldname;

/* Locate the Solid and the Body records. */
  strcpy(sldname, sldbfr);
  bodyB  = NULL;
_2:
  for (bodyA=System.sysBdy; bodyA; bodyA=bodyA->nxtBdy) {
    for (solidA=bodyA->bdySld; solidA; solidA=solidA->nxtSld) {
      if (strcmp(solidA->name, sldname) == 0) {
        break;
      }
    }
    if (solidA) {
      if (bodyB) {
        break;
      } else {
        solidB = solidA;
        bodyB  = bodyA;
        strcpy(sldname, sldaft);
        goto _2;
      }
    }
  }
  if (bodyA == NULL) {
    echoc();
    textc("*** Solid shape '", FALSE);
    textc(sldname, FALSE);
    textc("' is not defined. ***", TRUE);
    System.nerror = 3;
    goto DONE;
  }

/* Check for a self loop. */
  if (bodyA == bodyB) {
    echoc();
    textc("*** Error: A contact cannot connect a body to itself. ***",
      TRUE);
    System.nerror = 5;
    goto DONE;
  }

/* Delete any previous Contact with the same name. */
  for (contct=System.sysCnt; contct; contct=contct->nxtCnt) {
    if (strcmp(contct->name, cntnam) == 0) {
      xcntc(contct);
      echoc();
      textc("*** The former contact '", FALSE);
      textc(cntnam, FALSE);
      textc("' is replaced. ***", TRUE);
      break;
    }
  }

/* Form the new Contact record. */
  contct = (Contact *) malloc(sizeof(Contact));
  contct->type = CONTACT;
  strcpy(contct->name, cntnam);
  contct->nxtCnt = NULL;
  if (System.sysCnt) {      /* Add new Contact to end of linked list. */
    cnt = System.sysCnt;
    while (cnt->nxtCnt) cnt = cnt->nxtCnt;
    cnt->nxtCnt = contct;
  } else {
    System.sysCnt = contct;
  }
  contct->cnSldA = solidA;
  bsphrc(solidA);
  contct->cnSldB = solidB;
  bsphrc(solidB);
  contct->ptrA   = NULL;
  contct->ptrB   = NULL;
  contct->cntypA = CN_UNDEF;
  contct->cntypB = CN_UNDEF;
  contct->sepplane = FALSE;
  contct->nvxs   = 0;
  contct->numcr  = 0;
  ldnanc((void *) &(contct->timex));
  contct->rest_n = 1.0;
  contct->rest_t = 0.0;
  contct->rest_m =-1.0;
  contct->rest_mn= 0.0;
  contct->mu     = 0.0;
  contct->Rp     = 0.0;
DONE:
  return;
}
