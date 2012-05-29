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
/* libimp-01 Jan 00:16 Aug 09
|    (C)Copyright, JJU Research, 2000-2009
*
*     History:
*     01 Jan 00:JJU-Original.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
*     12 Mar 09:JJU-Implemented Euler parameters.
*     15 Jul 09:JJU-Generalized to include BDYDEF and libgeo.
* ------------------------------------------------------------------- */

#ifndef LIBIMP_INCLUDED
# include "..\libcad\libcad.h"
# include "filidc.h"
# define MAXCHR          (4)/* Max chars in an IMP alphanumeric Word. */
# define MXKOL          (72)/* Max characters in an IMP input record. */
# define MXTOKN         (36)    /* Max tokens in an IMP input record. */
# define UNDET    (0.000002) /* Pattern written to IMP files for NaN. */

# ifndef BDYDEF_INCLUDED
  /* IMP Body record architecture. *//*Must be defined before libgeo. */
    enum Rectyp {SYSTEM=65504,   BODY,    SOLID,   FACE,    PERIM,
      EDGE,    HEDGE,   CORNER,  VERTEX,  POINT,   AXES};
    typedef struct body_tag   Body;
    typedef struct solid_tag  Solid;
    typedef struct axes_tag   Axes;
    typedef struct point_tag  Point;
    typedef struct mass_tag   Mass;
    typedef struct force_tag  Force;
    typedef struct torque_tag Torque;
    typedef char   Word[MAXCHR+1];  /* MAXCHR chars+NULL in IMP Word. */
    struct body_tag {
      enum Rectyp type;     /* Set to BODY to identify a Body record. */
      Body       *nxtBdy;      /* Pointer to next Body in the system. */
      void       *bdySys;  /* Pointer to parent System for this Body. */
      Solid      *bdySld; /* Pointer to list of Solids for this Body. */
      Axes       *bdyAxs;    /* Pointer to list of Axes on this Body. */
      Point      *bdyPnt;  /* Pointer to list of Points on this Body. */
      int         bdyno;                /* Body number for this Body. */
      int         nslds;            /* Number of Solids in this Body. */
      int         kcolor;   /* Visibility/color number for this Body. */
      real        T0j[3][4];/* Global Xformation matrix of this Body. */
      Word        name;                         /* Name of this Body. */
      real        W[6];   /* Velocity operator (omega) for this Body. */
      real        A[6];/* Acceleration operator(alpha) for this Body. */
      long        loopflags; /* Bit flags showing existence in loops. */
      Mass       *bdyMas;            /* Pointer to Mass of this Body. */
      Force      *bdyFrc;  /* Pointer to list of Forces on this Body. */
      Torque     *bdyTrq; /* Pointer to list of Torques on this Body. */
    };     /* Name and on must be last for compatability with libgeo. */
#   define BDYDEF_INCLUDED
# endif
# ifndef AXSDEF_INCLUDED
  /* IMP Axes record architecture. *//*Must be defined before libgeo. */
    typedef struct joint_tag Joint;
    struct axes_tag {
      enum Rectyp type;    /* Set to AXES to identify an Axes record. */
      Axes       *nxtAxs;       /* Pointer to next Axes on this Body. */
      Body       *axsBdy;   /* Pointer to parent Body for these Axes. */
      int         kcolor;  /* Visibility/color number for these Axes. */
      real        S[3][4];   /* Shape matrix for these Axes wrt Body. */
      Word        name;                        /* Name of these Axes. */
      long        loopflags; /* Bit flags showing existence in loops. */
      Joint      *axsJnt;       /* Pointer to Joint using these Axes. */
    };     /* Name and on must be last for compatability with libgeo. */
#   define AXSDEF_INCLUDED
# endif
# include "..\geom\libgeo.h"

/* IMP Record structure definitions. */
  enum IMPtyp {JOINT=0, JVAR,  SGC,     IC,      MASS,    SPRING,
    DAMPER,  FORCE,   TORQUE,  CONTACT, REQUEST, VALUE};
  typedef struct   token_tag Token;
  typedef struct   value_tag Value;
  typedef struct    jvar_tag Jvar;
  typedef struct     sgc_tag Sgc;
  typedef struct      ic_tag Ic;
  typedef struct  spring_tag Spring;
  typedef struct  damper_tag Damper;
  typedef struct contact_tag Contact;
  typedef struct request_tag Request;

/* Token record architecture. */
  enum Fnctyp      {F_UNDEF=-1000,F_EQUAL=0,F_PLUS,   F_MINUS,  F_MULT,
    F_DIVIDE, F_POWER,  F_CONST,  F_TIME,   F_ABS,    F_ACCEL,  F_ACOS,
    F_ASIN,   F_ATAN,   F_COS,    F_EXP,    F_FORCE,  F_IF,     F_LOG,
    F_LOG10, F_POSITION,F_SIN,    F_SQRT,   F_TABLE,  F_TAN,    F_USER,
    F_VELOCITY,F_RETURN,F_END,    F_ALL=0};        /* Function types. */
  enum Tkntyp {TK_UNDEF=0, TK_CHAR, TK_INT, TK_REAL, TK_EXP, TK_VALUE,
    TK_XYZ, TK_FUNC, TK_UNKNOWN};                     /* Token types. */
  enum Optyp  {OP_UNDEF=-1000, OP_EQUAL=0, OP_ADD, OP_SUBTRACT,
    OP_MULTIPLY, OP_DIVIDE, OP_POWER, OP_PAREN=20};/* Operator types. */
  struct token_tag {
    enum Tkntyp kind;  /* Flag for type of data stored in this Token. */
    enum Optyp  op;/* Operator which terminated input for this Token. */
    union {
      int         number;            /* Integer value for this Token. */
      real        word;                 /* Real value for this Token. */
      Word        text;               /* String value for this Token. */
      Value      *value;   /* Pointer to Value record for this Token. */
      enum Fnctyp f;                 /* Function type for this Token. */
    } data;
  };
# include "inputc.h"

/* Value record architecture. */
  struct value_tag {
    enum IMPtyp type;     /* Set to VALUE to identify a Value record. */
    enum Fnctyp f;                      /* Function betweem operands. */
    Value      *nxtVal;       /* Pointer to next Value in the system. */
    Value      *arg[4]; /* Pointers to up to 4 operand Value records. */
    Word        name;                          /* Name of this Value. */
    real        v;                    /* Numeric value of this Value. */
    real        d1;           /* First time derivative of this Value. */
    real        d2;          /* Second time derivative of this Value. */
  };

/* System record architecture. */
  enum Modtyp {MD_UNDEF=0, MD_GEO,  MD_KIN,  MD_STAT, MD_DYN};
  enum Imptyp {IM_UNDEF=0, IM_REST, IM_FRIC, IM_BILIN};
  enum Xeqtyp {XQ_ANMAT=0, XQ_ERASE,XQ_PAUSE};
  extern struct system_tag {
    enum IMPtyp type; /* Set to SYSTEM to identify the System record. */
    enum Modtyp mode;                            /* Mode of analysis. */
    Body       *sysBdy;    /* Pointer to list of Bodys in the system. */
    Solid      *sysSld;/* Pointer to list of orphan Solids in system. */
    Joint      *sysJnt;   /* Pointer to list of Joints in the system. */
    Spring     *sysSpg;  /* Pointer to list of Springs in the system. */
    Damper     *sysDmp;  /* Pointer to list of Dampers in the system. */
    Contact    *sysCnt; /* Pointer to list of Contacts in the system. */
    Value      *sysVal;   /* Pointer to list of Values in the system. */
    Request    *sysReq; /* Pointer to list of Requests in the system. */
    Body       *ground;                 /* Pointer to the fixed Body. */
    char       *title;           /* Title for the IMP modeled system. */
    Word        base;                      /* Name of the fixed Body. */
    int         interact;  /* Logical flag for interactive execution. */
    int         echo;              /* Logical flag for echo of input. */
    int         nerror;         /* Number of most recent error found. */
    int         level;                /* Level of analysis completed. */
    int         hold;                           /* Logical hold flag. */
    int         xeqflags;             /* Execution control bit-flags. */
    int         nbdys;              /* Number of Bodys in the system. */
    int         nsolids;           /* Number of Solids in the system. */
    int         njnts;             /* Number of Joints in the system. */
    int         njvars;   /* Number of joint variables in the system. */
    int         nloops;   /* Number of kinematic loops in the system. */
    int         ndof;  /* Number of degrees of freedom in the system. */
    int         nsgc;                /* Number of SGCs in the system. */
    int         nfgc;                /* Number of FGCs in the system. */
    int         ndep;     /* Number of kinematically dependent jvars. */
    int         nfree; /* Number of jvars open for use as dep or fgc. */
    int         nc;    /* Number of constraint equations in Jacobian. */
    int         ci;       /* Iteration counter for position analysis. */
    int         cn;  /* Max iterations allowed for position analysis. */
    int         ei;         /* Iteration counter for static analysis. */
    int         en;    /* Max iterations allowed for static analysis. */
    int         mrank;        /* Rank of the system mass      matrix. */
    int         krank;        /* Rank of the system stiffness matrix. */
    enum Imptyp impacteq[3];           /* Impact models for impulses. */
    real        ascale;       /* Scale factor for angular  variables. */
    real        lscale;       /* Scale factor for distance variables. */
    real        dtola;   /* Tolerance for input data  angular  tests. */
    real        dtoll;   /* Tolerance for input data  distance tests. */
    real        ptola;   /* Tolerance for position    angular  tests. */
    real        ptoll;   /* Tolerance for position    distance tests. */
    real        etola;   /* Tolerance for equilibrium angular  tests. */
    real        etoll;   /* Tolerance for equilibrium distance tests. */
    real        fintol;/* Tolerance for determinate derivative tests. */
    real        fjtol; /* Tolerance for system Jacobian    rank test. */
    real        dytol; /* Tolerance for mass matrix singularity test. */
    real        fktol; /* Tolerance for stiffness   singularity test. */
    real        ferr;/* Dynamic force tolerance for time integration. */
    real        pferr;         /* Dynamic force percentage tolerance. */
    real        zero;    /* Tolerance for other small quantity tests. */
    real        gc;              /* Weight to mass conversion factor. */
    real        qi;                   /* Quality index of the system. */
    real       *sysJ;       /* Pointer to the system Jacobian matrix. */
    real      **d1;   /* Pointer to the jvar first derivative matrix. */
    real     ***d2;  /* Pointer to the jvar second derivative matrix. */
    real      **pd; /* Pointer to the jvar partial derivative matrix. */
    real        gravty[3];   /* Gravity vector in global coordinates. */
    real        tprev;                     /* Previous value of time. */
    real        t;                         /* Current  value of time. */
    real        tnxtio;                 /* Time for next user output. */
    real        tfinal;             /* Final value of time requested. */
    real        dt;                 /* Current size of the time step. */
    real        dtmin;         /* Minimum value of time step allowed. */
    real        dtmax;         /* Maximum value of time step allowed. */
    real        dtio;         /* Time increment between user outputs. */
  } System;

