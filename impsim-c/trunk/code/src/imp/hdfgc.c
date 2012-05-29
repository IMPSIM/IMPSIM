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
/* hdfgc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Output the free generalized positions, velocities, and accelera-
|     tions for PRINT HEADINGS and STORE HEADINGS requests.
|
|     Access:
|       (void) hdfgc();
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
void hdfgc()
{
  Joint   *joint;
  Jvar    *jvar;
  Request *request;
  char     string[48];
  int      i, ifile, lflag[4], lunfil3, njvar;
  real     save[3];

/* Initialize. */
  for (i=0; i<4; i++) {
    lflag[i] = FALSE;
  }
  lunfil3 = -1;
  if (System.nfgc > 0) {

/* Loop through all Request records. */
    for (request=System.sysReq; request; request=request->nxtReq) {
      switch (request->reqtyp) {

/* Check for a LIST HEADINGS request. */
      case RQ_LIST:
        ifile = 0;
        break;

/* Check for a PLOT HEADINGS request. */
      case RQ_PLOT:
        ifile = 1;
        break;

/* Check for a STORE HEADINGS request. */
      case RQ_STORE:
        ifile = 2;
        break;

/* Check for a PRINT HEADINGS request. */
      case RQ_PRINT:
        if (request->outtyp == OT_HDNG) {
          lflag[3] = TRUE;
          lunfil3  = lunitc("output");
        }
        break;
      default:
        ifile = -1;
      }
      if (ifile >= 0) {
        if (lunfil[ifile] > 0) {
          if (!lflag[ifile]) {
            fprintf(streams[lunfil[ifile]],
              " HDG. ---- %4i %#19.10e %#19.10e %#19.10e\n",
              System.nfgc, 0.0, 0.0, 0.0);
            lflag[ifile] = TRUE;
          }
        }
      }
    }

/* Collect data for FGC heading requests. */
    for (i=0; i<3; i++) save[i] = 0.0;
    for (njvar=System.ndep+System.nfgc-1; njvar>=System.ndep; njvar--) {
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          if (jvar->jvrnoS == njvar) {
            save[0] = jvposc(jvar);
            save[1] = jvvelc(jvar);
            save[2] = jvacc(jvar);

/* Output data for FGC heading requests. */
            for (i=0; i<3; i++) {
              if (lflag[i]) fprintf(streams[lunfil[i]],
                " FGC  %4s    3 %#19.10e %#19.10e %#19.10e\n",
                joint->name, save[0], save[1], save[2]);
            }
            if (lunfil3 >= 0) {
              textc("  ", FALSE);
              textc(joint->name, FALSE);
              textc(" ", FALSE);
              itextc(jvar->jvrnoJ+1);
              textc("    imp            ", FALSE);
              sprintf(string, "%#15.4f%#15.3f%#15.3f", save[0], save[1],
                save[2]);
              textc(string, TRUE);
            }
            goto _2;
          }
        }
      }
_2: continue;
    }
  }

/* Output other general heading information. */
  for (request=System.sysReq; request; request=request->nxtReq) {
    if (request->reqtyp != RQ_PRINT) continue;
    if (request->outtyp == OT_DYN) continue;
    textc("", TRUE);
    if (System.mode == MD_STAT) {
      textc("Equilibrium found after ", FALSE);
      itextc(System.ei);
      textc(" search steps.", TRUE);
    }
    textc("Degree of freedom = ", FALSE);
    itextc(System.ndof);
    textc(".  Quality index = ", FALSE);
    gtextc(System.qi);
    textc(" with ", FALSE);
    itextc(System.ci);
    textc(" iterations.", TRUE);
    if (System.ndof <= 0) {
      textc("*** Zero degrees of freedom.  System cannot move. ***",
        TRUE);
    }
    break;
  }
  return;
}
