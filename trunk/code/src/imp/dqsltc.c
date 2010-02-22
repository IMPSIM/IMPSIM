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
/* dqsltc-01 Jan 00:25 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Form the derivative of the Q operator for a SLOT joint.
|
|     Access:
|       (void) dqsltc(int ijv, int jjv, real real u, real v, real du,
|         real dv, real ddu, real ddv, real dQ[6]);
|     int  ijv,   i-number of the Q operator within the joint.
|     int  jjv,   i-number of the joint variable of the derivative.
|     real u,     i-Value of slot u profile function.
|     real v,     i-Value of slot v profile function.
|     real du,    i-Value of slot u profile function first derivative.
|     real dv,    i-Value of slot v profile function first derivative.
|     real ddu,   i-Value of slot u profile function second derivative.
|     real ddv,   i-Value of slot v profile function second derivative.
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
  void dqsltc(int ijv, int jjv, real u, real v, real du,
    real dv, real ddu, real ddv, real dQ[6])
#else
  void dqsltc(ijv, jjv, u, v, du, dv, ddu, ddv, dQ);
  int  ijv, jjv;
  real u, v, du, dv, ddu, ddv, dQ[6];
#endif
{
  int i;

  for (i=0; i<6; i++) dQ[i] = 0.0;
  switch (ijv) {
  case 0:
    switch (jjv) {
    case 0:
      dQ[0] = ddu;
      dQ[1] = ddv;
    }
    break;
  case 1:
    switch (jjv) {
    case 0:
      dQ[0] = dv;
      dQ[1] =-du;
    }
  }
  return;
}
