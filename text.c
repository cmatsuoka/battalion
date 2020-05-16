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
/* text.c v 1.3                                                        */
/* routines to display all the textual overlays for battalion          */
/***********************************************************************/

#include "battalion.h"

    /*************/
    /* colours   */
    /*************/

extern float colorolive[4];
extern float  planeGreen[4];
extern float  planeGreen2[4];
extern float  planeGreen3[4];
extern float  colorgreen[4];

extern float  colorblack[4];

extern float  colorred[4];
extern float  colorred_50[4];
extern float  colorred2[4];
extern float  colorred3[4];

extern float  colormaserblue[4];
extern float  colormaserblue2[4];

extern float  colorwhite[4];
extern float  colorwhite2[4];

extern float  colorsnow[4];
extern float  colorsnow2[4];

extern float  colorgrey1[4];
extern float  colorgrey1_50[4];
extern float  colorgrey2[4];
extern float  colorgrey3[4];
extern float  colorgrey3_50[4];
extern float  colorgrey4[4];

extern float  colorbrown[4];
extern float  colorbeige[4];

extern float  colorblue[4];
extern float  colorwater[4];

extern float  colorsnowvapour[4];

extern float  coloryellow[4];
extern float  colormaseryellow[4];
extern float  colororange[4];

extern float  healthGreen[4];

extern float  treeColor[4];
extern float  treeColor2[4];



extern GLuint titleObj;
extern GLuint titleObjOO;
extern GLuint titleObjOOO;

