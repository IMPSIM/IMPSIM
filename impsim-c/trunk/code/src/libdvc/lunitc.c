/* ------------------------------------------------------------------ */
/* lunitc-01 Jan 00:25 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Issues a new user-assignable logical unit (stream) number for
|     use by an operating program.
|
|     Access:
|       lun = (int) lunitc(char *type);
|     char *type,i-Keyword implying purpose for the stream:
|       type = "input"  for the standard input stream;
|       type = "output" for the standard output stream;
|       type = "error"  for the stream for error messages;
|       type = "echo"   for the stream for echo of input data;
|       type = "print"  for the stream for the printfile;
|       type = "read"   for the stream for input command data;
|       type = "symbol" for the stream for stroked characters;
|       type = "write"  for the stream for store of command data;
|       type = "file"   for a new stream to attach to a file.
|     int lun,o-Stream number issued.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If type is not one of the specified keywords, then type = "file"
|     is assumed.
|       When type="file", the next available unused stream number is
|     returned.  Any current attachment to an open file, disallows
|     return of such a number.
|       The number returned is not yet connected to any open file, nor
|     is such a file opened by lunitc().
*
*     History:
*     01 Jan 00:JJU-Original.
*     25 Aug 03:JJU-Added diagnostic message when lun's exhausted.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  int  lunitc(char *type)
#else
  int  lunitc(type)
  char *type;
#endif
{
  static int lun = MINLUN;
  char   kind[8];
  int    lun0;

  strcpy(kind, type);
  stripc(kind);
  kind[lenc(kind)] = '\0';
  lcasec(kind);
  if (strcmp(kind, "input")  == 0) return(STDIN);
  if (strcmp(kind, "output") == 0) return(STDOUT);
  if (strcmp(kind, "error")  == 0) return(STDERR);
  if (strcmp(kind, "echo")   == 0) return(luneco);
  if (strcmp(kind, "print")  == 0) return(lunpr);
  if (strcmp(kind, "read")   == 0) return(lunrd);
  if (strcmp(kind, "symbol") == 0) return(lunsmb);
  if (strcmp(kind, "write")  == 0) return(lunwr);
  lun0 = lun;
  do {
    if (++lun >= MXLUNS) lun = MINLUN + 1;
  } while((streams[lun] != NULL) && (lun != lun0));
  if (lun == lun0) textc(
    "*** Error: No unused LUN's available in lunitc(). ***", TRUE);
  return(lun);
}
