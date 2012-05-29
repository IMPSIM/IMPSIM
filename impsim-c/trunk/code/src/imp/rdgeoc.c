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
/* rdgeoc-01 Jan 00:29 Jul 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       This routine reads and stores solid geometry information from a
|     file previously written in JJU format.
|
|     Access:
|       (void) rdgeoc(int lun, Body *body, Solid *solid, char *datime);
|     int    lun,   i-Logical unit number for reading the file.
|     Body  *body,  i-Pointer to the Body record for the Solid read.
|     Solid *solid, o-Pointer to the Solid record created.
|     char  *datime,o-Date time character string for file storage.
|
|     Error Conditions:
|       If the file is not already opened, or if the file is not in JJU
|     standard 3DS or 2DS format, an error message is printed and exit
|     is made with no new Solid stored.
|
|     Comments:
|       It is assumed that a file has been previously written in JJU
|     format, and that the file has been succesfully opened and assigned
|     to FILE *streams[lun] before entry.
|       Upon successful completion, one or more new Solid records with
|     attendant Axes, and Points is formed and named.  No attempt is
|     made to check for or resolve duplication of names.
|       If *body does not point to a valid Body, the new Solid is made
|     an orphan and is pointed to by System.sysSld.
|       The data structure stored is based on the half-edge structure
|     described in "An Introduction to Solid Modeling", 1988, by Martti
|     Mantyla.  The structure is modified to handle non-manifold solids
|     by the use of Corners, Perimeters, and Halfedge pairs.
*
*     History:
*     01 Jan 00:JJU-Original.
*     06 Jul 03:JJU-datime string set to 20 chars for 20xx dates.
*     12 Feb 04:JJU-Release 5 is started. 
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void rdgeoc(int lun, Body *body, Solid *solid, char *datime)
#else
  void rdgeoc(lun, body, solid, datime)
  int    lun;
  Body  *body;
  Solid *solid;
  char  *datime;
#endif
{
  Axes    *axes, *axs;
  Corner **cnrtbl, *corner;
  Edge   **edgtbl, *edge;
  enum Dimtyp ndimen;
  Face    *face;
  Hedge  **hedlst, *hedge;
  Perim   *perim;
  Point   *pnt, *point;
  Vertex  *vtx;
  Word    name;
  char    buffer[MXINBF+2], form[4];
  int     i, ireleas, j, k, lflag, naxes, ncnrs, nedges, nfaces, nheds,
            nprms, npnts, nslds, nvtxs;
  real    T0j[3][4], tolrnc, x3max, x3min, y3max, y3min, z3max, z3min;

/* Initialize. */
  ndimen = UNKNOWN;
  lflag  = TRUE;
  solid  = NULL;
  hedlst = NULL;
  edgtbl = NULL;
  cnrtbl = NULL;
  datime  = "";

