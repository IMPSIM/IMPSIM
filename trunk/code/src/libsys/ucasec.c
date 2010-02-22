/* ------------------------------------------------------------------ */
/* ucasec-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Translate all lower case characters in a character string into
|     upper case.
|
|     Access:
|       (void) ucasec(char *string)
|     char *string,i/o-String to be translated to upper case.
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
  void ucasec(char *string)
#else
  void ucasec(string)
  char *string;
#endif
{
  char *chrptr;

  for (chrptr=string; *chrptr; chrptr++) {
    if (islower(*chrptr)) *chrptr = toupper(*chrptr);
  }
  return;
}
