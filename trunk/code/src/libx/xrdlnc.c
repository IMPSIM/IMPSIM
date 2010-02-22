/* ------------------------------------------------------------------ */
/* xrdlnc-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       This function gets a line from the keyboard, echoing it to the
|     screen as it is typed.
|
|     Access:
|       (void) xrdlnc();
|    
|     Error Conditions:
|       None.
|
|     Comments:
|       This function is not intended for use by the applications
|     programmer; it is a service routine for use within the X library.
|       The X library must have been initialized by a previous call to
|     function xinitc(). 
|       This function reads a line from X terminated by an enter.
|       This routine handles the text cursor and key events building the
|     string as keys are pressed.  The line is placed into the global
|     input buffer. 
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void xrdlnc()
{
# ifndef __WATCOMC__
#   include "xglblc.h"
    XKeyEvent *keyreport;
    KeySym keysym;
    char string[2];
    int  j, j0, jchar, length, width;

/* Initialize. */
    memset(inbufr, '\0', MXINBF);
    textq[ipen][jmax] = '\0';
    j0 = jchar = jpen;
    string[0] = '\0';
    string[1] = '\0';
    j = 0;
    crsry  = (ipen + 1) * font_height;
    crsron = TRUE;

/* Get the current cursor position. */
    do {
      crsrx = XTextWidth(font_info, textq[ipen], strlen(textq[ipen]));
      if (atext_en)
        XDrawString(dsp, win, text_gc, crsrx, crsry, crsr, 1);
      keyreport = (XKeyEvent *) xloopc(KeyPressMask);
      length = XLookupString(keyreport, string, 1, &keysym,
        (XComposeStatus *) NULL);      /* Assume length is 1 for now. */

/* Erase the cursor (draw it in background color). */
      if (atext_en) XDrawString(dsp, win, bkgnd_gc, crsrx,crsry,crsr,1);

/* Remove any control characters and echo the string. */
      if (length) {
        switch(*string) {
        case '\r':                              /* A carriage return. */
        case '\n':                                      /* A newline. */
          goto DONE;
          break;
        case '\b':                                    /* A backspace. */
          j = max(0, j - 1);
          inbufr[j] = '\0';
          jchar = max(j0, jchar - 1);
          width = XTextWidth(font_info, textq[ipen],
            (strlen(textq[ipen]) - 1)); 
          if (atext_en) XDrawString(dsp, win, bkgnd_gc, width, crsry,
            &(textq[ipen][jchar]), 1);
          textq[ipen][jchar] = '\0';
          break;
        default:                    /* All other (normal) characters. */
          inbufr[j++] = *string;
          textq[ipen][jchar++] = *string;
          textq[ipen][jchar] = '\0';
          if (jchar == jmax) {              /* Keep it on the screen. */
            textq[ipen][--jchar] = '\0';
            inbufr[--j] = '\0';
          }
          if (atext_en)          /* Redraw line on window right away. */
            XDrawString(dsp, win, text_gc, 0, crsry, textq[line0+ipen],
              strlen(textq[ipen]));
          break;
        }
      } else {                 /* Arrow Key, shift or something else. */
      }
    } while (j < MXINBF);
DONE:                                             /* Turn off cursor. */
    crsron = FALSE;
    jpen += jchar - j0;
    inbufr[MXINBF] = '\0';
# endif
  return;
}