/* Check the file format. */
  if (fgets(buffer, MXINBF+2, streams[lun])) {        /* Read line 1. */
    buffer[MXINBF] = '\0';
    if (lenc(buffer) > 0) { /* For JJU format line 1 should be blank. */
      echoc();
      textc("*** Error: File is not in JJU format. ***", TRUE);
      goto _DONE;
    } else {
      if (fgets(buffer, MXINBF+2, streams[lun])) {    /* Read line 2. */
        buffer[MXINBF] = '\0';
        sscanf(&buffer[21], "%7d", &ireleas);  /* Get release number. */
        strncpy(form, &buffer[18], 3);         /* Get dimensionality. */
        form[3] = '\0';
        if (((strcmp(form, "3DS") == 0) || (strcmp(form, "2DS") == 0))
          && (ireleas >= 2)) {
          if (strcmp(form, "2DS") == 0) {
            ndimen = PLANAR;
          } else {
            ndimen = SPATIAL;
          }
          if (ireleas < 3) {                         /* Release <= 2. */
            tolrnc = zrogeo;
            ldnanc((void *) &x3min);
            ldnanc((void *) &y3min);
            ldnanc((void *) &z3min);
            ldnanc((void *) &x3max);
            ldnanc((void *) &y3max);
            ldnanc((void *) &z3max);
          } else {                                   /* Release >= 3. */
            strncpy(datime, &buffer[32], 20);   /* Get date and time. */
            datime[20] = '\0';

            if (fgets(buffer, MXINBF+2, streams[lun])){/*Read line 3. */
              buffer[MXINBF] = '\0';
              stripc(buffer);
              buffer[lenc(buffer)] = '\0';
              ldttlc(buffer);                   /* Store scene title. */
            } else {
              goto _ERROR;
            }
            if (fgets(buffer, MXINBF+2, streams[lun])) {/*Read line 4.*/
              buffer[MXINBF] = '\0';
#             ifdef DOUBLE_PREC           /* Get geometric precision. */
                sscanf(buffer, "%lf", &tolrnc);
#             else
                sscanf(buffer, "%f",  &tolrnc);
#             endif
            } else {
              goto _ERROR;
            }
            if (fgets(buffer, MXINBF+2, streams[lun])){/*Read line 5. */
              buffer[MXINBF] = '\0';
#             ifdef DOUBLE_PREC           /* Get bounding box limits. */
                sscanf(buffer, "%lf%lf%lf%lf", &x3min, &y3min, &z3min,
#             else
                sscanf(buffer, "%f%f%f%f",     &x3min, &y3min, &z3min,
#             endif
                  &x3max);
            } else {
              goto _ERROR;
            }
            if (fgets(buffer, MXINBF+2, streams[lun])){/*Read line 6. */
              buffer[MXINBF] = '\0';
#             ifdef DOUBLE_PREC
                sscanf(buffer, "%lf%lf", &y3max, &z3max);
#             else
                sscanf(buffer, "%f%f",   &y3max, &z3max);
#             endif
            } else {
              goto _ERROR;
            }
          }

/* Look for T0j transform to signal a new Shape in the file. */
_BODY:    if (ireleas < 3) { /* T0j was not in file before release 3. */
            for (i=0; i<3; i++) {
              for (j=0; j<4; j++) {
                T0j[i][j] = 0.0; 
              }
              T0j[i][i] = 1.0;
            }
            nslds   = 1;   /* Only one Solid in file until release 5. */
            name[0] = '\0';   /*No Body name in file until release 3. */
            naxes   = 0; /*No Axes or Points in file until release 3. */
            npnts   = 0;
          } else {                             /* Release 3 or later. */
            for (i=0; i<3; i++) {
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0'; /* Get xf for body wrt global. */
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf%lf%lf%lf", &T0j[i][0], &T0j[i][1],
#               else
                  sscanf(buffer, "%f%f%f%f",     &T0j[i][0], &T0j[i][1],
#               endif
                    &T0j[i][2], &T0j[i][3]);
              } else {
                goto _DONE;                         /* File finished. */
              }
            }
            if (fgets(buffer, MXINBF+2, streams[lun])) {
              buffer[MXINBF] = '\0';
              if (ireleas < 5) {                   /* Release 3 or 4. */
                stripc(buffer);
                buffer[MAXCHR] = '\0';   /* Trim buffer to Word size. */
                buffer[lenc(buffer)] = '\0';
                strcpy(name, buffer);   /* Save as name of this Body. */
                nslds = 1; /* Only one Solid in earlier file formats. */
              } else {                         /* Release 5 or later. */
                sscanf(buffer, "%8s%d%d%d", &name, &nslds, &naxes,
                  &npnts);   /* Get name, no of Solids, Axes, Points. */
                stripc(name);
                name[lenc(name)] = '\0';
              }
            } else {
              goto _ERROR;
            }
          }
          if (body) {
            for (i=0; i<3; i++) {
              for (j=0; j<4; j++) {
                body->T0j[i][j] = T0j[i][j]; 
              }
            }
          }

/* Create a new Solid. */
_SOLID:   free(hedlst);
          free(edgtbl);
          free(cnrtbl);
          hedlst = NULL;
          edgtbl = NULL;
          cnrtbl = NULL;
          solid = mksldc(body);
          if (fgets(buffer, MXINBF+2, streams[lun])) {
            if (ireleas < 3) {
              solid->name[0]='\0';  /* No Solid name up to release 3. */
              strcpy(solid->name, name);  /* Store name of the solid. */
              buffer[MXINBF] = '\0';
              sscanf(buffer, "%d%d%d", &nfaces, &nedges, &nvtxs);
              nprms = nfaces;
              nheds = 2 * nedges;
              ncnrs = nvtxs;
            } else if (ireleas < 5) {              /* Release 3 or 4. */
              buffer[MXINBF] = '\0';
              strcpy(solid->name, name);  /* Store name of the solid. */
              sscanf(buffer, "%d%d%d%d%d", &nfaces, &nedges, &nvtxs,
                &naxes, &npnts);
              nprms = nfaces;
              nheds = 2 * nedges;
              ncnrs = nvtxs;
            } else {                           /* Release 5 or later. */
              buffer[MXINBF] = '\0';
              sscanf(buffer, "%8s%d%d%d%d%d%d%d", &solid->name,
                &ndimen, &nfaces, &nprms, &nheds, &nedges, &ncnrs,
                &nvtxs);
            }
            solid->kdimen = ndimen;          /* Store dimensionality. */
          } else {
            goto _ERROR;
          }
          if (ireleas < 4) {                      /* Up to release 3. */
            ldnanc((void *) &solid->area);  /* Release <= 3 had no    */
            ldnanc((void *) &solid->volume);/* area or volume stored. */
            for (i=0; i<6; i++) ldnanc((void *) &solid->screw[i]);
          } else if (ireleas < 5) {                     /* Release 4. */
            if (fgets(buffer, MXINBF+2, streams[lun])) {
              buffer[MXINBF] = '\0';
#             ifdef DOUBLE_PREC
                sscanf(buffer, "%lf%lf", &solid->volume, &solid->area);
#             else
                sscanf(buffer, "%f%f",   &solid->volume, &solid->area);
#             endif
              if (solid->area  < zrogeo) ldnanc((void *) &solid->area);
              if (solid->volume< zrogeo) ldnanc((void *)&solid->volume);
            } else {
              goto _ERROR;
            }
            if (fgets(buffer, MXINBF+2, streams[lun])) {
              buffer[MXINBF] = '\0';/* Read and ignore row of zeroes. */
            } else {
              goto _ERROR;
            }
            for (i=0; i<6; i++) ldnanc((void *) &solid->screw[i]);
          } else {                             /* Release 5 or later. */
            if (fgets(buffer, MXINBF+2, streams[lun])) {
              buffer[MXINBF] = '\0';
#             ifdef DOUBLE_PREC
                sscanf(buffer, "%lf%lf%lf%lf", &solid->volume,
#             else
                sscanf(buffer, "%f%f%f%f",     &solid->volume,
#             endif
                  &solid->area, &solid->screw[0], &solid->screw[1]);
              if (solid->area  < zrogeo) ldnanc((void *) &solid->area);
              if (solid->volume< zrogeo) ldnanc((void *)&solid->volume);
            } else {
              goto _ERROR;
            }
            if (fgets(buffer, MXINBF+2, streams[lun])) {
              buffer[MXINBF] = '\0';
#             ifdef DOUBLE_PREC
                sscanf(buffer, "%lf%lf%lf%lf", &solid->screw[2],
#             else
                sscanf(buffer, "%f%f%f%f",     &solid->screw[2],
#             endif
                  &solid->screw[3], &solid->screw[4], &solid->screw[5]);
            } else {
              goto _ERROR;
            }
          }

/* Aquire working space for Perim, Edge, and Corner pointer tables. */
          hedlst = (Hedge  **) calloc(nedges, sizeof(Hedge  *));
          edgtbl = (Edge   **) calloc(nedges, sizeof(Edge   *));
          cnrtbl = (Corner **) calloc(ncnrs,  sizeof(Corner *));

/* Create the Solid's Face and Perim records. */
          for (i=0; i<nfaces; i++) {
            face  = mkfac(solid);
            perim = mkprmc(face);
          }

/* Create the Solid's Edge and Hedge records. */
          for (i=0; i<nedges; i++) {
            edge  = mkedgc(solid);
            edgtbl[i] = edge;
            hedge = ldhedc(edge);
            edge->edgHeL = hedge;
            hedge = ldhedc(edge);
            edge->edgHeR = hedge;
            edge->edgHeR->hedMat = edge->edgHeL;
            edge->edgHeL->hedMat = edge->edgHeR;
          }

/* Create the Solid's Vertex and Corner records. */
          for (i=0; i<nvtxs; i++) {
            vtx = mkvtxc(solid, (real) i*PI, 0.0, 0.0);/* *** Use 
                  unique data to assure distinct Vertex creation. *** */
            cnrtbl[i] = mkcnrc(vtx);
          }

/* Read and store the Solid's Face information. */
          for (face=solid->sldFac; face; face=face->nxtFac) {
            if (ireleas <= 3) {                   /* Up to release 3. */
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf%lf%lf%lf%d",  &face->faceq[0],
#               else
                  sscanf(buffer, "%f%f%f%f%d",      &face->faceq[0],
#               endif
                    &face->faceq[1], &face->faceq[2], &face->faceq[3],
                    &face->kcolor);
              } else {
                goto _ERROR;
              }
              if (fscanf(streams[lun], "%d", &nheds) != 1) goto _ERROR;
              nprms = 1;
            } else if (ireleas == 4) {                  /* Release 4. */
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf%lf%lf%lf", &face->faceq[0],
#               else
                  sscanf(buffer, "%f%f%f%f",     &face->faceq[0],
#               endif
                    &face->faceq[1], &face->faceq[2], &face->faceq[3]);
              } else {
                goto _ERROR;
              }
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
                sscanf(buffer, "%d%d%d", &nheds, &face->facno,
                  &face->kcolor);
              } else {
                goto _ERROR;
              }
              nprms = 1;
            } else {                          /* Release 5 and later. */
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf%lf%lf%lf", &face->faceq[0],
#               else
                  sscanf(buffer, "%f%f%f%f",     &face->faceq[0],
#               endif
                    &face->faceq[1], &face->faceq[2], &face->faceq[3]);
              } else {
                goto _ERROR;
              }
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
                sscanf(buffer, "%d%d%d", &face->facno, &nprms,
                  &face->kcolor);
              } else {
                goto _ERROR;
              }
              if (fscanf(streams[lun], "%d", &nheds) != 1)goto _ERROR;
            }

/* Read and save this Face's (Perim's) Hedge information. */
            for (k=0; k<nheds; k++) {
              if (fscanf(streams[lun], "%d", &j) != 1) goto _ERROR;
              if (j > 0) {
                hedlst[k] = edgtbl[j-1]->edgHeL;
              } else {
                hedlst[k] = edgtbl[-j-1]->edgHeR;
              }
            }  /* Don't forget to read End of Record on streams[lun]. */
            if (fgets(buffer, MXINBF+1, streams[lun])) {
              buffer[MXINBF] = '\0';
            } else {
              goto _ERROR;
            }
            perim = face->facPrm;
            for (k=nheds-1; k>=0; k--) {
              hedge = hedlst[k];
              ringac(perim, hedge, perim->prmHed);
            }
            perim->nhedgs = nheds;
            if (ireleas >= 4) {/*Read and store the Face coefficient. */
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf", &face->coeff);
#               else
                  sscanf(buffer, "%f",  &face->coeff);
#               endif
              } else {
                goto _ERROR;
              }
            }
          }

