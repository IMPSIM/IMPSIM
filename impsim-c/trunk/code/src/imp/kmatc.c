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
/* kmatc-01 Jan 00:14 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form the stiffness matrix of the system.
|
|     Access:
|       (void) kmatc(int nfgc, real K[]);
|     int nfgc,         i-Number of free generalized coordinates.
|     real K[nfgc,nfgc],o-Stiffness matrix of the system.
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
  void kmatc(int nfgc, real K[])
#else
  void kmatc(nfgc, K)
  int  nfgc;
  real K[];
#endif
{
  int i, j;

  if (System.level < 7) abortc();
  for (i=0; i<nfgc; i++) {
    for (j=0; j<=i; j++) {
      K[i*nfgc+j] = 0.0;
    }
  }
  kgvtc(nfgc, K);
  kjtsc(nfgc, K);
  kptsc(nfgc, K);
  kjtfc(nfgc, K);
  kptfc(nfgc, K);
  kbdtc(nfgc, K);
  for (i=0; i<nfgc; i++) {
    for (j=0; j<i; j++) {
      K[j*nfgc+i] = K[i*nfgc+j];
    }
  }
  return;
}
