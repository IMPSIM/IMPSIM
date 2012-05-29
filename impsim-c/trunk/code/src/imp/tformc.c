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
/* tformc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form the transfer functions for a named joint or point.
|
|     Access:
|       (void) tformc(complex Tnumr[], Word name, int nexp, Word kind,
|         int *nmax, real cons[], complex Tfn[]);
|     complex Tnumr[3,nfgc,2*nfgc],i-The transfer function numerators.
|     Word    name,                i-The name of the joint or point.
|     int     nexp,                i-Order of derivative for transfer
|                                    func: 0=disp, 1=veloc, 2=accel.
|     Word    kind,                o-Type of named item: "jnt.", "pnt."
|     int *   nmax,                o-Number of components in named item.
|     real    cons[],              o-Array of constant (central) values.
|     complex Tfn[3,6,2*nfgc],     o-Transfer function components.
|
|     Error Conditions:
|       System.nerror=3 if no joint or force with the specified name is 
|     found; a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void tformc(complex Tnumr[], Word name, int nexp, Word kind,
    int *nmax, real cons[], complex Tfn[])
#else
  void tformc(Tnumr, name, nexp, kind, nmax, cons, Tfn)
  complex Tnumr[];
  Word    name, kind;
  int     nexp, *nmax;
  real    cons[];
  complex Tfn[];
#endif
{
  Body    *body;
  Joint   *joint;
  Jvar    *jvar;
  Point   *point;
  complex save;
  real    R[3], V[6], W[6];
  int     i, j, k, l, loc, m, n, nfgc, njvar[6], n2;

/* Initialize. */
  nfgc  = System.nfgc;
  n2    = nfgc + nfgc;
  joint = NULL;
  point = NULL;
  loc   = 0;
  for (i=0; i<3; i++) {
    for (j=0; j<6; j++) {
      for (k=0; k<n2; k++) {
        Tfn[loc].r = 0.0;
        Tfn[loc].i = 0.0;
        loc++;
      }
    }
  }

/* Locate the named item. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (point=body->bdyPnt; point; point=point->nxtPnt) {
      if (point->master) {
        if (strncmp(name, point->name, MAXCHR) == 0) {
          strcpy(kind, "pnt.");
          *nmax = 3;
          switch (nexp) {
          case 0:
            ptposc(point, R);
            for (i=0; i<3; i++) {
              cons[i] = R[i];
            }
            break;
          case 1:
            ptvelc(point, R, cons);
            break;
          case 2:
            ptacc(point, R, V, cons);
            break;
          }
          break;
        }
      }
    }
    if (point) break;
  }
  if (point) {
  } else {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      if (strncmp(name, joint->name, MAXCHR) == 0) break;
    }
    if (joint) {
      strcpy(kind, "jnt. ");
      m = 0;
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        njvar[m] = jvar->jvrnoS;
        switch (nexp) {
        case 0:
          cons[m] = jvar->pos;
          break;
        case 1:
          cons[m] = jvar->vel;
          break;
        case 2:
          cons[m] = jvar->acc;
          break;
        }
        m++;
      }
      *nmax = m;
    } else {
      textc("*** There is no joint or point named '", FALSE);
      textc(name, FALSE);
      textc("'. ***", TRUE);
      System.nerror = 3;
      return;
    }
  }

/* Form the transfer functions. */
  for (l=0; l<nfgc; l++) {
    if (point) {
      wmatc(body, l, W);
      mpydrc(W, R, V);
    } else {
      for (j=0; j<*nmax; j++) {
        n = njvar[j];
        if (n < System.ndep) {
          V[j] = System.d1[n][j];
        } else if (n == (System.ndep + l)) {
          V[j] = 1.0;
        } else {
          V[j] = 0.0;
        }
      }
    }
    for (j=0; j<*nmax; j++) {
      if (abs(V[j]) > 0.0) {
        save.r = V[j];
        save.i = 0.0;
        for (i=0; i<3; i++) {
          loc = (6 * i + j) * n2;
          for (k=0; k<n2; k++) {
            Tfn[loc] = cplusc(Tfn[loc], cmultc(save, Tnumr[i, l, k])); 
          }
        }
      }
    }
  }
  return;
}
