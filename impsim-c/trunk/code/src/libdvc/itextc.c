/* ------------------------------------------------------------------ */
/* itextc-22 Oct 00:15 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Output a string of characters to display a specified integer on
|     the alphanumeric display screen starting at the current alpha pen 
|     location.
|
|     Access:
|       (void) itextc(int intger)
|     int intger,i-The integer value to be output.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine is intended for output on the alphanumeric screen
|     rather than the graphic screen.
|       Text information to be placed onto the alpha screen should be
|     written by textc().
|       It is assumed that textc() will follow a call to itextc() and
|     will specify proper carriage control information.  itextc() itself
|     ends with an implicit crlf of FALSE.
|       Upon reaching the right screen boundary, any remaining charac-
|     ters are truncated.
*
*     History:
*     22 Oct 00:JJU-Original.
*     15 Oct 06:JJU-Implemented crlfc().
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void itextc(int intger)
#else
  void itextc(intger)
  int  intger;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
# endif
  char buffer[16];
  char *chr;

/* Finish the previous line with a newline if needed. */
  crlfc();

/* Output the new integer information in text. */
  _itoa(intger, buffer, 10);
  bfputc(buffer);
  if (lunpr > 0) {
    for (chr=buffer; *chr; chr++) {
      if (*chr >= SPACE) putc(*chr, streams[lunpr]);
    }
  }
# ifndef __WATCOMC__
/* Process events to allow for scroll-lock. */
    if (X_Initialized) xloopc(NoEventMask);
# endif

/* Update the flag showing no newline before the next textc(). */ 
  crlf = FALSE;
  return;
}