/* Joint record architecture. */
  enum Jnttyp        {RIGID=0, XPIN,    YPIN,    ZPIN,    XSLIDE,YSLIDE,
    ZSLIDE,  SCREW,   GEAR,    RACK,    BEVEL,   CYLINDER,UJOINT,  CAM,
    SLOT,    FLAT,    PLANE,   SPHERE,  OPEN};
  struct joint_tag {
    enum IMPtyp type;     /* Set to JOINT to identify a Joint record. */
    enum Jnttyp jtype;                         /* Type of this Joint. */
    Joint      *nxtJnt;       /* Pointer to next Joint in the System. */
    Axes       *jntAxA;      /* Pointer to Axes following this Joint. */
    Axes       *jntAxB;     /* Pointer to Axes preceeding this Joint. */
    Jvar       *jntJvr;   /* Pointer to list of Jvars for this Joint. */
    Word        name;                          /* Name of this Joint. */
    long        loopflags;/* Bit flags specifying existence in loops. */
    int         orient;  /* Orientation of Joint wrt user definition. */
    int         jntno;                      /* Number for this Joint. */
    int         njvars;            /* Number of Jvars for this Joint. */
    real        param[3];               /* Parameters for this joint. */
    real        Phi[3][4];       /* Xformation matrix for this Joint. */
    real        axsize;   /* Visibility setting for these Joint axes. */
  };

/* Jvar record architecture. */
  enum Jvrtyp {JV_UNDEF=0, JV_LINEAR, JV_ANGULAR, JV_EULER};
  struct jvar_tag {
    enum IMPtyp type;       /* Set to JVAR to identify a Jvar record. */
    enum Jvrtyp jvrtyp;               /* Variable type for this Jvar. */
    Jvar       *nxtJvr;        /* Pointer to next Jvar in this Joint. */
    Joint      *jvrJnt;     /* Pointer to Parent Joint for this Jvar. */
    Sgc        *jvrSgc;              /* Pointer to Sgc for this Jvar. */
    Ic         *jvrIc;                /* Pointer to Ic for this Jvar. */
    int         jvrnoJ;    /* Number within this Joint for this Jvar. */
    int         jvrnoS;    /* Number within the System for this Jvar. */
    real        D[6];           /* Derivative operator for this Jvar. */
    Value      *jvrVk;      /* Pointer to Value record for stiffness. */
    real        k;                  /* Stiffness value for this Jvar. */
    Value      *jvrVfp; /* Pointer to Value record for free position. */
    real        freepos;              /* Free position for this Jvar. */
    Value      *jvrVc;        /* Pointer to Value record for damping. */
    real        c;            /* Viscous damping value for this Jvar. */
    Value      *jvrVf;  /* Pointer to Value record for applied force. */
    real        force;    /* Force or torque acting within this Jvar. */
    Value      *jvrVup; /* Pointer to u Value record for slot or cam. */
    Value      *jvrVvp; /* Pointer to v Value record for slot or cam. */
    real        design;             /* Design position for this Jvar. */
    real        lastpos;     /* Last value of position for this Jvar. */
    real        lastvel;     /* Last value of velocity for this Jvar. */
    real        lastacc; /* Last value of acceleration for this Jvar. */
    real        pos;      /* Current value of position for this Jvar. */
    real        vel;      /* Current value of velocity for this Jvar. */
    real        acc;  /* Current value of acceleration for this Jvar. */
  };

/* Sgc record architecture. */
  struct sgc_tag {
    enum IMPtyp type;        /* Set to SGC to identify an Sgc record. */
    Jvar       *sgcJvr;              /* Pointer to Jvar for this Sgc. */
    Value      *sgcVal;    /* Pointer to Value record for Sgc motion. */
    int         incrnum;            /* Number of position increments. */
    real        incrpos;          /* Position increment for this Sgc. */
    real        initpos;            /* Initial position for this Sgc. */
    real        scale;                  /* Scale factor for this Sgc. */
    real        pos;                /* Current position for this Sgc. */
    real        vel;                /* Current velocity for this Sgc. */
    real        acc;            /* Current acceleration for this Sgc. */
  };

/* Ic record architecture. */
  struct ic_tag {
    enum IMPtyp type;          /* Set to IC to identify an Ic record. */
    Jvar       *icJvr;                /* Pointer to Jvar for this Ic. */
    real        scale;                   /* Scale factor for this Ic. */
    Value      *icVpos;   /* Pointer to Value record for Ic position. */
    real        initpos;             /* Initial position for this Ic. */
    Value      *icVvel;   /* Pointer to Value record for Ic velocity. */
    real        initvel;             /* Initial velocity for this Ic. */
  };

/* Mass record architecture. */
  struct mass_tag {
    enum IMPtyp type;       /* Set to MASS to identify a Mass record. */
    Body       *masBdy;         /* Pointer to the Body for this Mass. */
    real        I[10];/* Inertia: Ixx,Ixy,Iyy,Ixz,Iyz,Izz,mx,my,mz,m. */
  };

/* Spring record architecture. */
  struct spring_tag {
    enum IMPtyp type;   /* Set to SPRING to identify a Spring record. */
    Spring     *nxtSpg;      /* Pointer to next Spring in the System. */
    Point      *spgPtA;    /* Pointer to Point following this Spring. */
    Point      *spgPtB;   /* Pointer to Point preceeding this Spring. */
    Word        name;                         /* Name of this Spring. */
    int         kcolor;/*Visibility and color number for this Spring. */
    Value      *spgVk;    /* Pointer to Value record for Spring rate. */
    real       k;                        /* Stiffness of this Spring. */
    Value      *spgVfl; /* Pointer to Value record for Spring length. */
    real       freel;                  /* Free length of this Spring. */
  };

/* Damper record architecture. */
  struct damper_tag {
    enum IMPtyp type;   /* Set to DAMPER to identify a Damper record. */
    Damper     *nxtDmp;      /* Pointer to next Damper in the System. */
    Point      *dmpPtA;    /* Pointer to Point following this Damper. */
    Point      *dmpPtB;   /* Pointer to Point preceeding this Damper. */
    Word        name;                         /* Name of this Damper. */
    int         kcolor;/*Visibility and color number for this Damper. */
    Value      *dmpVc;    /* Pointer to Value record for Damper rate. */
    real       c;      /* Viscous damping coefficient of this Damper. */
    real       ol;   /* Original length of this Damper (for display). */
  };

/* Force record architecture. */
  struct force_tag {
    enum IMPtyp type;     /* Set to FORCE to identify a Force record. */
    Force      *nxtFrc;        /* Pointer to next Force on this Body. */
    Point      *frcPtA;     /* Pointer to Point following this Force. */
    Point      *frcPtB;    /* Pointer to Point preceeding this Force. */
    Point      *frcPtC;  /* Pointer to Point of application of Force. */
    Word        name;                          /* Name of this Force. */
    int         kcolor;/* Visibility and color number for this Force. */
    Value      *frcVf;     /* Pointer to Value record for Force size. */
    real        f;                        /* Magnitude of this Force. */
  };

/* Torque record architecture. */
  struct torque_tag {
    enum IMPtyp type;   /* Set to TORQUE to identify a Torque record. */
    Torque     *nxtTrq;       /* Pointer to next Torque on this Body. */
    Point      *trqPtA;    /* Pointer to Point following this Torque. */
    Point      *trqPtB;   /* Pointer to Point preceeding this Torque. */
    Body       *trqBdy; /* Pointer to Body for application of Torque. */
    Word        name;                         /* Name of this Torque. */
    int         kcolor;/*Visibility and color number for this Torque. */
    Value      *trqVt;    /* Pointer to Value record for Torque size. */
    real        t;                       /* Magnitude of this Torque. */
  };

/* Contact record architecture. */
  enum Cnttyp {CN_UNDEF=0, CN_VERTEX, CN_FACE, CN_EDGE};
  struct contact_tag {
    enum IMPtyp type; /* Set to CONTACT to identify a Contact record. */
    enum Cnttyp cntypA;  /* Type of Geometry  following this Contact. */
    enum Cnttyp cntypB;  /* Type of Geometry preceeding this Contact. */
    Contact    *nxtCnt;     /* Pointer to next Contact in the System. */
    Solid      *cnSldA;  /* Pointer to Solid following  this Contact. */
    Solid      *cnSldB;  /* Pointer to Solid preceeding this Contact. */
    Vertex     *near_vxs[4][2];        /* Cached points for distance. */
    void       *ptrA; /* Pointer to Geometry  following this Contact. */
    void       *ptrB; /* Pointer to Geometry preceeding this Contact. */
    Word        name;                        /* Name of this Contact. */
    int         sepplane;/* Flag set TRUE if separating plane exists. */
    int         nvxs;                   /* Number of cached near_vxs. */  
    int         numcr;   /* Number of vertices in the contact region. */
    real        CR[20][3];         /* Vertices in the contact region. */
    real        lambda[4];            
    real        pln_dir[3];            /* Direction of contact plane. */
    real        pln_pntA[3];/*Near point on solid  following Contact. */
    real        pln_pntB[3];/*Near point on solid preceeding Contact. */
    real        timex;                  /* Time for expected contact. */
    real        rest_n;  /* Coefficient of restitution (normal  dir). */
    real        rest_t;  /* Coefficient of restitution (tangent dir). */
    real        rest_m;  /* Coefficient of restitution   for  moment. */
    real        rest_mn; /* Coefficient of restitution   for torsion. */ 
    real        mu;                       /* Coefficient of friction. */
    real        Rp;                  /* Radius for torsional impulse. */
    real        cnplane[4];          /* Plane coordinates of Contact. */
    real        cnpoint[3];          /* Point coordinates at Contact. */
    real        cnnormal[3];         /* Normal     vector at Contact. */
    real        cntangnt[3];         /* Tangential vector at Contact. */
    real        cnbinorm[3];         /* Binormal   vector at Contact. */
  };

/* Request record architecture. */
  enum Reqtyp {RQ_UNDEF=0, RQ_PRINT, RQ_LIST,  RQ_PLOT,  RQ_STORE};
  enum Outtyp {OT_UNDEF=0, OT_VAL,  OT_POS,  OT_VEL,  OT_ACC,  OT_FORC,
    OT_HDNG, OT_FREQ, OT_DYN};
  struct request_tag {
    enum IMPtyp type; /* Set to REQUEST to identify a Request record. */
    enum Reqtyp reqtyp; /* Type of request: Print, List, Plot, Store. */
    enum Outtyp outtyp;  /* Type of analysis: Position, Velocity, ... */
    Request    *nxtReq;     /* Pointer to next Request in the System. */
    Token      *items;/* List of Tokens naming items of this Request. */
    int         nitems;          /* Number of Tokens in this Request. */
  };

