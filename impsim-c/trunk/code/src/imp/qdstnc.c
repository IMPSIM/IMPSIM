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
/* qdstnc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Check whether the distance between the two Solids of a Contact 
|     are at a distance > zero.
|
|     Access:
|       flag = (int) qdstnc(Contact *cntact);
|     Contact *cntact,i-Contact pair to be monitored for interference.
|     int      flag,  o-Flag returns TRUE for distance > 0.0 between
|                         points of the Contact being monitored, or
|                         FALSE otherwise.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This function also updates the other variables in the Contact
|     record, which can be used the next time a collision check is
|     required.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  int qdstnc(Contact *cntact)
#else
  int qdstnc(cntact)
  Contact *cntact;
#endif
{
  real lamda[4];
  
  if (mndstc(cntact->cnSldA, cntact->cnSldB, cntact->pln_dir, 
    cntact->pln_pntA, cntact->pln_pntB, cntact->near_vxs, lamda, 
    &(cntact->nvxs)) > zrogeo) {
    cntact->sepplane = TRUE;
    qhtimc(cntact, cntact->pln_pntA, cntact->pln_pntB);
    return(TRUE);
  } else {
    cntact->sepplane = FALSE;
    ldnanc((void *) &(cntact->timex));
    return(FALSE);
  }
}
