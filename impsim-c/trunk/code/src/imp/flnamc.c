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
/* flnamc-01 Jan 00:02 Feb 09
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Extract a filename from the end of the current IMP input
|     statement.
|
|     Access:
|       (void) flnamc(int n, char *filename);
|     int   n,       i-The number of words preceeding the filename.
|     char *filename,o-Filename string found from the IMP statement.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The filename returned contains the character string following
|     the nth separator of the current IMP input statement.
|       The usual $ and $$ imp language conventions may not be applied.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void flnamc(int n, char *filename)
#else
  void flnamc(n, filename)
  int   n;
  char *filename;
#endif
{
  char *chrptr, string[MXINBF+1];
  int i, kol;

/* Get a copy of the the current IMP input string. */
  strcpy(string, inbufr);

/* Eliminate possible ')' as the last character in the filename. */
  kol = lenc(string) - 1;
  if (string[kol] == ')') string[kol] = '\0';

/* Bypass lead characters up to and including the second separator. */
  chrptr = string + strspn(string, " ");
  for (i=0; i<n; i++){
    if (lenc(chrptr) > 0){
      chrptr += strcspn(chrptr, "+-*/=(,:;@ ");
      chrptr += strspn (chrptr, "+-*/=(,:;@ ");
    }
  }

/* Copy the filename to the output string. */
  strcpy(filename, chrptr);
  return;
}
