/* ------------------------------------------------------------------ */
/* bfinc-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Input a string of character data from the standard input device
|     into the local input buffer.
|
|     Access:
|       nogo = (int) bfinc(eorchr);
|     char *eorchr,i-Single character to be returned for end of record
|       when reading information from the local input buffer.
|     int nogo,o-flag indicating nogo=0 for successful read, nogo=1 for
|       "help" key input, nogo=2 for "oops" key input, or nogo=-1 for
|       end of file.
|
|     Error Conditions:
|       I/O errors are reported directly by the operating system.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Any carriage return and/or linefeed characters are stripped from
|     the buffer.
|       Character strings, integers, and real values may be accessed in
|     order from the local input buffer, after calling bfinc(), by
|     consecutive calls to alprdc(), bfgetc(), intrdc(), and relrdc(),
|     respectively.
|       After characters in the local buffer have been accessed once,
|     they are not available for access again.  The next access contin-
|     ues with succeeding characters.  Once all characters are exhausted
|     from the buffer, the eorchr character is returned instead.
|       If bfinc() is called again, before all characters in the local
|     input buffer have been accessed, any remaining characters from the
|     previous buffer are lost.
|       If bfinc() is expecting character (alpha) information from the
|     user, then any identifiable character (such as '#') may be used
|     for eorchr.  If bfinc() is expecting numeric information from the
|     user, then eorchr='/' can be used with the FORTRAN significance of
|     keeping the default value.  See intrdc() and relrdc() for further
|     information.
|       If the input data contains the special "help" character (?),
|     then bfinc() returns nogo=1.  If the input data contains the
|     special "oops" character (!), then bfinc returns nogo=2.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  int bfinc(char *eorchr)
#else
  int bfinc(eorchr)
  char *eorchr;
#endif
{
  char *jchar, *kchar;
  int   lun, luneof;

/* Initialize. */
  clrplc();
  EOR = *eorchr;
  luneof = FALSE;
  inbufr[0] = '\0';
  inloc = inbufr;

/* Issue a newline to the echo file if needed. */
  if (crlf) {
    if ((lunrd > 0) ||  (! intact)) {
      if (luneco == lunio) {
        bfputc("\n");
        ipen = (++ipen) % imax;
        if (ipen == 0) {
          ipen = line0 + imin;
          ++line0;
          if (line0 >= imax) line0 -= imax;
        }
        jpen = 0;
        textq[ipen][0] = '\0';
      } else if (luneco == lunpr) {
      } else if (luneco == lunwr) {
      } else if (luneco > 0) {
        putc('\n', streams[luneco]);
      }
    }

/* Issue a newline to the print file if needed. */
    if (lunpr > 0) putc('\n', streams[lunpr]);
  }

/* Read a buffer from the active input. */
# ifdef __WATCOMC__
    {
# else
    if ((dspdvc == DT_GRAPHIC) && (lunrd <= 0)) {
      xrdlnc();                                       /* Read from X. */
    } else {
# endif
    if (lunrd > 0) {
      lun = lunrd;
    } else if (lunin > 0) {
      lun = lunin;
    } else {
      lun = lunitc("input");
    }
    if (fgets(inbufr, MXINBF, streams[lun]) == NULL) inbufr[0] = '\0';
    if (feof(streams[lun])) luneof = TRUE;
  }

/* Guard against <cr> or <lf> in buffer. */
  for (jchar=kchar=inbufr; *jchar; jchar++) {
    if ((*jchar != '\r') && (*jchar != '\n')) *kchar++ = *jchar;
  }
  *kchar = *jchar;

/* Echo the line read to the screen if appropriate. */
  if ((!intact) || (lunrd > 0)) {
    if (luneco == lunio){
      bfputc(inbufr);
    } else if (luneco == lunpr) {
    } else if (luneco == lunwr) {
    } else if (luneco > 0) {
      fprintf(streams[luneco], "%s", inbufr);
    }
  }

/* Echo the line read to the print file if active. */
  if (lunpr > 0) fprintf(streams[lunpr], "%s", inbufr);

/* Echo the line read to the log file if active. */
  if (lunwr > 0) fprintf(streams[lunwr], "%s\n", inbufr);

/* Set inmax to the number of characters in the buffer. */
  if ((inmax = strlen(inbufr)) == 0) {
    inbufr[0] = EOR;
    inbufr[1] = '\0';
    inmax = 1;
  }
  crlf = TRUE;

/* Take special returns for 'help(?)' or 'oops(!)' keys. */
  if (strchr(inbufr, CHELP)) return(1);
  if (strchr(inbufr, COOPS)) return(2);
  if (luneof) return(-1);
  return(0);
}
