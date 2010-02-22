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
/* jvacc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Return the user oriented relative acceleration of a given joint
|     variable.
|
|     Access:
|       jvacc = (real) jvacc(Jvar *jvar);
|     Jvar *jvar,i-Pointer to the appropriate joint variable record.
|     real jvacc,o-User oriented relative acceleration value.
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
  real jvacc(Jvar *jvar)
#else
  real jvacc(jvar)
  Jvar *jvar;
#endif
{
  real jvacc;

  ldnanc((void *) &jvacc);
  if (System.level < 10) acc();
  if (System.nerror == 0) jvacc = jvar->acc;
  return(jvacc);
}
