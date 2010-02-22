/* ------------------------------------------------------------------ */
/* stripc-01 Jan 00:26 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
|
|     Description:
|       Strip all leading blank characters from a character string.
|
|     Access:
|       (void) stripc(char *string);
|     char *string,i/o-String to be stripped.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     26 Jan 04:JJU-Rewritten to remove limit on string length.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void stripc(char *string)
#else
  void stripc(string)
  char *string;
#endif
{
  int  i, j;
        
  j = strspn(string, " ");
  if (j > 0) {
    i = j - 1;
    do {
      i++;
      string[i-j] = string[i];
    } while (string[i] != '\0');
  }
  return;
}
