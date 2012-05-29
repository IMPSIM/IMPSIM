/* ------------------------------------------------------------------ */
/* framgc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the graph window boundaries for subsequent graph plotting
|     requests.
|
|     Access:
|       (void) framgc(real s1, real t1, real s2, real t2);
|     real s1,i-Screen coordinate for the left   edge of the grid.
|     real t1,i-Screen coordinate for the bottom edge of the grid.
|     real s2,i-Screen coordinate for the right  edge of the grid.
|     real t2,i-Screen coordinate for the top    edge of the grid.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       For equal min and max boundary values in either direction, the
|     max boundary value is increased by a small tolerance.
|       The grid for the graph must be drawn by a subsequent call to
|     gridc().  Then the graph may be drawn by appropriate calls to
|     drwagc() and movagc().
|       The graph window boundaries may be changed at will by repeated
|     calls to framgc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void framgc(real s1, real t1, real s2, real t2)
#else
  void framgc(s1, t1, s2, t2)
  real s1, t1, s2, t2;
#endif
{
  sgmin = min( max( min(s1, s2), smin), smax);
  sgmax = min( max( max(s1, s2), smin), smax);
  if (sgmax <= sgmin) sgmax = sgmin + stzero;
  tgmin = min( max( min(t1, t2), tmin), tmax);
  tgmax = min( max( max(t1, t2), tmin), tmax);
  if (tgmax <= tgmin) tgmax = tgmin + stzero;
  return;
}
