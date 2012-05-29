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
/* mksfvc-25 Jul 03:27 Jul 09
|     (C)Copyright, JJU Research, 2003-2009
|
|     Description:
|       Form a data structure for new Solid with a single Face, a single
|     Vertex, a single Corner, a single Perim, and a single Hedge.
|
|     Access:
|       solid = (Solid *) mksfvc(Body *body, real x, real y,real z);
|     Body  *body,  i-Pointer to the parent Body record.
|     real   x,     i-Coordinate of the vertex relative to Body axes.
|     real   y,     i-Coordinate of the vertex relative to Body axes.
|     real   z,     i-Coordinate of the vertex relative to Body axes.
|     Solid *solid, o-Pointer to the newly formed Solid record.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This is an Euler operator for geometry creation.
|       The Face formed has a Perim with a single Hedge; the Vertex has
|     a Corner with the same single Hedge; the Hedge is a self-loop and
|     has no Edge.
|       The new Solid is added to the end of the list of solids of the
|     designated Body.  If *body does not point to a valid Body record
|     then the new Solid is created as an orphan, without a parent Body.
*
*     History:
*     25 Jul 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libgeo.h"
#ifdef ANSI
  Solid *mksfvc(Body *body, real x, real y, real z)
#else
  Solid *mksfvc(body, x, y, z)
  Body  *body;
  real   x, y, z;
#endif
{
  Corner *corner;
  Face   *face;
  Hedge  *hedge;
  Perim  *perim;
  Solid  *solid;
  Vertex *vertex;

  solid = mksldc(body);                  /* Create the Solid  record. */
  face  = mkfac(solid);                  /* Create the Face   record. */
  vertex= mkvtxc(solid, x, y, z);        /* Create the Vertex record. */
  perim = mkprmc(face);                  /* Create the Perim  record. */
  corner= mkcnrc(vertex);                /* Create the Corner record. */
  hedge = mkhedc(perim, corner);         /* Create the Hedge  record. */
  hedge->hedMat = hedge;     /* Make this Hedge its own mating Hedge. */
  return(solid);
}
