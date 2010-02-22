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
/* lpfilc-01 Jan 00:15 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the loopflags in the Body, Joint, and Axes records according
|     to the information in the loops matrix.
|
|     Access:
|       (void) lpfilc(int **loops);
|     int loops[nloops][njnts],i-The loop/edge incidence matrix.
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
  void lpfilc(int **loops)
#else
  void lpfilc(loops)
  int  **loops;
#endif
{
  Axes  *axes;
  Body  *body;
  Joint *joint;
  int    i;
  long   mark;

/* Set all Axes, Body, and Joint loopflags to zero. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
      axes->loopflags = 0;
    }
    body->loopflags = 0;
  }
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    joint->loopflags = 0;
  }

/* Sequence through all loops, setting flags. */
  mark = 1;
  for (i=0; i<System.nloops; i++) {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      if (loops[i][joint->jntno]) { /* Test whether joint is in loop. */
        joint->jntAxA->loopflags |= mark; /* Mark the Axes loopflags. */
        joint->jntAxB->loopflags |= mark;
        joint->jntAxA->axsBdy->loopflags |= mark; /* Mark Body flags. */
        joint->jntAxB->axsBdy->loopflags |= mark;
        joint->loopflags |= mark;        /* Mark the Joint loopflags. */
      }
    }
    mark <<= 1;
  }
  return;
}