/* libimp macros. */
# define   mate(hed)   (((hed) == (hed)->hedEdg->edgHeL) ? \
                         (hed)->hedEdg->edgHeR : (hed)->hedEdg->edgHeL)

/* libimp routine names. */
# if defined(LINUX) || defined(MIPS) || defined(SUN)
#   define abortc abortc_
#   define acc    acc_
#   define accijc accijc_
#   define adjstc adjstc_
#   define ajustc ajustc_
#   define aldync aldync_
#   define axesc  axesc_
#   define basec  basec_
#   define beginc beginc_
#   define bformc bformc_
#   define bodyc  bodyc_
#   define bsphrc bsphrc_
#   define checkc checkc_
#   define cleanc cleanc_
#   define clearc clearc_
#   define closec closec_
#   define cmatc  cmatc_
#   define contac contac_
#   define dacc   dacc_
#   define damprc damprc_
#   define datac  datac_
#   define dbodyc dbodyc_
#   define dbvlc  dbvlc_
#   define dcamc  dcamc_
#   define dcontc dcontc_
#   define dcylc  dcylc_
#   define ddaldc ddaldc_
#   define ddampc ddampc_
#   define ddmatc ddmatc_
#   define deletc deletc_
#   define dforc  dforc_
#   define dgearc dgearc_
#   define dgravc dgravc_
#   define dic    dic_
#   define dinrtc dinrtc_
#   define djvarc djvarc_
#   define dmacc  dmacc_
#   define dmassc dmassc_
#   define dmatc  dmatc_
#   define dmforc dmforc_
#   define dmotnc dmotnc_
#   define dmposc dmposc_
#   define dmprpc dmprpc_
#   define dmvelc dmvelc_
#   define dpntc  dpntc_
#   define dpostc dpostc_
#   define dprmc  dprmc_
#   define dqbvlc dqbvlc_
#   define dqcamc dqcamc_
#   define dqgerc dqgerc_
#   define dqopnc dqopnc_
#   define dqrckc dqrckc_
#   define dqsltc dqsltc_
#   define dqsphc dqsphc_
#   define drawc  drawc_
#   define drckc  drckc_
#   define drdmpc drdmpc_
#   define drevc  drevc_
#   define drfrcc drfrcc_
#   define drgdc  drgdc_
#   define drspgc drspgc_
#   define drtrqc drtrqc_
#   define dscrwc dscrwc_
#   define dsetc  dsetc_
#   define dsltc  dsltc_
#   define dsolvc dsolvc_
#   define dsphc  dsphc_
#   define dspngc dspngc_
#   define dssldc dssldc_
#   define dstABc dstABc_
#   define dtimec dtimec_
#   define dtorqc dtorqc_
#   define dujtc  dujtc_
#   define dvelc  dvelc_
#   define dxrvc  dxrvc_
#   define dxslc  dxslc_
#   define dynmxc dynmxc_
#   define dynm1c dynm1c_
#   define dynm2c dynm2c_
#   define dynm3c dynm3c_
#   define dynm5c dynm5c_
#   define dyrvc  dyrvc_
#   define dysetc dysetc_
#   define dyslc  dyslc_
#   define dzrvc  dzrvc_
#   define dzslc  dzslc_
#   define edsrtc edsrtc_
#   define ematc  ematc_
#   define endc   endc_
#   define endsvc endsvc_
#   define eqjstc eqjstc_
#   define eqlibc eqlibc_
#   define fbdtc  fbdtc_
#   define fchekc fchekc_
#   define fdervc fdervc_
#   define fdync  fdync_
#   define fgvtc  fgvtc_
#   define fillc  fillc_
#   define fjtdc  fjtdc_
#   define fjtfc  fjtfc_
#   define fjtsc  fjtsc_
#   define flnamc flnamc_
#   define forcec forcec_
#   define fptdc  fptdc_
#   define fptfc  fptfc_
#   define fptsc  fptsc_
#   define freqnc freqnc_
#   define frmatc frmatc_
#   define fsetc  fsetc_
#   define gfbdtc gfbdtc_
#   define gfdync gfdync_
#   define gfgvtc gfgvtc_
#   define gfjtdc gfjtdc_
#   define gfjtfc gfjtfc_
#   define gfjtsc gfjtsc_
#   define gforc  gforc_
#   define gfptdc gfptdc_
#   define gfptfc gfptfc_
#   define gfptsc gfptsc_
#   define hdfgc  hdfgc_
#   define hdngc  hdngc_
#   define hdsgc  hdsgc_
#   define icsetc icsetc_
#   define identc identc_
#   define impctc impctc_
#   define imvelc imvelc_
#   define intfnc intfnc_
#   define intrpc intrpc_
#   define jmatc  jmatc_
#   define jointc jointc_
#   define jtacc  jtacc_
#   define jtforc jtforc_
#   define jtposc jtposc_
#   define jtvelc jtvelc_
#   define jvacc  jvacc_
#   define jvposc jvposc_
#   define jvvelc jvvelc_
#   define kbdtc  kbdtc_
#   define kgvtc  kgvtc_
#   define kjtfc  kjtfc_
#   define kjtsc  kjtsc_
#   define kmatc  kmatc_
#   define kptfc  kptfc_
#   define kptsc  kptsc_
#   define ksetc  ksetc_
#   define ldttlc ldttlc_
#   define listc  listc_
#   define lnxlnc lnxlnc_
#   define loopsc loopsc_
#   define lpbfsc lpbfsc_
#   define lpchkc lpchkc_
#   define lpfilc lpfilc_
#   define lsacc  lsacc_
#   define lsforc lsforc_
#   define lsposc lsposc_
#   define lstfnc lstfnc_
#   define lsvalc lsvalc_
#   define lsvelc lsvelc_
#   define lvinhc lvinhc_
#   define massc  massc_
#   define mdmasc mdmasc_
#   define mkbdyc mkbdyc_
#   define mksldc mksldc_
#   define mndstc mndstc_
#   define mpyddc mpyddc_
#   define mpydrc mpydrc_
#   define msetc  msetc_
#   define nmacc  nmacc_
#   define nmforc nmforc_
#   define nmposc nmposc_
#   define nmvelc nmvelc_
#   define pbvlc  pbvlc_
#   define pcamc  pcamc_
#   define pcylc  pcylc_
#   define pfltc  pfltc_
#   define pgerc  pgerc_
#   define pgfitc pgfitc_
#   define phi0c  phi0c_
#   define phbvlc phbvlc_
#   define phcamc phcamc_
#   define phcylc phcylc_
#   define phfltc phfltc_
#   define phgerc phgerc_
#   define phopnc phopnc_
#   define phplnc phplnc_
#   define phrckc phrckc_
#   define phrgdc phrgdc_
#   define phscrc phscrc_
#   define phsltc phsltc_
#   define phsphc phsphc_
#   define phujtc phujtc_
#   define phxprc phxprc_
#   define phxrvc phxrvc_
#   define phyprc phyprc_
#   define phyrvc phyrvc_
#   define phzprc phzprc_
#   define phzrvc phzrvc_
#   define placc  placc_
#   define plforc plforc_
#   define plotc  plotc_
#   define plposc plposc_
#   define pltfnc pltfnc_
#   define plvalc plvalc_
#   define plvelc plvelc_
#   define pmatc  pmatc_
#   define pntsc  pntsc_
#   define popnc  popnc_
#   define post0c post0c_
#   define post1c post1c_
#   define pplnc  pplnc_
#   define prckc  prckc_
#   define prgdc  prgdc_
#   define printc printc_
#   define procsc procsc_
#   define pscrc  pscrc_
#   define psltc  psltc_
#   define psphc  psphc_
#   define ptacc  ptacc_
#   define pthckc pthckc_
#   define ptocrc ptocrc_
#   define ptposc ptposc_
#   define ptvelc ptvelc_
#   define pujtc  pujtc_
#   define pvsetc pvsetc_
#   define pxprc  pxprc_
#   define pxrvc  pxrvc_
#   define pyprc  pyprc_
#   define pyrvc  pyrvc_
#   define pzprc  pzprc_
#   define pzrvc  pzrvc_
#   define qbvlc  qbvlc_
#   define qcamc  qcamc_
#   define qcnRpc qcnRpc_
#   define qcrgnc qcrgnc_
#   define qcylc  qcylc_
#   define qdstnc qdstnc_
#   define qeoetc qeoetc_
#   define qeoexc qeoexc_
#   define qeonfc qeonfc_
#   define qfltc  qfltc_
#   define qfonfc qfonfc_
#   define qgerc  qgerc_
#   define qhtimc qhtimc_
#   define qntbc  qntbc_
#   define qopnc  qopnc_
#   define qplnc  qplnc_
#   define qponec qponec_
#   define qponfc qponfc_
#   define qponpc qponpc_
#   define qponvc qponvc_
#   define qpprmc qpprmc_
#   define qrckc  qrckc_
#   define qrfevc qrfevc_
#   define qscrc  qscrc_
#   define qsltc  qsltc_
#   define qsphc  qsphc_
#   define qujtc  qujtc_
#   define qxprc  qxprc_
#   define qxrvc  qxrvc_
#   define qyprc  qyprc_
#   define qyrvc  qyrvc_
#   define qzprc  qzprc_
#   define qzrvc  qzrvc_
#   define rdfilc rdfilc_
#   define rdgeoc rdgeoc_
#   define rdstlc rdstlc_
#   define readc  readc_
#   define resetc resetc_
#   define romegc romegc_
#   define rvelc  rvelc_
#   define scalec scalec_
#   define sdervc sdervc_
#   define sgacc  sgacc_
#   define sgforc sgforc_
#   define sgposc sgposc_
#   define sgvelc sgvelc_
#   define shapec shapec_
#   define showc  showc_
#   define sizec  sizec_
#   define sldstc sldstc_
#   define solidc solidc_
#   define sprngc sprngc_
#   define stacc  stacc_
#   define stforc stforc_
#   define storec storec_
#   define stposc stposc_
#   define stsetc stsetc_
#   define sttfnc sttfnc_
#   define stvalc stvalc_
#   define stvelc stvelc_
#   define tablec tablec_
#   define tfbdtc tfbdtc_
#   define tfjtfc tfjtfc_
#   define tforc  tforc_
#   define tformc tformc_
#   define tfptfc tfptfc_
#   define tfunc  tfunc_
#   define tgtojc tgtojc_
#   define titlec titlec_
#   define tmbdtc tmbdtc_
#   define tmdync tmdync_
#   define tmgvtc tmgvtc_
#   define tmjtdc tmjtdc_
#   define tmjtfc tmjtfc_
#   define tmjtsc tmjtsc_
#   define tmptdc tmptdc_
#   define tmptfc tmptfc_
#   define tmptsc tmptsc_
#   define tnumrc tnumrc_
#   define torqec torqec_
#   define trwjwc trwjwc_
#   define userc  userc_
#   define vcmplc vcmplc_
#   define vdervc vdervc_
#   define velc   velc_
#   define vevalc vevalc_
#   define vzeroc vzeroc_
#   define wdeltc wdeltc_
#   define wmatc  wmatc_
#   define wracc  wracc_
#   define wrforc wrforc_
#   define wrlstc wrlstc_
#   define wrpltc wrpltc_
#   define wrposc wrposc_
#   define wrtfnc wrtfnc_
#   define wrvalc wrvalc_
#   define wrvelc wrvelc_
#   define xaxesc xaxesc_
#   define xcntc  xcntc_
#   define xdmprc xdmprc_
#   define xdxinc xdxinc_
#   define xdync  xdync_
#   define xecutc xecutc_
#   define xforc  xforc_
#   define xic    xic_
#   define xjntc  xjntc_
#   define xjvarc xjvarc_
#   define xjxtrc xjxtrc_
#   define xbodyc xbodyc_
#   define xmassc xmassc_
#   define xpntc  xpntc_
#   define xrqstc xrqstc_
#   define xsgc   xsgc_
#   define xspngc xspngc_
#   define xtoknc xtoknc_
#   define xtorqc xtorqc_
#   define xvaluc xvaluc_
#   define zeroc  zeroc_
# endif

