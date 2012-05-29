/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:10 Jun 09                                          |
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
/* libcad-01 Jan 00:19 Nov 06
|    (C)Copyright, JJU Research, 2000-2006.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#ifndef LIBCAD_INCLUDED

/* Define double precision accuracy if desired. */
/*# define DOUBLE_PREC*//* IMP requires float precision for Jacobian. */
# ifdef  DOUBLE_PREC
    typedef double real;      /* Use double precision real variables. */
# else
    typedef float  real;      /* Use single precision real variables. */
# endif

# ifdef __STDC__
#   ifndef   ANSI
#     define ANSI
#   endif
# endif
# ifdef HP
#   ifdef ANSI
#     ifndef   _HPUX_SOURCE
#       define _HPUX_SOURCE
#     endif
#   endif
# endif
 
# include <assert.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# ifdef __WATCOMC__
#   include <malloc.h>
# else
#   include <memory.h>
# endif
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>
 
/* Xlib includes. */
# ifndef __WATCOMC__
#   include <X11/cursorfont.h>
#   include <X11/keysym.h>
#   include <X11/Xatom.h>
#   include <X11/Xlib.h>
#   include <X11/Xos.h>
#   include <X11/Xutil.h>
# endif
 
/* Parameter definitions. */
# define TRUE             (1)
# define FALSE            (0)
# define INDEF   (2139095041)   /* Pattern for an undefined long int. */
# define LSBREL           (0)    /* Least sig bit of a real (offset). */
# define MAXINT    (LONG_MAX)         /* Max integer value supported. */
# ifdef DOUBLE_PREC
#   define MAXDIG   (DBL_DIG) /* Number of sig digits per real value. */
#   define NBITS         (64)       /* Number of bits in a real word. */
#   define NBYTES         (8)      /* Number of bytes in a real word. */
#   define ZERO (DBL_EPSILON)              /* Default zero tolerance. */
# else
#   define MAXDIG   (FLT_DIG) /* Number of sig digits per real value. */
#   define NBITS         (32)       /* Number of bits in a real word. */
#   define NBYTES         (4)      /* Number of bytes in a real word. */
#   define ZERO (FLT_EPSILON)              /* Default zero tolerance. */
# endif
# define MXCHAR           (8)   /* Max chars in an alphanumeric Name. */
# define MXFLCH          (64) /* Max characters in a filename string. */
# define PI   (3.14159265359)                         /* Value of Pi. */
# define STDERR           (0)    /* Stream number for error messages. */
# define STDIN            (5)     /* Stream number of standard input. */
# define STDOUT           (6)    /* Stream number of standard output. */
  typedef char Name[MXCHAR+1];  /*MXCHAR characters + NULL character. */
 
/* iobfrc definitions. */
# define MXLUNS          (64)           /* Max number of i/o streams. */
# define MINLUN          (10) /* Lowest assignable i/o stream number. */
# define MXINBF          (80)  /* Max characters in the input buffer. */
# define MXIOBF          (80)  /* Max characters in a line of output. */
# define MXLINE          (24)        /* Default max lines per screen. */
  enum   Filtyp  {FT_ERROR=0, FT_ECHO,  FT_PRINT, FT_READ,  FT_SYMBOL,
                  FT_WRITE};
# define CHELP            '?'                      /* Help character. */
# define COOPS            '!'                      /* Oops character. */
# define COMMA            ','                     /* Comma character. */
# define SLASH            '/'                     /* Slash character. */
# define SPACE            ' '                     /* Space character. */
# define CTRLC   (2063809872)      /* Ctrl-C character from keyboard. */
# include "iobfrc.h"
 
/* devic definitions. */
# define MXDSPLAY         (3)              /* Number of device types. */
  enum   Dsptyp  {DT_NONE=0, DT_ALPHA, DT_GRAPHIC};
# define MXCHOICE         (3)       /* Number of choice device types. */
  enum   Chctyp  {CT_NONE=0, CT_ALPHA, CT_LOCATOR};
# define MXLOCATR         (4)      /* Number of locator device types. */
  enum   Loctyp  {LT_NONE=0, LT_ALPHA, LT_MOUSE, LT_TABLET};
# include "devic.h"

/* iodvc definitions. */
# include "iodvc.h"

/* diridc definitions. */
# include "diridc.h"
 
/* screnc definitions. */
# define MXGLOBAL    (5)  /* Max number of global options for drmnuc. */
# define MXHDRS      (7)    /* Max menu headers across top of screen. */
# define MXHEADER   (16)  /* Max number of header options for drmnuc. */
# define MXMENU     (32)    /* Max number of menu options for drmnuc. */
# define MXPOLY     (72)   /* Max number of points in filled polygon. */
# define MXDASH     (10)    /* Max segments in software dash pattern. */
# define MXSMBL     (16)               /* Number of centered symbols. */
# define AbstoPix(X,Y,S,T)     (X) = (int) ((real) xpix *        (S)),\
                               (Y) = (int) ((real) ypix * (1.0 - (T)))
# define PixtoAbs(S,T,X,Y)     (S) =       ((real) (X) / (real) xpix),\
                               (T) = 1.0 - ((real) (Y) / (real) ypix)
# include "screnc.h"

/* graphc definitions. */
# include "graphc.h"

/* pagec definitions. */
# include "pagec.h"

/* imagec definitions. */
# include "imagec.h"

/* colorc definitions. */
# define MXCOLOR    (16)                     /* Max number of colors. */
# define BLACK       (0)
# define WHITE       (1)
# include "colorc.h"
 
/* viewc definitions. */
# include "viewc.h"
 
/* viewsc definitions. */
# define MXVIEW     (16)            /* Max views stored in view file. */
# define MAGIC_NUM (0x4a4d4c00)        /* JJU View File Magic Number. */
# define VIEW_HEAD (4+(MXVIEW+1)*sizeof(int))/* Size of view file hdr.*/
# define VIEW_SIZE ((MXFLCH+1)+(9*sizeof(int)))/* Size of view record.*/
# include "viewsc.h"
 
/* Useful mathematical functions. */
# define aint(X)                ((real)(((X)>0.0)?(floor(X)):(ceil(X))))
// 3.Jan.2010 (L.K.)    Getting error E1100 for 'max' and 'min' already defined.
//                      Ensuring that they are redefined here.
#undef max
#undef min
# define max(X,Y)                                    (((X)>(Y))?(X):(Y))
# define min(X,Y)                                    (((X)<(Y))?(X):(Y))
# define max3(X,Y,Z)                             (max((X),max((Y),(Z))))
# define min3(X,Y,Z)                             (min((X),min((Y),(Z))))
# define max4(W,X,Y,Z)                  (max(max((W),(X)),max((Y),(Z))))
# define min4(W,X,Y,Z)                  (min(min((W),(X)),min((Y),(Z))))
# define max8(Q,R,S,T,W,X,Y,Z)              (max(max4((Q),(R),(S),(T)),\
                                                 max4((W),(X),(Y),(Z))))
# define min8(Q,R,S,T,W,X,Y,Z)              (min(min4((Q),(R),(S),(T)),\
                                                 min4((W),(X),(Y),(Z))))
# define nint(X)     ((int)(((X)>0.0)?(floor((X)+0.5)):(ceil((X)-0.5))))
# define sign(X,Y)                     (((Y)>=0.0)?(fabs(X)):(-fabs(X)))
 
  typedef void (*PFV)();  /* Pointer to a function that returns void. */
  typedef struct {real r; real i;} complex;
 
/* libcad routine names. */
# if defined(LINUX) || defined(MIPS) || defined(SUN)
 
/* libsys routine names. */
#   define abortc   abortc_
#   define ccnvrt   ccnvrt_
#   define clockc   clockc_
#   define clbitc   clbitc_
#   define clbitu   clbitu_
#   define datec    datec_
#   define fcnvrt   fcnvrt_
#   define iandc    iandc_
#   define iorc     iorc_
#   define ishftc   ishftc_
#   define isnanc   isnanc_
#   define ixorc    ixorc_
#   define lcasec   lcasec_
#   define ldbitc   ldbitc_
#   define ldbitu   ldbitu_
#   define ldnanc   ldnanc_
#   define ldnblc   ldnblc_
#   define ldnblu   ldnblu_
#   define lenc     lenc_
#   define licnsc   licnsc_
#   define lxcmpc   lxcmpc_
#   define notc     notc_
#   define qbitc    qbitc_
#   define qbitu    qbitu_
#   define qiactc   qiactc_
#   define qnblc    qnblc_
#   define sleepc   sleepc_
#   define stripc   stripc_
#   define todc     todc_
#   define ucasec   ucasec_

