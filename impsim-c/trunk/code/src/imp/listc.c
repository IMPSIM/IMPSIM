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
/* listc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Create a RQ_LIST type of Request record.
|
|     Access:
|       (void) listc(Word kind, Token *names, int n);
|     Word kind,i-The type of analysis output for this Request.
|     Token names[n],i-An array of Tokens specifying Request items.
|     int n,i-Number of Tokens in the names array.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined kind of analysis.
|       System.nerror = 4 indicates that the list file could not be
|     opened.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void listc(Word kind, Token *names, int n)
#else
  void listc(kind, names, n)
  Word   kind;
  Token *names;
  int    n;
#endif
{
  Request *reqest, *rqst;
  enum Outtyp type;
  char newid[MXFLCH + 1];
  int  i, lun;

/* Open the list file if not already open. */
  if (lunfil[0] <= 0) {
    lun = lunitc("file");
    newid[0] = '\0';
    fnamec(idfile[0], newid);
    if ((newid[0] == '\0') || (newid[0] == '!')) {
      echoc();
      lunfil[0] = 0;
      System.nerror = 4;
      return;
    }
    streams[lun] = fopen(newid, "w+");
    if (streams[lun] == NULL) {
      echoc();
      textc("*** The LIST file cannot be opened. ***", TRUE);
      lunfil[0] = 0;
      System.nerror = 4;
      return;
    }
    strcpy(idfile[0], newid);
    lunfil[0] = lun;
  }

/* Check the kind of LIST request statement. */
  lcasec(kind);
  if (strncmp(kind, "value", MAXCHR) == 0) {
    type = OT_VAL;
  } else if (strncmp(kind, "position", MAXCHR) == 0) {
    type = OT_POS;
  } else if (strncmp(kind, "velocity", MAXCHR) == 0) {
    type = OT_VEL;
  } else if (strncmp(kind, "acceleration", MAXCHR) == 0) {
    type = OT_ACC;
  } else if (strncmp(kind, "force", MAXCHR) == 0) {
    type = OT_FORC;
  } else if (strncmp(kind, "dynamics", MAXCHR) == 0) {
    type = OT_DYN;
  } else {
    type = OT_UNDEF;
    echoc();
    textc("*** The LIST '", FALSE);
    textc(kind, FALSE);
    textc("' type of request is not defined. ***", TRUE);
    System.nerror = 3;
    return;
  }

/* Create the new request record. */
  reqest = (Request *) malloc(sizeof(Request));
  reqest->type = REQUEST;
  reqest->nxtReq = NULL;
  if (System.sysReq) {      /* Add new Request to end of linked list. */
    rqst = System.sysReq;
    while (rqst->nxtReq) rqst = rqst->nxtReq;
    rqst->nxtReq = reqest;
  } else {
    System.sysReq = reqest;
  }
  reqest->reqtyp = RQ_LIST;
  reqest->outtyp = type;
  reqest->nitems = n;
  reqest->items  = (Token *) calloc( n, sizeof(Token));
  for (i=0; i<n; i++) {
    reqest->items[i].kind = names[i].kind;
    reqest->items[i].op   = names[i].op;
    switch (names[i].kind) {
    case TK_INT:
      reqest->items[i].data.number = names[i].data.number;
      break;
    case TK_REAL:
      reqest->items[i].data.word = names[i].data.word;
      break;
    case TK_CHAR:
      strcpy(reqest->items[i].data.text, names[i].data.text);
      break;
    default:
      reqest->items[i].kind = TK_UNDEF;
      strcpy(reqest->items[i].data.text, "");
    }
  }
  return;
}
