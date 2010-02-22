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
/* dqsphc-13 Jun 09
|     (C)Copyright, JJU Research, 2009.
|
|     Description:
|       Form the derivative of the Q operator for a spheric joint.
|
|     Access:
|       (void) dqsphc(int i, int j, real dQ[6]);
|     int  i,     i-Euler parameter number of Q operator.
|     int  j,     i-Euler parameter number of the derivative.
|     real dQ[6], o-Derivative of the Q operator.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     13 Jun 09:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dqsphc(int i, int j, real dQ[6])
#else
  void dsphc(i, j, dQ)
  int  i, j;
  real dQ[6];
#endif
{
  int k;

  for (k=0; k<6; k++) dQ[k] = 0.0;
  switch (i) {
  case 0:
    switch (j) {
    case 1:
      dQ[5] = -2.0;
      break;
    case 2:
      dQ[4] =  2.0;
      break;
    case 3:
      dQ[3] =  2.0;
      break;
    }
    break;
  case 1:
    switch (j) {
    case 0:
      dQ[5] =  2.0;
      break;
    case 2:
      dQ[3] = -2.0;
      break;
    case 3:
      dQ[4] = -2.0;
      break;
    }
    break;
  case 2:
    switch (j) {
    case 0:
      dQ[4] = -2.0;
      break;
    case 1:
      dQ[3] =  2.0;
      break;
    case 3:
      dQ[5] =  2.0;
      break;
    }
    break;
  case 3:
    switch (j) {
    case 0:
      dQ[3] = -2.0;
      break;
    case 1:
      dQ[4] = -2.0;
      break;
    case 2:
      dQ[5] = -2.0;
      break;
    }
    break;
  }
  return;
}
