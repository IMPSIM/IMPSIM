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
/* cleanc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Given a pointer to a specified Solid, this routine merges any
|     coincident vertices, deletes any vertices or faces containing too
|     few edges, deletes any edges having zero length or too few faces,
|     and deletes any faces having zero area.
|
|     Access:
|       (void) cleanc(Solid *solid);
|     Solid *solid,o-Pointer to the Solid record to be cleaned.
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
  void cleanc(Solid *solid)
#else
  void cleanc(solid)
  Solid *solid;
#endif
{
  Edge   *edge;
  Face   *face;
  Hedge  *hedge, *nxthed;
  Perim  *perim, *perimL, *perimR;
  Corner *corner;
  Vertex *vertex, *vtx, *vx1, *vx2, *vx3, *vx4;
  int     i, indexx, indexy, indexz, lflag, lwait, ned1, ned2, ned3,
            ned4, ned5, nfc1, nfc2, nfc3, nfc4, nfc5, nfc6, ngenus,
            numpi, nvx1, nvx2, nvx3;
  real    angle, anglmx, big, costh, cross[3], curvature, denom, dist,
            distmx, dist12, dist34, dtheta, sinth, tau1, tau2, theta,
            x12, x31, x34, y12, y31, y34, z12, z31, z34;

/* Initialize. */
  lwait = FALSE;
  nvx1 = 0;
  nvx2 = 0;
  nfc1 = 0;
  nfc2 = 0;
  nfc3 = 0;
  ned1 = 0;
  ned2 = 0;
  ned3 = 0;
  ned4 = 0;
  ned5 = 0;
  if (solid->type == SOLID) {
    textc("Checking integrity of Solid '", FALSE);
    textc(solid->name, FALSE);
    textc("'.", TRUE);
_2: nvx3 = 0;
    nfc4 = 0;
    nfc5 = 0;
    nfc6 = 0;
    anglmx = 0.0;
    distmx = 0.0;

/* Eliminate any unused vertices. */
_3: solid->nvrtxs = 0;
    for (vertex=solid->sldVtx; vertex; vertex=vertex->nxtVtx) {
      if (vertex->vtxCnr == NULL) {
        xvtxc(vertex);
        ++nvx1;
        goto _3;
      }

/* Merge any coincident vertices. */
      vtx = mkvtxc(solid, vertex->coord[0], vertex->coord[1],
        vertex->coord[2]);
      if (vtx != vertex) {
        corner = vtx->vtxCnr;
        while (corner->nxtCnr != NULL) corner = corner->nxtCnr;
        corner->nxtCnr = vertex->vtxCnr;
        vertex->vtxCnr = vtx->vtxCnr;
        vtx->vtxCnr = NULL;
        xvtxc(vtx);
        ++nvx2;
        goto _3;
      }
      vertex->vtxno = solid->nvrtxs;
      ++solid->nvrtxs;
    }

/* Eliminate any under-defined or zero-length Edges. */
    lflag = FALSE;
_4: solid->nedges = 0;
    for (edge=solid->sldEdg; edge; edge=edge->nxtEdg) {
      if ((edge->edgHeL->hedCnr == NULL) ||
          (edge->edgHeR->hedCnr == NULL)) {
        lflag = TRUE;
        ++ned1;
        xedgc(edge);
        goto _4;
      } else if (edge->edgHeL->hedCnr == edge->edgHeR->hedCnr) {
        lflag = TRUE;
        ++ned2;
        xedgc(edge);
        goto _4;
      } else if ((edge->edgHeL == NULL) || (edge->edgHeR == NULL)) {
        lflag = TRUE;
        ++ned3;
        xedgc(edge);
        goto _4;
      } else if (edge->edgHeL == edge->edgHeR) {
        lflag = TRUE;
        ++ned4;
        xedgc(edge);
        goto _4;
      } else if (edlngc(edge) < zrogeo) {
        corner = edge->edgHeL->hedCnr;
        while (corner->nxtCnr != NULL) corner = corner->nxtCnr;
        corner->nxtCnr = edge->edgHeR->hedCnr;
        edge->edgHeR->hedCnr = NULL;
        lflag = TRUE;
        ++ned5;
        xedgc(edge);
        goto _4;
      }
      ++solid->nedges;
    }
    if (lflag) goto _3;

/* Eliminate any under-defined Faces. */
    solid->nfaces = 0;
    for (face=solid->sldFac; face; face=face->nxtFac) {
      edsrtc(face);
      face->nprms = 0;
      for (perim=face->facPrm; perim; perim=perim->nxtPrm) {
        perim->nhedgs = 0;
        hedge = perim->prmHed;
        do {
          ++perim->nhedgs;
          hedge = hedge->nxtHedPrm;
        } while (hedge != perim->prmHed);
        if (perim->nhedgs < 3) {
          ++nfc1;
          xprmc(perim);
          goto _3;
        }
        ++face->nprms;
      }
      fcnrmc(face);
      face->facno = solid->nfaces;
      ++solid->nfaces;
    }

/* Merge any adjacent small faces. */
    for (edge=solid->sldEdg; edge; edge=edge->nxtEdg) {
      perimL = edge->edgHeL->hedPrm;
      perimR = edge->edgHeR->hedPrm;
      if (fabs(prmarc(perimR)) < edlngc(edge) * zrogeo) {
        ++nfc2;
        hedge = perimR->prmHed;
        while (hedge->nxtHedPrm) {
          hedge->hedPrm = perimL;
          hedge = hedge->nxtHedPrm;
        }
        hedge->hedPrm = perimL;
        hedge->nxtHedPrm = perimL->prmHed;
        perimL->prmHed = perimR->prmHed;
        perimL->nhedgs += perimR->nhedgs;
        xprmc(perimR);
        face = perimL->prmFac;
        xedgc(edge);
        goto _2;
      }
    }
    vcrosc(perimL->prmFac->faceq, perimR->prmFac->faceq, cross);
    if (vabsc(3, cross) < zrogeo) {
      if (mrgfac(perimL, perimR)) {
        ++nfc3;
        goto _2;
      }
    }

/* Verify Vertex and Face normal data. */
    for (face=solid->sldFac; face; face=face->nxtFac) {
      for (perim=face->facPrm; perim; perim=perim->nxtPrm) {
        hedge = perim->prmHed;
        do {
          vertex = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
          dist = vdotc(4, vertex->coord, face->faceq);
          dist = fabs(dist);
          if (dist > (100.0 * zrogeo)) {
            ++nvx3;
            if (dist > distmx) distmx = dist;
          }
          hedge = hedge->nxtHedPrm;
        } while (hedge != perim->prmHed);


/* Test for reversed Face normals. */
        if (prmarc(perim) < (-10.0 * zrogeo)) ++nfc4;
      }
    }

/* Test for intersecting edges. */
    curvature = 0.0;
    for (face=solid->sldFac; face; face=face->nxtFac) {
      indexz = 0;
      big    = 0.0;
      for (i=0; i<3; i++) {
        if (fabs(face->faceq[i]) > big) {
          indexz = i;
          big = fabs(face->faceq[i]);
        }
      }
      indexx = (indexz + 1) % 3;
      indexy = (indexx + 1) % 3;
      for (perim=face->facPrm; perim; perim=perim->nxtPrm) {
        numpi = -2;
        theta = 0.0;
        hedge = perim->prmHed;
        do {
          dist12 = edlngc(hedge->hedEdg);
          if (hedge->hedEdg->edgHeL == hedge) {
            vx1 = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
            vx2 = hedge->hedEdg->edgHeR->hedCnr->cnrVtx;
          } else if (hedge->hedEdg->edgHeR == hedge) {
            vx1 = hedge->hedEdg->edgHeR->hedCnr->cnrVtx;
            vx2 = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
          } else {
            abortc();
          }
          x12 = (vx1->coord[indexx] - vx2->coord[indexx]) / dist12;
          y12 = (vx1->coord[indexy] - vx2->coord[indexy]) / dist12;
          z12 = (vx1->coord[indexz] - vx2->coord[indexz]) / dist12;
          for (nxthed=hedge->nxtHedPrm;nxthed;nxthed=nxthed->nxtHedPrm){
            if (nxthed->hedEdg->edgHeL == nxthed) {
              vx3 = nxthed->hedEdg->edgHeL->hedCnr->cnrVtx;
              vx4 = nxthed->hedEdg->edgHeR->hedCnr->cnrVtx;
            } else if (nxthed->hedEdg->edgHeR == nxthed) {
              vx3 = nxthed->hedEdg->edgHeR->hedCnr->cnrVtx;
              vx4 = nxthed->hedEdg->edgHeL->hedCnr->cnrVtx;
            } else {
              abortc();
            }
            x34 = vx3->coord[indexx] - vx4->coord[indexx];
            y34 = vx3->coord[indexy] - vx4->coord[indexy];
            z34 = vx3->coord[indexz] - vx4->coord[indexz];
            x31 = vx3->coord[indexx] - vx1->coord[indexx];
            y31 = vx3->coord[indexy] - vx1->coord[indexy];
            z31 = vx3->coord[indexz] - vx1->coord[indexz];
            denom = y12 * x34 - x12 * y34;
            if (fabs(denom) > zrogeo) {
              tau1 = (x31 * y34 - y31 * x34) / denom;
              if ((tau1 > zrogeo) && (tau1 < (dist12 - zrogeo))) {
                tau2 = (y12 * x31 - x12 * y31) / denom;
                if ((tau2 > zrogeo) && (tau2 < (1.0 - zrogeo))) {
                  if (fabs(tau1*z12 - tau2*z34 + z31) > zrogeo) ++nfc5;
                }
              }
            }
          }

/* Test the Gauss Benet theorem. */
          ++numpi;
          if (hedge->nxtHedPrm == NULL) {
            nxthed = perim->prmHed;
          } else {
            nxthed = hedge->nxtHedPrm;
          }
          dist34 = edlngc(nxthed->hedEdg);
          if (fabs(dist34) < zrogeo) dist34 = zrogeo;
          if (nxthed->hedEdg->edgHeL == nxthed) {
            vx3 = nxthed->hedEdg->edgHeL->hedCnr->cnrVtx;
            vx4 = nxthed->hedEdg->edgHeR->hedCnr->cnrVtx;
          } else if (nxthed->hedEdg->edgHeR == nxthed) {
            vx3 = nxthed->hedEdg->edgHeR->hedCnr->cnrVtx;
            vx4 = nxthed->hedEdg->edgHeL->hedCnr->cnrVtx;
          } else {
            abortc();
          }
          x34 = (vx3->coord[indexx] - vx4->coord[indexx]) / dist34;
          y34 = (vx3->coord[indexy] - vx4->coord[indexy]) / dist34;
          z34 = (vx3->coord[indexz] - vx4->coord[indexz]) / dist34;
          cross[indexx] = y12 * z34 - z12 * y34;
          cross[indexy] = z12 * x34 - x12 * z34;
          cross[indexz] = x12 * y34 - y12 * x34;
          sinth = vdotc(3, face->faceq, cross);
          costh = -(x12 * x34 + y12 * y34 + z12 * z34);
          dtheta = atan2(sinth, costh);
          if (dtheta < 0.0) dtheta += (PI + PI);
          theta += dtheta;
          hedge = hedge->nxtHedPrm;
        } while (hedge != perim->prmHed);
        curvature += theta;
        angle = fabs(fabs(theta) / numpi - PI);
        if (angle > 100.0 * zrogeo) {
          ++nfc6;
          if (angle > anglmx) anglmx = angle;
        }
      }
    }
    ngenus = nint(curvature / (PI + PI)) - (solid->nvrtxs) + 2;

/* Print error messages. */
    if (nvx1 > 0) {
      itextc(nvx1);
      textc(" isolated vertices are deleted.", TRUE);
      lwait = TRUE;
    }
    if (nvx2 > 0) {
      itextc(nvx2);
      textc(" coincident vertices are merged.", TRUE);
      lwait = TRUE;
    }
    if (nfc1 > 0) {
      itextc(nfc1);
      textc(" faces of two or less edges are deleted.", TRUE);
      lwait = TRUE;
    }
    if (nfc2 > 0) {
      itextc(nfc2);
      textc(" faces with zero area are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned1 > 0) {
      itextc(ned1);
      textc(" edges without two vertices are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned2 > 0) {
      itextc(ned2);
      textc(" edges meeting a vertex twice are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned3 > 0) {
      itextc(ned3);
      textc(" edges without two faces are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned4 > 0) {
      itextc(ned4);
      textc(" edges without any faces are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned5 > 0) {
      itextc(ned5);
      textc(" edges of zero length are deleted.", TRUE);
      lwait = TRUE;
    }
    if (nvx3 > 0) {
      textc("Warning: ", FALSE);
      itextc(nvx3);
      textc(" vertices do not fit face planes.", TRUE);
      textc("  Max error = ", FALSE);
      gtextc(distmx);
      textc(" units.", TRUE);
      lwait = TRUE;
    }
    if (nfc3 > 0) {
      itextc(nfc3);
      textc(" adjacent coplanar faces are merged.", TRUE);
      lwait = TRUE;
    }
    if (nfc4 > 0) {
      textc("Warning: ", FALSE);
      itextc(nfc4);
      textc(" faces have reversed normals.", TRUE);
      lwait = TRUE;
    }
    if (nfc5 > 0) {
      textc("Warning: ", FALSE);
      itextc(nfc5);
      textc(" faces are self-intersecting.", TRUE);
      lwait = TRUE;
    }
    if (nfc6 > 0) {
      textc("Warning: ", FALSE);
      itextc(nfc6);
      textc(" faces are not geometrically closed.", TRUE);
      textc("  Max error = ", FALSE);
      gtextc(System.ascale*anglmx);
      textc(" degrees.", TRUE);
      lwait = TRUE;
    }
    if ((nvx3 + nfc4 + nfc5 + nfc6) == 0) {
      if ((ngenus % 2) == 0) {
        textc("No errors were found in this body", FALSE);
        if (ngenus > 0) {
          textc(" of genus ", FALSE);
        } else {
          textc(" of multiplicity ", FALSE);
        }
        itextc((abs(ngenus) / 2));
        textc(".", TRUE);
      } else {
        textc("Warning:  This geometry is not valid.", TRUE);
      }
      lwait = TRUE;
    }
    if (lwait) waitc();
  }
  return;
}
