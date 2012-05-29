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
/* dbodyc-01 Jan 00:31 Jul 09
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form and store the transformation matrix from a reference coord-
|     inate system to a coordinate system specified by an origin (pt0),
|     a point on the positive primary joint axis (pt1), and a point on
|     the positive next consecutive axis (pt2).
|
|     Access:
|       (void) dbodyc(Word name, Word ref, Token pt0[3], Token pt1[3], 
|         Token pt2[3]);
|     Word name,i   -Name of the body holding the coordinate system.
|     Word ref,i    -Keyword "body" or the name of the joint.
|     Token pt0[3],i-Array containing coordinate data for pt0.
|     Token pt1[3],i-Array containing coordinate data for pt1.
|     Token pt2[3],i-Array containing coordinate data for pt2.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined body or joint name.
|       System.nerror = 4 indicates inaccurate or faulty data.
|
|     Comments:
|       A warning message is printed when previous data are redefined.
|       System.level <= 1 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     07 May 00:JJU-Removed argument specifying the primary axis.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dbodyc(Word name, Word ref, Token pt0[3], Token pt1[3], 
    Token pt2[3])
#else
  void dbodyc(name, ref, pt0, pt1, pt2)
  Word name, ref;
  Token pt0[3], pt1[3], pt2[3];
#endif
{
  Axes  *axes;
  Body  *body;
  Joint *joint;
  Jvar  *jvar;
  Word   lcref;
  int    i, j, last, naxis, next;
  real   size, xform[3][4], xold[3][4];

/* Locate the body and joint records. */
  joint = NULL;
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strcmp(body->name, name) == 0) {
      strcpy(lcref, ref);
      lcasec(lcref);
      if (strncmp(lcref, "body", MAXCHR) == 0) {
        naxis = 2;
      } else if (strncmp(lcref, "link", MAXCHR) == 0) {
        naxis = 2;
      } else {
        for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
          if (axes->axsJnt) {
            if (strcmp(axes->axsJnt->name, ref) == 0) {
              joint = axes->axsJnt;
              switch (joint->jtype) {
              case XPIN: 
              case XSLIDE:
                naxis = 0;
                break;
              case YPIN:
              case YSLIDE:
                naxis = 1;
                break;
              case RIGID:
              case ZPIN:
              case ZSLIDE:
              case SCREW:
              case GEAR:
              case RACK:
              case BEVEL:
              case CYLINDER:
              case UJOINT:
              case CAM:
              case SLOT:
              case FLAT:
              case PLANE:
              case SPHERE:
              case OPEN:
              default:
                naxis = 2;
              }
              break;
            }
          }
        }
        if (joint == NULL) {
          echoc();
          textc("*** There is no joint named ", FALSE);
          textc(ref, FALSE);
          textc(" on body ", FALSE);
          textc(name, FALSE);
          textc(". ***", TRUE);
          System.nerror = 3;
          goto _DONE;
        }
      }

/* Form the new transformation matrix. */
      next = (naxis + 1) % 3;
      last = (next  + 1) % 3;
      size = 0.0;
      for (i=0; i<3; i++) {
        xform[i][    3] = pt0[i].data.word;
        xform[i][naxis] = pt1[i].data.word - pt0[i].data.word;
        xform[i][ next] = pt2[i].data.word - pt0[i].data.word;
        size += xform[i][naxis] * xform[i][naxis];
      }
      size = sqrt(size);
      if (size > System.dtoll) {
        for (i=0; i<3; i++) {
          xform[i][naxis] /= size;
        }
        size = 0.0;
        for (i=0; i<3; i++) {
          xform[i][last] = xform[(i+1)%3][naxis] * xform[(i+2)%3][next]
                         - xform[(i+2)%3][naxis] * xform[(i+1)%3][next];
          size += xform[i][last] * xform[i][last];
        }
      } else {
        goto _ERROR;
      }
      size = sqrt(size);
      if (size > System.dtoll) {
        for (i=0; i<3; i++) {
          xform[i][last] /= size;
        }
        size = 0.0;
        for (i=0; i<3; i++) {
          xform[i][next] = xform[(i+1)%3][last] * xform[(i+2)%3][naxis]
                         - xform[(i+2)%3][last] * xform[(i+1)%3][naxis];
          size += xform[i][next] * xform[i][next];
        }
      } else {
        goto _ERROR;
      }
      if (size > System.dtoll) {
        for (i=0; i<3; i++) {
          xform[i][next] /= size;
        }
      } else {
        goto _ERROR;
      }

/* Treat the position of a set of joint axes. */
      if (joint) {
        invxc(body->T0j, xold);
        mpyxxc(xold, xform, axes->S);
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          ldnanc((void *) &(jvar->design));
        }

/* Treat the absolute position of a body. */
      } else {
        for (i=0; i<3; i++) {
          for (j=0; j<4; j++) {
            xold[i][j]      = body->T0j[i][j];
            body->T0j[i][j] = xform[i][j];
          }
        }
        invxc(xform, xform);
        mpyxxc(xform, xold, xform);
        for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
          mpyxxc(xform, axes->S, axes->S);
          if (axes->axsJnt) {
            for (jvar=axes->axsJnt->jntJvr; jvar; jvar=jvar->nxtJvr) {
              ldnanc((void *) &(jvar->design));
            }
          }
        }
      }
      goto _DONE;
    }
  }
  echoc();
  textc("*** There is no body named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  goto _DONE;

_ERROR:
  echoc();
  textc("*** Data for body ", FALSE);
  textc(name, FALSE);
  if (joint) {
    textc(" at ", FALSE);
    textc(ref, FALSE);
  }
  textc(" is in error. ***", TRUE);
  System.nerror = 4;
_DONE:;
  return;
}
