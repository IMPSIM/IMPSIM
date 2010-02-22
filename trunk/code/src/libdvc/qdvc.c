/* ------------------------------------------------------------------ */
/* qdvc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       This routine returns character strings identification for the
|     current display, choice, and locator devices.
|
|     Access:
|       (void) qdvc(char *dsplay, char *chdevc, char *lcdevc);
|     char *dsplay,o-Current graphic display device id. Possible id's
|       returned are:
|       dsplay = "alpha"   for a non-graphic alphameric-only display.
|       dsplay = "graphic" for a graphic workstation  color display.
|     char *chdevc,o-Current choice device id; possible id's are:
|       chdevc = "alpha"   for alphanumeric keyboard choice input.
|       chdevc = "locator" for choice input from the locator device.
|     char *lcdevc,o-Current locator device id; possible id's are:
|       lcdevc = "alpha"  for alphanumeric keyboard locator input.
|       lcdevc = "mouse"  for mouse locator input.
|       lcdevc = "tablet" for tablet locator input.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().  It may be redefined at will by subsequent calls to
|     devic().
|       The choice and locator devices may be redefined by subsequent
|     calls to chcdvc() and/or locdvc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qdvc(char *dsplay, char *chdevc, char *lcdevc)
#else
  void qdvc(dsplay, chdevc, lcdevc)
  char *dsplay, *chdevc, *lcdevc;
#endif
{
  strcpy(dsplay, DspTyp[dspdvc]);
  strcpy(chdevc, ChcTyp[chdvc]);
  strcpy(lcdevc, LocTyp[lcdvc]);
  return;
}
