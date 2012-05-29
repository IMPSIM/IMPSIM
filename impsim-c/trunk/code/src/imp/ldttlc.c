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
/* ldttlc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Load a title for the system into System.title.
|
|     Access:
|       (void) ldttlc(char *titel);
|     char *titel,i-Title to be stored for the system.
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
  void ldttlc(char *titel)
#else
  void ldttlc(titel)
  char *titel;
#endif
{
  int n;

/* Allocate space for the new title string. */
  if (System.title) free (System.title);
  n = lenc(titel);
  System.title = (char *) malloc(n + 1);

/* Copy the new title to the System storage string. */
  strncpy(System.title, titel, n);
  System.title[n] = '\0';
  return;
}
