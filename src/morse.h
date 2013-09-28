

extern int rcvr_(real *, real *);
extern int noise_(real *, real *, real *);
extern  int initl_(void);
extern  int stats_(real *, real *, real *, integer *, real *, real *, real *, real *, integer *);
extern  int bpfdet_(real *, real *);
extern  int simsgi_(real *, real *);
extern int proces_(real *z, real *rn, integer *xhat, real *px, integer *elmhat, real *spdhat, integer *imax, real *pmax);
extern  int inputl_(void);
extern int transl_(int *ltr);
extern int trelis_(integer *isave, integer *pathsv, integer *lambda, integer *imax, integer *ipmax);


extern int probp_(real *, real *, integer *, real *);
extern int  sprob_(real *, integer *, integer *, real *, integer *, real *, real *);
extern int trprob_(integer *, integer *, real *, integer *, real *);
extern int savep_(real *, integer *, integer *, integer *, integer *, real *, integer *, integer *, real *, integer *, integer *, real *);
extern int likhd_(real *, real *, integer *, integer *, real *, integer *, real *, real *);
extern int path_(integer *, integer *, real *, integer *, integer *, real *, integer *);
extern doublereal spdtr_(integer *, integer *, integer *, integer *);

#define FSAMPLE 4000.0			// Sampling Frequency  FLDIGI=8000   MORSE.M =4000
#define DECIMATE  20			// Decimation     FLDIGI=40    MORSE.M=20 
#define SAMPLEDURATION  (1000. * DECIMATE) / FSAMPLE	// 1000*DECIMATE / FSAMPLE SHOULD BE  5 msec
#define NDELAY  200				// 200 SAMPLES * 5 msec = 1000 msec decoding delay 
