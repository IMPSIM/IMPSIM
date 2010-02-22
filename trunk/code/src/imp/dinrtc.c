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
/* dinrtc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Store the mass moments and products of inertia of a specified
|     body.
|
|     Access:
|       (void) dinrtc(Word name, Word ref, real Ixx, real Iyy, real Izz,
|         real Ixy, real, Iyz, real Izx);
|     Word name,i-Name of the body for the inertias to be set.
|     Word ref,i-Name of the reference coordinate system for the data.
|     real Ixx,Iyy,Izz,i-Mass moments  of inertia of the named body.
|     real Ixy,Iyz,Izx,i-Mass products of inertia of the named body.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined body or joint name.
|       System.nerror = 4 indicates missing or faulty data.
|
|     Comments:
|       A warning message is printed when previous data are redefined.
|       System.level <= 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dinrtc(Word name, Word ref, real Ixx, real Iyy, real Izz,
    real Ixy, real Iyz, real Izx)
#else
  void dinrtc(name, ref, Ixx, Iyy, Izz, Ixy, Iyz, Izx)
  Word name, ref;
  real Ixx, Iyy, Izz, Ixy, Iyz, Izx;
#endif
{
  Axes  *axes;
  Body  *body;
  Joint *joint;
  Mass  *mass;
  Word   bdyref;
  int    i;
  real   Sinv[3][4], sum, tensor[4][4], vector[10];

  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strcmp(body->name, name) == 0) {
      if (body->bdyMas) {
        mass = body->bdyMas;
      } else {
        echoc();
        textc("*** DATA:MASS statement is missing for body ", FALSE);
        textc(name, FALSE);
        textc(". ***", TRUE);
        System.nerror = 4;
        return;
      }
      joint = NULL;
      strcpy(bdyref, ref);
      lcasec(bdyref);
      if (strncmp(bdyref, "body", MAXCHR) == 0) {
      } else {
        for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
          if (axes->axsJnt) {
            if (strcmp(axes->axsJnt->name, ref) == 0) {
              joint = axes->axsJnt;
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
          return;
        }
      }
      if ((Ixx < 0.0) || (Iyy < 0.0) || (Izz < 0.0)) {
        echoc();
        textc("*** Negative moment of inertia is meaningless. ***",
          TRUE);
        System.nerror = 4;
        return;
      } else {
        sum = 0.5 * (Ixx + Iyy + Izz);
        vector[0] = sum - Ixx;
        vector[1] = Ixy;
        vector[2] = sum - Iyy;
        vector[3] = Izx;
        vector[4] = Iyz;
        vector[5] = sum - Izz;
        for (i=0; i<6; i++) {
          vector[i] *= System.gc;           /* Convert to mass units. */
        }
        for (i=6; i<10; i++) {
          vector[i] = mass->I[i]; /* May not be in consistent coords! */
        }
        if (joint) {
          invxc(axes->S, Sinv);
          mpyxvc(Sinv, &vector[6], &vector[6]); /* Temp joint coords. */
          xjxtrc(axes->S, vector, tensor);    /* Back in body coords. */
          vector[0] = tensor[0][0];
          vector[1] = tensor[1][0];
          vector[2] = tensor[1][1];
          vector[3] = tensor[2][0];
          vector[4] = tensor[2][1];
          vector[5] = tensor[2][2];
          vector[6] = tensor[3][0];
          vector[7] = tensor[3][1];
          vector[8] = tensor[3][2];
          vector[9] = tensor[3][3];
        }
        for (i=0; i<10; i++) {
          mass->I[i] = vector[i];
        }
        if (System.level > 3) System.level = 3;
        return;
      }
    }
  }
  echoc();
  textc("*** There is no body named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
