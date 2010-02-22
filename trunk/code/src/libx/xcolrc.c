/* ------------------------------------------------------------------ */
/* xcolrc-01 Jan 00:29 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|  
|     Description:
|       Create the default JJU colormap.
|
|     Access:
|       (void) xcolrc(Display *dsplay, int screen)
|     Display *dsplay,i-A pointer to the display.    
|     int screen,i-The screen. 
|    
|     Error Conditions:
|       If one of the color names is not recognized, that color is not
|     allocated.  A message is printed.
|       If all color cells become allocated execution is aborted.
|
|     Comments:
|       This function is not intended for use by the applications
|     programmer; it is a service routine for use within the X library.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#if defined(__WATCOMC__)
  void xcolrc()
#elif defined(ANSI)
  void xcolrc(Display *dsplay, int scrn)
#else
  void xcolrc(dsplay, scrn)
  Display *dsplay;
  int      scrn;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
#   if defined(ANSI)
      static char *name[MXCOLOR] =
        { "black", "white",       "red",    "orange red",
          "orange","gold",        "yellow", "chartreuse",
          "green", "spring green","cyan",   "dodger blue", 
          "blue",  "dark violet", "magenta","deep pink" };
#   endif
    int j;

    cmap = DefaultColormap(dsplay, scrn);
    for (j=0; j<MXCOLOR; j++) {
      if (XParseColor(dsplay, cmap, name[j], &(xcolors[j]))) {
        if (XAllocColor(dsplay, cmap, &(xcolors[j]))) {
          colors[j] = (xcolors[j]).pixel;
        } else {
          fprintf(stderr, "Color %s is not allocated.\n", name[j]);
          exit(0);
        }
      } else {
        fprintf(stderr, "Basic color %s is not recognized.\n", name[j]);
      }
    }
    rev_video = FALSE;   /* Set flag to show colors are not reversed. */
# endif
  return;
}
