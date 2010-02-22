/* ------------------------------------------------------------------ */
/* prntrc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Open or close a data file for post-processed off-line printing
|     of text output.
|
|     Access:
|       (void) prntrc(char *filename, char *title, char *release,
|         char *cpyrgt);
|     char filename[], i-Postprocessor print filename.
|     char title[],    i-Title of the program.
|     char release[12],i-Release date in the form "01 Jul 1995".
|     char cpyrgt[5],  i-Initial copyright year, e.g. "1995".
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The postprocessor print file is an ASCII format (editable) file.
|       The routine prntrc() itself causes no lines to be printed or
|     stored in the print file; it only opens, activates, suspends, or
|     closes the file.  When the file is opened and active, subsequent
|     output specified by textc() is written to the file.
|       If the command input file is open and active, routine bfinc()
|     accepts input from that file.  If not, it accepts input from the
|     lunitc("input") logical unit.
|       Output to the print file may be temporarily discontinued by
|     calling routine prntrc() with filename = "off".  Printing may then
|     be resumed on the previous filename by calling prntrc() again with
|     filename = "on".
|       Output to the print file may be permanently discontinued by
|     calling routine prntrc() with filename = "close".  Output to that
|     filename may then not be resumed again since the file will begin
|     as a new file if reopened.
|       If interactive and filename = "" or NULL, the previously defined 
|     filename is used; a prompt is issued for a filename on the initial 
|     call to routine prntrc().  If not interactive, the filename 
|     "prt.dat" is assigned.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void prntrc(char *filename, char *title, char *release, char *cpyrgt)
#else
  void prntrc(filename, title, release, cpyrgt)
  char *filename, *title, *release, *cpyrgt;
#endif
{
  char  *space = "                                                  ";
  static char fileid[MXFLCH+1], date[12], tod[9], version[7], yrleas[5];
  static int lun = 0;
  int index, n;
 
/* Open the print file if necessary. */
  opnflc(&lunpr, FT_PRINT, "w", filename, fileid);

/* If a new file, enter the JJU copyright and header at the top. */
  if ((lunpr > 0) && (lunpr != abs(lun))) {
    datec(date);
    todc(tod);
#   if __WATCOMC__
      strcpy(version, "Win/NT");
#   else
      strcpy(version, "Unix  ");
#   endif
    strncpy(yrleas, &(release[7]), 4);
    yrleas[4] = '\0';
    lun = lunpr;
    fprintf(streams[lun],
      "\n                           <<<  Notice  >>>\n\n");
    fprintf(streams[lun], "This is the %s program.\n", title);
    fprintf(streams[lun],
      "(C)Copyright, JJU Research, %4s", cpyrgt);
    if (strcmp(yrleas, cpyrgt)){
      fprintf(streams[lun], "-%4s", yrleas);
    }
    fprintf(streams[lun], ".  All rights reserved.\n\n");
    fprintf(streams[lun], "JJU Research is endeavoring to make this ");
    fprintf(streams[lun], "program as complete,  accurate,\n");
    fprintf(streams[lun], "and  easy  to use as possible.   ");
    fprintf(streams[lun], "Suggestions  and comments are welcomed.\n");
    fprintf(streams[lun], "Any errors encountered in either the ");
    fprintf(streams[lun], "documentation  or  in  the  resluts\n");
    fprintf(streams[lun], "should be immediately brought to our ");
    fprintf(streams[lun], "attention.\n\n");
    fprintf(streams[lun], "Neither JJU Research nor those supplying  ");
    fprintf(streams[lun], "the  computer  facilities  for\n");
    fprintf(streams[lun], "this  analysis  assume any responsibility ");
    fprintf(streams[lun], "for the validity, accuracy, or\n");
    fprintf(streams[lun], "applicablitiy of any results obtained ");
    fprintf(streams[lun], "from this system; users must verify\n");
    fprintf(streams[lun], "their own results.\n\n");
    fprintf(streams[lun], "************************************");
    fprintf(streams[lun], "************************************\n");
    n = strlen(title);
    index = 50-((70-n)/2);
    fprintf(streams[lun], "*%s", &(space[index]));
    fprintf(streams[lun], "%s", title);
    index = 50-(20-n+index);
    fprintf(streams[lun], "%s*", &(space[index]));
    fprintf(streams[lun],
      "\n*                %6s Version --", version);
    fprintf(streams[lun], " Released %11s                *", release);
    fprintf(streams[lun], "\n*                 on %11s   ", date);
    fprintf(streams[lun], "        at %8s                 *", tod);
    fprintf(streams[lun], "\n**********************************");
    fprintf(streams[lun], "**************************************");
  }
  return;
}
