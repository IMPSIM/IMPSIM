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
/* zeroc-01 Jan 00:15 Jan 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Set or reset a specified tolerance to a specified value.
|
|     Access:
|       (void) zeroc(Word kind, Token tkn[]);
|     Word kind,i-Keyword indicating the tolerance specified.
|     Token tkn[],i-Array of Tokens containing tolerance values.
|
|     Error Conditions:
|       System.nerror = 3 indicates an unrecognized keyword for kind; a
|     message is printed and no tolerance values are changed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void zeroc(Word kind, Token tkn[])
#else
  void zeroc(kind, tkn)
  Word  kind;
  Token tkn[];
#endif
{

/* Treat a zero(data) statement. */
  lcasec(kind);
  if (strncmp(kind, "data", MAXCHR) == 0) {
    System.dtola = fabs(tkn[0].data.word/System.ascale);
    System.dtoll = fabs(tkn[0].data.word);

/* Treat a zero(position) statement. */
  } else if (strncmp(kind, "position", MAXCHR) == 0) {
    System.ptola = fabs(tkn[0].data.word/System.ascale);
    System.ptoll = fabs(tkn[0].data.word);
    if (tkn[1].kind == TK_INT) {
      if (tkn[1].data.number > 0) System.cn = abs(tkn[1].data.number);
    }

/* Treat a zero(equilibrium) statement. */
  } else if (strncmp(kind, "equilibrium", MAXCHR) == 0) {
    System.etola = fabs(tkn[0].data.word/System.ascale);
    System.etoll = fabs(tkn[0].data.word);
    if (tkn[1].kind == TK_INT) {
      if (tkn[1].data.number > 0) System.en = abs(tkn[1].data.number);
    }

/* Treat a zero(indet) statement. */
  } else if (strncmp(kind, "indet", MAXCHR) == 0) {
    System.fintol = fabs(tkn[0].data.word);

/* Treat a zero(inertia) statement. */
  } else if (strncmp(kind, "inertia", MAXCHR) == 0) {
    System.dytol = fabs(tkn[0].data.word);

/* Treat a zero(spring) statement. */
  } else if (strncmp(kind, "spring", MAXCHR) == 0) {
    System.fktol = fabs(tkn[0].data.word);

/* Treat a zero(force) statement. */
  } else if (strncmp(kind, "force", MAXCHR) == 0) {
    System.ferr = fabs(tkn[0].data.word);
    if (tkn[1].kind == TK_INT) {
      System.pferr = fabs(tkn[1].data.number / 100.0);
    } else if (tkn[1].kind == TK_REAL) {
      System.pferr = fabs(tkn[1].data.word / 100.0);
    }

/* Treat a zero(system) statement. */
  } else if (strncmp(kind, "system", MAXCHR) == 0) {
    System.fjtol = fabs(tkn[0].data.word);

/* Treat a zero(zero) statement. */
  } else if (strncmp(kind, "zero", MAXCHR) == 0) {
    System.zero = fabs(tkn[0].data.word);

/* Treat an unrecognized type of zero statement. */
  } else {
    echoc();
    textc("*** This type of ZERO statement is not defined. ***", TRUE);
    System.nerror = 3;
  }
  return;
}
