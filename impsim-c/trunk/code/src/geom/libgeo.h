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
/* libgeo-18 Jul 03:27 Jul 09
|    (C)Copyright, JJU Research, 2003-2009.
*
*     History:
*     18 Jul 03:JJU-Original.
*     15 Jul 09:JJU-Generalized with BDYDEF to fit IMP.
* ------------------------------------------------------------------- */

#ifndef LIBGEO_INCLUDED
# include "..\libcad\libcad.h"

# ifndef BDYDEF_INCLUDED
    enum Rectyp {SYSTEM=65504,   BODY,    SOLID,   FACE,    PERIM,
      EDGE,    HEDGE,   CORNER,  VERTEX,  POINT,   AXES};
  /* Body record architecture. */
    typedef struct body_tag  Body;
    typedef struct solid_tag Solid;
    typedef struct axes_tag  Axes;
    typedef struct point_tag Point;
    struct body_tag {
      enum Rectyp type;     /* Set to BODY to identify a Body record. */
      Body       *nxtBdy;      /* Pointer to next Body in the System. */
      void       *bdySys;  /* Pointer to parent System for this Body. */
      Solid      *bdySld;  /* Pointer to list of Solids in this Body. */
      Axes       *bdyAxs;    /* Pointer to list of Axes on this Body. */
      Point      *bdyPnt;  /* Pointer to list of Points on this Body. */
      int         bdyno;                 /* Body number of this Body. */
      int         nslds;            /* Number of Solids in this Body. */
      int         kcolor;                  /*Visibility of this Body. */
      real        T0j[3][4];/* Global Xformation matrix of this Body. */
      Name        name;                         /* Name of this Body. */
    };               /* Name must be last for compatability with IMP. */
#   define BDYDEF_INCLUDED
# endif
# ifndef AXSDEF_INCLUDED
  /* Axes record architecture. */
    struct axes_tag {
      enum Rectyp type;    /* Set to AXES to identify an Axes record. */
      Axes       *nxtAxs;       /* Pointer to next Axes on this Body. */
      Body       *axsBdy;   /* Pointer to parent Body for these Axes. */
      int         kcolor;   /* Visibility/color number of these Axes. */
      real        S[3][4]; /* Transformation for these Axes wrt Body. */
      Name        name;                        /* Name of these Axes. */
    };               /* Name must be last for compatability with IMP. */
#   define AXSDEF_INCLUDED
# endif

/* Solid record architecture. */
/* The data structure for Solid is based on the half edge structure as
 * described in "An Introduction to Solid Modeling" by Martti Mantyla.
 * The structure is modified to handle non-manifold solids by the use
 * of vertex cones and of halfedge pairs. */
  enum Dimtyp   {UNKNOWN=0, SPATIAL, PLANAR, REVOLUTION, EXTRUSION};
  typedef struct face_tag    Face;
  typedef struct edge_tag    Edge;
  typedef struct vertex_tag  Vertex;
  struct solid_tag {
    enum Rectyp type;     /* Set to SOLID to identify a Solid record. */
    Solid      *nxtSld;        /* Pointer to next Solid in this Body. */
    Body       *sldBdy;     /* Pointer to parent Body for this Solid. */
    Face       *sldFac;    /* Pointer to list of Faces in this Solid. */
    Edge       *sldEdg;    /* Pointer to list of Edges in this Solid. */
    Vertex     *sldVtx; /* Pointer to list of Vertices in this Solid. */
    Name        name;                          /* Name of this Solid. */
    int         sldno;                       /* Number of this Solid. */
    int         kcolor;     /* Visibility/color number of this Solid. */
    int         nfaces;             /* Number of Faces in this Solid. */
    int         nprms;             /* Number of Perims in this Solid. */
    int         nhedgs;            /* Number of Hedges in this Solid. */
    int         nedges;             /* Number of Edges in this Solid. */
    int         ncnrs;            /* Number of Corners in this Solid. */
    int         nvrtxs;          /* Number of Vertices in this Solid. */
    enum Dimtyp kdimen;         /* Dimensionality of the data stored. */
    real        screw[6];  /* Axis for solid of revolution/extrusion. */
    real        area;                  /* Surface area of this Solid. */
    real        volume;                      /* Volume of this Solid. */
    real        cg[3];              /* Centroid coords of this Solid. */
    real        smin_coord[3];   /* Oriented bounding box min coords. */
    real        smax_coord[3];   /* Oriented bounding box max coords. */
    real        bs_ctr[3];          /* Bounding sphere center coords. */
    real        bs_rad;                    /* Bounding sphere radius. */
  };

