/* ------------------------------------------------------------------ */
/* ldmnuc-01 Jan 00:26 Nov 05
|     (C)Copyright, JJU Research, 2000-2005.
|
|     Description:
|       Set a set of menu options into the libcad global memory.
|
|     Access:
|       (void) ldmnuc(char *titel, int noptns, char *mnu[]);
|     char *titel,   i-Title of the menu being defined.
|     int   noptns,  i-Number of options being defined in the menu.
|     char  mnu[][9],i-Array of 8-character menu strings.
|
|     Error Conditions:
|       If titel is not found among the array of headers previously set
|     by ldhdrc(), then khdr and menumx are both set to zero and new
|     menu options are not stored.  A message is printed.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The menu header strings must have been defined by a previous
|     call to ldhdrc().
|       This routine must be called to define the menu options before
|     drmnuc() is executed.
*
*     History:
*     01 Jan 00:JJU-Original.
*     05 Aug 03:JJU-Separated mnu into a C style array of strings.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldmnuc(char *titel, int noptns, char *mnu[])
#else
  void ldmnuc(titel, noptns, mnu)
  char *titel;
  int   noptns;
  char *mnu[];
#endif
{
# define MXCHRS 9
  char   titl[MXCHRS];
  int    j, nchars, nmenu;
 
  strncpy(titl, titel, MXCHRS);
  titl[MXCHRS-1] = '\0';
  stripc(titl);
  ucasec(titl);
  nchars = min(lenc(titl), MXCHRS-1);
  nmenu  = 0;
  for (j=0; j<nhdrs; j++) {
    if (strncmp(header[j], titl, nchars) == 0) {
      nmenu = j + 1;
      break;
    }
  }
  if (nmenu <= 0) {
    textc("Error:  Invalid menu header.", TRUE);
    khdr   = 0;
    menumx = 0;
  } else {
    for (j=0; j<noptns; j++) {
      free(menu[j]);
      menu[j] = (char *) malloc(MXCHRS * sizeof(char));
      strncpy(menu[j], mnu[j], MXCHRS);
      menu[j][MXCHRS-1] = '\0';
    }
    khdr   = nmenu;
    menumx = noptns;
  }
  return;
# undef MXCHRS
}
