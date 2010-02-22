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
/* titlec-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Store the title for the system from IMP input.
|
|     Access:
|       (void) titlec(char *titel);
|     char *titel,o-Title for the IMP modeled system.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If a previous system title is being redefined, a message is
|     printed.
|       The usual $ and $$ IMP language conventions are not allowed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void titlec(char *titel)
#else
  void titlec(titel)
  char *titel;
#endif
{
  char *chrptr;

/* Print a message if the previous title is changing. */
  if (System.title) {
    free (System.title);
    System.title = NULL;
  }

/* Bypass lead characters up to and including the first separator. */
  chrptr = inbufr + strspn(inbufr, " ");
  if (lenc(chrptr) > 0) {
    chrptr += strcspn(chrptr, "+-*/=(,:;@ ");
    chrptr += strspn (chrptr, "+-*/=(,:;@ ");
  }

/* Store the new title in System.title. */
  ldttlc(chrptr);

/* Copy the new title to the output string. */
  strcpy(titel, System.title);
  return;
}
