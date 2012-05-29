/* ------------------------------------------------------------------ */
/* alprdc-01 Jan 00:01 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
|
|     Description:
|       This function returns an alphanumeric string from the input
|     buffer if possible.  It operates like a Fortran-77 list-directed
|     (i.e., free format) read from the local input buffer.
|
|     Access:
|       void alprdc(char *dfault, char *string)
|     char *dfault,i-Initial or default value for string.
|     char *string,o-Left-justified string returned.
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
|     separator ("," or " " or "<EOR>") to be ready for subsequent reads
|     from the same input buffer.
|       The string read will be returned left-justified with blank fill
|     on the right for strings shorter than the specified length.
|       The string value stored in dfault will be returned for a null
|     string (consecutive separators) in the buffer.  The end of record
|     character defined by the bfinc() call will be returned if the
|     buffer is empty.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void alprdc(char *dfault, char *string)
#else
  void alprdc(dfault, string)
  char *dfault, *string;
#endif
{
  char *end, save, skip[4];

/* Check for an empty buffer. */
  if ((! inloc) || (! *inloc) || (*inloc == EOR)) {
    strcpy(string, dfault);
    return;
  }
  inloc += strspn(inloc, " ");

/* Treat an empty field. */
  if (*inloc == COMMA) {
    inloc++;
    strcpy(string, dfault);
    return;
  }
  if (*inloc == SLASH) {
    dfltline = TRUE;
    strcpy(string, dfault);
    return;
  }

/* Search for the end of the string. */
  sprintf(skip, " ,%c", EOR);
  end = inloc + strcspn(inloc, skip);
  save = *end;
  *end = '\0';

/* Copy the string. */
  strcpy(string, inloc);
  *end = save;
  inloc = end;
  inloc += strspn(inloc, " ");
  if (*inloc == COMMA) inloc++;
  if (*string == '\0') strcpy(string, dfault);
  return;
}
