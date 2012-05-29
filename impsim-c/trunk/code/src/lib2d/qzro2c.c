/* ------------------------------------------------------------------ */
/* qzro2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return a small numeric value in 2D units which can be used for
|     tolerance testing and is smaller than the size of one screen pixel
|     on the current graphic display screen.
|
|     Access:
|       zero = (real) qzro2c();
|     real zero,o-Small 2D level tolerance value.
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
real qzro2c()
{
  return(min( x2scal, y2scal) * stzero);
}
