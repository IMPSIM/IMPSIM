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
/* tablec-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Calculate and store the Fourier series coefficients from an
|     appropriate file of numeric data.
|
|     Access:
|       (void) tablec(char *fileid, Value *value);
|     char *fileid,i/o-Filename string for the numeric data.
|     Value *value,i  -Pointer to the Value record.
|
|     Error Conditions:
|       System.nerror = 1 indicates that a valid filename is not found
|     or that the file cannot be opened; a message is printed.
|       System.nerror = 2 indicates that more than NSIZE = 1024 data
|     were found in the file and cannot be held in IMP memory.  An error
|     message is printed.
|       System.nerror = 3 indicates a read error from the data file.  An
|     error message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void tablec(char *fileid, Value *value)
#else
  void tablec(fileid, value)
  char  *fileid;
  Value *value;
#endif
{
# define NSIZE 1024
  char     filename[MXFLCH+1];
  complex *coeff, exponent, term;
  int      i, k, lun, npts;
  real    *data, f0, f1, phi;

/* Create a temporary record for the tabular data. */
  data = ((real *) calloc((NSIZE + 2), sizeof(real)));

/* Obtain the filename from the input string. */
  fnamec(fileid, filename);
  if (filename[0] == '!') {
    echoc();
    textc("*** A valid filename is not found. ***", TRUE);
    System.nerror = 1;

/* Open the file. */
  } else {
    lun = lunitc("file");
    streams[lun] = fopen(filename, "r");
    if (streams[lun] == NULL) {
      echoc();
      textc("*** File '", FALSE);
      textc(filename, FALSE);
      textc("' can not be opened. ***", TRUE);
      System.nerror = 1;

/* Read the data from the file. */
    } else {
#     ifdef DOUBLE_PREC
        fscanf(streams[lun], "%lf%lf", &f0, &f1);
#     else
        fscanf(streams[lun], "%f%f",   &f0, &f1);
#     endif
      data[0] = f0;
      data[1] = f1;
      data   += 2;                  /* Offset the array address by 2. */
      npts = 0;
      for (i=0; i<NSIZE; i++) {
        f0 = 0.0;
#       ifdef DOUBLE_PREC
          fscanf(streams[lun], "%lf", &f0);
#       else
          fscanf(streams[lun], "%f",  &f0);
#       endif
        if (feof(streams[lun])) break;
        if (ferror(streams[lun])) {
          echoc();
          textc("*** Error in reading TABLE data file. ***", TRUE);
          System.nerror = 3;
          goto _2;
        }
        data[i] = f0;
        npts++;
      }
      if (npts >= NSIZE) {
        echoc();
        textc("*** The data file is too big for IMP memory. ***", TRUE);
        System.nerror = 2;

/* Create the record for the Fourier series coefficients. */
      } else {
        coeff = ((complex *) calloc((npts / 2 + 2), sizeof(complex)));
        value->arg[1] = (void *) coeff; /* Attach to the TABLE Value. */
        coeff[0].r = (real) npts;
        coeff[0].i = 0.0;
        coeff[1].r = data[-2];
        coeff[1].i = data[-1];

/* Calculate the Fourier series coefficients from the tabular data. */
        phi = 2.0 * PI / npts;
        for (k=0; k<(npts/2); k++) {
          coeff[k+2].r = 0.0;
          coeff[k+2].i = 0.0;
          for (i=0; i<npts; i++) {
            exponent = cmplxc(0.0, -k * i * phi);
            term = cexpc(exponent);
            coeff[k+2].r += data[i] * term.r;
            coeff[k+2].i += data[i] * term.i;
          }
          coeff[k+2].r /= npts;
          coeff[k+2].i /= npts;
        }
      }
    }
  }
_2:
  free(data - 2);
  fclose(streams[lun]);
  return;
# undef NSIZE
}
