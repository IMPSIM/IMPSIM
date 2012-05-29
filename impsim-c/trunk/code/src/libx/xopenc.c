/* ------------------------------------------------------------------ */
/* xopenc-01 Jan 00:19 Nov 06
|    (C)Copyright, JJU Research, 2000-2006.
|
|    Description:
|      This function creates an X window and returns it to the caller.
|
|    Access:
|      win = (Window) xopenc(Window parent);
|    Window parent,i-Parent of this window (usually the root window).
|    Window win,   o-The new window that is created. 
|    
|    Error Conditions:
|      None.
|
|    Comments:
|      The X library must have been initialized by a previous call to
|    function xinitc(). 
|      This function sets all the required attributes for the window and
|    creates extra structures to be used with the window.  Since many of
|    these additional structures are global, only one window should be
|    open at a time.
|      This function also waits for an initial expose event; when this
|    function returns the window can be drawn upon immediately.
*
*    History:
*    01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#if defined(__WATCOMC__)
  void xopenc()
#elif defined(ANSI)
  Window xopenc(Window parent)
#else
  Window xopenc(parent)
  Window parent;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
#   include "btmapc.h"
    Pixmap bitmap;
    Window w;
    XSizeHints    size_hints;
    unsigned int  bdrwidth = 5;
    unsigned long bkgnd, bordr;

    depth = DefaultDepth(dsp, screen);
    bordr = colors[WHITE]; 
    bkgnd = colors[BLACK];
    w = XCreateSimpleWindow(dsp, parent, xpos, ypos, xpix, ypix,
      bdrwidth, bordr, bkgnd);
    size_hints.flags = USPosition | PSize | PMinSize | PPosition;
    size_hints.x = xpos;
    size_hints.y = ypos;
    size_hints.width  = xpix;
    size_hints.height = ypix;
    size_hints.min_width  = xwmin;
    size_hints.min_height = ywmin;
    if (!TitleBar) TitleBar = "JJU Research";
    bitmap=XCreateBitmapFromData(dsp, w, icon_bits, ICON_WIDTH,
      ICON_HEIGHT);
    XSetStandardProperties(dsp, w, "", TitleBar, bitmap, 0, 0,
      &size_hints);
    XSetWindowBackground(dsp, w, colors[BLACK]);
    XStoreName(dsp, w, TitleBar);
    XMapWindow(dsp, w);
    XSelectInput(dsp, w, event_mask);
    XDefineCursor(dsp,w,arrow_cursor);/* Change to the chosen cursor. */
    pixmap = XCreatePixmap(dsp,w,xpix,ypix,depth);/* Graphics pixmap. */
    XFillRectangle(dsp, pixmap, bkgnd_gc, 0, 0, xpix, ypix);
    txtmap = XCreatePixmap(dsp, w, xpix, ypix, depth);/* Text pixmap. */
    XFillRectangle(dsp, txtmap, bkgnd_gc, 0, 0, xpix, ypix); 
    
/* Wait for initial Expose event. */
    (void) xloopc(ExposureMask);
    return(w);
# endif
}
