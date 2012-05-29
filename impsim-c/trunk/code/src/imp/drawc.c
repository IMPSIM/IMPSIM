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
/* drawc-10 Aug 03:06 Aug 09
|     (C)Copyright, JJU Research, 2003-2009
|
|     Description:
|       This module draws all visible bodies.
|
|     Access:
|       (void) drawc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     10 Aug 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void drawc()
{
  Axes   *axes;
  Body   *body;
  Damper *damper;
  Face   *face, *faceR;
  Force  *force;
  Hedge  *hedge;
  Joint  *joint;
  Perim  *perim;
  Point  *point;
  Solid  *solid;
  Spring *spring;
  Torque *torque;
  Vertex *vxA, *vxB;
  char   chdvc[9], device[9], lcdvc[9], label[3] = "u\0\0", string[16];
  int    i, j, k, lpen, n;
  real   creas, denom, dot, dotL, dotR, ds, dt, factor, pta[3],
           ptavg[3], ptb[3], ptc[3], s, smax, smin, spen, ssymbl, t,
           tenth, tic, tmax, tmin, tpen, tsymbl, xform[3][4], x2scal,
           x32new[4][4], x32sav[4][4], y2scal, zeye[4];

/* Initialize. */
  qx32c(x32sav);
  creas = cos(crease);
  qchszc(&ssymbl, &tsymbl);
  qscl2c(&x2scal, &y2scal);
  factor = qscl3c() / x2scal;
  n = nint(log10(0.25 / factor));
  szaxes = sign(pow(10.0, (real) n), szaxes);

/* Erase the screen if ERASE ON is set. */
  if (qbitc(XQ_ERASE, (void *) &System.xeqflags)) newpgc();

/* Draw the global coordinate system. */
  if (szaxes > 0.0) {
    colrfc(kaxes);
    colrsc(kaxes);
    mova3c(0.0, 0.0, 0.0, 1.0);
    drwr3c(szaxes, 0.0, 0.0, 1.0);
    qpensc(&spen, &tpen, &lpen);
    if (lpen) htextc("X0");
    mova3c(0.0, 0.0, 0.0, 1.0);
    drwr3c(0.0, szaxes, 0.0, 1.0);
    qpensc(&spen, &tpen, &lpen);
    if (lpen) htextc("Y0");
    mova3c(0.0, 0.0, 0.0, 1.0);
    drwr3c(0.0, 0.0, szaxes, 1.0);
    qpensc(&spen, &tpen, &lpen);
    if (lpen) htextc("Z0");
  }

/* Display the scale. */
  colrfc(kfrgnd);
  colrsc(ktext);
  qfrmsc(&smin, &tmin, &smax, &tmax);
  ds =       ssymbl;
  dt = 2.0 * tsymbl;
  movasc((smin + ds), (tmin + dt - tsymbl));
  drwrsc(0.0, tsymbl);
  movrsc((-0.5 * ssymbl), (0.2 * tsymbl));
  htextc("0");
  movasc((smin + ds), (tmin + dt));
  tenth = 0.10 * factor * fabs(szaxes);
  tic   = 0.25 * tsymbl;
  for (i=1; i<10; i++) {
    movrsc(tenth, 0.0);
    if ((i % 5) == 0) {
      drwrsc(0.0, -2.0 * tic);
      movrsc(0.0, 2.0 * tic);
    } else {
      drwrsc(0.0, -tic);
      movrsc(0.0,  tic);
    }
  }
  movasc((smin + ds), (tmin + dt));
  movrsc((5.0 * tenth - 2.5 * ssymbl), (0.2 * tsymbl));
  htextc("Scale");
  movasc((smin + ds), (tmin + dt));
  drwrsc((10.0 * tenth), 0.0);
  drwrsc(0.0, -tsymbl);
  movrsc((-0.5 * (max(0, n) + 1) * ssymbl), (1.2 * tsymbl));
  sprintf(string, "%6.3g", fabs(szaxes));
  stripc(string);
  htextc(string);

