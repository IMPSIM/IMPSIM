/* ------------------------------------------------------------------ */
/* helpc-04 Aug 03:28 Sep 06
|     (C)Copyright, JJU Research, 2003-2006.
|
|     Description:
|       This function displays a help message for a chosen menu option.
|
|     Access:
|       (void) helpc(int noptns, char *mnu[], char prefix);
|     int noptns,   i - Number of options in the menu array.
|     char *mnu[],  i - Array of menu option strings.
|     char  prefix, i - Single character prefix to menu strings for help
|                       filenames.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Help files are assumed stored in the directory pointed to by
|     helpdir of diridc.h.  The filenames are assumed to match the menu
|     strings, truncated to MXCHAR characters, prefixed by the given
|     single character prefix and suffixed with the extension which is
|     assumed to be ".hlp".
*
*     History:
*     04 Aug 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void helpc(int noptns, char *mnu[], char prefix)
#else
  void helpc(noptns, mnu[], prefix)
  int   noptns;
  char *mnu[];
  char  prefix;
#endif
{
  char  buffer[(MXINBF+1)], fileid[(MXFLCH+1)], name[(MXCHAR+1)];
  int   ipick, khdr, lfirst, lun, nchrs, nhdrs;

  qhdrc(&khdr, &nhdrs);
  if (noptns <= 1) {
    ipick = 1;
  } else {
    textc("Select a menu option.", TRUE);
    ipick = mnupkc();
    ldkhdc(khdr); /* Reset the header if a different menu was chosen. */
  }

/* Build the correct help filename. */
  if ((ipick > 0) && (ipick <= noptns)) {
    strcpy(name, mnu[ipick-1]);
  } else if ((ipick > 100) && (ipick <= (100+nhdrs))) {
    qheadc(name, ipick-100);
  } else if (ipick == 201) {
    strcpy(name, "quest");
  } else if (ipick == 202) {
    strcpy(name, "current");
  } else if (ipick == 203) {
    strcpy(name, "help");
  } else if (ipick == 204) {
    strcpy(name, "multivu");
  } else if (ipick == 205) {
    strcpy(name, "refresh");
  } else {
    strcpy(name, "@@@@@@");
  }
  stripc(name);
  name[min(lenc(name), MXCHAR)]='\0';/* Truncate to MXCHAR chars max. */
  lcasec(name);
  strcpy(fileid, helpdir);        /* Copy the helpdir file directory. */
  nchrs = lenc(fileid);
  if ((prefix != NULL) && (prefix != SPACE)) {
    fileid[nchrs] = prefix;              /* Add the prefix if needed. */
    nchrs++;
  }
  fileid[nchrs] = '\0';          /* Truncate any trailing whitespace. */
  strcat(fileid, name);    /* Add the name of the chosen help option. */
  strcat(fileid, ".hlp"); /* Suffix the ".hlp" extension to the name. */
  fileid[lenc(fileid)] = '\0';

/* Open the helpfile. */
  lun = lunitc("file");
  streams[lun] = fopen(fileid, "r");
  if (streams[lun] == NULL) {
    textc("Error ", FALSE);
    itextc(errno);
    textc(" opening: ", FALSE);
    textc(fileid, TRUE);
    textc("Error:  Problem in the Help processor.", TRUE);

/* Copy the helpfile contents to a fresh screen. */
  } else {
    newpgc();
    lfirst = TRUE;
    while (fgets(buffer, MXINBF, streams[lun]) != NULL) {
      if (!lfirst) {                 /* Skip printing the first line. */
        buffer[lenc(buffer)]='\0';/*Truncate any trailing whitespace. */
        textc(buffer, TRUE);
      }
      lfirst = FALSE;
    }
    fclose (streams[lun]);
    streams[lun] = NULL;  /* Make available to lunitc() for reassign. */
  }

/* Pause and wait for the user before continuing. */
  waitc();
  ldraw = TRUE;
  return;
}
