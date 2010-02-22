/* ------------------------------------------------------------------ */
/* datec-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Set up today's date in a character string ready for printing.
|     The format is "dd mmm yyyy", (e.g., "01 Apr 2000").
|
|     Access:
|       (void) datec(char *adate)
|     char *adate,o-Character string to hold the date.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The character string adate must be at least twelve characters
|     in length, or the date will be truncated.  If longer than or equal
|     to twelve characters, the above format will be left adjusted in 
|     the string and NULL terminated.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void datec(char *adate)
#else
  void datec(adate)
  char *adate;
#endif
{
  time_t timer;
  struct tm *ltime;

  (void) time(&timer);
  ltime = localtime(&timer);
  strftime(adate, (size_t) 12, "%d %b %Y\0", ltime);
  return;
}
