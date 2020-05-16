/****************************************************************/
/* code copyright 1995-1996 Andrew Johnson - ALL RIGHTS RESERVED*/
/*                          ajohnson@eecs.uic.edu               */
/*                                                              */
/*                      Electronic Visualization Lab (M/C 154)  */
/*                      University of Illinois at Chicago       */
/*                      851 South Morgan St. Room 1120 SEO      */
/*                      Chicago, IL 60607-7053                  */
/*                                                              */
/*                      (312) 996-3002     (312) 413-7585 FAX   */
/***********************************************************************/
/* header file v 1.3                                                   */
/***********************************************************************/

#define RECONNECT_TIME		15
#define IM_NOT_DEAD_YET_TIME	60
#define IM_NOT_DEAD_SEND_TIME	19
#define MAXLINE			256
#define COMPUTER_MONSTER	-1
#define MONSTER_UPDATE_RATE	5
#define DEFAULT_PORT 		6000
#define MAXCLIENTS	    	10

#define MESG_BUILDING		"bld"
#define MESG_UPDATE		"upd"
#define MESG_REQUEST		"req"
#define MESG_NOTDEADYET		"Iliv"
#define MESG_REAQUIRE		"yo"
#define MESG_ACKNOWLEDGE	"ack"
#define MESG_NEW_TANK		"newTank"
#define MESG_UPDATE_TANK	"updateTank"
#define MESG_CLIENT_CLIENT_UPDATE "client"

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <pwd.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>

#ifdef SGIVERSION
#include <bstring.h>
#endif

#ifdef SOLARIS
/* from Johan Hagman <Johan.Hagman@mailbox.swipnet.se> */
# include <sys/stat.h>
# include <sys/file.h>

/* BSD compatibility */
# define bzero(dst,len) memset(dst, 0, len)
#endif

#ifdef SUNAUDIO
/* Audio support */
# include <multimedia/libaudio.h>
# include <multimedia/audio_device.h>
#endif

#ifdef HPVERSION
/* to get non-blocking I/O under HP-UX */
/* from Neil Harkin <T.N.Harkin@csc.liv.ac.uk> */
#define FNDELAY O_NDELAY
#endif



#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include "tk.h"


#include <time.h>
#include <sys/time.h>


/* audio routines */
/*****************/

#ifdef SGIVERSION

#include <audio.h>
#include <audiofile.h>

#endif

/* added for the OpenGL version */
#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

#define ENGLISH 0
#define JAPANESE 1

#define MAXTARGETS	    3

/************************************/
/* to try and speed up computations */
/************************************/

#ifdef SGIVERSION

#define fabs fabsf
#define sqrt fsqrt
#define sin fsin
#define cos fcos
#define atan fatan
#define atan2 atan2f

#else

#define amalloc(x,y)	malloc(x)
#define afree(x,y)	free(x)
#define acalloc(n,x,y)	calloc(n,x)

#endif


#define MONSTERFOGSTART		2.5
#define MONSTERFOGEND		6

#define ARMYFOGSTART		4
#define ARMYFOGEND		12

#define OVERVIEWFOGSTART	6
#define OVERVIEWFOGEND		12



/**********************/
/* monster ID numbers */
/**********************/

#define GOOGELON	    0
#define VAPOUR		    1
#define	TECHS		    2
#define FLUTTER		    3

/**********************/
/* misc stuff         */
/**********************/

#ifndef PI
	#define PI	    3.14159265
#endif

#define TWOPI		    6.2831853

#ifdef MESAVERSION

    #define	CYLINDERSIDES	    6
    #define	MORECYLINDERSIDES   12

#else

    #define	CYLINDERSIDES	    12
    #define	MORECYLINDERSIDES   20

#endif

#define CYLINDER_EPSILON    0.0001
#define NEARZERO	    0.0001
#define BIGNUM		    99999

#define ARMCOUNT	    8
#define NULLROAD	    10

#define MAXSTRING	    256

