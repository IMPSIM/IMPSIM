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
/* endc-01 Jan 00:26 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Wrapup IMP execution per particular instalation requirements.
|
|     Access:
|       void endc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Execution of IMP is halted in this routine; control is not
|     returned to the calling routine.
|       The applications programmer may wish to modify this routine to
|     meet individual needs.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void endc()
{
  int i;

/* Wrap up all files. */
  for (i=0; i<3; i++){
    fclose(streams[lunfil[i]]); /* Close list, plot, and store files. */
    streams[lunfil[i]] = NULL;
    lunfil[i] = 0;
    if (idfile[i] != NULL){
/*    if (i<2)remove(idfile[i]);*/ /* Delete old list and plot files. */
      idfile[i] = "\0"; /* Free old list, plot, and store file names. */
    }
  }
  endsvc();       /* Deactivate any store:input or recall:input file. */ 
  readrc("close");                    /* Close any recall:input file. */
  writrc("close");                     /* Close any store:input file. */
  echonc(0);                /* Terminate any echo of input data read. */
  vclosc();                            /* Close any stored view file. */
  finplc();                  /* Terminate any libcad input or output. */
  exit(EXIT_SUCCESS); /* Terminate the current IMP program execution. */
}
