/* ------------------------------------------------------------------ */
/* ptextc-09 Jan 06:15 Oct 06
|     (C)Copyright, JJU Research, 2006
|
|     Description:
|       Output a string of characters to display a specified pointer 
|     on the alphanumeric display screen starting at the current alpha
|     pen location using p format.
|
|     Access:
|       (void) ptextc(void *value)
|     void *value,i-The pointer value to be output.
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
|       It is assumed that ptextc() will follow a call to textc() which
|     will specify proper carriage control information.  ptextc() itself
|     ends with an implicit crlf of FALSE.
|       Upon reaching the right screen boundary, any remaining charac-
|     ters are truncated.
*
*     History:
*     09 Jan 06:JJU-Original.
*     15 Oct 06:JJU-Implemented crlfc().
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void ptextc(void *value)
#else
  void ptextc(value)
  void *value;
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
  sprintf(buffer, "%-p", value);
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
