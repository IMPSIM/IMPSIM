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
/* tfjtfc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Add the effects of a joint force input to the generalized forces 
|     for a transfer function.
|
|     Access:
|       (void) tfjtfc(Jvar *jvar, real G[]);
|     Jvar *jvar,    i-Jvar record for the input force.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This function assumes that the G[] array has been initialized 
|     before entry and that other effects are added elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void tfjtfc(Jvar *jvar, real G[])
#else
  void tfjtfc(jvar, G)
  Jvar *jvar;
  real G[];
#endif
{
  int i, ngc;
  
  if (jvar->jvrnoS < System.ndep) {
    for (i=0; i<System.nfgc; i++) {
      G[i] += System.d1[jvar->jvrnoS][i];
    }
  } else {
    ngc = jvar->jvrnoS-System.ndep;
    if (ngc < System.nfgc) {
      G[ngc] += 1.0;
    }
  }
  return;
}
