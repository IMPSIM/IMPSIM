/* ------------------------------------------------------------------ */
/* gaxisc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Recommend axis parameters for plotting a given range of values.
|
|     Access:
|       (void) gaxisc(int kind, real xmin, real xmax, real *gmin,
|         real *gmax, real *gdelta);
|     int   kind,  i-Type of axis being parametrized:
|       kind = 0 specifies a linear axis; kind = 1 specifies a log axis.
|     real  xmin,  i-Minimum coordinate value of data to be plotted.
|     real  xmax,  i-Maximum coordinate value of data to be plotted.
|     real *gmin,  o-Recommended minimum grid value.
|     real *gmax,  o-Recommended maximum grid value.
|     real *gdelta,o-Recommended increment for use with gmin and gmax.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Minimum and maximum data values can be determined by a previous
|     call to amnmxc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void gaxisc(int kind, real xmin, real xmax, real *gmin, real *gmax,
    real *gdelta)
#else
  void gaxisc(kind, xmin, xmax, gmin, gmax, gdelta)
  int  kind;
  real xmin, xmax, *gmin, *gmax, *gdelta;
#endif
{
  *gmin = min(xmin, xmax);
  *gmax = max(xmin, xmax);
  if (kind == 0) {
    *gdelta = *gmax - *gmin;
    if (*gdelta <= stzero) {
      *gmin = *gmin - 1.0 + stzero;
      *gmax = *gmax + 1.0 - stzero;
      *gdelta = 2.0;
    }
  } else {
    *gmax = max(*gmax, stzero);
    *gmin = max(*gmin, *gmax / 1000.0);
    *gdelta = *gmax;
  }
  *gdelta = pow(10.0, (aint(log10(*gdelta) + 1000.0) - 1000.0));
  *gmax   = *gdelta * (aint(*gmax / *gdelta + 21.0 - stzero) - 20.0);
  if (kind != 0) *gdelta = pow(10.0,(aint(log10(*gmin)+1000.0)-1000.0));
  *gmin   = *gdelta * (aint(*gmin / *gdelta + 20.0 + stzero) - 20.0);
  return;
}
