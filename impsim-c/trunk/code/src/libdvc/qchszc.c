/* ------------------------------------------------------------------ */
/* qchszc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the horizontal and vertical sizes in screen units of a
|     single text character (including inter-character spacing).
|
|     Access:
|       (void) qchszc(real *hsymbl, real *vsymbl)
|     real *hsymbl,o-Current horizontal symbol size in screen units.
|     real *vsymbl,o-Current vertical   symbol size in screen units.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The character size may be changed at will by calling stdchc() or
|     chsizc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qchszc(real *hsymbl, real *vsymbl)
#else
  void qchszc(hsymbl, vsymbl)
  real *hsymbl, *vsymbl;
#endif
{
  *hsymbl = ssymbl;
  *vsymbl = tsymbl;
  return;
}
