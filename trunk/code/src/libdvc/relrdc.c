/* ------------------------------------------------------------------ */
/* relrdc-01 Jan 00:01 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
|
|     Description:
|       This function returns a real value from the input buffer if
|     possible.  It operates like a Fortran-77 list-directed (i.e., free
|     format) read from the local input buffer.
|
|     Access:
|       relrd = (real) relrdc(real dfault, int *istate)
|     real dfault,i-Initial or default value.
|     int *istate,o-Flag set to zero if no error has occurred.
|     real relrd, o-Value read.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Character data must have been previously read into the local
|     input buffer by a call to bfinc().
|       The input buffer pointer will be advanced to the next valid
|     separator ("," or " " or <EOR>) to be ready for subsequent reads
|     from the same input buffer.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#if defined(ANSI)
  real relrdc(real dfault, int *istate)
#else
  real relrdc(dfault, istate)
  real dfault;
  int *istate;
#endif
{
  int  cnvrt;
  real value;
 
/* Return dfault value if slash occured earlier on this line. */
  *istate = 0;
  if (dfltline) return(dfault);
 
/* Return dfault value for an empty buffer. */
  if ((! inloc) || (! *inloc) || (*inloc == EOR)) {
    return(dfault);
  }
 
/* Step over leading spaces. */
  inloc += strspn(inloc, " ");
 
/* Return dfault value for a blank field. */
  if (*inloc == COMMA) {
    inloc++;
    return(dfault);
  }

/* Return dfault value for slash input. */
  if (*inloc == SLASH) {
    dfltline = TRUE;
    return(dfault);
  }

/* Read the value from the input buffer. */
  cnvrt = sscanf(inloc, "%f", &value);
 
/* Skip over the characters that were just read. */
  inloc += strspn(inloc, "+-.0123456789eE");
 
/* Also skip over the terminating seperator. */
  inloc += strspn(inloc, " ");
  if (*inloc == COMMA) inloc++;
 
/* Print a message for an error in input conversion. */
  if (cnvrt < 1) {
    *istate = 1;
    textc("Error: Real numeric value(s) expected.", TRUE);
    return(dfault);
  }

/* Return the value read. */
  return(value);
}
