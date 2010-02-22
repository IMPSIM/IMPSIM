/* ------------------------------------------------------------------ */
/* bflshc-01 Jan 00:13 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Output to the standard output device any remaining character
|     data stored in the local output buffer.
|
|     Access:
|       (void) bflshc();
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
|     filled.  It may be forced to output before it is filled by calling
|     bflshc() or clrplc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void bflshc()
{
# ifndef __WATCOMC__
#   include "xglblc.h"
 
    if (dspdvc == DT_GRAPHIC) {
 
/* Check for any Events needing attention (Expose, Resize, etc.); recopy
     the window (like an expose) if new elements have been put into the
     pixmap since the last expose. */
      xloopc(NoEventMask);
      if (pix_drwn) {
        xposec();
        XFlush(dsp);
      }
    }
# endif
  if (lunio > 0) fflush(streams[lunio]);
  return;
}
