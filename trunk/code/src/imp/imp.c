/* imp-01 Jan 00:10 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Disclaimer:
|       This is the Integrated Mechanisms Program (IMP-2009).  It  is  a
|     research and development system and is continuously being modified
|     and extended to new capabilities.  No claim is made, nor should be
|     implied  that the program is free of errors.   The user of the IMP
|     program retains full control over and is  solely  responsible  for
|     the  mechanical  design  of his equipment,  systems, and products.
|     Neither the authors,  JJU Research,  nor any  other  companies  or
|     individuals  involved  in  the  development or distribution of IMP
|     makes any warranty with respect  to  the  validity,  accuracy,  or
|     applicability of the IMP program, or its mechantability or fitness
|     for a particular purpose.
|
|  *********************************************************************
|  *                                                                   *
|  *                 The Integrated Mechanisms Program                 *
|  *              (A computer aided system for the design              *
|  *                  analysis of mechanical systems)                  *
|  *                             IMP - 2009                            *
|  *                                                                   *
|  *                                by:                                *
|  *                            JJU Research                           *
|  *                        1513 University Ave.                       *
|  *                   Madison, Wisconsin 53711, USA                   *
|  *                     Telephone: (608) 262-0225                     *
|  *                                                                   *
|  *********************************************************************
|
|     Description:
|       This is the main routine of the Integrated Mechanisms Program.
|       The  IMP system can perform the simulation of two- or three-dim-
|     ensional rigid-body articulated mechanical systems  having  single
|     or multiple degrees of freedom.
|       The system model may include rigid, revolute (pinned), prismatic
|     (sliding), spur gear, bevel gear, rack and pinion, screw (helical),
|     disk  cam,  planar  curved  slot,  cylindric,  universal,  planar,
|     spheric (ball and socket),  and open (no constraint) joints in any
|     open- or closed-loop combination.
|       Linear or non-linear springs and viscous  dampers  may  also  be
|     included,  either within joints or acting between specified points
|     on the moving bodies.
|       Mass (distributed) and gravity effects can be simulated.
|       The system can be driven either by applied forces  or  by  input
|     motions  which may be specified functions of time or of the system 
|     geometry.
|       The IMP system is capable of simulation in any of three  differ-
|     ent modes: kinematic (geometric), static (equilibrium), or dynamic
|     (time-response) mode.
|       In any of these modes,  IMP calculates the requested  positions,
|     velocities,  accelerations,  static and dynamic constraint forces,
|     natural frequencies, damping ratios,  and small oscillation trans-
|     fer functions (principal vibration modes) of the mechanical system
|     simulated.   
|       When executing in dynamic (time response) mode, IMP will monitor
|     specified  bodies with specified (solid model) shapes for possible
|     collision.   Upon contact, the proper momentum transfer is simula-
|     ted and execution continues.
|       Also in any mode, animated drawings can be produced if appropri-
|     ate body shapes are defined; these may be solid models.
|
|     Access:
|       imp
|
|     Error Conditions:
|       Errors are tested for internally and  appropriate  messages  are
|     printed.  Most errors are non-fatal and may be corrected interact-
|     ively allowing the simulation to continue.
|
|     Comments:
|       Refer to the IMP Users Manual,  especially Chapter 1,  for  more
|     detailed discussion of system operation and capabilities.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

# include "libimp.h"
extern int main(int argc, char *argv[])
{
  char mode[5];
  int  done, i, lflag, lun;

/* Initialize. */
  devic("alpha");
  if (qiactc()) {
    lun = 0;
  } else {
    lun = lunitc("output");
  }
  echonc(lun);
  clearc();
  beginc();

/* Read and interpret the IMP language input. */
  done = FALSE;
  while (!done) {/* Continue user input until 'end' sets done = TRUE. */
    intrpc();

/* Print the output banner. */
    lflag = qbitc(XQ_ANMAT, (void *) &System.xeqflags);
    hdngc(lflag);

/* Preprocess the system model per the mode setting. */
    switch (System.mode) {
      case MD_DYN:
        strcpy(mode, "DYN.");
        break;
      case MD_STAT:
        strcpy(mode, "STAT");
        break;
      default:
        strcpy(mode, "KIN.");
        System.mode = MD_KIN;
    }
    post1c();
    for (i=0; i<3; i++) {  /* Write mode to list, plot & store files. */
      lun = lunfil[i];
      if (lun > 0) fprintf(streams[lun],
        " %4s ----    0 %#19.10e %#19.10e %#19.10e\n", mode, 0.0, 0.0,
        0.0);
    }

/* Execute the IMP analysis. */
    if (System.nerror == 0) xecutc();

/* Output any requested transfer functions. */
    if ((System.level >= 7) && (System.nerror == 0)) tfunc();

/* Post-process the output and maybe reset the reference position. */
    post0c();
  }
  exit(EXIT_SUCCESS);
  return(0);  /* Avoid Watcom compiler warning for 'no return value'. */
}
/* ------------------------------------------------------------------ */
/* userc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Special IMP function to be coded by the user to supply Values
|     not describeable through the IMP language.
|
|     Access:
|       userval = (real) userc(Word name, real t, int nderiv);
|     Word name,   i-Name specified in the reference.
|     real t,      i-Value of time (or position number).
|     int  nderiv, i-Number of the derivative being sought: nderiv = 0
|                      for value; nderiv = 1 for 1st time derivative; 
|                      nderiv = 2 for 2nd time derivative.
|     real userval,o-Numeric value of the user defined function (or its
|                      nderiv derivative).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This function provides a skeleton model for the form of userc
|     functions which the user may wish to write.
|       This function should return userval = NaN (set by ldnanc) for
|     a case which is indeterminate or in which an error is discovered.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  real userc(Word name, real t, int nderiv)
#else
  real userc(name, t, nderiv)
  Word name;
  real t;
  int  nderiv;
#endif
{
  real userval;

  ldnanc((void *) &userval);
  return(userval);
}
