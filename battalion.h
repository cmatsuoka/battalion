#ifndef BATTALION_H_
#define BATTALION_H_

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

/* text buffer size */
#define TEXT_SIZE (256 + 50 + MAXPATH)
/* message size */
#define MESG_SIZE (MAXLINE + 20)
/* score name size */
#define NAME_SIZE 16

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

#include <AL/al.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include "tk.h"


#include <time.h>
#include <sys/time.h>


/* audio routines */
/*****************/

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



#define MONSTERFOGSTART		2.5
#define MONSTERFOGEND		6.0

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
#define ELECTRIC            8
#define TELEPORTER          9

/************************/
/*   music              */
/************************/
#define ID_MUSIC        1

#define MUSIC_OFFSET   10

#define PLAY_MUSIC      0
#define DEMO_MUSIC      1
#define DEFEAT_MUSIC    2
#define SUCCESS_MUSIC   3

#define MUSIC               8

/* #define MAXMUSIC 36 */
#define MAXMUSIC 2
#define MAXDEADMUSIC 2

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
        ALuint source;              /* sound source */
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
        ALuint source;              /* sound source */
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
	char name[NAME_SIZE];
    	};


#define same(x,y) (!strcmp(x, y))


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

void doDrawing (int);

struct monsterInfo autopilot(float, float, struct monsterInfo);

void reshape( int, int);
void id(void);

void showCommands(char *);


void showError(char *);


#endif  // BATTALION_H_

