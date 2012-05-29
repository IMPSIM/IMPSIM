/* ------------------------------------------------------------------ */
/* clockc-01 Jan 00:29 Sep 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Return the clock time in minutes and seconds after midnight.
|
|     Access:
|       (void) clockc(int *imins, int *isecs)
|     int *imins,o-Minutes after midnight, (0 <= *imins < 1440).
|     int *isecs,o-Seconds after the imins minute, (0 <= *isecs < 60).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void clockc(int *imins, int *isecs)
#else
  void clockc(imins, isecs)
  int *imins, *isecs;
#endif
{
  time_t timer;
  struct tm *ltime;

  (void) time(&timer);
  ltime  = localtime(&timer);
  *imins = (ltime->tm_hour * 60) + ltime->tm_min;
  *isecs = ltime->tm_sec; 
  return;
}
