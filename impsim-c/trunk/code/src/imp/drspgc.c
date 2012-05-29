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
/* drspgc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Draw a spring symbol between two given endpoints.
|
|     Access:
|       (void) drspgc(real p[3], real q[3]);
|     real p[3],i-Global coordinates of one endpoint.
|     real q[3],i-Global coordinates of the other endpoint.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The length of the symbol is scaled to fit the two endpoints; the
|     width is always 0.04 2-D distance units.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void drspgc(real p[3], real q[3])
#else
  void drspgc(p, q)
  real p[3], q[3];
#endif
{
  long int imesh, jmesh;
  real costh, d, d1, d2, denom, dist, q1, q2, sinth, theta, u, u1, u2,
    v, v1, v2, w1, w2, x, y;

  imesh = 120202021;
  jmesh = 123456789;
  x3to2c(p[0], p[1], p[2], 1.0, &u1, &v1, &w1, &q1);
  x3to2c(q[0], q[1], q[2], 1.0, &u2, &v2, &w2, &q2);
  d1 = q1 * u2 - q2 * u1;
  d2 = q1 * v2 - q2 * v1;
  denom = max(ZERO, fabs(q1 * q2));
  dist = sqrt(d1 * d1 + d2 * d2) / (10.0 * denom * denom);
  if (dist >= ZERO){
    theta = atan2((d1 / denom), (d2 / denom));
    costh = cos(theta);
    sinth = sin(theta);
    d = sign(max(ZERO, fabs(q1)), q1);
    u1 /= d;
    v1 /= d;
    d = sign(max(ZERO, fabs(q2)), q2);
    u2 /= d;
    v2 /= d;
    mova2c(u2, v2);
    while (jmesh > 0){
      x = 0.4 * (real) (imesh % 10 - 1);
      imesh /= 10;
      y = dist * (real) (jmesh % 10);
      jmesh /= 10;
      u = u1 + costh * x + sinth * y;
      v = v1 - sinth * x + costh * y;
      drwa2c(u, v);
    }
    drwa2c(u1, v1);
  }
  return;
}