/* Prototypes for libimp. */
  extern void abortc();
  extern void acc();
  extern void accijc(
# ifdef ANSI
    Body *body, int kgc1, int kgc2, real A[6]);
# else
    body, kgc1, kgc2, A)
    Body *body;
    int kgc1, kgc2;
    real A[6];
# endif
  extern void adjstc();
  extern int  ajustc(
# ifdef ANSI
    real Jinv[], real E[], int irow[], int icol[], int irank);
# else
    Jinv, E, irow, icol, irank)
    real Jinv[], E[];
    int irow[], icol[], irank;
# endif
  extern void aldync(
# ifdef ANSI
    Body *body, real phi2dot[], real A[6]);
# else
    body, phi2dot, A)
    Body *body;
    real phi2dot[], A[6];
# endif
  extern void axesc(
# ifdef ANSI
    real size, Token names[], int n);
# else
    size, names, n)
    real size;
    Token names[];
    int n;
# endif
  extern void basec(
# ifdef ANSI
    Word name);
# else
    name)
    Word name;
# endif
  extern void beginc();
  extern int  bformc(
# ifdef ANSI
    int nfgc, real M[], real K[], complex eigvct[], complex Bstar[]);
# else
    nfgc, M K, eigvct, Bstar)
    int nfgc;
    real M[], K[];
    complex eigvct[], Bstar[];
# endif
  extern void bodyc(
# ifdef ANSI
    Word bdname, int n, Token sldnam[]);
# else
    bdname, n, sldnam)
    Word bdname;
    int n;
    Token sldnam[];
# endif
  extern void bsphrc(
# ifdef ANSI
    Solid *solid);
# else
    solid)
    Solid *solid;
# endif
  extern void checkc();
  extern void cleanc(
# ifdef ANSI
    Solid *solid);
# else
    solid)
    Solid *solid;
# endif
  extern void clearc();
  extern void closec();
  extern void cmatc(
# ifdef ANSI
    int nfgc, real D[]);
# else
    nfgc, D)
    int nfgc;
    real D[];
# endif
  extern void contac(
# ifdef ANSI
    Word cntname, Word sldbefr, Word sldaftr);
# else
    cntname, sldbefr, sldaftr)
    Word cntname, sldbefr, sldaftr;
# endif
  extern void dacc(
# ifdef ANSI
    Word name, real accel);
#else
    name, accel)
    Word name;
    real accel;
# endif
  extern void damprc(
# ifdef ANSI
    Word dmpnam, Word namptB, Word namptA);
# else
    dmpnam, namptB, namptA)
    Word dmpnam, namptB, namptA;
# endif
  extern void datac();
  extern void dbodyc(
# ifdef ANSI
    Word name, Word ref, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, ref, pt0, pt1, pt2)
    Word name, ref;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void dbvlc(
# ifdef ANSI
    Word name, real conei, real coneo);
# else
    name, conei, coneo)
    Word name;
    real conei, coneo;
# endif
  extern void dcamc(
# ifdef ANSI
    Word name, Token curveu, Token curvev);
# else
    name, curveu, curvev)
    Word name;
    Token curveu, curvev;
# endif
  extern void dcontc(
# ifdef ANSI
    Word cntname, real en, real et, real em, real emn, real mu);
# else
    cntname, en, et, em, emn, mu)
    Word cntname;
    real en, et, em, emn, mu;
# endif
  extern void dcylc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, pt0, pt1, pt2)
    Word name;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void ddaldc(
# ifdef ANSI
    Jvar *jvar, real W[6], real dphi, real dD[6]);
# else
    jvar, W, dphi, dD)
    Jvar *jvar;
    real W[6], dphi, dD[6];
# endif
  extern void ddampc(
# ifdef ANSI
    Word name, Token coeff[]);
# else
    name, coeff)
    Word name;
    Token coeff[];
# endif
  extern void ddmatc(
# ifdef ANSI
    Jvar *jvar, real W[6], int k, real dD[6]);
# else
    jvar, W, k, dD)
    Jvar *jvar;
    int  k;
    real W[6], dD[6];
# endif
  extern void deletc();
  extern void dforc(
# ifdef ANSI
    Word name, Token token[]);
# else
    name, token)
    Word name;
    Token token[];
# endif
  extern void dgearc(
# ifdef ANSI
    Word name, real ratio, real helix, real ctrdist);
# else
    name, ratio, helix, ctrdist)
    Word name;
    real ratio, helix, ctrdist;
# endif
  extern void dgravc(
# ifdef ANSI
    real gravx, real gravy, real gravz);
# else
    gravx, gravy, gravz)
    real gravx, gravy, gravz;
# endif
  extern void dic(
# ifdef ANSI
    Word name, Token token[]);
# else
    name, token)
    Word name;
    Token token[];
# endif
  extern void dinrtc(
# ifdef ANSI
    Word name, Word ref, real Ixx, real Iyy, real Izz, real Ixy,
      real Iyz, real Izx);
# else
    name, ref, Ixx, Iyy, Izz, Ixy, Iyz, Izx)
    Word name, ref;
    real Ixx, Iyy, Izz, Ixy, Iyz, Izx;
# endif
  extern void djvarc(
# ifdef ANSI
    Word name, Token values[]);
# else
    name, values)
    Word name;
    Token values[];
# endif
  extern void dmacc(
# ifdef ANSI
    Damper *damper, real acc[3]);
# else
    damper, acc)
    Damper *damper;
    real acc[3];
# endif
  extern void dmassc(
# ifdef ANSI
    Word name, Word ref, real m, Token rbar[3]);
# else
    name, ref, m, rbar)
    Word name, ref;
    real m;
    Token rbar[3];
# endif
  extern void dmatc();
  extern real dmforc(
# ifdef ANSI
    Damper *damper);
# else
    damper)
    Damper *damper;
# endif
  extern void dmotnc(
# ifdef ANSI
    Word name, Token token[]);
# else
    name, token)
    Word name;
    Token token[];
# endif
  extern void dmposc(
# ifdef ANSI
    Damper *damper, real pos[3]);
# else
    damper, pos)
    Damper *damper;
    real pos[3];
# endif
  extern void dmprpc(
# ifdef ANSI
    Word name, real density);
# else
    name, density)
    Word name;
    real density;
# endif
  extern void dmvelc(
# ifdef ANSI
    Damper *damper, real vel[3]);
# else
    damper, vel)
    Damper *damper;
    real vel[3];
# endif
  extern void dpntc(
# ifdef ANSI
    Word name, Word ref, real r[3]);
# else
    name, ref, r)
    Word name, ref;
    real r[3];
# endif
  extern void dpostc(
# ifdef ANSI
    Word name, real psi, real dpsi, int nsteps);
# else
    name, psi, dpsi, nsteps)
    Word name;
    real psi, dpsi;
    int nsteps;
# endif
  extern void dprmc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, pt0, pt1, pt2)
    Word name;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void dqbvlc(
# ifdef ANSI
    int ijv, int jjv, real phi[2], real conei, real coneo, real dQ[6]);
# else
    ijv, jjv, phi, conei, coneo, dQ)
    int  ijv, jjv;
    real phi[2], conei, coneo, dQ[6];
# endif
  extern void dqcamc(
# ifdef ANSI
    int ijv, int jjv, real phi[3], real u, real v, real du, real dv,
      real ddu, real ddv, real dQ[6]);
# else
    ijv, jjv, phi, u, v, du, dv, ddu, ddv, dQ)
    int ijv, jjv;
    real phi[3], u, v, du, dv, ddu, ddv, dQ[6]);
# endif
  extern void dqgerc(
# ifdef ANSI
    int ijv, int jjv, real phi[3], real ratio, real helix, real cd,
      real dQ[6]);
# else
    ijv, jjv, phi, ratio, helix, cd, dQ)
    int ijv, jjv;
    real phi[3], ratio, helix, cd, dQ[6];
# endif
  extern void dqopnc(
# ifdef ANSI
    int i, int j, real dQ[6]);
# else
    i, j, dQ)
    int  i, j;
    real dQ[6];
# endif
  extern void dqrckc(
# ifdef ANSI
    int ijv, int jjv, real radius, real helix, real dQ[6]);
# else
    ijv, jjv, radius, helix, dQ)
    int ijv, jjv;
    real radius, helix, dQ[6];
# endif
  extern void dqsltc(
# ifdef ANSI
    int ijv, int jjv, real u, real v, real du, real dv, real ddu,
      real ddv, real dQ[6]);
# else
    ijv, jjv, u, v, du, dv, ddu, ddv, dQ)
    int ijv, jjv;
    real u, v, du, dv, ddu, ddv, dQ[6]);
# endif
  extern void dqsphc(
# ifdef ANSI
    int i, int j, real dQ[6]);
# else
    i, j, dQ)
    int  i, j;
    real dQ[6];
# endif
  extern void drawc();
  extern void drckc(
# ifdef ANSI
    Word name, real radius, real helix);
# else
    name, radius, helix)
    Word name;
    real radius, helix;
# endif
  extern void drdmpc(
# ifdef ANSI
    real p[3], real q[3]);
# else
    p, q)
    real p[3], q[3];
