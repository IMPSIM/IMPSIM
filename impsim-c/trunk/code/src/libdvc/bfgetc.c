/* ------------------------------------------------------------------ */
/* bfgetc-01 Jan 00:13 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the next available character string from the local input
|     buffer.
|
|     Access:
|       (void) bfgetc(char *string);
|     char *string,o-Next available input string.
|
|     Error Conditions:
|       If there are no remaining characters in the local input buffer,
|     string is returned as the end of record character specified by the
|     previous call to bfinc().
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Character data must have been previously read into the local
|     input buffer by a call to routine bfinc().  Character strings are
|     then accessed from the buffer, in order, by consecutive calls to
|     routines alprdc(), bfgetc(), intrdc(), and/or relrdc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void bfgetc(char *string)
#else
  void bfgetc(string)
  char *string;
#endif
{
  if (inloc) {
    strcpy(string, inloc);
    inloc = NULL;
  } else {
    string[0] = EOR;
    string[1] = '\0';
  }
  return;
}
