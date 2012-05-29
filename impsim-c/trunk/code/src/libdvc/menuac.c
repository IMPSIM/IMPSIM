/* ------------------------------------------------------------------ */
/* menuac-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Prompt the user with a command line (prompt) and accept a user
|     input from the keyboard.  This user input is compared against the
|     global, header, and menu options stored.  Minimum match spelling
|     is sufficient.  The index of the option which matches is returned.
|
|     Access:
|       nchosn = (int) menuac();
|     int nchosn,o-Number of the menu option matched.
|
|     Error Conditions:
|       menuac() returns -1 for a null input, and 0 for an ambiguous or
|     unrecognized input, or for improperly ordered options.
|       In noninteractive use, menuac() always returns nchosn = 0.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The header and menu lists must be upper-case and must be stored
|     in lexically increasing order.
|       If a header option is picked, then its number + 100 is returned.
|       If a global option is picked, then its number + 200 is returned.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
int menuac()
{
  char choice[9];
  int  high, iglobl, lex, low, mid, nchars;
 
/* Treat non-interactive use. */
  if (!intact) return(0);
 
/* Prompt user and get response. */
  textc(header[khdr-1], FALSE);
  textc(": > ", FALSE);
  bfinc(" ");
  bfgetc(choice);
  stripc(choice);
  nchars = lenc(choice);
  choice[nchars] = '\0';
  ucasec(choice);
 
/* Treat a null response. */
  if (choice[0] == '\0') return(-1);

/* Check for a global option. */
  for (iglobl=0; iglobl<MXGLOBAL; iglobl++) {
    lex = strncmp(choice, global[iglobl], nchars);
    if (lex == 0) return(iglobl + 201);
  }
 
/* Binary search of headers. */
  low  = 0;
  high = nhdrs;
  while (high > low){
    mid = (high + low) / 2;
    lex = strncmp(choice, header[mid], nchars);
    if (lex > 0) {
      low  = mid + 1;
    } else if (lex < 0){
      high = mid;
    } else {
      break;
    }
  }
  mid = (high + low) / 2;
 
/* If pick is not a header; binary search the menu options. */
  if (strncmp(choice, header[mid], nchars)) {
    low  = 0;
    high = menumx;
    while (high > low) {
      mid = (high + low) / 2;
      lex = strncmp(choice, menu[mid], nchars);
      if (lex > 0) {
        low  = mid + 1;
      } else if (lex < 0) {
        high = mid;
      } else {
        break;
      }
    }
    mid = (high + low) / 2;
 
/* If the pick is not found, return. */
    if (strncmp(menu[mid], choice, nchars))
    return(-1);
 
/* Check for ambiguity among menu options. */
    if (mid > 0) {
      low = strncmp(choice, menu[mid-1], nchars);
    } else {
      low = 1;
    }
    if (mid < (menumx - 1)) {
      high = strncmp(choice, menu[mid+1], nchars);
    } else {
      high = -1;
    }
 
/* Parser found menu not in correct order. */
    if ((low < 0) || (high > 0)) {
      textc("Error:  Menu items are not in lexical order.", TRUE);
      return(-1);
    }
 
/* Command was found in menu but is ambiguous. */
    if (!(low && high)) {
      textc("Error:  Ambiguous menu options found.", TRUE);
      return(0);
    }
 
/* Command was found in menu and is unique. */
    return(mid + 1);
  }
 
/* Check for ambiguity among headers. */
  if (mid > 0) {
    low = strncmp(choice, header[mid-1], nchars);
  } else {
    low = 1;
  }
  if (mid < (nhdrs - 1)) {
    high = strncmp(choice, header[mid+1], nchars);
  } else {
    high = -1;
  }
  if ((low < 0) || (high > 0)) {
    textc("Error:  Menu headers are not in lexical order.", TRUE);
    return(-1);
  }
 
/* Command was found in headers but is ambiguous. */
  if (!(low && high)) {
    textc("Error:  Ambiguous menu headers found.", TRUE);
    return(0);
  }
 
/* Command was found among headers and is unique. */
  khdr = mid + 1;
  return(mid + 101);
}
