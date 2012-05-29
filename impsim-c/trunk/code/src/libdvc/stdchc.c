/* ------------------------------------------------------------------ */
/* stdchc-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Set the display device for hardware generated characters in
|     succeeding text.
|
|     Access:
|       (void) stdchc(int nsize);
|     int nsize,i-An integer code specifying desired character size:
|       nsize =-3 for the         smallest hardware characters.
|       nsize =-2 for the next to smallest hardware characters.
|       nsize =-1 for the next    smaller  hardware characters.
|       nsize = 0 for     standard size    hardware characters.
|       nsize = 1 for the next    larger   hardware characters.
|       nsize = 2 for the next to largest  hardware characters.
|       nsize = 3 for the         largest  hardware characters.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Stroke generated characters on the graphic display device may be
|     requested by calling chsizc().
|       If the requested nsize is not available through hardware gener-
|     ated characters, then nsize = 0 is used.  If hardware characters
|     are not available at all, then stroke generated characters are
|     used.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void stdchc(int nsize)
#else
  void stdchc(nsize)
  int  nsize;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
    real   factor, high, wide;
    struct videoconfig vc;
# else
#   include "xglblc.h"
# endif
    char *new_text_buff, **new_textq; 
    int  *new_text_color;
    int  i, line, new_ipen, new_imax, new_jmax, num_lines;

/* Finish former use of stroke-generated characters. */
  if (lunsmb) {
    if (lunsmb < 0) lunsmb = -lunsmb;
    fclose(streams[lunsmb]);
    streams[lunsmb] = (FILE *) NULL;
  }
  lunsmb = 0;

/* Set new character size and spacing parameters. */
  if (dspdvc == DT_GRAPHIC) {
#   ifdef __WATCOMC__
      _getvideoconfig(&vc);
      new_imax = vc.numtextrows;
      new_jmax = vc.numtextcols;
      factor = (1.0 - 0.15 * (real) nsize);
      high = factor / new_imax;
      wide = factor / new_jmax;
      _setcharsize_w(0.9 * high, wide);
      _setcharspacing_w(0.1 * wide);
      _settextpath(_PATH_RIGHT);
      _settextwindow(1, 1, new_imax, new_jmax);
#   else
      new_imax = (ypix / font_height);
      new_jmax = MXIOBF;
#   endif
  } else {
    new_imax = MXLINE;
    new_jmax = MXIOBF;
  }
  
/* Make a new text buffer if needed. */
  if (new_imax != imax) {
    new_text_buff  = (char *)  malloc( new_imax * (MXIOBF + 1));
    new_textq      = (char **) malloc( new_imax * sizeof(char *));
    new_text_color = (int  *)  malloc( new_imax * sizeof(int));
    if ((! new_text_buff) || (! new_textq) || (! new_text_color)) {
      fprintf(stderr, "Fatal error in stdchc: Out of memory.\n");
      exit(0);
    }
    for (i=0; i<new_imax; i++) {
      new_textq[i]      = &(new_text_buff[i * (MXIOBF+1)]);
      new_textq[i][0]   = '\0';
      new_text_color[i] = kfrgnd;
    }
  
/* Now recopy old text buffer (as much as possible). */
    num_lines = ipen - line0 - imin + 1;
    if (num_lines > new_imax) {
      line0 += (num_lines - new_imax);
      if (line0 >= imax) line0 -= imax;
    }
    if (line0 < 0) line0 += imax;
    line = line0;
    new_ipen = imin;
    for (i=0; i<new_imax; i++) {
      strcpy(new_textq[i], textq[line]);
      new_text_color[i] = text_color[line];
      if (line == ipen){
        new_ipen = i;
        break;
      }
      line = (++line) % imax;
      if (line == line0) break;
    } 
 
/* Free old text buffer and queue and reset to new. */ 
    free(text_buff);
    free(textq);
    free(text_color);
    text_buff  = new_text_buff;
    textq      = new_textq;
    text_color = new_text_color;
 
/* Reset line0, ipen, imax, jmax. */ 
    line0 = 0;
    ipen  = new_ipen;
    ipen  = min(ipen, new_imax - 1);
    imax  = new_imax;
    jmax  = new_jmax;
  }

/* Reset screen symbol size. */
  ssymbl = 1.0 / jmax;
  tsymbl = 1.0 / imax;
  return;
}
