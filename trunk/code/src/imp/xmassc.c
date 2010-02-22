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
/* xmassc-01 Jan 00:12 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Mass record.
|
|     Access:
|       (void) xmassc(Mass *mass);
|     Mass *mass,i-Pointer to the Mass record to be deleted.
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
  void xmassc(Mass *mass)
#else
  void xmassc(mass)
  Mass *mass;
#endif
{
  Body  *body;

  if (mass->type == MASS) {
    body = mass->masBdy;
    if (body->bdyMas == mass) body->bdyMas = NULL;
    free(mass);
  }
  return;
}
