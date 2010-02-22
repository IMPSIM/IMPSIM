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
/* dynmxc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       Control the time integration process for dynamic mode.
|
|     Access:
|       (void) dynmxc();
|
|     Error Conditions:
|       System.nerror==3  indicates a singular mass matrix.
|       System.nerror==4  indicates that normal modes could not be found
|       System.nerror==5  indicates a singular matrix of eigenvectors.
|       System.nerror==10 indicates failure in loop closure.
|
|     Comments:
|       The method of time integration is not a classical technique.  It
|     has been developed specially for the IMP class of problems.
|     Further discussion may be found in the IMP user's manual, Chapter
|     1, and associated references.
|       If force error(s) is detected or if an impact is bypassed or not
|     hit exactly during the time step, then the time step interval is
|     reduced and, depending on severity, the time step may be repeated.
|       If loop closure is not achieved at some timestep, then the time
|     step interval is decreased and the step is attempted again.
|       Time integration may be interrupted by the user by striking the
|     keyboard interrupt (<CTRL> C).  This causes time integration to
|     halt at the completion of the time step being performed, and
|     return to the calling program.
|       Early interruption of time integration may also result from the
|     RETURN or END options being returned from a VALUE function.
|       A warning message is printed if the system stiffness matrix
|     becomes singular; execution continues.
*
*     History:
*     01 Jan 00:JJU-Original.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void dynmxc()
{
  Contact *cntact;
  complex *Dyn, *Eigvct, *W, *Z;
  int     *bloksz, collide, loc, i, *icol, ii, iii, *irow, j, k, lpass1, 
            *mult, nblock, *ndef, *ndfloc, nerr, *next, nfgc, nkol, 
            nsquar, nxt, n2;
  real    *delnrm, detM, divisor, firsthit, force, *D, *G, *K, *M, 
            *MDKG, percnt, *supdiag, *sm, timex, vA[3], vAB[3], vB[3];

/* Initialize. */  
  Eigvct = NULL;
  lpass1 = TRUE;
  nfgc   = 0;
  ldnanc((void *) &firsthit);
  ldnanc((void *) &timex);
  vzeroc(F_ALL);
  if (isnanc((void *) &System.t)) {  /* Test if reenter or new start. */
    System.t = 0.0;
    icsetc();                          /* Set the initial conditions. */
    if (System.nerror) return;
  }

/* Set the timing information. */
  System.dt     = System.dtmin;
  System.tnxtio = System.dtio * ceil(System.t / System.dtio);
  System.t      = System.tnxtio;
  System.tprev  = System.t - System.dt;

