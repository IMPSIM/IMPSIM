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
/* dmprpc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Calculate and store the mass properties of a three-dimensional
|     Solid shape.
|
|     Access:
|       (void) dmprpc(Word name, real density);
|     Word name,   i-Name of the specified Solid.
|     real density,i-Mass density of the solid body material.
|
|     Error Conditions:
|       System.nerror = 4 indicates that no Solid with the specified
|     name could be found.  A message is printed and no data is stored.
|
|     Comments:
|       The mass properties of Solid shapes are found using four-point
|     Gaussian quadrature over triangles on all faces.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dmprpc(Word name, real density)
#else
  void dmprpc(name, density)
  Word  name;
  real *density;
#endif
{
  Body   *body;
  Face   *face;
  Hedge  *hedge;
  Mass   *mass;
  Perim  *perim;
  Solid  *solid;
  Vertex *vx0, *vxb, *vxa;
  int     i;
  real    areax, areay, areaz, ax, ay, az, cx, cy, cz, dx, dy, dz,
    px[4], py[4], pz[4], rii[3], rij[3], smass, sum, w[4], x[3], y[3],
    z[3];

/* Initialize. */
  w[0] = -0.5625;
  for (i=0; i<3; i++) {
    w[i+1] = 0.52083333;    /* w[i] are quadrature weighting factors. */
  }

/* Locate the named Solid record. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (solid=body->bdySld; solid; solid=solid->nxtSld) {
      if (strcmp(name, solid->name) == 0) {

/* Print a message for the update of a previous Mass record. */
        if (body->bdyMas) {
          mass = body->bdyMas;
          echoc();
          textc("*** Mass data are updated for body '", FALSE);
          textc(body->name, FALSE);
          textc("'. ***", TRUE);

/* Form the new Mass record for the Body if needed. */
        } else {
          mass = (Mass *) malloc(sizeof(Mass));
          if (mass) {
            mass->type = MASS;
            mass->masBdy = body;
            for (i=0; i<10; i++) {
              mass->I[i] = 0.0;
            }
            body->bdyMas = mass;
          }
        }

/* Initialize the properties of this Solid. */
        solid->area   = 0.0;
        solid->volume = 0.0;
        for (i=0; i<3; i++) {
          solid->cg[i] = 0.0;
          rii[i] = 0.0;
          rij[i] = 0.0;
        }

/* Cycle through all Perims of the Faces of this Solid. */
        for (face=solid->sldFac; face; face=face->nxtFac) {
          areax = 0.0;
          areay = 0.0;
          areaz = 0.0;
          for (perim=face->facPrm; perim; perim=perim->nxtPrm) {

/* Cycle through all Hedges of the Perim. */
            hedge = perim->prmHed;
            if (hedge->hedEdg->edgHeL == hedge) {
              vx0 = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
            } else {
              vx0 = hedge->hedEdg->edgHeR->hedCnr->cnrVtx;
            }
            x[0]  = vx0->coord[0];
            y[0]  = vx0->coord[1];
            z[0]  = vx0->coord[2];
            do {
              if (hedge->hedEdg->edgHeL == hedge) {
                vxb = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
                vxa = hedge->hedEdg->edgHeR->hedCnr->cnrVtx;
              } else {
                vxb = hedge->hedEdg->edgHeR->hedCnr->cnrVtx;
                vxa = hedge->hedEdg->edgHeL->hedCnr->cnrVtx;
              }
              x[1] = vxb->coord[0];
              y[1] = vxb->coord[1];
              z[1] = vxb->coord[2];
              x[2] = vxa->coord[0];
              y[2] = vxa->coord[1];
              z[2] = vxa->coord[2];

/* Data is now in terms of a single triangle. */
              px[0] = (x[0] + x[1] + x[2]) / 3.0;
              py[0] = (y[0] + y[1] + y[2]) / 3.0;
              pz[0] = (z[0] + z[1] + z[2]) / 3.0;
              dx = 0.6 * px[0];
              dy = 0.6 * py[0];
              dz = 0.6 * pz[0];
              for (i=0; i<3; i++) {
                px[i+1] = dx + 0.4 * x[i];
                py[i+1] = dy + 0.4 * y[i];
                pz[i+1] = dz + 0.4 * z[i];
              }

/* Calculate the area vector for this triangle. */
              ax = 0.5 * (z[0] * (y[2] - y[1])
                       +  z[1] * (y[0] - y[2])
                       +  z[2] * (y[1] - y[0]));
              ay = 0.5 * (x[0] * (z[2] - z[1])
                       +  x[1] * (z[0] - z[2])
                       +  x[2] * (z[1] - z[0]));
              az = 0.5 * (y[0] * (x[2] - x[1])
                       +  y[1] * (x[0] - x[2])
                       +  y[2] * (x[1] - x[0]));
              areax += ax;
              areay += ay;
              areaz += az;

/* Calculate mass properties for this triangle. */
              for (i=0; i<4; i++) {
                cx = ax * w[i] * px[i];  /* 0th power of coordinates. */
                cy = ay * w[i] * py[i];
                cz = az * w[i] * pz[i];
                solid->volume += (cx + cy + cz);
                cx *= px[i];             /* 1st power of coordinates. */
                cy *= py[i];
                cz *= pz[i];
                solid->cg[0] += cx;
                solid->cg[1] += cy;
                solid->cg[2] += cz;
                rij[0] += (cx * py[i]);
                rij[1] += (cy * pz[i]);
                rij[2] += (cz * px[i]);
                cx *= px[i];             /* 2nd power of coordinates. */
                cy *= py[i];
                cz *= pz[i];
                rii[0] += (cy + cz);
                rii[1] += (cz + cx);
                rii[2] += (cx + cy);
              }
              hedge = hedge->nxtHedPrm;
            } while (hedge != perim->prmHed);
          }
          solid->area += sqrt(areax*areax + areay*areay + areaz*areaz);
        }
        solid->volume /= 3.0;
        smass = density * solid->volume;
        sum = 0.0;
        for (i=0; i<3; i++) {
          rii[i] *= (density / 3.0);
          sum    += (0.5 * rii[i]);
          rij[i] *= (0.5 * density);
          solid->cg[i] /= (2.0 * solid->volume);
          mass->I[i+6] += (smass * solid->cg[i]);
        }
        mass->I[0] += (sum - rii[0]);
        mass->I[1] += rij[0];
        mass->I[2] += (sum - rii[1]);
        mass->I[3] += rij[2];
        mass->I[4] += rij[2];
        mass->I[5] += (sum - rii[2]);
        mass->I[9] += smass;
        goto _1;
      }
    }
  }
  echoc();
  textc("*** There is no solid shape named '", FALSE);
  textc(name, FALSE);
  textc("' attached to any body. ***", TRUE);
  System.nerror = 4;
_1:
  return;
}
