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
/* qhtimc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Find and set the expected hit time between the two Solids of a 
|     Contact pair.  
|
|     Access:
|       (void) qhtimc(Contact *cntact, real RA[3], real RB[3]);
|     Contact *cntact,i-Contact pair to be monitored for interference.
|     real RA[3],     i-Global coordinates of point following contact.
|     real RB[3],     i-Global coordinates of point preceding contact.
|
|     Error Conditions:
|       If the estimated hit time has been passed or cannot be found
|     then cntact->timex is set to NaN.
|
|     Comments:
|       The hit time is estimated based on the relative velocity and 
|     relative acceleration between the near points of the two Solids.
|     This estimated hit time is stored in the Contact record rather
|     than returned by the function.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void qhtimc(Contact *cntact, real RA[3], real RB[3])
#else
  void qhtimc(cntact, RA, RB)
  Contact *cntact;
  real     RA[3], RB[3];
#endif
{
  int  i;
  real aA[3], aAB, aB[3], distAB, RAB[3], temp[3], tmp, vA[3], vAB, 
         vB[3];

/* Find the distance between the two points. */
  for (i=0; i<3; i++) {RAB[i] = RA[i] - RB[i];}
  distAB = vabsc(3, RAB);

/* Find the relative velocity of the two points. */
  mpydrc(cntact->cnSldA->sldBdy->W, RA, vA);
  mpydrc(cntact->cnSldB->sldBdy->W, RB, vB);
  for (i=0; i<3; i++) {temp[i] = vA[i] - vB[i];}
  vAB = - vdotc(3, temp, RAB) / distAB;

/* Find the relative acceleration of the two points. */
  vcrosc(cntact->cnSldA->sldBdy->W, vA, aA);
  mpydrc(cntact->cnSldA->sldBdy->A, RA, temp);
  for (i=0; i<3; i++) {aA[i] += temp[i];}
  vcrosc(cntact->cnSldB->sldBdy->W, vB, aB);
  mpydrc(cntact->cnSldB->sldBdy->A, RB, temp);
  for (i=0; i<3; i++) {aB[i] += temp[i];}
  for (i=0; i<3; i++) {temp[i] = aA[i] - aB[i];}
  aAB = - vdotc(3, temp, RAB) / distAB;

/* Find the estimated hit time for this Contact. */
  if (fabs(aAB) < System.zero) {
    if (fabs(vAB) < System.zero) {
      ldnanc((void *) &(cntact->timex));
    } else {
      cntact->timex = System.t + distAB / vAB;
    }
  } else {
    tmp = vAB * vAB + 2.0 * aAB * distAB;
    if (tmp < System.zero) {
      ldnanc((void *) &(cntact->timex));
    } else {
      cntact->timex = System.t + (sqrt(tmp) - vAB) / aAB;
    }

  }
  return;
}