/**********************/
/* game stuff         */
/**********************/

#ifdef MESAVERSION

    #define MAXTRIBUTES	    25

#else

    #define MAXTRIBUTES	    45

#endif

#define ARRIVALRATE	    62
#define STARTACCURACY	    200
#define STARTFIRINGDELAY    43

#define GRAVITY		    0.01
#define BEAMKILL	    0.31

#define BLASTR		    0.5
#define TREEBLASTR	    0.25
#define TREEBLASTHEIGHTR    1
#define BLASTRX2	    1
#define BLASTRX04	    0.2
#define BLASTRX05	    0.25
#define BLASTRX06	    0.3
#define BLASTRX07	    0.35
#define BLASTRX075	    0.375

#define TANKV		    0.03
#define MAXLIFE		    100
#define BLASTPOINTS	    2

/**********************/
/* stereo stuff       */
/**********************/

#define YMAXSTEREO	    491
#define YOFFSET		    532

/**********************/
/* battlefield stuff  */
/**********************/

#ifdef MESAVERSION

    #define PLANESIZE	    6

#else

    #define PLANESIZE	    8

#endif	    

				    /* height of the battlefield */
#define PLANEY		    -1
				    /* PLANEY + 0.003 */
#define SHADOWS		    -0.997
				    /* PLANEY + 0.001 */
#define ROADS		    -0.999

#define MAXROADSONPLANE	    1000
#define ROADLINETHICKNESS   0.04
#define ROADLINELENGTH	    0.13   

/**********************/
/* views              */
/**********************/

#define OMNISCIENTVIEW	    0
#define MONSTERVIEW	    1
#define ARMYVIEW	    2
#define MAPVIEW		    4

#define NOTANKONPLANE	    -9999

/**********************/
/* modes              */
/**********************/

#define DEMOMODE	    0
#define PLAYMODE	    1

/**********************/
/* sounds             */
/**********************/

#define TANKFIRE	    0
#define HELOROCKET	    1
#define TANKMASER	    2
#define EXPLOSION	    3
#define MONSTERBEAM	    4
#define SLAG		    5
#define CRASH		    6
#define TECHSHOOT	    7
#define MUSIC		    8	

/* #define MAXMUSIC 36 */
#define MAXMUSIC 5
#define MAXDEADMUSIC 5

#define MAXSOUNDS 25

/**********************/
/*limits              */
/**********************/
	    
#define MAXTREESONPLANE	    800
#define MAXFIRESONPLANE	    150
#define MAXTANKSONPLANE	    200

#define ARENASIZE	    100000

#define MAXPATH		    400
#define MAXBEAMS	     50

/**********************/
/* conversions        */
/**********************/

#define BIG_DEG_TO_RAD	    0.0017453292
			    /* (2 x pi) / 3600 */
#define RAD_TO_BIG_DEG	    572.9577951
			    /* 360 / (2 x pi) */
#define RAD_TO_SMALL_DEG    57.29577951
			    /* 3600 / (2 x pi) */
#define DEG_TO_RAD	    0.0174532925
			    /* Pi / 180 */

/**********************/
/* vehicles           */
/**********************/

#define TANK	    0
#define MASERTANK   1
#define HELO	    2
#define MECHAG	    3
#define CHH	    4
#define HERO	    5
#define AIRPLANE    6
#define LAUNCHER    7
#define FIGHTER     8

#define PARTIALM  100
#define PARTIALH  101
#define PARTIALC  102

#define BUILDING    99
#define MONSTER     75

/**********************/
/* projectiles        */
/**********************/

#define PROJTANK    0
#define PROJROCKET  1
#define PROJTECHS   2
#define PROJFIRE    3
#define PROJHERO    4
#define PROJSCAR    5
#define PROJWATER   6

#define  computeAngle(x, y, z, w) (atan2( (z - w) ,  (x - y)) + PI)

#define  randy(x) (((rand() % 2001) - 1000) * x * 0.001)


