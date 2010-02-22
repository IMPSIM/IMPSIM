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
/* tfbdtc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Add the effects of a body torque to the generalized forces for a
|     transfer function.
|
|     Access:
|       (void) tfbdtc(Torque *torque, real G[]);
|     Torque *torque,  i-Torque record for the input torque.
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
  void tfbdtc(Torque *torque, real G[])
#else
  void tfbdtc(torque, G)
  Torque *torque;
  real   G[];
#endif
{ 
  Body *body;
  int  i;
  real RA[3], RAB[3], RB[3], size, W[6];

  ptposc(torque->trqPtA, RA);
  ptposc(torque->trqPtB, RB);
  for (i=0; i<3; i++) {
    RAB[i] = RA[i] - RB[i];
  }
  size = vabsc(3, RAB); 
  if (size >= System.ptoll) {
    body = torque->trqBdy;
    for (i=0; i<System.nfgc; i++) {
      wmatc(body, i, W);
      G[i] += vdotc(3, W, RAB) / size;
    }
  } else {
    textc("*** Axis points for '", FALSE);
    textc(torque->name, FALSE);
    textc("' are coincident. ***", TRUE);
    System.nerror = 4;
  }
  return;
}
