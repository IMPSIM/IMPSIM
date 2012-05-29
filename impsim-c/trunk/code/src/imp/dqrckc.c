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
/* dqrckc-01 Jan 00:20 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative of a Q operator for a specified jvar of a
|     rack joint with respect to another jvar of the same joint.
|
|     Access:
|       (void) dqrckc(int ijv, int jjv, real radius, real helix,
|         real dQ[6]);
|     int  ijv,   i-Number of the jvar of the Q operator.
|     int  jjv,   i-Number of the jvar for the derivative.
|     real radius,i-Radius of the pinion of the rack joint.
|     real helix  i-Helix angle of the pinion of the rack joint.
|     real dQ[6], o-Derivative of the Q operator.
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
  void dqrckc(int ijv, int jjv, real radius, real helix, real dQ[6])
#else
  void dqrckc(ijv, jjv, radius, helix, dQ)
  int  ijv, jjv;
  real radius, helix, dQ[6];
#endif
{
  int i;
  real factor;

  for (i=0; i<6; i++) dQ[i] = 0.0;
  switch (ijv) {
  case 0:
    factor  = 1.0 / radius;
    switch (jjv) {
    case 0:
      dQ[1] = factor;
      break;
    case 1:
      dQ[0] =-factor;
      break;
    case 2:
      break;
    }
    break;
  case 1:
    factor  = tan (20.0 / System.ascale) / radius;
    switch (jjv) {
    case 0:
      dQ[1] = factor;
      break;
    case 1:
      dQ[0] =-factor;
      break;
    case 2:
      break;
    }
    break;
  case 2:
    factor  = tan(helix) / radius;
    switch (jjv) {
    case 0:
      dQ[1] =-factor;
      break;
    case 1:
      dQ[0] = factor;
      break;
    case 2:
      break;
    }
    break;
  }
  return;
}