struct projectile
	{
	struct projectile * next;   /* pointer to next projectile */
	struct monsterInfo * mine;  /* pointer to ownder of projectile */
	float x, y, z;		    /* location of projectile */
	float xv, yv, zv;	    /* velocity of projectile */
	char count;		    /* time after launch before arming */
	char type;		    /* type of projectile */
	};

struct boom
	{
	struct boom * next;	    /* pointer to next explosion */
	struct monsterInfo * mine;  /* pointer to ownder of boom */
	float x, y, z;		    /* location of explosion */
	int count;		    /* explosion timer */
	};

struct tree
	{
	struct tree * next;	    /* pointer to next structure */
	float x, y, z;		    /* location of structure */
	float rad,  theta;
	float height;
	int deathCount;
	int death2;
	int number;
	char type; 
	char treeshape; 
	char intact;		    /* is structure intact? */
	};

struct tank
	{
	struct tank * next;
	struct monsterInfo* goforit;
	float x, y, z;		    /* location of vehicle */
	float xv, zv;		    /* velocity of vehicle */
	float range;		    /* distance from vehicle to monster */
	float minrange;		    /* minimum range vehicle can fire */
	float finalR;		    /* final range vehicle is attempting */
	float rad, theta;
	float speed;		    /* speed of vehicle */
	float rand1, rand2, rand3;
	int count; 
	int maserCount;
	int damage;		    /* amount of damage vehicle can take */
	int walking;
	int number;
	char type;		    /* type of vehicle */
	char subtype;		    /* sub type (for hero) */
	};

struct road
	{
	float x, y;		    /* location of road */
	char type;		    /* type: 0 vert, 1 horz, 2 cross */
	};

struct monsterInfo
	{
	float a[MAXTRIBUTES][5];    /* vapour particles */
	float energyRemaining;	    /* amount of energy remaining */
	float rot1,rot2;
	float speed;		    /* movement speed */
	float xspeed;		    /* turning rate */
	float moveCost;		    /* energy loss from moving */
	float height;		    /* height of monster */
	float width;		    /* width of monster */
	float bottom;		    /* bottom of monster */
	float regenRate;	    /* rate of energy gain */
	int moveCount;		    /* for leg and wing rotation */
	int monsterID;		    /* code # of monster */
	int headHorzRotate;	    /* horizontal head angle */
	int headVertRotate;	    /* vertical head angle */
	int monsterScore;	    /* monster's score */
	int deadCount;		    /* time monster is dying */
	int timeDead;		    /* time monster has been dead */
	int monster;		    /* type of monster */
	int monsterIsDead;	    /* is monster alive or dead? */
	int beamOn;		    /* is the energy weapon on */
	int monsterGo;		    /* is the monster going forward? */
	int monsterBack;	    /* is the monster going backward? */
	int monsterMoving;	    /* is the monster moving? */
	};

struct targetInfo
	{
	struct monsterInfo monster;
	struct targetInfo * next;
	float x,z;
	float net_energyRemaining;
	float net_x,  net_z;
	long net_clientFrom;
	int net_headHorzRotate;
	int net_headVertRotate;
	int net_beamOn;
	int lastUpdateFrame;
	};

struct fireType
	{
	float x, z;		    /* location of flame */
	float xwid, zwid;	    /* width of flame */
	float height;		    /* height of flame */
	float col;		    /* color of flame */
	};

struct aSound
	{
	short *sampleBuffer;
	long samplesPerFrame;
	long numberSamples;
	long samplesPerBuffer;
	long audioRate;
	};

struct sound
	{
#ifdef SGIVERSION
	ALport audio_port;
#endif
	struct sound * next;
	int type;
	};

struct enemy
	{
	float r;		    /* range to enemy */
	float y;		    /* height of enemy */
	float ang;		    /* angle to enemy */
	};
	
struct score
    	{
	int number;
	char name[256];
    	};

/***************************
 * tk.c
 * 
 ***************************/