/* Face record architecture. */
  typedef struct perim_tag   Perim;
  struct face_tag {
    enum Rectyp type;       /* Set to FACE to identify a Face record. */
    Face       *nxtFac;        /* Pointer to next Face in this Solid. */
    Solid      *facSld;     /* Pointer to parent Solid for this Face. */
    Perim      *facPrm;    /* Pointer to list of Perims on this Face. */
    int         nprms;              /* Number of Perims on this Face. */
    int         facno;                        /* Number of this Face. */
    int         kcolor;      /* Visibility/color number of this Face. */
    real        area;      /* Surface area (wrt normal) of this Face. */
    real        faceq[4];   /* Coefficients of equation of this Face. */
    real        coeff;                   /* Coefficient of this Face. */
  };

/* Perim record architecture. */
  typedef struct hedge_tag   Hedge;
  struct perim_tag {
    enum Rectyp type;     /* Set to PERIM to identify a Perim record. */
    Perim      *nxtPrm;     /* Pointer to next   Perim in this  Face. */
    Face       *prmFac;     /* Pointer to parent Face for this Perim. */
    Hedge      *prmHed;   /* Pointer to ring of Hedges in this Perim. */
    int         nhedgs;            /* Number of Hedges in this Perim. */
    real        area;           /* Surface area inside of this Perim. */
  };

/* Hedge record architecture. */
  typedef struct corner_tag  Corner;
  struct hedge_tag {
    enum Rectyp type;     /* Set to HEDGE to identify a Hedge record. */
    Hedge      *nxtHedPrm; /* Pointer to next   Hedge in this  Perim. */
    Hedge      *nxtHedCnr; /* Pointer to next   Hedge in this Corner. */
    Perim      *hedPrm;    /* Pointer to parent Perim for this Hedge. */
    Corner     *hedCnr;  /* Pointer to starting Corner of this Hedge. */
    Edge       *hedEdg;        /* Pointer to the Edge for this Hedge. */
    Hedge      *hedMat;        /* Pointer to the Mate for this Hedge. */
  };

/* Edge record architecture. */
  struct edge_tag {
    enum Rectyp type;      /* Set to EDGE to identify an Edge record. */
    Edge       *nxtEdg;     /* Pointer to next   Edge  in this Solid. */
    Solid      *edgSld;     /* Pointer to parent Solid for this Edge. */
    Hedge      *edgHeL;  /* Pointer to the left  Hedge for this Edge. */
    Hedge      *edgHeR;  /* Pointer to the right Hedge for this Edge. */
    real        length;                       /* Length of this Edge. */
    real        coeff;                   /* Coefficient of this Edge. */
  };

/* Corner record architecture. */
  struct corner_tag {
    enum Rectyp type;   /* Set to CORNER to identify a Corner record. */
    Corner     *nxtCnr;  /* Pointer to next   Corner  at this Vertex. */
    Vertex     *cnrVtx;  /* Pointer to parent Vertex for this Corner. */
    Hedge      *cnrHed;  /* Pointer to ring of Hedges in this Corner. */
    int         nhedgs;           /* Number of Hedges in this Corner. */
    real        sldang;      /* Solid angle subtended by this Corner. */
  };

/* Vertex record architecture. */
  struct vertex_tag {
    enum Rectyp type;   /* Set to VERTEX to identify a Vertex record. */
    Vertex     *nxtVtx;   /* Pointer to next   Vertex in this  Solid. */
    Solid      *vtxSld;   /* Pointer to parent Solid for this Vertex. */
    Corner     *vtxCnr; /* Pointer to list of Corners at this Vertex. */
    int         ncnrs;           /* Number of Corners at this Vertex. */
    int         vtxno;                      /* Number of this Vertex. */
    int         kcolor;           /* Visibility/color of this Vertex. */
    real        sldang;      /* Solid angle subtended at this Vertex. */
    real        coord[4]; /* Coordinate data wrt Body of this Vertex. */
    real        coeff;                 /* Coefficient of this Vertex. */
  };

