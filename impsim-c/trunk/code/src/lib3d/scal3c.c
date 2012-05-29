/* ------------------------------------------------------------------ */
/* scal3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Magnify the current 3D to 2D scale by the given factor.
|
|     Access:
|       (void) scal3c(real factor);
|     real factor,i-The desired magnification factor.
|
|     Error Conditions:
|       If the absolute value of factor is less than 0.0001, then 0.0
|     is used instead.
|       If execution is non-interactive, the absolute value of factor
|     is used; a value of zero is treated as one.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The current 3D to 2D scale factor may be obtained at will by use
|     of qscl3c().
|       If factor > 0.0, magnification is about the screen center.
|       If factor < 0.0, the user is prompted to enter the new view cen-
|     ter via the current locator device.
|       If factor = 0.0, the user is prompted to enter two opposite cor-
|     ners of the new view via the current locator device.
|       If factor is 0.0 and the two locations input give either the new
|     view width or height equal to zero, then the user is requested to
|     enter the two locations again.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void scal3c(real factor)
#else
  void scal3c(factor)
  real factor;
#endif
{
# define ZRO 0.0001
  int  i, lgoto;
  real du, dv, fact, u0, v0, u1, v1, u2, v2;
 
  fact = factor;
  if (fabs(fact) < ZRO) fact = 0.0;
  if (! intact) {
    fact = fabs(fact);
    if (fact == 0.0) fact = 1.0;
  }
  if (fact < 0.0) {
    textc("Indicate new view center.", TRUE);
    qloc2c(&u0, &v0, &lgoto);
    fact = fabs(fact);
  } else
_2: if (fact == 0.0){
    textc("Indicate opposite corners of new view.", TRUE);
    qloc2c(&u1, &v1, &lgoto);
    qloc2c(&u2, &v2, &lgoto);
    u0 = 0.5 * (u1 + u2);
    v0 = 0.5 * (v1 + v2);
    du = fabs(u1 - u2);
    dv = fabs(v1 - v2);
    if ((du < ZRO) || (dv < ZRO)) goto _2;
    fact = min((x2max - x2min) / du, (y2max - y2min) / dv);
  } else if (fact > 0.0){
    u0 = 0.5 * (x2max + x2min);
    v0 = 0.5 * (y2max + y2min);
  }
  u0 = 0.5 * (x2max + x2min) / fact - u0;
  v0 = 0.5 * (y2max + y2min) / fact - v0;
  x3to2[0][3] += u0 * x3to2[3][3];
  x3to2[1][3] += v0 * x3to2[3][3];
  x3to2[3][3] /= fact;
  for (i=0; i<3; i++) {
    x2to3[i][3] -= x2to3[i][0] * u0 + x2to3[i][1] * v0;
  }
  for (i=0; i<4; i++) {
    x2to3[i][3] *= fact;
  }
  lspen = FALSE;
  l3pen = FALSE;
  return;
# undef ZRO
}
