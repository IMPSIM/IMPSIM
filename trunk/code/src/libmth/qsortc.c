/* ------------------------------------------------------------------ */
/* qsortc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       This routine sorts an array of real values into descending
|     numerical order.
|
|     Access:
|       (void) qsortc(int n, real array[]);
|     int n,i-Number of values in the array to be sorted.
|     real array[],i/o-The array of values to be sorted.
|
|     Error Conditions:
|       If more than 32 levels of stack space are needed, execution is
|     aborted.
|
|     Comments:
|       The algorithm used is a quick-sort approach.  This version is
|     adapted from the reference: "Numerical Recipes", Cambridge
|     University Press, 1986, p. 236.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qsortc(int n, real array[])
#else
  void qsortc(n, array)
  int  n;
  real array[];
#endif
{
# define FA    211
# define FC   1663
# define FM   7875
# define M       7
# define NSTACK 32
  int      istack[NSTACK+1], i, j, k, low = 1, last, level = 0;
  long int fx = 0L;
  real     temp;

  last = n;
  for (;;){
 
/* Use selection sort if the range is small. */
    if ((last - low) < M){
      for (i=low; i<last; i++) {
        temp = array[i];
        for (j=i; array[j-1]<temp && j>0; j--) array[j] = array[j-1];
        array[j] = temp;
      }
      if (level == 0) return;
      last = istack[(level--)];
      low  = istack[(level--)];
 
/* Otherwise, use quicksort; start by partitioning the array. */
    } else {
      i = low;
      j = last;
      fx= (fx * FA + FC) % FM;
      k = low + ((last - low + 1) * fx) / FM;
      temp = array[k-1];
      array[k-1] = array[low-1];
      for (;;) {
        while ((j > 0) && (temp > array[j-1])) j--;
        if (j <= i) {
          array[i-1] = temp;
          break;
        }
        array[(i++)-1] = array[j-1];
        while ((temp < array[i-1]) && (i <= n)) i++;
        if (j <= i) {
          array[(i=j)-1] = temp;
          break;
        }
        array[(j--)-1] = array[i-1];
      }
      if ((level + 2) > NSTACK) abortc();
      if ((last-i) >= (i-low)) {
        istack[(++level)] = i + 1;
        istack[(++level)] = last;
        last = i - 1;
      } else {
        istack[(++level)] = low;
        istack[(++level)] = i - 1;
        low = i + 1;
      }
    }
  }
# undef FA
# undef FC
# undef FM
# undef M
# undef NSTACK
}
