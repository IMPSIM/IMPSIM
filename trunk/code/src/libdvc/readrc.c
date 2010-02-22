/* ------------------------------------------------------------------ */
/* readrc-01 Jan 00:24 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Open or close a data file for reading of input commands.
|
|     Access:
|       (void) readrc(char *filename)
|     char *filename,i-Command input filename.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The command input file is an ASCII format (editable) file.
|       readrc() itself causes no lines to be read from the command
|     input file; it only opens, activates, suspends, or closes the
|     file.  When the file is opened and active, subsequent input
|     commands read by routine bfinc() are read from the file.
|       If the command input file is open and active, routine bfinc()
|     accepts input from that file.  If not, it accepts input from the
|     lunitc("input") logical unit.
|       Input from the command input file may be temporarily discontin-
|     ued by calling routine readrc() with filename = "off".  Input from
|     the file may then be resumed on the previous filename by calling
|     readrc() again with filename = "on".
|       Input from the command file may be permanently discontinued by
|     calling routine readrc() with filename = "close".  Input from that
|     filename may then not be resumed again since the file will begin
|     as a new file if reopened.
|       If interactive and filename = " " or NULL, the previously
|     defined filename is used; a prompt is issued for a filename on the
|     initial call to routine readrc().  If not interactive, the name
|     "log.dat" is assigned.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void readrc(char *filename)
#else
  void readrc(filename)
  char *filename;
#endif
{
  static char fileid[MXFLCH+1] = "";

  opnflc(&lunrd, FT_READ, "r", filename, fileid);
  return;
}
