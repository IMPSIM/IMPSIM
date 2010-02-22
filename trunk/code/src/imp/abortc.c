/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:11 Jul 09                                          |
|     (C) Copyright, JJU Research, 1984-2009.                          |
|                                                                      |
|     This material is released under the terms of the                 |
|     GNU General Public License, version 3 (GNU GPLv3).               |
|     The full text of that license is available from the 'IMPSim'     |
|     project site on Google Code.                                     |
|                                                                      |
|     This initial release of 'IMPSim' is equivalent to the            |
|     IMP Integrated Mechanisms Program (IMP-2009) and is released     |
|     with the full approval of JJU Research of Madison, WI.           |
|                                                                      |
* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------ */
/* abortc-01 Jan 00:04 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Abort procedure for fatal errors in the IMP system.
|
|     Access:
|       void abortc()
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine halts execution of the IMP program.
|       The applications programmer may wish to modify this routine in
|     order to print a traceback, flush any buffers, close and save
|     any files, etc.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
  void abortc()
{
  int iostat;

/* Wrap up all files. */
  endsvc();
  readrc("close");

/* Print a message to the user. */
  textc("", TRUE);
  textc("Fatal Error in the IMP Software Library.", TRUE);
  textc("Please save all printed results and", TRUE);
  textc("Phone: (608) 262-0225 for assistance.", TRUE);

/* Request go ahead from an interactive user. */
  if (qiactc()){
    textc("Press RETURN when ready to abort: > ", FALSE);
    iostat = bfinc("?");
  }
  finplc();
  abort();
}
