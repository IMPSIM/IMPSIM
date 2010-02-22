/* ------------------------------------------------------------------ */
/* bfopnc-01 Jan 00:10 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Open and initialize the local buffers to control direct
|     character i/o to or from the standard i/o devices, including the
|     display device.
|
|     Access:
|       (void) bfopnc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine sets the interaction flag to TRUE for interactive
|     execution and FALSE for background.
|       This routine also sets the keyboard interrupt flag to FALSE.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
void bfopnc()
{
  int   i;

/* Initialize the interactivity and keyboard interrupt flags. */
  intact = qiactc();
  kbint  = FALSE;

/* Open a channel to the standard input and output devices. */
  lunin  = lunitc("input");
  lunio  = lunitc("output");
  lunerr = lunitc("error");
  streams[lunin]  = stdin;
  streams[lunio]  = stdout;
  streams[lunerr] = stderr;

/* Set pointers into the local buffers. */
  crlf   = TRUE;
  inloc  = NULL;
  line0  = 0;
  imin   = (nhdrs > 0) ? ((nhdrs - 1) / MXHDRS + 1) : 0;
  ipen   = line0 + imin;    /* Present alpha pen location in textq[]. */
  jpen   = 0;
  imax   = MXLINE;                     /* Maximum alpha pen location. */
  jmax   = MXIOBF;
# ifndef __WATCOMC__
    if (dspdvc == DT_GRAPHIC) {
      if (X_Initialized) imax = ypix / font_height - 1;
      txt_drwn = FALSE;
      crsron   = FALSE;
    }
# endif

/* Get a buffer and circular queue of pointers for scrolling text. */
  text_buff  = (char *)  malloc(imax * (MXIOBF + 1));
  textq      = (char **) malloc(imax * sizeof(char *));
  text_color = (int *)   malloc(imax * sizeof(int));
  if ((! text_buff) || (! textq) || (! text_color)) {
    fprintf(stderr, "Fatal error in bfopnc: Out of memory.\n");
    exit(0);
  } 

/* Set up as initially all empty strings. */
  for (i=0; i<imax; i++) {
    textq[i]      = &(text_buff[i * (MXIOBF+1)]);
    textq[i][0]   = '\0';
    text_color[i] = kfrgnd;
  }
  return;
}
