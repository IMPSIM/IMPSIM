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
/* wrtfnc-01 Jan 00:02 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Print the requested transfer functions versus frequency.
|
|     Access:
|       (void) wrtfnc(complex Tnumr[], real wr[], real wi[], 
|         Word kindin, Word namein, int nin, Token names[], int ntkns);
|     complex Tnumr[3,nfgc,2*nfgc],i-The transfer function numerators.
|     real    wr[2*nfgc],          i-Real parts of system eigenvalues.
|     real    wi[2*nfgc],          i-Imaginary parts of eigenvalues.
|     Word    kindin,              i-Type of input, 'forc' or 'moti'.
|     Word    namein,              i-Name of the input force or joint.
|     int     nin,                 i-Component number of namein input.
|     Token   names[2*n],          i-Types and names of listings sought.
|     int     ntkns,               i-Number of tokens, 2*n.
|
|     Error Conditions:
|       If no joint or force with the specified name is found, no 
|     listing is produced; a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     22 Mar 03:JJU-Implemented with itextc and ftextc functions.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void wrtfnc(complex Tnumr[], real wr[], real wi[], Word kindin, 
    Word namein, int nin, Token names[], int ntkns)
#else
  void wrtfnc(Tnumr, wr, wi, kindin, namein, nin, names, ntkns)
  complex Tnumr[];
  real    wr[], wi[];
  Word    kindin, namein;
  int     nin, ntkns;
  Token   names[];
#endif
{
  complex *Tfn;
  int     i, iadres, j, k, last, loc, lprint, nexp, nfgc, n2;
  real    cons[6], zero;
  Word    kind, name, type;

/* Initialize. */
  nfgc = System.nfgc;
  n2   = nfgc + nfgc;
  zero = System.zero;
  Tfn  = (complex *) calloc(36*nfgc, sizeof(complex));

/* Sequence through the requested output listings. */
  for (i=0; i<ntkns; i=i+2) {

/* Determine the type of response requested. */
    if (names[i].kind != TK_CHAR) continue;
    strncpy(type, names[i].data.text, MAXCHR);
    lcasec(type);
    if (strncmp(type, "position", MAXCHR) == 0) {
      strncpy(type, "Pos.", MAXCHR);
      nexp = 0;
    } else if (strncmp(type, "velocity", MAXCHR) == 0) {
      strncpy(type, "Vel.", MAXCHR);
      nexp = 1;
    } else if (strncmp(type, "acceleration", MAXCHR) == 0) {
      strncpy(type, "Acc.", MAXCHR);
      nexp = 2;
    } else {
      textc("*** '", FALSE);
      textc(names[i].data.text, FALSE);
      textc((char *)SPACE, FALSE);
      textc(names[i+1].data.text, FALSE);
      textc("' is not defined. ***", TRUE);
      continue;
    }

/* Get the item name; sequence through names for name == 'all'. */
    if (names[i+1].kind != TK_CHAR) continue;
    strncpy(name, names[i+1].data.text, MAXCHR);
    lcasec(name);
    if (strncmp(name, "all", MAXCHR) == 0) {
    } else {
      strncpy(name, names[i+1].data.text, MAXCHR);

/* Form the transfer function for this item. */
      tformc(Tnumr, name, nexp, kind, &last, cons, Tfn);
      if (System.nerror) {
        textc("*** ", FALSE);
        textc(name, FALSE);
        textc("' ignored. ***", TRUE);
        System.nerror = 0;
        continue;
      }
      if (last <= 0) continue;

/* Print the transfer function for this item. */
      loc = 0;
      for (j=0; j<last; j++) {
        textc("",     TRUE);
        textc(type,   FALSE);
        textc(" response of ", FALSE);
        textc(kind,   FALSE);
        textc(" ",    FALSE);
        textc(name,   FALSE);
        textc(",",    FALSE);
        itextc(j);
        textc(" to ", FALSE);
        textc(kindin, FALSE);
        textc(" in ", FALSE);
        textc(namein, FALSE);
        textc(",",    FALSE);
        itextc(nin);
        textc(" = ", FALSE);
        ftextc(cons[j]);
        textc("", TRUE);

/* Loop through the modes. */
        for (k=0; k<n2; k++) {

/* Print the numerator. */
          iadres = loc + k;
          lprint = FALSE;
          if (cabsc(Tfn[iadres]) > zero) {
            lprint = TRUE;
            textc("  +(", FALSE);
            if (abs(Tfn[iadres].r) > zero) {
              ftextc(Tfn[iadres].r);
            }
            if (abs(Tfn[iadres].i) > zero) {
              textc("+", FALSE);
              ftextc(Tfn[iadres].i);
              textc("j", FALSE);
            }
            textc(")", FALSE);
            if (nexp > 0) {
              textc("S", FALSE);
              if (nexp > 1) {
                textc("^", FALSE);
                itextc(nexp);
              }
            }
          }
          iadres += 6 * n2;
          if (cabsc(Tfn[iadres]) > zero) {
            lprint = TRUE;
            textc("+(", FALSE);
            if (abs(Tfn[iadres].r) > zero) {
              ftextc(Tfn[iadres].r);
            }
            if (abs(Tfn[iadres].i) > zero) {
              textc("+", FALSE);
              ftextc(Tfn[iadres].i);
              textc("j", FALSE);
            }
            textc(")", FALSE);
            if (nexp > 0) {
              textc("S", FALSE);
              if (nexp > 1) {
                textc("^", FALSE);
                itextc(nexp);
              }
            }
          }
          iadres += 6 * n2;
          if (cabsc(Tfn[iadres]) > zero) {
            lprint = TRUE;
            textc("+(", FALSE);
            if (abs(Tfn[iadres].r) > zero) {
              ftextc(Tfn[iadres].r);
            }
            if (abs(Tfn[iadres].i) > zero) {
              textc("+", FALSE);
              ftextc(Tfn[iadres].i);
              textc("j", FALSE);
            }
            textc(")", FALSE);
            if (nexp > 0) {
              textc("S", FALSE);
              if (nexp > 1) {
                textc("^", FALSE);
                itextc(nexp);
              }
            }
          }

/* Print the denominator. */
          if (lprint) {
            textc("/(s", FALSE);
            if ((abs(wr[k]) > zero) || (abs(wi[k]) > zero)) {
              if (abs(wr[k]) > zero) {
                ftextc(-wr[k]);
              }
              if (abs(wi[k]) > zero) {
                textc("+", FALSE);
                ftextc(-wi[k]);
                textc("j", FALSE);
              }
            }
            textc(")", TRUE);
          }
        }
        loc += n2;
      }
    }
  }
  free (Tfn);
  return;
}
