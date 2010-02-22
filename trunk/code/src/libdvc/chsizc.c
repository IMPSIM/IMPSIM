/* ------------------------------------------------------------------ */
/* chsizc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Set the character width for future stroke generated characters
|     produced by routines htextc(), vtextc(), and/or symblc().
|
|     Access:
|       (void) chsizc(real width);
|     real width,i-Desired character width in screen units including
|       intercharacter spacing.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       If hardware character generation is possible, stroke generated
|     characters are never used by textc(), but only by htextc(),
|     vtextc() and symblc().
|       Hardware character generation for all characters may be reques-
|     ted by calling stdchc().
|       If width <= 0.0, future characters will be produced by the
|     graphic display hardware character generator if one exists.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void chsizc(real width)
#else
  void chsizc(width)
  real width;
#endif
{
  char fileid[MXFLCH+1];
 
  if (width <= 0.0) {
    stdchc(0);
  } else {
    strcpy(fileid, getenv("JJUHOME"));
    strcat(fileid, "symblu.dat");
    if (lunsmb <= 0){
      lunsmb = lunitc("file");
      if ((streams[lunsmb] = fopen(fileid, "rb")) == NULL) abortc();
    }
    ssymbl = width;
    tsymbl = 11.0 * ssymbl / 7.0;
  }
  return;
}
