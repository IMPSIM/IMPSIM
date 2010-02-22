/* ------------------------------------------------------------------ */
/* ldkhdc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the pointer in libcad global memory to make a specified menu
|     number current.
|
|     Access:
|       (void) ldkhdc(int kheadr);
|     int kheadr,i-Number of the menu to be set current.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldkhdc(int kheadr)
#else
  void ldkhdc(kheadr)
  int kheadr;
#endif
{
  khdr = kheadr;
  return;
}