# endif
  extern void drevc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3], Token pt3[3]);
# else
    name, pt0, pt1, pt2, pt3)
    Word name;
    Token pt0[3], pt1[3], pt2[3], pt3[3];
# endif
  extern void drfrcc(
# ifdef ANSI
    real p[3], real q[3]);
# else
    p, q)
    real p[3], q[3];
# endif
  extern void drgdc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, pt0, pt1, pt2)
    Word name;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void drspgc(
# ifdef ANSI
    real p[3], real q[3]
# endif
  );
  extern void drtrqc(
# ifdef ANSI
    real p[3], real q[3]);
# else
    p, q)
    real p[3], q[3];
# endif
  extern void dscrwc(
# ifdef ANSI
    Word name, real advnc);
# else
    name, advnc)
    Word name;
    real advnc;
# endif
  extern void dsetc();
  extern void dsltc(
# ifdef ANSI
    Word name, Token curveu, Token curvev);
# else
    name, curveu, curvev)
    Word name;
    Token curveu, curvev;
# endif
  extern int dsolvc(
# ifdef ANSI
    real Jinv[], real c[], real tol, real dq[]);
# else
    Jinv, c, tol, dq)
    real Jinv[], c[], tol, dq[];
# endif
  extern void dsphc(
# ifdef ANSI
    Word name, Token pt0[3]);
# else
    name, pt0)
    Word name;
    Token pt0[3];
# endif
  extern void dspngc(
# ifdef ANSI
    Word name, Token token[]);
# else
    name, token)
    Word name;
    Token token[];
# endif
  extern real dssldc(
# ifdef ANSI
    Solid *solid, real direc[3], real R[3], Vertex **vtx);
# else
    solid, direc, R, vtx)
    Solid *solid;
    real direc[3], R[3];
    Vertex **vtx;
# endif
  extern real dstABc(
# ifdef ANSI
    Solid *solidA, Solid *solidB, real direc[3], real Sk[3], 
      Vertex **VxA, Vertex **VxB);
# else
    solidA, solidB, direc, Sk, VxA, VxB)
    Solid *solidA, *solidB;
    real direc[3], Sk[3];
    Vertex **VxA, **VxB;
# endif
  extern void dtimec(
# ifdef ANSI
    real tfinal, real dtmin, real dtio);
# else
    tfinal, dtmin, dtio)
    real tfinal, dtmin, dtio;
# endif
  extern void dtorqc(
# ifdef ANSI
    Word name, Token token[]);
# else
    name, token)
    Word name;
    Token token[];
# endif
  extern void dujtc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, pt0, pt1, pt2)
    Word name;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void dvelc(
# ifdef ANSI
    Word name, real velocity);
# else
    name, velocity)
    Word name;
    real velocity;
# endif
  extern void dxrvc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, pt0, pt1, pt2)
    Word name;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void dxslc(
# ifdef ANSI
    Word name, Token pt0[3]);
# else
    name, pt0)
    Word name;
    Token pt0[3];
# endif
  extern void dynmxc();
  extern void dynm1c(
# ifdef ANSI
    int nfgc, real MDKG[], int icol[]);
# else
    nfgc, MDKG, icol)
    int nfgc;
    real MDKG[];
    int icol[];
# endif
  extern void dynm2c(
# ifdef ANSI
    int nfgc, real MDKG[], int irow[], complex Dyn[]);
# else
    nfgc, MDKG, irow, Dyn)
    int nfgc;
    real MDKG[];
    int irow[];
    complex Dyn[];
# endif
  extern int dynm3c(
# ifdef ANSI
    real t, complex Eigvct[], complex W[], real MDKG[], int nblock, 
      int bloksz[], int icol[]);
# else
    t, Eigvct, W, MDKG, nblock, bloksz, icol)
    real t;
    complex Eigvct[], W[];
    real MDKG[];
    int nblock, bloksz[], icol[];
# endif
  extern void dynm5c(
# ifdef ANSI
    int nfgc, real MDKG[], int irow[], real Dyn[]);
# else
    nfgc, MDKG, irow, Dyn)
    int nfgc;
    real MDKG[];
    int irow[];
    real Dyn[];
# endif
  extern void dyrvc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, pt0, pt1, pt2)
    Word name;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void dysetc();
  extern void dyslc(
# ifdef ANSI
    Word name, Token pt0[3]);
# else
    name, pt0)
    Word name;
    Token pt0[3];
# endif
  extern void dzrvc(
# ifdef ANSI
    Word name, Token pt0[3], Token pt1[3], Token pt2[3]);
# else
    name, pt0, pt1, pt2)
    Word name;
    Token pt0[3], pt1[3], pt2[3];
# endif
  extern void dzslc(
# ifdef ANSI
    Word name, Token pt0[3]);
# else
    name, pt0)
    Word name;
    Token pt0[3];
# endif
  extern void edsrtc(
# ifdef ANSI
    Face *face);
# else
    face)
    Face *face;
# endif
  extern void ematc(
# ifdef ANSI
    real E[]);
# else
    E)
    real E[];
# endif
  extern void endc();
  extern void endsvc();
  extern int  eqjstc(
# ifdef ANSI
    int nfgc, real KinvG[], real G[], int icol[]);
# else
    nfgc, KinvG, G, icol)
    int nfgc;
    real KinvG[], real G[];
    int icol[];
# endif
  extern void eqlibc();
  extern void fbdtc(
# ifdef ANSI
    Joint *joint, real f[6]);
# else
    joint, f)
    Joint *joint;
    real f[6];
# endif
  extern void fchekc(
# ifdef ANSI
    int nfgc, real M[], real D[], real G[], real *dforce, real *percnt);
# else
    nfgc, M, D, G, dforce, percnt)
    int nfgc;
    real M[], D[], G[], *dforce, *percnt;
# endif
  extern void fdervc(
# ifdef ANSI
    real Jinv[], int irow[], int icol[]);
# else
    Jinv, irow, icol)
    real Jinv[];
    int irow[], icol[];
# endif
  extern void fdync(
# ifdef ANSI
    Joint *joint, real f[6]);
# else
    joint, f)
    Joint *joint;
    real f[6];
# endif
  extern void fgvtc(
# ifdef ANSI
    Joint *joint, real f[6]);
# else
    joint, f)
    Joint *joint;
    real f[6];
# endif
  extern void fillc(
# ifdef ANSI
    long loopflags, real dmat[6], int ncol, real matrix[]);
# else
    loopflags, dmat, ncol, matrix)
    long loopflags;
    real dmat[6];
    int ncol;
    real matrix[];
# endif
  extern void fjtdc(
# ifdef ANSI
    real f[6]);
# else
    f)
    real f[6];
# endif
  extern void fjtfc(
# ifdef ANSI
    real f[6]);
# else
    f)
    real f[6];
# endif
  extern void fjtsc(
# ifdef ANSI
    real f[6]);
# else
    f)
    real f[6];
# endif
  extern void flnamc(
# ifdef ANSI
    int n, char *filename);
# else
    n, filename)
    int n;
    char *filename;
# endif
  extern void forcec(
# ifdef ANSI
    Word frcnam, Word namept, Word namptB, Word namptA);
# else
    frcnam, namept, namptB, namptA)
    Word frcnam, namept, namptB, namptA;
# endif
  extern void fptdc(
# ifdef ANSI
    Joint *joint, real f[6]);
# else
    joint, f)
    Joint *joint;
    real f[6];
# endif
  extern void fptfc(
# ifdef ANSI
    Joint *joint, real f[6]);
# else
    joint, f)
    Joint *joint;
    real f[6];
# endif
  extern void fptsc(
# ifdef ANSI
    Joint *joint, real f[6]);
# else
    joint, f)
    Joint *joint;
    real f[6];
# endif
  extern void freqnc();
  extern int  frmatc(
# ifdef ANSI
    int index, int n, enum Tkntyp kind);
# else
    index, n, kind)
    int index, n;
    enum Tkntyp kind;
# endif
  extern void fsetc();
  extern void gfbdtc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfdync(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfgvtc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfjtdc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfjtfc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfjtsc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gforc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfptdc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfptfc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void gfptsc(
# ifdef ANSI
    int nfgc, real G[]);
# else
    nfgc, G)
    int nfgc;
    real G[];
# endif
  extern void hdfgc();
  extern void hdngc(
# ifdef ANSI
    int lanimate);
# else
    lanimate)
    int lanimate;
# endif
  extern void hdsgc();
  extern void icsetc();
  extern void identc(
# ifdef ANSI
    Token kinds[], int nkinds);
# else
    kinds, nkinds)
    Token kinds[];
    int nkinds;
# endif
  extern void impctc(
# ifdef ANSI
    Contact *cntact);
# else
    cntact)
    Contact *cntact;
# endif
  extern void imvelc(
# ifdef ANSI
    Contact *cntact, enum Imptyp tangmode, enum Imptyp mommode, 
      enum Imptyp torsmode, real *fgcvel);
# else
    cntact, tangmode, mommode, torsmode, fgcvel)
    Contact *cntact;
    enum Imptyp tangmode, mommode, torsmode;
    real *fgcvel;
# endif
  extern int intfnc(
# ifdef ANSI
    Contact *cntact);
# else
    cntact)
    Contact *cntact;
# endif
  extern void intrpc();
  extern void jmatc(
# ifdef ANSI
    int nrows, int ncols, real *J, int *irow, int *icol);
# else
    nrows, ncols, J, irow, icol)
    int nrows, ncols;
    real *J;
    int *irow, *icol;
# endif
  extern void jointc(
# ifdef ANSI
    enum Jnttyp jttype, Word jtname, Word bdbefr, Word bdaftr);
# else
    jttype, jtname, bdbefr, bdaftr)
    enum Jnttyp jttype;
    Word jtname, bdbefr, bdaftr;
# endif
  extern void jtacc(
# ifdef ANSI
    Joint *joint, real acc[], int *n);
# else
    joint, acc, n)
    Joint *joint;
    real acc[];
    int *n;
# endif
  extern void jtforc(
# ifdef ANSI
    Joint *joint, real f[6]);
# else
    joint, f)
    Joint *joint;
    real f[6];
# endif
  extern void jtposc(
# ifdef ANSI
    Joint *joint, real pos[], int *n);
# else
    joint, pos, n)
    Joint *joint;
    real pos[];
    int *n;
# endif
  extern void jtvelc(
# ifdef ANSI
    Joint *joint, real vel[], int *n);
# else
    joint, vel, n)
    Joint *joint;
    real vel[];
    int *n;
# endif
  extern real jvacc(
# ifdef ANSI
    Jvar *jvar);
# else
    jvar)
    Jvar *jvar;
# endif
  extern real jvposc(
# ifdef ANSI
    Jvar *jvar);
# else
    jvar)
    Jvar *jvar;