/* Loop through all visible Bodies and orphan Solids. */
  body  = System.sysBdy;
  solid = System.sysSld;
  do {
    if (qkbic()) break;            /* Check for a keyboard interrupt. */
    if (solid || (body && body->kcolor > 0)) {/*Test body visibility. */
      if (body) {
        for (i=0; i<4; i++) {
          for (j=0; j<4; j++) {
            x32new[i][j] = 0.0;
            for (k=0; k<3; k++) {
              x32new[i][j] += x32sav[i][k] * body->T0j[k][j];
            }
          }
          x32new[i][3] += x32sav[i][3];
        }
        ldx32c(x32new);  /* Set xf for body location and orientation. */
        x2to3c(0.0,0.0,1.0,0.0, &zeye[0],&zeye[1],&zeye[2],&zeye[3]);

/* Draw any wire-frame trails of Points. */
        colrfc(body->kcolor);
        for (point=body->bdyPnt; point; point=point->nxtPnt) {
          ptposc(point, ptc);
          if (point->kcolor > 0) {
            drwa3c(ptc[0], ptc[1], ptc[2], 1.0);
          } else {
            mova3c(ptc[0], ptc[1], ptc[2], 1.0);
          }
        }

/* Draw the Body coordinate system. */
        if (szaxes > 0) {
          colrfc(kaxes);
          colrsc(kaxes);
          mova3c(0.0, 0.0, 0.0, 1.0);
          drwr3c(szaxes, 0.0, 0.0, 2.0); /* Draw Body axes half size. */
          qpensc(&spen, &tpen, &lpen);
          if (lpen) htextc("x");
          mova3c(0.0, 0.0, 0.0, 1.0);
          drwr3c(0.0, szaxes, 0.0, 2.0);
          qpensc(&spen, &tpen, &lpen);
          if (lpen) htextc("y");
          mova3c(0.0, 0.0, 0.0, 1.0);
          drwr3c(0.0, 0.0, szaxes, 2.0);
          qpensc(&spen, &tpen, &lpen);
          if (lpen) htextc("z");
          colrfc(kfrgnd);
          colrsc(ktext);
        }
        solid = body->bdySld;
      }

/* Loop through all visible Faces of each Solid. */
      while (solid) {
        if (solid->kcolor > 0) {    /* Test visibility of this Solid. */
          face = solid->sldFac;
          while (face) {
            if (qkbic()) break;    /* Check for a keyboard interrupt. */
            dotL  = vdotc(3, face->faceq, zeye);
            if ((dotL > 0.0) || (!lpoor)) {       /* Is face visible? */
              if (face->kcolor > 0) {
                colrfc(face->kcolor);

/* Locate the middle of the Face for expansion. */
                fcavgc(face, &ptavg[0], &ptavg[1], &ptavg[2]);

/* Loop through all Hedges in face. */
                perim = face->facPrm;
                while (perim) {
                  hedge = perim->prmHed;
                  do {
                    vxB = hedge->hedCnr->cnrVtx;
                    vxA = hedge->nxtHedPrm->hedCnr->cnrVtx;
                    for (i=0; i<3; i++) {  /* Apply expansion factor. */
                      ptb[i] = ptavg[i]+expand*(vxB->coord[i]-ptavg[i]);
                      pta[i] = ptavg[i]+expand*(vxA->coord[i]-ptavg[i]);
                    }

/* If 3-D Solid, test the crease angle for visibility of the Edge. */
                    if (solid->kdimen == SPATIAL) {
                      faceR = hedge->hedMat->hedPrm->prmFac;
                      dotR  = vdotc(3, faceR->faceq, zeye);
                      dot   = vdotc(3, face->faceq, faceR->faceq);
                      if ((dot <= creas) || (dotL * dotR <= 0.0)) {
                        mova3c(ptb[0], ptb[1], ptb[2], 1.0);
                        drwa3c(pta[0], pta[1], pta[2], 1.0);
                      }
                    } else {
                      mova3c(ptb[0], ptb[1], ptb[2], 1.0);
                      drwa3c(pta[0], pta[1], pta[2], 1.0);
                    }
                    hedge = hedge->nxtHedPrm;
                  } while (hedge != perim->prmHed);
                  colrfc(face->kcolor);
                  colrsc(ktext);
                  perim = perim->nxtPrm;
                }
                colrfc(kfrgnd);
              }
            }
            face = face->nxtFac;
          }
        }
        solid = solid->nxtSld;
      }
      if (body) {
        denom = 4.0 / fabs(szaxes);  /* Draw other Axes quarter size. */
        axes  = body->bdyAxs;
        while (axes) {
          if (axes->kcolor > 0) {               /* Test visibility,   */
            colrfc(axes->kcolor);               /*   set axes color,  */
            for (j=0; j<3; j++) {               /*     and draw axes. */
              mova3c(axes->S[0][3], axes->S[1][3], axes->S[2][3], 1.0);
              drwr3c(axes->S[0][j], axes->S[1][j], axes->S[2][j],denom);
            }
            colrfc(kfrgnd);
          }
          axes = axes->nxtAxs;
        }
      }
    }
    if (body) {
      body = body->nxtBdy;
    } else {
      solid = System.sysSld;                   /* Draw orphan Solids. */
    }
  } while (body || solid);

