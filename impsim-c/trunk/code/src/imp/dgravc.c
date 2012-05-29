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
/* dgravc-01 Jan 00:05 May 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Store data for the gravity vector.
|
|     Access:
|       (void) dgravc(real gravx, real gravy, real gravz);
|     real gravx,i-Global X component of the gravity vector.
|     real gravy,i-Global Y component of the gravity vector.
|     real gravz,i-Global Z component of the gravity vector.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       When previous data are redefined, a message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dgravc(real gravx, real gravy, real gravz)
#else
  void dgravc(gravx, gravy, gravz)
  real gravx, gravy, gravz;
#endif
{
  if (isnanc((void *) &gravx)) {
  } else if (isnanc((void *) &System.gravty[0])) {
  } else if ((gravx == System.gravty[0]) && (gravy == System.gravty[1])
          && (gravz == System.gravty[2])) {
  } else {
    echoc();
    textc("*** The gravity vector is redefined. ***", TRUE);
  }
  System.gravty[0] = gravx;
  System.gravty[1] = gravy;
  System.gravty[2] = gravz;
  return;
}
