/* ------------------------------------------------------------------ */
/* xinitc-01 Jan 00:29 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       This function initializes the X library, setting up the colors,
|     graphic context, and other defaults.
|
|     Access:
|       root = (Window) xinitc();
|     Window root,o-The root window of this display.
|    
|     Error Conditions:
|       None.
|
|     Comments:
|       The X library must be initialized with a call to this function
|     before any of the other X library calls are used.
|       If X has already been initialized this function simply returns
|     the root window that was obtained by that call.
*
*     History:
*     01 Jan 00:JJU-Original.
*     16 Feb 03:JJU-Renamed globlx.h to xglblc.h.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef __WATCOMC__
  void xinitc()
{
#else
  Window xinitc()
{
# include "xglblc.h"
# define DFLTXMIN   500            /* Default window characteristics. */
# define DFLTYMIN   500
# define DFLTXPIX   750
# define DFLTYPIX   750
# define DFLTXPOS    50
# define DFLTYPOS    50
# define DFLTFONT "9x15"                             /* Default Font. */
# define RED          2
  char *displayname = NULL;
    
  if (X_Initialized) {
                        /* No action if this routine is called again. */
  } else {
    strcpy(FontName, DFLTFONT);
    xpos  = DFLTXPOS;
    ypos  = DFLTYPOS;
    xpix  = DFLTXPIX;
    ypix  = DFLTYPIX;
    xwmin = DFLTXMIN;
    ywmin = DFLTYMIN;
    if ((dsp = XOpenDisplay(displayname)) == NULL) {
      fprintf(stderr, "Error: Bad display name = <%s>\n",displayname);
      exit(-1);
    }
    screen = DefaultScreen(dsp);
    rootwin = RootWindow(dsp, screen);
    event_mask = ExposureMask | StructureNotifyMask | ButtonPressMask 
      | KeyPressMask | KeyReleaseMask;        /* For Ctrl-C handling. */
    xcolrc(dsp, screen);
    xmkgcc(dsp, rootwin);
    arrow_cursor = XCreateFontCursor(dsp, XC_top_left_arrow); 
    XRecolorCursor(dsp, arrow_cursor, &(xcolors[RED]),
      &(xcolors[BLACK]));
    watch_cursor = XCreateFontCursor(dsp, XC_watch); 
    XRecolorCursor(dsp, watch_cursor, &(xcolors[BLACK]),
      &(xcolors[WHITE]));
    X_Initialized = TRUE;
  }
  return(rootwin);
# undef DFLTXMIN
# undef DFLTYMIN
# undef DFLTXPIX
# undef DFLTYPIX
# undef DFLTXPOS
# undef DFLTYPOS
# undef DFLTFONT
# undef RED
#endif
}