/* libmth routine names. */
#   define adj33c   adj33c_
#   define adj44c   adj44c_
#   define amnmxc   amnmxc_
#   define bsortc   bsortc_
#   define bsortu   bsortu_
#   define cabsc    cabsc_
#   define cbalnc   cbalnc_
#   define cblbkc   cblbkc_
#   define cdeflc   cdeflc_
#   define cdivc    cdivc_
#   define cexpc    cexpc_
#   define cgausc   cgausc_
#   define chesnc   chesnc_
#   define clessc   clessc_
#   define clr2c    clr2c_
#   define cmplxc   cmplxc_
#   define cmultc   cmultc_
#   define conjgc   conjgc_
#   define cplusc   cplusc_
#   define csqrtc   csqrtc_
#   define csvdc    csvdc_
#   define decisc   decisc_
#   define eigenc   eigenc_
#   define eigrsc   eigrsc_
#   define eigrsu   eigrsu_
#   define eigvec   eigvec_
#   define eigvlc   eigvlc_
#   define fservc   fservc_
#   define invrtc   invrtc_
#   define invxc    invxc_
#   define invxu    invxu_
#   define jnfc     jnfc_
#   define mpymmc   mpymmc_
#   define mpymmu   mpymmu_
#   define mpyxrc   mpyxrc_
#   define mpyxru   mpyxru_
#   define mpyxvc   mpyxvc_
#   define mpyxvu   mpyxvu_
#   define mpyxxc   mpyxxc_
#   define mpyxxu   mpyxxu_
#   define qsortc   qsortc_
#   define qsortu   qsortu_
#   define shsrtc   shsrtc_
#   define shsrtu   shsrtu_
#   define vabsc    vabsc_
#   define vabsu    vabsu_
#   define vcrosc   vcrosc_
#   define vdotc    vdotc_
#   define vdotu    vdotu_
#   define veqc     veqc_
#   define vequ     vequ_
#   define vlessc   vlessc_
#   define vnormc   vnormc_
#   define vnormu   vnormu_
#   define vplusc   vplusc_
 
/* libdvc routine names. */
#   define akbic    akbic_
#   define alprdc   alprdc_
#   define amodec   amodec_
#   define bannrc   bannrc_
#   define bellc    bellc_
#   define bfgetc   bfgetc_
#   define bfinc    bfinc_
#   define bflshc   bflshc_
#   define bfopnc   bfopnc_
#   define bfputc   bfputc_
#   define chcdvc   chcdvc_
#   define chsizc   chsizc_
#   define ckbic    ckbic_
#   define clrplc   clrplc_
#   define crlfc    crlfc_
#   define cursrc   cursrc_
#   define cursru   cursru_
#   define devic    devic_
#   define drmnuc   drmnuc_
#   define echoc    echoc_
#   define echonc   echonc_
#   define fbkspc   fbkspc_
#   define finplc   finplc_
#   define fnamec   fnamec_
#   define framac   framac_
#   define ftextc   ftextc_
#   define gtextc   gtextc_
#   define homec    homec_
#   define indvc    indvc_
#   define intrdc   intrdc_
#   define intrdu   intrdu_
#   define itextc   itextc_
#   define kbic     kbic_
#   define locdvc   locdvc_
#   define lunitc   lunitc_
#   define menuac   menuac_
#   define newpgc   newpgc_
#   define prntrc   prntrc_
#   define promtc   promtc_
#   define ptextc   ptextc_
#   define qchszc   qchszc_
#   define qdvc     qdvc_
#   define qfrmac   qfrmac_
#   define qkbic    qkbic_
#   define qpenac   qpenac_
#   define readrc   readrc_
#   define relrdc   relrdc_
#   define relrdu   relrdu_
#   define skbic    skbic_
#   define stdchc   stdchc_
#   define textc    textc_
#   define waitc    waitc_
#   define writrc   writrc_
 
/* libclr routine names. */
#   define clrgbc   clrgbc_
#   define clrgbu   clrgbu_
#   define clrpkc   clrpkc_
#   define clrpku   clrpku_
#   define clrvlc   clrvlc_
#   define cmapc    cmapc_
#   define colrac   colrac_
#   define colrau   colrau_
#   define colrfc   colrfc_
#   define colrfu   colrfu_
#   define colrsc   colrsc_
#   define colrsu   colrsu_
#   define ctablc   ctablc_
#   define cunpkc   cunpkc_
#   define cunpku   cunpku_
#   define icolrc   icolrc_
#   define idthrc   idthrc_
#   define idthru   idthru_
#   define ldclrc   ldclrc_
#   define ldclru   ldclru_
#   define ncolrc   ncolrc_
#   define qcmapc   qcmapc_
#   define qcolrc   qcolrc_
#   define rvsvdc   rvsvdc_
#   define tohlsc   tohlsc_
#   define torgbc   torgbc_
 
/* libndc routine names. */
#   define csmblc   csmblc_
#   define csmblu   csmblu_
#   define dashc    dashc_
#   define dashu    dashu_
#   define drwasc   drwasc_
#   define drwrsc   drwrsc_
#   define drwrsu   drwrsu_
#   define fillsc   fillsc_
#   define framsc   framsc_
#   define framsu   framsu_
#   define helpc    helpc_
#   define htextc   htextc_
#   define ldhdrc   ldhdrc_
#   define ldhdru   ldhdru_
#   define ldkhdc   ldkhdc_
#   define ldkhdu   ldkhdu_
#   define ldmnuc   ldmnuc_
#   define ldmnuu   ldmnuu_
#   define menusc   menusc_
#   define mltvc    mltvc_
#   define mltvuc   mltvuc_
#   define movasc   movasc_
#   define movasu   movasu_
#   define movrsc   movrsc_
#   define movrsu   movrsu_
#   define pntasc   pntasc_
#   define pntasu   pntasu_
#   define pntrsc   pntrsc_
#   define prcntc   prcntc_
#   define prcntu   prcntu_
#   define qaspsc   qaspsc_
#   define qdashc   qdashc_
#   define qfrmsc   qfrmsc_
#   define qhdrc    qhdrc_
#   define qheadc   qheadc_
#   define qlocsc   qlocsc_
#   define qpensc   qpensc_
#   define qsclsc   qsclsc_
#   define qzrosc   qzrosc_
#   define symblc   symblc_
#   define vtextc   vtextc_
#   define wrpenc   wrpenc_
 
/* libgrd routine names. */
#   define drwagc   drwagc_
#   define drwagu   drwagu_
#   define framgc   framgc_
#   define framgu   framgu_
#   define gaxisc   gaxisc_
#   define gridc    gridc_
#   define gridu    gridu_
#   define movagc   movagc_
#   define movagu   movagu_
#   define qfrmgc   qfrmgc_
#   define xgtosc   xgtosc_
 
/* lib2d routine names. */
#   define circlc   circlc_
#   define clipsc   clipsc_
#   define drwa2c   drwa2c_
#   define drwa2u   drwa2u_
#   define drwr2c   drwr2c_
#   define drwr2u   drwr2u_
#   define fill2c   fill2c_
#   define fram2c   fram2c_
#   define fram2u   fram2u_
#   define menu2c   menu2c_
#   define mova2c   mova2c_
#   define mova2u   mova2u_
#   define movr2c   movr2c_
#   deine  movr2u   movr2u_
#   define pnta2c   pnta2c_
#   define pntr2c   pntr2c_
#   define qasp2c   qasp2c_
#   define qfrm2c   qfrm2c_
#   define qloc2c   qloc2c_
#   define qorg2c   qorg2c_
#   define qpen2c   qpen2c_
#   define qscl2c   qscl2c_
#   define qzro2c   qzro2c_
#   define scal2c   scal2c_
#   define slid2c   slid2c_
#   define x2tosc   x2tosc_
#   define xsto2c   xsto2c_
 
/* lib3d routine names. */
#   define arro3c   arro3c_
#   define clip2c   clip2c_
#   define cnturc   cnturc_
#   define cnturu   cnturu_
#   define drwa3c   drwa3c_
#   define drwa3u   drwa3u_
#   define drwlnc   drwlnc_
#   define drwlnu   drwlnu_
#   define drwr3c   drwr3c_
#   define drwr3u   drwr3u_
#   define dvuec    dvuec_
#   define fill3c   fill3c_
#   define fram3c   fram3c_
#   define fram3u   fram3u_
#   define ldx32c   ldx32c_
#   define ldx32u   ldx32u_
#   define menu3c   menu3c_
#   define mnupkc   mnupkc_
#   define mnuptc   mnuptc_
#   define mova3c   mova3c_
#   define mova3u   mova3u_
#   define movr3c   movr3c_
#   define opnflc   opnflc_
#   define perspc   perspc_
#   define pnta3c   pnta3c_
#   define pntr3c   pntr3c_
#   define qfrntc   qfrntc_
#   define qfrntu   qfrntu_
#   define qloc3c   qloc3c_
#   define qorg3c   qorg3c_
#   define qpen3c   qpen3c_
#   define qscl3c   qscl3c_
#   define qx32c    qx32c_
#   define qx32u    qx32u_
#   define rgtvuc   rgtvuc_
#   define scal3c   scal3c_
#   define scal3u   scal3u_
#   define slid3c   slid3c_
#   define slidec   slidec_
#   define slideu   slideu_
#   define spur2c   spur2c_
#   define spur2u   spur2u_
#   define spur3c   spur3c_
#   define spur3u   spur3u_
#   define turn3c   turn3c_
#   define turn3u   turn3u_
#   define turnc    turnc_
#   define vclosc   vclosc_
#   define vdelc    vdelc_
#   define vdelu    vdelu_
#   define vdirc    vdirc_
#   define vopenc   vopenc_
#   define vreadc   vreadc_
#   define vreadu   vreadu_
#   define vstorc   vstorc_
#   define vstoru   vstoru_
#   define x2to3c   x2to3c_
#   define x2to3u   x2to3u_
#   define x3ndcc   x3ndcc_
#   define x3ndcu   x3ndcu_
#   define x3to2c   x3to2c_
#   define x3to2u   x3to2u_
#   define xformc   xformc_
#   define xformu   xformu_
#   define zclipc   zclipc_
#   define zclipu   zclipu_
 
