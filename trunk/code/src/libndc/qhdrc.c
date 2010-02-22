/* ------------------------------------------------------------------ */
/* qhdrc-01 Jan 00:09 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return to the calling program the current integer menu number
|     and the number of menu headers currently defined.
|
|     Access:
|       (void) qhdrc(int *kheadr, int *nmenus);
|     int *kheadr,o-Current menu number; *kheadr = 1, 2, ..., *nmenus.
|       interpretation of the integer returned.
|     int *nmenus,o-Total number of menu headers currently defined.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The menu numbers are arranged in alphabetical order.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qhdrc(int *kheadr, int *nmenus)
#else
  void qhdrc(kheadr, nmenus)
  int *kheadr, *nmenus;
#endif
{
  *kheadr = khdr;
  *nmenus = nhdrs;
  return;
}
