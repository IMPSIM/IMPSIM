/* ------------------------------------------------------------------ */
/* qzrosc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       This function returns a small numeric value in screen units
|     which can be used for tolerance testing and is smaller than the
|     size of one pixel on the current graphic display screen.
|
|     Access:
|       zero = (real) qzrosc();
|     real zero,o-Small screen level tolerance value.
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
real qzrosc()
{
  return(stzero);
}
