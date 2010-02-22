/* ------------------------------------------------------------------ */
/* mpymmc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the product of two real matrices a and b, and store the
|     result in the matrix c = a * b.
|
|     Access:
|       (void) mpymmc(int nrowsa, int ncolsa, int ncolsb, real a[],
|         real b[], real c[]);
|     int nrowsa,i-The number of rows in matrix a[].
|     int ncolsa,i-The number of columns in matrix a[].  This must be
|       equal to the number of rows in matrix b[].
|     int ncolsb,i-The number of columns in matrix b[].
|     real a[],i-The premultiplying matrix a[].
|     real b[],i-The postmultiplying matrix b[].
|     real c[],o-The product matrix, c[] = a[] * b[].
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Note that matrices a[], b[], and c[] are assumed stored in row-
|     major (C) not column-major (Fortran) order.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void mpymmc(int nrowsa, int ncolsa, int ncolsb, real a[], real b[],
    real c[])
#else
  void mpymmc(nrowsa, ncolsa, ncolsb, a, b, c)
  real a[], b[], c[];
  int nrowsa, ncolsa, ncolsb;
#endif
{
  int j, jk, k;
 
  for (j=0; j<nrowsa; j++) {
    for (k=0; k<ncolsb; k++) {
      c[j*ncolsa+k] = 0.0;
      for (jk=0; jk<ncolsa; jk++) {
        c[j*ncolsa+k] += a[j*ncolsa+jk] * b[jk*ncolsb+k];
      }
    }
  }
  return;
}
