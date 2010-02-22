/* ------------------------------------------------------------------ */
/* qfrntc-01 Jan 00:07 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Sort the data array indices so that the segments between data
|     points are drawn in the correct order for the floating horizon
|     hidden line removal algorithm.
|
|     Access:
|       (void) qfrntc(real theta, int nrows, int nkols, int *n1axis,
|         int *n1strt, int *n1stop, int *n1inc, int *n2strt,
|         int *n2stop, int *n2inc);
|     real theta, i-Angle of rotation about the Z axis.
|     int nrows,  i-Max row number filled in the Z array.
|     int nkols,  i-Max column number filled in the Z array.
|     int *n1axis,o-Number of axis most perpendicular to screen.
|     int *n1strt,o-Z index for initial curve.
|     int *n1stop,o-Z index for final curve.
|     int *n1inc, o-Z index increment between curves.
|     int *n2strt,o-Initial Z index for each curve segment.
|     int *n2stop,o-Final Z index for each curve segment.
|     int *n2inc, o-Z index increment for each curve segment.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This is a service utility routine for the floating horizon
|     algorithm of subroutine surfac().  It should not be called direct-
|     ly by the applications program.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qfrntc(real theta, int nrows, int nkols, int *n1axis,int *n1strt,
    int *n1stop, int *n1inc, int *n2strt, int *n2stop, int *n2inc)
#else
  void qfrntc(theta, nrows, nkols, n1axis, n1strt, n1stop, n1inc,
    n2strt, n2stop, n2inc)
  real theta;
  int  nrows, nkols, *n1axis, *n1strt, *n1stop, *n1inc, *n2strt,
    *n2stop, *n2inc;
#endif
{
  int istrt, istop, iinc, jstrt, jstop, jinc;
 
  if (cos(theta) >= 0.0) {
    istrt = nrows;
    istop =  1;
    iinc  = -1;
  } else {
    istrt = 1;
    istop = nrows;
    iinc  = 1;
  }
  if (sin(theta) >= 0.0) {
    jstrt = 1;
    jstop = nkols;
    jinc  = 1;
  } else {
    jstrt = nkols;
    jstop =  1;
    jinc  = -1;
  }
  if (sin(2.0 * theta + 0.50 * PI) >= 0.0) {
    *n1axis = 1;
    *n1strt = istrt;
    *n1stop = istop;
    *n1inc  = iinc;
    *n2strt = jstrt;
    *n2stop = jstop;
    *n2inc  = jinc;
  } else {
    *n1axis = 2;
    *n1strt = jstrt;
    *n1stop = jstop;
    *n1inc  = jinc;
    *n2strt = istrt;
    *n2stop = istop;
    *n2inc  = iinc;
  }
  return;
}