/* Read and store the Solid's Edge connections. */
          for (i=0; i<nedges; i++) {
            if (fgets(buffer, MXINBF+2, streams[lun])) {
              buffer[MXINBF] = '\0';
              edge = edgtbl[i];
              sscanf(buffer, "%d%d", &j, &k);
              corner = cnrtbl[j-1];
              edge->edgHeL->hedCnr = corner;
/*            edge->edgHeL->nxtHedPrm->hedEdg =
                corner->cnrHed->hedEdg;*/  /* ?? What does this do ?? */
              corner->cnrHed->hedEdg = edge;
              corner = cnrtbl[k-1];
              edge->edgHeR->hedCnr = corner;
/*            edge->edgHeR->nxtHedCnr->hedEdg =
                corner->cnrHed->hedEdg;*/  /* ?? What does this do ?? */
              corner->cnrHed->hedEdg = edge;
            } else {
              goto _ERROR;
            }
            if (ireleas >= 4) {/*Read and store the Edge coefficient. */
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf", &edge->coeff);
#               else
                  sscanf(buffer, "%f",  &edge->coeff);
#               endif
              } else {
                goto _ERROR;
              }
            }
          }

/* Read and store the Solid's Vertex coordinate data. */
          for (i=0; i<nvtxs; i++) {
            if (fgets(buffer, MXINBF+2, streams[lun])) {
              vtx = cnrtbl[i]->cnrVtx;
              buffer[MXINBF] = '\0';
#             ifdef DOUBLE_PREC
                sscanf(buffer, "%lf%lf%lf", &vtx->coord[0],
#             else
                sscanf(buffer, "%f%f%f",    &vtx->coord[0],
#             endif
                  &vtx->coord[1], &vtx->coord[2]);
            } else {
              goto _ERROR;
            }
            if (ireleas >= 4) { /* Read and store Vertex coefficient. */
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf", &vtx->coeff);
#               else
                  sscanf(buffer, "%f",  &vtx->coeff);
#               endif
              } else {
                goto _ERROR;
              }
            }
          }

