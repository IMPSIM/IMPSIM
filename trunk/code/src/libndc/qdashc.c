/* ------------------------------------------------------------------ */
/* qdashc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return to the calling program the current integer dash pattern
|     code for visible lines drawn.
|
|     Access:
|       (void) qdashc(int *icode)
|     int *icode,o-Current integer dash pattern code.  See dashc() for
|       interpretation of the coded values.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The dash pattern can be changed at will by calling dashc().
|     Before the first call to dashc() solid lines (icode=0) are
|     assumed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qdashc(int *icode)
#else
  void qdashc(icode)
  int *icode;
#endif
{
  *icode = idash;
  return;
}
