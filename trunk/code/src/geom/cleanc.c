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
|     few edges, deletes any edges of zero length or having less than 
|     two faces, and deletes any faces having zero area.
|
|     Access:
|       (void) cleanc(Solid *solid);
|     Solid *solid,i-Pointer to the Solid record to be cleaned.
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
 
#include "libgeo.h"
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
            npi, nvx1, nvx2, nvx3;
  real    angle, anglmx, big, costh, cross[3], curvature, denom, dist,
            distmx, dist12, dist34, dtheta, sinth, tau1, tau2, theta, w, 
            w1, w2, w3, w4, x12, x31, x34, y12, y31, y34, z12, z31, z34;

/* Initialize. */
  lwait = FALSE;
  nvx1 = 0;
  nvx2 = 0;
  ned1 = 0;
  ned2 = 0;
  ned3 = 0;
  ned4 = 0;
  ned5 = 0;
  nfc1 = 0;
  nfc2 = 0;
  nfc3 = 0;
  if (solid->type == SOLID) {
    echoc();
    textc("Checking integrity of body '", FALSE);
    textc(solid->sldBdy->name, FALSE);
    if (solid->sldBdy->nslds > 1) {
      textc(",", FALSE);
      textc(solid->name, FALSE);
    }
    textc("'.", TRUE);
_BEGIN:
    nvx3 = 0;
    nfc4 = 0;
    nfc5 = 0;
    nfc6 = 0;
    anglmx = 0.0;
    distmx = 0.0;

/* Check all Vertices. */
_VERTEX:
    solid->nvrtxs = 0;

/* Eliminate any Vertices with no Corners. */
    vertex = solid->sldVtx;
    while (vertex) {
      if (vertex->vtxCnr == NULL) {
        xvtxc(vertex);
        ++nvx1;
        goto _VERTEX;
      }

/* Merge any coincident vertices. */
      w = vertex->coord[3];
      vtx = mkvtxc(solid, vertex->coord[0]/w, vertex->coord[1]/w,
        vertex->coord[2]/w);
      if (vtx != vertex) {
        corner = vtx->vtxCnr;
        if (corner) {
          while (corner->nxtCnr) corner = corner->nxtCnr;
          corner->nxtCnr = vertex->vtxCnr;
        }
        vertex->vtxCnr = NULL;
        xvtxc(vertex);
        ++nvx2;
        goto _VERTEX;
      }
      vertex->vtxno = ++solid->nvrtxs;  /* vtxno = 1, 2, ..., nvrtxs. */
      vertex = vertex->nxtVtx;
    }

/* Check all Edges. */
    lflag = FALSE;
_EDGE:
    solid->nedges = 0;
    edge = solid->sldEdg;
    while (edge) {

/* Eliminate any under-defined or zero-length Edges. */
      if ((edge->edgHeL == NULL) || (edge->edgHeR == NULL)) {
        lflag = TRUE;
        ++ned1;
        xedgc(edge);
        goto _EDGE;
      } else if ((edge->edgHeL->hedCnr == NULL) ||
                 (edge->edgHeR->hedCnr == NULL)) {
        lflag = TRUE;
        ++ned2;
        xedgc(edge);
        goto _EDGE;
      } else if (edge->edgHeL->hedCnr == edge->edgHeR->hedCnr) {
        lflag = TRUE;
        ++ned3;
        xedgc(edge);
        goto _EDGE;
      } else if (edge->edgHeL == edge->edgHeR) {
        lflag = TRUE;
        ++ned4;
        xedgc(edge);
        goto _EDGE;
      }
      edlngc(edge);
      if (edge->length < zrogeo) {
        lflag = TRUE;
        ++ned5;
        xedgc(edge);
        goto _EDGE;
      }
      ++solid->nedges;
      edge = edge->nxtEdg;
    }
    if (lflag) goto _VERTEX;

/* Check all Faces. */
    solid->nfaces = 0;
    solid->nprms  = 0;
    solid->nhedgs = 0;
    face = solid->sldFac;
    while (face) {

/* Check all Perims of each Face. */
      face->nprms = 0;
      perim = face->facPrm;
      while (perim) {

/* Eliminate any Perims with less than three Hedges. */
        perim->nhedgs = 0;
        hedge = perim->prmHed;
        do {
          ++perim->nhedgs;
          ++solid->nhedgs;
          hedge = hedge->nxtHedPrm;
        } while (hedge != perim->prmHed);
        if (perim->nhedgs < 3) {
          ++nfc1;
          xprmc(perim);
          goto _VERTEX;
        }
        ++face->nprms;
        ++solid->nprms;
        perim = perim->nxtPrm;
      }
      fcnrmc(face);
      face->facno = ++solid->nfaces;    /* facno = 1, 2, ..., nfaces. */
      face = face->nxtFac;
    }

/* Merge any coplanar or adjacent small faces. */
    edge = solid->sldEdg;
    while (edge) {
      perimL = edge->edgHeL->hedPrm;
      perimR = edge->edgHeR->hedPrm;
      if (fabs(prmarc(perimR)) < edge->length * zrogeo) {
        ++nfc2;                    /* Merge small perimR into perimL. */
        hedge = perimR->prmHed;
        do {
          hedge->hedPrm = perimL;
          hedge = hedge->nxtHedPrm;
        } while (hedge != perimR->prmHed);
        hedge = edge->edgHeR;
        while (hedge->nxtHedPrm != edge->edgHeR) hedge=hedge->nxtHedPrm;
        hedge->nxtHedPrm = edge->edgHeL->nxtHedPrm;
        hedge = edge->edgHeL;
        while (hedge->nxtHedPrm != edge->edgHeL) hedge=hedge->nxtHedPrm;
        hedge->nxtHedPrm = edge->edgHeR->nxtHedPrm;
        edge->edgHeR->nxtHedPrm = edge->edgHeL;
        edge->edgHeL->nxtHedPrm = edge->edgHeR;
        edge->edgHeL->hedPrm = perimR;
        perimL->nhedgs += perimR->nhedgs - 2;
        perimR->nhedgs  = 2;
        xprmc(perimR);
        face = perimL->prmFac;
        xedgc(edge);
        goto _BEGIN;
      }
      if (fabs(prmarc(perimL)) < edge->length * zrogeo) {
        ++nfc2;                    /* Merge small perimL into perimR. */
        hedge = perimL->prmHed;
        do {
          hedge->hedPrm = perimR;
          hedge = hedge->nxtHedPrm;
        } while (hedge != perimL->prmHed);
        hedge = edge->edgHeL;
        while (hedge->nxtHedPrm != edge->edgHeL) hedge=hedge->nxtHedPrm;
        hedge->nxtHedPrm = edge->edgHeR->nxtHedPrm;
        hedge = edge->edgHeR;
        while (hedge->nxtHedPrm != edge->edgHeR) hedge=hedge->nxtHedPrm;
        hedge->nxtHedPrm = edge->edgHeL->nxtHedPrm;
        edge->edgHeL->nxtHedPrm = edge->edgHeR;
        edge->edgHeR->nxtHedPrm = edge->edgHeL;
        edge->edgHeR->hedPrm = perimL;
        perimR->nhedgs += perimL->nhedgs - 2;
        perimL->nhedgs  = 2;
        xprmc(perimL);
        face = perimR->prmFac;
        xedgc(edge);
        goto _BEGIN;
      }
      vcrosc(perimL->prmFac->faceq, perimR->prmFac->faceq, cross);
      if (vabsc(3, cross) < zrogeo) {  /* Test for and merge coplanar */
        if (mrgfac(perimL, perimR)) {  /*   perimL and perimR.        */
          ++nfc3;
          goto _BEGIN;
        }
      }      
      edge = edge->nxtEdg;
    }

/* Verify Vertex and Face normal data of all Perims. */
    face = solid->sldFac;
    while (face) {
      vx1 = hedge->hedCnr->cnrVtx;
      vx2 = hedge->nxtHedPrm->hedCnr->cnrVtx;
      perim = face->facPrm;
      while (perim) {
        hedge = perim->prmHed;
        do {
          vertex = hedge->hedCnr->cnrVtx;
          dist = vdotc(3, vertex->coord, face->faceq) + face->faceq[3];
          dist = fabs(dist);   /* Distance from Vertex to Face plane. */
          if (dist > (100.0 * zrogeo)) {
            ++nvx3;
            if (dist > distmx) distmx = dist;    /* Remember largest. */
          }
          hedge = hedge->nxtHedPrm;
        } while (hedge != perim->prmHed);
        if (prmarc(perim) < (-10.0*zrogeo)) ++nfc4;/*Reversed normal? */
        perim = perim->nxtPrm;
      }
      face = face->nxtFac;
    }

/* Test for intersecting edges. */
    curvature = 0.0;
    face = solid->sldFac;
    while (face) {                                 /* Test each Face. */
      indexz = 0;
      big    = 0.0;
      for (i=0; i<3; i++) {/*Identify best projection plane for Face. */
        if (fabs(face->faceq[i]) > big) {
          indexz = i;
          big = fabs(face->faceq[i]);
        }
      }
      indexx = (indexz + 1) % 3;
      indexy = (indexx + 1) % 3;
      perim = face->facPrm;
      while (perim) {                /* Test each Perim of this Face. */
        npi   = -2;
        theta = 0.0;
        hedge = perim->prmHed;
        do {                        /* Test each Hedge of this Perim. */
          dist12 = hedge->hedEdg->length;
          if (fabs(dist12) < zrogeo) dist12 = zrogeo;
          vx1 = hedge->hedCnr->cnrVtx;
          w1  = vx1->coord[3];
          vx2 = hedge->nxtHedPrm->hedCnr->cnrVtx;
          w2  = vx2->coord[3];
          x12 = (vx1->coord[indexx]/w1-vx2->coord[indexx]/w2) / dist12;
          y12 = (vx1->coord[indexy]/w1-vx2->coord[indexy]/w2) / dist12;
          z12 = (vx1->coord[indexz]/w1-vx2->coord[indexz]/w2) / dist12;
          nxthed = hedge->nxtHedPrm;
          do {      /* Test against all further Hedges of this Perim. */
            vx3 = nxthed->hedCnr->cnrVtx;
            w3  = vx3->coord[3];
            vx4 = nxthed->nxtHedPrm->hedCnr->cnrVtx;
            w4  = vx4->coord[3];
            x34 = vx3->coord[indexx] / w3 - vx4->coord[indexx] / w4;
            y34 = vx3->coord[indexy] / w3 - vx4->coord[indexy] / w4;
            z34 = vx3->coord[indexz] / w3 - vx4->coord[indexz] / w4;
            x31 = vx3->coord[indexx] / w3 - vx1->coord[indexx] / w1;
            y31 = vx3->coord[indexy] / w3 - vx1->coord[indexy] / w1;
            z31 = vx3->coord[indexz] / w3 - vx1->coord[indexz] / w1;
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
            nxthed = nxthed->nxtHedPrm;
          } while (nxthed != perim->prmHed);

/* Test the Gauss Benet theorem. */
          ++npi;
          nxthed = hedge->nxtHedPrm;
          dist34 = nxthed->hedEdg->length;
          if (fabs(dist34) < zrogeo) dist34 = zrogeo;
          vx3 = nxthed->hedCnr->cnrVtx;
          w3  = vx3->coord[3];
          vx4 = nxthed->nxtHedPrm->hedCnr->cnrVtx;
          w4  = vx4->coord[4];
          x34 = (vx3->coord[indexx]/w3-vx4->coord[indexx]/w4) / dist34;
          y34 = (vx3->coord[indexy]/w3-vx4->coord[indexy]/w4) / dist34;
          z34 = (vx3->coord[indexz]/w3-vx4->coord[indexz]/w4) / dist34;
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
        angle = fabs(fabs(theta) / npi - PI);
        if (angle > 100.0 * zrogeo) {
          ++nfc6;
          if (angle > anglmx) anglmx = angle;
        }
        curvature += theta;
        perim = perim->nxtPrm;
      }
      face = face->nxtFac;
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
      textc(" face perims with two or less edges are deleted.", TRUE);
      lwait = TRUE;
    }
    if (nfc2 > 0) {
      itextc(nfc2);
      textc(" faces with zero area are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned1 > 0) {
      itextc(ned1);
      textc(" edges without two faces are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned2 > 0) {
      itextc(ned2);
      textc(" edges without two vertices are deleted.", TRUE);
      lwait = TRUE;
    }
    if (ned3 > 0) {
      itextc(ned3);
      textc(" edges meeting a vertex twice are deleted.", TRUE);
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
      gtextc(anglmx * 180.0 / PI);
      textc(" degrees.", TRUE);
      lwait = TRUE;
    }
    if ((nvx3 + nfc4 + nfc5 + nfc6) == 0) {
      if ((ngenus % 2) == 0) {
        textc("No errors were found in this solid", FALSE);
        if (ngenus > 0) {
          textc(" of genus ", FALSE);
          itextc(ngenus / 2);
        } else if (ngenus < 0) {
          textc(" of multiplicity ", FALSE);
          itextc(1 - ngenus / 2);
        }
        textc(".", TRUE);
      } else {
        textc("Warning:  This geometry is not valid.", TRUE);
        lwait = TRUE;
      }
    }
    if (lwait) waitc();
  }
  return;
}
