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
/* readc-01 Jan 00:02 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Free format input routine and parser for the IMP language.
|
|     Access:
|       (void) readc();
|
|     Error Conditions:
|       If an end of file condition is detected, a '$$' or 'return'
|     statement is simulated and a warning message is printed.
|       If more than MXTOKN tokens are found in a single input record,
|     the statement is marked as too long by a warning message, and an
|     error return is made to the calling routine.
|
|     Comments:
|       Up to MAXKOL characters are read for each line of the file.
|       $ signals continuation of the statement on the next line.
|       $$ signals the end of a statement.
|       The last line read is stored in the inbufr character string.
|       Character, integer, and real word forms are accepted, separated
|     by + - * / = ( , : ; @ and blank delimiters.
|       The number of tokens read (<= MXTOKN) is stored in ntokns.
|       The individual values of the tokens are returned in the token[]
|     array with token[].number for integer and token[].word for real.
|     Character strings are stripped and truncated at MAXCHR characters;
|     they are stored in Word format in token[].text.
|       The token[].kind field returns an indicator of the token type
|     (TK_UNDEF for undefined, TK_CHAR for Word, TK_INT for int, TK_REAL
|     for real).
|       The token[].op field returns the level of parentheses and the
|     operator which ended each token.  Level < 0 before the equal sign
|     and > 0 after.  The values of token[].op are treated mod OP_PAREN,
|     and are defined by combinations of OP_UNDEF = -1000, OP_EQUAL = 0,
|     OP_ADD = 1, OP_SUBTRACT = 2, OP_MULTIPLY = 3, OP_DIVIDE = 4,
|     OP_POWER = 5, and OP_PAREN = 20; the factors of OP_PAREN represent
|     levels of nested parentheses.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void readc()
{
  char buffer[MXINBF+1], letrs[MAXCHR+1] = "    ", letter;
  enum Tkntyp kind;
  int  i, kolum, kontnu, ksign, level, lsigns, ndec, ndigit, ndolrs,
    nkol, nletrs, nsign, number;
  real word;

/* Initialize for a new IMP input statement. */
  level  = OP_UNDEF;
  kontnu = -1;
  ksign  = +1;
  ntokns = -1;
  for (i=0; i<MXTOKN; i++) {
    token[i].kind = TK_UNDEF;
    token[i].op   = OP_UNDEF;
  }

/* Initialize for a new line of input. */
_NEWLINE:
  kontnu++;
  kolum  = -1;
  nkol   =  0;
  ndolrs =  0;

/* Read the next line of input. */
  promtc();
  if (bfinc("\0") != 0) {

/* Simulate a return or $$ statement on hitting end of input stream. */
    if (lunitc("read") <= 0) {
      textc("*** $$ statement simulated. ***", TRUE);
    } else {
      textc("*** RETURN statement simulated at end of file. ***", TRUE);
      token[0].kind = TK_CHAR;
      strncpy(token[0].data.text, "return", MAXCHR);
      token[0].data.text[MAXCHR] = '\0';
      ntokns = 1;
    }
    goto _DONE;

/* Recover the next line of input. */
  } else {
    bfgetc(buffer);
    for (i=0; buffer[i]; i++) {            /* Change any non-printing */
/*    if (iscntrl(buffer[i])) buffer[i] = SPACE;*//* chars to blanks. */
      if(buffer[i] < 32) buffer[i] = SPACE;       /* chars to blanks. */
    }
    nkol = min(lenc(buffer), MXKOL);
    buffer[nkol] = '\0';
  }
  if (kontnu > 0) goto _NEWCHR;

/* Initialize for a new token. */
_NEWTOKEN:
  ntokns++;
  if (ntokns >= MXTOKN) {
    ntokns = 0;
    ndolrs = 3;
  }
  kind   = TK_UNKNOWN;
  number = 0;
  lsigns = FALSE;
  nsign  = ksign;
  ksign  = 1;
  nletrs = 0;
  for (i=0; i<MAXCHR; i++) letrs[i] = SPACE;
  letrs[MAXCHR] = '\0';
  token[ntokns].op = level;

/* Initialize for a new character. */
_NEWCHR:
  kolum++;

/* Test for end of line. */
  if (kolum >= nkol) {
    letter = SPACE;
    if (ndolrs == 1) goto _NEWLINE;
    if (ndolrs == 3)
      textc("*** Error:  Statement too long; ignored. ***", TRUE);
    ndolrs = 2;
    goto _ENDTOKEN;
  } else {
    letter = buffer[kolum];
    if (ndolrs != 0) goto _NEWCHR;
  }

