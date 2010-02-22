/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:10 Jun 09                                          |
|     (C) Copyright, JJU Research, 1984-2009.                          |
|                                                                      |
|     This material is released under the terms of the                 |
|     GNU General Public License, version 3 (GNU GPLv3).               |
|     The full text of that license is available from the 'IMPSim'     |
|     project site on Google Code.                                     |
|                                                                      |
|     This initial release of 'IMPSim' is equivalent to the            |
|     IMP Integrated Mechanisms Program (IMP-2009) and is released     |
|     with the full approval of JJU Research of Madison, WI.           |
|                                                                      |
* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------ */
/* iobfrc-01 Jan 00:23 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  IOBFRC_INCLUDED
  extern FILE  *streams[MXLUNS];              /* Stream i/o pointers. */
  extern char   inbufr[MXINBF+1];             /* Input buffer string. */
  extern char  *inloc; /* Pointer to next input character for access. */
  extern int    inmax;   /* Total number of characters read by bfinc. */
  extern int    kbwtch;     /* Flag set TRUE for watching interrupts. */
  extern int    kbint;      /* Flag set TRUE by a keyboard interrupt. */
  extern char   EOR;       /* Character used to detect end of record. */
  extern int    dfltline;       /* Flag set TRUE for slash (/) input. */
  extern int    crlf;     /* Flag set TRUE for newline on next textc. */
  extern int    line0;  /* Number of line in circular buffer textq(). */
  extern char **textq;   /* Array of pointers to output text strings. */
  extern char  *text_buff;         /* Buffer for output text strings. */
  extern int   *text_color;/*Array of colors for output text strings. */
# define IOBFRC_INCLUDED
#endif
