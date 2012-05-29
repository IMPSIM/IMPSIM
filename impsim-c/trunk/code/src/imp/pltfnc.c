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
/* pltfnc-01 Jan 00:02 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Plot the requested transfer functions versus frequency.
|
|     Access:
|       (void) pltfnc(complex Tnumr[], real wr[], real wi[], real w0,
|         real wf, real winc, Word kindin, Word namein, int nin,
|         Token names[], int ntkns);
|     complex Tnumr[3,nfgc,2*nfgc],i-The transfer function numerators.
|     real    wr[2*nfgc],          i-Real parts of system eigenvalues.
|     real    wi[2*nfgc],          i-Imaginary parts of eigenvalues.
|     real    w0,                  i-Lower bound for frequency plots.
|     real    wf,                  i-Upper bound for frequency plots.
|     real    winc,                i-Initial (low) frequency increment.
|     Word    kindin,              i-Type of input, 'forc' or 'moti'.
|     Word    namein,              i-Name of the input force or joint.
|     int     nin,                 i-Component number for namein input.
|     Token   names[2*n],          i-Types and names of plots sought.
|     int     ntkns,               i-Number of tokens, 2*n.
|
|     Error Conditions:
|       If w0<=0 or wf<w0 or winc<=0 no plots are produced; a message is
|     printed.
|       If no joint or force with a specified name is found, no plot is
|     produced; a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void pltfnc(complex Tnumr[], real wr[], real wi[], real w0, real wf,
    real winc, Word kindin, Word namein, int nin, Token names[], 
    int ntkns)
#else
  void pltfnc(Tnumr, wr, wi, w0, wf, winc, kindin, namein, nin, names, 
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
  int      i, j, k, last, loc, loc1, loc2, m, maxout, n, nexp, nfgc, n2;
  real     cons[6], dw, *out, schsiz, tchsiz, w, x, y, ymin, ymax, zero;
  Word     kind, name, type;

/* Initialize. */
  nfgc = System.nfgc;
  n2   = nfgc + nfgc;
  zero = System.zero;
  qchszc(&schsiz, &tchsiz);
  qdvc(dsplay, chcdvc, locdvc);
  if ((w0 <= zero) || (wf < w0) || (winc <= 0.0)) {
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
      k = 0;
      for (j=0; j<last; j++) {

/* Plot the response graph for this item. */
        newpgc();
        framgc(6.0*schsiz, 4.0*tchsiz, 1.0-3.0*schsiz, 0.8);
        amnmxc(&out[k], 12, maxout/12, &ymin, &ymax);
        gridc(3, w0, ymin, wf, ymax);
        movagc(w0, out[k]);
        m = k;
        for (w=w0; w<=wf; w=min(wf, w*dw)) {
          drwagc(w, out[m]);
          m += 12;
        }
        framgc(6.0*schsiz, 0.8+tchsiz, 1.0-3.0*schsiz, 1.0-tchsiz);
        gridc(1, w0, -180.0, wf, 180.0);
        movagc(w0, out[k+1]);
        m = k + 1;
        for (w=w0; w<=wf; w=min(wf, w*dw)) {
          drwagc(w, out[m]);
          m += 12;
        }
        movasc(0.0, tchsiz);
        htextc(type);
        htextc(" response of ");
        htextc(kind);
        htextc(" ");
        htextc(name);
        htextc(",");
        htextc(_itoa(j, string, 10));
        htextc(" to ");
        htextc(kindin);
        htextc(" of ");
        htextc(namein);
        htextc(",");
        htextc(_itoa(nin, string, 10));
        htextc(" about ");
        sprintf(string, "%9.4f", cons[j]);
        stripc(string);
        htextc(string);
        movasc(schsiz, 0.9 + 2.5 * tchsiz);
        vtextc("Phase");
        movasc(schsiz, 0.4 + 4.5 * tchsiz);
        vtextc("Amplitude");

/* Print the title of the modeled system. */
        n=strlen(System.title);
        if (n > 0){
          movasc(0.5*(1.0-n*schsiz), 0.0);
          htextc(System.title);
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
