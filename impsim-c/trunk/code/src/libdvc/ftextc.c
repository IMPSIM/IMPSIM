/* ------------------------------------------------------------------ */
/* ftextc-22 Oct 00:15 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Output a string of characters to display a given real value on
|     the alphanumeric display screen starting at the current alpha pen
|     location in f format.
|
|     Access:
|       (void) ftextc(real value)
|     real value,i-The real value to be output.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine is intended for output on the alphanumeric screen
|     rather than the graphic screen.
|       It is assumed that a call to textc() will follow ftextc() and
|     will specify proper carriage control information.  ftextc() itself
|     ends with an implicit crlf of FALSE.
|       Upon reaching the right screen boundary, any remaining charac-
|     ters are truncated.
*
*     History:
*     22 Oct 00:JJU-Original.
*     08 Dec 05:JJU-Changed to f format with gtextc() implemented.
*     15 Oct 06:JJU-Implemented crlfc().
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void ftextc(real value)
#else
  void ftextc(value)
  real value;
#endif
{
# ifndef __WATCOMC__
#   include "xglblc.h"
# endif
  char buffer[16];
  char *chr;

/* Finish the previous line with a newline if needed. */
  crlfc();

/* Output the new real information in text. */
  sprintf(buffer, "%#-011.4f", value);
  buffer[lenc(buffer)]='\0';         /* Truncate any trailing blanks. */
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
