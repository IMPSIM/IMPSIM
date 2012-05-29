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
/* vcmplc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Compile and store a Value expression.
|
|     Access:
|       value = (Value *) vcmplc(Word name);
|     Word name,i-Name to be assigned to the Value record.
|     Value *value,o-Pointer returned for the Value record formed.
|
|     Error Conditions:
|       System.nerror != 0 indicates a format error in the input VALUE
|     expression.  An appropriate diagnostic message is printed.
|
|     Comments:
|       It is assumed that readc() has been called and that inputc.h
|     contains the tokens defining the VALUE expression.
|       Any previously defined Value expression of the same name is
|     redefined.  A warning message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  Value *vcmplc(Word name)
#else
  Value *vcmplc(name)
  Word name;
#endif
{
  Value *queue, *v, *val, *value, *vl;
  Word  string;
  char *chrptr, *fileid, *inbfr;
  int   i, imax, imin, j, lop, n, nmax, nmin;

/* Prevent redefinition of keywords. */
  strcpy(string, name);
  ucasec(string);
  if ((strcmp(string, "PI") == 0) || (strcmp(string, "T") == 0) ||
    (strcmp(string, "TIME") == 0)) {
    echoc();
    textc("*** Keyword '", FALSE);
    textc(name, FALSE);
    textc("' cannot be redefined. ***", TRUE);
    System.nerror = 3;
    return(NULL);
  }

/* Delete any previous Value of the same name. */
  for (val=System.sysVal; val; val=val->nxtVal) {
    if (strcmp(name, val->name) == 0) {
      xvaluc(val);
      echoc();
      textc("*** Previous definition of VALUE(", FALSE);
      textc(name, FALSE);
      textc(") is deleted. ***", TRUE);
      break;
    }
  }

/* Create the new Value record. */
  value = (Value *) malloc(sizeof(Value));
  value->type = VALUE;
  strcpy(value->name, name);
  value->nxtVal = NULL;
  if (System.sysVal) {        /* Add new Value to end of linked list. */
    val = System.sysVal;
    while (val->nxtVal) val = val->nxtVal;
    val->nxtVal = value;
  } else {
    System.sysVal = value;
  }
  for (i=0; i<4; i++) {
    value->arg[i] = NULL;
  }
  value->f    = F_UNDEF;
  ldnanc((void *) &(value->v));
  ldnanc((void *) &(value->d1));
  ldnanc((void *) &(value->d2));

/* Obtain fileid for a TABLE function. */
  inbfr = (char *) malloc(MXKOL+1);
  strcpy(inbfr, inbufr);
  ucasec(inbfr);
  if (chrptr = strstr(inbfr, "TABL")) {
    fileid = strstr(chrptr, ":");
    if (fileid == NULL) {
      echoc();
      textc("*** There is no colon(:) in this TABLE statement. ***",
        TRUE);
      goto _ERROR;
    } else {
      fileid += strspn(fileid, ": ");
      chrptr = fileid;
      while (lenc(chrptr) > 0) {   /* Remove fileid from token count. */
        chrptr += strcspn(chrptr, "+-*/=(,:;@ ");
        ntokns--;
        chrptr += strspn(chrptr, " ");
        if (strspn(chrptr, "+-*/(,:;@")) chrptr++;
        chrptr += strspn(chrptr, " ");
      }
      strcpy(inbfr, inbufr);  /* Restore case sensitivity for fileid. */
    }
  }

/* Search for both ends of the Value expression. */
  nmin = -1;
  nmax = ntokns;
  for (i=0; i<ntokns; i++) {
    if (token[i].op >= 0) {
      nmin = i;
      break;
    } else {
      token[i].op = OP_UNDEF;
    }
  }
  if (nmin < 0) {
    echoc();
    textc("*** There is no equal sign (=) in this statement. ***",TRUE);
    goto _ERROR;
  }

/* Check for unbalanced parentheses. */
  if (token[nmax-1].op != 0) {
    echoc();
    textc("*** This statement has unbalanced parentheses. ***", TRUE);
    goto _ERROR;
  }

