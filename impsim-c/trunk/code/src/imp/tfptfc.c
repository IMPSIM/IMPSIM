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
/* tfptfc-01 Jan 00:12 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Add the effects of point forces to the generalized forces for a
|     transfer function.
|
|     Access:
|       (void) tfptfc(Force *force, real G[]);
|     Force *force,  i-Force record for the input force.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       If the two direction defining points are coincident within ptoll 
|     a message is printed and exit is made with System.nerror = 4.
|
|     Comments:
|       This function assumes that the G[] array has been initialized 
|     before entry and that other effects are added elsewhere.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void tfptfc(Force *force, real G[])
#else
  void tfptfc(force, G)
  Force *force;
  real   G[];
#endif
{ 
  Body *body;
  int   i;
  real  DR[3], R[3], RA[3], RB[3], RAB[3], size, W[6];

  ptposc(force->frcPtA, RA);
  ptposc(force->frcPtB, RB);
  ptposc(force->frcPtC, R);
  for (i=0; i<3; i++) {
    RAB[i] = RA[i] - RB[i];
  }
  size = vabsc(3, RAB); 
  if (size >= System.ptoll) {
    body = force->frcPtC->pntBdy;
    for (i=0; i<System.nfgc; i++) {
      wmatc(body, i, W);
      mpydrc(W, R, DR);
      G[i] += vdotc(3, DR, RAB) / size;
    }
  } else {
    textc("*** Direction points for '", FALSE);
    textc(force->name, FALSE);
    textc("' are coincident. ***", TRUE);
    System.nerror = 4;
  }
  return;
}