/* Complete the geometric data for all faces of the Solid. */
          for (face=solid->sldFac; face; face=face->nxtFac) {
            fcnrmc(face);
          }
/*        cleanc(solid);*/

/* Cycle back to read the next Solid as needed. */
          if (body) {
            if (body->nslds < nslds) goto _SOLID;

/* Read and store the Body's Axes information. */
            for (i=0; i<naxes; i++) {
              axes = (Axes *) malloc(sizeof(Axes));
              axes->type   = AXES;
              axes->nxtAxs = NULL;
              if (body->bdyAxs) {  /* Add Axes to end of linked list. */
                axs = body->bdyAxs;
                while (axs->nxtAxs) axs = axs->nxtAxs;
                axs->nxtAxs = axes;
              } else {
                body->bdyAxs = axes;
              }
              axes->axsBdy = body;
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
                stripc(buffer);
                buffer[MAXCHR] = '\0';          /* Trim to Word size. */
                buffer[lenc(buffer)] = '\0';      /* Truncate spaces. */
                strcpy(axes->name, buffer);
              } else {
                goto _ERROR;
              }
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
                sscanf(buffer, "%d", &axes->kcolor);
              } else {
                goto _ERROR;
              }
              for (j=0; j<3; j++) {
                if (fgets(buffer, MXINBF+2, streams[lun])) {
                  buffer[MXINBF] = '\0';
#                 ifdef DOUBLE_PREC
                    sscanf(buffer, "%lf%lf%lf%lf",  &axes->S[j][0],
#                 else
                    sscanf(buffer, "%f%f%f%f",      &axes->S[j][0],
#                 endif
                      &axes->S[j][1], &axes->S[j][2], &axes->S[j][3]);
                } else {
                  goto _ERROR;
                }
              }
            }

