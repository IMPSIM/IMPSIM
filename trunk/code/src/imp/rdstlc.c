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
/* rdstlc-01 Jan 00:15 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       This routine reads solid geometry previously stored in STL
|     format from a file opened for reading on a specified lun.
|
|     Access:
|       (void) rdstlc(int lun, Body *body, Solid *solid);
|     int    lun,  i-Logical unit for reading the already opened file.
|     Body  *body, i-Pointer to the Body record for this Solid.
|     Solid *solid,o-Pointer to the Solid record created.
|
|     Error Conditions:
|       If lun has not been opened or if the file is not in proper STL
|     format, an error message is printed and exit is made with no solid
|     formed.
|
|     Comments:
|       If *body does not point to a valid BODY record, then the new
|     solid is created on the list of orphan Solids in the System.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void rdstlc(int lun, Body *body, Solid *solid)
#else
  void rdstlc(lun, body, solid)
  int    lun;
  Body  *body;
  Solid *solid;
#endif
{
# define   TOLERANCE   0.00015   /* Standard tolerance for STL files. */
  Body    *bdy;
  Corner  *corner;
  Edge    *edge, *edg12, *edg23, *edg31;
  Face    *face;
  Hedge   *hedge, *hed;
  Perim   *perim, *perimL, *perimR;
  Solid   *shape;
  Vertex  *vx0, *vx1, *vx2, *vx3;
  Word     dfault, string;
  char     buffer[MXINBF+1], uprbfr[MXINBF+1];
  int      k, kount, lmerge, merged, nfaces, nogo, nsmall;
  real     d12, d23, d31, edge_length, fcnorm[3], save, size, small,
           v[3], width, x, y, z;

/* Initialize. */
  save   = zrogeo;
  zrogeo = TOLERANCE;         /* Change default tolerance for mkvtxc. */
  solid  = NULL;
  face   = NULL;
  vx1    = NULL;
  vx2    = NULL;
  vx3    = NULL;
  kount  = 0;
  merged = 0;
  nfaces = 0;
  nsmall = 0;
  size   = 0.0;
  small  = 0.0;