/* miscellaneous routine names. */
#   define FMAIN    fmain_
#   define paintc   paintc_
 
/* miscellaneous routine names. */
# else
#   define FMAIN    fmain
#   define paintc   paintc
# endif
 
/*  MIPS doesn't like F77 doing the final compile step. */
# ifdef MIPS
#   define MAIN     MAIN__
# else
#   define MAIN     main
# endif
 
/* Prototype for <stdlib.h> to override Watcom compiler option. */
  extern char *_itoa(int value, char *buffer, int radix);

/* Prototypes for temporary service functions. */
  extern void ccnvrt(
# ifdef ANSI
    char *cstring, int *clength, char *fstring, int *flength);
# else
    cstring, clength, fstring, flength)
    char *cstring;
    int  *clength;
    char *fstring;
    int  *flength;
# endif
  extern void fcnvrt(
# ifdef ANSI
    char *fstring, int *flength, char *cstring);
# else
    fstring, flength, cstring)
    char *fstring;
    int  *flength;
    char *cstring;
# endif

/* Prototypes for libsys. */
  extern void abortc();
  extern void clbitc(
# ifdef ANSI
    int nbit, void *word);
# else
    nbit, word)
    int   nbit;
    void *word;
# endif
  extern void clbitu(
# ifdef ANSI
    int *nbit, void *word);
# else
    nbit, word)
    int  *nbit;
    void *word;
# endif
  extern void clockc(
# ifdef ANSI
    int *imins, int *isecs);
# else
    imins, isecs)
    int  *imins, *isecs;
# endif
  extern void datec(
# ifdef ANSI
    char *adate);
# else
    adate)
    char *adate;
# endif
  extern unsigned long iandc(
# ifdef ANSI
    void *iword1, void *iword2);
# else
    iword1, iword2)
    void *iword1, *iword2;
# endif
  extern unsigned long iorc(
# ifdef ANSI
    void *iword1, void *iword2);
# else
    iword1, iword2)
    void *iword1, *iword2;
# endif
  extern unsigned long ishftc(
# ifdef ANSI
    void *iword, int ibits);
# else
    iword, ibits)
    void *iword;
    int   ibits;
# endif
  extern int isnanc(
# ifdef ANSI
    void *word);
# else
    word)
    void *word;
# endif
  extern unsigned long ixorc(
# ifdef ANSI
    void *iword1, void *iword2);
# else
    iword1, iword2)
    void *iword1, *iword2;
# endif
  extern void lcasec(
# ifdef ANSI
    char *string);
# else
    string)
    char *string;
# endif
  extern void ldbitc(
# ifdef ANSI
    int nbit, void *word);
# else
    nbit, word)
    int   nbit;
    void *word;
# endif
  extern void ldbitu(
# ifdef ANSI
    int *nbit, void *word);
# else
    nbit, word)
    int  *nbit;
    void *word;
# endif
  extern void ldnanc(
# ifdef ANSI
    void *word);
# else
    word)
    void *word;
# endif
  extern void ldnblc(
# ifdef ANSI
    int intger, void *word);
# else
    intger, word)
    int   intger;
    void *word;
# endif
  extern void ldnblu(
# ifdef ANSI
    int *intger, void *word);
# else
    intger, word)
    int *intger;
    void *word;
# endif
  extern int lenc(
# ifdef ANSI
    char *string);
# else
    string)
    char *string;
# endif
  extern void licnsc();
  extern int  lxcmpc(
# ifdef ANSI
    char *cword1, char *cword2);
# else
    cword1, cword2)
    char *cword1, *cword2;
# endif
  extern unsigned long notc(
# ifdef ANSI
    void *word);
# else
    word)
    void *word;
# endif
  extern int opnflc(
# ifdef ANSI
    int *lun, enum Filtyp type, char *rwflag, char *keyword,
      char *filename);
# else
    lun, type, rwflag, keyword, filename)
    int *lun;
    enum  Filtyp type;
    char *rwflag, *keyword, *filename;
# endif
  extern int qbitc(
# ifdef ANSI
    int nbit, void *word);
# else
    nbit, word)
    int   nbit;
    void *word;
# endif
  extern int qbitu(
# ifdef ANSI
    int *nbit, void *word);
# else
    nbit, word)
    int  *nbit;
    void *word;
# endif
  extern int qiactc();
  extern int qnblc(
# ifdef ANSI
    void *word);
# else
    word)
    void *word;
# endif
  extern void sleepc(
# ifdef ANSI
    real secnds);
# else
    secnds)
    real secnds;
# endif
  extern void stripc(
# ifdef ANSI
    char *string);
# else
    string)
    char *string;
# endif
  extern void todc(
# ifdef ANSI
    char *tod);
# else
    tod)
    char *tod;
# endif
  extern void ucasec(
# ifdef ANSI
    char *string);
# else
    string)
    char *string;
# endif
 
/* Prototypes for libmth. */
  extern void adj33c(
# ifdef ANSI
    real a[3][3], real adj[3][3]);
# else
    a[3][3], adj[3][3])
    real a[3][3], adj[3][3];
# endif
  extern void adj44c(
# ifdef ANSI
    real a[4][4], real adj[4][4]);
# else
    a[4][4], adj[4][4])
    real a[4][4], adj[4][4];
# endif
  extern void amnmxc(
# ifdef ANSI
    real array[], int nrows, int nkols, real *amin, real *amax);
# else
    array[], nrows, nkols, amin, amax)
    real  array[];
    int   nrows, nkols;
    real *amin, *amax;
# endif
  extern void bsortc(
# ifdef ANSI
    int n, real array[]);
# else
    n, array[])
    int  n;
    real array[];
# endif
  extern void bsortu(
# ifdef ANSI
    int *n, real array[]);
# else
    n, array[])
    int *n;
    real array[];
# endif
  extern real cabsc(
# ifdef ANSI
    complex value);
# else
    value)
    complex value;
# endif
  extern void cbalnc(
# ifdef ANSI
    int n, complex H[], int *low, int *high, real scale[]);
# else
    n, H[], low, high, scale[])
    int     n;
    complex H[];
    int    *low, *high;
    real    scale[];
# endif
  extern void cblbkc(
# ifdef ANSI
    int n, int low, int high, int m, int intger[], real scale[], 
      complex Z[]);
# else
    n, low, high, m, intger[], scale[], Z[])
    int     n, low, high, m, intger[];
    real    scale[];
    complex Z[];
# endif
  extern int cdeflc(
# ifdef ANSI
    int n, int kb, complex H[], complex Z[], real tolfnm, int id, 
      real c1, real c2, real *dlsq);
# else
    n, kb, H[], Z[], tolfnm, id, c1, c2, *dlsq)
    int     n, kb;
    complex H[], Z[];
    real    tolfnm;
    int     id;
    real    c1, c2, *dlsq;
# endif
  extern complex cdivc(
# ifdef ANSI
    complex a, complex b);
# else
    a, b)
    complex a, b;
# endif
  extern complex cexpc(
# ifdef ANSI
    complex value);
# else
    value)
    complex value;
# endif
  extern int cgausc(
# ifdef ANSI
    complex A[], int n, complex C[], int m);
# else
    A[], n, C[], m)
    complex A[];
    int     n;
    complex C[];
    int     m;
# endif
  extern void chesnc(
# ifdef ANSI
    int n, int low, int high, complex H[], int intger[]);
# else
    n, low, high, H[], intger[])
    int     n, low, high;
    complex H[];
    int     intger[];
# endif
  extern complex clessc(
# ifdef ANSI
    complex a, complex b);
# else
    a, b)
    complex a, b;
# endif
  extern int clr2c(
# ifdef ANSI
    int n, int lvects, int low, int high, int intger[], complex H[], 
      complex W[], complex Z[]);
# else
    n, lvects, low, high, intger[], H[], W[], Z[])
    int     n, lvects, low, high, intger[];
    complex H[], W[], Z[];
# endif
  extern complex cmplxc(
# ifdef ANSI
    real creal, real cimag);
# else
    creal, cimag)
    real creal, cimag;
# endif
  extern complex cmultc(
# ifdef ANSI
    complex a, complex b);
# else
    a, b)
    complex a, b;
# endif
  extern complex conjgc(
# ifdef ANSI
    complex value);
# else
    value)
    complex value;
# endif
  extern complex cplusc(
# ifdef ANSI
    complex a, complex b);
# else
    a, b)
    complex a, b;
# endif
  extern complex csqrtc(
# ifdef ANSI
    complex value);
# else
    value)
    complex value;
# endif
  extern void csvdc(
# ifdef ANSI
  complex H[], int mmax, int nmax, int m, int n, int np, int nu, int nv, 
    real s[], complex U[], complex V[]);
# else
  H[], mmax, nmax, m, n, np, nu, nv, s[], U[], V[])
  complex H[];
  int     mmax, nmax, m, n, np, nu, nv;
  real    s[];
  complex U[], V[]
# endif
  extern void decisc(
# ifdef ANSI
    int n, int nblock, int ndel[], complex Wmlt[], complex H[]);
