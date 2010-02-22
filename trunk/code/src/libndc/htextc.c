/* ------------------------------------------------------------------ */
/* htextc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Plot a horizontal string of characters on the graphic display
|     device starting at the current pen location.
|
|     Access:
|       (void) htextc(char *text);
|     char *text,i-Character string to be plotted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine will output either hardware generated characters or
|     stroke generated characters, depending on any previous calls to
|     chsizc() and/or stdchc().
|       Any nonprintable characters, i.e. those not in the range between
|     ASCII 32 and ASCII 126 inclusive, are not printed.
|       Any remaining characters are truncated from the specified string
|     upon reaching the right screen boundary.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void htextc(char *text)
#else
  void htextc(text)
  char *text;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
    int txt_x, txt_y; 
# endif
  int nchars;

  if (dspdvc == DT_GRAPHIC) {
    nchars = strlen(text);
#   ifdef __WATCOMC__
      _grtext_w(spen, (tpen + 0.7 * tsymbl), text);
      spen += nchars * ssymbl;
#   else
      AbstoPix(txt_x, txt_y, spen, tpen);
      if (nchars) {
        XDrawString(dsp, pixmap, gtext_gc, txt_x, txt_y, text, nchars);
        pix_drwn = TRUE;
      }
      txt_x += XTextWidth(font_info, text, nchars); 
      PixtoAbs(spen, tpen, txt_x, txt_y);
#   endif
    spen  = min(spen, smax);
    lspen = FALSE;
    l2pen = FALSE;
    l3pen = FALSE;
  }
  return;
}
