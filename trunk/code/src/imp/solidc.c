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
/* solidc-01 Jan 00:02 Feb 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Treat a READ SOLID statement.
|
|     Access:
|       (void) solidc(name);
|     Word name,i-Name of the Solid to be read.
|
|     Error Conditions:
|       System.nerror = 3 indicates a missing shape file.
|       System.nerror = 4 indicates a  faulty shape file format.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     06 Jul 03:JJU-Set datime string to 20 chars for 2xxx dates.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void solidc()
{
  Solid *solid;
  char   datime[21], fileid[MXFLCH] = "\0";
  int    lun;

  flnamc(3, fileid);      /* Look for the filename and open the file. */
  if (lenc(fileid) > 0) {
  } else if (qiactc()) {
    echoc();
    textc("Enter the shape file name: > ", FALSE);
    if (bfinc(" ")) return;
    bfgetc(fileid);
    if (fileid[0] == '!') goto DONE;
    if (lenc(fileid) <= 0) goto DONE;
  } else {
    echoc();
    textc("*** Error: There is no shape file specified. ***", TRUE);
    System.nerror = 3;
    goto DONE;
  }
  lun = lunitc("file");
  streams[lun] = fopen(fileid, "r");
  solid = NULL;
  if (streams[lun] == NULL) {
    echoc();
    textc("*** Error in opening file '", FALSE);
    textc(fileid, FALSE);
    textc("'. ***", TRUE);
    System.nerror = 3;
  } else if (strstr(fileid, ".geo")) {     /* Read a ******.geo file. */
    rdgeoc(lun, System.ground, solid, datime);
  } else if (strstr(fileid, ".stl")) {     /* Read a ******.stl file. */
    rdstlc(lun, System.ground, solid);
  } else {
    echoc();
    textc("*** Error: IMP does not know this file format. ***", TRUE);
    System.nerror = 4;
  }
DONE:
  return;
}