# else
    n, nblock, ndel[], Wmlt[], H[])
    int     n, nblock, ndel[];
    complex Wmlt[], H[];
# endif
  extern int eigenc(
# ifdef ANSI
    real a[], int n, int lgoto, real wr[], real wi[], complex eigvct[]);
# else
    a[], n, lgoto, wr[], wi[], eigvct[])
    real    a[];
    int     n, lgoto;
    real    wr[], wi[];
    complex eigvct[];
# endif
  extern void eigrsc(
# ifdef ANSI
    real a[], int n, real eigvct[]);
# else
    a[], n, eigvct[])
    real a[];
    int  n;
    real eigvct[];
# endif
  extern void eigrsu(
# ifdef ANSI
    real a[], int *n, real eigvct[]);
# else
    a[], *n, eigvct[])
    real a[];
    int *n;
    real eigvct[];
# endif
  extern int eigvec(
# ifdef ANSI
    real a[], int n, real wr[], real wi[], complex eigvct[]);
# else
    a[], n, wr[], wi[], eigvct[])
    real    a[];
    int     n;
    real    wr[], wi[];
    complex eigvct[];
# endif
  extern int eigvlc(
# ifdef ANSI
    real a[], int n, real wr[], real wi[]);
# else
    a[], n, wr[], wi[])
    real a[];
    int n;
    real wr[], wi[];
# endif
  extern void fservc(
# ifdef ANSI
    real x, real xmin, real xmax, complex coeff[], int ncoeff, real *y,
      real *dy, real *ddy);
# else
    x, xmin, xmax, coeff[], ncoeff, *y, *dy, *ddy)
    real    x, xmin, xmax;
    complex coeff[];
    int     ncoeff;
    real   *y, *dy, *ddy;
# endif
  extern void invrtc(
# ifdef ANSI
    real a[], int m, int n, int nfree, real zero, int *irank, real *det,
      int irow[], int icol[]);
# else
    a[], m, n, nfree, zero, *irank, *det, irow[], icol[])
    real  a[];
    int   m, n, nfree;
    real  zero;
    int  *irank;
    real *det;
    int   irow[], icol[];
# endif
  extern void invxc(
# ifdef ANSI
    real x[3][4], real xinv[3][4]);
# else
    x[3][4], xinv[3][4])
    real x[3][4], xinv[3][4];
# endif
  extern void invxu(
# ifdef ANSI
    real x[12], real xinv[12]);
# else
    x[12], xinv[12])
    real x[12], xinv[12];
# endif
  extern int jnfc(
# ifdef ANSI
    int n, int istep, real ein, real tol, complex H[], complex Z[], 
      complex W[], real supd[], int nxt[], int ndel[], int ndefl[], 
      int ndb[], int *nblock, real dele[], real sm[]);
# else
    n, istep, ein, tol, H[], Z[], W[], supd[], nxt[], ndel[], ndefl[], 
      ndb[], *nblock, dele[], sm[])
    int     n, istep;
    real    ein, tol;
    complex H[], Z[], W[];
    real    supd[];
    int     nxt[], ndel[], ndefl[], ndb[], *nblock;
    real    dele[], sm[];
# endif
  extern void mpymmc(
# ifdef ANSI
    int nrowsa, int ncolsa, int ncolsb, real a[], real b[], real c[]);
# else
    nrowsa, ncolsa, ncolsb, a[], b[], c[])
    int  nrowsa, ncolsa, ncolsb;
    real a[], b[], c[];
# endif
  extern void mpymmu(
# ifdef ANSI
    int *nrowsa, int *ncolsa, int *ncolsb, real a[], real b[],
      real c[]);
# else
    *nrowsa, *ncolsa, *ncolsb, a[], b[], c[])
    int  *nrowsa, *ncolsa, *ncolsb;
    real  a[], b[], c[];
# endif
  extern void mpyxrc(
# ifdef ANSI
    real x[3][4], real r[3], real xr[3]);
# else
    x[3][4], r[3], xr[3])
    real x[3][4], r[3], xr[3];
# endif
  extern void mpyxru(
# ifdef ANSI
    real x[12], real r[3], real xr[3]);
# else
    x[12], r[3], xr[3])
    real x[12], r[3], xr[3];
# endif
  extern void mpyxvc(
# ifdef ANSI
    real x[3][4], real v[3], real xv[3]);
# else
    x[3][4], v[3], xv[3])
    real x[3][4], v[3], xv[3];
# endif
  extern void mpyxvu(
# ifdef ANSI
    real x[12], real v[3], real xv[3]);
# else
    x[12], v[3], xv[3])
    real x[12], v[3], xv[3];
# endif
  extern void mpyxxc(
# ifdef ANSI
    real x1[3][4], real x2[3][4], real xx[3][4]);
# else
    x1[3][4], x2[3][4], xx[3][4])
    real x1[3][4], x2[3][4], xx[3][4];
# endif
  extern void mpyxxu(
# ifdef ANSI
    real x1[12], real x2[12], real xx[12]);
# else
    x1[12], x2[12], xx[12])
    real x1[12], x2[12], xx[12];
# endif
  extern void qsortc(
# ifdef ANSI
    int n, real array[]);
# else
    n, array[])
    int  n;
    real array[];
# endif
  extern void qsortu(
# ifdef ANSI
    int *n, real array[]);
# else
    n, array[])
    int  *n;
    real  array[];
# endif
  extern void shsrtc(
# ifdef ANSI
    int n, real array[], int iarray[]);
# else
    n, array[], iarray[])
    int  n;
    real array[];
    int  iarray[];
# endif
  extern void shsrtu(
# ifdef ANSI
    int *n, real array[], int iarray[]);
# else
    n, array[], iarray[])
    int  *n;
    real  array[];
    int   iarray[];
# endif
  extern real vabsc(
# ifdef ANSI
    int n, real v[]);
# else
    n, v[])
    int n;
    real v[];
# endif
  extern real vabsu(
# ifdef ANSI
    int *n, real v[]);
# else
    n, v[])
    int  *n;
    real  v[];
# endif
  extern void vcrosc(
# ifdef ANSI
    real v[3], real u[3], real vxu[3]);
# else
    v[3], u[3], vxu[3])
    real v[3], u[3], vxu[3];
# endif
  extern real vdotc(
# ifdef ANSI
    int n, real v[], real u[]);
# else
    n, v[], u[])
    int  n;
    real v[], u[];
# endif
  extern real vdotu(
# ifdef ANSI
    int *n, real v[], real u[]);
# else
    n, v[], u[])
    int  *n;
    real  v[], u[];
# endif
  extern void veqc(
# ifdef ANSI
    int n, real u[], real v[]);
# else
    n, u[], v[])
    int  n;
    real u[], v[];
# endif
  extern void vequ(
# ifdef ANSI
    int *n, real u[], real v[]);
# else
    n, u[], v[])
    int  *n;
    real  u[], v[];
# endif
  extern void vlessc(
# ifdef ANSI
    int n, real v[], real u[], real w[]);
# else
    n, v[], u[], w[])
    int  n;
    real v[], u[], w[];
# endif
  extern void vnormc(
# ifdef ANSI
    int n, real v[]);
# else
    n, v[])
    int  n;
    real v[];
# endif
  extern void vnormu(
# ifdef ANSI
    int *n, real v[]);
# else
    n, v[])
    int *n;
    real v[];
# endif
  extern void vplusc(
# ifdef ANSI
    int n, real v[], real u[], real w[]);
# else
    n, v[], u[], w[])
    int  n;
    real v[], u[], w[];
# endif
 
/* Prototypes for libx. */
  extern void xclosc(
# ifdef ANSI
#   ifndef __WATCOMC__
      Window w
#   endif
# endif
  );
  extern void xcolrc(
# ifdef ANSI
#   ifndef __WATCOMC__
      Display *dsplay, int screen
#   endif
# endif
  );
  extern void xendc();
  extern void xinitc();
# ifdef __WATCOMC__
    void xloopc(
# else
    Xevent *xloopc(
#   ifdef ANSI
      Mask emask
#   endif
# endif
  );
  extern void xmkgcc(
# ifdef ANSI
#   ifndef __WATCOMC__
      Display *dsplay, Window wndw
#   endif
# endif
  );
# ifdef __WATCOMC__
    extern void xopenc(
# else
    Window xopenc(
#   ifdef ANSI
      Window parent
#   endif
# endif
  );
  extern void xposec();
  extern void xrdlnc();
  extern void xreszc(
# ifdef ANSI
#   ifndef __WATCOMC__
      XConfigureEvent *xce
#   endif
# endif
  );
 
/* Prototypes for libdvc. */
  extern void akbic();
  extern void alprdc(
# ifdef ANSI
    char *dfault, char *alprd);
# else
    dfault, alprd)
    char *dfault, *alprd;
# endif
  extern void amodec();
  extern void bannrc(
# ifdef ANSI
    char *title, char *releas, char *cpyrgt);
# else
    title, releas, cpyrgt)
    char *title, *releas, *cpyrgt;
# endif
  extern void bellc();
  extern void bfgetc(
# ifdef ANSI
    char *string);
# else
    string)
    char *string;
# endif
  extern int bfinc(
# ifdef ANSI
    char *eorchr);
# else
    eorchr)
    char *eorchr;
