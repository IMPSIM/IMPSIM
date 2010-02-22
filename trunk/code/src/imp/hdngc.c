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
/* hdngc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Print a heading at the beginning of the analysis output.
|
|     Access:
|       (void) hdngc(lanimate);
|     int lanimate,i-Logical flag set TRUE for graphic animation.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       When the graphic animation flag is set TRUE, no printed heading
|     is output.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void hdngc(int lanimate)
#else
  void hdngc(lanimate)
  int lanimate;
#endif
{
  char chdate[12], chtime[9], 
    space[33] = "                                ";
  int m, n;

/* Skip the printed output heading when animating graphics. */
  if (!lanimate){
    newpgc();                       /* Skip to the top of a new page. */
    textc("************************************", FALSE);
    textc("************************************", TRUE);

/* Print the title of the modeled system. */
    n=strlen(System.title);
    if (n > 0){
      m = (64 - n) / 2;
      textc("*   ", FALSE);
      textc(&space[32-m], FALSE);
      textc(System.title, FALSE);
      textc(&space[32-m-(n%2)], FALSE);
      textc("   *", TRUE);
    }

/* Print the simulation mode. */
    textc("*                            ", FALSE);
    if (System.mode == MD_DYN){
      textc(" Dynamic Mode ", FALSE);
    } else if(System.mode == MD_STAT){
      textc(" Static Mode  ", FALSE);
    } else {
      textc("Kinematic Mode", FALSE);
    }
    textc("                            *", TRUE);

/* Print the current time and date. */
    textc("*                    on ", FALSE);
    datec(chdate);
    textc(chdate, FALSE);
    textc("     at ", FALSE);
    todc(chtime);
    textc(chtime, FALSE);
    textc("                    *", TRUE);
    textc("************************************", FALSE);
    textc("************************************", TRUE);
  }
  return;
}
