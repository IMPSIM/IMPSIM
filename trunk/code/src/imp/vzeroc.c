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
/* vzeroc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set a specified type and all dependent Value records undefined.
|
|     Access:
|       (void) vzeroc(enum Fnctyp type);
|     enum Fnctyp type,i-Type of Value functions to be zeroed.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If F_ALL is used for type, then all Values are set undefined
|     except for F_CONSTANT values.
|       If F_TIME, F_POSITION, F_VELOCITY, F_ACCEL, or F_FORCE is used
|     for type, then the Value records using that function and all Value
|     records dependent on them are set undefined.
|       If type has any other value then no action results.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void vzeroc(enum Fnctyp type)
#else
  void vzeroc(type)
  enum Fnctyp type;
#endif
{
  Value *value;
  int    i;

  for (value=System.sysVal; value; value=value->nxtVal) {
    if (value->f == F_CONST) continue;
    if (type == F_ALL) goto _2;
    if (value->f == F_USER) goto _2;
    if (value->f == type) goto _2;
    if (isnanc((void *) &value->v)) goto _2;
    for (i=0; i<4; i++) {
      if (value->arg[i] == NULL) break;
      if (isnanc((void *) &value->arg[i]->v)) goto _2;
    }
    continue;
_2: ldnanc((void *) &value->v);
    ldnanc((void *) &value->d1);
    ldnanc((void *) &value->d2);
  }
  return;
}