# endif
  extern void bflshc();
  extern void bfopnc();
  extern void bfputc(
# ifdef ANSI
    char *string);
# else
    string)
    char *string;
# endif
  extern void chcdvc(
# ifdef ANSI
    char *kind);
# else
    kind)
    char *kind;
# endif
  extern void chsizc(
# ifdef ANSI
    real width);
# else
    width)
    real width;
# endif
  extern void ckbic();
  extern void clrplc();
  extern void crlfc();
  extern void cursrc(
# ifdef ANSI
    int cflag);
# else
    cflag)
    int cflag;
# endif
  extern void cursru(
# ifdef ANSI
    int *cflag);
# else
    cflag)
    int *cflag;
# endif
  extern void devic(
# ifdef ANSI
    char *kind);
# else
    kind)
    char *kind;
# endif
  extern void drmnuc();
  extern void echoc();
  extern void echonc(
# ifdef ANSI
    int lun);
# else
    lun)
    int lun;
# endif
  extern void fbkspc(
# ifdef ANSI
    int lun);
# else
    lun)
    int lun;
# endif
  extern void finplc();
  extern void fnamec(
# ifdef ANSI
    char *filename, char *fileid);
# else
    filename, fileid)
    char *filename, *fileid;
# endif
  extern void framac(
# ifdef ANSI
    int imx, int jmx);
# else
    imx, jmx)
    int imx, jmx;
# endif
  extern void ftextc(
# ifdef ANSI
    real value);
# else
    value)
    real value;
# endif
  extern void gtextc(
#ifdef ANSI
    real value);
#else
    value)
    real value;
#endif
  extern void homec();
  extern void indvc();
  extern int intrdc(
# ifdef ANSI
    int ideflt, int *istate);
# else
    ideflt, istate)
    int ideflt, *istate;
# endif
  extern int intrdu(
# ifdef ANSI
    int *ideflt, int *istate);
# else
    ideflt, istate)
    int *ideflt, *istate;
# endif
  extern void itextc(
# ifdef ANSI
    int intger);
# else
    intger)
    int intger;
# endif
  extern void kbic(
# ifdef ANSI
    int nsignal);
# else
    nsignal)
    int nsignal;
# endif
  extern void locdvc(
# ifdef ANSI
    char *kind);
# else
    kind)
    char *kind;
# endif
  extern int lunitc(
# ifdef ANSI
    char *type);
# else
    type)
    char *type;
# endif
  extern int  menuac();
  extern void newpgc();
  extern void prntrc(
# ifdef ANSI
    char *filename, char *title, char *release, char *cpyrgt);
# else
    filename, title, release, cpyrgt)
    char *filename, *title, *release, *cpyrgt;
# endif
  extern void promtc();
  extern void ptextc(
#ifdef ANSI
    void *value);
#else
    value)
    void *value;
#endif
  extern void qchszc(
# ifdef ANSI
    real *hsymbl, real *vsymbl);
# else
    hsymbl, vsymbl)
    real *hsymbl, *vsymbl;
# endif
  extern void qdvc(
# ifdef ANSI
    char *dsplay, char *chdevc, char *lcdevc);
# else
    dsplay, chdevc, lcdevc)
    char *dsplay, *chdevc, *lcdevc;
# endif
  extern void qfrmac(
# ifdef ANSI
    int *imx, int *jmx);
# else
    imx, jmx)
    int *imx, *jmx;
# endif
  extern int  qkbic();
  extern void qpenac(
# ifdef ANSI
    int *i, int *j);
# else
    i, j)
    int *i, *j;
# endif
  extern void readrc(
# ifdef ANSI
    char *filename);
# else
    filename)
    char *filename;
# endif
  extern real relrdc(
# ifdef ANSI
    real dfault, int *istate);
# else
    dfault, istate)
    real dfault;
    int *istate;
# endif
  extern real relrdu(
# ifdef ANSI
    real *dfault, int *istate);
# else
    dfault, istate)
    real *dfault;
    int *istate;
# endif
  extern void skbic();
  extern void stdchc(
# ifdef ANSI
    int nsize);
# else
    nsize)
    int nsize;
# endif
  extern void textc(
# ifdef ANSI
    char *text, int lcrtn);
# else
    text, lcrtn)
    char *text;
    int lcrtn;
# endif
  extern void waitc();
  extern void writrc(
# ifdef ANSI
    char *filename);
# else
    filename)
    char *filename;
# endif
 
/* Prototypes for libclr. */
  extern void clrgbc(
# ifdef ANSI
    int ncolor, int *ired, int *igrn, int *iblu);
# else
    ncolor, ired, igrn, iblu)
    int ncolor, *ired, *igrn, *iblu;
# endif
  extern void clrgbu(
# ifdef ANSI
    int *ncolor, int *ired, int *igrn, int *iblu);
# else
    ncolor, ired, igrn, iblu)
    int *ncolor, *ired, *igrn, *iblu;
# endif
  extern int clrpkc(
# ifdef ANSI
    int ired, int igreen, int iblue);
# else
    ired, igreen, iblue)
    int ired, igreen, iblue;
# endif
  extern int clrpku(
# ifdef ANSI
    int *ired, int *igreen, int *iblue);
# else
    ired, igreen, iblue)
    int *ired, *igreen, *iblue;
# endif
  extern real clrvlc(
# ifdef ANSI
    real x1, real x2, real xhue);
# else
    x1, x2, xhue)
    real x1, x2, xhue;
# endif
  extern void cmapc(
# ifdef ANSI
    int icolor, int ihue, int ilite, int isat);
# else
    icolor, ihue, ilite, isat)
    int icolor, ihue, ilite, isat;
# endif
  extern void colrac(
# ifdef ANSI
    int icolor);
# else
    icolor)
    int icolor;
# endif
  extern void colrau(
# ifdef ANSI
    int *icolor);
# else
    icolor)
    int *icolor;
# endif
  extern void colrfc(
# ifdef ANSI
    int icolor);
# else
    icolor)
    int icolor;
# endif
  extern void colrfu(
# ifdef ANSI
    int *icolor);
# else
    icolor)
    int *icolor;
# endif
  extern void colrsc(
# ifdef ANSI
    int icolor);
# else
    icolor)
    int icolor;
# endif
  extern void colrsu(
# ifdef ANSI
    int *icolor);
# else
    icolor)
    int *icolor;
# endif
  extern void ctablc(
# ifdef ANSI
    int ncbits, int mode, int ihue, int ilit, int isat);
# else
    ncbits, mode, ihue, ilit, isat)
    int ncbits, mode, ihue, ilit, isat;
# endif
  extern void cunpkc(
# ifdef ANSI
    long int icolor, int *ired, int *igreen, int *iblue);
# else
    icolor, ired, igreen, iblue)
    long int icolor;
    int *ired, *igreen, *iblue;
# endif
  extern void cunpku(
# ifdef ANSI
    long int *icolor, int *ired, int *igreen, int *iblue);
# else
    icolor, ired, igreen, iblue)
    long int *icolor;
    int      *ired, *igreen, *iblue;
# endif
  extern int icolrc(
# ifdef ANSI
    int ncolor);
# else
    ncolor)
    int ncolor;
# endif
  extern int idthrc(
# ifdef ANSI
    int intens, int ix, int iy);
# else
    intens, ix, iy)
    int intens, ix, iy;
# endif
  extern int idthru(
# ifdef ANSI
    int *intens, int *ix, int *iy);
# else
    intens, ix, iy)
    int *intens, *ix, *iy;
# endif
  extern void ldclrc(
# ifdef ANSI
    int nbkgnd, int nfrgnd, int nmenu, int nmntxt, int ntext,
      int npctbr, int naxes, int ndfgeo, int nvface);
# else
    nbkgnd, nfrgnd, nmenu, nmntxt, ntext, npctbr, naxes, ndfgeo, nvface)
    int nbkgnd, nfrgnd, nmenu, nmntxt, ntext, npctbr, naxes, ndfgeo,
      nvface;
# endif
  extern void ldclru(
# ifdef ANSI
    int *nbkgnd, int *nfrgnd, int *nmenu, int *nmntxt, int *ntext,
      int *npctbr, int *naxes, int *ndfgeo, int *nvface);
# else
    nbkgnd, nfrgnd, nmenu, nmntxt, ntext, npctbr, naxes, ndfgeo, nvface)
    int *nbkgnd, *nfrgnd, *nmenu, *nmntxt, *ntext, *npctbr, *naxes,
      *ndfgeo, *nvface;
# endif
  extern int ncolrc(
# ifdef ANSI
    char *color);
# else
    color)
    char *color;
# endif
  extern void qcmapc(
# ifdef ANSI
    int *ncbits, int *mxcbts);
# else
    ncbits, mxcbts)
    int *ncbits, *mxcbts;
# endif
  extern void qcolrc(
# ifdef ANSI
    int *nbkgnd, int *nfrgnd, int *nmenu, int *nmntxt, int *ntext,
      int *npctbr, int *naxes, int *ndfgeo, int *nvface);
# else
    nbkgnd, nfrgnd, nmenu, nmntxt, ntext, npctbr, naxes, ndfgeo, nvface)
    int *nbkgnd, *nfrgnd, *nmenu, *nmntxt, *ntext, *npctbr, *naxes,
      *ndfgeo, *nvface;
