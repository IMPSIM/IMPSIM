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
/* mkbdyc-01 Jan 00:25 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Locate or create a Body with a given name.
|
|     Access:
|       (Body *) mkbdyc(Word name);
|     Word name,i-Name of the Body.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  Body *mkbdyc(Word name)
#else
  Body *mkbdyc(name)
  Word name;
#endif
{
  Body *body, *bdy;
  int   i, j;

/* Check for previous use of name. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strncmp(body->name, name, MAXCHR) == 0) goto DONE;
  }

/* Form the new Body record. */
  body = (Body *) malloc(sizeof(Body));
  body->type = BODY;
  strncpy(body->name, name, MAXCHR);
  body->name[MAXCHR] = '\0';
  body->nxtBdy = NULL;
  if (System.sysBdy) {         /* Add new Body to end of linked list. */
    bdy = System.sysBdy;
    while (bdy->nxtBdy) bdy = bdy->nxtBdy;
    bdy->nxtBdy = body;
  } else {
    System.sysBdy = body;
  }
  body->bdySys = &System;
  body->bdySld = NULL;
  body->bdyAxs = NULL;
  body->bdyPnt = NULL;
  body->bdyMas = NULL;
  body->bdyFrc = NULL;
  body->bdyTrq = NULL;
  body->bdyno  = ++System.nbdys;
  body->nslds  = 0;
  body->kcolor = kdfgeo;
  for (i=0; i<3; i++) {
    for (j=0; j<4; j++) {
      body->T0j[i][j] = 0.0;
    }
    body->T0j[i][i] = 1.0;
  }
  ldnanc((void *) &(body->W[0]));
  ldnanc((void *) &(body->A[0]));
  ldnanc((void *) &(body->loopflags));
DONE:
  return(body);
}
