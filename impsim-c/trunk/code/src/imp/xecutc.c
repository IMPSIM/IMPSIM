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
/* xecutc-01 Jan 00:06 May 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Control the flow of IMP during the analysis phase.
|
|     Access:
|       (void) xecutc();
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
void xecutc()
{

/* Set the SGC values. */
  if (qbitc(XQ_ANMAT, (void *) &System.xeqflags) &&
     !qbitc(XQ_ERASE, (void *) &System.xeqflags)) newpgc();
  akbic();
  if (isnanc((void *) &System.t))    System.t    = 0.0;
  if (isnanc((void *) &System.dtio)) System.dtio = 1.0;
  while ((!qkbic()) && (System.t <= System.tfinal + System.zero)) {;
    vzeroc(F_TIME);
    msetc();
    if (System.mode != MD_DYN) hdsgc();

/* Assemble the mechanism. */
    adjstc();
    closec();

/* Search for equilibrium if in static mode. */
    if ((System.nerror == 0) && (System.mode == MD_STAT)) eqlibc();
    if (System.nerror) {
      resetc();
      if (System.mode != MD_DYN) {
        textc("*** Position ignored. ***", TRUE);
        System.nerror = 0;
        closec();
        if (System.nerror == 0) goto TINC;
      }
      break;
    }
    pvsetc();

/* Time integrate if in dynamic mode. */
    if ((System.mode == MD_DYN) && (System.ndof > 0)) {
      dynmxc();
      break;
    }

/* Print the requested output. */
    if (qbitc(XQ_ANMAT, (void *) &System.xeqflags)) drawc();
    hdfgc();
    dsetc();
    ksetc();
    fsetc();
    procsc();

/* Increment the time. */
TINC: 
    System.t += System.dtio;
  }
  ckbic();
  return;
}