# endif
  extern void rvsvdc();
  extern void tohlsc(
# ifdef ANSI
    int ired, int igreen, int iblue, int *ihue, int *ilite, int *isat);
# else
    ired, igreen, iblue, ihue, ilite, isat)
    int  ired, igreen, iblue;
    int *ihue, *ilite, *isat;
# endif
  extern void torgbc(
# ifdef ANSI
    int ihue, int ilite, int isat, int *ired, int *igreen, int *iblue);
# else
    ihue, ilite, isat, ired, igreen, iblue)
    int  ihue, ilite, isat;
    int *ired, *igreen, *iblue;
# endif
 
/* Prototypes for libndc. */
  extern void csmblc(
# ifdef ANSI
    int number, real width);
# else
    number, width)
    int  number;
    real width;
# endif
  extern void csmblu(
# ifdef ANSI
    int *number, real *width);
# else
    number, width)
    int  *number;
    real *width;
# endif
  extern void dashc(
# ifdef ANSI
    int icode);
# else
    icode)
    int icode;
# endif
  extern void dashu(
# ifdef ANSI
    int *icode);
# else
    icode)
    int *icode;
# endif
  extern void drwasc(
# ifdef ANSI
    real s, real t);
# else
    s, t)
    real s, t;
# endif
  extern void drwrsc(
# ifdef ANSI
    real ds, real dt);
# else
    ds, dt)
    real ds, dt;
# endif
  extern void drwrsu(
# ifdef ANSI
    real *ds, real *dt);
# else
    ds, dt)
    real *ds, *dt;
# endif
  extern void fillsc(
# ifdef ANSI
    int n, real s[], real t[]);
# else
    n, s[], t[])
    int n;
    real s[], t[];
# endif
  extern void framsc(
# ifdef ANSI
    real s1, real t1, real s2, real t2);
# else
    s1, t1, s2, t2)
    real s1, t1, s2, t2;
# endif
  extern void framsu(
# ifdef ANSI
    real *s1, real *t1, real *s2, real *t2);
# else
    s1, t1, s2, t2)
    real *s1, *t1, *s2, *t2;
# endif
  extern void helpc(
# ifdef ANSI
    int noptns, char *mnu[], char prefix);
# else
    noptns, mnu[], prefix)
    int noptns;
    char *mnu[], prefix;
# endif
  extern void htextc(
# ifdef ANSI
    char *text);
# else
    text)
    char *text;
# endif
  extern void ldhdrc(
# ifdef ANSI
    int nmenus, char *hdrs[]);
# else
    nmenus, hdrs[])
    int nmenus;
    char *hdrs[];
# endif
  extern void ldhdru(
# ifdef ANSI
    int *nmenus, char *hdrs);
# else
    nmenus, hdrs)
    int *nmenus;
    char *hdrs;
# endif
  extern void ldkhdc(
# ifdef ANSI
    int kheadr);
# else
    kheadr)
    int kheadr;
# endif
  extern void ldkhdu(
# ifdef ANSI
    int *kheadr);
# else
    kheadr)
    int *kheadr;
# endif
  extern void ldmnuc(
# ifdef ANSI
    char *titel, int noptns, char *optns[]);
# else
    titel, noptns, optns[])
    char *titel;
    int   noptns;
    char *optns[];
# endif
  extern void ldmnuu(
# ifdef ANSI
    char *titel, int *noptns, char *optns);
# else
    titel, noptns, optns)
    char *titel;
    int  *noptns;
    char *optns;
# endif
  extern int menusc(
# ifdef ANSI
    real *s, real *t);
# else
    s, t)
    real *s, *t;
# endif
  extern void mltvc(
# ifdef ANSI
    int *draw);
# else
    draw)
    int *draw;
# endif
  extern void mltvuc(
# ifdef ANSI
    int mviews, int iviews[], int *draw);
# else
    mviews, iviews[], draw)
    int mviews, iviews[], *draw;
# endif
  extern void movasc(
# ifdef ANSI
    real s, real t);
# else
    s, t)
    real s, t;
# endif
  extern void movasu(
# ifdef ANSI
    real *s, real *t);
# else
    s, t)
    real *s, *t;
# endif
  extern void movrsc(
# ifdef ANSI
    real ds, real dt);
# else
    ds, dt)
    real ds, dt;
# endif
  extern void movrsu(
# ifdef ANSI
    real *ds, real *dt);
# else
    ds, dt)
    real *ds, *dt;
# endif
  extern void pntasc(
# ifdef ANSI
    real s, real t);
# else
    s, t)
    real s, t;
# endif
  extern void pntasu(
# ifdef ANSI
    real *s, real *t);
# else
    s, t)
    real *s, *t;
# endif
  extern void pntrsc(
# ifdef ANSI
    real ds, real dt);
# else
    ds, dt)
    real ds, dt;
# endif
  extern void prcntc(
# ifdef ANSI
    real prcent);
# else
    prcent)
    real prcent;
# endif
  extern void prcntu(
# ifdef ANSI
    real *prcent);
# else
    prcent)
    real *prcent;
# endif
  extern real qaspsc();
  extern void qdashc(
# ifdef ANSI
    int *icode);
# else
    icode)
    int *icode;
# endif
  extern void qfrmsc(
# ifdef ANSI
    real *smn, real *tmn, real *smx, real *tmx);
# else
    smn, tmn, smx, tmx)
    real *smn, *tmn, *smx, *tmx;
# endif
  extern void qhdrc(
# ifdef ANSI
    int *kheadr, int *nmenus);
# else
    kheadr, nmenus)
    int *kheadr, *nmenus;
# endif
  extern void qheadc(
# ifdef ANSI
    char *headr, int nmenu);
# else
    headr, nmenu)
    char *headr;
    int   nmenu;
# endif
  extern void qlocsc(
# ifdef ANSI
    real *s, real *t, int *lflag);
# else
    s, t, lflag)
    real *s, *t;
    int  *lflag;
# endif
  extern void qpensc(
# ifdef ANSI
    real *s, real *t, int *lpen);
# else
    s, t, lpen)
    real *s, *t;
    int  *lpen;
# endif
  extern void qsclsc(
# ifdef ANSI
    real *sscal, real *tscal);
# else
    *sscal, *tscal)
    real *sscal, *tscal;
# endif
  extern real qzrosc();
  extern void symblc(
# ifdef ANSI
    char chr);
# else
    chr)
    char chr;
# endif
  extern void vtextc(
# ifdef ANSI
    char *text);
# else
    text)
    char *text;
# endif
  extern void wrpenc(
# ifdef ANSI
    real s, real t);
# else
    s, t)
    real s, t;
# endif
 
/* Prototypes for libgrd. */
  extern void drwagc(
# ifdef ANSI
    real x, real y);
# else
    x, y)
    real x, y;
# endif
  extern void drwagu(
# ifdef ANSI
    real *x, real *y);
# else
    x, y)
    real *x, *y;
# endif
  extern void framgc(
# ifdef ANSI
    real s1, real t1, real s2, real t2);
# else
    s1, t1, s2, t2)
    real s1, t1, s2, t2;
# endif
  extern void framgu(
# ifdef ANSI
    real *s1, real *t1, real *s2, real *t2);
# else
    s1, t1, s2, t2)
    real *s1, *t1, *s2, *t2;
# endif
  extern void gaxisc(
# ifdef ANSI
    int kind, real xmin, real xmax, real *gmin, real *gmax,
      real *gdelta);
# else
    kind, xmin, xmax, *gmin, *gmax, *gdelta)
    int  kind;
    real xmin, xmax, *gmin, *gmax, *gdelta;
# endif
  extern void gridc(
# ifdef ANSI
    int kind, real xmin, real ymin, real xmax, real ymax);
# else
    kind, xmin, ymin, xmax, ymax)
    int  kind;
    real xmin, ymin, xmax, ymax;
# endif
  extern void gridu(
# ifdef ANSI
    int *kind, real *xmin, real *ymin, real *xmax, real *ymax);
# else
    kind, xmin, ymin, xmax, ymax)
    int  *kind;
    real *xmin, *ymin, *xmax, *ymax;
# endif
  extern void movagc(
# ifdef ANSI
    real x, real y);
# else
    x, y)
    real x, y;
# endif
  extern void movagu(
# ifdef ANSI
    real *x, real *y);
# else
    x, y)
    real *x, *y;
# endif
  extern void qfrmgc(
# ifdef ANSI
    real *sgmn, real *tgmn, real *sgmx, real *tgmx);
# else
    sgmn, tgmn, sgmx, tgmx)
    real *sgmn, *tgmn, *sgmx, *tgmx;
# endif
  extern void xgtosc(
# ifdef ANSI
    real x, real y, real *s, real *t);
# else
    x, y, s, t)
    real x, y, *s, *t;
# endif
 
/* Prototypes for lib2d. */
  extern void circlc(
# ifdef ANSI
    real x2ctr, real y2ctr, real radius);
# else
    x2ctr, y2ctr, radius)
    real x2ctr, y2ctr, radius;
# endif
  extern void clipsc(
# ifdef ANSI
    real s0, real t0, real sf, real tf, real *s1, real *t1, real *s2,
      real *t2, int *iclip);
# else
    s0, t0, sf, tf, s1, t1, s2, t2, iclip)
    real s0, t0, sf, tf, *s1, *t1, *s2, *t2;
    int *iclip;
