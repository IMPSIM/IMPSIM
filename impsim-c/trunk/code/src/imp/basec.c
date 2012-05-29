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
/* basec-01 Jan 00:14 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Store the name of the base body.
|
|     Access:
|       (void) basec(Word name);
|     Word name,i-Name of the new base body.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       System.level and System.nloops are set to 0 with successful
|     completion.  Thus, new kinematic loops must be found at the
|     beginning of the next execution of the model.
*
*     History:
*     01 Jan 00:JJU-Original.
*     11 Jul 07:JJU-Renamed LINK records to type BODY records.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void basec(Word name)
#else
  void basec(name)
  Word name;
#endif
{
  if (strncmp(System.base, name, MAXCHR) != 0) {
    echoc();
    textc("*** The fixed body is redefined. ***", TRUE);
    strncpy(System.base, name, MAXCHR);
    System.base[MAXCHR] = '\0';
  }
  System.ground = NULL;
  System.level  = 0;
  System.nloops = 0;
  return;
}