# endif
  extern real jvvelc(
# ifdef ANSI
    Jvar *jvar);
# else
    jvar)
    Jvar *jvar;
# endif
  extern void kbdtc(
# ifdef ANSI
    int nfgc, real K[]);
# else
    nfgc, K)
    int nfgc;
    real K[];
# endif
  extern void kgvtc(
# ifdef ANSI
    int nfgc, real K[]);
# else
    nfgc, K)
    int nfgc;
    real K[];
# endif
  extern void kjtfc(
# ifdef ANSI
    int nfgc, real K[]);
# else
    nfgc, K)
    int nfgc;
    real K[];
# endif
  extern void kjtsc(
# ifdef ANSI
    int nfgc, real K[]);
# else
    nfgc, K)
    int nfgc;
    real K[];
# endif
  extern void kmatc(
# ifdef ANSI
    int nfgc, real K[]);
# else
    nfgc, K)
    int nfgc;
    real K[];
# endif
  extern void kptfc(
# ifdef ANSI
    int nfgc, real K[]);
# else
    nfgc, K)
    int nfgc;
    real K[];
# endif
  extern void kptsc(
# ifdef ANSI
    int nfgc, real K[]);
# else
    nfgc, K)
    int nfgc;
    real K[];
# endif
  extern void ksetc();
  extern void ldttlc(
# ifdef ANSI
    char *titel);
# else
    titel)
    char *titel;
# endif
  extern void listc(
# ifdef ANSI
    Word kind, Token *names, int n);
# else
    kind, names, n)
    Word kind;
    Token *names;
    int n;
# endif
  extern int lnxlnc(
# ifdef ANSI
    real r1[3], real r2[3], real r3[3], real r4[3], int ignore, 
      real *t1, real *t2);
# else
    r1, r2, r3, r4, ignore, t1, t2)
    real r1[3], r2[3], r3[3], r4[3];
    int ignore;
    real *t1, *t2;
# endif
  extern void loopsc();
  extern void lpbfsc(
# ifdef ANSI
    int nroot, int **incdnc, int **loops, int **paths);
# else
    nroot, incdnc, loops, paths)
    int nroot, **incdnc, **loops, **paths;
# endif
  extern void lpchkc(
# ifdef ANSI
    int **loops);
# else
    loops)
    int **loops;
# endif
  extern void lpfilc(
# ifdef ANSI
    int **loops);
# else
    loops)
    int **loops;
# endif
  extern void lsacc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void lsforc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void lsposc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void lstfnc( 
# ifdef ANSI
    complex Tnumr[], real wr[], real wi[], real w0, real wf, real winc, 
      Word kindin, Word namein, int nin, Token names[], int ntkns);
# else
    Tnumr, wr, wi, w0, wf, winc, kindin, namein, nin, names, ntkns)
    complex Tnumr[];
    real wr[], wi[], w0, wf, winc;
    Word kindin, namein;
    int nin;
    Token names[];
    int ntkns;
# endif
  extern void lsvalc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void lsvelc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern int lvinhc(
# ifdef ANSI
    real pnt[3], Hedge *hedge, Face *face);
# else
    pnt, hedge, face)
    real pnt[3];
    Hedge *hedge;
    Face *face;
# endif
  extern void massc(
# ifdef ANSI
    int nfgc, real M[]);
# else
    nfgc, M)
    int nfgc;
    real M[];
# endif
  extern void mdmasc(
# ifdef ANSI
    real M[], real D[], complex Eigvct[]);
# else
    M, D, Eigvct)
    real M[], D[];
    complex Eigvct[];
# endif
  extern Body *mkbdyc(
# ifdef ANSI
    Word bdname);
# else
    bdname)
    Word bdname;
# endif
  extern Solid *mksldc(
#ifdef ANSI
  Body *body);
#else
  body)
  Body  *body;
#endif
  extern real mndstc(
# ifdef ANSI
    Solid *solidA, Solid *solidB, real plndir[3], real RA[3], 
      real RB[3], Vertex *nrVtxs[4][2], real lambda[4], int *nVtxs);
# else
    solidA, solidB, plndir, RA, RB, nrVtxs, lambda, nVtxs)
    Solid *solidA, *solidB;
    real plndir[3], RA[3], RB[3];
    Vertex *nrVtxs[4][2];
    real lambda[4];
    int *nVtxs;
# endif
  extern void mpyddc(
# ifdef ANSI
    real d1[6], real d2[6], real dd[3][4]);
# else
    d1, d2, dd)
    real d1[6], d2[6], dd[3][4];
# endif
  extern void mpydrc(
# ifdef ANSI
    real D[6], real r[3], real Dr[3]);
# else
    D, r, Dr)
    real D[6], r[3], Dr[3];
# endif
  extern void msetc();
  extern void nmacc(
# ifdef ANSI
    Word name, enum Rectyp *kind, real acc[], int *n);
# else
    name, kind, acc, n)
    Word name;
    enum Rectyp *kind;
    real acc[];
    int *n;
# endif
  extern void nmforc(
# ifdef ANSI
    Word name, enum Rectyp *kind, real frc[], int *n);
# else
    name, kind, frc, n)
    Word name;
    enum Rectyp *kind;
    real frc[];
    int *n;
# endif
  extern void nmposc(
# ifdef ANSI
    Word name, enum Rectyp *kind, real pos[], int *n);
# else
    name, kind, pos, n)
    Word name;
    enum Rectyp *kind;
    real pos[];
    int *n;
# endif
  extern void nmvelc(
# ifdef ANSI
    Word name, enum Rectyp *kind, real vel[], int *n);
# else
    name, kind, vel, n)
    Word name;
    enum Rectyp *kind;
    real vel[];
    int *n;
# endif
  extern void pbvlc(
# ifdef ANSI
    real phi[2], real ratio, real radius, real Phi[3][4]);
# else
    phi, ratio, radius, Phi)
    real phi[2], ratio, radius, Phi[3][4];
# endif
  extern void pcamc(
# ifdef ANSI
    real phi[3], real u, real v, real du, real dv, real Phi[3][4]);
# else
    phi, u, v, du, dv, Phi)
    real phi[3], u, v, du, dv, Phi[3][4];
# endif
  extern void pcylc(
# ifdef ANSI
    real phi[2], real Phi[3][4]);
# else
    phi, Phi)
    real phi[2], Phi[3][4];
# endif
  extern void pfltc(
# ifdef ANSI
    real phi[3], real Phi[3][4]);
# else
    phi, Phi)
    real phi[3], Phi[3][4];
# endif
  extern void pgerc(
# ifdef ANSI
    real phi[3], real ratio, real helix, real cd, real Phi[3][4]);
# else
    phi, ratio, helix, cd, Phi)
    real phi[3], ratio, helix, cd, Phi[3][4];
# endif
  extern void pgfitc();
  extern void phi0c();
  extern int phbvlc(
# ifdef ANSI
    real Phi[3][4], real conei, real coneo, real phi[2]);
# else
    Phi, conei, coneo, phi)
    real Phi[3][4], conei, coneo, phi[2];
# endif
  extern int phcamc(
# ifdef ANSI
    real Phi[3][4], real phi[2]);
# else
    Phi. phi)
    real Phi[3][4], phi[2];
# endif
  extern int phcylc(
# ifdef ANSI
    real Phi[3][4], real phi[2]);
# else
    Phi. phi)
    real Phi[3][4], phi[2];
# endif
  extern int phfltc(
# ifdef ANSI
    real Phi[3][4], real phi[3]);
# else
    Phi. phi)
    real Phi[3][4], phi[3];
# endif
  extern int phgerc(
# ifdef ANSI
    real Phi[3][4], real ratio, real *cdist, real phi[3]);
# else
    Phi, ratio, cdist, phi)
    real Phi[3][4], ratio, *cdist, phi[3];
# endif
  extern void phopnc(
# ifdef ANSI
    real Phi[3][4], real phi[7]);
# else
    Phi. phi)
    real Phi[3][4], phi[7];
# endif
  extern int phplnc(
# ifdef ANSI
    real Phi[3][4], real phi[3]);
# else
    Phi. phi)
    real Phi[3][4], phi[3];
# endif
  extern int phrckc(
# ifdef ANSI
    real Phi[3][4], real *radius, real helix, real phi[3]);
# else
    Phi, radius, helix, phi)
    real Phi[3][4], *radius, helix, phi[3];
# endif
  extern int phrgdc(
# ifdef ANSI
    real Phi[3][4]);
# else
    Phi)
    real Phi[3][4];
# endif
  extern int phscrc(
# ifdef ANSI
    real Phi[3][4], real *phi);
# else
    Phi. phi)
    real Phi[3][4], *phi;
# endif
  extern int phsltc(
# ifdef ANSI
    real Phi[3][4], real phi[3]);
# else
    Phi. phi)
    real Phi[3][4], phi[3];
# endif
  extern int phsphc(
# ifdef ANSI
    real Phi[3][4], real phi[4]);
# else
    Phi. phi)
    real Phi[3][4], phi[4];
# endif
  extern int phujtc(
# ifdef ANSI
    real Phi[3][4], real phi[2]);
# else
    Phi. phi)
    real Phi[3][4], phi[2];
# endif
  extern int phxprc(
# ifdef ANSI
    real Phi[3][4], real *phi);
# else
    Phi. phi)
    real Phi[3][4], *phi;
# endif
  extern int phxrvc(
# ifdef ANSI
    real Phi[3][4], real *phi);
# else
    Phi. phi)
    real Phi[3][4], *phi;
# endif
  extern int phyprc(
# ifdef ANSI
    real Phi[3][4], real *phi);
# else
    Phi. phi)
    real Phi[3][4], *phi;
# endif
  extern int phyrvc(
# ifdef ANSI
    real Phi[3][4], real *phi);
# else
    Phi. phi)
    real Phi[3][4], *phi;
# endif
  extern int phzprc(
# ifdef ANSI
    real Phi[3][4], real *phi);
# else
    Phi. phi)
    real Phi[3][4], *phi;
# endif
  extern int phzrvc(
# ifdef ANSI
    real Phi[3][4], real *phi);
# else
    Phi. phi)
    real Phi[3][4], *phi;
# endif
  extern void placc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void plforc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void plotc(
# ifdef ANSI
    Word kind, Token *names, int n);
# else
    kind, names, n)
    Word kind;
    Token *names;
    int n;
# endif
  extern void plposc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void pltfnc(
# ifdef ANSI
    complex Tnumr[], real wr[], real wi[], real w0, real wf, real winc, 
    Word kindin, Word namein, int nin, Token names[], int ntkns);
# else
    Tnumr, wr, wi, w0, wf, winc, kindin, namein, nin, names, ntkns)
    complex Tnumr[];
    real wr[], wi[], w0, wf, winc;
    Word kindin, namein;
    int nin;
    Token names[];
    int ntkns;
