/* ------------------------------------------------------------------ */
/* kbic-01 Jan 00:19 Aug 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       This routine is called by the keyboard interrupt handler of the
|     host system to set the kbint flag when the interrupt occurs.
|
|     Access:
|       (PFV) kbic();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine is called by the keyboard interrupt handler only,
|     never directly by the application program.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void kbic(
# ifdef __WATCOMC__
  int nsignal
# endif
)
{
/* The interrupt resets the default handler; put this one back. */
  akbic();
  if (kbwtch) kbint = TRUE;
  return;
}
