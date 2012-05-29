/* ------------------------------------------------------------------ */
/* shsrtc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Sort an array of real values into increasing order, and a second
|     array of integers into the equivalent order.
|
|     Access:
|       (void) shsrtc(int n, real array[], int iarray[])
|     int  n,        i  -Number of values defined in arrays.
|     real array[n], i/o-Sorted real values.
|     int  iarray[n],i/o-Rearranged integer values.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The algorithm used is a shell sort technique.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void shsrtc(int n, real array[], int iarray[])
#else
  void shsrtc(n, array, iarray)
  int  n, iarray[];
  real array[];
#endif
{
  int  i, idist, itemp, j, k;
  real temp;
 
  idist = 4;
  while (idist < n) idist += idist;
  idist--;
  while (idist > 1) {
    idist /= 2;
    for (i=0; i<(n-idist); i++) {
      for (j=i; j>=0; j-=idist) {
        k = idist + j;
        if (array[j] > array[k]) {
          temp      = array[k];
          array[k]  = array[j];
          array[j]  = temp;
          itemp     = iarray[k];
          iarray[k] = iarray[j];
          iarray[j] = itemp;
        }
      }
    }
  }
  return;
}