/* Read the next record from the file. */
_5:
  if (fgets(buffer, MXINBF+1, streams[lun]) != NULL) {
    buffer[MXINBF] = '\0';
    strcpy(uprbfr, buffer);
    ucasec(uprbfr);
    stripc(uprbfr);

/* Skip an all blank record. */
    if (strlen(uprbfr) == 0) {

/* Read an ENDFACET record and finish this face of the Solid. */
    } else if (strncmp(uprbfr, "ENDFACET", 8) == 0) {
      if (solid) {
        if (face) {
          face->kcolor = kdfgeo;
_2:       edsrtc(face);
          for (perim=face->facPrm; perim; perim=perim->nxtPrm) {
            for (hedge=perim->prmHed; hedge; hedge=hedge->nxtHedPrm) {
              edge = hedge->hedEdg;
              perimL = edge->edgHeL->hedPrm;
              perimR = edge->edgHeR->hedPrm;
              if ((perimL!=NULL)&&(perimR!=NULL)&&(perimL!=perimR)) {
                edge_length = edlngc(edge);
                if (isnanc((void *) &edge_length)) {
                  edge_length = TOLERANCE;
                } else if (edge_length < TOLERANCE) {
                  edge_length = TOLERANCE;
                }
                width = fabs(prmarc(perimR)) / edge_length;
                if (width < TOLERANCE) {
                  merged++;
                  nsmall++;
                  small += width;
                  hed = perimR->prmHed;
                  while (hed->nxtHedPrm) {
                    hed->hedPrm = perimL;
                    hed = hed->nxtHedPrm;
                  }
                  hed->hedPrm = perimL;
                  hed->nxtHedPrm  = perimL->prmHed;
                  perimL->prmHed  = perimR->prmHed;
                  perimL->nhedgs += perimR->nhedgs;
                  xprmc(perimR);
                  face = perimL->prmFac;
                  goto _2;
                }
                vcrosc(perimL->prmFac->faceq, perimR->prmFac->faceq, v);
                if (vabsc(3, v) < TOLERANCE) {
                  lmerge = mrgfac(perimL, perimR);
                  if (lmerge) {
                    merged++;
                    face = perimL->prmFac;
                    goto _2;
                  }
                }
              }
            }
          }
        }
      }

/* Read an ENDLOOP record and create edges and a Perim for this Face. */
    } else if (strncmp(uprbfr, "ENDLOOP", 7) == 0) {
      if (solid) {
        if (face) {
          if ((vx1 != NULL) && (vx2 != NULL) && (vx3 != NULL)) {
            d12 = 0.0;
            d23 = 0.0;
            d31 = 0.0;
            for (k=0; k<3; k++) {
              d12 += pow((vx2->coord[k] - vx1->coord[k]), 2);
              d23 += pow((vx3->coord[k] - vx2->coord[k]), 2);
              d31 += pow((vx1->coord[k] - vx3->coord[k]), 2);
            }
            d12 = sqrt(d12);
            d23 = sqrt(d23);
            d31 = sqrt(d31);
            if ((d12>TOLERANCE) && (d23>TOLERANCE) && (d31>TOLERANCE)) {
              if (perim) {
                corner= mkcnrc(vx1);
                hedge = mkhedc(perim, corner);
                hedge->hedMat = hedge;
                edg12 = mkevc(hedge, hedge,
                        vx2->coord[0], vx2->coord[1], vx2->coord[2]);
                edg23 = mkevc(edg12->edgHeR, edg12->edgHeR,
                        vx3->coord[0], vx3->coord[1], vx3->coord[2]);
                edg31 = mkefc(edg23->edgHeR, edg12->edgHeL);
                face  = edg31->edgHeL->hedPrm->prmFac;
              }
            } else {
              merged++;
              kount++;
              size += min(d12, min(d23, d31));
            }
          }
          vx1 = NULL;
          vx2 = NULL;
          vx3 = NULL;
        }
      }

/* Read the ENDSOLID record and finish the Solid. */
    } else if (strncmp(uprbfr, "ENDSOLID", 8) == 0) {
      if (solid) {
        if (vx0->vtxCnr == NULL) xvtxc(vx0);
        itextc(nfaces);
        textc(" facets were processed.", TRUE);
        if (kount > 0) {
          itextc(kount);
          textc(" facets did not meet edge length tolerance.", TRUE);
          if (size > 0.0) {
            textc("  Average short edge length was ", FALSE);
            gtextc(size/kount);
            textc("", TRUE);
          }
        }
        if (nsmall > 0) {
          itextc(nsmall);
          textc(" facets did not meet width tolerance.", TRUE);
          textc("  Average facet width was ", FALSE);
          gtextc(small/nsmall);
          textc("", TRUE);
        }
        if (merged > 0) {
          itextc(merged);
          textc(" facets were merged.", TRUE);
        }
        waitc();
        cleanc(solid);
      }
      goto _1;

/* Read a FACET NORMAL record and create a new Face for the Solid. */
    } else if (strncmp(uprbfr, "FACET NORMAL", 12) == 0) {
      if (solid) {
        if (face) {
          nfaces++;
          sscanf(&uprbfr[12], "%g %g %g", &fcnorm[0], &fcnorm[1],
            &fcnorm[2]);
          vnormc(3, fcnorm);
          vx1 = NULL;
          vx2 = NULL;
          vx3 = NULL;
        }
      }

/* Read an OUTER LOOP record and create a Perim on the face. */
    } else if (strncmp(uprbfr, "OUTER LOOP", 10) == 0) {
      if (face) perim = mkprmc(face);

/* Read a SOLID record and create a new Solid. */
    } else if (strncmp(uprbfr, "SOLID", 5) == 0) {
      stripc(buffer);
      stripc(&buffer[6]);
      strncpy(dfault, &buffer[6], MAXCHR);
      dfault[MAXCHR] = '\0';
      strcpy(string, dfault);
      if (qiactc()) {
        echoc();
_3:     textc("Enter a name for the solid", FALSE);
        if (lenc(dfault) > 0) {
          textc(" [", FALSE);
          textc(dfault, FALSE);
          textc("]", FALSE);
        }
        textc(": > ", FALSE);
        nogo = bfinc("/");
        if (nogo == 1) goto _3;
        if (nogo == 2) goto _1;
        alprdc(dfault, string);
        if ((string[0] == '/') || (lenc(string) <= 0)) {
          strncpy(string, dfault, MAXCHR);
          string[MAXCHR] = '\0';
        }
        for (bdy=System.sysBdy; bdy; bdy=bdy->nxtBdy) {
          for (shape=bdy->bdySld; shape; shape=shape->nxtSld) {
            if (strcmp(string, shape->name) == 0) {
              echoc();
_4:           textc("Warning: Solid '", FALSE);
              textc(string, FALSE);
              textc("' already exists.  Delete it?  Y/N [N]: > ",
                FALSE);
              nogo = bfinc("n");
              if (nogo == 1) goto _4;
              if (nogo == 2) goto _3;
              alprdc("n", string);
              if ((string[0] != 'Y') && (string[0] != 'y')) goto _3;
              xsldc(shape);
            }
          }
        }
      }
      solid = mksfvc(body, 0.0, 0.0, 0.0);
      strcpy(solid->name, string);
      face = solid->sldFac;
      vx0 = solid->sldVtx;
      vx1 = NULL;
      vx2 = NULL;
      vx3 = NULL;

/* Read a VERTEX record and locate or create a Vertex for the Solid. */
    } else if (strncmp(uprbfr, "VERTEX", 6) == 0) {
      if (solid) {
        sscanf(&uprbfr[6], "%g %g %g", &x, &y, &z);
        vx1 = vx2;
        vx2 = vx3;
        vx3 = mkvtxc(solid, x, y, z);
      }

/* Treat an error in the file format. */
    } else {
      echoc();
      textc("*** Error: The file is not in STL format. ***", TRUE);
      textc(buffer, TRUE);
      waitc();
      if (solid) xsldc(solid);
      solid = NULL;
    }
    goto _5;
  } else if (ferror(streams[lun]) != 0) {
    echoc();
    textc("*** Error in reading STL file. ***", TRUE);
    if (solid) xsldc(solid);
    solid = NULL;
  } else if (feof(streams[lun]) != 0) {
    echoc();
    textc("*** Premature end of STL file. ***", TRUE);
    if (solid) xsldc(solid);
    solid = NULL;
  }
_1:
  zrogeo = save;
  return;
}