# endif
  extern void plvalc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void plvelc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void pmatc();
  extern void pntsc(
# ifdef ANSI
    Word bdname, Token *names, int n);
# else
    bdname, names, n)
    Word bdname;
    Token *names;
    int n;
# endif
  extern void popnc(
# ifdef ANSI
    real phi[7], real Phi[3][4]);
# else
    phi, Phi)
    real phi[7], Phi[3][4];
# endif
  extern void post0c();
  extern void post1c();
  extern void pplnc(
# ifdef ANSI
    real phi[3], real Phi[3][4]);
# else
    phi, Phi)
    real phi[3], Phi[3][4];
# endif
  extern void prckc(
# ifdef ANSI
    real phi[3], real radius, real helix, real Phi[3][4]);
# else
    phi, radius, helix, Phi)
    real phi[3], radius, helix, Phi[3][4];
# endif
  extern void prgdc(
# ifdef ANSI
    real Phi[3][4]);
# else
    Phi)
    real Phi[3][4];
# endif
  extern void printc(
# ifdef ANSI
    Word kind, Token *names, int n);
# else
    kind, names, n)
    Word kind;
    Token *names;
    int n;
# endif
  extern void procsc();
  extern void pscrc(
# ifdef ANSI
    real phi, real advnc, real Phi[3][4]);
# else
    phi, advnc, Phi)
    real phi, advnc, Phi[3][4];
# endif
  extern void psltc(
# ifdef ANSI
    real phi[3], real u, real v, real Phi[3][4]);
# else
    phi, u, v, Phi)
    real phi[3], u, v, Phi[3][4];
# endif
  extern void psphc(
# ifdef ANSI
    real phi[4], real Phi[3][4]);
# else
    phi, Phi)
    real phi[4], Phi[3][4];
# endif
  extern void ptacc(
# ifdef ANSI
    Point *point, real pos[3], real vel[3], real acc[3]);
# else
    point, pos, vel, acc)
    Point *point;
    real pos[3], vel[3], acc[3];
# endif
  extern void pthckc(
# ifdef ANSI
    int **loops, int **paths);
# else
    loops, paths)
    int **loops, **paths;
# endif
  extern int ptocrc(
# ifdef ANSI
    real pnt[3], real ptcrc[][3], int *nptcrc);
# else
    pnt, ptcrc, nptcrc)
    real pnt[3], ptcrc[][3];
    int *nptcrc;
# endif
  extern void ptposc(
# ifdef ANSI
    Point *point, real pos[3]);
# else
    point, pos)
    Point *point;
    real pos[3];
# endif
  extern void ptvelc(
# ifdef ANSI
    Point *point, real pos[3], real vel[3]);
# else
    point, pos, vel)
    Point *point;
    real pos[3], vel[3];
# endif
  extern void pujtc(
# ifdef ANSI
    real phi[2], real Phi[3][4]);
# else
    phi, Phi)
    real phi[2], Phi[3][4];
# endif
  extern void pvsetc();
  extern void pxprc(
# ifdef ANSI
    real phi, real Phi[3][4]);
# else
    phi, Phi)
    real phi, Phi[3][4];
# endif
  extern void pxrvc(
# ifdef ANSI
    real phi, real Phi[3][4]);
# else
    phi, Phi)
    real phi, Phi[3][4];
# endif
  extern void pyprc(
# ifdef ANSI
    real phi, real Phi[3][4]);
# else
    phi, Phi)
    real phi, Phi[3][4];
# endif
  extern void pyrvc(
# ifdef ANSI
    real phi, real Phi[3][4]);
# else
    phi, Phi)
    real phi, Phi[3][4];
# endif
  extern void pzprc(
# ifdef ANSI
    real phi, real Phi[3][4]);
# else
    phi, Phi)
    real phi, Phi[3][4];
# endif
  extern void pzrvc(
# ifdef ANSI
    real phi, real Phi[3][4]);
# else
    phi, Phi)
    real phi, Phi[3][4];
# endif
  extern void qbvlc(
# ifdef ANSI
    real phi, real ratio, real radout, real Q[6]);
# else
    phi, ratio, radout, Q)
    real phi, ratio, radout, Q[6];
# endif
  extern void qcamc(
# ifdef ANSI
    int njvar, real phi[2], real u, real v, real du, real dv, real ddu,
      real ddv, real Q[6]);
# else
    njvar, phi, u, v, du, dv, ddu, ddv, Q)
    int njvar;
    real phi[2], u, v, du, dv, ddu, ddv, Q[6];
# endif
  extern real qcnRpc(
# ifdef ANSI
    real pnt[][3], int npnts, real center[3]);
# else
    pnt, npnts, center)
    real pnt[][3];
    int npnts;
    real center[3];
# endif
  extern int qcrgnc(
# ifdef ANSI
    Contact *cntact);
# else
    cntact)
    Contact *cntact;
# endif
  extern void qcylc(
# ifdef ANSI
    int njvar, real Q[6]);
# else
    njvar, Q)
    int njvar;
    real Q[6];
# endif
  extern int qdstnc(
# ifdef ANSI
    Contact *cntact);
# else
    cntact)
    Contact *cntact;
# endif
  extern int qeoetc(
# ifdef ANSI
    Edge *edge1, Edge *edge2, real pnt[2][3], int *npnts);
# else
    edge1, edge2, pnt, npnts)
    Edge *edge1, *edge2;
    real pnt[2][3];
    int *npnts;
# endif
  extern int qeoexc(
# ifdef ANSI
    Edge *edge1, Edge *edge2, real pnt[3]);
# else
    edge1, edge2, pnt)
    Edge *edge1, *edge2;
    real pnt[3];
# endif
  extern int qeonfc(
# ifdef ANSI
    Edge *edge, Face *face, real pnt[2][3], int *npnts);
# else
    edge, face, pnt, npnts)
    Edge *edge;
    Face *face;
    real pnt[2][3];
    int *npnts;
# endif
  extern void qfltc(
# ifdef ANSI
    int njvar, real phi[3], real Q[6]);
# else
    njvar, phi, Q)
    int njvar;
    real phi[3], Q[6];
# endif
  extern int qfonfc(
# ifdef ANSI
    Face *face1, Face *face2, real pnt[][3], int *npnts);
# else
    face1, face2, pnt, npnts)
    Face *face1, *face2;
    real pnt[][3];
    int *npnts;
# endif
  extern void qgerc(
# ifdef ANSI
    int njvar, real phi[3], real ratio, real helix, real cd, real Q[6]);
# else
    njvar, phi, ratio, helix, cd, Q)
    int  njvar;
    real phi[3], ratio, helix, cd, Q[6];
# endif
  extern void qhtimc(
# ifdef ANSI
    Contact *cntact, real RA[3], real RB[3]);
# else
    cntact, RA, RB)
    Contact *cntact;
    real RA[3], RB[3];
# endif
  extern int qntbc(
# ifdef ANSI
    Contact *cntact);
# else
    cntact)
    Contact *cntact;
# endif
  extern void qopnc(
# ifdef ANSI
    int njvar, real phi[7], real Q[6]);
# else
    njvar, phi, Q)
    int njvar;
    real phi[7], Q[6];
# endif
  extern void qplnc(
# ifdef ANSI
    int njvar, real phi[3], real Q[6]);
# else
    njvar, phi, Q)
    int njvar;
    real phi[3], Q[6];
# endif
  extern int qponec(
# ifdef ANSI
    real pnt[3], Edge *edge);
# else
    pnt, edge)
    real pnt[3];
    Edge *edge;
# endif
  extern int qponfc(
# ifdef ANSI
    real pnt[3], Face *face);
# else
    pnt, face)
    real pnt[3];
    Face *face;
# endif
  extern int qponpc(
# ifdef ANSI
    real pnt[3], Perim *perim, int *ignore, int *nvertx);
# else
    pnt, perim, ignore, nvertx)
    real pnt[3];
    Perim *perim;
    int *ignore, *nvertx;
# endif
  extern int qponvc(
# ifdef ANSI
    real pnt[3], Vertex *vertex);
# else
    pnt, vertex)
    real pnt[3];
    Vertex *vertex;
# endif
  extern int qpprmc(
# ifdef ANSI
    real pnt[3], Perim *perim, int *nvertx);
# else
    pnt, perim, nvertx)
    real pnt[3];
    Perim *perim;
    int *nvertx;
# endif
  extern void qrckc(
# ifdef ANSI
    int njvar, real phi[3], real radius, real helix, real Q[6]);
# else
    njvar, phi, radius, helix, Q)
    int  njvar;
    real phi[3], radius, helix, Q[6];
# endif
  extern void qrfevc(
# ifdef ANSI
    Solid *solid, real pnt[3], Face *faceon[], Edge *edgeon[], 
      Vertex *vtxon[], int *nfacon, int *nedgon, int *nvtxon);
# else
    solid, pnt, faceon, edgeon, vtxon, nfacon, nedgon, nvtxon)
    Solid  *solid;
    real    pnt[3];
    Face   *faceon[];
    Edge   *edgeon[];
    Vertex *vtxon[];
    int    *nfacon, *nedgon, *nvtxon;
# endif
  extern void qscrc(
# ifdef ANSI
    real advnc, real Q[6]);
# else
    advnc, Q)
    real advnc, Q[6];
# endif
  extern void qsltc(
# ifdef ANSI
    int njvar, real phi[2], real u, real v, real du, real dv,real Q[6]);
# else
    njvar, phi, u, v, du, dv, Q)
    int njvar;
    real phi[2], u, v, du, dv, Q[6];
# endif
  extern void qsphc(
# ifdef ANSI
    int njvar, real phi[4], real Q[6]);
# else
    njvar, phi, Q)
    int njvar;
    real phi[4], Q[6];
# endif
  extern void qujtc(
# ifdef ANSI
    int njvar, real phi[2], real Q[6]);
# else
    njvar, phi, Q)
    int njvar;
    real phi[2], Q[6];
# endif
  extern void qxprc(
# ifdef ANSI
    real Q[6]);
# else
    Q)
    real Q[6];
# endif
  extern void qxrvc(
# ifdef ANSI
    real Q[6]);
# else
    Q)
    real Q[6];
# endif
  extern void qyprc(
# ifdef ANSI
    real Q[6]);
# else
    Q)
    real Q[6];
# endif
  extern void qyrvc(
# ifdef ANSI
    real Q[6]);
# else
    Q)
    real Q[6];
# endif
  extern void qzprc(
# ifdef ANSI
    real Q[6]);
# else
    Q)
    real Q[6];
# endif
  extern void qzrvc(
# ifdef ANSI
    real Q[6]);
# else
    Q)
    real Q[6];
