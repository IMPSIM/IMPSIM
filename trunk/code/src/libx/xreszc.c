/* ------------------------------------------------------------------ */
/* xreszc-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       This function handles a resize of the X window.
|
|     Access:
|       (void) xreszc(XConfigureEvent *xce);
|     XConfigureEvent *xce,i-The resize event. 
|    
|     Error Conditions:
|       None.
|
|     Comments:
|       This function is not intended for use by the applications
|     programmer; it is a service routine for use within the X library.
|       The X library must have been initialized by a previous call to
|     function xinitc(). 
|       This function handles only resize events, all other configura-
|     tion events are ignored.  On resize, this routine attempts to save
|     as much alpha text as possible.  The graphics screen is cleared
|     and repainted by paintc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#if defined(__WATCOMC__)
  void xreszc()
#elif defined(ANSI)
  void xreszc(XConfigureEvent *xce)
#else
  void xreszc(xce)
  XConfigureEvent *xce;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
    char *new_text_buff, **new_textq; 
    int  *new_text_color;
    int   i, line, new_ipen, new_imax, new_jmax, new_xpix, new_ypix,
      num_lines;

    new_xpix = xce->width;
    new_ypix = xce->height;
  
/* Ignore everything but size changes. */
    if ((new_xpix == xpix) && (new_ypix == ypix)) return;

/* Take largest sqare as the new window. */ 
    xpix = min(new_xpix, new_ypix);
    ypix = xpix;
    new_imax = (ypix / font_height) - 1;
    new_jmax = MXIOBF;
  
/* Free up pixmaps that were grabbed. */
    XFreePixmap(dsp, pixmap);
    XFreePixmap(dsp, txtmap);
  
/* Make new pixmaps; make one for graphics. */
    pixmap = XCreatePixmap(dsp, win, xpix, ypix, depth);
    XFillRectangle(dsp, pixmap, bkgnd_gc, 0, 0, xpix, ypix);
  
/* And one for text. */
    txtmap = XCreatePixmap(dsp, win, xpix, ypix, depth);
    XFillRectangle(dsp, txtmap, bkgnd_gc, 0, 0, xpix, ypix); 
  
/* Make a new text buffer if needed. */
    if (new_imax != imax) {
      new_text_buff = (char *) malloc( new_imax * (MXIOBF + 1));
      new_textq = (char **) malloc( sizeof(char *) * new_imax );
      new_text_color = (int *) malloc( sizeof(int) * new_imax );
      if ((! new_text_buff) || (! new_textq) || (! new_text_color)) {
        fprintf(stderr, "Fatal error in xreszc: Out of memory.\n");
        exit(0);
      }
      for (i=0; i < new_imax; i++) {
        new_textq[i] = &(new_text_buff[i * (MXIOBF + 1)]);
        new_textq[i][0] = '\0';
        new_text_color[i] = kfrgnd;
      }
  
/* Now recopy old text buffer (as much as possible). */
      num_lines = ipen -line0 - imin + 1;
      if (num_lines < 0) num_lines += imax;

/* Copy as many as possible. */ 
      if (num_lines > new_imax) {
        line0 = (line0 + num_lines - new_imax) % imax;
      }
      line = line0;
      new_ipen = 0;
      for (i=0; i < new_imax; i++) {
        strcpy(new_textq[i], textq[line]);
        new_text_color[i] = text_color[line];
        if (line == ipen) {
          new_ipen = i;
          break;
        }
        line = (++line) % imax;
        if (line == line0) break;
      } 
 
/* Free old text buffer and queue. */ 
      free(text_buff);
      free(textq);
      free(text_color);
      text_buff  = new_text_buff;
      textq      = new_textq;
      text_color = new_text_color;
 
/* Reset line0, ipen, imax, jmax. */ 
      line0 = 0;
      ipen  = min(new_ipen, new_imax - 1);
      if (crsr) crsry = (ipen + 1) * font_height;
      imax  = new_imax;
      jmax  = new_jmax;
    }

/* Call-back to a repaint routine. */
    paintc(0);
    xposec();
# endif
  return;
}
