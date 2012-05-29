/* ------------------------------------------------------------------ */
/* locdvc-01 Jan 00:24 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the locator device for subsequent graphic input from the
|     keyboard or mouse or tablet.
|
|     Access:
|       (void) locdvc(char *kind)
|     char *kind,i/o-Locator device type:
|       kind = "alpha"  for the alphanumeric keyboard.
|       kind = "mouse"  for a mouse.
|       kind = "tablet" for a tablet.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The graphic display device must have been defined by a previous
|     call to devic().
|       Before this routine is called, the default locator device type
|     is kind = "alpha".
|       If execution is not interactive, kind is treated as "alpha".
|       Routine locdvc() may be called as often as desired to switch
|     among different locator devices.
|       If kind is not recognized, or not available on the current
|     display device, it is treated as a system dependent locator device
|     type.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void locdvc(char *kind)
#else
  void locdvc(kind)
  char *kind;
#endif
{
  char type[8];
 
  strcpy(type, kind);
  stripc(type);
  type[lenc(type)] = '\0';
  lcasec(type);
  if (intact) {
    if (dspdvc == DT_ALPHA) {
      if (strcmp(type, "alpha") != 0) {
        textc("Warning: Invalid locator device set to 'alpha'.", TRUE);
        lcdvc = LT_ALPHA;
      }
    } else if (dspdvc == DT_GRAPHIC) {
      if (strcmp(type, "alpha") == 0) {
        lcdvc = LT_ALPHA;
      } else if (strcmp(type, "mouse") == 0) {
        lcdvc = LT_MOUSE;
      } else if (strcmp(type, "tablet") == 0) {
        lcdvc = LT_TABLET;
      } else {
        textc("Warning: Invalid locator device set to 'mouse'.", TRUE);
        lcdvc = LT_MOUSE;
      }
    }
  } else {
    if (strcmp(type, "alpha") != 0) {
      textc("Warning: Noninteractive locator device set to 'alpha'.",
        TRUE);
      lcdvc = LT_ALPHA;
    }
  }
  return;
}
