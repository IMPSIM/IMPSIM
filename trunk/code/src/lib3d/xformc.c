/* ------------------------------------------------------------------ */
/* xformc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Transform all new grid-points into the disply array in 2D
|     coordinates.
|
|     Access:
|       (void) xformc(int mxsize, int nrows, int nkols, int n1axis,
|         int n1, int n2strt, int n2stop, int n2inc, real z[],
|         real zmax, real x32[3][4], real disply[]);
|     int mxsize,i-Max. dimension of the z[mxsize,mxsize] array.
|     int nrows, i-Max. row number filled in the z[,] array.
|     int nkols, i-Max. column number filled in the z[,] array.
|     int n1axis,i-Number of the axis most perpendicular to the screen.
|     int n1,    i-z[,] first  axis         index for a curve.
|     int n2strt,i-z[,] second axis initial index for a curve.
|     int n2stop,i-z[,] second axis final   index for a curve.
|     int n2inc, i-z[,] second axis index increment for curve.
|     real z[],  i-Function data for z[,].
|     real zmax, i-Largest value in the z[,] data array.
|     real x32[3][4],i-Total 3D to 2D transformation matrix.
|     real disply[mxsize,4],i/o-Transformed 2D point data.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This is a service utility routine for the floating horizon
|     algorithm of srfacu.  It should not be called directly by the
|     applications program.
|       Note that the x32[3][4], z[,], and disply[,] arrays are assumed
|     stored in row-major (C) rather than column-major (Fortran) order.
|       The display device must have been defined by a previous call to
|     devic.
*
*     History:
*     01 Jan 95:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void xformc(int mxsize, int nrows, int nkols, int n1axis, int n1,
    int n2strt, int n2stop, int n2inc, real z[], real zmax,
    real x32[3][4], real disply[])
#else
  void xformc(mxsize, nrows, nkols, n1axis, n1, n2strt, n2stop, n2inc,
    z, zmax, x32, disply)
  int  mxsize, nrows, nkols, n1axis, n1, n2strt, n2stop, n2inc;
  real z[], zmax, x32[3][4], disply[];
#endif
{
  real denom, r[3];
  int  ix, iy, n2;
 
  denom = (real) (max3(nrows, nkols, 2) - 1);
  for (n2=n2strt;
    (((n2inc<0)&&(n2>=n2stop))||((n2inc>0)&&(n2<=n2stop))); n2+=n2inc) {
    if (n1axis == 1) {
      ix = n1 - 1;
      iy = n2 - 1;
    } else if (n1axis == 2) {
      ix = n2 - 1;
      iy = n1 - 1;
    }
    r[0] = ((real) ix) / denom;
    r[1] = ((real) iy) / denom;
    r[2] = z[ix*mxsize+iy] / zmax;
    mpyxrc(x32, r, r);
    disply[4*(n2-1)+2] = r[0];
    disply[4*(n2-1)+3] = r[1];
  }
  return;
}
