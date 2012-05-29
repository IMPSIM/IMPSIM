/* ------------------------------------------------------------------ */
/* xposec-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       This function refreshes the X window using the global pixmaps,
|     and redraws the alpha text if needed.
|
|     Access:
|       (void) xposec();
|    
|     Error Conditions:
|       None.
|
|     Comments:
|       This function is not intended for use by the applications
|     programmer; it is a service routine for use within the X library.
|       The X library must have been initialized by a previous call to
|     function xinitc(). 
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void  xposec()
{
# ifndef __WATCOMC__
#   include "screnc.h"
#   include "xglblc.h"
    int i, j, kolor, length;

    if (txt_drwn && atext_en) {
      XCopyArea(dsp, pixmap, txtmap, line_gc, 0, 0, xpix, ypix, 0, 0);

/* Move circularly through the queue; draw text on txtmap.
   line0 indicates the line that is currently at the top-of-screen. */
      i = (line0 + imin) % imax;
      j = imin;
      do {
        length = strlen(textq[i]);
        if (length) {
          kolor = icolrc(text_color[i]);
          XSetForeground(dsp, text_gc, colors[kolor]);
          XDrawString(dsp, txtmap, text_gc, 0, (j*font_height),
            textq[i], length);
        }
        i = (++i) % imax;
        j++;
      } while (i <= ipen); 
      kolor = icolrc(text_color[icolra]);
      XSetForeground(dsp, text_gc, colors[kolor]);
  
/* Draw the text cursor if it is turned on. */ 
      if (crsron)
        XDrawString(dsp, txtmap, text_gc, crsrx, crsry, crsr, 1);
      XCopyArea(dsp, txtmap, win, text_gc, 0, 0, xpix, ypix, 0, 0);
    } else {
      XCopyArea(dsp, pixmap, win, text_gc, 0, 0, xpix, ypix, 0, 0);
    }
    pix_drwn = FALSE;
# endif
  return;
}