/* Replace constants and Value names by pointers to Value records. */
  for (i=nmin; i<nmax; i++) {
    if (token[i].kind == TK_CHAR) {
      strcpy(string, token[i].data.text);
      ucasec(string);
      if (strcmp(string, "T") == 0) {
        strncpy(string, "TIME", MAXCHR);
        string[MAXCHR] = '\0';
      }
      if (strncmp(string, "ABS", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_ABS;
      } else if (strncmp(string, "ACCELERATION", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_ACCEL;
      } else if (strncmp(string, "ACOS", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_ACOS;
      } else if (strncmp(string, "ASIN", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_ASIN;
      } else if (strncmp(string, "ATAN", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_ATAN;
      } else if (strncmp(string, "COS", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_COS;
      } else if (strncmp(string, "EXP", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_EXP;
      } else if (strncmp(string, "FORCE", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_FORCE;
      } else if (strncmp(string, "IF", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_IF;
      } else if (strncmp(string, "LOG", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_LOG;
      } else if (strncmp(string, "LOG10", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_LOG10;
      } else if (strncmp(string, "POSITION", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_POSITION;
      } else if (strncmp(string, "SIN", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_SIN;
      } else if (strncmp(string, "SQRT", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_SQRT;
      } else if (strncmp(string, "TABLE", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_TABLE;
      } else if (strncmp(string, "TAN", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_TAN;
      } else if (strncmp(string, "USER", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_USER;
      } else if (strncmp(string, "VELOCITY", MAXCHR) == 0) {
        token[i].kind   = TK_FUNC;
        token[i].op    += 6;
        token[i].data.f = F_VELOCITY;
      } else {
        for (val=System.sysVal; val; val=val->nxtVal) {
          if (strncmp(token[i].data.text, val->name, MAXCHR) == 0) {
            token[i].kind       = TK_VALUE;
            token[i].data.value = val;
            break;
          }
        }
      }
    } else if (token[i].kind == TK_UNDEF) {
      continue;

/* Identify any numeric values already stored as constants. */
    } else {
      frmatc(i, 1, TK_REAL);
      if (System.nerror != 0) goto _ERROR;
      for (val=System.sysVal; val; val=val->nxtVal) {
        if (val->f == F_CONST) {
          if (!isnanc((void *) &val->v)) {
            if (val->v == token[i].data.word) {
              token[i].kind       = TK_VALUE;
              token[i].data.value = val;
              break;
            }
          }
        }
      }
    }
    if (token[i].kind == TK_VALUE) continue;

/* Store constants. */
    if ((token[i].kind == TK_CHAR) || (token[i].kind == TK_REAL)) {
      val = (Value *) malloc(sizeof(Value));
      strcpy(val->name, "");
      val->type = VALUE;
      val->nxtVal = NULL;
      if (System.sysVal) {
        v = System.sysVal;
        while (v->nxtVal) v = v->nxtVal;
        v->nxtVal = val;        /* Add new Value to end of linked list. */
      } else {
        System.sysVal = val;
      }
      for (j=0; j<4; j++) {
        val->arg[j] = NULL;
      }
      val->f  = F_CONST;
      ldnanc((void *) &(val->v));
      val->d1 = 0.0;
      val->d2 = 0.0;
      switch (token[i].kind) {
      case TK_CHAR:
        strcpy(val->name, token[i].data.text);
        if (strcmp(string, "PI") == 0) {
          strcpy(val->name, "PI");
          val->v = PI;
        } else if (strcmp(string, "TIME") == 0) {
          val->f  = F_TIME;
          val->d1 = 1.0;
        }
        break;
      case TK_REAL:
        val->v = token[i].data.word;
        break;
      }
      token[i].kind       = TK_VALUE;
      token[i].data.value = val;
    }
  }

/* Compress out any null operations. */
_COMPRESS:
  for (i=nmin; i<nmax; i++) {
    if ((token[i].kind == TK_UNDEF) && (token[i].op <= 0)) {
      for (j=i; j<ntokns; j++) {
        token[j].kind = token[j+1].kind;
        token[j].op   = token[j+1].op;
        switch (token[j].kind) {
        case TK_CHAR:
          strcpy(token[j].data.text, token[j+1].data.text);
          break;
        case TK_INT:
          token[j].data.number = token[j+1].data.number;
          break;
        case TK_REAL:
        default:
          token[j].data.word = token[j+1].data.word;
          break;
        case TK_VALUE:
          token[j].data.value = token[j+1].data.value;
        }
      }
      ntokns--;
      token[ntokns].kind = TK_UNDEF;
      token[ntokns].op   = 0;
      ldnanc((void *) &(token[ntokns].data.word));
      nmax--;
      if (nmax <= nmin) goto _MESSAGE;
      goto _COMPRESS;
    }
  }

/* Determine the highest priority operation. */
  if ((nmax == (nmin+2)) && (token[nmin].op == OP_EQUAL)) goto _FINISH;
  n = nmin;
  lop = OP_UNDEF;
  for (i=nmin; i<nmax; i++) {
    if (token[i].op > lop) {
      lop = token[i].op;
      n   = i;
    }
  }
  if (lop < 0) goto _MESSAGE;
  lop = lop % OP_PAREN;
  if (lop == OP_EQUAL) {
    token[n].op = OP_EQUAL;
    goto _COMPRESS;

/* Store an arithmetic function. */
  } else if (lop != 6) {
    imin = n;
    imax = n + 1;

/* Store a function. */
  } else {
    lop = token[n].data.f;
    imin = n + 1;
    switch (lop) {
    case F_ABS:
    case F_ACOS:
    case F_ASIN:
    case F_COS:
    case F_EXP:
    case F_LOG:
    case F_LOG10:
    case F_SIN:
    case F_SQRT:
    case F_TABLE:
    case F_TAN:
    case F_USER:
      imax = 1;
      break;
    case F_ACCEL:
    case F_ATAN:
    case F_FORCE:
    case F_POSITION:
    case F_VELOCITY:
      imax = 2;
      break;
    case F_IF:
      imax = 4;
      break;
    default:
      goto _MESSAGE;
    }
    imax += n;
  }
  val = (Value *) malloc(sizeof(Value));
  val->type = VALUE;
  strcpy(val->name, "");
  val->nxtVal = NULL;
  if (System.sysVal) {
    v = System.sysVal;
    while (v->nxtVal) v = v->nxtVal;
    v->nxtVal = val;            /* Add new Value to end of linked list. */
  } else {
    System.sysVal = val;
  }
  for (i=0; i<4; i++) {
    val->arg[i] = NULL;
  }
  val->f  = lop;
  ldnanc((void *) &(val->v));
  val->d1 = 0.0;
  val->d2 = 0.0;
  lop = token[imax].op;
  for (i=imin; i<=imax; i++) {
    if (token[i].kind == TK_VALUE) {
      val->arg[i-imin] = token[i].data.value;
    } else {
      goto _MESSAGE;
    }
    token[i].kind = TK_UNDEF;
    token[i].op   = OP_UNDEF;
    ldnanc((void *) &(token[i].data.word));
  }
  token[n].kind       = TK_VALUE;
  token[n].op         = lop;
  token[n].data.value = val;
  if (val->f == F_TABLE) {
    tablec(fileid, val);
    if (System.nerror) goto _ERROR;
  }
  goto _COMPRESS;

/* Finish storing the expression. */
_FINISH:
  if (token[nmin].kind != TK_VALUE) goto _MESSAGE;
  value->f               = F_EQUAL;
  value->arg[0]          = token[nmax-1].data.value;
  token[nmin].kind       = TK_VALUE;
  token[nmin].op         = OP_UNDEF;
  token[nmin].data.value = value;

/* Reorder for sequential evaluation. */
  if (System.sysVal == value) {
    System.sysVal = value->nxtVal;
  } else {
    for (v=System.sysVal; v; v=v->nxtVal) {
      if (v->nxtVal == value) {
        v->nxtVal = value->nxtVal;
        break;
      }
    }
  }
  value->nxtVal = NULL;
  queue = value;
_QUEUE:
  if (queue) {
    val = queue;
_SORT:
    for (vl=System.sysVal; vl; vl=vl->nxtVal) {
      for (i=0; i<4; i++) {
        if (vl->arg[i] == val) {
          for (v=System.sysVal; v; v=v->nxtVal) {
            if (v->nxtVal == vl) {
              v->nxtVal = vl->nxtVal;
              vl->nxtVal = queue;
              queue = vl;
              goto _SORT;
            }
          }
        }
      }
    }
    vl = System.sysVal;
    while (vl->nxtVal) vl = vl->nxtVal;
    queue = val->nxtVal;
    vl->nxtVal = val;
    val->nxtVal = NULL;
    goto _QUEUE;
  }
  goto _RETURN;

/* Print a diagnostic message. */
_MESSAGE:
  echoc();
  textc("*** There is a syntax error in this statement. ***", TRUE);
_ERROR:
  System.nerror = 4;
  xvaluc(value);
  value = NULL;
_RETURN:
  free (inbfr);
  return(value);
}
