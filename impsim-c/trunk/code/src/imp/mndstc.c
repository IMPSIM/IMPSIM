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
/* mndstc-01 Jan 00:13 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       This function finds the minimum distance between two specified 
|     solids.  
|
|     Access:
|       distnc = (real) mndstc(Solid *solidA, Solid *solidB, 
|         real plndir[3], real RA[3], real RB[3], Vertex *nrVtxs[4][2], 
|         real lambda[4], int *nVtxs);
|     Solid  *solidA,      i-Solid following the monitored contact.
|     Solid  *solidB,      i-Solid preceding the monitored contact.
|     real    plndir[3],   o-Plane direction vector between the Solids.
|     real    RA[3],       o-Global coords of point following contact.
|     real    RB[3],       o-Global coords of point preceding contact.
|     Vertex *nrVtxs[4][2],o-Cached list of Vertex pairs near contact.
|     real    lambda[4],   o-Parameter values for nrVtxs[i] distances.
|     int    *nVtxs,       o-Number of Vertex pairs in nrVtxs[i][2].
|     real    distnc,      o-Minimum distance found for this Contact.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine computes the Euclidean distance between two poly-
|     topes in 3-D using a modified Barr-Gilbert algorithm detailed in 
|     the following reference:
|       E.G.Gilbert, D.W.Johnson and S.S.Keerthi, "A Fast Procedure for
|       Computing the Distance Between Complex Objects in Three Space," 
|       Report RSD-TR-26-86, Center for Research On Integrated Manufac-
|       turing, College of Engineering, The University of Michigan,
|       Oct. 1986.
|     Each of the two polytopes should be described as the convex hull
|     of a finite set of points in 3-D.
|       Very simply stated, the algorithm starts with an initial approx-
|     imate solution, goes through many cycles (in each cycle it 
|     improves the solution by decreasing the distance between the 
|     objects), and terminates when a stopping criterion is satisfied.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  real mndstc(Solid *solidA, Solid *solidB, real plndir[3], real RA[3], 
		real RB[3], Vertex *nrVtxs[4][2], real lambda[4], 
		int *nVtxs)
#else
  real mndstc(solidA, solidB, plndir, RA, RB, nrVtxs, lambda, nVtxs)
  Solid  *solidA, *solidB;
  real   plndir[3], RA[3], RB[3];
  Vertex *nrVtxs[4][2];
  real   lambda[4];
  int    *nVtxs;
#endif
{
  Vertex *vtxA, *vtxB;
  int     i, irs[4], j, jrs[4], lbakup, lpass, nvxs, nvxsold;
  real    als[4], Cp[3], del[16], dstsq, Gp, neg_Vk[3], olddstsq, 
            temp[3], v[4][3], Vk[3], y[12];

/* Initialize. */
  if (*nVtxs == 0) {
    *nVtxs = 1;
    for (i=0; i<3; i++) {
      temp[i] = solidA->bs_ctr[i] - solidB->bs_ctr[i];
    }
    dstABc(solidA, solidB, temp, v[1], &(nrVtxs[0][0]),
      &(nrVtxs[0][1]));
  }
  lpass  = FALSE;
  lbakup = FALSE;
  nvxs   = *nVtxs;
  ldnanc((void *) &olddstsq);

/* Iterate over all simplexes. */
  do {
    for (i=0; i<nvxs; i++) {
      irs[i] = i;
      jrs[i] = i;
      mpyxrc(solidA->sldBdy->T0j, (nrVtxs[i][0])->coord, v[i]);
      mpyxrc(solidB->sldBdy->T0j, (nrVtxs[i][1])->coord, temp);
      for (j=0; j<3; j++) {
	v[i][j] -= temp[j];
	y[i*3+j] = v[i][j];
      }
    }
    for (i=0; i<nvxs; i++) {
      for (j=0; j<=i; j++) {
	del[j*4+i] = del[i*4+j] = vdotc(3, v[i], v[j]);
      }
    }
    nvxsold = nvxs;               /* Save the old number of vertices. */

/* Compute the distance to the simplex. */
    sldstc(&nvxs, irs, jrs, y, del, Vk, als, &dstsq, &lbakup);
  
/* Compute Gp. */
    for (i=0; i<3; i++) {neg_Vk[i] = -Vk[i];}
    Gp = vdotc(3, Vk, Vk) + dstABc(solidA, solidB, neg_Vk, Cp, &vtxA, 
      &vtxB); 
    if (fabs(Gp) < 2.0e-10) {
      lpass = TRUE;                              /* We have solution. */
    } else {                                      /* No solution yet. */
      if ((dstsq < olddstsq) && (nvxs < 4)) {      /* Subset is okay. */
	for (i=0; i<nvxs; i++) {                /* Rearrange the set. */
	  if (irs[i] != i) {
	    nrVtxs[i][0] = nrVtxs[irs[i]][0];
	    nrVtxs[i][1] = nrVtxs[irs[i]][1];
	  }
	}
        nrVtxs[nvxs][0] = vtxA;         /* Add the additional vertex. */
        nrVtxs[nvxs][1] = vtxB;
	nvxs++;
	olddstsq = dstsq;
      } else {                                 /* Subset is not okay. */
	if (!lbakup) {        /* Backup subalgorithm is not used yet. */
	  lbakup = TRUE;                        /* Rerun with backup. */
	  nvxs = nvxsold;
	} else {        /* Backup subalgorithm has already been used. */
	  lpass = TRUE;
	}
      }
    }
  } while (!lpass);

/* Gather the results. */
  *nVtxs = nvxs;
  for (i=0; i<nvxs; i++) {
    if (irs[i] != i) {
      nrVtxs[i][0] = nrVtxs[irs[i]][0];
      nrVtxs[i][1] = nrVtxs[irs[i]][1];
    }
  }
  for (i=0; i<3; i++) {
    RA[i] = 0.0;
    RB[i] = 0.0;
  }

/* Compute the near Vertices on each Solid. */
  for (i=0; i<*nVtxs; i++) {
    lambda[i] = als[i];
    vtxA = nrVtxs[i][0];   /* Set the index of near Vertex in solidA. */
    vtxB = nrVtxs[i][1];   /* Set the index of near Vertex in solidB. */
    mpyxrc(solidA->sldBdy->T0j, vtxA->coord, temp);
    for (j=0; j<3; j++) {RA[j] += lambda[i] * temp[j];}
    mpyxrc(solidB->sldBdy->T0j, vtxB->coord, temp);
    for (j=0; j<3; j++) {RB[j] += lambda[i] * temp[j];}
  }
  for (i=0; i<3; i++) {plndir[i] = Vk[i];}
  return(vabsc(3, plndir));
}
