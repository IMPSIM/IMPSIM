/* ------------------------------------------------------------------ */
/* todc-01 Jan 00:05 Jul 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set up and return the current time of day in character format,
|     (e.g., "13:45:00" for 1:45 pm).
|
|     Access:
|       (void) todc(char *tod)
|     char *tod,o-Time  of day in "hh:mm:ss" format.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The character string tod is assumed to exist and to be 9 or more
|     characters in length.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void todc(char *tod)
#else
  void todc(tod)
  char *tod;
#endif
{
  time_t timer;
  struct tm *ltime;

  (void) time(&timer);
  ltime = localtime(&timer);
  strftime(tod, (size_t) 9, "%H:%M:%S", ltime);
  return;
}
