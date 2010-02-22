/* libcad-01 Jan 00:22 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
*
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "libcad.h"

/* iobfrc definitions and initialization. */
FILE *streams[MXLUNS];                        /* Stream i/o pointers. */
char  EOR;                 /* Character used to detect end of record. */
char  inbufr[MXINBF+1];                              /* Input Buffer. */
int   dfltline  = FALSE;  /* Flag set TRUE to signal slash (/) input. */
int   line0;      /* Number of split line in circular buffer textq(). */
char *text_buff = NULL;   /* Circular buffer for output text strings. */
char **textq    = NULL;  /* Array of pointers to output text strings. */
int  *text_color= NULL;   /* Array of colors for output text strings. */

/* iodvc definitions. */
int   crlf;             /* Flag set TRUE for newline on next textc(). */
int   lunin;                         /* Stream number for input data. */
char *inloc;   /* Pointer to the next input character to be accessed. */
int   inmax;           /* Total number of characters read by bfinc(). */
int   intact;             /* Flag set TRUE for interactive execution. */
int   lunio;                        /* Stream number for output data. */
int   kbint;                /* Flag set TRUE by a keyboard interrupt. */
int   kbwtch;          /* Flag set TRUE when watching for interrupts. */
int   luneco;            /* Stream number for echo of input commands. */
int   lunerr;                    /* Stream number for error messages. */
int   lunpr;                     /* Stream number for printed output. */
int   lunrd;                     /* Stream number for input commands. */
int   lunsmb;            /* Stream number for stroked character file. */
int   lunwr;             /* Stream number for output of command file. */

/* devic definitions and initialization. */
enum  Dsptyp dspdvc;                   /* The current display device. */
char *DspTyp[MXDSPLAY] = {"none", "alpha", "graphic"};
enum  Chctyp chdvc;               /* The current choice input device. */
char *ChcTyp[MXCHOICE] = {"none", "alpha", "locator"};
enum  Loctyp lcdvc;              /* The current locator input device. */
char *LocTyp[MXLOCATR] = {"none", "alpha", "mouse", "tablet"};

/* xglblc definitions. */
#ifndef __WATCOMC__
  int           X_Initialized = FALSE;   /* Has xinitc() been called? */
  Display      *dsp;
  int           screen;
  int           depth;
  Window        rootwin;
  Window        win;
  unsigned long event_mask;
  XEvent        report;
  Cursor        arrow_cursor;
  Cursor        watch_cursor;
  Pixmap        pixmap;
  Pixmap        txtmap;
  Colormap      cmap;
  int           colors [MXCOLOR];
  XColor        xcolors[MXCOLOR];
  GC            text_gc;                 /* Graphic context for text. */
  GC            gtext_gc;        /* Graphic context for graphic text. */
  GC            line_gc;                /* Graphic context for lines. */
  GC            fill_gc;         /* Graphic context for filled areas. */
  GC            bkgnd_gc;      /* Graphic context for screen erasing. */
  int           font_height;                          /* Font height. */
  XFontStruct  *font_info;        /* Info about the font we're using. */
  int           xpix, ypix;                 /* Window size in pixels. */
  int           xwmin, ywmin;       /* Minimum Window size in pixels. */
  int           xpos, ypos;               /* Current window position. */
  char          FontName[32];                         /* Font to use. */
  int           txt_drwn;   /* Any text drawn on the graphics window? */
  int           pix_drwn; /* Any NEW pixels drawn on graphics window? */
  char         *crsr = "_";                       /* The text cursor. */
  int           crsron;                /* Is the text cursor in use?. */
  int           crsrx, crsry;  /* Text cursor's position (if in use). */
  int           ctrl_indx; /* Indicates if Control key is being held. */
  int           rev_video;        /* Is the video currently reversed? */
  char         *TitleBar = "JJU Research";
#endif