void tkCloseWindow(void);
static GLenum DoNextEvent(void);
void tkExec(void);
void tkGetMouseLoc(int *x, int *y);
static XVisualInfo *FindVisual(GLenum type);
static int MakeVisualType(XVisualInfo *vi);
static int WaitForMapNotify(Display *d, XEvent *e, char *arg);
void tkInitPosition(int x, int y, int width, int height);
void tkInitDisplayMode(GLenum type);
GLenum tkInitWindow(char *title);
static int Ignore(Display *parm1, XErrorEvent *parm2);
void tkSetRGBMap(int size, float *rgb);
void tkSwapBuffers(void);
void unGrabPointer();
void grabPointer();

/***************************
 * update.c
 * holds the update routines
 ***************************/

void showError(char *);
float buildingHeight(int,  int);
struct monsterInfo resetMonsterParameters(struct monsterInfo);

int same(char *, char *);
int different(char *, char *);


float centerText(char *,  float);

void updateGun(float, float, int, int, int,struct monsterInfo *);
void updateVap(float, float, int,struct monsterInfo *);
void updatetrees(struct tree *, int);
void updateBeam(struct monsterInfo *, struct targetInfo *, float, float, struct tank *, struct tree **, int, struct monsterInfo *);
void updateTanks(struct tank *, float, float, float, int, int, struct tank *, 
		float, int, int, struct monsterInfo *, struct targetInfo *);
void updateSlagTanks(struct tank *);
void updateBooms(struct boom *, struct tank *);
int tankHit(struct tank *, float, float, float);
void addNewTank(struct targetInfo *, float,  float,  int, struct tank *, struct tree *, int, int, struct monsterInfo *);


/****************************************************
 * audio.c
 * holds audio routines for battalion
 ****************************************************/

void turnSoundOff();
void turnSoundOn();
void toggleSound();
int getSoundOn();
void turnMusicOff();
void turnMusicOn();
void toggleMusic();
int getMusicOn();

void checkSound(char *);
void initSounds(void);
void flushSounds(void);
void soundKiller(int);
void doSound(int);
void InitAudio(char *,  char *, int);
void OutAudio(int);


/****************************************************
 * battalion.c
 * holds everything that hasnt been put somewhere else
 ****************************************************/

void goToHighDetail();
void goToLowDetail();

void updateScores(char *, int, int, int, char *);

void quickTanks(void);

int checkForBlock(struct tank *, float rad, float theta, float y);

void addScore(int, struct monsterInfo *);
void addBoom(float x, float y, float z,struct monsterInfo *);
void addProjectile( float x, float y, float z, int type, 
		    float xv, float yv, float zv, float accuracy,struct monsterInfo *);
void updateProjectiles(void);
void updatetrees(struct tree *, int);
void updateTanks(struct tank *, float, float, float, int, int, 
		struct tank*, float, int, int,
		struct monsterInfo *, struct targetInfo *);
void updateSlagTanks(struct tank *);
void addNewTank(struct targetInfo *, float, float, int, struct tank *, 
		struct tree *, int, int, struct monsterInfo *);
void updateBooms(struct boom *, struct tank *);

void buildHillPart(struct tree, int, float, float);

void setPlayConditions(void);
void addRandomTarget(void);

void initialization(void);

void goto3d(void);
void goto1d(void);

void checkMouse(void);
void checkInput (void);
GLenum MouseDown(int, int, GLenum);
GLenum MouseUp(int, int, GLenum);
void demoKeys(int);
void playKeys(int);
void playNoPauseKeys(int);
GLenum processKey(int, GLenum);
GLenum processKeyRelease(int);
void checkInput (void);

void updateDeadMonster(float, float, struct monsterInfo * );
void updateVapourLook(float a[MAXTRIBUTES][5], int);
void updateTargets(void);

void doUpdate (void);

void goToMonsterView(int);
void goToArmyView(int);
void goToMapView(void);
void goToOverView(int);

void drawAMonster(float, struct monsterInfo, float, int, int);

void doDrawing (int);

