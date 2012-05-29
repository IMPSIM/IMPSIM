/* ------------------------------------------------------------------ */
/* xloopc-01 Jan 00:01 Jan 04
|    (C)Copyright, JJU Research, 2000-2004.
|
|    Description:
|      This function is the main event loop for the X library.
|
|    Access:
|      event = (XEvent *) xloopc(Mask emask);
|    Mask emask,   i-A mask of the events (if any) that are interesting.
|    XEvent *event,o-An event matching the mask. 
|    
|    Error Conditions:
|      None.
|
|    Comments:
|      The X library must have been initialized by a previous call to
|    function xinitc(). 
|      This function contains an event loop which processes the more
|    mundane Events (Expose, Configure) itself, passing back an event
|    whose type is one of those specified in the Mask.  This routine may
|    be called with an empty event mask (NoEventMask); in that case all
|    pending (queued) events are processed, and a NULL pointer is
|    returned. 
*
*    History:
*    01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#if defined(__WATCOMC__)
  void xloopc()
#elif defined(ANSI)
  XEvent *xloopc(Mask emask)
#else
  XEvent *xloopc(emask)
  Mask emask;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
#   define INTRPT_KEY XK_ccedilla             /* This is "Control-C". */
    int pending;
    KeySym keysym;
    XKeyEvent *xke;

    do {
      pending = XPending(dsp);
      do {
        if ((emask == NoEventMask) && (pending == 0)) break;
        XNextEvent(dsp, &report);
        switch(report.type) {
        case Expose:
          if (emask & ExposureMask) return(&report);
          while ((XPending(dsp) > 0) && /* Clear any waiting exposes. */
            (XPeekEvent(dsp, &report), report.type == Expose)) {
              XNextEvent(dsp, &report);
          }
          xposec();
          break;
        case ConfigureNotify:
          xreszc((XConfigureEvent *) &report);
          break;
        case MappingNotify:     /* Keyboard configuration may change. */
          XRefreshKeyboardMapping((XMappingEvent *) &report); 
          break;
        case ButtonPress:
          if (emask & ButtonPressMask) return(&report);
          break;
        case KeyPress:
          xke = (XKeyEvent *) &report;
          keysym = XKeycodeToKeysym(dsp, xke->keycode, ctrl_indx);
          if (keysym == XK_Escape) {  /* Escape is alpha text toggle. */
            if (atext_en) {
              atext_en = FALSE;
            } else {
              atext_en = TRUE;
            }
            xposec();              /* Update the screen immediatedly. */
            break;
          }
          if ((keysym == XK_Control_L) || (keysym == XK_Control_R)) {
            ctrl_indx = ControlMapIndex;    /* Check for control key. */
          }
          if ((keysym == XK_Break) || (keysym == XK_Cancel)
            || (keysym == INTRPT_KEY)) {
            if (kbwtch) kbint = TRUE;       /* Check for break/abort. */
          } else if (keysym == XK_ssharp) {      /* Check for Ctrl-S. */
            scroll_en = FALSE;
          } else if (keysym == XK_periodcentered){/*Check for Ctrl-Q. */
            scroll_en = TRUE;
          } else if (emask & KeyPressMask) {
            return(&report);
          }
          break;
        case KeyRelease:
          xke = (XKeyEvent *) &report;
          keysym = XKeycodeToKeysym(dsp, xke->keycode, 0);
          if ((keysym == XK_Control_L) || (keysym == XK_Control_R)) {
            ctrl_indx = 0;
          }
          break;
        default:
          break;                     /* Throw away any unknown event. */
        }
      } while (--pending > 0); 
      if (emask == NoEventMask) return((XEvent *) NULL);
    } while(TRUE);
    return((XEvent *) NULL);                        /*   Unreachable. */
#   undef INTRPT_KEY
# endif
}
