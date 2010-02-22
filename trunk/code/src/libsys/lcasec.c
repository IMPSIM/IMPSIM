/* ------------------------------------------------------------------ */
/* lcasec-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Translate all upper case characters in a character string into
|     lower case.
|
|     Access:
|       (void) lcasec(char *string)
|     char *string,i/o-String to be translated to lower case.
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
  void lcasec(char *string)
#else
  void lcasec(string)
  char *string;
#endif
{
  char *chrptr;

  for (chrptr=string; *chrptr; chrptr++)
    if (isupper(*chrptr)) *chrptr = tolower(*chrptr);
  return;
}
