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
/* dmassc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Store the mass and center of mass location of a specified body.
|
|     Access:
|       (void) dmassc(Word name, Word ref, real m, Token rbar[3]);
|     Word name,i-Name of the body for the mass to be set.
|     Word ref, i-Name of the reference coordinate system for rbar data.
|     real m,   i-Mass of the named body.
|     Token rbar[3],i-Center of mass coordinates with respect to ref.
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
  void dmassc(Word name, Word ref, real m, Token rbar[3])
#else
  void dmassc(name, ref, m, rbar)
  Word name, ref;
  real m;
  Token rbar[3];
#endif
{
  Axes  *axes;
  Body  *body;
  Joint *joint;
  Mass  *mass;
  Word   bdyref;
  int    i, j, k;
  real   vector[3];

  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strcmp(body->name, name) == 0) {
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
      if (m < System.zero) {
        echoc();
        textc("*** Mass must be greater than zero. ***", TRUE);
        System.nerror = 4;
        return;
      }
      if (body->bdyMas) {
        echoc();
        textc("*** Previous mass data for body ", FALSE);
        textc(name, FALSE);
        textc(" are redefined. ***", TRUE);
        free(body->bdyMas);
      }
      mass = (Mass *) malloc(sizeof(Mass));
      mass->type = MASS;
      mass->masBdy = body;
      body->bdyMas = mass;
      for (i=0; i<3; i++) {
        vector[i] = rbar[i].data.word;
      }
      if (joint) mpyxvc(axes->S, vector, vector);
      mass->I[9] = m * System.gc;
      k = 0;
      for (i=0; i<3; i++) {
        mass->I[i+6] = mass->I[9] * vector[i];
        for (j=0; j<=i; j++) {
          mass->I[k] = mass->I[i+6] * vector[j];
          k++;
        }
      }
      if (System.level > 3) System.level = 3;
      return;
    }
  }
  echoc();
  textc("*** There is no body named '", FALSE);
  textc(name, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
  return;
}
