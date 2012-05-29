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
/* lstfnc-01 Jan 00:02 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       List the requested transfer functions versus frequency.
|
|     Access:
|       (void) lstfnc(complex Tnumr[], real wr[], real wi[], real w0,
|         real wf, real winc, Word kindin, Word namein, int nin,
|         Token names[], int ntkns);
|     complex Tnumr[3,nfgc,2*nfgc],i-The transfer function numerators.
|     real    wr[2*nfgc],          i-Real parts of system eigenvalues.
|     real    wi[2*nfgc],          i-Imaginary parts of eigenvalues.
|     real    w0,                  i-Lower bound for frequency listings.
|     real    wf,                  i-Upper bound for frequency listings.
|     real    winc,                i-Initial (low) frequency increment.
|     Word    kindin,              i-Type of input, 'forc' or 'moti'.
|     Word    namein,              i-Name of the input force or joint.
|     int     nin,                 i-Component number of namein input.
|     Token   names[2*n],          i-Types and names of listings sought.
|     int     ntkns,               i-Number of tokens, 2*n.
|
|     Error Conditions:
|       If w0<=0 or wf<w0 or winc<=0 no listings are produced; a message
|     is printed.
|       If no joint or force with a specified name is found, no listing
|     is produced; a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     22 Mar 03:JJU-Implemented itextc and ftextc functions.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void lstfnc(complex Tnumr[], real wr[], real wi[], real w0, real wf,
    real winc, Word kindin, Word namein, int nin, Token names[], 
    int ntkns)
#else
  void lstfnc(Tnumr, wr, wi, w0, wf, winc, kindin, namein, nin, names, 
    ntkns)
  complex Tnumr[];
  real    wr[], wi[], w0, wf, winc;
  Word    kindin, namein;
  int     nin, ntkns;
  Token   names[];
#endif
{
  complex *Tfn, z;
  char     chcdvc[8], dsplay[8], locdvc[8], string[16];
  int      i, j, k, last, line, loc, loc1, loc2, m, maxout, nexp, nfgc, 
           n2;
  real     cons[6], dw, *out, w, x, y, zero;
  Word     kind, name, type;

/* Initialize. */
  nfgc = System.nfgc;
  n2   = nfgc + nfgc;
  zero = System.zero;
  qdvc(dsplay, chcdvc, locdvc);
  if ((w0 <= zero) || (wf < w0) || (winc < 0.0)) {
    textc("*** Frequency range for '", FALSE);
    textc(kindin, FALSE);
    textc((char *)SPACE, FALSE);
    textc(namein, FALSE);
    textc("' is in error. ***", TRUE);
    goto _1;
  }
  dw  = 1.0 + winc / w0;
  maxout = nint(2.0 + log(wf / w0) / log(dw));
  out = (real *)    calloc(12*maxout, sizeof(real));
  Tfn = (complex *) calloc(36*nfgc,   sizeof(complex));

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
      maxout = 0;
      for (w=w0; w<=wf; w=min(wf, w*dw)) {
        loc = 0;
        m   = maxout;
        for (j=0; j<last; j++) {
          loc1= loc +  6 * n2;
          loc2= loc + 12 * n2;
          z.r = 0.0;
          z.i = 0.0;
          for (k=0; k<n2; k++) {
            x = Tfn[loc+k].r - (Tfn[loc1+k].i + (Tfn[loc2+k].r * w) *w);
            y = Tfn[loc+k].i + (Tfn[loc1+k].r - (Tfn[loc2+k].i * w) *w);
            z = clessc(z, cdivc(cmplxc(x, y), cmplxc(wr[k],(wi[k]-w))));
          }
          loc += n2;
          if (nexp >  0) z = cmultc(z, cmplxc(0.0, w));
          if (nexp >= 0) z = cmultc(z, cmplxc(0.0, w));
          out[m] = cabsc(z);
          if(out[m] < zero) {
            out[m+1] = 0.0;
          } else {
            out[m+1] = System.ascale * atan2(z.i, z.r);
          }
          loc += n2;
          m   += 2;
        }
        maxout += 12;
      }

/* List the response for this item. */
      k = 0;
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
        textc(" about ", FALSE);
        ftextc(cons[j]);
        textc("", TRUE);
        textc("      Frequency      Amplitude          Phase", TRUE);
        line = 4;
        for (w=w0; w<=wf; w=min(wf, w*dw)) {
          line = (line + 1) % 5;
          if (line <= 0) textc("", TRUE);
          sprintf(string, "%#15.2f", w);
          textc(string, FALSE);
          sprintf(string, "%#15.4f", out[k]);
          textc(string, FALSE);
          sprintf(string, "%#15.2f", out[k+1]);
          textc(string, TRUE);
          k += 12;
        }
        if (qbitc(XQ_PAUSE, (void *) System.xeqflags)) {
          if (strcmp(dsplay, "graphic") == 0) waitc();
        } else {
          clrplc();
        }
        k += 2;
      }
    }
  }
  free (out);
  free (Tfn);
_1:
  return;
}
