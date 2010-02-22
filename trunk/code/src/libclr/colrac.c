/* ------------------------------------------------------------------ */
/* colrac-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Set the color for future alpha output.
|
|     Access:
|       (void) colrac(int icolor)
|     int icolor,i-JJU Color index.
|
|     Error Conditions:
|       If icolor is not in the range 0 <= icolor < MXCOLOR, no action
|     is taken.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void colrac(int icolor)
#else
  void colrac(icolor)
  int  icolor;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
# endif
  int kolor;
 
  if (icolor >= 0 && icolor < MXCOLOR) {
    if (dspdvc == DT_GRAPHIC) {
      kolor = icolrc(icolor);
#     ifdef __WATCOMC__
        _settextcolor(kolor);
#     else
        XSetForeground(dsp, text_gc, colors[kolor]);
        pix_drwn |= txt_drwn;
#     endif
      icolrs = icolra = icolor;
    }
  }
  return;
}
