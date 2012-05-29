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
/* jvvelc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Return the user oriented relative velocity of a given joint var-
|     iable.
|
|     Access:
|       jvvel = (real) jvvelc(Jvar *jvar);
|     Jvar *jvar,i-Pointer to the appropriate joint variable record.
|     real jvvel,o-User oriented relative velocity value.
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
  real jvvelc(Jvar *jvar)
#else
  real jvvelc(jvar)
  Jvar *jvar;
#endif
{
  real jvvel;

  ldnanc((void *) &jvvel);
  if (System.level < 8) velc();
  if (System.nerror == 0) jvvel = jvar->vel;
  return(jvvel);
}