struct monsterInfo autopilot(float, float, struct monsterInfo);

void reshape( int, int);
static void doDisplay(void);
void id(void);

void showCommands(char *);

/*******************************
 * net.c
 * holds the network primitives
 *******************************/

void turnBeamOnSinceLast(void);
void setUnconnected(void);
void setPortNumber(int);
void setHostAddr(char *);

void addNewNetworkTank(char *, struct tank *, void *, int);
void updateNetworkTank(char *, struct tank *);
void tellAboutAllTanks(struct sockaddr_in *, int, struct tank *);

void updateClientMonster(char *, void *);


int setUpClient(void);
int setUpNetwork(void);
void updateNetworkBuildings(char *, struct tree *);
void updateNetworkMonsters(char *, long, void *);
int sendMessage(char *, struct sockaddr_in *, int);
void processClient(time_t, int, int, struct tree *, struct tank *,
    void * arena, int sizeTank, struct monsterInfo, int, int *);
void tellAboutAllDeadBuildings(struct sockaddr_in *, int, int, int *);
void processNetwork(time_t, int, int, struct tree *, struct tank *,
    void *, struct monsterInfo, int, int, int *, int *);
void addNetworkTarget(long, int, float, float, float, float, float,
    int, void *);

/*******************************
 * gprim.c
 * holds the graphics primitives
 *******************************/

void drawCylinder(float *, float *, float, int,  int, int);
void drawClosedCylinder(float *, float *,  int, int);

void drawCone(float *, float *, float, int,  int);
void drawClosedCone(float *, float *,  int);

void maker(float tail2[8][3], float,  float,  float,
		float,  float,  float, 
		float *,  float,  float,  float,  float);

void makerP(float tail2[8][3], float *, float,  float,  float,
		float,  float,  float);


void makeitd(int,  float *,  float,  float,  float,
		float,  float,  float);

void makeitPyr(int,  float *,  float,  float,  float,
		float,  float,  float);

void makercube(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4]);

void makerbluecube(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4]);

void makercubenobacknotop(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4]);

void makerlogo(float x,  float y,  float z,
		float u,  float v,  float w, int, int, int);
		
void makercubeTopBack(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4]);

void makercubenobtm(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4]);

void makercubenobtmnotop(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4]);

void makercubenobtmnotopTEX(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4]);

void makerrotcubexy(float u,  float v,  float w, 
		float theta, float c[4]);
		
void makerrotcubexyflat(float u,  float v,  float w, 
		float theta, float c[4]);


/*****************************************
 * objects.c
 * holds the objects for the graphics routines
 *****************************************/

GLuint makeMonsterLookat(void);
GLuint makeOverviewLookat(void);

GLuint makeshell2(void);
GLuint makeHeroShell(void);
GLuint makeWaterShell(void);

GLuint makeTankShadow(void);
GLuint makeFighterShadow(void);
GLuint makePlaneShadow(void);

GLuint makeTank(void);
GLuint makeSlagTank(void);
GLuint makeLauncherTank(void);
GLuint makeSlagLauncherTank(void);
GLuint makeMaserTank(void);
GLuint makeSlagMaserTank(void);

GLuint makeHelo(void);
GLuint makeSlagHelo(void);
GLuint makeBigRotor(void);
GLuint makeSmallRotor(void);
GLuint makePropeller(void);
GLuint makeAirplaneBody(void);
GLuint makeFighterBody(void);

GLuint makeLeg(void);
GLuint makeHead(void);
GLuint makeTail(void);
GLuint makeSimpleHead(void);
GLuint makeSimpleTail(void);
GLuint makeBody(void);

GLuint makeFlutterHead(void);
GLuint makeFlutterShadow(void);
GLuint makeFlutterXMas(void);
GLuint makeFlutterBody(void);
GLuint makeFlutterWing1(void);
GLuint makeFlutterWing2(void);

