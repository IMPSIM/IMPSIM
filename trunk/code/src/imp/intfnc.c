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
/* intfnc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Test the two solids of a contact pair to determine whether they 
|     are in contact or interference.
|
|     Access:
|       colide = (int) intfnc(Contact *cntact);
|     Contact *cntact,i-Contact pair to be monitored for interference.
|     int      colide,o-Flag set TRUE for interference.
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
  int intfnc(Contact *cntact)
#else
  int intfcc(cntact)
  Contact *cntact;
#endif
{
  Vertex *vtxA, *vtxB;
  int     i;
  real    cA[3], cAB[3], cB[3], rAB, temp[3], temp2[3];                              /*, lambda[4]; */

/* Check for interference of bounding spheres. */
  mpyxrc(cntact->cnSldA->sldBdy->T0j, cntact->cnSldA->bs_ctr, cA);  
  mpyxrc(cntact->cnSldB->sldBdy->T0j, cntact->cnSldB->bs_ctr, cB);
  rAB = cntact->cnSldA->bs_rad + cntact->cnSldB->bs_rad;
  for (i=0; i<3; i++) {cAB[i] = cA[i] - cB[i];}
  if (vabsc(3,cAB) > rAB) {         /* Perform bounding sphere check. */
    vnormc(3, cAB);
    for (i=0; i<3; i++) {
      cB[i] += cntact->cnSldB->bs_rad * cAB[i];
      cA[i] -= cntact->cnSldA->bs_rad * cAB[i];
    }
    qhtimc(cntact, cB, cA);
    return(FALSE);
  } 

/* Check if a separating plane exists. */
  if (cntact->sepplane) {
    for (i=0; i<3; i++) {temp[i] = -cntact->pln_dir[i];}
    vnormc(3, temp);
    dstABc(cntact->cnSldB, cntact->cnSldA, temp, temp2 , &vtxB, &vtxA);
    if (vdotc(3, temp, temp2) < 0) {
      return(FALSE);      
    } else {
      return(!qdstnc(cntact));
    }
  } else {
    return(!qdstnc(cntact));  
  }
}  
