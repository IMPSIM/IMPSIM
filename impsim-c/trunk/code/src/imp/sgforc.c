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
/* sgforc-01 Jan 00:06 May 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Determine the current axial tensile force in a specified spring.
|
|     Access:
|       force = (real) sgforc(Spring *spring);
|     Spring *spring,i-Pointer to the spring record.
|     real force,    o-Axial tensile force found.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined spring rate or free
|     length.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  real sgforc(Spring *spring)
#else
  real sgforc(spring)
  Spring *spring;
#endif
{
  real forc, rba[3], size;

  if (isnanc((void *) &spring->k) || isnanc((void *) &spring->freel)) {
    ldnanc((void *) &forc);
    System.nerror = 3;
  } else {
    sgposc(spring, rba);
    size = vabsc(3, rba);
    forc = spring->k * (size - spring->freel);
  }
  return (forc);
}