/* Point record architecture. */
  struct point_tag {
    enum Rectyp type;     /* Set to POINT to identify a Point record. */
    Point      *nxtPnt;     /* Pointer to next   Point on this  Body. */
    Body       *pntBdy;     /* Pointer to parent Body for this Point. */
    Name        name;                          /* Name of this Point. */
    int         master;  /* Logical flag set TRUE for a master Point. */
    int         local;       /* Logical flag set TRUE for local data. */
    int         kcolor;     /* Visibility/color number of this Point. */
    real        coord[4];  /* Coordinate data wrt Body of this Point. */
  };

/* Geometric Node definitions. */
  typedef union  nodes       Node;
  union  node_tag {
    Body        bdy;
    Solid       sld;
    Face        fac;
    Perim       prm;
    Hedge       hed;
    Edge        edg;
    Corner      cnr;
    Vertex      vtx;
    Axes        axs;
    Point       pnt;
  };

/* libgeo macros. */
# define   mate(hed)   (((hed) == (hed)->hedEdg->edgHeL) ? \
                         (hed)->hedEdg->edgHeR : (hed)->hedEdg->edgHeL)

/* libgeo routine names. */
# if defined(LINUX) || defined(MIPS) || defined(SUN)
#   define abortc  abortc_
#   define cleanc  cleanc_
#   define edlngc  edlngc_
#   define fcavgc  fcavgc_
#   define fcnrmc  fcnrmc_
#   define geaxsc  geaxsc_
#   define hedvxc  hedvxc_
#   define ldhedc  ldhedc_
#   define lptprc  lptprc_
#   define mkcnrc  mkcnrc_
#   define mkedgc  mkedgc_
#   define mkefc   mkefc_
#   define mkevc   mkevc_
#   define mkfac   mkfac_
#   define mkhedc  mkhedc_
#   define mkobjc  mkobjc_
#   define mkprmc  mkprmc_
#   define mkvtxc  mkvtxc_
#   define mrgfac  mrgfac_
#   define mvvtxc  mvvtxc_
#   define nedgec  nedgec_
#   define pointc  pointc_
#   define prmarc  prmarc_
#   define ringac  ringac_
#   define ringbc  ringbc_
#   define sclbdc  sclbdc_
#   define xcnrc   xcnrc_
#   define xedgc   xedgc_
#   define xedgc   xfac_
#   define xfbdyc  xfbdyc_
#   define xhedc   xhedc_
#   define xprmc   xprmc_
#   define xsfvc   xsfvc_
#   define xsldc   xsldc_
#   define xvtxc   xvtxc_
# endif

/* Prototypes for libgeo. */
  extern void abortc();
  extern void cleanc(
# ifdef ANSI
    Solid *solid);
# else
    solid)
    Solid *solid;
# endif
  extern real edlngc(
# ifdef ANSI
    Edge *edge);
# else
    edge)
    Edge *edge;
# endif
  extern void fcavgc(
# ifdef ANSI
    Face *face, real *xavg, real *yavg, real *zavg);
# else
    face, xavg, yavg, zavg)
    Face *face;
    real *xavg, *yavg, *zavg;
# endif
  extern void fcnrmc(
# ifdef ANSI
    Face *face);
# else
    face)
    Face *face;
# endif
  extern Axes *geaxsc(
# ifdef ANSI
    Body *body, Name *name, real x0, real y0, real z0, real thx,
      real thy, real thz);
# else
    body, name, x0, y0, z0, thx, thy, thz)
    Body *body;
    Name *name;
    real  x0, y0, z0, thx, thy, thz;
# endif
  extern void hedvxc(
#ifdef ANSI
  Hedge *hedge, Vertex **vxB, Vertex **vxA);
#else
  hedge, vxB, vxA)
  Hedge  *hedge;
  Vertex **vxB, **vxA;
#endif
  extern Hedge *ldhedc(
# ifdef ANSI
    Edge *edge);
# else
    edge)
    Edge *edge;
# endif
  extern int lptprc(
# ifdef ANSI
    real pt[3], Perim *perim);
# else
    pt[3], perim)
    real  pt[3];
    Perim *perim;
