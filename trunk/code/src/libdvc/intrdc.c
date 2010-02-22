/* ------------------------------------------------------------------ */
/* intrdc-01 Jan 00:01 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
|
|     Description:
|       This function returns an integer value from the input buffer if
|     possible.  It operates like a Fortran-77 list-directed (i.e., free
|     format) read from the local input buffer.
|
|     Access:
|       intrd = (int) intrdc(int ideflt, int *istate);
|     int  ideflt,i-Initial or default value for the number.
|     int *istate,o-Flag set equal to zero if no error has occurred.
|     int  intrd, o-Integer value read.
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
#ifdef ANSI
  int intrdc(int ideflt, int *istate)
#else
  int intrdc(ideflt, istate)
  int ideflt, *istate;
#endif
{
  int cnvrt, intrd;
 
/* Slash occured earlier on this line. */
  *istate=0;
  if (dfltline) return(ideflt);
 
/* Check for an empty buffer. */
  if ((! inloc) || (! *inloc) || (*inloc == EOR)) {
    return(ideflt);
  }
 
/* Step over spaces. */
  inloc += strspn(inloc, " ");
 
/* Blank field. */
  if (*inloc == COMMA) {
    inloc++;
    return(ideflt);
  }
  if (*inloc == SLASH) {
    dfltline = TRUE;
    return(ideflt);
  }
  cnvrt = sscanf(inloc, "%d", &intrd);
 
/* Skip over the number that was just read in. */
  inloc += strspn(inloc, "+-0123456789");
 
/* And the following seperator. */
  inloc += strspn(inloc, " ");
  if (*inloc == COMMA) inloc++;
 
/* Error in input conversion. */
  if (cnvrt < 1) {
    *istate = 1;
    textc("Error: Integer value(s) expected.", TRUE);
    return(ideflt);
  }
  return(intrd);
}
