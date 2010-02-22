/* ------------------------------------------------------------------ */
/* gridc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Plot and label a grid in graph coordinates to fit the current
|     graph window boundaries and given ranges of values.
|
|     Access:
|       (void) gridc(int kind, real xmin, real ymin, real xmax,
|         real ymax);
|     int kind,i-Type of grid desired:
|       kind = 0 specifies linear-linear axes.
|       kind = 1 specifies linear-log axes.
|       kind = 2 specifies log-linear axes.
|       kind = 3 specifies log-log axes.
|     real xmin,i-Minimum x-component of the data to be plotted.
|     real ymin,i-Minimum y-component of the data to be plotted.
|     real xmax,i-Maximum x-component of the data to be plotted.
|     real ymax,i-Maximum y-component of the data to be plotted.
|
|     Error Conditions:
|       If xmin or ymin is specified non-positive for a log axis, the
|     axis type is changed to linear.
|
|     Comments:
|       The graphic display must have been defined by a previous call to
|     devic().
|       The grid will be drawn within the limits of the current graph
|     window.  The applications programmer must have defined a suitable
|     window by a previous call to framgc().
|       Minimum and maximum data values may be determined by previous
|     calls to amnmxc().
|       Plotting data on the grid can be done by subsequent calls to
|     movagc() and drwagc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void gridc(int kind, real xmin, real ymin, real xmax, real ymax)
#else
  void gridc(kind, xmin, ymin, xmax, ymax)
  int  kind;
  real xmin, ymin, xmax, ymax;
#endif
{
  char text[10];
  int icnt, itype, jtype, n;
  real deltap, deltaq, dp, dq, ds, dt, p, q, pmax, qmax, pmin, qmin,
    p1, p2, q1, q2, s, t;
 
/* Set the grid type and transformation parameters. */
  kgrid = min( max(kind, 0), 3);
  itype = kgrid & 1;
  gaxisc(itype, xmin, xmax, &pmin, &pmax, &dp);
  p1 = pmin;
  p2 = pmax;
  if (pmin <= 0.0) kgrid &= 2;
  itype = kgrid & 1;
  if (itype) {
    p1 = log(p1);
    p2 = log(p2);
  }
  deltap = max(p2 - p1, stzero);
  pscale = (sgmax - sgmin) / deltap;
  p0 = (sgmin * p2 - sgmax * p1) / deltap;
  jtype = kgrid / 2;
  gaxisc(jtype, ymin, ymax, &qmin, &qmax, &dq);
  q1 = qmin;
  q2 = qmax;
  if (qmin <= 0.0) kgrid &= 1;
  jtype = kgrid / 2;
  if (jtype) {
    q1 = log(q1);
    q2 = log(q2);
  }
  deltaq = max(q2 - q1, stzero);
  qscale = (tgmax - tgmin) / deltaq;
  q0 = (tgmin * q2 - tgmax * q1) / deltaq;
 
/* Draw the horizontal grid lines. */
  p1 = pmin;
  p2 = pmax;
  n = qmin / dq + stzero;
  n = jtype * n - 10;
  deltaq = dq;
  q = qmin;
  while (q <= qmax) {
    xgtosc(p1, q, &s, &t);
    movasc(s, t);
    xgtosc(p2, q, &s, &t);
    drwasc(s, t);
    p  = p2;
    p2 = p1;
    p1 = p;
    q += deltaq;
    n += jtype;
    if (n >= 0){
      n = -9;
      deltaq = q;
    }
  }
 
/* Draw the vertical grid lines. */
  q1 = qmin;
  q2 = qmax;
  n = pmin / dp + stzero;
  n = itype * n - 10;
  deltap = dp;
  p = pmin;
  while (p <= pmax) {
    xgtosc(p, q1, &s, &t);
    movasc(s, t);
    xgtosc(p, q2, &s, &t);
    drwasc(s, t);
    q  = q2;
    q2 = q1;
    q1 = q;
    p += deltap;
    n += itype;
    if (n >= 0){
      n = -9;
      deltap = p;
    }
  }
 
/* Label the vertical axis. */
  p = pmin;
  if (fabs(pmax + pmin) < (pmax - pmin)) p = 0.0;
  q = qmin;
  if (jtype) dq = 10.0 * dq - qmin;
  ds = -6.75 * ssymbl;
  while (q <= qmax) {
    xgtosc(p, q, &s, &t);
    movasc(s + ds, t);
    sprintf(text, "%10.3f", q);
    htextc(text);
    q += dq;
    if (jtype) dq = 9.0 * q;
  }
 
/* Label the horizontal axis. */
  q = qmin;
  if (fabs(qmax + qmin) < (qmax - qmin)) q = 0.0;
  p = pmin;
  if (itype) dp = 10.0 * dp - pmin;
  ds = -6.75 * ssymbl;
  icnt = 0;
  while (p <= pmax) {
    dt = -tsymbl;
    icnt++;
    if ((icnt % 2) <= 0) dt += dt;
    xgtosc(p, q, &s, &t);
    movasc(s + ds, t + dt);
    sprintf(text, "%10.3f", p);
    htextc(text);
    p += dp;
    if (itype) dp = 9.0 * p;
  }
  return;
}
