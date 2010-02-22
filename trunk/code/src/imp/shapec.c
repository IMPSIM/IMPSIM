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
/* shapec-01 Jan 00:30 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Create one or more Solids on a specified Body.
|
|     Access:
|       (void) shapec(Word bdynam, Token *names, int n);
|     Word  bdynam,  i-Name of the Body for these Solid shapes.
|     Token names[n],i-Array of Tokens specifying Solid shape names.
|     int   n,       i-Number of Tokens in the names array.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If bdynam[0] is '\0' then the solid names[] are set to orphans.
|       If bdynam does not refer to a current Body record, a new Body of
|     the specified name is formed.
|       If names[i] refers to a Solid on the Body named bdynam no action
|     is taken.  If names[i] refers to a Solid on the list of orphan
|     Bodies, then that Solid is moved to the Body named bdynam.  If
|     names[i] is found as a Solid on some other Body, then it is moved
|     to the Body named bdynam.  if names[i] does not fit any of these
|     conditions, then names[i] is ignored; a message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void shapec(Word bdynam, Token *names, int n)
#else
  void shapec(bdynam, names, n)
  Word   bdynam;
  Token *names;
  int    n;
#endif
{
  Body  *body, *bdy;
  Solid *solid, *sldbfr;
  int    i;

/* Locate or create the named Body record. */
  if (bdynam == '\0') {
    body = NULL;
  } else {
    body = mkbdyc(bdynam);
  }

/* Locate each named Solid. */
  for (i=0; i<n; i++) {

/* Look on the named body. */
    for (solid=body->bdySld; solid; solid=solid->nxtSld) {
      if(strcmp(names[i].data.text, solid->name) == 0) goto NEXT;
    }

/* Look through all Solids on all Bodies. */
    for (bdy=System.sysBdy; bdy; bdy=bdy->nxtBdy) {
      for (solid=bdy->bdySld; solid; solid=solid->nxtSld) {
        if(strcmp(names[i].data.text, solid->name) == 0) {

/* Move the Solid to the named Body. */
          if (bdy->bdySld == solid) {
            bdy->bdySld = solid->nxtSld;
          } else {
            sldbfr = bdy->bdySld;
            while (sldbfr->nxtSld != solid) sldbfr = sldbfr->nxtSld;
            sldbfr->nxtSld = solid->nxtSld;
          }
          bdy->nslds--;
          if (body) {
            if (body->bdySld) {
              sldbfr = body->bdySld;
              while (sldbfr->nxtSld) sldbfr = sldbfr-> nxtSld;
              sldbfr->nxtSld = solid;
            } else {
              body->bdySld = solid;
            }
            solid->sldBdy = body;
            body->nslds++;
          } else {
            if (System.sysSld) {
              sldbfr = System.sysSld;
              while (sldbfr->nxtSld) sldbfr = sldbfr->nxtSld;
              sldbfr->nxtSld = solid;
            } else {
              System.sysSld = solid;
            }
            solid->sldBdy = NULL;
          }
          solid->nxtSld = NULL;
          goto NEXT;
        }
      }
    }

/* Look through orphan Solids. */
    for (solid=System.sysSld; solid; solid=solid->nxtSld) {
      if(strcmp(names[i].data.text, solid->name) == 0) {

/* Move the Solid to the named Body. */
        if (body) {
          if (System.sysSld == solid) {
            System.sysSld = solid->nxtSld;
          } else {
            sldbfr = System.sysSld;
            while (sldbfr->nxtSld != solid) sldbfr = sldbfr->nxtSld;
            sldbfr->nxtSld = solid->nxtSld;
          }
          sldbfr = body->bdySld;
          if (sldbfr) {
            while (sldbfr->nxtSld) sldbfr = sldbfr-> nxtSld;
            sldbfr->nxtSld = solid;
          } else {
            body->bdySld = solid;
          }
          solid->nxtSld = NULL;
          solid->sldBdy = body;
          body->nslds++;
        }
        goto NEXT;
      }
    }

/* Named Solid is not found. */
    echoc();
    textc("*** Error: Solid ", FALSE);
    textc(names[i].data.text, FALSE);
    textc(" is not found.  Ignored. ***", TRUE);
    System.nerror = 0;      
NEXT:;
  }
  return;
}
