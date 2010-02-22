/* ------------------------------------------------------------------ */
/* textc-01 Jan 00:15 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Output a string of characters to the alphanumeric display screen
|     starting at the current alpha pen location.
|
|     Access:
|       (void) textc(char *text, int lcrtn)
|     char *text, i-Character string to be written.
|     int   lcrtn,i-Flag for desired end-of-text carriage control:
|       lcrtn = TRUE to begin the next textc with a "\n";
|       lcrtn = FALSE for text of the next textc to follow this text.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine is intended for text output on the alphanumeric
|     screen rather than the graphic screen.
|       Text information to be placed onto the graphic picture should
|     not be written with this routine, but rather by htextc() or
|     vtextc().
|       Upon reaching the right screen boundary, any remaining charac-
|     ters are truncated from the specified text.
*
*     History:
*     01 Jan 00:JJU-Original.
*     15 Oct 06:JJU-Implemented crlfc().
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void textc(char *text, int lcrtn)
#else
  void textc(text, lcrtn)
  char *text;
  int   lcrtn;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
# endif
  char *chr;

/* Finish the previous line with a newline if needed. */
  crlfc();

/* Output the new text. */
  bfputc(text);
  if (lunpr > 0) {
    for (chr=text; *chr; chr++) {
      if (*chr >= SPACE) putc(*chr, streams[lunpr]);
    }
  }
# ifndef __WATCOMC__
/* Process events to allow for scroll-lock. */
    if (X_Initialized) xloopc(NoEventMask);
# endif

/* Output the text buffer if necessary. */
  if (lcrtn) bflshc();

/* Update the flag for using a newline on the next textc(). */ 
  crlf = lcrtn;
  return;
}