/* Read and store the Body's Point information. */
            for (i=0; i<npnts; i++) {
              point = (Point *) malloc(sizeof(Point));
              point->type = POINT;
              point->nxtPnt = NULL;
              if (body->bdyPnt) {/* Add Points to end of linked list. */
                pnt = body->bdyPnt;
                while (pnt->nxtPnt) pnt = pnt->nxtPnt;
                pnt->nxtPnt = point;
              } else {
                body->bdyPnt = point;
              }
              point->pntBdy = body;
              point->master = TRUE;
              point->local  = FALSE;
              if (i == 0) {
                point->kcolor = -kdfgeo;
              } else {
                point->kcolor =  kdfgeo;
              }
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
                stripc(buffer);
                buffer[MAXCHR] = '\0';          /* Trim to Word size. */
                buffer[lenc(buffer)] = '\0';      /* Truncate spaces. */
                strcpy(point->name, buffer);  /* Save name for point. */
              } else {
                goto _ERROR;
              }
              if (fgets(buffer, MXINBF+2, streams[lun])) {
                buffer[MXINBF] = '\0';
#               ifdef DOUBLE_PREC
                  sscanf(buffer, "%lf%lf%lf", &point->coord[0],
#               else
                  sscanf(buffer, "%f%f%f",    &point->coord[0],
#               endif
                    &point->coord[1], &point->coord[2]);
                point->coord[3] = 1.0;
              } else {
                goto _ERROR;
              }
            }
          }
          echoc();
          textc("Solid '", FALSE);
          textc(solid->name, FALSE);
          if (body) {
            textc("' of Body '", FALSE);
            textc(body->name, FALSE);
          }
          textc("' was read from file.", TRUE);
          if (lflag && (ireleas < 5)) {
            echoc();
            textc("Warning: This file is in an out of date format.",
              TRUE);
            textc("Please store shapes again and discard old file.",
              TRUE);
            waitc();
            lflag = FALSE;
          }
          if (ireleas >= 3) goto _BODY;      /* Look for another Body.*/
        } else {

/* Treat an error in the file format. */
          echoc();
          textc("*** Error: File is not in JJU format. ***", TRUE);
        }
        goto _DONE;
      }
    }
  }
_ERROR:
  echoc();
  textc("*** Error in reading file. ***", TRUE);
_DONE:
  free(hedlst);
  free(edgtbl);
  free(cnrtbl);
  fclose (streams[lun]);
  return;
}
