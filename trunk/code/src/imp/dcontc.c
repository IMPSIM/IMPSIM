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
/* dcontc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Supply data for properties of a specified Contact.
|
|     Access:
|       (void) dcontc(Word cntname, real en, real et, real em, real emn,
|         real mu);
|     Word cntname,i-Name of the Contact for this data.
|     real en,     i-Coefficient of restitution in normal direction.
|     real et,     i-Coefficient of restitution in tangent direction.
|     real em,     i-Coefficient of restitution in binormal direction.
|     real emn,    i-Coefficient of restitution in torsion.
|     real mu,     i-Coefficient of Coulomb friction.
|
|     Error Conditions:
|       System.nerror = 3 indicates an undefined Contact name.  A
|     message is printed but no data is stored.
|
|     Comments:
|       Any previously defined data for this Contact is replaced; no
|     message is printed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dcontc(Word cntname, real en, real et, real em, real emn,
    real mu)
#else
  void dcontc(cntname, en, et, em, emn, mu)
  Word cntname;
  real en, et, em, emn, mu
#endif
{
  Contact *contact;

/* Locate the Contact record. */
  for (contact=System.sysCnt; contact; contact=contact->nxtCnt) {
    if (strcmp(contact->name, cntname) == 0) {
      contact->rest_n  = en;
      contact->rest_t  = et;
      contact->rest_m  = em;
      contact->rest_mn = emn;
      contact->mu      = mu;
      goto DONE;
    }
  }
  echoc();
  textc("*** There is no Contact named '", FALSE);
  textc(cntname, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
DONE:
  return;
}
