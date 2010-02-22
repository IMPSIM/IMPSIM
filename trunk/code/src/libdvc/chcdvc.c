/* ------------------------------------------------------------------ */
/* chcdvc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the choice device for subsequent choice input to either the
|     keyboard or the locator.
|
|     Access:
|       (void) chcdvc(char *kind);
|     char *kind,i/o-Choice device type:
|       kind = "alpha"   for the alphanumeric keyboard.
|       kind = "locator" for the locator device.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The graphic display device must have been defined by a previous
|     call to devic().
|       Before this routine is called, the default choice device type is
|     kind="locator".
|       Routine chcdvc may be called as often as desired to switch among
|     different choice devices.
|       If kind is not recognized, or not available for the current
|     display device, it is treated as kind="locator".
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void chcdvc(char *kind)
#else
  void chcdvc(kind)
  char *kind;
#endif
{
  char type[8];
 
  strcpy(type, kind);
  stripc(type);
  type[lenc(type)] = '\0';
  lcasec(type);
  if (strcmp(type, "alpha") == 0) {
    chdvc = CT_ALPHA;
  } else if (strcmp(type, "locator") == 0) {
    chdvc = CT_LOCATOR;
  } else {
    textc("Warning: Invalid choice device set to 'locator'.", TRUE);
    chdvc = CT_LOCATOR;
  }
  return;
}