/* colorc definitions and initialization. */
int   kbkgnd = 0;             /* Color number for display background. */
int   kfrgnd = 1;             /* Color number for display foreground. */
int   kmenu  = 0;             /* Color number for menu box outlines.  */
int   kmntxt = 1;             /* Color number for text in menu boxes. */
int   ktext  = 1;                           /* Color number for text. */
int   kpctbr = 3;          /* Color number for percent completed bar. */
int   kaxes  = 8;        /* Color number for axes, scale factor, etc. */
int   kdfgeo = 1;         /* Color number (default) for new geometry. */
int   kvface = 6;              /* Color number for virtual cut faces. */

/* screnc definitions. */
int   lsmode;                  /* Flag set TRUE when in graphic mode. */
int   lspen;            /* Flag set TRUE when graphic pen is visible. */
int   l2pen;                 /* Flag set TRUE when 2D pen is updated. */
int   l3pen;                 /* Flag set TRUE when 3D pen is updated. */
int   scroll_en;          /* Flag set TRUE when scrolling is enabled. */
int   atext_en;          /* Flag set TRUE when alpha text is enabled. */
int   imin;            /* Row number of top printable line of screen. */
int   ipen;        /* Row    number of last character in textq[    ]. */
int   jpen;        /* Column number of last character in textq[ipen]. */
int   imax;              /* Total available rows on the alpha screen. */
int   jmax;           /* Total available columns on the alpha screen. */
char *global[MXGLOBAL] ={"?", "CURRENT", "HELP", "MULTIVU", "REFRESH "};
int   menumx;       /* Total number of menu items listed by drmnuc(). */
char *menu[MXMENU];     /* Strings for menu items listed by drmnuc(). */
int   nhdrs;      /* Total number of menu headers listed by drmnuc(). */
char *header[MXHEADER];/* Strings of menu headers listed by drmnuc(). */
int   khdr;                     /* Number of the current menu header. */
int   icolra;         /* Color number for current alpha text setting. */
int   icolrb;         /* Color number for current background setting. */
int   icolrf;        /* Color number for current graphic pen setting. */
int   icolrs;        /* Color number for current screen text setting. */
int   iline;                      /* Line style code for graphic pen. */
int   idash;                    /* Dash pattern code for graphic pen. */
int   ndash;        /* Number of strokes in the current dash pattern. */
int   ldash;        /* Stroke number within the current dash pattern. */
real  dshtbl[MXDASH];/* Table defining software dash pattern lengths. */
real  dshseg;       /* Percentage of stroke left from last dash line. */
real  xtrasz;  /* Fractional increase of menu box height over tsymbl. */
real  spen;    /* Actual horizontal screen coordinate of graphic pen. */
real  tpen;      /* Actual vertical screen coordinate of graphic pen. */
real  smin; /* Minimum horizontal value of the current screen window. */
real  tmin;   /* Minimum vertical value of the current screen window. */
real  smax; /* Maximum horizontal value of the current screen window. */
real  tmax;   /* Maximum vertical value of the current screen window. */
real  aspect;                  /* Aspect ratio of the graphic screen. */
real  sscale;      /* Number of horizontal pixels per graphic screen. */
real  tscale;        /* Number of vertical pixels per graphic screen. */
real  ssymbl; /* Screen units for one graphic screen character width. */
real  tsymbl;/* Screen units for one graphic screen character height. */
real  stzero;    /* Minimum screen unit to be smaller than one pixel. */
real  zrogeo = 1.0e-6;        /* Tolerence value for geometric tests. */

/* graphc definitions. */
int   kgrid;            /* Flag indicating linear/log axes for graph. */
real  sgmin;            /* Screen coordinates for left edge of graph. */
real  tgmin;          /* Screen coordinates for bottom edge of graph. */
real  sgmax;           /* Screen coordinates for right edge of graph. */
real  tgmax;             /* Screen coordinates for top edge of graph. */
real  pscale;  /* Horizontal scale factor from graph to screen units. */
real  qscale;    /* Vertical scale factor from graph to screen units. */
real  p0;           /* Horizontal offset from graph to screen origin. */
real  q0;             /* Vertical offset from graph to screen origin. */

