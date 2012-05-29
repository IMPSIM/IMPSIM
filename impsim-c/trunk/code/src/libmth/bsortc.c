/* ------------------------------------------------------------------ */
/* bsortc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Sort an array of real values into increasing order.
|
|     Access:
|       (void} bsortc(int n, real array[]);
|     int n,i-The number of elements defined in array.
|     real array[],i/o-The array of values.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The algorithm used is a bubble sort technique.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void bsortc(int n, real array[])
#else
  void bsortc(n, array)
  int n;
  real array[];
#endif
{
  real temp;
  int  ldone, i, j;
 
  for (i=1; i<n; i++) {
    ldone = TRUE;
    for (j=1; j<n; j++) {
      if (array[j-1] > array[j]) {
        temp       = array[j];
        array[j]   = array[j-1];
        array[j-1] = temp;
        ldone      = FALSE;
      }
    }
    if (ldone) break;
  }
  return;
}
