/* ------------------------------------------------------------------ */
/* opnflc-01 Jan 00:15 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
|
|     Description:
|       Open, activate, suspend, or close a data file.
|
|     Access:
|       nogo = (int) opnflc(int *lun, enum Filtyp type, char *rwflag,
|         char *keyword, char *filename);
|     int  *lun,     i/o-The stream number for the file.
|     enum Filtyp type,i-The enumeration type of the file to open; valid
|       enumeration values for Filtyp are:
|         enum Filtyp {FT_ERROR=0, FT_ECHO, FT_PRINT, FT_READ, 
|           FT_SYMBOL, FT_WRITE};
|     char *rwflag,  i-Indicates if the file should be opened for 
|       reading (*rwflag = "r") or writing (*rwflag = "w").
|     char *keyword,i-Keyword: "on", "off", "close", or former filename.
|     char *filename,i/o-New input or output filename.
|     int  nogo,     o-Set TRUE on exit if the file is actually opened.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The graphic display device must have been defined by a previous
|     call to devic.
|       The function opnflc() itself causes no lines to be input from or
|     output to the file; it only opens, activates, suspends, or closes
|     the file.
|       Input from or output to the file may be temporarily discontinued
|     by calling opnflc() with keyword = "off". Input/output from/to the
|     previous filename may then be resumed by calling opnflc() again
|     with keyword = "on".
|       Input from or output to the file may be permanently discontinued
|     by calling opnflc() with keyword = "close".  Input from or output
|     to that file may then not be resumed again since the file begins
|     anew if it is reopened.
|       If interactive and keyword = " " or NULL, the previously defined
|     filename is used; a prompt is issued for a filename on the initial
|     call to this function.  If not interactive, a preassigned default 
|     name is assigned.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int opnflc(int *lun, enum Filtyp type, char *rwflag, char *keyword,
    char *filename)
#else
  int opnflc(lun, type, rwflag, keyword, filename)
  int  *lun;
  enum Filtyp type;
  char *rwflag, *keyword, *filename;
#endif
{
# define MX_FILETYPES   6                    /* Number of file types. */
  static char *prompt[MX_FILETYPES] = 
    {"an error", "an echo", "a print", "a command input", "a symbol",
      "an output log"};
  static char *dfault[MX_FILETYPES] =
    {"err.dat", "ech.dat", "prt.dat", "log.dat", "sym.dat", "log.dat"};
  char key[6], *pntr1, *pntr2;
  int i;
 
/* Check for keyword = "on". */
  for (i=0; i<5; i++) key[i] = tolower(keyword[i]);
  key[5] = '\0';
  if (strncmp(key, "on", 2) == 0) {
    if (*lun < 0) *lun = -(*lun);
    goto DONE;
 
/* Check for keyword = "off". */
  } else if (strncmp(key, "off", 3) == 0) {
    if (*lun > 0) *lun = -(*lun);
    goto DONE;
 
/* Check for keyword = "close". */
  } else if (strncmp(key, "close", 5) == 0) {
    if (*lun < 0) *lun = -(*lun);
    if (*lun){
      fclose(streams[*lun]);
      streams[*lun] = (FILE *) NULL;
    }
    *lun = 0;
    *filename = '\0';
    goto DONE;
  }
 
/* Check for and replace a blank filename. */
  if (lenc(keyword) == 0) {
    if (lenc(filename) == 0) {
      if (intact){
        textc("Enter a name for ", FALSE);
        textc(prompt[type], FALSE);
        textc(" file.", TRUE);
        fnamec("", filename);
      } else {
        strcpy(filename, dfault[type]);
      }
    } else if (*lun) {
      if (*lun < 0) *lun = -(*lun);
      goto DONE;
    }
 
/* Check for and close old file if a new filename is specified. */
  } else {
    if (lenc(filename) > 0) {
      if (*lun < 0) *lun = -(*lun);
      if (*lun) {
        fclose(streams[*lun]);
        streams[*lun] = (FILE *) NULL;
      }
      *lun = 0;

/* Copy former filename from keyword to replace blank filename. */
    } else {
      strcpy(filename, keyword);
    }
  }
 
/* Remove any blanks from the filename. */
  for (pntr1=pntr2=filename; *pntr1; pntr1++) {
    if (*pntr1 != SPACE) *pntr2++ = *pntr1;
  }
  *pntr2 = '\0';
 
/* Open the file. */
  *lun = lunitc("file");
  if ((streams[*lun] = fopen(filename, rwflag)) == NULL) {
    textc("Cannot open '", FALSE);
    textc(filename, FALSE);
    textc("' as ", FALSE);
    textc(prompt[type], FALSE);
    textc(" file.", TRUE);
    *filename = '\0';
    *lun = 0;
    goto DONE;
  } else {
    return(TRUE);
  }
DONE:
  return(FALSE);
# undef MX_FILETYPES
}