/* Draw any visible joint axes. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    axes = joint->jntAxB;
    body = axes->axsBdy;
    if ((body->kcolor > 0) && (joint->axsize != 0.0)) {
      colrfc(body->kcolor);
      colrsc(body->kcolor);
      mpyxxc(body->T0j, axes->S, xform);
      for (i=0; i<3; i++) {
        mova3c(xform[0][3], xform[1][3], xform[2][3], 1.0);
        drwr3c(xform[0][i], xform[1][i], xform[2][i], joint->axsize);
        qpensc(&spen, &tpen, &lpen);
        if (lpen) {
          label[0] = 'u' + i;
          label[1] = '\0';
          htextc(label);
        }
      }
    }
  }

/* Draw the visible kinematic loops. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
      if (axes->kcolor > 0) {
        colrfc(axes->kcolor);
        mpyxxc(body->T0j, axes->S, xform);
        for (i=0; i<3; i++) {
          ptb[i] = body->T0j[i][3];
          pta[i] = xform[i][3];
        }
        dashc(3);
        arro3c(0.025, ptb, pta, 2);
        dashc(1);
        mova3c(ptb[0], ptb[1], ptb[2], 1.0);
        drwa3c(pta[0], pta[1], pta[2], 1.0);
      }
    }
  }

/* Draw all visible springs. */
  for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
    if (spring->kcolor > 0) {
      colrfc(spring->kcolor);
      ptposc(spring->spgPtB, ptb);
      ptposc(spring->spgPtA, pta);
      drspgc(ptb, pta);
    }
  }

/* Draw all visible dampers. */
  for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
    if (damper->kcolor > 0) {
      colrfc(damper->kcolor);
      ptposc(damper->dmpPtB, ptb);
      ptposc(damper->dmpPtA, pta);
      drdmpc(ptb, pta);
    }
  }

/* Draw all visible forces. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (force=body->bdyFrc; force; force=force->nxtFrc) {
      if (force->kcolor > 0) {
        colrfc(force->kcolor);
        ptposc(force->frcPtB, ptb);
        ptposc(force->frcPtA, pta);
        ptposc(force->frcPtC, ptc);
        for (i=0; i<3; i++) {
          pta[i] = ptc[i] + ptb[i] - pta[i];
        }
        drfrcc(ptc, pta);
      }
    }
  }

/* Draw all visible torques. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
      if (torque->kcolor > 0) {
        colrfc(torque->kcolor);
        ptposc(torque->trqPtB, ptb);
        ptposc(torque->trqPtA, pta);
        for (i=0; i<3; i++) {
          ptc[i] = body->T0j[i][3];
          pta[i] = ptc[i] + ptb[i] - pta[i];
        }
        drtrqc(ptc, pta);
      }
    }
  }

/* Finish the picture. */
  dashc(0);
  colrfc(kfrgnd);
  colrsc(ktext);
  n = lenc(System.title);
  if (n > 0) {
    qchszc(&ssymbl, &tsymbl);
    s = 0.5 * (1.0 - n * ssymbl);
    t = 0.25 * tsymbl;
    movasc(s, t);
    htextc(System.title);
  }
  movasc(0.0, 1.0);

/* Pause if PAUSE ON is set. */
  if (qbitc(XQ_PAUSE, (void *) &System.xeqflags)) {
    qdvc(device, chdvc, lcdvc);
    if (strcmp(device, "alpha") != 0) waitc();
  } else {
    clrplc();
  }
  ldx32c(x32sav);  /* Restore the original colors and transformation. */
  colrfc(kfrgnd);
  colrsc(ktext);
  return;
}
