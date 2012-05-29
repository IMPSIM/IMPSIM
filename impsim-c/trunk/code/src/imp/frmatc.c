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
/* frmatc-01 Jan 00:16 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Check n tokens of inputc.h beginning with token[index], and
|     convert them into the type shown by kind.
|
|     Access:
|       nerr = (int) frmatc(int index, int n, enum Numtyp kind);
|     int index,i-Index of the first token to be checked.
|     int n,i-Number of tokens to be checked.
|     enum Numtyp kind,i-Flag for the form desired: 
|       kind=TK_CHAR  for token[].data.text   in type Word, 
|       kind=TK_INT   for token[].data.number in type int, 
|       kind=TK_REAL  for token[].data.word   in type real, 
|       kind=TK_VALUE for token[].data.value  in type Value *, 
|       kind=TK_FUNC  for token[].data.f,     or 
|       kind=TK_XYZ   for token[].data.text   to be converted from the 
|         name of a Point record into token[0].word, token[1].word, and
|         token[2].word containing the TK_REAL global position coordin-
|         ates of the named point.
|     int nerr,o-Error flag: set to zero for no error, or set to the
|       token[] index for any irrecoverable format error.
|
|     Error Conditions:
|       System.nerror = 2 indicates an irrecoverable format error in
|     token[nerr].
|
|     Comments:
|       On entry, the values of token[].kind are set according to the
|     input formats found when reading the record in readc(): TK_UNDEF
|     for undefined, TK_CHAR for type Word, TK_INT for type int, or
|     TK_REAL for type real.
|       If kind = TK_XYZ causes the evaluation of a point name into the
|     equivalent position coordinates, then ntokens (the number of
|     tokens in inputc.h) will increase by two.
|       kind = TK_FUNC should not happen when the tokens are first read
|     by readc(), nor by transitions in frmatc().  This condition should
|     only result from the parsing of vcmplc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int frmatc(int index, int n, enum Tkntyp kind)
#else
  int frmatc(index, n, kind)
  int index, n;
  enum Numtyp kind;
#endif
{
  Body  *body;
  Point *point;
  Value *value;
  int    i, j, k;
  Word   string;

  i = index;
  for (j=0; j<n; j++) {
    switch (kind) {
    case TK_CHAR:
      switch (token[i].kind) {
      case TK_CHAR:
        break;
      case TK_INT:
      case TK_REAL:
        token[i].kind = TK_CHAR;
        strcpy(token[i].data.text, "");
        System.nerror = 2;
        echoc();
        textc("*** Expecting alpha for word ", FALSE);
        itextc(i+1);
        textc(". ***", TRUE);
        return(i);
      case TK_VALUE:
        token[i].kind = TK_CHAR;
        strcpy(token[i].data.text, token[i].data.value->name);
        break;
      default:
        token[i].kind = TK_CHAR;
        strcpy(token[i].data.text, "");
      }
      break;
    case TK_INT:
      switch (token[i].kind){
      case TK_CHAR:
        token[i].kind = TK_INT;
        token[i].data.number = 0;
        System.nerror = 2;
        echoc();
        textc("*** Expecting an integer for word ", FALSE);
        itextc(i+1);
        textc(". ***", TRUE);
        return(i);
      case TK_INT:
        break;
      case TK_REAL:
        token[i].kind = TK_INT;
        token[i].data.number = (int) (token[i].data.word + 0.4999999);
        break;
      case TK_VALUE:
        token[i].kind = TK_INT;
        if (isnanc((void *) &token[i].data.value->v)) {
          token[i].data.number = 0;
        } else {
          token[i].data.number =(int)(token[i].data.value->v+0.4999999);
        }
        break;
      default:
        token[i].kind = TK_INT;
        token[i].data.number = 0;
      }
      break;
    case TK_REAL:
      switch (token[i].kind){
      case TK_CHAR:
        token[i].kind = TK_REAL;
        token[i].data.word = 0.0;
        System.nerror = 2;
        echoc();
        textc("*** Expecting a real value for word ", FALSE);
        itextc(i+1);
        textc(". ***", TRUE);
        return(i);
      case TK_INT:
        token[i].kind = TK_REAL;
        token[i].data.word = (real) token[i].data.number;
        break;
      case TK_REAL:
        break;
      case TK_VALUE:
        token[i].kind = TK_REAL;
        if (isnanc((void *) &token[i].data.value->v)) {
          token[i].data.word = 0.0;
        } else {
          token[i].data.word = token[i].data.value->v;
        }
        break;
      default:
        token[i].kind = TK_REAL;
        token[i].data.word = 0.0;
      }
      break;
    case TK_VALUE:
      switch (token[i].kind){
      case TK_INT:
        token[i].kind = TK_REAL;
        token[i].data.word = (real) token[i].data.number;
      case TK_REAL:
      default:
        token[i].kind = TK_REAL;
      case TK_VALUE:
        break;
      case TK_CHAR:
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strncmp(string, "none", MAXCHR) == 0) {
          token[i].kind = TK_VALUE;
          token[i].data.value = NULL;
          break;
        } else {
          value = System.sysVal;
          while (value) {
            if (strcmp(token[i].data.text, value->name) == 0) {
              token[i].kind = TK_VALUE;
              token[i].data.value = value;
              break;
            }
            value = value->nxtVal;
          }
          if (value) break;
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
          System.nerror = 2;
          echoc();
          textc("*** Expecting a real or Value name for word ", FALSE);
          itextc(i+1);
          textc(". ***", TRUE);
          return(i);
        }
      }
      break;
    case TK_XYZ:
      switch (token[i].kind){
      case TK_CHAR:
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (point=body->bdyPnt; point; point=point->nxtPnt) {
            if (strcmp(token[i].data.text, point->name) == 0) {
              if ((ntokns + 2) < MXTOKN) {
                for (k=ntokns-1; k>i; k--) {
                  token[k+2].kind = token[k].kind;
                  switch (token[k].kind) {
                  case TK_INT:
                    token[k+2].data.number = token[k].data.number;
                    break;
                  case TK_REAL:
                    token[k+2].data.word = token[k].data.word;
                    break;
                  case TK_CHAR:
                    strcpy(token[k+2].data.text, token[k].data.text);
                    break;
                  case TK_VALUE:
                    token[k+2].data.value = token[k].data.value;
                    break;
                  }
                }
                ptposc(point, &(token[i].data.word));
                for (k=0; k<3; k++) {
                  token[i].kind = TK_REAL;
                  i++;
                }
              } else {
                abortc();
              }
            }
          }
          if (point) break;
        }
        if (body) break;
        System.nerror = 2;
        echoc();
        textc("*** Expecting a point name or 3 real values for word ",
          FALSE);
        itextc(i+1);
        textc(". ***", TRUE);
        return(i);
      case TK_UNDEF:
      case TK_INT:
      case TK_REAL:
        for (k=i; k<i+3; k++) {
          switch (token[k].kind) {
          case TK_UNDEF:
            token[k].kind = TK_REAL;
            token[k].data.word = 0.0;
            continue;
          case TK_INT:
            token[k].kind = TK_REAL;
            token[k].data.word = (real) token[k].data.number;
            continue;
          case TK_REAL:
            continue;
          default:
            System.nerror = 2;
            echoc();
            textc("*** Expecting a real value for word ", FALSE);
            itextc(k+1);
            textc(". ***", TRUE);
            return(k);
          }
        }
        i++;
        i++;
        break;
      default:
        System.nerror = 2;
        echoc();
        textc("*** Expecting a point name or 3 real values for word ",
          FALSE);
        itextc(i+1);
        textc(". ***", TRUE);
        return(i);
      }
    }
    i++;
  }
  return(0);
}