/* Test for and ignore ')'. */
  if (letter == ')') {
    token[ntokns].op -= OP_PAREN;
    level -= OP_PAREN;
    goto _NEWCHR;

/* Test for '$' or "$$". */
  } else if (letter == '$') {
    ndolrs = 1;
    if (kolum >= nkol) goto _NEWCHR;
    if (buffer[kolum+1] == '$') ndolrs = 2;
    goto _NEWCHR;

/* Test for ',', ':', or ';' delimiters. */
  } else if ((letter == ',') || (letter == ':') || (letter == ';')) {

/* Test for '('. */
  } else if (letter == '(') {
    level += OP_PAREN;

/* Test for '='. */
  } else if (letter == '=') {
    token[ntokns].op = OP_EQUAL;
    level = OP_EQUAL;

/* Test for '+'. */
  } else if (letter == '+') {
    switch (kind) {
    case TK_CHAR:
    case TK_INT:
    case TK_REAL:
      token[ntokns].op += ((3 - ksign) / 2);
      break;
    case TK_EXP:
      if (lsigns) {
        token[ntokns].op += ((3 - ksign) / 2);
        break;
      } else {
        lsigns = TRUE;
        nsign  = ksign;
        ksign  = 1;
        goto _NEWCHR;
      }
    default:
      nsign = ksign;
      ksign = 1;
      goto _NEWCHR;
    }

/* Test for '-'. */
  } else if (letter == '-') {
    switch (kind) {
    case TK_CHAR:
    case TK_INT:
    case TK_REAL:
      token[ntokns].op += OP_SUBTRACT;
      ksign = -1;
      break;
    case TK_EXP:
      if (lsigns) {
        token[ntokns].op += OP_SUBTRACT;
        ksign = -1;
        break;
      } else {
        lsigns = TRUE;
        nsign  = -1;
        ksign  =  1;
        goto _NEWCHR;
      }
    default:
      nsign = -1;
      ksign =  1;
      goto _NEWCHR;
    }

/* Test for '*'. */
  } else if (letter == '*') {
    token[ntokns].op += OP_MULTIPLY;

/* Test for '/'. */
  } else if (letter == '/') {
    token[ntokns].op += OP_DIVIDE;

/* Test for '@'. */
  } else if (letter == '@') {
    token[ntokns].op += OP_POWER;

/* Test for blank, SPACE. */
  } else if (letter == SPACE) {
    if ((kind == TK_UNKNOWN) || (kolum >= nkol)) goto _NEWCHR;
    if (strspn(&buffer[kolum+1], "+-*/=(,:;@ $)") > 0) goto _NEWCHR;

/* Test for decimal point, '.'. */
  } else if (letter == '.') {
    switch (kind) {
    case TK_CHAR:
      if (nletrs < MAXCHR) letrs[nletrs] = letter;
      nletrs++;
      goto _NEWCHR;
    case TK_REAL:
    case TK_EXP:
      kolum--;
      break;
    default:
      kind = TK_REAL;
      word = (real) number;
      ndec = 0;
      goto _NEWCHR;
    }

/* Test for exponent, 'E' or 'e'. */
  } else if ((letter == 'E') || (letter == 'e')) {
    switch (kind) {
    case TK_CHAR:
      if (nletrs < MAXCHR) letrs[nletrs] = letter;
      nletrs++;
      goto _NEWCHR;
    case TK_INT:
      kind = TK_EXP;
      word = (real) (nsign * number);
      if (nsign == -1) token[ntokns-1].op--;
      nsign = 1;
      number = 0;
      goto _NEWCHR;
    case TK_REAL:
      kind = TK_EXP;
      word *= nsign;
      if (nsign == -1) token[ntokns-1].op--;
      nsign = 1;
      number = 0;
      goto _NEWCHR;
    case TK_EXP:
      kolum--;
      break;
    default:
      kind = TK_CHAR;
      if (nletrs < MAXCHR) letrs[nletrs] = letter;
      nletrs++;
      goto _NEWCHR;
    }

/* Add character if in an alphameric token. */
  } else if (kind == TK_CHAR) {
    if (nletrs < MAXCHR) letrs[nletrs] = letter;
    nletrs++;
    goto _NEWCHR;

/* Test for a numeral. */
/*} else if (isdigit(letter)) { */
  } else if ((letter >= '0') && (letter <= '9')) {
    ndigit = letter - '0';
    switch (kind) {
    case TK_REAL:
      ndec--;
      word += (real) (ndigit * pow(10.0, (double) ndec));
      break;
    case TK_UNKNOWN:
      kind = TK_INT;
    default:
      number = 10 * number + ndigit;
    }
    goto _NEWCHR;

/* Store an unrecognized character as alphameric. */
  } else {
    if (kind == TK_UNKNOWN) {
      kind = TK_CHAR;
      if (nletrs < MAXCHR) letrs[nletrs] = letter;
      nletrs++;
    }
    goto _NEWCHR;
  }

/* Complete a token. */
_ENDTOKEN:
  token[ntokns].kind = kind;
  switch (kind) {
  case TK_UNKNOWN:
    token[ntokns].kind = TK_UNDEF;
    if ((token[ntokns].op % OP_PAREN) == OP_EQUAL)
      token[ntokns].op = min(OP_EQUAL, token[ntokns].op);
    break;
  case TK_CHAR:
    if (nletrs <= MAXCHR) letrs[nletrs] = '\0';
    strncpy(token[ntokns].data.text, letrs, MAXCHR);
    token[ntokns].data.text[MAXCHR] = '\0';
    break;
  case TK_INT:
    token[ntokns].data.number = nsign * number;
    if ((nsign < 0) && ((token[ntokns-1].op % OP_PAREN) == OP_SUBTRACT))
      token[ntokns-1].op--;
    break;
  case TK_REAL:
    token[ntokns].data.word = nsign * word;
    if ((nsign < 0) && ((token[ntokns-1].op % OP_PAREN) == OP_SUBTRACT))
      token[ntokns-1].op--;
    break;
  case TK_EXP:
    token[ntokns].kind = TK_REAL;
    number *= nsign;
    token[ntokns].data.word = word * pow(10.0, (double) number);
  }
  if (ndolrs < 2) goto _NEWTOKEN;
  if (token[ntokns].kind == TK_UNDEF) ntokns--;
_DONE:
  ntokns++;
  return;
}
