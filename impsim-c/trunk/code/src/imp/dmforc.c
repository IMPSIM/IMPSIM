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
/* dmforc-01 Jan 00:05 May 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Determine the current axial tensile force in a specified damper.
|
|     Access:
|       force = (real) dmforc(Damper *damper);
|     Damper *damper,i-Pointer to the damper.
|     real force,    o-Axial tensile force found.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined damping coefficient.
|       System.nerror = 4 indicates an indeterminate damper axis.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  real dmforc(Damper *damper)
#else
  real dmforc(damper)
  Damper *damper;
#endif
{
  real forc, rba[3], size, vba[3];

  if (isnanc((void *) &damper->c)) {
    ldnanc((void *) &forc);
    System.nerror = 3;
  } else {
    dmposc(damper, rba);
    size = vabsc(3, rba);
    if (size < System.ptoll) {
      textc("*** The endpoints of damper '", FALSE);
      textc(damper->name, FALSE);
      textc("' are coincident. ***", TRUE);
      ldnanc((void *) &forc);
      System.nerror = 4;
    } else {
      dmvelc(damper, vba);
      forc = damper->c * vdotc(3, vba, rba) / size;
    }
  }
  return (forc);
}
