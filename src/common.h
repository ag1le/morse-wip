
/* Common Block Declarations */

struct BLKTRN {
    integer ltrmap[400], iblank[400];
} blktrn;


struct Alpha {
    char ialph[70];
} alpha;



struct BLK1 {
    real tau;
} blk1;


struct BLK6 {
    real dmean;
	real xdur;
	real esep[6];
	real edev[6];
} blk6;


struct BLK2 {
    real wc, wchirp, asigma, bsigma, phisgm, rsigm, tchirp, gamma;
} blk2;


struct BLKLAM {
    integer ielmst[400], ilami[16], ilamx[6];
} blklam;


struct BLKELM {
    real elemtr[6][16]	/* was [16][6] */;
} blkelm;


struct BLKSPD {
    real rtrans[2][5]	/* was [5][2] */;
    integer mempr[6][6]	/* was [6][6] */;
} blkspd;


struct BLKRAT {
    integer memdel[6][6]	/* was [6][6] */;
} blkrat;


struct BLKMEM {
    integer memfcn[6][400]	/* was [400][6] */;
} blkmem;


struct BLKS {
    integer isx[6];
} blks;

struct BLKSV {
    real ykkip[25], pkkip[25], ykksv[750], pkksv[750];
} blksv;


struct BLKEND {
    integer iend;
} blkend;


struct BLKTXT {
    integer itext[200];
} blktxt;



extern int path_(integer ip, integer *lambda, real *dur, integer *ilrate, integer lamsav[][25], real dursav[][25], integer ilrsav[][25]);
extern int likhd_(real *z, real *rn, integer ip, integer *lambda, real *dur, integer *ilrate, real p[][25], real lkhd[][25]);
extern int savep_(real p[][25], integer *pathsv, integer *isave, integer *imax, integer lamsav[][25], real dursav[][25], integer ilrsav[][25], integer *lambda, real *dur, integer *ilrate, integer *sort);
extern int probp_(real p[][25], real pin[][25], integer *isave, real lkhd[][25]);
extern int sprob_(real p[][25], integer *isave, integer ilrsav[][25], real *pelm, integer *khat, real *spdhat, real *px);
extern int trelis_(integer *, integer *, integer *, integer *);
extern int trprob_(integer , integer *, real *, integer *, real [][25]);