# endif
  extern void drwa2c(
# ifdef ANSI
    real x2, real y2);
# else
    x2, y2)
    real x2, y2;
# endif
  extern void drwa2u(
# ifdef ANSI
    real *x2, real *y2);
# else
    x2, y2)
    real *x2, *y2;
# endif
  extern void drwr2c(
# ifdef ANSI
    real dx2, real dy2);
# else
    dx2, dy2)
    real dx2, dy2;
# endif
  extern void drwr2u(
# ifdef ANSI
    real *dx2, real *dy2);
# else
    dx2, dy2)
    real *dx2, *dy2;
# endif
  extern void fill2c(
# ifdef ANSI
    int n, real x2[], real y2[]);
# else
    n, x2[], y2[])
    int  n;
    real x2[], y2[];
# endif
  extern void fram2c(
# ifdef ANSI
    real x2mn, real y2mn, real x2mx, real y2mx);
# else
    x2mn, y2mn, x2mx, y2mx)
    real x2mn, y2mn, x2mx, y2mx;
# endif
  extern void fram2u(
# ifdef ANSI
    real *x2mn, real *y2mn, real *x2mx, real *y2mx);
# else
    x2mn, y2mn, x2mx, y2mx)
    real *x2mn, *y2mn, *x2mx, *y2mx;
# endif
  extern int menu2c(
# ifdef ANSI
    real *x2, real *y2);
# else
    x2, y2)
    real *x2, *y2;
# endif
  extern void mova2c(
# ifdef ANSI
    real x2, real y2);
# else
    x2, y2)
    real x2, y2;
# endif
  extern void mova2u(
# ifdef ANSI
    real *x2, real *y2);
# else
    x2, y2)
    real *x2, *y2;
# endif
  extern void movr2c(
# ifdef ANSI
    real dx2, real dy2);
# else
    dx2, dy2)
    real dx2, dy2;
# endif
  extern void movr2u(
# ifdef ANSI
    real *dx2, real *dy2);
# else
    dx2, dy2)
    real *dx2, *dy2;
# endif
  extern void pnta2c(
# ifdef ANSI
    real x2, real y2);
# else
    x2, y2)
    real x2, y2;
# endif
  extern void pntr2c(
# ifdef ANSI
    real dx2, real dy2);
# else
    dx2, dy2)
    real dx2, dy2;
# endif
  extern real qasp2c();
  extern void qfrm2c(
# ifdef ANSI
    real *x2mn, real *y2mn, real *x2mx, real *y2mx);
# else
    x2mn, y2mn, x2mx, y2mx)
    real *x2mn, *y2mn, *x2mx, *y2mx;
# endif
  extern void qloc2c(
# ifdef ANSI
    real *x2, real *y2, int *lflag);
# else
    x2, y2, lflag)
    real *x2, *y2;
    int  *lflag;
# endif
  extern void qorg2c(
# ifdef ANSI
    real *s0, real *t0);
# else
    s0, t0)
    real *s0, *t0;
# endif
  extern void qpen2c(
# ifdef ANSI
    real *x2, real *y2);
# else
    x2, y2)
    real *x2, *y2;
# endif
  extern void qscl2c(
# ifdef ANSI
    real *x2scl, real *y2scl);
# else
    x2scl, y2scl)
    real *x2scl, *y2scl;
# endif
  extern real qzro2c();
  extern void scal2c(
# ifdef ANSI
    real x2scl, real y2scl);
# else
    x2scl, y2scl)
    real x2scl, y2scl;
# endif
  extern void slid2c(
# ifdef ANSI
    real dx2, real dy2);
# else
    dx2, dy2)
    real dx2, dy2;
# endif
  extern void x2tosc(
# ifdef ANSI
    real x2, real y2, real *s, real *t);
# else
    x2, y2, s, t)
    real x2, y2, *s, *t;
# endif
  extern void xsto2c(
# ifdef ANSI
    real s, real t, real *x2, real *y2);
# else
    s, t, x2, y2)
    real s, t, *x2, *y2;
# endif
 
/* Prototypes for lib3d. */
  extern void arro3c(
# ifdef ANSI
    real size, real pt1[3], real pt2[3], int iopt);
# else
    size, pt1[3], pt2[3], iopt)
    real size, pt1[3], pt2[3];
    int  iopt;
# endif
  extern int clip2c(
# ifdef ANSI
    real x2s, real y2s, real z2s, real w2s, real x2f, real y2f,
      real z2f, real w2f, real *x21, real *y21, real *z21, real *x22,
      real *y22, real *z22);
# else
    x2s, y2s, z2s, w2s, x2f, y2f, z2f, w2f, *x21, *y21, *z21, *x22,
      *y22, *z22)
    real x2s, y2s, z2s, w2s, x2f, y2f, z2f, w2f, *x21, *y21, *z21, *x22,
      *y22, *z22;
# endif
  extern void cnturc(
# ifdef ANSI
    real x[], real y[], real z[], int ip, int iq, real hgts[], int ir,
      PFV spurc);
# else
    x[], y[], z[], ip, iq, hgts[], ir, spurc)
    real x[], y[], z[];
    int  ip, iq;
    real hgts[];
    int  ir;
    PFV  spurc;
# endif
  extern void cnturu(
# ifdef ANSI
    real x[], real y[], real z[], int *ip, int *iq, real hgts[],
      int *ir, PFV spuru);
# else
    x[], y[], z[], ip, iq, hgts[], ir, spuru)
    real  x[], y[], z[];
    int  *ip, *iq;
    real  hgts[];
    int  *ir;
    PFV   spuru;
# endif
  extern void drwa3c(
# ifdef ANSI
    real x, real y, real z, real w);
# else
    x, y, z, w)
    real x, y, z, w;
# endif
  extern void drwa3u(
# ifdef ANSI
    real *x, real *y, real *z, real *w);
# else
    x, y, z, w)
    real *x, *y, *z, *w;
# endif
  extern void drwlnc(
# ifdef ANSI
    int mxpixl, int khrzon[], int lhrzon[], real x21, real y21,
      real x22, real y22);
# else
    mxpixl, khrzon[], lhrzon[], x21, y21, x22, y22)
    int  mxpixl, khrzon[], lhrzon[];
    real x21, y21, x22, y22;
# endif
  extern void drwlnu(
# ifdef ANSI
    int *mxpixl, int khrzon[], int lhrzon[], real *x21, real *y21,
      real *x22, real *y22);
# else
    mxpixl, khrzon[], lhrzon[], x21, y21, x22, y22)
    int  *mxpixl, khrzon[], lhrzon[];
    real *x21, *y21, *x22, *y22;
# endif
  extern void drwr3c(
# ifdef ANSI
    real dx, real dy, real dz, real w);
# else
    dx, dy, dz, w)
    real dx, dy, dz, w;
# endif
  extern void drwr3u(
# ifdef ANSI
    real *dx, real *dy, real *dz, real *w);
# else
    dx, dy, dz, w)
    real *dx, *dy, *dz, *w;
# endif
  extern void dvuec(
# ifdef ANSI
    real out[3], real vert[3]);
# else
    out[3], vert[3])
    real out[3], vert[3];
# endif
  extern void fill3c(
# ifdef ANSI
    real xpnt[], real ypnt[], real zpnt[], real wpnt[], int n);
# else
    xpnt[], ypnt[], zpnt[], wpnt[], n)
    real xpnt[], ypnt[], zpnt[], wpnt[];
    int  n;
# endif
  extern void fram3c(
# ifdef ANSI
    real xmin, real ymin, real zmin, real xmax, real ymax, real zmax);
# else
    xmin, ymin, zmin, xmax, ymax, zmax)
    real xmin, ymin, zmin, xmax, ymax, zmax;
# endif
  extern void fram3u(
# ifdef ANSI
    real *xmin, real *ymin, real *zmin, real *xmax, real *ymax,
      real *zmax);
# else
    xmin, ymin, zmin, xmax, ymax, zmax)
    real *xmin, *ymin, *zmin, *xmax, *ymax, *zmax;
# endif
  extern void ldx32c(
# ifdef ANSI
    real x32[4][4]);
# else
    x32[4][4])
    real x32[4][4];
# endif
  extern void ldx32u(
# ifdef ANSI
    real x32[16]);
# else
    x32[16])
    real x32[16];
# endif
  extern int menu3c(
# ifdef ANSI
    real *x, real *y, real *z, real *w);
# else
    x, y, z, w)
    real *x, *y, *z, *w;
# endif
  extern int mnupkc();
  extern int mnuptc(
# ifdef ANSI
    real *x, real *y, real *z);
# else
    x, y, z)
    real *x, *y, *z;
# endif
  extern void mova3c(
# ifdef ANSI
    real x, real y, real z, real w);
# else
    x, y, z, w)
    real x, y, z, w;
# endif
  extern void mova3u(
# ifdef ANSI
    real *x, real *y, real *z, real *w);
# else
    x, y, z, w)
    real *x, *y, *z, *w;
# endif
  extern void movr3c(
# ifdef ANSI
    real dx, real dy, real dz, real w);
# else
    dx, dy, dz, w)
    real dx, dy, dz, w;
# endif
  extern void perspc(
# ifdef ANSI
    real eyedst);
# else
    eyedst)
    real eyedst;
