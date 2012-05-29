/* ------------------------------------------------------------------ */
/* ldhdrc-01 Jan 00:28 Sep 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Set the menu header strings into libcad global memory.
|
|     Access:
|       (void) ldhdrc(int nmenus, char *hdrs[]);
|     int  nmenus,   i-Number of menu headers defined.
|     char hdrs[][9],i-Array of 8-character menu header strings.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine must be called to define the menu headers before
|     drmnuc() is executed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldhdrc(int nmenus, char *hdrs[])
#else
  void ldhdrc(nmenus, hdrs)
  int   nmenus;
  char *hdrs[];
#endif
{
# define MXCHRS 9
  int    j;

  for (j=0; j<nhdrs; j++) {
    free(header[j]);
  }
  nhdrs = nmenus;
  for (j=0; j<nhdrs; j++) {
    header[j] = (char *) malloc(MXCHRS * sizeof(char));
    strncpy(header[j], hdrs[j], MXCHRS);
    header[j][MXCHRS-1] = '\0';
  }
  imin = (nhdrs > 0) ? ((nhdrs - 1) / MXHDRS + 1) : 0;
  return;
# undef MXCHRS
}
