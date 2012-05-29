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
/* clearc-01 Jan 00:12 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Initialize the IMP data structure for a new model.
|
|     Access:
|       (void) clearc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The clearc function is always called as IMP first enters
|     execution.  It may also be activated by the CLEAR command to
|     reinitialize for a new problem after completion of another.
|       On reinitialization, only the system model is cleared.  Terminal
|     and host parameters such as the interactivity flag and display
|     device type are not reset to defaults.
*
*     History:
*     01 Jan 00:JJU-Original.
*     29 Sep 00:JJU-Modified idfile[] names for networked DOS systems.
*     11 Jul 07:JJU-Renamed LINK records to type BODY records.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void clearc()
{
  char release[12] = "01 Jan 2009";
  int i, lun;

/* Finish and close any previous files. */
  endsvc();
  readrc("close");
  for (i=0; i<3; i++) {
    lun = lunfil[i];
    if (lun > 0) {
/*    if (i < 2) remove(idfile[i]); */
      if (streams[lun] != NULL) fclose(streams[lun]);
      streams[lun] = NULL;
      free (idfile[i]);
    };
    lunfil[i] = 0;
    idfile[i] = (char *) malloc(MXFLCH+1);
  };
/* For networked DOS systems, IMP may be executing from a drive which */
/*   does not have read/write (w+) privileges as needed for idfile[]! */
# ifdef __WATCOMC__
    strcpy(idfile[0], "C:\\TEMP\\list.imp");
    strcpy(idfile[1], "C:\\TEMP\\plot.imp");
# else
    strcpy(idfile[0], "list.imp");
    strcpy(idfile[1], "plot.imp");
# endif
  idfile[2] = "\0";

/* Print a banner at the top of the output. */
  bannrc("Integrated Mechanisms Program (IMP-2009)", release, "1971");

/* Clear the IMP data structure. */
  System.type    = SYSTEM;
  strncpy(System.base, "BASE", MAXCHR);
  System.base[MAXCHR] = '\0';
  System.sysVal  = NULL;
  System.sysBdy  = NULL;
  System.ground  = NULL;
  System.sysJnt  = NULL;
  System.sysSld  = NULL;
  System.sysSpg  = NULL;
  System.sysDmp  = NULL;
  System.sysCnt  = NULL;
  System.sysReq  = NULL;
  System.title   = NULL;
  System.mode    = MD_GEO;
  System.echo    = 0;        
  System.nerror  = 0;
  System.level   = 0;
  System.hold    = FALSE;
  System.xeqflags= 0;
  System.nbdys   = 0;
  System.nsolids = 0;
  System.njnts   = 0;
  System.njvars  = 0;
  System.nloops  = 0;
  System.ndof    = 0;
  System.nsgc    = 0;
  System.nfgc    = 0;
  System.ndep    = 0;
  System.nfree   = 0;
  System.nc      = 0;
  System.ci      = 0;
  System.cn      = 20;
  System.ei      = 0;
  System.en      = 25;
  System.mrank   = 0;
  System.krank   = 0;
  System.impacteq[0]=IM_UNDEF;
  System.impacteq[1]=IM_UNDEF;
  System.impacteq[2]=IM_UNDEF;
  System.lscale  = 1.0;                 
  System.ascale  = 180.0/PI;                   /* Degrees per radian. */
  System.dtoll   = 1.0e-4;
  System.dtola   = System.dtoll/System.ascale;
  System.ptoll   = 1.0e-5;
  System.ptola   = System.ptoll/System.ascale;
  System.etoll   = 1.0e-3;
  System.etola   = System.etoll/System.ascale;
  System.fintol  = 1.0e-4;
  System.fjtol   = 1.0e-7;
  System.dytol   = 1.0e-5;
  System.fktol   = 1.0e-5;
  System.ferr    = 0.1;
  System.pferr   = 0.01;
  System.zero    = 1.0e-6;
  System.gc      = 0.00259008309;/*US customary units:lbf.sec^2/lbm.in*/
  ldnanc((void *) &System.qi);
  System.sysJ    = NULL;
  System.d1      = NULL;
  System.d2      = NULL;
  System.pd      = NULL;
  ldnanc((void *) &System.gravty[0]);
  ldnanc((void *) &System.gravty[1]);
  ldnanc((void *) &System.gravty[2]);
  ldnanc((void *) &System.tprev);
  ldnanc((void *) &System.t);
  ldnanc((void *) &System.tnxtio);
  ldnanc((void *) &System.tfinal);
  ldnanc((void *) &System.dt);
  ldnanc((void *) &System.dtmin);
  ldnanc((void *) &System.dtmax);
  ldnanc((void *) &System.dtio);
  ldttlc("\0");                           /* Cancel the system title. */
  return;
}
