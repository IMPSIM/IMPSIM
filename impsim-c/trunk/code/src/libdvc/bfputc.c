/* ------------------------------------------------------------------ */
/* bfputc-01 Jan 00:13 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Put a character string into the local output buffer.
|
|     Access:
|       (void) bfputc(char *string);
|     char *string,i-String to be placed in i/o buffer.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Characters, including non-printing ASCII characters, may be
|     stored in the local output buffer by calls to bfputc().
|       The local output buffer is automatically output when it becomes
|     filled.  It may be output before it is filled by calling bflshc()
|     or clrplc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void bfputc(char *string)
#else
  void bfputc(string)
  char *string;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
# endif
  int length;

  if (dspdvc == DT_GRAPHIC) {
#   ifdef __WATCOMC__
      if (lunio > 0) _outtext(string);
#   endif
  } else {
    if (lunio > 0) fputs(string, streams[lunio]);
  }
  length = min(strlen(string), (jmax - jpen));
  text_color[ipen] = icolra;
  strncpy(&(textq[ipen][jpen]), string, length);
  jpen += length;
  textq[ipen][jpen] = '\0';
  return;
}