# endif
  extern void pnta3c(
# ifdef ANSI
    real x, real y, real z, real w);
# else
    x, y, z, w)
    real x, y, z, w;
# endif
  extern void pntr3c(
# ifdef ANSI
    real dx, real dy, real dz, real w);
# else
    dx, dy, dz, w)
    real dx, dy, dz, w;
# endif
  extern void qfrntc(
# ifdef ANSI
    real theta, int nrows, int nkols, int *n1axis, int *n1strt,
      int *n1stop, int *n1inc, int *n2strt, int *n2stop, int *n2inc);
# else
    theta, nrows, nkols, n1axis, n1strt, n1stop, n1inc, n2strt, n2stop,
      n2inc)
    real theta;
    int  nrows, nkols, *n1axis, *n1strt, *n1stop, *n1inc, *n2strt,
      *n2stop, *n2inc;
# endif
  extern void qfrntu(
# ifdef ANSI
    real *theta, int *nrows, int *nkols, int *n1axis, int *n1strt,
      int *n1stop, int *n1inc, int *n2strt, int *n2stop, int *n2inc);
# else
    theta, nrows, nkols, n1axis, n1strt, n1stop, n1inc, n2strt, n2stop,
      n2inc)
    real *theta;
    int  *nrows, *nkols, *n1axis, *n1strt, *n1stop, *n1inc, *n2strt,
      *n2stop, *n2inc;
# endif
  extern void qloc3c(
# ifdef ANSI
    real *x, real *y, real *z, real *w, int *lflag);
# else
    x, y, z, w, lflag)
    real *x, *y, *z, *w;
    int  *lflag;
# endif
  extern void qorg3c(
# ifdef ANSI
    real *x2, real *y2, real *z2);
# else
    x2, y2, z2)
    real *x2, *y2, *z2;
# endif
  extern void qpen3c(
# ifdef ANSI
    real *x, real *y, real *z, real *w);
# else
    x, y, z, w)
    real *x, *y, *z, *w;
# endif
  extern real qscl3c();
  extern void qx32c(
# ifdef ANSI
    real x32[4][4]);
# else
    x32[4][4])
    real x32[4][4];
# endif
  extern void qx32u(
# ifdef ANSI
    real x32[16]);
# else
    x32[16])
    real x32[16];
# endif
  extern void rgtvuc(
# ifdef ANSI
    real vnorm[3]);
# else
    vnorm[3])
    real vnorm[3];
# endif
  extern void scal3c(
# ifdef ANSI
    real factor);
# else
    factor)
    real factor;
# endif
  extern void scal3u(
# ifdef ANSI
    real *factor);
# else
    factor)
    real *factor;
# endif
  extern void slid3c(
# ifdef ANSI
    real dx, real dy, real dz, real w);
# else
    dx, dy, dz, w)
    real dx, dy, dz, w;
# endif
  extern void slidec(
# ifdef ANSI
    int naxis, real delta);
# else
    naxis, delta)
    int  naxis;
    real delta;
# endif
  extern void slideu(
# ifdef ANSI
    int *naxis, real *delta);
# else
    naxis, delta)
    int  *naxis;
    real *delta;
# endif
  extern void spur2c(
# ifdef ANSI
    real x[], real y[], real z[], int ip, int iq, double height,
      int lopen, int i0, int j0, int iinc0, int jinc0);
# else
    x[], y[], z[], ip, iq, height, lopen, i0, j0, iinc0, jinc0)
    real   x[], y[], z[];
    int    ip, iq;
    double height;
    int    lopen, i0, j0, iinc0, jinc0;
# endif
  extern void spur2u(
# ifdef ANSI
    real x[], real y[], real z[], int ip, int iq, double height,
      int lopen, int i0, int j0, int iinc0, int jinc0);
# else
    x[], y[], z[], ip, iq, height, lopen, i0, j0, iinc0, jinc0)
    real   x[], y[], z[];
    int    ip, iq;
    double height;
    int    lopen, i0, j0, iinc0, jinc0;
# endif
  extern void spur3c(
# ifdef ANSI
    real x[], real y[], real z[], int ip, int iq, double height,
      int lopen, int i0, int j0, int iinc0, int jinc0);
# else
    x[], y[], z[], ip, iq, height, lopen, i0, j0, iinc0, jinc0)
    real   x[], y[], z[];
    int    ip, iq;
    double height;
    int    lopen, i0, j0, iinc0, jinc0;
# endif
  extern void spur3u(
# ifdef ANSI
    real x[], real y[], real z[], int ip, int iq, double height,
      int lopen, int i0, int j0, int iinc0, int jinc0);
# else
    x[], y[], z[], ip, iq, height, lopen, i0, j0, iinc0, jinc0)
    real   x[], y[], z[];
    int    ip, iq;
    double height;
    int    lopen, i0, j0, iinc0, jinc0;
# endif
  extern void turn3c(
# ifdef ANSI
    int naxis, real angle);
# else
    naxis, angle)
    int  naxis;
    real angle;
# endif
  extern void turnc(
# ifdef ANSI
    int naxis, real angle);
# else
    naxis, angle)
    int  naxis;
    real angle;
# endif
  extern void vclosc();
  extern void vdelc(
# ifdef ANSI
    int nview);
# else
    nview)
    int nview;
# endif
  extern void vdelu(
# ifdef ANSI
    int *nview);
# else
    nview)
    int *nview;
# endif
  extern void vdirc();
  extern void vopenc();
  extern void vreadc(
# ifdef ANSI
    int nview);
# else
    nview)
    int nview;
# endif
  extern void vreadu(
# ifdef ANSI
    int *nview);
# else
    nview)
    int *nview;
# endif
  extern void vstorc(
# ifdef ANSI
    int nview, char viewid[]);
# else
    nview, viewid[])
    int  nview;
    char viewid[];
# endif
  extern void vstoru(
# ifdef ANSI
    int *nview, char viewid[]);
# else
    nview, viewid[])
    int *nview;
    char viewid[];
# endif
  extern void x2to3c(
# ifdef ANSI
    real x2, real y2, real z2, real w2, real *x3, real *y3, real *z3,
      real *w3);
# else
    x2, y2, z2, w2, x3, y3, z3, w3)
    real x2, y2, z2, w2, *x3, *y3, *z3, *w3;
# endif
  extern void x2to3u(
# ifdef ANSI
    real *x2, real *y2, real *z2, real *w2, real *x3, real *y3,
      real *z3, real *w3);
# else
    x2, y2, z2, w2, x3, y3, z3, w3)
    real *x2, *y2, *z2, *w2, *x3, *y3, *z3, *w3;
# endif
  extern void x3ndcc(
# ifdef ANSI
    real scl32, real x20, real y20, real *theta, real *phi,
      real x32[3][4]);
# else
    scl32, x20, y20, theta, phi, x32)
    real scl32, x20, y20, *theta, *phi, x32[3][4];
# endif
  extern void x3ndcu(
# ifdef ANSI
    real *scl32, real *x20, real *y20, real *theta, real *phi,
      real x32f[12]);
# else
    scl32, x20, y20, theta, phi, x32f)
    real *scl32, *x20, *y20, *theta, *phi, x32f[12];
# endif
  extern void x3to2c(
# ifdef ANSI
    real x3, real y3, real z3, real w3, real *x2, real *y2, real *z2,
      real *w2);
# else
    x3, y3, z3, w3, x2, y2, z2, w2)
    real x3, y3, z3, w3, *x2, *y2, *z2, *w2;
# endif
  extern void x3to2u(
# ifdef ANSI
    real *x3, real *y3, real *z3, real *w3, real *x2, real *y2,
      real *z2, real *w2);
# else
    x3, y3, z3, w3, x2, y2, z2, w2)
    real *x3, *y3, *z3, *w3, *x2, *y2, *z2, *w2;
# endif
  extern void xformc(
# ifdef ANSI
    int mxsize, int nrows, int nkols, int n1axis, int n1, int n2strt,
      int n2stop, int n2inc, real z[], real zmax, real x32[3][4],
      real disply[]);
# else
    mxsize, nrows, nkols, n1axis, n1, n2strt, n2stop, n2inc, z[], zmax,
      x32[3][4], disply[])
    int mxsize, nrows, nkols, n1axis, n1, n2strt, n2stop, n2inc;
    real z[], zmax, x32[3][4], disply[];
# endif
  extern void xformu(
# ifdef ANSI
    int *mxsize, int *nrows, int *nkols, int *n1axis, int *n1,
      int *n2strt, int *n2stop, int *n2inc, real z[], real *zmax,
      real x32f[12], real disply[]);
# else
    mxsize, nrows, nkols, n1axis, n1, n2strt, n2stop, n2inc, z[], zmax,
      x32f[12], disply[])
    int *mxsize, *nrows, *nkols, *n1axis, *n1, *n2strt, *n2stop, *n2inc;
    real z[], *zmax, x32f[12], disply[];
# endif
  extern void zclipc(
# ifdef ANSI
    real z2mn, real z2mx);
# else
    z2mn, z2mx)
    real z2mn, z2mx;
# endif
  extern void zclipu(
# ifdef ANSI
    real *z2mn, real *z2mx);
# else
    z2mn, z2mx)
    real *z2mn, *z2mx;
# endif
# define LIBCAD_INCLUDED
#endif
