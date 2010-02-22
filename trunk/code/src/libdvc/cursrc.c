/* ------------------------------------------------------------------ */
/* cursrc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Turn the X window cursor on (to a red arrow) or off (to a watch)
|     depending on the argument passed.
|
|     Access:
|       (void) cursrc(int flag)
|     int flag,i-Flag indicating if cursor should be turned off (0) or
|       on (non-zero).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The device must be GRAPHIC.  Otherwise, no action is taken.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void cursrc(int flag)
#else
  void cursrc(flag)
  int flag;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
 
/* Change the cursor to a red arrow. */
    if (dspdvc == DT_GRAPHIC) {
      if (flag) {
        XDefineCursor(dsp, win, arrow_cursor);
 
/* Change the cursor to a watch. */
      } else {
        XDefineCursor(dsp, win, watch_cursor);
      }
      XFlush(dsp);
    }
# endif
  return;
}
