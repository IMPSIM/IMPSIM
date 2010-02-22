/* ------------------------------------------------------------------ */
/* fnamec-01 Jan 00:24 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Expand and validate the syntax of a character string as a system
|     filename.
|
|     Access:
|       (void) fnamec(char *filename, char *fileid);
|     char *filename,i-Character string supplied.
|     char *fileid,o-Validated filename.
|
|     Error Conditions:
|       I/O errors are reported directly by the operating system.
|
|     Comments:
|       If filename=" " or NULL is used, the display device must have
|     been defined by a previous call to devic().
|       If interactive, filename=" " or NULL causes a prompt for a
|     filename.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fnamec(char *filename, char *fileid)
#else
  void fnamec(filename, fileid)
  char *filename, *fileid;
#endif
{
  char *pntr1, *pntr2;
  int   j;
 
  if (intact && ((lenc(filename) <= 0))) {
    do {
      textc("  Filename: > ", FALSE);
    } while(bfinc(" ") != 0);
    bfgetc(fileid);
  } else {
    strcpy(fileid, filename);
  }
  for (pntr1=pntr2=fileid; *pntr1; pntr1++) {
    if (*pntr1 != SPACE) *pntr2++ = *pntr1;/* Remove internal blanks. */
  }
  *pntr2 = '\0';
  for (j=MXFLCH-strlen(fileid); j; j--) *pntr2++ = '\0';
  return;
}
