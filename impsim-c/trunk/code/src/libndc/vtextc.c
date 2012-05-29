/* ------------------------------------------------------------------ */
/* vtextc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Plot a vertical string of characters on the graphic display
|     device starting at the current pen location.
|
|     Access:
|       (void) vtextc(char *text);
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
  void vtextc(char *text)
#else
  void vtextc(text)
  char *text;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
    int j, itext, jtext; 
# endif
  int nchars;

  if (dspdvc == DT_GRAPHIC) {
    nchars = strlen(text);
#   ifdef __WATCOMC__
      _settextpath(_PATH_DOWN);
      _grtext_w(spen, tpen + 0.7 * tsymbl, text);
      _settextpath(_PATH_RIGHT);
      tpen -= nchars * tsymbl;
#   else
      AbstoPix(itext, jtext, spen, tpen);
      for (j=0; j < nchars; j++){
        XDrawString(dsp, pixmap, gtext_gc, itext, jtext, &(text[j]), 1);
        jtext += font_height;
        pix_drwn = TRUE;
      }
      PixtoAbs(spen, tpen, itext, jtext);
#   endif
    tpen  = max(tpen, tmin);
    lspen = FALSE;
    l2pen = FALSE;
    l3pen = FALSE;
  }
  return;
}
