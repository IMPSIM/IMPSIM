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
/* axesc-01 Jan 00:15 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the joint visibility flags to show specified joint axes.
|
|     Access:
|       (void) axesc(real size, Token names[], int n);
|     real size,i-Size of joint axes to be drawn.
|     Token names[n],i-Array of names of the joint axes to be visible.
|     int n,i-Count of the number of joints named in the names array.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       A value of size of fabs(size) < System.dtoll is used for
|     joint axes to invisibile.
|       A names[] entry of "all" sets all joint axes to size.
|       If there is no joint with joint->name = names[], then that entry
|     of names[] is ignored.  No message is printed.
|       If n <= 0, then names[0] is treated as "all".
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void axesc(real size, Token names[], int n)
#else
  void axesc(size, names, n)
  real  size;
  Token names[];
  int   n;
#endif
{
  Joint *joint;
  Word   name;
  int    i, lgoto;
  real   denom;

  denom = 0.0;
  if (fabs(size) >= System.dtoll) denom = 1.0 / size;
  i = 0;
  lgoto = TRUE;
  do {
    if (i < n) {
      strcpy(name, names[i].data.text);
      lcasec(name);
      lgoto = (strcmp(name, "all") == 0);
    }
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      if (lgoto) {
        joint->axsize = denom;
      } else if (strcmp(names[i].data.text, joint->name) == 0) {
        joint->axsize = denom;
      }
    }
    i++;
  } while (i < n);
  return;
}