extern GLuint plaintank;
extern GLuint masertank;  
extern GLuint launchertank;

    GLuint strokeBase;
    char textline[80];

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void initFonts(void)
    {
    strokeBase = glGenLists(256);
    if (tkCreateStrokeFont(strokeBase) == GL_FALSE)
	{
	showError("Can't create font");
	exit(1);
	}
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw status display (energy and score)                        */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void showText(struct targetInfo * targets, float energy, int score,
	    long winX, int paused,  int grabbed)
    {
    float pixtoSpace;
    struct targetInfo * temptarget;
    float drop;

static    char energyEnglish[]		= "energy:";
static    char pausedEnglish[]		= "<p>aused";
static    char grabbedEnglish[]		= "<g>rabbed";
    
static float energyBar[4][3] = {
	-4.0, 4.81, 0.0, 
	-4.0, 4.39, 0.0, 
	 0.0, 4.39, 0.0, 
	 0.0, 4.81, 0.0};

    glPushAttrib(GL_DEPTH_BUFFER_BIT);
    
    glDisable(GL_DEPTH_TEST);
         
    pixtoSpace = 10.0 / winX;

    /* draw the energy bar */


    if (energy > (MAXLIFE / 3))
	glColor3fv(healthGreen);
    else if (energy > (MAXLIFE / 10))
	glColor3fv(colorbrown); 
    else
	glColor3fv(colorred); 
	
    energyBar[2][0] = energyBar[3][0] = energy / MAXLIFE * 3 - 4;

    glPushAttrib(GL_POLYGON_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

    glBegin(GL_QUADS);
	glVertex3fv(energyBar[0]);
	glVertex3fv(energyBar[1]);
	glVertex3fv(energyBar[2]);
	glVertex3fv(energyBar[3]);
    glEnd(); 


    energyBar[2][0] = energyBar[3][0] = -1;


    glColor3fv(colorwhite);	
	
    glBegin(GL_LINE_LOOP);
	glVertex3fv(energyBar[0]);
	glVertex3fv(energyBar[1]);
	glVertex3fv(energyBar[2]);
	glVertex3fv(energyBar[3]);
    glEnd(); 

    /************************************************/
    /* draw energy bar for any target on the screen */
    /************************************************/

    if (targets->next != NULL)
	{
	drop = 0;
	for(temptarget = targets->next; temptarget != NULL; temptarget = temptarget->next)
	    if ((fabs(temptarget->x) <= PLANESIZE) && (fabs(temptarget->z) <= PLANESIZE))
	    {
	    drop -=0.6;
    
	    glPushMatrix();
		glTranslatef(0, drop, 0);
    
		energy = temptarget->monster.energyRemaining;
    
		if (energy > (MAXLIFE / 3))
		    glColor3fv(healthGreen);
		else if (energy > (MAXLIFE / 10))
		    glColor3fv(colorbrown); 
		else
		    glColor3fv(colorred); 
		    
		energyBar[2][0] = energyBar[3][0] = energy / MAXLIFE * 3 - 4;
	    
		glBegin(GL_QUADS);
		    glVertex3fv(energyBar[0]);
		    glVertex3fv(energyBar[1]);
		    glVertex3fv(energyBar[2]);
		    glVertex3fv(energyBar[3]);
		glEnd(); 
	    
		energyBar[2][0] = energyBar[3][0] = -1;
	    
		glColor3fv(colorwhite);	
		    
		glBegin(GL_LINE_LOOP);
		    glVertex3fv(energyBar[0]);
		    glVertex3fv(energyBar[1]);
		    glVertex3fv(energyBar[2]);
		    glVertex3fv(energyBar[3]);
		glEnd(); 
    
	    glPopMatrix();
    
	    glPushMatrix();
		glTranslatef(-3.8,  4.4+drop,  0);
		
		switch(temptarget->monster.monster)
		    {
		    case GOOGELON:  tkDrawStr(strokeBase,"Googelon");
				    break;
		    case TECHS:	    tkDrawStr(strokeBase,"Techs");
				    break;
		    case VAPOUR:    tkDrawStr(strokeBase,"Vapour");
				    break;
		    case FLUTTER:   tkDrawStr(strokeBase,"Flutter");
				    break;
		    }
		glPopMatrix();
	    }	
	}
	
    glPopAttrib(); /* polygon drawing */
 
    glPushMatrix();
	glTranslatef(-3.8,  4.45,  0);
	tkDrawStr(strokeBase, energyEnglish);
    glPopMatrix();

    /***********************/
    /* print out the score */
    /***********************/


    sprintf(textline, "score: %1d", score);
    
    glPushMatrix();
	glTranslatef(1.9,  4.45,  0);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();


    /****************************/
    /* print out the frame rate */
    /****************************/

#ifdef DEBUG
    sprintf(textline,  "%d",  winX);

    glPushMatrix();
	glTranslatef(0,  4.4,  0);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
#endif

    if (paused)
	{
	glPushMatrix();
	    glTranslatef(-0.7,  4.6,  0);	
	    tkDrawStr(strokeBase, pausedEnglish);
	glPopMatrix();

	}
	
    if (grabbed)
	{
	glPushMatrix();
	    glTranslatef(-0.85,  4.2,  0);	
	    tkDrawStr(strokeBase, grabbedEnglish);
	glPopMatrix();

	}
	
    glPopAttrib();
    }   

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void showScores(int itsChristmas, struct score* gscore, struct score* vscore,
		struct score* tscore, struct score* fscore, 
		struct monsterInfo monster, int counter,
		float offsetX, int detail)
    {
    char textString[256];
    struct monsterInfo tempMonster;
    GLfloat lineWidthNow;

static    float scoreBox[4][3] = {
	-1,  0.42, 7.1,
	-1, -0.6, 7.1,
	 1, -0.6, 7.1, 
	 1,  0.42, 7.1};

glPushAttrib(GL_DEPTH_BUFFER_BIT);

    /***********************************/
    /* these monsters are always alive */
    /***********************************/
   
    tempMonster 		= monster;
    tempMonster.energyRemaining = 100;
    tempMonster.monsterIsDead 	= 0;
    tempMonster.deadCount 	= 0;
        	
    /*************************************/
    /* draw transparent brown background */
    /*************************************/

    glColor4fv(colorbrown);

    glDisable(GL_DEPTH_TEST);

    if (detail <= 0)
	{
	glBegin(GL_QUADS);
	    glVertex3fv(scoreBox[0]);
	    glVertex3fv(scoreBox[1]);
	    glVertex3fv(scoreBox[2]);
	    glVertex3fv(scoreBox[3]);
	glEnd();		
 	}
    else
	{
	glEnable(GL_BLEND);
	
	glBegin(GL_QUADS);
	    glVertex3fv(scoreBox[0]);
	    glVertex3fv(scoreBox[1]);
	    glVertex3fv(scoreBox[2]);
	    glVertex3fv(scoreBox[3]);
	glEnd();		
     
	glDisable(GL_BLEND);
	}

    /*****************/
    /* draw monsters */
    /*****************/

    if (detail != -1)
	glEnable(GL_DEPTH_TEST);

    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
    glLineWidth(2.01);

	    
    glPushMatrix();
	glTranslatef(-0.8,  0.14,  7.2);
	glScalef(.2,  .2,  .2);
	drawMonster(tempMonster, counter, itsChristmas, detail);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-0.8,  -0.23,  7.2);
	glScalef(.2,  .2,  .2);
	drawVapour(tempMonster, itsChristmas, detail);
    glPopMatrix();
	
    glPushMatrix();
	glTranslatef(+.14,  0.1,  7.2);
	glScalef(.2,  .2,  .2);
	drawTechs(tempMonster, detail);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(+.14,  -0.26,  7.2);
	glScalef(.2,  .2,  .2);
	drawFlutter(tempMonster, counter, itsChristmas, offsetX, OMNISCIENTVIEW, detail);
    glPopMatrix();

    glLineWidth(lineWidthNow);


    /*************/
    /* draw text */
    /*************/

    glColor3fv(colorwhite); 

   glDisable(GL_DEPTH_TEST);

    glPushMatrix();
	glTranslatef(-2,  1.4,  0);
	tkDrawStr(strokeBase, "High Scores");
    glPopMatrix();


    /*************************************/


    if (gscore[0].number > -1)
        {
	sprintf(textString, "%5d %s", gscore[0].number, gscore[0].name); 
	glPushMatrix();
	    glTranslatef(-4,  0.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
        }
    else
	{
	glPushMatrix();
	    glTranslatef(-4,  0.5,  0);
	    tkDrawStr(strokeBase, "  none");
	glPopMatrix();
	}
    
    if (gscore[1].number > -1)
        {
	sprintf(textString, "%5d %s", gscore[1].number, gscore[1].name); 
	glPushMatrix();
	    glTranslatef(-4,  0,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
       }
    
    if (gscore[2].number > -1)
        {
	sprintf(textString, "%5d %s", gscore[2].number, gscore[2].name); 
	glPushMatrix();
	    glTranslatef(-4,  -0.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
        }

    /*************************************/

    if (vscore[0].number > -1)
        {
	sprintf(textString, "%5d %s", vscore[0].number, vscore[0].name); 
	glPushMatrix();
	    glTranslatef(-4,  -1.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}
    else
	{
	glPushMatrix();
	    glTranslatef(-4,  -1.5,  0);
	    tkDrawStr(strokeBase, "  none");
	glPopMatrix();
	}
	
    if (vscore[1].number > -1)
        {
	sprintf(textString, "%5d %s", vscore[1].number, vscore[1].name); 
	glPushMatrix();
	    glTranslatef(-4,  -2,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}

    if (vscore[2].number > -1)
        {
	sprintf(textString, "%5d %s", vscore[2].number, vscore[2].name); 
	glPushMatrix();
	    glTranslatef(-4,  -2.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}
	
    /*************************************/

    if (tscore[0].number > -1)
        {
	sprintf(textString, "%5d %s", tscore[0].number, tscore[0].name); 
	glPushMatrix();
	    glTranslatef(0.6,  0.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}
    else
	{
	glPushMatrix();
	    glTranslatef(0.6,  0.5,  0);
	    tkDrawStr(strokeBase, "  none");
	glPopMatrix();
	}
	
   if (tscore[1].number > -1)
        {
	sprintf(textString, "%5d %s", tscore[1].number, tscore[1].name); 
	glPushMatrix();
	    glTranslatef(0.6,  0,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}
	
   if (tscore[2].number > -1)
        {
	sprintf(textString, "%5d %s", tscore[2].number, tscore[2].name); 
	glPushMatrix();
	    glTranslatef(0.6,  -0.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}
	
    /*************************************/

    if (fscore[0].number > -1)
        {
	sprintf(textString, "%5d %s", fscore[0].number, fscore[0].name); 
	glPushMatrix();
	    glTranslatef(0.6,  -1.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}
    else
	{
	glPushMatrix();
	    glTranslatef(0.6,  -1.5,  0);
	    tkDrawStr(strokeBase, "  none");
	glPopMatrix();
	}

    if (fscore[1].number > -1)
        {
	sprintf(textString, "%5d %s", fscore[1].number, fscore[1].name); 
	glPushMatrix();
	    glTranslatef(0.6,  -2,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}
	
    if (fscore[2].number > -1)
        {	
	sprintf(textString, "%5d %s", fscore[2].number, fscore[2].name); 
	glPushMatrix();
	    glTranslatef(0.6,  -2.5,  0);
	    tkDrawStr(strokeBase, textString);
	glPopMatrix();
	}

    glPopAttrib();
    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw list of views/options/controls)                          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void showText2(long winX, int soundOn, int noSound, int musicOn, 
		int mode3D, int no3D, int detail, int paused,
		int itsChristmas, int ptrGrab)
    {
    float pixtoSpace;
    float right;
    int garbage;

static    char viewsEnglish[]	= "Views:";
static    char views1English[]	= "-Monster";
static    char views2English[]	= "-Overview";
static    char views3English[]	= "-Army";

static    char onstring[]		= " (ON)";
static    char offstring[]		= " (OFF)";
static    char linstring[]		= " (VEC)";
static    char lowstring[]		= " (LOW)";
static    char medstring[]		= " (MED)";
static    char highstring[]		= " (HIGH)";
static    char unavailablestring[] 	= " ( - )";

static    char moveEnglish[]		= "mouse/arrows";
static    char shootEnglish[]		= "left btn/ctrl";
static    char azEnglish[]		= "a z";

static    char grabEnglish[]		= "-PtGrab";
/* static    char videoEnglish[]	= "-3D"; */

static    char rotateEnglish[]		= "- Rotate Overview";
static    char ijklEnglish[]		= "ijkl";
static    char showcaseEnglish[]	= "-Help";

static    char pauseEnglish[]		= "-Pause";
static    char detailEnglish[]		= "-Detail";
static    char soundEnglish[]		= "-Sound";
static    char musicEnglish[]		= "-Music";

    glPushAttrib(GL_DEPTH_BUFFER_BIT);
    
    pixtoSpace = 3.0/ winX;
          
    glDisable(GL_DEPTH_TEST);


    if (itsChristmas)
	glColor3fv(planeGreen); 
    else
	glColor3fv(coloryellow); 

    /*********/
    /* views */
    /*********/

    glPushMatrix();
	glTranslatef(-5.0,  +0.7,  0);
	tkDrawStr(strokeBase, viewsEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-4.8,  0.2,  0);
	tkDrawStr(strokeBase, "1");
	
	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, views1English);
    glPopMatrix();
    
    glPushMatrix();
	glTranslatef(-4.8,  -0.3,  0);
	tkDrawStr(strokeBase, "2");
	
	glTranslatef(0.2,  0,  0);	
	tkDrawStr(strokeBase, views2English);
    glPopMatrix();    
    
    glPushMatrix();
	glTranslatef(-4.8,  -0.8,  0);
	tkDrawStr(strokeBase, "3");
	
	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, views3English);
    glPopMatrix();    



    /************/
    /* controls */
    /************/

    if (mode3D)
	right = 0.2;
    else
	right = -1.0;


    glPushMatrix();
	glTranslatef(right+0.3,  -2,  0);
	tkDrawStr(strokeBase, "Controls:");
    glPopMatrix();

    glPushMatrix();
	glTranslatef(right + 0.5,  -2.5,  0);
	tkDrawStr(strokeBase, moveEnglish);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(right + 4.1,  -2.5,  0);
	tkDrawStr(strokeBase, "-Move");
    glPopMatrix();
	

    glPushMatrix();
	glTranslatef(right + 0.5,  -3,  0);
	tkDrawStr(strokeBase, shootEnglish);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(right + 4.1,  -3,  0);
	tkDrawStr(strokeBase, "-Attack");
    glPopMatrix();
   

    glPushMatrix();
	glTranslatef(right+0.5,  -3.5,  0);
	tkDrawStr(strokeBase, azEnglish);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(right + 3.25,  -3.5,  0);
	tkDrawStr(strokeBase, "-Tilt Head");
    glPopMatrix();


    glPushMatrix();
	glTranslatef(right+0.5,  -4,  0);
	tkDrawStr(strokeBase, ijklEnglish);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(right+1.5,  -4,  0);
	tkDrawStr(strokeBase, rotateEnglish);
    glPopMatrix();

    /***********/
    /* options */
    /***********/


    glPushMatrix();
	glTranslatef(-5,  -2,  0);
	tkDrawStr(strokeBase, "Options:");
    glPopMatrix();



    glPushMatrix();
	glTranslatef(-4.8,  -2.5,  0);
	tkDrawStr(strokeBase, "d");

	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, detailEnglish);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(-2.65,  -2.5,  0);
	switch (detail) {
	case -1:
	    tkDrawStr(strokeBase, linstring);
	    break;
	case 0:
	    tkDrawStr(strokeBase, lowstring);
	    break;
	case 1:
	    tkDrawStr(strokeBase, medstring);
	    break;
	case 2:
	    tkDrawStr(strokeBase, highstring);
	    break;
	}
    glPopMatrix();
    
    


    glPushMatrix();
	glTranslatef(-4.8,  -3,  0);
	tkDrawStr(strokeBase, "s");

	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, soundEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-2.65,  -3,  0);

	if (noSound)
	    tkDrawStr(strokeBase,unavailablestring);
	else
	    soundOn ? tkDrawStr(strokeBase,onstring) : tkDrawStr(strokeBase,offstring);
    glPopMatrix();


    glPushMatrix();
	glTranslatef(-4.8,  -3.5,  0);
	tkDrawStr(strokeBase, "m");

	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, musicEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-2.65,  -3.5,  0);

	if (noSound)
	    tkDrawStr(strokeBase,unavailablestring);
	else
	    musicOn ? tkDrawStr(strokeBase,onstring) : tkDrawStr(strokeBase,offstring);
    glPopMatrix();
	
	
    glPushMatrix();
	glTranslatef(-4.8,  -4,  0);
	tkDrawStr(strokeBase, "p");

	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, pauseEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-2.65,  -4,  0);
	paused ? tkDrawStr(strokeBase,onstring) : tkDrawStr(strokeBase,offstring);
    glPopMatrix();


    glPushMatrix();
	glTranslatef(-4.8,  -4.5,  0);
	tkDrawStr(strokeBase, "g");

	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, grabEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-2.65,  -4.5,  0);

	ptrGrab ? tkDrawStr(strokeBase,onstring) :
		  tkDrawStr(strokeBase,offstring);
    glPopMatrix();

    garbage = no3D;
/* someday the 3D from the Original GL version will return in
 * the OpenGL version ... but not yet

    glPushMatrix();
	glTranslatef(-4.8,  -4.5,  0);
	tkDrawStr(strokeBase, "v");

	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, videoEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-2.65, -4.5,  0);

	if (no3D)
	    tkDrawStr(strokeBase,unavailablestring);
	else
	    mode3D ? tkDrawStr(strokeBase,onstring) : tkDrawStr(strokeBase,offstring);

    glPopMatrix();
*/

    glPushMatrix();
	glTranslatef(-4.8,  -5,  0);
	tkDrawStr(strokeBase, "h");

	glTranslatef(0.2,  0,  0);
	tkDrawStr(strokeBase, showcaseEnglish);
    glPopMatrix();

#ifndef SGIVERSION
    glPushMatrix();
	glTranslatef(-2.75,  -5,  0);

	tkDrawStr(strokeBase,unavailablestring);

    glPopMatrix();
#endif

    glPopAttrib();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw the 'andy johnson's battalion' title                     */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void showText3(int detail)
    {
static    char andyEnglish[]		= "andy johnson's";
static    char versionEnglish[]		= "1.3";

    /************************/
    /* print battalion logo */
    /************************/

    if (detail > 0)
	glCallList(titleObj);
    else if (detail == 0)
	glCallList(titleObjOO);
    else if (detail == -1)
	{
	glPushAttrib(GL_POLYGON_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glCallList(titleObjOOO);
	glPopAttrib();
	}
	
    glColor3fv(colorwhite); 

    /**************************/
    /* print "andy johnsons'" */
    /**************************/

    glPushMatrix();
	glTranslatef(1.6 ,  +3.85,  0);
	glScalef(0.57, 0.83, 1);
	tkDrawStr(strokeBase, andyEnglish);
    glPopMatrix();

    /************************/
    /* print version number */
    /************************/

    glPushMatrix();
	glTranslatef(4.3,  -5.1,  0);
	glScalef(0.75, 0.75, 1);
	tkDrawStr(strokeBase, versionEnglish);
    glPopMatrix();
   }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw 'press spacebar to begin'                                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void showText4()
    {
static    char spaceEnglish[]		= "Press the spacebar to begin";

    glColor3fv(colorwhite); 

    glPushMatrix();
	glTranslatef(-3.85,  2.3,  0);
	tkDrawStr(strokeBase, spaceEnglish);
    glPopMatrix();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw option menu for choosing monster                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void doOptions(struct monsterInfo monster, long xWin, int counter,
		int itsChristmas, float offsetX, int detail)
    {
    float pixtoSpace;
    struct monsterInfo tempMonster;
    GLfloat lineWidthNow;

static    char googelonEnglish[]	= "Googelon-6";    
static    char techsEnglish[]		= "Techs-7";    
static    char vapourEnglish[]		= "The Vapour-8";    
static    char flutterEnglish[]		= "Flutter-9";

    static float optionsBox[4][3] = {
	-0.85,  0.5, 7.1,
	-0.85, -1.0, 7.1,
	 0.85, -1.0, 7.1, 
	 0.85,  0.5, 7.1};

    glPushAttrib(GL_DEPTH_BUFFER_BIT);
 
    /***********************************/
    /* these monsters are always alive */
    /***********************************/
   
    tempMonster 		= monster;
    tempMonster.energyRemaining = 100;
    tempMonster.monsterIsDead 	= 0;
    tempMonster.deadCount 	= 0;
        	
    /*************************************/
    /* draw transparent brown background */
    /*************************************/

    glDisable(GL_DEPTH_TEST);

    glColor4fv(colorbrown);

    if (detail <= 0)
	{
	glBegin(GL_QUADS);
	    glVertex3fv(optionsBox[0]);
	    glVertex3fv(optionsBox[1]);
	    glVertex3fv(optionsBox[2]);
	    glVertex3fv(optionsBox[3]);
	glEnd();		
	}
    else
	{
	glEnable(GL_BLEND);
	
	glBegin(GL_QUADS);
	    glVertex3fv(optionsBox[0]);
	    glVertex3fv(optionsBox[1]);
	    glVertex3fv(optionsBox[2]);
	    glVertex3fv(optionsBox[3]);
	glEnd();		
    
	glDisable(GL_BLEND);
	}


    /*************/
    /* draw text */
    /*************/

    pixtoSpace = 2.0 / xWin;

    glColor3fv(colorwhite); 

    glPushMatrix();
	glTranslatef(-2.72,  1.75,  0);	
	tkDrawStr(strokeBase, "Choose your monster:");
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-3.72,  -.6,  0);
	tkDrawStr(strokeBase, googelonEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1.2,  -.6,  0);
	tkDrawStr(strokeBase, techsEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-4,  -4,  0);
	tkDrawStr(strokeBase, vapourEnglish);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(1.1,  -4,  0);
	tkDrawStr(strokeBase, flutterEnglish);
    glPopMatrix();


    /*****************/
    /* draw monsters */
    /*****************/

    if (detail != -1)
	glEnable(GL_DEPTH_TEST);

    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
    glLineWidth(2.01);
	    
    glPushMatrix();
	glTranslatef(-.5,  0.25,  7.2);
	glScalef(.25,  .25,  .25);
	drawMonster(tempMonster, counter, itsChristmas, detail);
    glPopMatrix();
	
    glPushMatrix();
	glTranslatef(+.5,  0.25,  7.2);
	glScalef(.25,  .25,  .25);
	drawTechs(tempMonster, detail);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(-.5,  -0.4,  7.2);
	glScalef(.25,  .25,  .25);
	drawVapour(tempMonster, itsChristmas, detail);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(+.5,  -0.4,  7.2);
	glScalef(.25,  .25,  .25);
	drawFlutter(tempMonster, counter, itsChristmas, offsetX, OMNISCIENTVIEW, detail);
    glPopMatrix();

    glPopAttrib();

    glLineWidth(lineWidthNow);
   }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw summary of kills                                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void doSummary(int monster,  int deadTime, long winX, int killtanks,
		int killmtanks, int killhelos,
		int killCHHs, int killmechags,
		int killheros, int killplanes, int killlaunchers,
		int killfighters,
		int counter, int detail, int moreThanOne)
    {    
    int angle;
    float pixtoSpace;
    char resultString[15];
    char monsterString[40];
    GLfloat lineWidthNow;

static    float summaryBox[4][3] = {
	-0.97,  0.25,  7.0,
	-0.97, -1.05,  7.0,
	 0.97, -1.05,  7.0, 
	 0.97,  0.25,  7.0};

    glPushAttrib(GL_DEPTH_BUFFER_BIT);

    pixtoSpace = 2.0 / winX;

    angle = (deadTime * 10) % 3600;

    glDisable(GL_DEPTH_TEST);

    glColor4fv(colorbrown);
    
    if (detail <= 0)
	{
	glBegin(GL_QUADS);
	    glVertex3fv(summaryBox[0]);
	    glVertex3fv(summaryBox[1]);
	    glVertex3fv(summaryBox[2]);
	    glVertex3fv(summaryBox[3]);
	glEnd();		
	}
    else
	{
	glEnable(GL_BLEND);
	
	glBegin(GL_QUADS);
	    glVertex3fv(summaryBox[0]);
	    glVertex3fv(summaryBox[1]);
	    glVertex3fv(summaryBox[2]);
	    glVertex3fv(summaryBox[3]);
	glEnd();		
    
	glDisable(GL_BLEND);
	}
    

    glColor3fv(colorwhite); 

    if ((killtanks > 0) || (killlaunchers > 0) || (killmtanks > 0) || (killhelos > 0) ||
	(killmechags > 0) || (killfighters > 0) || (killCHHs > 0) || (killheros > 0) || (killplanes > 0))
	    strcpy(resultString, ":");
    else
	    strcpy(resultString, " nothing.");

    if (moreThanOne)    
	{
	 sprintf(monsterString, "The monsters destroyed %s", resultString);
	}
    else
	{
	switch(monster){
	    case GOOGELON:  sprintf(monsterString, "Googelon destroyed %s", resultString);
			    break;
	    case VAPOUR:    sprintf(monsterString, "The Vapour destroyed %s", resultString);
			    break;
	    case TECHS:     sprintf(monsterString, "Techs destroyed %s", resultString);
			    break;
	    case FLUTTER:   sprintf(monsterString, "Flutter destroyed %s", resultString);
			    break;
	    default:	    showError("Bogus Monster! (doSummary)");
			    break;
	    }
	}

    glPushMatrix();
	glTranslatef(-4.25, .5,  0);
	tkDrawStr(strokeBase, monsterString);
    glPopMatrix();


    if (killfighters > 0)
	{
    glPushMatrix();
	glTranslatef(-2.9-1.3,  -2.3,  0);
	if (killfighters > 1)
		sprintf(textline,  "%1u Fighters", killfighters);
	else
		sprintf(textline,  "%1u Fighter", killfighters);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}

    if (killtanks > 0)
	{
    glPushMatrix();
	glTranslatef(-3-1.1,  -1,  0);
	if (killtanks > 1)
		sprintf(textline,  "%1u Tanks", killtanks);
	else
		sprintf(textline,  "%1u Tank", killtanks);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}

    if (killlaunchers > 0)
	{
    glPushMatrix();
	glTranslatef(2.6-1.6,  -2.3,  0);
	if (killlaunchers > 1)
		sprintf(textline,  "%1u Launchers", killlaunchers);
	else
		sprintf(textline,  "%1u Launcher", killlaunchers);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}
	
    if (killhelos > 0)
	{
    glPushMatrix();
	glTranslatef(3.1-1.0,  -1,  0);
	if (killhelos > 1)
		sprintf(textline,  "%1u Helos", killhelos);
	else
		sprintf(textline,  "%1u Helo", killhelos);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}

    if (killmtanks > 0)
	{
    glPushMatrix();
    	glTranslatef(-0.2-1.2, -2.8,  0);
	if (killmtanks > 1)
		sprintf(textline,  "%1u Masers", killmtanks);
	else
		sprintf(textline,  "%1u Maser", killmtanks);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}


    if (killplanes > 0)
	{
    glPushMatrix();
	glTranslatef(0-1.4,  -1,  0);
	if (killplanes > 1)
		sprintf(textline,  "%1u Bombers", killplanes);
	else
		sprintf(textline,  "%1u Bomber", killplanes);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}
	
	
    if (killmechags > 0)
	{
    glPushMatrix();
	glTranslatef(2.8-1.4,  -4.7,  0);
	if (killmechags > 1)
		sprintf(textline,  "%1u MechaGs", killmechags);
	else
		sprintf(textline,  "%1u MechaG", killmechags);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}
	
    if (killCHHs > 0)
	{
    glPushMatrix();
	glTranslatef(0-1.3,  -4.7,  0);
	if (killCHHs > 1)
		sprintf(textline,  "%1u Hunters", killCHHs);
	else
		sprintf(textline,  "%1u Hunter", killCHHs);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}

    if (killheros > 0)
	{
    glPushMatrix();
	glTranslatef(-3-1.0,  -4.7,  0);
	if (killheros > 1)
		sprintf(textline,  "%1u Heros", killheros);
	else
		sprintf(textline,  "%1u Hero", killheros);
	tkDrawStr(strokeBase, textline);
    glPopMatrix();
	}

    if (detail != -1)
	glEnable(GL_DEPTH_TEST);

    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
    glLineWidth(2.01);

    if (killfighters > 0)
	{
	glPushMatrix();
	    glTranslatef(-0.65,  -.3,  7.1);
	    glRotatef(.1*angle + 180, 0, 1, 0);
	    glScalef(.6,  .6,  .6);
	    drawFighter();
	glPopMatrix();
	}

    if (killtanks > 0)
	{
	glPushMatrix();
	    glTranslatef(-.65,  -.1,  7.1);
	    glRotatef(.1*angle + 270, 0, 1, 0);
	    glScalef(0.33,  0.33,  0.33);
	    glCallList(plaintank);
	glPopMatrix();
	}

    if (killlaunchers > 0)
	{
	glPushMatrix();
	    glTranslatef(.5,  -.35,  7.1);
	    glRotatef(.1*angle + 270, 0, 1, 0);
	    glScalef(0.33,  0.33,  0.33);
	    glCallList(launchertank);
	glPopMatrix();
	}
 	
    if (killmtanks > 0)
	{
	glPushMatrix();
	    glTranslatef(-0.1,  -.42,  7.1);
	    glRotatef(.1*angle + 45, 0, 1, 0);
	    glScalef(0.05,  0.05,  0.05);
	    glCallList(masertank);
	glPopMatrix();
	}
 
    if (killhelos > 0)
	{
	glPushMatrix();
	    glTranslatef(.65,  0,  7.1);
	    glRotatef(.1*angle + 180, 0, 1, 0);
	    glScalef(.3,  .3,  .3);
	    drawHelo((counter*9) % 360,  0);
	glPopMatrix();
	}

    if (killplanes > 0)
	{
	glPushMatrix();
	    glTranslatef(0,  0,  7.1);
	    glRotatef(.1*angle, 0, 1, 0);
	    glScalef(.75,  .75,  .75);
	    drawAirplane((counter*2) % 360);
	glPopMatrix();
	}

    if (killmechags > 0)
	{
	glPushMatrix();
	    glTranslatef(0.6,  -.6,  7.1);
	    glRotatef(.1*angle + 90, 0, 1, 0);
	    glScalef(.25,  .25,  .25);
	    drawMechaMonster(50, counter, detail);
	glPopMatrix();
	}

    if (killCHHs > 0)
	{
	glPushMatrix();
	    glTranslatef(-0.1,  -.8,  7.1);
	    glRotatef(.1*angle + 180, 0, 1, 0);
	    glScalef(.3,  .3,  .3);
	    makeCHH(20);
	glPopMatrix();
	}

    if (killheros > 0)
	{
	glPushMatrix();
	    glTranslatef(-.6,  -.61,  7.1);
	    glRotatef(.1*angle + 180, 0, 1, 0);
	    glScalef(.25,  .25,  .25);
	    drawHeroDude2(100, counter, 0, 0, detail);
	glPopMatrix();
	}

    glPopAttrib();

    glLineWidth(lineWidthNow);
    }
