/* ------------------------------------------------------------------ */
/* crlfc-15 Oct 06
|     (C)Copyright, JJU Research, 2006.
|
|     Description:
|       Output a newline at the current alpha pen location if required.
|
|     Access:
|       (void) crlfc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Text information to be placed on the alpha screen should be
|     written by textc(), itextc(), ftextc(), gtextc() and/or ptextc().
|     It is assumed that the last of these is a call to textc().  The
|     lcrtn argument in this call determines if a call to crlf() is
|     needed at a later time.
*
*     History:
*     15 Oct 06:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void crlfc()
{
# include "..\libcad\devic.h"
# include "..\libcad\iodvc.h"
# include "..\libcad\screnc.h"
# ifndef __WATCOMC__
#   include "xglblc.h"
# endif

/* Insure the system is in alpha mode. */
  amodec();
# ifndef __WATCOMC__
    pix_drwn = txt_drwn = TRUE;
# endif

/* Finish the previous line with a newline if needed. */
  if (crlf) {
    if (lunpr > 0) putc('\n', streams[lunpr]);
#   ifdef __WATCOMC__
      bfputc("\n");
#   else
      if (dspdvc != DT_GRAPHIC) bfputc("\n");
#   endif
    ipen = (++ipen) % imax;
    if (ipen == line0) ipen = line0 + imin;
    jpen = 0;
    textq[ipen][0] = '\0';
#   ifndef __WATCOMC__
      if (dspdvc == DT_GRAPHIC) {
/* Scrolling is not presently enabled; wait until it is. */
        if (X_Initialized && (ipen == (imax - 1)) && ! scroll_en) {
          do xloopc(NoEventMask); while (! scroll_en);
        }
      }
#   endif
  }

/* Update the flag showing that newline has been issued. */ 
  crlf = FALSE;
  return;
}
