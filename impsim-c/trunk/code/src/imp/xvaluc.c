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
/* xvaluc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Value record and all dependent data.
|
|     Access:
|       (void) xvaluc(Value *value);
|     Value *value,i-Pointer to the Value record to be deleted.
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
  void xvaluc(Value *value)
#else
  void xvaluc(value)
  Value *value;
#endif
{
  Value *val;
  int    i;

  if (value->type == VALUE) {
    if (System.sysVal == value) {
      System.sysVal = value->nxtVal;
    } else {
      val = System.sysVal;
      while (val) {
        if (val->nxtVal == value) {
          val->nxtVal = value->nxtVal;
          break;
        } else {
          val = val->nxtVal;
        }
      }
    }
  }
  value->f = F_UNDEF;
  for (val=System.sysVal; val; val=val->nxtVal) {
    for (i=0; i<4; i++) {
      if (val->arg[i]) {
        if (val->arg[i]->f == F_UNDEF) val->f = F_UNDEF;
      }
    }
  }
  free(value);
  for (val=System.sysVal; val; val=val->nxtVal) {
    if (val->f == F_UNDEF) xvaluc(val);
  }
  return;
}
