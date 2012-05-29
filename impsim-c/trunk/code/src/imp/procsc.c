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
/* procsc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Output the requested results for the current position.
|
|     Access:
|       (void) procsc();
|
|     Error Conditions:
|       System.nerror = 9 indicates a RETURN result of a Value.
|       If either the Reqtyp or the Outtyp of a Request record is not
|     defined, the entire record is ignored.  No message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void procsc()
{
  Request *request;

/* Sequence through all output requests. */
  for (request=System.sysReq; request; request=request->nxtReq) {

/* Identify the output type. */
    switch (request->outtyp) {

/* Process VALUE requests. */
    case OT_VAL:
      switch (request->reqtyp) {
      case RQ_PRINT:
        wrvalc(request->items, request->nitems);
        break;
      case RQ_LIST:
        lsvalc(request->items, request->nitems);
        break;
      case RQ_PLOT:
        plvalc(request->items, request->nitems);
        break;
      case RQ_STORE:
        stvalc(request->items, request->nitems);
      }
      break;

/* Process POSITION requests. */
    case OT_POS:
      switch (request->reqtyp) {
      case RQ_PRINT:
        wrposc(request->items, request->nitems);
        break;
      case RQ_LIST:
        lsposc(request->items, request->nitems);
        break;
      case RQ_PLOT:
        plposc(request->items, request->nitems);
        break;
      case RQ_STORE:
        stposc(request->items, request->nitems);
      }
      break;

/* Process VELOCITY requests. */
    case OT_VEL:
      switch (request->reqtyp) {
      case RQ_PRINT:
        wrvelc(request->items, request->nitems);
        break;
      case RQ_LIST:
        lsvelc(request->items, request->nitems);
        break;
      case RQ_PLOT:
        plvelc(request->items, request->nitems);
        break;
      case RQ_STORE:
        stvelc(request->items, request->nitems);
      }
      break;

/* Process ACCELERARION requests. */
    case OT_ACC:
      switch (request->reqtyp) {
      case RQ_PRINT:
        wracc(request->items, request->nitems);
        break;
      case RQ_LIST:
        lsacc(request->items, request->nitems);
        break;
      case RQ_PLOT:
        placc(request->items, request->nitems);
        break;
      case RQ_STORE:
        stacc(request->items, request->nitems);
      }
      break;

/* Process FORCE requests. */
    case OT_FORC:
      switch (request->reqtyp) {
      case RQ_PRINT:
        wrforc(request->items, request->nitems);
        break;
      case RQ_LIST:
        lsforc(request->items, request->nitems);
        break;
      case RQ_PLOT:
        plforc(request->items, request->nitems);
        break;
      case RQ_STORE:
        stforc(request->items, request->nitems);
      }
      break;

/* Process PRINT FREQUENCY requests. */
    case OT_FREQ:
      switch (request->reqtyp) {
      case RQ_PRINT:
        freqnc();
      }
    }
  }
  fflush(NULL);
  return;
}
