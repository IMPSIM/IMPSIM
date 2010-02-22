/* ------------------------------------------------------------------ */
/* writrc-01 Jan 00:13 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Open or close a data file for logging of the input commands.
|
|     Access:
|       (void) writrc(char *filename);
|     char *filename,i-Input command log filename.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The input command log file is an ASCII format (editable) file.
|       The routine writrc() itself causes no lines to be printed or
|     stored in the log file; it only opens, activates, suspends, or
|     closes the file.  When the file is opened and active, subsequent
|     input commands read by subroutine bfinc() are written to the file.
|       Output to the log file may be temporarily discontinued by call-
|     ing routine writrc() with filename = "off".  Logging may then be
|     resumed on the previous filename by calling writrc() again with
|     filename = "on".
|       Output to the log file may be permanently discontinued by call-
|     ing routine writrc() with filename = "close".  Output to that
|     filename may then not be resumed again since the file will begin
|     as a new file if reopened.
|       If interactive and filename = " ", the previously defined file-
|     name is used; a prompt is issued for a filename on the initial
|     call to routine writrc().  If not interactive, the name "log.dat"
|     is assigned.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void writrc(char *filename)
#else
  void writrc(filename)
  char *filename;
#endif
{
  static char fileid[MXFLCH+1] = "";

  opnflc(&lunwr, FT_WRITE, "w", filename, fileid);
  if (strncmp(filename, "off", 3) == 0) {
  } else if (strncmp(filename, "close", 5) == 0) {
  } else if ((lunwr > 0) && (lenc(fileid) > 0)) {
    if (lenc(filename) > 0) streams[lunwr] = fopen(fileid, "r+");
  }
  return;
}
