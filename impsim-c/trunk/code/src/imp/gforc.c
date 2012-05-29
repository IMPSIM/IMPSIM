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
/* gforc-01 Jan 00:14 Jul 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Compute the generalized forces applied to the free generalized
|     coordinates of the system.
|
|     Access:
|       (void) gforc(int nfgc, real G[]);
|     int nfgc,    i-Number of free generalized coordinates.
|     real G[nfgc],o-Vector of generalized forces at the FGC's.
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
  void gforc(int nfgc, real G[])
#else
  void gforc(nfgc, G)
  int  nfgc;
  real G[];
#endif
{
  int  i;

  if (System.level < 9) sdervc();
  if (System.nerror == 0) {
    if (nfgc > 0) {
      for (i=0; i<nfgc; i++) G[i] = 0.0;
      if (System.mode != MD_STAT) {
        gfdync(nfgc, G);
        gfjtdc(nfgc, G);
        gfptdc(nfgc, G);
      }
      gfgvtc(nfgc, G);
      gfjtsc(nfgc, G);
      gfptsc(nfgc, G);
      gfjtfc(nfgc, G);
      gfptfc(nfgc, G);
      gfbdtc(nfgc, G);
    }
  }
  return;
}
