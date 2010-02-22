/* ------------------------------------------------------------------ */
/* amnmxc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Find the minimum and maximum values in the first column of a
|     real two-dimensional array.
|
|     Access:
|       (void) amnmxc(real array[], int nrows, int nkols, real *amin,
|         real *amax);
|     real array[],i-The (nrows x nkols) two-dimensional array to be
|       searched.
|     int   nrows,i-The number of rows in the array.
|     int   nkols,i-The number of columns in the array.
|     real *amin, o-The minimum value found.
|     real *amax, o-The maximum value found.
|
|     Error Conditions:
|       If nrows <= 0, amin and amax are set equal to array[0].
|
|     Comments:
|       Note that the array is assumed stored in row-major (C) order
|     rather than column-major (Fortran) order.
|       This procedure is useful, for example, in determining the
|     extremes required for the axis of a grid used for plotting the
|     data stored in a 2-D array.
|       The minimum and maximum values in the j-th column of a two-
|     dimensional array may also be found by calling this routine as
|     follows:  amnmxc(&(a[j]),nrows,nkols,&amin,&amax)
|       The minimum and maximum values in the i-th row of a two-
|     dimensional array may also be found by calling this rouine as
|     follows:  amnmxc(&(a[i*nkols]),nkols,1,&amin,&amax).
|       Similar variations may be found for obtaining the minimum and
|     maximum values stored in a singly- or multiply-dimensioned array
|     by considering the order of storage of the array elements and
|     defining an equivalent two-dimensional array, perhaps with a
|     shifted starting address.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void amnmxc(real array[], int nrows, int nkols, real *amin,
    real *amax)
#else
  void amnmxc(array, nrows, nkols, amin, amax)
  real  array[];
  int   nrows, nkols;
  real *amin, *amax;
#endif
{
  int j;
 
  *amax = *amin = array[0];
  for (j=1; j<nrows; j++) {
    *amin = min(*amin, array[j * nkols]);
    *amax = max(*amax, array[j * nkols]);
  }
  return;
}