/* pagec definitions. */
real  x2pen;   /* Horizontal page coordinate of current pen location. */
real  y2pen;     /* Vertical page coordinate of current pen location. */
real  x2min;                     /* Minimum horizontal page boundary. */
real  y2min;                       /* Minimum vertical page boundary. */
real  z2min;                        /* Minimum outward page boundary. */
real  x2max;                     /* Maximum horizontal page boundary. */
real  y2max;                       /* Maximum vertical page boundary. */
real  z2max;                        /* Maximum outward page boundary. */
real  x2scal;              /* Horizontal page to screen scale factor. */
real  y2scal;                /* Vertical page to screen scale factor. */
real  x20;                       /* Horizontal page to screen offset. */
real  y20;                         /* Vertical page to screen offset. */
real  eyeinv;/* Reciprocal of 3D viewer's eye distance from the page. */

/* diridc.h parameter definitions. */
char *filedir = NULL;         /* Directory string for JJU data files. */
char *helpdir = NULL;         /* Directory string for JJU help files. */
char *homedir = NULL;         /* Directory string for JJU home files. */

/* imagec definitions. */
real  x3pen;          /* x-coordinate of the current 3D pen location. */
real  y3pen;          /* y-coordinate of the current 3D pen location. */
real  z3pen;          /* z-coordinate of the current 3D pen location. */
real  w3pen;/* Homogeneous coordinate of the current 3D pen location. */
real  x3to2[4][4];    /* 3D to page coordinate transformation matrix. */
real  x2to3[4][4];    /* Page to 3D coordinate transformation matrix. */

/* viewc parameter definitions and initialization. */
real  szaxes = 1.0;         /* Length of global 3-D axes to be drawn. */
real  expand = 1.0; /* Percent actual size for faces after expansion. */
real  crease = 0.43633;      /* Crease angle for 3-D edge visibility. */
real  xresol = 750.01;  /* Hidden/shaded image horizontal resolution. */
real  yresol = 750.01;  /* Hidden/shaded image vertical   resolution. */
real  ambent = 0.100;  /* Coefficient of ambient  lighting intensity. */
real  difuse = 0.250;  /* Coefficient of diffuse  lighting intensity. */
real  spculr = 0.650;  /* Coefficient of specular lighting intensity. */
real  shiny  = 1.0;    /* Exponent   for specular lighting intensity. */
real  rlight[3]={INDEF,0.0,0.0};/*Global position of the light source.*/
int   iexprt = 1; /* Level of expertise expected of interactive user. */
int   ivrbos = 1; /* Level of detail desired  for interactive output. */
int   nviews = 0;           /* Number of views in a multi-view scene. */
int   jviews[5]={-7,-5,-1,-4,-7};/* View numbers for multiview scene. */
int   khilit = 16777215;/*Packed RGB highlite values for shaded image.*/
int   lsaved = TRUE;        /* Flag set TRUE when geometry is stored. */
int   ldraw  = TRUE;  /* Flag set TRUE for redraw after each erasure. */
int   lmenu  = TRUE;        /* Flag set TRUE for displaying the menu. */
int   label  = FALSE;    /* Flag set TRUE for displaying face labels. */
int   lpoor  = TRUE;         /* Flag set TRUE for poormans algorithm. */
int   lhide  = FALSE;    /* Flag set TRUE for hidden surface removal. */
int   l1pass = FALSE; /* Flag set TRUE for single pass hidden images. */
int   lshade = FALSE;             /* Flag set TRUE for shaded images. */
int   lrvsvd = FALSE;     /* Flag set true for reversed video images. */

/* viewsc definitions. */
char  filvue[MXFLCH+1];       /* Filename of direct access view file. */
char  idvue[MXVIEW+1][MXFLCH+1]; /* Array of titles for stored views. */
real  x32vue[MXVIEW+1][3][3];/* Array of transforms for stored views. */
int   lvue[MXVIEW+1];    /* Array of flags set TRUE for stored views. */