# endif
  extern Corner *mkcnrc(
# ifdef ANSI
    Vertex *vertex);
# else
    vertex)
    Vertex *vertex;
# endif
  extern Edge *mkedgc(
# ifdef ANSI
    Solid *solid);
# else
    solid)
    Solid *solid;
# endif
  extern Edge *mkefc(
# ifdef ANSI
    Hedge *heB, Hedge *heA);
# else
    heB, heA)
    Hedge *heB, *heA;
# endif
  extern Edge *mkevc(
# ifdef ANSI
    Hedge *hedB, Hedge *hedA, real x, real y,real z);
# else
    hedB, hedA, x, y, z)
    Hedge *hedB, *hedA;
    real  x, y, z;
# endif
  extern Face *mkfac(
# ifdef ANSI
    Solid *solid);
# else
    sld)
    Solid *sld;
# endif
  extern Hedge *mkhedc(
# ifdef ANSI
    Perim *perim, Corner *corner);
# else
    perim, corner)
    Perim  *perim;
    Corner *corner;
# endif
  extern Body  *mkobjc();
  extern Perim *mkprmc(
# ifdef ANSI
    Face *face);
# else
    face)
    Face *face;
# endif
  extern Solid *mksfvc(
# ifdef ANSI
    Body *body, real x, real y, real z);
# else
    body, x, y, z)
    Body *body;
    real  x, y, z;
# endif
  extern Solid *mksldc(
# ifdef ANSI
    Body *body);
# else
    body)
    Body *body;
# endif
  extern Vertex *mkvtxc(
# ifdef ANSI
    Solid *solid, real x, real y, real z);
# else
    solid, x, y, z)
    Solid *solid;
    real  x, y, z;
# endif
  extern int mrgfac(
# ifdef ANSI
    Perim *perim1, Perim *perim2);
# else
    perim1, perim2)
    Perim *perim1, *perim2;
# endif
  extern void mvvtxc(
# ifdef ANSI
    Vertex *vertex, real x, real y, real z);
# else
    vertex, x, y, z)
    Vertex *vertex;
    real   x, y, z;
# endif
  extern int nedgec(
# ifdef ANSI
    Edge *edge);
# else
    edge)
    Edge  *edge;
# endif
  extern Point *pointc(
# ifdef ANSI
    Body *body, Name *name, real x0, real y0, real z0);
# else
    body, name, x0, y0, z0)
    Body *body;
    Name *name;
    real  x0, y0, z0;
# endif
  extern real prmarc(
# ifdef ANSI
    Perim *perim);
# else
    perim)
    Perim *perim;
# endif
  extern void ringac(
#ifdef ANSI
    void *parent, Hedge *hedge, Hedge *hedbfr);
#else
    parent, hedge, member)
    void  *parent;
    Hedge *hedge, *member;
#endif
  extern void ringbc(
#ifdef ANSI
    void *parent, Hedge *hedge, Hedge *hedaft);
#else
    parent, hedge, member)
    void  *parent;
    Hedge *hedge, *member;
#endif
  extern void sclbdc(
# ifdef ANSI
    Body *body, real factor);
# else
    body, factor)
    Body *body;
    real  factor;
# endif
  extern void xcnrc(
# ifdef ANSI
    Corner *cnr);
# else
    cnr)
    Corner *cnr;
# endif
  extern void xedgc(
# ifdef ANSI
    Edge *edg);
# else
    edg)
    Edge *edg;
# endif
  extern void xfac(
# ifdef ANSI
    Face *fac);
# else
    fac)
    Face *fac;
# endif
  extern void xfbdyc(
# ifdef ANSI
    Body *body, real xform[3][4]);
# else
    body, xform)
    Body *body;
    real   xform[3][4];
# endif
  extern void xhedc(
# ifdef ANSI
    Hedge *hed);
# else
    hed)
    Hedge *hed;
# endif
  extern void xprmc(
# ifdef ANSI
    Perim *perim);
# else
    prm)
    Perim *perim;
# endif
  extern void xsldc(
# ifdef ANSI
    Solid *sld);
# else
    sld)
    Solid *sld;
# endif
  extern void xvtxc(
# ifdef ANSI
    Vertex *vtx);
# else
    vtx)
    Vertex *vtx;
# endif
# define LIBGEO_INCLUDED
#endif
