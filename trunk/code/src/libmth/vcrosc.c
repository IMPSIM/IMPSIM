/* ------------------------------------------------------------------ */
/* vcrosc-01 JAN 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the cross product of two three-dimensional real vectors v
|     and u, and store the result in the vector vxu = v x u.
|
|     Access:
|       (void) vcrosc(real v[3], real u[3], real vxu[3])
|     real v[3],  i-The components of the premultiplying vector.
|     real u[3],  i-The components of the postmultiplying vector.
|     real vxu[3],o-The components of the resulting vector, vxu = v x u.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If desired, the product vector vxu may overwrite either of the
|     given vectors, v or u, as follows: vcrosu(v, u, v).
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void vcrosc(real v[3], real u[3], real vxu[3])
#else
  void vcrosc(v, u, vxu)
  real v[3], u[3], vxu[3];
#endif
{
  int  j;
  real temp[3];
 
  temp[0] = v[1] * u[2] - v[2] * u[1];
  temp[1] = v[2] * u[0] - v[0] * u[2];
  temp[2] = v[0] * u[1] - v[1] * u[0];
  for (j=0; j<3; j++) {
    vxu[j] = temp[j];
  }
  return;
}