GLuint makeTechsBody(void);
GLuint makeTechsHead(void);
GLuint makeTechsSimpleBody(void);
GLuint makeTechsSimpleHead(void);
GLuint makeTechsShadow(void);

GLuint makePowerTower(void);
GLuint makeGenericWindows(void);
GLuint makebuilding1(int);
GLuint makebuilding2(int);
GLuint makebuilding5(int);
GLuint makebuilding7(void);
GLuint makebuilding9(int);
GLuint makebuilding10(void);
GLuint makebuilding12(int);
GLuint makebuilding14(void);
GLuint makebuilding19(int);
GLuint makebuilding20(int);
GLuint makebuilding21(int);
GLuint makebuilding31(void);
GLuint makebuilding32(void);
GLuint makeStrip1(int);
GLuint makeStrip2(int);
GLuint makeStrip3(int);

GLuint makeTitles(int);

GLuint makeLowDPlane(void);
GLuint makeHighDPlane(void);
GLuint makeBigPlane(void);
GLuint makePlaneDots(int);

GLuint makeRoundTreeShadow(void);

/*****************************************
 * text.c
 * holds the textual overlay routines
 *****************************************/

void initFonts(void);
void showText(struct targetInfo *, float,  int,  long, int, int);
void showText2(long, int, int, int, int, int, int, int, int, int);
void showText3(int);
void showText4(void);

void doOptions(struct monsterInfo, long, int, int, float, int);
void doSummary(int,  int, long, int,
		int, int, int,
		int, int, int, int, int, int, int,int);

void showScores(int, struct score*, struct score*, struct score*, struct score*, struct monsterInfo, int,float, int);

/*****************************************
 * graphics.c
 * holds the higher level graphics routines
 *****************************************/

void makeObjects(char *);

void shadow (float,  float,  float,  float);

void makeCHH(int);
void drawHelo(float, int);
void drawAirplane(int);
void drawFighter();

void drawMonster(struct monsterInfo, int, int, int);
void drawSimpleMonster(struct monsterInfo, int, int, int);

void drawVapour(struct monsterInfo, int, int);

void drawFlutter(struct monsterInfo, int, int, float, int, int);
void drawTechs(struct monsterInfo, int);
void drawSimpleTechs(struct monsterInfo, int);
void drawHeroDude(int, int,  int, int, int);
void drawHeroDude2(int, int,  int, int, int);
void drawMechaMonster(int, int, int);

void wzminus(float,  float,  float,  float,  float);
void wzplus(float,  float,  float,  float,  float);
void wxplus(float,  float,  float,  float,  float);
void wxminus(float,  float,  float,  float,  float);


void makeBooms(void);

void drawBuilding0(float *, int);
void drawBuilding6(int, float *,  float *, int);
void drawBuilding8(float *,float *, int);
void drawBuilding11(int);
void drawBuilding15(float *,  float *, int);
void drawBuilding22(float *);
void drawBuilding25(void);
void drawBuilding26(int, int);
void drawBuilding29(int,int);
void drawBuilding33(int, int);
void drawTower(int, int);
void drawCoolingTower(int);

void drawHills(int,int);
void drawWater(int,int);

void drawBattlefield(struct road *, float, float, int, int,int);

void drawLake0(int);
void drawLake1(int);
void drawHill0(int);
void drawHill1(int, int);
void drawHill2(int, int);
void drawHill3(int, int);

void drawtrees(struct tree *, int, int, int, int,int);

void drawSlagTanks(struct tank *, int, int);
void drawTanks(struct tank *, int, struct monsterInfo, struct targetInfo *, int, int,int);

void drawMaser(float, float, float, int, float, float, float, float, float, float, float, int, int, int);
void drawHeroWeapon(float, float, float, float, float, float *, float, float);

void drawBooms(struct boom *, int);
void drawBeam(float, float, int,  int, int, int);

void drawRoads(struct road *,  float,  float, int, int, int);
void drawProjectiles(struct projectile *, int, struct fireType*, int, int, int);

void andysphdraw(float loc[4], int);

