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
/* xrqstc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Request record.
|
|     Access:
|       (void) xrqstc(Request *request);
|     Request *request,i-Pointer to the Request record to be deleted.
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
 
#include "libimp.h"
#ifdef ANSI
  void xrqstc(Request *request)
#else
  void xrqstc(request)
  Request *request;
#endif
{
  Request *rqst;

  if (request->type == REQUEST) {
    if (System.sysReq == request) {
      System.sysReq = request->nxtReq;
    } else {
      rqst = System.sysReq;
      while (rqst->nxtReq) {
        if (rqst->nxtReq == request) {
          rqst->nxtReq = request->nxtReq;
          break;
        } else {
          rqst = rqst->nxtReq;
        }
      }
    }
    free(request);
  }
  return;
}
