/* ------------------------------------------------------------------ */
/* fservc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the value of a Fourier series and its first and second
|     derivatives for a given value of the independent variable x.
|
|     Access:
|       (void) fservc(real x, real xmin, real xmax, complex coeff[],
|         int ncoeff, real *y, real *dy, real *ddy);
|     real x,    i-Value of the independent variable.
|     real xmin, i-Lower bound of range of the independent variable.
|     real xmax, i-Upper bound of range of the independent variable.
|     complex coeff[ncoeff],i-Fourier series coefficients.
|     int ncoeff,i-Number of terms in the Fourier series.
|     real *y,   o-Value of the series at this value of x.
|     real *dy,  o-First derivative of *y at this value of x.
|     real *ddy, o-Second derivative of *y at this value of x.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The coeff[] array specifies the terms of a complex Fourier ser-
|     ies.  However, they are assumed to represent a real function, and
|     the resulting *y, *dy, and *ddy values are returned as real.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fservc(real x, real xmin, real xmax, complex coeff[], int ncoeff,
    real *y, real *dy, real *ddy)
#else
  void fservc(x, xmin, xmax, coeff, ncoeff, y, dy, ddy)
  real    x, xmin, xmax;
  complex coeff[];
  int     ncoeff;
  real   *y, *dy, *ddy;
#endif
{
  complex expnt, term;
  int     k;
  real    c0, c1, c2, dtheta, range, ratio, sigk, theta, value;

/* Scale the interval to 0 <= x < 2*PI. */
  range = xmax - xmin;
  ratio = 2.0 * PI / range;
  value = x;
  while (value <  xmin) value += range;
  while (value >= xmax) value -= range;
  value = ratio * (value - xmin);

/* Sum the terms of the Fourier series. */
  c0 = 0.0;
  c1 = 0.0;
  c2 = 0.0;
  dtheta = PI / ((real) ncoeff);
  for (k=1; k<ncoeff; k++) {
    theta = dtheta * (real) k;
    sigk  = sin(theta) * (real) k / theta;
    expnt.r = cos(value * (real) k);
    expnt.i = sin(value * (real) k);
    term.r  = coeff[k].r * expnt.r - coeff[k].i * expnt.i;
    term.i  = coeff[k].r * expnt.i + coeff[k].i * expnt.r;
    c0 += term.r;
    c1 -= term.i * sigk;
    c2 += term.r * sigk * sigk;
  }

/* Extract the values of y, dy, and ddy. */
  *y   = 2.0 * c0 + coeff[0].r;
  *dy  = 2.0 * ratio * c1;
  *ddy = 2.0 * ratio * ratio * c2;
  return;
}
