/* ------------------------------------------------------------------ */
/* newpgc-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Erase the screen and place the alpha and graphic pens at their
|     home locations.
|
|     Access:
|       (void) newpgc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void newpgc()
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
# endif
  int i;
 
/* Clear the graphics screen. */
  if (dspdvc == DT_GRAPHIC) {
#   ifdef __WATCOMC__
      _clearscreen(_GCLEARSCREEN);
#   else
      XFillRectangle(dsp, pixmap, bkgnd_gc, 0, 0, xpix, ypix);
      txt_drwn = FALSE;
      pix_drwn = FALSE;
#   endif
 
/* Issue a formfeed for alpha screens. */
  } else {
    bfputc("\n\f");
  }
 
/* Start a new page on the print file. */
  if (lunpr > 0) fputs("\n\f", streams[lunpr]);
 
/* Clear the circular text buffer. */
  for (i=0; i<imax; i++) *(textq[i]) = '\0';
 
/* Update the global variables. */
  amodec();
  ipen   = line0;
  jpen   = 0;
  crlf   = TRUE;
  lsmode = FALSE;
  lspen  = FALSE;
  spen   = smin;
  tpen   = tmax;
  return;
}
