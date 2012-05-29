/* ------------------------------------------------------------------ */
/* xclosc-01 Jan 00:29 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       This function closes an X window and frees the associated
|     memory.
|
|     Access:
|       (void) xclosc(Window win)
|     Window win,i-The window to be closed. 
|    
|     Error Conditions:
|       None.
|
|     Comments:
|       The X library must have been initialized by a previous call to
|     function xinitc().
|       The window must have been obtained through a call to xopenc(). 
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#if defined(__WATCOMC__)
  void xclosc()
#elif defined(ANSI)
  void xclosc(Window w)
#else
  void xclosc(w)
  Window w;
#endif

{
# ifndef __WATCOMC__
#   include "xglblc.h"

/* Unmap and free window. */
    XUnmapWindow(dsp, w);
    XDestroyWindow(dsp, w);
    XFree((caddr_t) &w);

/* Free pixmaps. */
    XFreePixmap(dsp, pixmap);
    XFreePixmap(dsp, txtmap);
# endif
  return;
}
