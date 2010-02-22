/* ------------------------------------------------------------------ */
/* xmkgcc-01 Jan 00:01 Jan 04
|    (C)Copyright, JJU Research, 2000-2004.
|
|    Description:
|      This function creates all graphics contexts (GCs) for the X
|    library.
|
|    Access:
|      (void) xmkgcc(Display *dsplay, Window wndw)
|    Display *dsplay,i-A pointer to the display.    
|    Window   wndw,  i-A window. 
|    
|    Error Conditions:
|      None.
|
|    Comments:
|      This function is not intended for use by the applications
|    programmer; it is a service routine for use within the X library.
|      This function creates five GCs for: regular text, graphics text,
|    lines, filled areas, and the background.
*
*    History:
*    01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#if defined(__WATCOMC__)
  void xmkgcc()
#elif defined(ANSI)
  void xmkgcc(Display *dsplay, Window wndw)
#else
  void xmkgcc(dsplay, wndw)
  Display *dsplay;
  Window   wndw;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
    XGCValues xgcvalues;

    xgcvalues.foreground = colors[WHITE];
    xgcvalues.background = None;
    xgcvalues.graphics_exposures = FALSE;

/* Create text GCs. */
    text_gc = XCreateGC(dsplay, wndw,
      (GCForeground | GCBackground | GCGraphicsExposures), &xgcvalues);
    gtext_gc = XCreateGC(dsplay, wndw,
      (GCForeground | GCBackground | GCGraphicsExposures), &xgcvalues);

/* Load a font. */
    font_info = XLoadQueryFont(dsplay, FontName);
    if (font_info == NULL) {
      fprintf(stderr, "Error: Can not open the %s font.\n", FontName);
      return;
    }
    
/* Set the font into the text GCs. */
    XSetFont(dsplay, text_gc,  (font_info)->fid);
    XSetFont(dsplay, gtext_gc, (font_info)->fid);
    font_height = font_info->ascent + font_info->descent;

/* Now create graphic GCs. */
    xgcvalues.foreground = colors[WHITE];
    xgcvalues.background = colors[BLACK];
    xgcvalues.graphics_exposures = FALSE;
    line_gc = XCreateGC(dsplay, wndw,
      (GCForeground | GCBackground | GCGraphicsExposures), &xgcvalues);
    fill_gc = XCreateGC(dsplay, wndw,
      (GCForeground | GCBackground | GCGraphicsExposures), &xgcvalues);
   
/* The background GC: used to erase things. */ 
    xgcvalues.foreground = colors[BLACK];
    bkgnd_gc = XCreateGC(dsplay, wndw,
      (GCForeground | GCBackground | GCGraphicsExposures), &xgcvalues);
    
/* Set the font in this GC (for erasing single characters). */
    XSetFont(dsplay, bkgnd_gc, (font_info)->fid);
# endif
  return;
}
