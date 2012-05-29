/* ------------------------------------------------------------------ */
/* colrfc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Set the foreground color for future graphic output.
|
|     Access:
|       (void) colrfc(int icolor)
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
  void colrfc(int icolor)
#else
  void colrfc(icolor)
  int  icolor;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
# endif
  int kolor;
 
  if ((icolor >= 0) && (icolor < MXCOLOR)) {
    if (dspdvc == DT_GRAPHIC) {
      kolor = icolrc(icolor);
#     ifdef __WATCOMC__
        _setcolor(kolor);
#     else
        XSetForeground(dsp, line_gc, colors[kolor]);
        XSetForeground(dsp, fill_gc, colors[kolor]);
#     endif
      icolrf = icolor;
    }
  }
  return;
}
