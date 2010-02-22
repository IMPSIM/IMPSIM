/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:11 Jul 09                                          |
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
/* libimp-01 Jan 00:17 Jan 04
|    (C)Copyright, JJU Research, 2000-2004.
* ------------------------------------------------------------------- */

#include "libimp.h"

/* System definition. */
struct system_tag System;        /* Data structure for the IMP model. */

/* filidc definitions. */
char *idfile[3];    /* Filenames for IMP list, plot, and store files. */
int   lunfil[3];   /* Stream numbers for list, plot, and store files. */

/* inputc definitions. */
int   ntokns = 0;           /* Number of tokens in last input record. */
Token token[MXTOKN];            /* Token values of last input record. */
