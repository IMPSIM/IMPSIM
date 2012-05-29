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
/* xic-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Delete a specified IC record.
|
|     Access:
|       (void) xic(Ic *ic);
|     Ic *ic,i-Pointer to the IC record to be deleted.
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
  void xic(Ic *ic)
#else
  void xic(ic)
  Ic *ic;
#endif
{
  Jvar  *jvar;

  if (ic->type == IC) {
    jvar = ic->icJvr;
    if (jvar) {
      if (jvar->jvrIc == ic) jvar->jvrIc = NULL;
    }
    free(ic);
  }
  return;
}
