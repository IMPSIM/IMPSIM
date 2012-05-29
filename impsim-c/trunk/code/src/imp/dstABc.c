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
/* dstABc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Finds the support function and the contact vertices for the set 
|     difference of two solids in a specified direction.
|
|     Access:
|       distnc = (real) dstABc(Solid *solidA, Solid *solidB, 
|         real direc[3], real sk[3], Vertex **VxA, Vertex **VxB, 
|         real distnc);
|     Solid   *solidA,  i-Solid following the monitored contact.
|     Solid   *solidB,  i-Solid preceding the monitored contact.
|     real     direc[3],i-Specified direction to be tested.
|     real     Sk[3],   o-Support funtion vector found.
|     Vertex **VxA,     o-Vertex found following contact.
|     Vertex **VxB,     o-Vertex found preceding contact.
|     real     distnc,  o-Distance found in the specified direction.
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
  real dstABc(Solid *solidA, Solid *solidB, real direc[3], real Sk[3], 
	   Vertex **VxA, Vertex **VxB)
#else
  real dstABc(solidA, solidB, direc, Sk, VxA, VxB)
  Solid  *solidA, *solidB;
  real   direc[3], Sk[3];
  Vertex **VxA, **VxB;
#endif
{
  int  i;
  real dstA, dstB, neg_direc[3], RA[3], RB[3];

  for (i=0; i<3; i++) {neg_direc[i] = -direc[i];}
  dstA = dssldc(solidA, direc,     RA, VxA);
  dstB = dssldc(solidB, neg_direc, RB, VxB);
  for (i=0; i<3; i++) {Sk[i] = RA[i] - RB[i];}
  return(dstA + dstB);
}
