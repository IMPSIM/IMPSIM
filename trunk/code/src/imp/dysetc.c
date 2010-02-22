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
/* dysetc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Set the mode flag for dynamic analysis.
|
|     Access:
|       (void) dysetc();
|
|     Error Conditions:
|       System.nerror = 3 indicates a conflict in mode.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void dysetc()
{
  if ((System.mode == MD_KIN) || (System.mode == MD_STAT)) {
    echoc();
    textc("*** The mode is already set. ***", TRUE);
    textc("*** DELETE:INPUT(ALL) will unset it. ***", TRUE);
    System.nerror = 3;
  } else {
    ldnanc((void *) &System.t);
    System.mode = MD_DYN;
  }
  return;
}
