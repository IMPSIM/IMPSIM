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
/* impctc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Determine and set the adjusted FGC velocities resulting from an
|     impact at a specified contact.
|
|     Access:
|       (void) impctc(Contact *cntact);
|     Contact *cntact,i-Contact record specified for possible impact.
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
  void impctc(Contact *cntact)
#else
  void inpctc(cntact)
  Contact *cntact;
#endif
{
  enum Imptyp impulsemode, momentmode, tangentmode, torsionmode; 
  int         ifgc;
  real        *fgcvel1, *fgcvel2;
  Joint       *joint;
  Jvar        *jvar;
  
/* Initialize. */
  fgcvel1 = (real *) calloc(System.nfgc+5, sizeof(real));
  fgcvel2 = (real *) calloc(System.nfgc+5, sizeof(real));

/* If not face to face contact, no angular impulses apply. */
  tangentmode = System.impacteq[0];
  if (cntact->cntypA != FACE || cntact->cntypB !=FACE) {
    momentmode  = IM_UNDEF;
    torsionmode = IM_UNDEF;
  } else {
    momentmode  = System.impacteq[1];
    torsionmode = System.impacteq[2];
  }
  
/* Neither tangential nor torsional are bilinear models. */
  if (tangentmode != IM_BILIN && torsionmode != IM_BILIN) {
    imvelc(cntact, tangentmode, momentmode, torsionmode, fgcvel1); 
    impulsemode = IM_REST;

/* Bilinear tangential impulse model. */
  } else if (tangentmode == IM_BILIN && torsionmode != IM_BILIN) {
    imvelc(cntact, IM_REST, momentmode, torsionmode, fgcvel1);
    imvelc(cntact, IM_FRIC, momentmode, torsionmode, fgcvel2);
    if (rvelc(cntact, fgcvel1) < rvelc(cntact, fgcvel2)) {
      impulsemode = IM_REST;
    } else {
      impulsemode = IM_FRIC;
    }

/* Bilinear torsional impulse model. */
  } else if (tangentmode!=IM_BILIN && System.impacteq[2]==IM_BILIN) {
    imvelc(cntact, tangentmode, momentmode, IM_REST, fgcvel1);
    imvelc(cntact, tangentmode, momentmode, IM_FRIC, fgcvel2);
    if (romegc(cntact, fgcvel1) < romegc(cntact, fgcvel2)) {
      impulsemode = IM_REST;
    } else {
      impulsemode = IM_FRIC;
    }

/* Both bilinear models. */
  } else {
    imvelc(cntact, IM_REST, momentmode, IM_UNDEF, fgcvel1);
    imvelc(cntact, IM_FRIC, momentmode, IM_UNDEF, fgcvel2);
    if (rvelc(cntact, fgcvel1) < rvelc(cntact, fgcvel2)) {  
      imvelc(cntact, IM_REST, momentmode, IM_REST, fgcvel1);
      imvelc(cntact, IM_REST, momentmode, IM_FRIC, fgcvel2);
    } else {
      imvelc(cntact, IM_FRIC, momentmode, IM_REST, fgcvel1);
      imvelc(cntact, IM_FRIC, momentmode, IM_FRIC, fgcvel2);
    }
    if (romegc(cntact, fgcvel1) < romegc(cntact, fgcvel2)) {
      impulsemode = IM_REST;
    } else {
      impulsemode = IM_FRIC;
    }
  }

/* Reset the FGC velocities. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      ifgc = jvar->jvrnoS - System.ndep;
      if((ifgc >= 0) && (ifgc < System.nfgc)) {
        if (impulsemode == IM_REST) {
          jvar->vel = fgcvel1[ifgc];
        } else {
          jvar->vel = fgcvel2[ifgc];
        }
      }
    }
  }

/* Free working space. */
  free (fgcvel1);
  free (fgcvel2);
  return;
}
