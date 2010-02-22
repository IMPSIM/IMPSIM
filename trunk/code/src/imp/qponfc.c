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
/* qponfc-01 Jan 00:14 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine whether a specified point is in contact with a 
|     specified face.
|
|     Access:
|       lflag = (int) qponfc(real pnt[3], Face *face);
|     real  pnt[3], i-Point to be tested for contact.
|     Face *face,   i-Face record to be tested for contact.
|     int   lflag,  o-Flag set TRUE if contact is verified.
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
  int qponfc(real pnt[3], Face *face)
#else
  int qponfc(pnt, face)
  real    pnt[3];
  Face   *face;
#endif
{
  int    ignore, lflag, lin, lout, nvertx;
  Perim *perim;

  lflag = FALSE;
  if (fabs(face->faceq[3]+vdotc(3, pnt, face->faceq)) <= zrogeo) {
    if ((lout = qponpc(pnt, face->facPrm, &ignore, &nvertx)) != TRUE) {
      lflag = lout;                 /* Outside or on the outer perim. */
    } else {                               /* Inside the outer perim. */
      for (perim=face->facPrm; perim; perim=perim->nxtPrm) {
        if (perim != face->facPrm) { /* Check with only inner perims. */
          if ((lin = qponpc(pnt, perim, &ignore, &nvertx)) == TRUE) {
            lflag = FALSE;
            goto DONE;                         /* Inside inner perim. */
          } else if (lin > 1) {        /* On boundary of inner perim. */
            lflag = lin;
            break;
          }
        }
      }
      lflag = TRUE;
    }
  }
DONE:
  return (lflag);
}
