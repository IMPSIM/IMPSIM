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
/* sttfnc-01 Jan 00:02 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Store the requested transfer functions on the store file.
|
|     Access:
|       (void) sttfnc(complex Tnumr[], real wr[], real wi[], 
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
|       If no joint or force with the specified name is found, no stored 
|     output is produced; a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void sttfnc(complex Tnumr[], real wr[], real wi[], Word kindin, 
    Word namein, int nin, Token names[], int ntkns)
#else
  void sttfnc(Tnumr, wr, wi, kindin, namein, nin, names, ntkns)
  complex Tnumr[];
  real    wr[], wi[];
  Word    kindin, namein;
  int     nin, ntkns;
  Token   names[];
#endif
{
  complex *Tfn;
  int     i, j, k, last, loc, lun, nexp, nfgc, n2;
  real    cons[6], zero;
  Word    kind, name, type;

/* Initialize. */
  nfgc = System.nfgc;
  n2   = nfgc + nfgc;
  zero = System.zero;
  lun  = lunfil[2];
  if (lun > 0) {
    fprintf(streams[lun]," DYN. ---- %#4i %#19.10e %#19.10e %#19.10e\n",
      ntkns/2, (real) n2, 0.0, 0.0);
    for (k=0; k<n2; k++) {
      fprintf(streams[lun], "%#12.5e%#12.5e\n", wr[k], wi[k]);
    }
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

/* Store the transfer function for this item. */
        fprintf(streams[lun],
          " %4s %4s %#4i %#19.10e %#19.10e %#19.10e\n",
          type, name, last, (real) n2, 0.0, 0.0);
        for (j=0; j<last; j++) {
          fprintf(streams[lun], " %#19.10e", cons[j]);
        }
        fprintf(streams[lun], "\n");
        loc = 0;
        for (j=0; j<last; j++) {
          for (k=0; k<n2; k++) {
            fprintf(streams[lun], "%#12.5e%#12.5e%", 
              Tfn[loc+k].r, Tfn[loc+k].i);
            if ((k > 0) && (k % 3 == 0)) fprintf(streams[lun], "\n");
          }
          loc += n2;
        }
      }
    }
  }
  free (Tfn);
  return;
}