# endif
  extern void rdfilc(
# ifdef ANSI
    int lun, enum Outtyp outtyp, Word name, int *last, real *t,
      enum Rectyp *kind, int *mxdata, real *data);
# else
    lun, outtyp, name, last, t, kind, mxdata, data)
    int lun;
    enum Outtyp outtyp;
    Word name;
    int *last;
    real *t;
    enum Rectyp *kind;
    int *mxdata;
    real *data;
# endif
  extern void rdgeoc(
# ifdef ANSI
    int lun, Body *body, Solid *solid, char *datime);
# else
    lun, body, solid, datime);
    int lun;
    Body *body;
    Solid *solid;
    char *datime;
# endif
  extern void rdstlc(
# ifdef ANSI
    int lun, Body *body, Solid *solid);
# else
    lun, body, solid)
    int lun;
    Body *body;
    Solid *solid;
# endif
  extern void readc();
  extern void resetc();
  real romegc(
# ifdef ANSI
    Contact *cntact, real fgcvel[]);
# else
    cntact, fgcvel)
    Contact *cntact;
    real fgcvel[];
# endif
  real rvelc(
# ifdef ANSI
    Contact *cntact, real fgcvel[]);
# else
    cntact, fgcvel)
    Contact *cntact;
    real fgcvel[];
# endif
  extern void scalec();
  extern void sdervc();
  extern void sgacc(
# ifdef ANSI
    Spring *spring, real acc[3]);
# else
    spring, acc)
    Spring *spring;
    real acc[3];
# endif
  extern real sgforc(
# ifdef ANSI
    Spring *spring);
# else
    spring)
    Spring *spring;
# endif
  extern void sgposc(
# ifdef ANSI
    Spring *spring, real pos[3]);
# else
    spring, pos)
    Spring *spring;
    real pos[3];
# endif
  extern void sgvelc(
# ifdef ANSI
    Spring *spring, real vel[3]);
# else
    spring, vel)
    Spring *spring;
    real vel[3];
# endif
  extern void shapec(
# ifdef ANSI
    Word bdname, Token names[], int n);
# else
    bdname, names, n)
    Word bdname;
    Token *names;
    int n;
# endif
  extern void showc(
# ifdef ANSI
    int color, Token names[], int n);
# else
    color, names, n)
    int color;
    Token names[];
    int n;
# endif
  extern void sizec(
# ifdef ANSI
    real *xmin, real *ymin, real *zmin, real *xmax, real *ymax,
      real *zmax);
# else
    xmin, ymin, zmin, xmax, ymax, zmax)
    real *xmin, *ymin, *zmin, *xmax, *ymax, *zmax;
# endif
  extern void sldstc(
# ifdef ANSI
    int *nvxs, int irs[4], int jrs[4], real y[12], real del[16], 
      real zsol[3], real als[4], real *dstsq, int *lbackup);
# else
    nvxs, irs, jrs, y, del, zsol, als, dstsq, lbackup)
    int *nvxs, irs[4], jrs[4];
    real y[12], del[16], zsol[3], als[4], *dstsq;
    int *lbackup;
# endif
  extern void solidc(
# ifdef ANSI
    Word sldnam);
# else
    sldnam)
    Word sldnam;
# endif
  extern void sprngc(
# ifdef ANSI
    Word spgnam, Word namptB, Word namptA);
# else
    spgnam, namptB, namptA)
    Word spgnam, namptB, namptA;
# endif
  extern void stacc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void stforc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void storec(
# ifdef ANSI
    Word kind, Token *names, int n);
# else
    kind, names, n)
    Word kind;
    Token *names;
    int n;
# endif
  extern void stposc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void stsetc();
  extern void sttfnc(
# ifdef ANSI
    complex Tnumr[], real wr[], real wi[], Word kindin, Word namein, 
      int nin, Token names[], int ntkns);
# else
    Tnumr, wr, wi, kindin, namein, nin, names, ntkns)
    complex Tnumr[];
    real wr[], wi[];
    Word kindin, namein;
    int nin;
    Token names[];
    int ntkns;
# endif
  extern void stvalc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void stvelc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void tablec(
# ifdef ANSI
    char *fileid, Value *value);
# else
    fileid, value)
    char *fileid;
    Value *value;
# endif
  void tfbdtc(
# ifdef ANSI
    Torque *torque, real G[]);
# else
    torque, G)
    Torque *torque;
    real G[];
# endif
  void tfjtfc(
# ifdef ANSI
    Jvar *jvar, real G[]);
# else
    jvar, G)
    Jvar *jvar;
    real G[];
# endif
  extern void tforc(
# ifdef ANSI
    Word kindin, Word namein, int nin, real G[]);
# else
    kindin, namein, nin, G)
    Word kindin, namein;
    int nin;
    real G[];
# endif
  extern void tformc(
# ifdef ANSI
    complex Tnumr[], Word name, int nexp, Word kind, int *nmax, 
      real cons[], complex Tfn[]);
# else
    Tnumr, name, nexp, kind, nmax, cons, Tfn)
    complex Tnumr[];
    Word name;
    int nexp;
    Word kind;
    int *nmax;
    real cons[];
    complex Tfn[];
# endif
  void tfptfc(
# ifdef ANSI
    Force *force, real G[]);
# else
    force, G)
    Force *force;
    real G[];
# endif
  extern void tfunc();
  extern void tgtojc();
  extern void titlec(
# ifdef ANSI
    char *titel);
# else
    titel)
    char *titel;
# endif
  extern void tmbdtc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmdync(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmgvtc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmjtdc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmjtfc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmjtsc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmptdc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmptfc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tmptsc(
# ifdef ANSI
    int ngc, real G[]);
# else
    ngc, G)
    int ngc;
    real G[];
# endif
  extern void tnumrc(
# ifdef ANSI
    complex Eigvct[], real G[], complex tnumr[]);
# else
    Eigvct, G, tnumr)
    complex Eigvct[];
    real G[];
    complex tnumr[];
# endif
  extern void torqec(
# ifdef ANSI
    Word trqnam, Word nambdy, Word namptB, Word namptA);
# else
    trqnam, nambdy, namptB, namptA)
    Word trqnam, nambdy, namptB, namptA;
# endif
  extern real trwjwc(
# ifdef ANSI
    real w[6], real mass[4][4], real ww[3][4]);
# else
    w, mass, ww)
    real w[6], mass[4][4], ww[3][4];
# endif
  extern real userc(
# ifdef ANSI
    Word name, real t, int nderiv);
# else
    name, t, nderiv)
    Word name;
    real t;
    int nderiv;
# endif
  extern Value *vcmplc(
# ifdef ANSI
    Word name);
# else
    name)
    Word name;
# endif
  extern void vdervc(
# ifdef ANSI
    Joint *joint);
# else
    joint)
    Joint *joint;
# endif
  extern void velc();
  extern void vevalc(
# ifdef ANSI
    Value *value, real val[3]);
# else
    value, val)
    Value *value;
    real val[3];
# endif
  extern void vzeroc(
# ifdef ANSI
    enum Fnctyp type);
# else
    type)
    enum Fnctyp type;
# endif
  extern void wdeltc(
# ifdef ANSI
    Body *body, Joint *joint, int n, real W[6]);
# else
    body, joint, n, W)
    Body *body;
    Joint *joint;
    int n;
    real W[6];
# endif
  extern void wmatc(
# ifdef ANSI
    Body *body, int kgc, real wmat[6]);
# else
    body, kgc, wmat)
    Body *body;
    int kgc;
    real wmat[6];
# endif
  extern void wracc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void wrforc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void wrlstc();
  extern void wrpltc();
  extern void wrposc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void wrtfnc(
# ifdef ANSI
    complex Tnumr[], real wr[], real wi[], Word kindin, Word namein, 
      int nin, Token names[], int ntkns);
# else
    Tnumr. wr, wi, kindin, namein, nin, names, ntkns)
    complex Tnumr[];
    real wr[], wi[];
    Word kindin, namein;
    int nin;
    Token names[];
    int ntkns;
# endif
  extern void wrvalc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void wrvelc(
# ifdef ANSI
    Token name[], int n);
# else
    name, n)
    Token name[];
    int n;
# endif
  extern void xaxesc(
# ifdef ANSI
    Axes *axes);
# else
    axes)
    Axes *axes;
# endif
  extern void xcntc(
# ifdef ANSI
    Contact *contact);
# else
    contact)
    Contact *contact;
# endif
  extern void xdmprc(
# ifdef ANSI
    Damper *damper);
# else
    damper)
    Damper *damper;
# endif
  extern void xdxinc(
# ifdef ANSI
    real x[3][4], real d[6], real xdxinv[6]);
# else
    x, d, xdxinv)
    real x[3][4], d[6], xdxinv[6];
# endif
  extern void xdync();
  extern void xecutc();
  extern void xforc(
# ifdef ANSI
    Force *force);
# else
    force)
    Force *force;
# endif
  extern void xic(
# ifdef ANSI
    Ic *ic);
# else
    ic)
    Ic *ic;
# endif
  extern void xjntc(
# ifdef ANSI
    Joint *joint);
# else
    joint)
    Joint *joint;
# endif
  extern void xjvarc(
# ifdef ANSI
    Jvar *jvar);
# else
    jvar)
    Jvar *jvar;
# endif
  extern void xjxtrc(
# ifdef ANSI
    real x[3][4], real mass[10], real xjxtr[4][4]);
# else
    x, mass, xjxtr)
    real x[3][4], mass[10], xjxtr[4][4];
# endif
  extern void xbodyc(
# ifdef ANSI
    Body *body);
# else
    body)
    Body *body;
# endif
  extern void xmassc(
# ifdef ANSI
    Mass *mass);
# else
    mass)
    Mass *mass;
# endif
  extern void xpntc(
# ifdef ANSI
    Point *point);
# else
    point)
    Point *point;
# endif
  extern void xrqstc(
# ifdef ANSI
    Request *request);
# else
    request)
    Request *request;
# endif
  extern void xsgc(
# ifdef ANSI
    Sgc *sgc);
# else
    sgc)
    Sgc *sgc;
# endif
  extern void xspngc(
# ifdef ANSI
    Spring *spring);
# else
    spring)
    Spring *spring;
# endif
  extern void xtoknc(
# ifdef ANSI
    int index);
# else
    index)
    int index;
# endif
  extern void xtorqc(
# ifdef ANSI
    Torque *torque);
# else
    torque)
    Torque *torque;
# endif
  extern void xvaluc(
# ifdef ANSI
    Value *value);
# else
    value)
    Value *value;
# endif
  extern void zeroc(
# ifdef ANSI
    Word kind, Token tkn[]);
# else
    kind, tkn)
    Word kind;
    Token tkn[];
# endif
# define LIBIMP_INCLUDED
#endif
