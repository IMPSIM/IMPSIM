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
/* hdsgc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Output the user specified generalized positions, velocities, and
|     accelerations for PRINT HEADINGS and STORE HEADINGS requests.
|
|     Access:
|       (void) hdsgc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void hdsgc()
{
  Joint   *joint;
  Jvar    *jvar;
  Request *request;
  Sgc     *sgc;
  char     string[16];
  int      i, ifile, ldone, lflag[4];
  real     pos;

  for (i=0; i<4; i++) {
    lflag[i] = FALSE;
  }
  if (System.nerror == 0) {
    for (request=System.sysReq; request; request=request->nxtReq) {
      switch (request->reqtyp) {
      case RQ_LIST:
        ifile = 0;
        break;
      case RQ_PLOT:
        ifile = 1;
        break;
      case RQ_STORE:
        ifile = 2;
        break;
      case RQ_PRINT:
        if (request->outtyp == OT_HDNG) lflag[3] = TRUE;
      default:
        ifile = -1;
      }
      if (ifile >= 0) {
        if (lunfil[ifile] > 0) {
          if (!lflag[ifile]) {
            fprintf(streams[lunfil[ifile]],
              " TIME ----    1 %#19.10e %#19.10e %#19.10e\n",
              System.t, 0.0, 0.0);
            lflag[ifile] = TRUE;
          }
        }
      }
    }
  }
  if (lflag[3] || !qbitc(XQ_ANMAT, (void *) &System.xeqflags)) {
    textc("", TRUE);
    textc("time = ", FALSE);
    ftextc(System.t);
    textc("", TRUE);
  }
  if (lflag[3]) {
    textc("", TRUE);
    textc("The Generalized Coordinates are:", TRUE);
    textc("   Joint  Set by                  ", FALSE);
    textc("Position       Velocity   Acceleration", TRUE);
  }
  ldone = TRUE;
  for (i=0; i<3; i++) {
    if (lflag[i]) {
      fprintf(streams[lunfil[i]],
        " HDG. ---- %4i %#19.10e %#19.10e %#19.10e\n", System.nsgc,
        0.0, 0.0, 0.0);
      ldone = FALSE;
    }
  }
  if (ldone && !lflag[3]) return;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      sgc = jvar->jvrSgc;
      if (sgc != NULL) {
        pos = sgc->pos;
        if (jvar->jvrtyp == JV_ANGULAR) pos *= System.ascale;
        for (i=0; i<3; i++) {
          if (lflag[i]) {
           fprintf(streams[lunfil[i]],
             " SGC  %4s    3 %#19.10e %#19.10e %#19.10e\n",
             joint->name, pos, sgc->vel, sgc->acc);
          }
        }
        if (lflag[3]) {
          textc("  ", FALSE);
          textc(joint->name, FALSE);
          sprintf(string, "%2i", jvar->jvrnoJ+1);
          textc(string, FALSE);
          textc("    user           ", FALSE);
          sprintf(string, "%#15.4f", pos);
          textc(string, FALSE);
          sprintf(string, "%#15.3f", sgc->vel);
          textc(string, FALSE);
          sprintf(string, "%#15.3f", sgc->acc);
          textc(string, TRUE);
        }
      }
    }
  }
  return;
}
