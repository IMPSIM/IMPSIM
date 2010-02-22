/* ------------------------------------------------------------------ */
/* rvsvdc-01 Jan 00:01 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
|
|     Description:
|       This routine switches white and black in the colormap.
|
|     Access:
|       (void) rvsvdc();
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
void rvsvdc()
{
# ifdef __WATCOMC__
    static int kblack = 0, kwhite = 1;
# else
#   include "xglblc.h"
    int tmp;
    XColor xtmp;
# endif
 
  if (dspdvc == DT_GRAPHIC) {
#   ifdef __WATCOMC__
      kblack = 1 - kblack;
      cmapc(kblack, 0, 0, 0);
      kwhite = 1 - kblack;
      cmapc(kwhite, 0, 99, 99);
#   else
      xtmp           = xcolors[BLACK];
      xcolors[BLACK] = xcolors[WHITE];
      xcolors[WHITE] = xtmp;
      tmp            = colors[BLACK];
      colors[BLACK]  = colors[WHITE];
      colors[WHITE]  = tmp;
      XSetBackground(dsp, text_gc,  colors[BLACK]);
      XSetBackground(dsp, gtext_gc, colors[BLACK]);
      XSetBackground(dsp, line_gc,  colors[BLACK]);
      XSetBackground(dsp, fill_gc,  colors[BLACK]);
      XSetForeground(dsp, bkgnd_gc, colors[BLACK]);
      XSetBackground(dsp, bkgnd_gc, colors[BLACK]);
      XFillRectangle(dsp, pixmap, bkgnd_gc, 0, 0, xpix, ypix);
      XFillRectangle(dsp, txtmap, bkgnd_gc, 0, 0, xpix, ypix);
      rev_video = !(rev_video);
      colrac(icolra);
      colrfc(icolrf);
      colrsc(icolrs);
/*    paintc(0); */
      xposec();
#   endif
  }
  return;
}
