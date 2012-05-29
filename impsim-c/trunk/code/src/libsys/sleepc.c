/* ------------------------------------------------------------------ */
/* sleepc-01 Jan 00:10 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Produce a specified time delay in the execution of the calling
|     program if executing interactively.
|
|     Access:
|       (void) sleepc(real secnds);
|     real secnds,i-Duration of desired time delay in seconds.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Any local I/O buffers should be flushed, if required, before
|     calling sleepc().
|       This routine is inoperative if called in background execution.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void sleepc(real secnds)
#else
  void sleepc(secnds)
  real secnds;
#endif
{
# if defined( HP )
    struct timeval timeout;
# elif defined( __WATCOMC__ )
#   include <dos.h>
# endif
  unsigned long usec;

  usec = (int) (secnds * 1000000.0);
  if (qiactc() && (usec != 0)){
#   if defined( HP )
      timeout.tv_usec = usec % (unsigned long) 1000000;
      timeout.tv_sec  = usec / (unsigned long) 1000000;
      select(0, (void *) 0, (void *) 0, (void *) 0, &timeout);
#   elif defined( __WATCOMC__ )
      delay((int) (usec / 1000));
#   else
      usleep(usec);
#   endif
  }
  return;
}