/* Perform the time integration of the equations of motion. */
  do {
    if (qkbic()) break;
    if (!isnanc((void *) &firsthit)) {
      if (System.t > firsthit) ldnanc((void *) &firsthit);
    }
    vzeroc(F_ALL);
    msetc();                 /* Set any user specified motion inputs. */
    if (System.nerror) break;
    adjstc();
    closec();                                 /* Assemble the system. */
    if (System.nerror) {                        /* If not closed, ... */
      if (System.t <= 0.0) break;
      goto _REPEAT;
    }
    System.nfree = System.njvars - System.nsgc;

/* Begin collision detection and impact dynamics. */
    if (!lpass1) {
      ldnanc((void *) &timex); 
      collide = FALSE;
      for (cntact=System.sysCnt; cntact; cntact=cntact->nxtCnt) {  
	collide = intfnc(cntact);             /* Check for collision. */
	if (collide) {
	  if (System.dt > System.dtmin) {    /* Refine the time step. */
	    firsthit = System.t; 
	    goto _REPEAT;
	  } else {                       /* System.dt = System.dtmin  */
	    if (qcrgnc(cntact)) {             /* First contact found. */
	      if (qntbc(cntact)) {                     /* Usual case. */
                mpydrc(cntact->cnSldA->sldBdy->W, cntact->cnpoint, vA);
                mpydrc(cntact->cnSldB->sldBdy->W, cntact->cnpoint, vB);
		for (i=0; i<3; i++) {
		  vAB[i] = vA[i] - vB[i];   /* Get relative velocity. */
		}
                if (vdotc(3, vAB, cntact->cnnormal) <= System.zero) {
		  ldnanc((void *) &firsthit); /* Points moving apart. */
		  collide = FALSE;
		} else {      /* Points are moving toward each other. */
		  firsthit = System.t;     /* Collision has occurred. */
		  break;                /* Break out of the for loop. */
		}
	      } else {                /* Degenerate case; do nothing. */
		ldnanc((void *) &firsthit);
		collide = FALSE;
	      }
	    } else {                       /* Collision has occurred. */
	      firsthit = System.t;
	      break;                    /* Break out of the for loop. */
	    }       
	  }
        } else {                        /* Bodies do not yet collide. */
	  qhtimc(cntact, cntact->pln_pntA, cntact->pln_pntB);
	  if (cntact->timex < timex) timex = cntact->timex;  
	}
      }
      if (collide) {     
	if (System.dt > System.dtmin ) {
	  firsthit = System.t; 
	  goto _REPEAT;
	
/* If the contact type is defined , do impact dynamics. */   
	} else if (qcrgnc(cntact)) { 
	  hdsgc();
	  hdfgc();
	  procsc();
          if (qbitc(XQ_ANMAT, (void *) &System.xeqflags)) drawc();
	  if (qntbc(cntact)) {
	    cntact->Rp = qcnRpc(cntact->CR, cntact->numcr, 
              cntact->cnpoint);
	    impctc(cntact);
	    hdsgc();
	    hdfgc();
	    procsc();
	    ldnanc((void *) &firsthit);
	    System.dt = System.dtmin;
	  }

/* If the time step is large, refine the time step and go back. */
	} else if (System.dt > System.dtmin) {
	  firsthit = System.t; 
	  goto _REPEAT; 
	} else {                             
	  for (i=0; i<3; i++) {
	    cntact->CR[0][i]   = cntact->pln_pntA[i];
            cntact->cnpoint[i] = cntact->pln_pntA[i];
            cntact->cnnormal[i]= cntact->pln_pntB[i] 
			       - cntact->pln_pntA[i];
	  }
	  cntact->numcr = 1;
          vnormc(3, cntact->cnnormal);
	  hdsgc();
	  hdfgc();
	  procsc();
          if (qbitc(XQ_ANMAT, (void *) &System.xeqflags)) drawc();
	  impctc(cntact);
	  hdsgc();
	  hdfgc();
	  procsc();
	  ldnanc((void *) &firsthit);
	  System.dt = System.dtmin;
	}
      }
    }              /* End of collision detection and impact dynamics. */

/* Obtain working space for normal mode calculations. */
    if (System.nfgc > 0) {
      if (System.nfgc != nfgc) {
	nfgc   = System.nfgc;
	n2     = nfgc + nfgc;
	nkol   = n2 + nfgc + 1;
	nsquar = nfgc * nfgc;
	if (Eigvct) {
	  free (bloksz);
	  free (icol);
	  free (irow);
	  free (mult);
	  free (ndef);
	  free (ndfloc);
	  free (next);
	  free (D);
	  free (G);
	  free (K);
	  free (M);
	  free (MDKG);
	  free (delnrm);
	  free (supdiag);
	  free (sm);
	  free (Dyn);
	  free (W);
	  free (Z);
	  free (Eigvct);
	}
	bloksz = (int *)     calloc(n2,        sizeof(int));
	icol   = (int *)     calloc(nkol,      sizeof(int));
	irow   = (int *)     calloc(nfgc,      sizeof(int));
	mult   = (int *)     calloc(n2,        sizeof(int));
	ndef   = (int *)     calloc(n2,        sizeof(int));
	ndfloc = (int *)     calloc(n2,        sizeof(int));
	next   = (int *)     calloc(n2,        sizeof(int));
	D      = (real *)    calloc(nsquar,    sizeof(real));
	G      = (real *)    calloc(nfgc,      sizeof(real));
	K      = (real *)    calloc(nsquar,    sizeof(real));
	M      = (real *)    calloc(nsquar,    sizeof(real));
	MDKG   = (real *)    calloc(nfgc*nkol, sizeof(real));
	delnrm = (real *)    calloc(n2,        sizeof(real));
	supdiag= (real *)    calloc(n2,        sizeof(real));
	sm     = (real *)    calloc(n2,        sizeof(real));
	Dyn    = (complex *) calloc(n2*n2,     sizeof(complex));
	W      = (complex *) calloc(n2,        sizeof(complex));
	Z      = (complex *) calloc(n2*n2,     sizeof(complex));
	Eigvct = (complex *) calloc(n2*n2,     sizeof(complex));
      }
    }

/* Set the sizes of any variable dampers, springs, and/or forces. */
    dsetc();
    if (System.nerror) break;
    ksetc();
    if (System.nerror) break;
    fsetc();
    if (System.nerror) break;

/* Form the mass, stiffness, damping, and generalized force matrices. */
    if (System.nfgc > 0) {
      massc(nfgc, M);
      cmatc(nfgc, D);
      kmatc(nfgc, K);
      gforc(nfgc, G);

/* First assume that time step is controlled by force imbalance. */
/*   Otherwise, time step is controlled by collision. */
      if (lpass1) {
	lpass1 = FALSE;
      } else {
        if (isnanc((void *) &firsthit)) {  /* Check for no collision. */
	  fchekc(nfgc, M, D, G, &force, &percnt);
	  if ((force > 1.5*System.ferr) && (percnt > 1.5*System.pferr)){
	    if (System.dt > (System.dtmin + System.zero)) {
	      resetc(System.njvars);      /* Backup to previous time. */
	      closec();                                /* Reassemble. */
	      System.dt = max(((System.pferr / percnt) * System.dt),
		System.dtmin);
	      goto _STEP;
	    }
	  }
	  if ((force < 0.5*System.ferr) || (percnt < 0.5*System.pferr)){
	    System.dt = min((2.0*System.dt), (System.tnxtio-System.t));
	    System.dt = max( System.dt, System.dtmin);
	  } else if ((force > System.ferr) || (percnt > System.pferr)) {
	    System.dt = max((0.5 * System.dt), System.dtmin);
	  }
	}
      }

/* Copy mass, damping, stiffness, and force matrices into MDKG. */
      for (i=0; i<nfgc; i++) {
	ii  = i * nfgc;
	iii = i * nkol;
	for (j=0; j<nfgc; j++) {
	  MDKG[iii+     j]  = M[ii+j];
	  MDKG[iii+nfgc+j]  = D[ii+j];
	  MDKG[iii+n2  +j]  = K[ii+j];
	}
	  MDKG[iii+n2+nfgc] = G[i];
      }

/* Invert the mass matrix. */
      invrtc(MDKG, nfgc, nkol, nfgc, System.dytol, &System.mrank, &detM, 
	irow, icol);
      if (System.mrank != nfgc) {
	hdsgc();
	hdfgc();
	textc("*** The mass matrix is singular. ***", TRUE);
	textc("*** Only ", FALSE);
        itextc(System.mrank);
	textc(" of the FGC's exhibit inertia. ***", TRUE);
	System.nerror = 3;
	break;
      }

/* Form the corrected generalized accelerations. */
      dynm1c(nfgc, MDKG, icol);
      acc();
    }
    pvsetc();

/* Print the requested results. */
    if (System.t >= System.tnxtio) {
      hdsgc();
      hdfgc();
      procsc();
      if (qbitc(XQ_ANMAT, (void *) &System.xeqflags)) drawc();
      System.tnxtio = min((System.tnxtio + System.dtio), System.tfinal);
    }

/* Form the normal modes. */
    if (System.nfgc > 0) {
      dynm2c(nfgc, MDKG, irow, Dyn);
      nerr = jnfc(n2, 7, 1.0e-8, 1.0e-6, Dyn, Z, W, supdiag, next, mult, 
	ndef, ndfloc, &nblock, delnrm, sm);
      if (nerr) {
	hdsgc();
	hdfgc();
	textc("*** Normal modes could not be found. ***", TRUE);
	System.nerror = 4;
	break;             /* Break out of the time integration loop. */
      }

/* Copy and rearrange the principal vectors. */
      for(i=0;i<n2; i++) {
	for (j=0; j<n2;j++) {
	  Eigvct[i*n2+j].r = Z[j*n2+i].r;
	  Eigvct[i*n2+j].i = Z[j*n2+i].i;
	}
      }
      for (i=0; i<n2; i++) bloksz[i] = 0;
      nblock = 0;
      j = 0;
      for (i=0; i<n2; i++) {
	if (next[i] != -1) {            /* Vector is not yet visited. */
	  loc = i;
	  divisor = 1.0;
	  do {
	    nxt = next[loc] - 1;
	    for (k=0; k<n2; k++) {     /* Copy the principle vectors. */
	      Eigvct[k*n2+j].r = Z[loc*n2+k].r / divisor;
	      Eigvct[k*n2+j].i = Z[loc*n2+k].i / divisor;
	    }
	    next[loc] = -1;                       /* Mark as visited. */
	    j++;
	    (bloksz[nblock])++;
	    divisor *= supdiag[loc];
	  } while ((loc = nxt) != -1);       /* Go through the chain. */
	  nblock++;                /* Increment the number of blocks. */
	}
      }
    }
    System.tprev = System.t;  /* Reset the known valid solution time. */
    if (System.t >= System.tfinal) break;   /* Exit integration loop. */
    goto _STEP;

/* Backup, decrease time step increment, and repeat the step. */
_REPEAT:
    System.nerror = 0;
    resetc(System.njvars);            /* Backup to previous position. */
    closec();                                          /* Reassemble. */
    if (System.dt <= System.dtmin) break;    /* Cannot decrease step. */
    System.dt = max(0.5 * System.dt, System.dtmin);/* Half time step. */

/* Increment the time. */
_STEP:
    System.t  = min(System.tprev + System.dt, System.tnxtio);
    System.dt = max(System.t - System.tprev,  System.dtmin );
   
/* Update the fgc's for this time step. */
    if (System.nfgc > 0) {
      vzeroc(F_TIME);
      nerr = dynm3c(System.dt, Eigvct, W, MDKG, nblock, bloksz, icol);
      if (nerr) {
	System.nerror = 5;         /* Eigenvector matrix is singular. */
	break;             /* Break out of the time integration loop. */
      }
      System.level = 7;
      acc();
    }
  } while (System.t <= System.tfinal);

/* Return working space. */
  free (Dyn);
  free (W);
  free (Z);
  free (Eigvct);
  free (D);
  free (G);
  free (K);
  free (M);
  free (MDKG);
  free (delnrm);
  free (supdiag);
  free (sm);
  free (bloksz);
  free (icol);
  free (irow);
  free (mult);
  free (ndef);
  free (ndfloc);
  free (next);
  return;
}
