/* ------------------------------------------------------------------ */
/* qiactc-01 Jan 00:24 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       This function returns the interactive or background nature of
|     the currently active job.
|
|     Access:
|       flag = (int) qiactc();
|     int flag,o-Current value of interactivity register:
|       flag = TRUE if execution is interactive; otherwise FALSE.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
int qiactc()
{
/* *** This feature has not yet been implemented. *** */
  intact = TRUE; 
  return(TRUE);
}
