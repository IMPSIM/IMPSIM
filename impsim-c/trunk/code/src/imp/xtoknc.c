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
/* xtoknc-01 Jan 00:15 Jan 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Delete the token of specified index from the array in inputc.h.
|
|     Access:
|       (void) xtoknc(int index);
|
|     Error Conditions:
|       Unless 0 <= index < ntokns, no action is taken.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xtoknc(int index)
#else
  void xtoknc(index)
  int index;
#endif
{
  int i;

/* Test for the existence of token k. */
  if ((index >= 0) && (index < ntokns)) {

/* Loop through all higher index tokens. */
    for (i=index+1; i<ntokns; i++) {

/* Copy each token to the next lower index. */
      token[i-1].kind = token[i].kind;
      token[i-1].op   = token[i].op;
      switch (token[i].kind) {
        case TK_CHAR:
          strcpy(token[i-1].data.text, token[i].data.text);
          break;
        case TK_INT:
          token[i-1].data.number = token[i].data.number;
          break;
        case TK_REAL:
          token[i-1].data.word   = token[i].data.word;
          break;
        case TK_VALUE:
          token[i-1].data.value  = token[i].data.value;
          break;
        case TK_FUNC:
          token[i-1].data.f      = token[i].data.f;
      }
    }

/* Reduce the count of total tokens by one. */
    ntokns--;
  }
  return;
}
