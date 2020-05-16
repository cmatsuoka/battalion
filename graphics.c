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
/* graphics.c v 1.3                                                    */
/* high level graphics routines for battalion                          */
/***********************************************************************/

#include "battalion.h"

    /*************/
    /* colours   */
    /*************/

    float colorolive[4]	    	= {0,    0.34,  0.0,  0.0};
    float planeGreen[4]	    	= {0.21, 0.49,  0.0,  0.0};
    float planeGreen2[4]    	= {0.25, 0.60,  0.0,  0.0}; 
    float planeGreen3[4]    	= {0.10, 0.25,  0.0,  0.0}; 
    float colorgreen[4]	    	= {0.0,  0.9,  0.1,  0.0};

    float colorblack[4]	    	= {0.2,  0.2,  0.2,  0.95};

    float colorred[4]	    	= {0.98, 0.17, 0.0,  0.7};
    float colorred_50[4]	= {0.49, 0.085, 0.0,  0.7}; /* colorred * 0.5 */
    float colorred2[4]	    	= {1.0,  0.0,  0.0,  0.0};
    float colorred3[4]	   	= {0.5,  0.08, 0.0,  0.7};

    float colormaserblue[4] 	= {0.3,  0.7,  1.0,  0.75};
    float colormaserblue2[4]	= {0.0,  1.0,  1.0,  0.75};

    float colorwhite[4]	    	= {1.0,  1.0,  1.0,  0.2};
    float colorwhite2[4]    	= {1.0,  1.0,  1.0,  0.4}; /* dying vapour */

    float colorsnow[4]	    	= {0.8,  0.8,  0.9,  0.4};
    float colorsnow2[4]	    	= {0.7,  0.7,  0.8,  0.4};

    float colorgrey1[4]	    	= {0.5,  0.5,  0.5,  0.8};
    float colorgrey1_50[4]	= {0.25, 0.25, 0.25, 0.4}; /* colorgrey * 0.5 */
    float colorgrey2[4]	    	= {0.7,  0.7,  0.7,  0.0};
    float colorgrey3[4]	    	= {0.6,  0.6,  0.6,  0.0};
    float colorgrey3_50[4]    	= {0.3,  0.3,  0.3,  0.0}; /* colorgrey3 * 0.5 */
    float colorgrey4[4]	    	= {0.55, 0.55, 0.55, 0.0};

    float colorbrown[4]	    	= {0.75, 0.33, 0.0,  0.8};
    float colorbeige[4]	    	= {0.75, 0.75, 0.5,  0.7};

    float colorblue[4]	    	= {0.0,  0.0,  1.0,  0.6};
    float colorblue2[4]	    	= {0.0,  0.0,  0.7,  0.0};
    float colorwater[4]	    	= {0.0,  0.25, 0.5,  0.0};

    float colorsnowvapour[4]	= {0.3,  0.3,  1.0,  0.4};

    float coloryellow[4]    	= {1.0,  1.0,  0.0,  0.0};
    float colormaseryellow[4]	= {1.0,  0.7,  0.0,  0.0};
    float colororange[4]    	= {1.0,  0.7,  0.0,  0.0};

    float healthGreen[4]    	= {0.21, 0.49, 0.0,  0.0}; 

    float treeColor[4] 		= {0.03, 0.34, 0.025, 0};
    float treeColor2[4] 	= {0.05, 0.4,  0.025, 0};
    
    /*************/
    /* objects   */
    /*************/

    GLuint 
	plaintank, slagtank, masertank, slagmasertank,  
	launchertank, slaglaunchertank, helo, slagHelo, 
	bigRotor, smallRotor, propeller,  

	airplaneBody, fighterBody,  
    
	monsterleg, monsterHead,
	monsterTail, monsterBody,
	monsterSimpleHead, monsterSimpleTail, 
	flutterHead,  

	techsBody, techsHead, techsShadow, 
	techsSimpleBody, techsSimpleHead, 
	
	watershellObj, heroshellObj,  

	tankShadow, planeShadow, fighterShadow, 

	flutterShadow, flutterBody, flutterXMas, 
	flutterWing1, flutterWing2, 

	planeDotsObj, planeDotsObjD0,
    
	shellObj, shell2Obj, 
 
	titleObj, titleObjOO, titleObjOOO, 
	lowDPlane, highDPlane, bigPlane, 
		
	roundTreeShadow,   

	boom1Obj, boom2Obj, boom3Obj, boom4Obj, boom5Obj, 
	boom6Obj, boom7Obj, boom8Obj, boom9Obj, boom10Obj, 

	boom1ObjD0, boom2ObjD0, boom3ObjD0, boom4ObjD0, boom5ObjD0, 
	boom6ObjD0, boom7ObjD0, boom8ObjD0, boom9ObjD0, boom10ObjD0, 
	
	strip1Obj, strip2Obj, strip3Obj, 
	strip1ObjD0, strip2ObjD0, strip3ObjD0, 
    
	powerTower,
	genericWindows, 
 
	building1Obj, building2Obj, building7Obj, building9Obj,  building9ObjOO,  
	building10Obj, building12Obj, building14Obj, building19Obj,  
	building20Obj, building21Obj, building31Obj, building32Obj,  
	building5Obj,
	building1ObjD0, building2ObjD0, building5ObjD0, building12ObjD0,
	building19ObjD0, building20ObjD0, building21ObjD0;

    /***************************/
    /* texture mapping stuff   */
    /***************************/

    GLuint leftScreen, rightScreen;
    GLuint treeWood, roadtex, officeLogo;

    char picleft[32400], picright[32400]; /* 180 x 180 tmap arrays*/
					  /* only 128 x 128 in use now */
    char officeLogoData[32400];
    		  
    char treeWoodData[5000];
    char roadtexData[5000];
    

    struct road roadsOnPlane[MAXROADSONPLANE];

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void doTexStuff(char * dataPath, char * fileName, int width, int height,
		char * TheArray, GLuint * theObj, int interpolation, int repeat)
    {
    register int x, y;
    char fullPath[MAXPATH];
    int arrayLoc;
    FILE * imageFile;

    strcpy(fullPath, dataPath);
    strcat(fullPath, fileName);
    imageFile = fopen(fullPath, "r");
	
    if (imageFile == NULL) 
	showError("Cannot find texture file in data directory");
    else
	{	    
	for (y = 0; y < height; y++)
	    for (x = 0; x < width; x++)
		    {
		    arrayLoc = (height-1-y) * width + (width-1-x);
		    TheArray[arrayLoc]	= (char) fgetc(imageFile);
		    }
		    
	*theObj = glGenLists(1);		    
	glNewList(*theObj, GL_COMPILE);
	
	    glTexImage2D(GL_TEXTURE_2D, 0, 1, width, height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, (const GLvoid *) TheArray);

	    if (repeat)
		{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
	    else
		{		    
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		}
	    
	    if (interpolation)
		{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
	    else
		{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
	    
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEndList();
	
	fclose(imageFile);
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create the objects to be used in the game                     */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makeObjects(char * dataPath)
    {
    GLfloat lineWidthNow;

    /********************/
    /* load in textures */
    /********************/

    doTexStuff(dataPath, "TEXTURES/screenleft.tex", 128, 128, picleft, &leftScreen, 0, 0);
    doTexStuff(dataPath, "TEXTURES/screenright.tex", 128, 128, picright, &rightScreen, 0, 0);

    doTexStuff(dataPath, "TEXTURES/treewood.tex", 64, 64, treeWoodData, &treeWood, 1, 0);
    doTexStuff(dataPath, "TEXTURES/road.tex", 64, 64, roadtexData, &roadtex, 1, 0);

/*     doTexStuff(dataPath,"TEXTURES/logo.tex", 128, 128, officeLogoData, &officeLogo, 0, 0);
*/

    /********************/
    /* make the objects */
    /********************/

    plaintank		= makeTank();
    slagtank		= makeSlagTank();
    masertank		= makeMaserTank();
    slagmasertank	= makeSlagMaserTank();
    launchertank	= makeLauncherTank();
    slaglaunchertank	= makeSlagLauncherTank();
    helo		= makeHelo();
    slagHelo		= makeSlagHelo();
    bigRotor		= makeBigRotor();
    smallRotor		= makeSmallRotor();
    propeller		= makePropeller();
    
    monsterleg		= makeLeg();
    monsterHead		= makeHead();
    monsterSimpleHead	= makeSimpleHead();
    monsterSimpleTail	= makeSimpleTail();
    monsterTail		= makeTail();
    monsterBody		= makeBody();
    flutterHead		= makeFlutterHead();
    techsBody		= makeTechsBody();
    techsHead		= makeTechsHead();
    techsSimpleBody	= makeTechsSimpleBody();
    techsSimpleHead	= makeTechsSimpleHead();
    techsShadow		= makeTechsShadow();

    tankShadow		= makeTankShadow();
    planeShadow		= makePlaneShadow();
    fighterShadow	= makeFighterShadow();
 
    shellObj		= glGenLists(1);     
    shell2Obj		= makeshell2();
    heroshellObj	= makeHeroShell();
    watershellObj	= makeWaterShell();

    titleObj		= makeTitles(1);
    titleObjOO		= makeTitles(0);
    titleObjOOO		= makeTitles(-1);
    
    planeDotsObj	= makePlaneDots(1);
    planeDotsObjD0	= makePlaneDots(0);

    powerTower		= makePowerTower(); 
    genericWindows	= makeGenericWindows(); 

    strip1Obj		= makeStrip1(1);
    strip2Obj		= makeStrip2(1);
    strip3Obj		= makeStrip3(1);
    strip1ObjD0		= makeStrip1(0);
    strip2ObjD0		= makeStrip2(0);
    strip3ObjD0		= makeStrip3(0);

    building1Obj	= makebuilding1(1); 
    building1ObjD0	= makebuilding1(0); 
    building2Obj	= makebuilding2(1);
    building2ObjD0	= makebuilding2(0);
    building5Obj	= makebuilding5(1);
    building5ObjD0	= makebuilding5(0);
    building7Obj	= makebuilding7();
    building9Obj	= makebuilding9(0);
    building9ObjOO	= makebuilding9(1);
    
    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
    building10Obj	= makebuilding10();
    glLineWidth(lineWidthNow);
    
    building12Obj	= makebuilding12(1);
    building12ObjD0	= makebuilding12(0);
    building14Obj	= makebuilding14();
    building19Obj	= makebuilding19(1);
    building19ObjD0	= makebuilding19(0);
    building20Obj	= makebuilding20(1);
    building20ObjD0	= makebuilding20(0);
    building21Obj	= makebuilding21(1);
    building21ObjD0	= makebuilding21(0);
    building31Obj	= makebuilding31();
    building32Obj	= makebuilding32();

    lowDPlane		= makeLowDPlane();
    highDPlane		= makeHighDPlane();
    bigPlane		= makeBigPlane();

    airplaneBody	= makeAirplaneBody();
    fighterBody		= makeFighterBody();
    flutterShadow	= makeFlutterShadow();
    flutterXMas		= makeFlutterXMas();
    flutterBody		= makeFlutterBody();
    flutterWing1	= makeFlutterWing1();
    flutterWing2	= makeFlutterWing2();

    roundTreeShadow	= makeRoundTreeShadow();

    makeBooms();

    initFonts();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a rectangular shadow on the ground                       */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void shadow (float x, float z, float wx, float wz)
    {
    float v[3];
    v[1] = SHADOWS;

    glBegin(GL_QUADS);
	v[0] = x+wx; v[2] = z+wz;
	glVertex3fv(v);

	v[2] = z-wz;
	glVertex3fv(v);

	v[0] = x-wx;
	glVertex3fv(v);

	v[2] = z+wz;
	glVertex3fv(v);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a  hunter                                                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makeCHH(int dam)
    {
    if (dam > 16)
	makercube(-0.15, -0.05, -0.2, 0.07, 0.07, 0.1, colorblue);
    else
	makeitd(0, colorblue,  -0.15, -0.05, -0.2, 0.07, 0.07, 0.1);

    if (dam > 12)
	makercube(0.15, -0.05, -0.2, 0.07, 0.07, .1, colorblue);
    else
	makeitd(1, colorblue, 0.15, -0.05, -0.2, 0.07, 0.07, .1);

    if (dam > 8)
	makercube(0.0, -0.05, 0.1, 0.2, 0.05, 0.1, colorgrey1);
    else
	makeitd(0, colorgrey1,  0.0, -0.05, 0.1, 0.2, 0.05, 0.1);

    if (dam > 4)
	makercube(0.0, -0.05, -0.2, 0.1, 0.05, 0.2, colorgrey1);
    else
	makeitd(1, colorgrey1,  0.0, -0.05, -0.2, 0.1, 0.05, 0.2);

    if (dam > 0)
	makeitPyr(3, colorgrey2,  0.0, +0.05, 0.1, 0.2, 0.05, 0.1);
    else
	makeitPyr(3, colorgrey1,  0.0, +0.05, 0.1, 0.2, 0.05, 0.1);

    makercube( 0.05, -0.1,  0.15, 0.02, 0.01, 0.02, colorwhite);
    makercube(-0.05, -0.1,  0.15, 0.02, 0.01, 0.02, colorwhite);
    makercube( 0.05, -0.1, -0.35, 0.02, 0.01, 0.02, colorwhite);
    makercube(-0.05, -0.1, -0.35, 0.02, 0.01, 0.02, colorwhite);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a helicopter                                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHelo(float percent,  int slag)
    {
    GLint shadeNow;
    
    glGetIntegerv(GL_SHADE_MODEL, &shadeNow);
    
    /*************/
    /* draw body */
    /*************/

    glShadeModel(GL_FLAT);

    if (!slag)
	glCallList(helo);
    else
	glCallList(slagHelo);
	
    glShadeModel(shadeNow);

    /***************/
    /* draw rotors */
    /***************/

    glPushMatrix();
	glRotatef(-percent, 0, 1, 0);
	glCallList(bigRotor);	
    glPopMatrix();

    /********************/
    /* draw tail rotor  */
    /********************/

    glPushMatrix();
	glTranslatef(0.04,  0,  0.375);
	glRotatef( -percent, 1, 0, 0);
	glCallList(smallRotor);
    glPopMatrix();
	}

    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a bomber                                                 */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawAirplane(int counter)
    {
    float percent;

    percent = counter * 10.0;

    glCallList(airplaneBody);
    
    /*******************/
    /* draw propellers */
    /*******************/

    glPushMatrix();
	glTranslatef(-0.09,  -0.014,  -0.07);
	glRotatef( -percent, 0, 0, 1);
	glCallList(propeller);	
    glPopMatrix();

    glPushMatrix();
	glTranslatef(+0.09,  -0.014,  -0.07);
	glRotatef( -percent, 0, 0, 1);
	glCallList(propeller);	
    glPopMatrix();

    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a fighter                                                 */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawFighter(void)
    {
    glCallList(fighterBody);    
    }
	


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw Googelon                                                 */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawMonster(struct monsterInfo monster, int counter,
		int itsChristmas, int detail)
    {    
    float v[4];

    /*********************/
    /* googelon's shadow */
    /*********************/

static    float googShadow1[3] = {0.1, SHADOWS, -0.5};
static    float googShadow2[3] = {0.0, SHADOWS, -0.7};
static    float googShadow3[3] = {-0.1, SHADOWS, -0.5};

    glPushMatrix();

	glRotatef(.1*monster.headHorzRotate, 0, 1, 0);

	/********/
	/* head */
	/********/

	glPushMatrix();
	    glRotatef(.1*monster.headVertRotate, 1, 0, 0);

	    glCallList(monsterHead);
	    	    
	    if (itsChristmas)
		{
		glPushMatrix();
		    glScalef(1.2,  .5,  1.2);
		    glTranslatef(0.0,  PLANEY+1.7,  0.0);
			glColor3fv(colorwhite);
			v[0] = v[1] = v[2] = 0;
			v[3] = .14;
			andysphdraw(v, 4);
		glPopMatrix();
		glPushMatrix();
		    glTranslatef(-0.15,  PLANEY+1.55,  -0.15);
		    glScalef(0.15,  0.2,  0.15);
		    drawClosedCone(colorred, colorred, 1);
		glPopMatrix();

		glPushMatrix();
		    glTranslatef(-0.09,  PLANEY+1.75,  0.04);
		    glRotatef(.1*(1100), 1, 0, 0);
		    glRotatef(.1*(450), 0, 0, 1);
		    glScalef(.04,  .11,  .1);
		    drawClosedCone(colorred, colorred, 1);
		glPopMatrix();

		glColor3fv(colorwhite);
		v[0] = -0.15;
		v[1] = PLANEY+1.6;
		v[2] = 0.1;
		v[3] = 0.05;
		andysphdraw(v, 4);
		}
	    
	glPopMatrix();   

	/********/
	/* body */
	/********/

	glCallList(monsterBody);
    
	/***********************/
	/* legs, feet and toes */
	/***********************/

	glPushMatrix();
	    glTranslatef(0.2,  monster.rot1,  monster.rot2);
	    glCallList(monsterleg);
	    glTranslatef(-0.4,   -2*monster.rot1,  -2*monster.rot2);
	    glCallList(monsterleg);
	glPopMatrix();

	if ((!monster.monsterIsDead) && (detail > 0))
	      {
	      glColor4fv(colorblack);
	      
	      shadow (0.0,   0.0,          0.2, 0.2);
	      shadow (0.2,   monster.rot2, 0.1, 0.15);
	      shadow (-0.2, -monster.rot2, 0.1, 0.15);
	      }

	/********/
	/* tail */
	/********/
    
	    glRotatef(sin(counter * 0.15915)*10, 0, 1, 0); /* 1/(2 * pi) */

	    glCallList(monsterTail);

	    if (itsChristmas)
		{
 		glPushMatrix();
		    glTranslatef(-0.15,  PLANEY+0.85,  -0.45);
		    glScalef(0.15,  0.15,  0.15);
		    drawClosedCone(colorbeige, colorbrown, 1);
		glPopMatrix();
   
		glPushMatrix();
		    glTranslatef(0.0,  PLANEY+0.5,  -0.3);
		    glScalef(1,  1.5,  1);
		    glColor3fv(colorbeige);
		    v[0] = v[1] = v[2] = 0;
		    v[3] = 0.2;
		    andysphdraw(v, 4);
		glPopMatrix();
		}

	    if ((!monster.monsterIsDead) && (detail > 0))
		{
		glColor4fv(colorblack);
		
		shadow (0.0,  -0.25,  0.1,  0.25);

		glColor3fv(colorblack);

		glBegin(GL_TRIANGLES);
		    glVertex3fv(googShadow1);
		    glVertex3fv(googShadow2);
		    glVertex3fv(googShadow3);
		glEnd();
		}

    glPopMatrix();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw SIMPLIFIED Googelon (to save time in monsterview)        */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawSimpleMonster(struct monsterInfo monster, int counter,
		int itsChristmas, int detail)
    {    
    float v[4];

    /*********************/
    /* googelon's shadow */
    /*********************/

    glPushMatrix();

	glRotatef(.1*monster.headHorzRotate, 0, 1, 0);

	/********/
	/* head */
	/********/

	glPushMatrix();
	    glRotatef(.1*monster.headVertRotate, 1, 0, 0);

	    glCallList(monsterSimpleHead);
	    	    
	    if (itsChristmas)
		{
		glPushMatrix();
		    glScalef(1.2,  .5,  1.2);
		    glTranslatef(0.0,  PLANEY+1.7,  0.0);
			glColor3fv(colorwhite);
			v[0] = v[1] = v[2] = 0;
			v[3] = .14;
			andysphdraw(v, 4);
		glPopMatrix();
		glPushMatrix();
		    glTranslatef(-0.15,  PLANEY+1.55,  -0.15);
		    glScalef(0.15,  0.2,  0.15);
		    drawClosedCone(colorred, colorred, 1);
		glPopMatrix();

		glPushMatrix();
		    glTranslatef(-0.09,  PLANEY+1.75,  0.04);
		    glRotatef(.1*(1100), 1, 0, 0);
		    glRotatef(.1*(450), 0, 0, 1);
		    glScalef(.04,  .11,  .1);
		    drawClosedCone(colorred, colorred, 1);
		glPopMatrix();

		glColor3fv(colorwhite);
		v[0] = -0.15;
		v[1] = PLANEY+1.6;
		v[2] = 0.1;
		v[3] = 0.05;
		andysphdraw(v, 4);
		}
	    
	glPopMatrix();   

	/********/
	/* body */
	/********/

	makercubeTopBack(0.0, PLANEY+0.5, 0.0,  0.2,  0.3, 0.2,  colorred);
	makercubeTopBack(0.0, PLANEY+0.9, 0.0,  0.15, 0.2, 0.15, colorred);
    
	/***********************/
	/* legs, feet and toes */
	/***********************/

	glPushMatrix();
	    glTranslatef(0.2,  monster.rot1,  monster.rot2);

	    makercubeTopBack( 0.0,   PLANEY+0.2,  0.0,   0.1,  0.2,  0.1,  colorred);
	    makercubeTopBack( 0.0,   PLANEY+0.06, 0.17,  0.1,  0.06, 0.08, colorred);

	    glTranslatef(-0.4,   -2*monster.rot1,  -2*monster.rot2);

	    makercubeTopBack( 0.0,   PLANEY+0.2,  0.0,   0.1,  0.2,  0.1,  colorred);
	    makercubeTopBack( 0.0,   PLANEY+0.06, 0.17,  0.1,  0.06, 0.08, colorred);

	glPopMatrix();

	if ((!monster.monsterIsDead) && (detail > 0))
	      {
	      glColor4fv(colorblack);
	      
	      shadow (0.0,   0.0,          0.2, 0.2);
	      shadow (0.2,   monster.rot2, 0.1, 0.15);
	      shadow (-0.2, -monster.rot2, 0.1, 0.15);
	      }

	    /********/
	    /* tail */
	    /********/
    
	    glRotatef(sin(counter * 0.15915)*10, 0, 1, 0); /* 1/(2 * pi) */

	    glCallList(monsterSimpleTail);

	    if (itsChristmas)
		{
 		glPushMatrix();
		    glTranslatef(-0.15,  PLANEY+0.85,  -0.45);
		    glScalef(0.15,  0.15,  0.15);
		    drawClosedCone(colorbeige, colorbrown, 1);
		glPopMatrix();
   
		glPushMatrix();
		    glTranslatef(0.0,  PLANEY+0.5,  -0.3);
		    glScalef(1,  1.5,  1);
		    glColor3fv(colorbeige);
		    v[0] = v[1] = v[2] = 0;
		    v[3] = 0.2;
		    andysphdraw(v, 4);
		glPopMatrix();
		}


    glPopMatrix();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* Draw the Vapour                                               */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawVapour(struct monsterInfo monster, int itsChristmas, int detail)
    {
    register int i;
    glPushMatrix();

    if (detail > 0)
	glEnable(GL_BLEND);
	
    glRotatef(0.1 * monster.headHorzRotate, 0, 1, 0);

    colorwhite2[0] = 1;
    colorwhite2[1] = 1;
    colorwhite2[2] = 1;

    if (monster.monsterIsDead)
	{
	if (detail == -1)
	    {
	    colorwhite2[0] = 1 - monster.deadCount * 0.022;
	    colorwhite2[1] = 1 - monster.deadCount * 0.022;
	    colorwhite2[2] = 1 - monster.deadCount * 0.022;
	    }

	colorwhite2[3] = 1 - monster.deadCount * 0.022;
	glColor4fv(colorwhite2);
	}
    else if (itsChristmas)
	glColor4fv(colorsnowvapour);
    else
	glColor4fv(colorwhite); 

    if (detail == 0)
	for(i = 0; i < (int) (MAXTRIBUTES/1.5); i++)
	    andysphdraw(monster.a[i], 0);
    else
	for(i=0; i<MAXTRIBUTES; i++)
	    andysphdraw(monster.a[i], 0);

    glDisable(GL_BLEND);

    glPopMatrix();
    } 


   
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw Flutter                                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawFlutter(struct monsterInfo monster, int counter,
		int itsChristmas, float offsetX, int thaView, int detail)
    {
    float rotAmt;
    
    rotAmt = sin(counter * 0.3183) * 15;
    

    glPushMatrix();
	glRotatef(0.1 * monster.headHorzRotate, 0, 1, 0);

	/* shadow */

	if (!monster.monsterIsDead)
	    {
	    glPushAttrib(GL_DEPTH_BUFFER_BIT);
	    glPushAttrib(GL_COLOR_BUFFER_BIT);
	    
	    if (thaView == MONSTERVIEW)
		{
		if (detail > 0)	
		    glEnable(GL_BLEND);		    
		glDisable(GL_DEPTH_TEST);
		}
    
	    glCallList(flutterShadow); 
		
	    glPopAttrib();
	    glPopAttrib();
	    }

   
 
	glPushMatrix();
	    glRotatef(offsetX * 10, 0, 0, 1);

	    if (itsChristmas)
		glCallList(flutterXMas);		
		
	    glPushMatrix();
		glRotatef(monster.headVertRotate * 0.05, 1, 0, 0);

		glCallList(flutterHead);
	    glPopMatrix();

	    glCallList(flutterBody);
    
	    glTranslatef(0, PLANEY+1.15, 0);

	    glPushMatrix();
		glRotatef(  rotAmt, 0, 0, 1); /* 1/(2 * pi) */
		glCallList(flutterWing1);
	    glPopMatrix();
	    
	    glPushMatrix();
		glRotatef( - rotAmt, 0, 0, 1); /* 1/(2 * pi) */
		glCallList(flutterWing2);
	    glPopMatrix();

	    
	glPopMatrix();
	
    glPopMatrix();

    } 



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw Techs                                                    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawTechs(struct monsterInfo monster, int detail)
    {
    glPushMatrix();

    glRotatef(0.1 * monster.headHorzRotate, 0, 1, 0);
 
    if (monster.deadCount < 45)
	{    
	glPushMatrix();
	    glRotatef(0.1 * monster.headVertRotate, 1, 0, 0);
	    glCallList(techsHead);    
	glPopMatrix();   

	glCallList(techsBody);
	}
    
    if ((!monster.monsterIsDead) && (detail > 0))
	{
	glCallList(techsShadow);
	}
	
    glPopMatrix();
		    
    if (monster.deadCount >= 45)
	{
	glPushMatrix();
	    glTranslatef(monster.timeDead * 0.05 + 0.2,  -monster.timeDead * 0.05,   monster.timeDead * 0.05);
	    glRotatef(monster.timeDead*10, 1, 0, 0);
	    glRotatef(monster.timeDead*15, 0, 1, 0);
	    makercube(0.0,    0, 0, 0.03, 0.25, 0.2, colorgrey2);
	    makercube(0.011,  0, 0, 0.02, 0.2, 0.15, colorblack);
	glPopMatrix();

	glPushMatrix();
	    glTranslatef(-monster.timeDead * 0.05 - 0.2,  monster.timeDead * 0.05,   monster.timeDead * 0.05);
	    glRotatef(monster.timeDead*10, 1, 0, 0);
	    glRotatef(monster.timeDead*15, 0, 1, 0);
	    makercube( 0.0,   0, 0, 0.03, 0.25, 0.2, colorgrey2);
	    makercube(-0.011, 0, 0, 0.02, 0.2, 0.15, colorblack);
	glPopMatrix();
	}
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw SIMPLE Techs                                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawSimpleTechs(struct monsterInfo monster, int detail)
    {
    glPushMatrix();

    glRotatef(0.1 * monster.headHorzRotate, 0, 1, 0);
 
    if (monster.deadCount < 45)
	{    
	glPushMatrix();
	    glRotatef(0.1 * monster.headVertRotate, 1, 0, 0);
	    glCallList(techsSimpleHead);    
	glPopMatrix();   

	glCallList(techsSimpleBody);
	}
    
    if ((!monster.monsterIsDead) && (detail > 0))
	{
	glCallList(techsShadow);
	}
	
    glPopMatrix();
		    
    }

  
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw the energy typhoon hero                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHeroDude(int power, int counter,
		int mcount, int dCount, int detail)
    {
    float spheredat[4];
    int ang;
    int amount, amount2;
    float dam;
    float c1[4], c2[4], c3[4], c4[4], c5[4];
    int sph;
    
    if (detail >= 2)
	sph = 4;
    else
	sph = 3;

    c1[3] = c2[3] = c3[3] = c4[3] = c5[3] = 1;
    dam = dCount * 0.075;
    
    c2[0] = (colorwhite[0] + dam) >= 1 ? 1 : (colorwhite[0] + dam);
    c2[1] = (colorwhite[1] + dam) >= 1 ? 1 : (colorwhite[1] + dam);
    c2[2] = (colorwhite[2] + dam) >= 1 ? 1 : (colorwhite[2] + dam);
    
    c1[0] = (colorwater[0] + dam) >= 1 ? 1 : (colorwater[0] + dam);
    c1[1] = (colorwater[1] + dam) >= 1 ? 1 : (colorwater[1] + dam);
    c1[2] = (colorwater[2] + dam) >= 1 ? 1 : (colorwater[2] + dam);

    c3[0] = (colorblack[0] + dam) >= 1 ? 1 : (colorblack[0] + dam);
    c3[1] = (colorblack[1] + dam) >= 1 ? 1 : (colorblack[1] + dam);
    c3[2] = (colorblack[2] + dam) >= 1 ? 1 : (colorblack[2] + dam);

    c4[0] = (colorgrey2[0] + dam) >= 1 ? 1 : (colorgrey2[0] + dam);
    c4[1] = (colorgrey2[1] + dam) >= 1 ? 1 : (colorgrey2[1] + dam);
    c4[2] = (colorgrey2[2] + dam) >= 1 ? 1 : (colorgrey2[2] + dam);

    c5[0] = (colorwater[0] + dam) >= 1 ? 1 : (colorwater[0] + dam);
    c5[1] = (colorwater[1] + dam) >= 1 ? 1 : (colorwater[1] + dam);
    c5[2] = (colorwater[2] + dam) >= 1 ? 1 : (colorwater[2] + dam);

    /********/
    /* head */
    /********/
    
    glPushMatrix();
	    glScalef(0.55,  1,  0.55);  
	    glColor4fv(c4);
	    spheredat[0] = 0;
	    spheredat[1] = PLANEY+1.21;
	    spheredat[2] = 0;
	    spheredat[3] = 0.12;
	    andysphdraw(spheredat, sph);
	    
	    if (power > 8)
		makercube(.06, PLANEY+1.25, .075,  0.03, 0.015, 0.035, c3);
	    else
		makeitd(1, c3, .06, PLANEY+1.25, .075,  0.03, 0.015, 0.035);

	    if (power > 5)	    
		makercube(-.06, PLANEY+1.25, .075,  0.03, 0.015, 0.035, c3);
	    else
		makeitd(0, c3, -.06, PLANEY+1.25, .075,  0.03, 0.015, 0.035);
		
	    if (power > 3)
		makercube(0, PLANEY+1.16, .075,  0.03, 0.014, 0.035, c4);
	    else
		makeitd(1,  c4, 0, PLANEY+1.16, .075,  0.03, 0.014, 0.035);
	    glColor4fv(c5);
	    spheredat[2] = -0.01;
	    andysphdraw(spheredat, sph);
    glPopMatrix();


    /********/
    /* neck */
    /********/
    
    if (power > 10)
	makercube(0, PLANEY+1.075, 0,  0.025, 0.025, 0.025, c2);
    else
	makeitd(1, c2, 0, PLANEY+1.075, 0,  0.025, 0.025, 0.025);
   
    /********/
    /* body */
    /********/
   
    if (power > 15)
	makercube(0, PLANEY+0.95, 0,  0.075, 0.1, 0.055, c1);
    else
	makeitd(0, c1, 0, PLANEY+0.95, 0,  0.075, 0.1, 0.055);
	
    if (power > 20)
	makercube(0, PLANEY+0.75, 0,  0.075, 0.1, 0.055, c2);
    else
	makeitd(0, c2, 0, PLANEY+0.75, 0,  0.075, 0.1, 0.055);
	
    if (power > 25)
	makercube(0, PLANEY+1.01, 0.055,  0.02, 0.05, 0.01, c2);
    else
	makeitd(1, c2, 0, PLANEY+1.01, 0.055,  0.02, 0.05, 0.01);

    /*************/
    /* shoulders */
    /*************/

    if (power > 30)
	makercube(0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05, c2);
    else
	makeitd(0, c2, 0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05);
	
    if (power > 35)
	makercube(-0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05, c2);
    else
	makeitd(1, c2, -0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05);

    /********/
    /* arms */
    /********/

    if (mcount > 30)
	amount = (40 - mcount) * 9;
    else if (mcount > 10)
	amount = 90;
    else
	amount = mcount * 9;
    
    ang = (int) amount * 10;

    glPushMatrix();
	glRotatef(.1*(-ang), 1, 0, 0);

	if (power > 40)
	    makercube(0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025, c1);
	else
	    makeitd(1, c1, 0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025);

	glPushMatrix();
	    glTranslatef(0.13,  PLANEY+0.75,  0);
	
	    if (power > 45)
		makercube(0, -0.09, 0,  0.024, 0.11, 0.024, c2);
	    else
		makeitd(0, c2, 0, -0.09, 0,  0.024, 0.11, 0.024);
	    
	    if (power > 50)
		makercube(0, -0.19, 0,  0.03, 0.03, 0.028, c1);
	    else
		makeitd(1, c1, 0, -0.19, 0,  0.03, 0.03, 0.028);
	glPopMatrix();
    glPopMatrix();
 
    glPushMatrix();
	glRotatef(.1*(-ang), 1, 0, 0);

	if (power > 55)
	    makercube(-0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025, c1);
	else
	    makeitd(0, c1, -0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025);
   
	glPushMatrix();
	    glTranslatef(-0.13,  PLANEY+0.75,  0);
	    
	    if (power > 60)
		makercube(0, -0.09, 0,  0.024, 0.11, 0.024, c2);
	    else
		makeitd(0, c2, 0, -0.09, 0,  0.024, 0.11, 0.024);
	    
	    if (power > 65)
		makercube(0, -0.19, 0,  0.03, 0.03, 0.028, c1);
	    else
		makeitd(1, c1, 0, -0.19, 0,  0.03, 0.03, 0.028);
	glPopMatrix();
    glPopMatrix();
    
    /********/
    /* legs */
    /********/

    amount = (counter * 100) % 2400;
    if (amount < 1200)
        amount2 = 300 + amount;
    else
        amount2 = 900 + amount;

    ang = (int) (cos(BIG_DEG_TO_RAD * amount2) * RAD_TO_SMALL_DEG * 2.5);

    glPushMatrix();
	glTranslatef(0.04,  PLANEY+0.65,  0);
	glRotatef(.1*(ang ), 1, 0, 0);
	
	if (power > 70)
	    makercube(0, -0.12, 0,  0.035, 0.13, 0.03, c2);
	else
	    makeitd(0, c2, 0, -0.12, 0,  0.035, 0.13, 0.03);
	    
	if (power > 75)	
	    makercube(0, -.35, 0,  0.024, 0.2, 0.029, c1);
	else
	    makeitd(1, c1, 0, -.35, 0,  0.024, 0.2, 0.029);
	    
	if (power > 80)
	    makercube(0, -.59, +0.025,  0.026, 0.04, 0.075, c2);
	else
	    makeitd(0, c2, 0, -.59, +0.025,  0.026, 0.04, 0.075);
    glPopMatrix();
    
    glPushMatrix();
	glTranslatef(-0.04,  PLANEY+0.65,  0);
	glRotatef(.1*(-ang), 1, 0, 0);
	
	if (power > 85)
	    makercube(0, -0.12, 0,  0.035, 0.13, 0.03, c2);
	else
	    makeitd(1, c2, 0, -0.12, 0,  0.035, 0.13, 0.03);
	    
	if (power > 90)
	    makercube(0, -.35, 0,  0.024, 0.2, 0.029, c1);
	else
	    makeitd(0, c1, 0, -.35, 0,  0.024, 0.2, 0.029);
	    
	if (power > 95)
	    makercube(0, -.59, +0.025,  0.026, 0.04, 0.075, c2);
	else
	    makeitd(1, c2, 0, -.59, +0.025,  0.026, 0.04, 0.075);
    glPopMatrix();
    
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw the energy beam hero                                     */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHeroDude2(int power, int counter,
		    int mcount, int dCount, int detail)
    {
    float spheredat[4];
    int ang;
    int amount, amount2;
    float dam;
    float c1[4], c2[4], c3[4], c4[4], c5[4];
    int sph;
    

    if (detail >= 2)
	sph=4;
    else
	sph=3 ;


    c1[3] = c2[3] = c3[3] = c4[3] = c5[3] = 1;
    dam = dCount * 0.075;

    c1[0] = (colorwhite[0] + dam) >= 1 ? 1 : (colorwhite[0] + dam);
    c1[1] = (colorwhite[1] + dam) >= 1 ? 1 : (colorwhite[1] + dam);
    c1[2] = (colorwhite[2] + dam) >= 1 ? 1 : (colorwhite[2] + dam);
    
    c2[0] = (colorred[0] + dam) >= 1 ? 1 : (colorred[0] + dam);
    c2[1] = (colorred[1] + dam) >= 1 ? 1 : (colorred[1] + dam);
    c2[2] = (colorred[2] + dam) >= 1 ? 1 : (colorred[2] + dam);

    c3[0] = (colorblack[0] + dam) >= 1 ? 1 : (colorblack[0] + dam);
    c3[1] = (colorblack[1] + dam) >= 1 ? 1 : (colorblack[1] + dam);
    c3[2] = (colorblack[2] + dam) >= 1 ? 1 : (colorblack[2] + dam);
 
    c4[0] = (colorgrey2[0] + dam) >= 1 ? 1 : (colorgrey2[0] + dam);
    c4[1] = (colorgrey2[1] + dam) >= 1 ? 1 : (colorgrey2[1] + dam);
    c4[2] = (colorgrey2[2] + dam) >= 1 ? 1 : (colorgrey2[2] + dam);

    c5[0] = (colorred3[0] + dam) >= 1 ? 1 : (colorred3[0] + dam);
    c5[1] = (colorred3[1] + dam) >= 1 ? 1 : (colorred3[1] + dam);
    c5[2] = (colorred3[2] + dam) >= 1 ? 1 : (colorred3[2] + dam);

    /********/
    /* head */
    /********/
    
    glPushMatrix();
	    glScalef(0.55, 1,   0.55);  
	    glColor4fv(c4);
	    spheredat[0] = 0;
	    spheredat[1] = PLANEY+1.21;
	    spheredat[2] = 0;
	    spheredat[3] = 0.12;
	    andysphdraw(spheredat, sph);
	    
	    if (power > 8)
		makercube(.06, PLANEY+1.25, .075,  0.03, 0.015, 0.035, c3);
	    else
		makeitd(1, c3, .06, PLANEY+1.25, .075,  0.03, 0.015, 0.035);

	    if (power > 5)	    
		makercube(-.06, PLANEY+1.25, .075,  0.03, 0.015, 0.035, c3);
	    else
		makeitd(0, c3, -.06, PLANEY+1.25, .075,  0.03, 0.015, 0.035);
		
	    if (power > 3)
		makercube(0, PLANEY+1.16, .075,  0.03, 0.014, 0.035, c4);
	    else
		makeitd(1,  c4, 0, PLANEY+1.16, .075,  0.03, 0.014, 0.035);
	    glColor4fv(c5);
	    spheredat[2] = -0.01;
	    andysphdraw(spheredat, sph);
    glPopMatrix();

    /********/
    /* neck */
    /********/
    
    if (power > 10)
	makercube(0, PLANEY+1.075, 0,  0.025, 0.025, 0.025, c2);
    else
	makeitd(1, c2, 0, PLANEY+1.075, 0,  0.025, 0.025, 0.025);
   
    /********/
    /* body */
    /********/
   
    if (power > 15)
	makercube(0, PLANEY+0.95, 0,  0.075, 0.1, 0.055, c1);
    else
	makeitd(0, c1, 0, PLANEY+0.95, 0,  0.075, 0.1, 0.055);
	
    if (power > 20)
	makercube(0, PLANEY+0.75, 0,  0.075, 0.1, 0.055, c2);
    else
	makeitd(0, c2, 0, PLANEY+0.75, 0,  0.075, 0.1, 0.055);
	
    if (power > 25)
	makercube(0, PLANEY+1.01, 0.055,  0.02, 0.05, 0.01, c2);
    else
	makeitd(1, c2, 0, PLANEY+1.01, 0.055,  0.02, 0.05, 0.01);

    /*************/
    /* shoulders */
    /*************/

    if (power > 30)
	makercube(0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05, c2);
    else
	makeitd(0, c2, 0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05);
	
    if (power > 35)
	makercube(-0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05, c2);
    else
	makeitd(1, c2, -0.075, PLANEY+1.0, 0,  0.075, 0.051, 0.05);

    /********/
    /* arms */
    /********/

    if (mcount > 30)
	amount = (40 - mcount) * 9;
    else if (mcount > 10)
	amount = 90;
    else
	amount = mcount * 9;
    
    ang = (int) amount * 10;

    if (power > 40)
	makercube(0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025, c1);
    else
	makeitd(1, c1, 0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025);

    glPushMatrix();
	glTranslatef(0.13,  PLANEY+0.75,  0);
	
	if (power > 45)
	    makercube(0, -0.09, 0,  0.024, 0.11, 0.024, c2);
	else
	    makeitd(0, c2, 0, -0.09, 0,  0.024, 0.11, 0.024);
	    
	if (power > 50)
	    makercube(0, -0.19, 0,  0.03, 0.03, 0.028, c1);
	else
	    makeitd(1, c1, 0, -0.19, 0,  0.03, 0.03, 0.028);
    glPopMatrix();

 
    glPushMatrix();
	glRotatef(.1*(-ang/2 ), 1, 0, 0);

	if (power > 55)
	    makercube(-0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025, c1);
	else
	    makeitd(0, c1, -0.13, PLANEY+0.875, 0,  0.025, 0.125, 0.025);
   
	glPushMatrix();
	    glTranslatef(-0.13,  PLANEY+0.75,  0);
	    glRotatef(.1*(ang ), 0, 0, 1);
	    
	    if (power > 60)
		makercube(0, -0.09, 0,  0.024, 0.11, 0.024, c2);
	    else
		makeitd(0, c2, 0, -0.09, 0,  0.024, 0.11, 0.024);
	    
	    if (power > 65)
		makercube(0, -0.19, 0,  0.03, 0.03, 0.028, c1);
	    else
		makeitd(1, c1, 0, -0.19, 0,  0.03, 0.03, 0.028);
	glPopMatrix();
    glPopMatrix();
    
    /********/
    /* legs */
    /********/

    amount = (counter *100) % 2400;
    if (amount < 1200)
        amount2 = 300 + amount;
    else
        amount2 = 900 + amount;

    ang = (int) (cos(BIG_DEG_TO_RAD * amount2) * RAD_TO_SMALL_DEG * 2.5);

    glPushMatrix();
	glTranslatef(0.04,  PLANEY+0.65,  0);
	glRotatef(.1*(ang ), 1, 0, 0);
	
	if (power > 70)
	    makercube(0, -0.12, 0,  0.035, 0.13, 0.03, c2);
	else
	    makeitd(0, c2, 0, -0.12, 0,  0.035, 0.13, 0.03);
	    
	if (power > 75)	
	    makercube(0, -.35, 0,  0.024, 0.2, 0.029, c1);
	else
	    makeitd(1, c1, 0, -.35, 0,  0.024, 0.2, 0.029);
	    
	if (power > 80)
	    makercube(0, -.59, +0.025,  0.026, 0.04, 0.075, c2);
	else
	    makeitd(0, c2, 0, -.59, +0.025,  0.026, 0.04, 0.075);
    glPopMatrix();
    
    glPushMatrix();
	glTranslatef(-0.04,  PLANEY+0.65,  0);
	glRotatef(.1*(-ang), 1, 0, 0);
	
	if (power > 85)
	    makercube(0, -0.12, 0,  0.035, 0.13, 0.03, c2);
	else
	    makeitd(1, c2, 0, -0.12, 0,  0.035, 0.13, 0.03);
	    
	if (power > 90)
	    makercube(0, -.35, 0,  0.024, 0.2, 0.029, c1);
	else
	    makeitd(0, c1, 0, -.35, 0,  0.024, 0.2, 0.029);
	    
	if (power > 95)
	    makercube(0, -.59, +0.025,  0.026, 0.04, 0.075, c2);
	else
	    makeitd(1, c2, 0, -.59, +0.025,  0.026, 0.04, 0.075);
    glPopMatrix();
    
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw MechaGoogelon                                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


void drawMechaMonster(int dam, int counter, int detail)
    {
    if (dam > 48)
       makercube(0.2, PLANEY+0.7, 0,  0.05, 0.05, 0.15, colorblue);
    else
       makeitd(1, colorblue, 0.2, PLANEY+0.7, 0,  0.05, 0.05, 0.15);

    if (dam > 45)
       makercube(-0.2, PLANEY+0.7, 0,  0.05, 0.05, 0.15, colorblue);
    else
       makeitd(0, colorblue, -0.2, PLANEY+0.7, 0,  0.05, 0.05, 0.15);

    /**************************/
    /* legs, feet of one side */
    /**************************/

    if (dam > 43)
       makercube(0.2, PLANEY+0.2, 0,  0.12, 0.2, 0.1, colorgrey2);
    else
       makeitd(0, colorgrey2, 0.2, PLANEY+0.2, 0,  0.12, 0.2, 0.1);

    if (dam > 40)
       makercube(0.2, PLANEY+0.06, 0.1,  0.1, 0.06, 0.15, colorwhite);
    else
       makeitd(1, colorwhite, 0.2, PLANEY+0.06, 0.1,  0.1, 0.06, 0.15);

    /****************************/
    /* legs, feet of other side */
    /****************************/

    if (dam > 38)
       makercube(-0.2, PLANEY+0.2, 0,  0.12, 0.2, 0.1, colorgrey2);
    else
        makeitd(1, colorgrey2, -0.2, PLANEY+0.2, 0,  0.12, 0.2, 0.1);

    if (dam > 35)
        makercube(-0.2, PLANEY+0.06, 0.1,  0.1, 0.06, 0.15, colorwhite);
    else
        makeitd(0, colorwhite, -0.2, PLANEY+0.06, 0.1,  0.1, 0.06, 0.15);
  
    /********/
    /* tail */
    /********/

    if (dam > 30)
        {
        makercube(0, PLANEY+0.2, -0.2,  0.1, 0.15, 0.2, colorwhite);
        makercube(0, PLANEY+0.1, -0.4,  0.08, 0.1, 0.2, colorgrey2);
        }
    else
        {
        makeitd(0, colorwhite, 0, PLANEY+0.2, -0.2,  0.1, 0.15, 0.2);
        makeitd(1, colorgrey2, 0, PLANEY+0.1, -0.4,  0.08, 0.1, 0.2);
        }

    glColor4fv(colorblack);

    if (detail > 0)
	{    
	shadow (0,  -0.2,  0.1,  0.2);
	shadow (0,  -0.4,  0.08,  0.2);
	}
    
    /********/
    /* head */
    /********/

    if (dam > 26)
        makercube(0, PLANEY + 1.15, 0,  0.25, 0.15, 0.12, colorwhite);
    else
        makeitd(0, colorwhite, 0, PLANEY + 1.15, 0,  0.25, 0.15, 0.12);

    makeitPyr(2, colorwhite, 0, PLANEY + 1.15, -.24,  0.25, 0.15, 0.12);

    if (dam > 22)
        makercube(0, PLANEY + 1.15, -0.24,  0.13, 0.08, 0.1, colorgrey2);
    else
        makeitd(1, colorgrey2, 0, PLANEY + 1.15, -0.24,  0.13, 0.08, 0.1);

    /*******/
    /* eye */
    /*******/

    if (dam > 18)
        makercube(0, PLANEY + 1.20, 0.1, 0.15, 0.06, 0.05, colorblack);
    else
        makeitd(1, colorblack,  0, PLANEY + 1.20, 0.1, 0.15, 0.06, 0.05);

    if (dam > 14)
       makercube(sin((counter % 20) * 0.314) * 0.14, PLANEY + 1.20, 0.14,  0.04, 0.04, 0.04, colorred);
    else
       makeitd(0, colorred, sin((counter % 20) * 0.314) * 0.14, PLANEY + 1.20, 0.14,  0.04, 0.04, 0.04);

    /********/
    /* body */
    /********/

    if (dam > 10)
       makercube(0, PLANEY + 0.9, 0,  0.1, 0.2, 0.1, colorgrey2);
    else
       makeitd(0, colorgrey2, 0, PLANEY + 0.9, 0,  0.1, 0.2, 0.1);


    if (dam > 5)
       makercube(0, PLANEY + 0.5, 0.2, 0.1, 0.15, 0.05, colorgrey1);
    else
       makeitd(1, colorgrey1, 0, PLANEY + 0.5, 0.2, 0.1, 0.15, 0.05);


    if (dam > 0)
       makercube(0, PLANEY + 0.5, 0, 0.2, 0.3, 0.2, colorwhite);
    else
       makeitd(0, colorwhite, 0, PLANEY + 0.5, 0, 0.2, 0.3, 0.2);

    glColor4fv(colorblack);

    if (detail > 0)    
	shadow (0,  0,  0.2,  0.2);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a window on the negative z side of a building            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void wzminus(float x,  float y,  float z,  float wx,  float wy)
    {
    float v[3];

    v[2] = z;

    glBegin(GL_QUADS);
	v[0] = x-wx; v[1] = y-wy;   
	glVertex3fv(v);

	v[1] = y+wy;
	glVertex3fv(v);

	v[0] = x+wx;
	glVertex3fv(v);

	v[1] = y-wy;
	glVertex3fv(v);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a window on the positive z side of a building            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
   
void wzplus(float x,  float y,  float z,  float wx,  float wy)
    {
    float v[3];

    v[2] = z;

    glBegin(GL_QUADS);
	v[0] = x+wx; v[1] = y-wy;
	glVertex3fv(v);

	v[1] = y+wy;
	glVertex3fv(v);

	v[0] = x-wx;
	glVertex3fv(v);

	v[1] = y-wy;
	glVertex3fv(v);
    glEnd();
    }
 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a window on the positive x side of a building            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void wxplus(float x,  float y,  float z,  float wy,  float wz)
    {
    float v[3];

    v[0] = x;
    
    glBegin(GL_QUADS);
	v[1] = y+wy;   v[2] = z-wz;
	glVertex3fv(v);

	v[2] = z+wz;
	glVertex3fv(v);

	v[1] = y-wy;
	glVertex3fv(v);

	v[2] = z-wz;
	glVertex3fv(v);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a window on the negative x side of a building            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void wxminus(float x,  float y,  float z,  float wy,  float wz)
    {
    float v[3];

    v[0] = x;

    glBegin(GL_QUADS);
	v[1] = y-wy;   v[2] = z-wz;
	glVertex3fv(v);

	v[2] = z+wz;
	glVertex3fv(v);

	v[1] = y+wy;
	glVertex3fv(v);

	v[2] = z-wz;
	glVertex3fv(v);
    glEnd();
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw generic square building                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding0(float * colour, int detail)
    {
    makercubenobtm(0.0, 0.4, 0.0, 0.3, 0.4, 0.3, colour);
    if (detail > 0)
	glCallList(genericWindows);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw generic fast food resteraunt                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
   
void drawBuilding6(int counter, float * c1,  float * c2, int detail)
    {
    makercubenobtmnotop(  0,  .2, 0,  .3, .2, .35, c1);
    makeitPyr(1, c2,  0,  .5, 0,  .35, .1, .45);

    makercubenobtm(  .38,  .25, 0.1,  .01, .25, .015, colorgrey2);
    
    glPushMatrix();
    glTranslatef(.38,   .6,  0.1);
	glRotatef((counter*15) % 360, 0, 1, 0);
	makercube(0.0, 0.0, 0.0, 0.01,  0.1,  0.14, c2);
	makercube(0.0, 0.0, 0.0, 0.013, 0.07, 0.11, c1);
    glPopMatrix();

    /* windows */
    
    if (detail > 0)
	{
    	glColor3fv(colorblack);
    
    	wxplus(0.303, 0.15, -0.15, 0.15,  0.05);

    	wxplus(0.303, 0.2,   0.15, 0.075, 0.075);
    
    	wzminus(-0.15, 0.2, -0.352, 0.075, 0.075);
    	wzplus( -0.15, 0.2,  0.352, 0.075, 0.075);
    	wzplus(  0.15, 0.2,  0.352, 0.075, 0.075);
    	wzminus( 0.15, 0.2, -0.352, 0.075, 0.075);
	}
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw warehouse / hanger                                       */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding8(float * c1,  float * c2, int detail)
    {
    makercubenobtmnotop(0,  .2, 0,  .35, .2, .3, c1);
    makeitPyr(4, c2,  0,  .5, 0,  .35, .1, .3);

    /* windows */
    
    if (detail > 0)    
	{
    	glColor3fv(colorblack);
    
    	wzminus(0.0, 0.15, -0.303, 0.25, 0.15);
    	wzplus( 0.0, 0.15,  0.303, 0.25, 0.15);
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw cooling towers                                           */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawCoolingTower(int detail)
    {
    GLUquadricObj *qobj;

    glPushMatrix();
	glTranslatef(-0.3,  0.5,  -0.3);
	glScalef(0.3,  0.5,  0.3);
	
	drawClosedCylinder(colorgrey3,  colorwhite,  0, detail);
	    
    glPopMatrix();

    if (detail >= 0)
	{
	glPushMatrix();
	    glColor3fv(colorblack);
	    glTranslatef(0.0,  0.9,  0.0);
	    glRotatef(-90, 1, 0, 0);
	    
	    qobj = gluNewQuadric();
	    gluDisk( qobj, 0.,  0.28, 32, 1);
	    gluDeleteQuadric(qobj);
    
	glPopMatrix();
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw factory smokestacks                                      */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding11(int detail)
    {
    makercubenobtm(  0,  .05, 0,  .3, .05, .3, colorgrey1);

    glPushMatrix();
	glTranslatef(-.25,  .8,  -.1);
	glScalef(.1,  .8,  .1);
	drawClosedCylinder(colorgrey2,  colorgrey3,  0, detail);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(.05,  .8,  -.1);
	glScalef(.1,  .8,  .1);
	drawClosedCylinder(colorgrey2,  colorgrey3,  0, detail);
    glPopMatrix();
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw strip-mall store                                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding15(float * buildingColour,  float * awningColour, int detail)
    {
    makeitPyr(13, awningColour,  +.1,  .54, 0,  .3, .25, .297);

    makercubenobtm(  -.1,  .4, 0,  .3, .4, .3, buildingColour);

    if (detail > 0)
	{
	glColor3fv(colorblack);
    
	wxplus(0.203,  .15,  -.15,  .15,  .05);
	wxminus(-0.403,  .15,  -.15,  .15,  .05);

	wxplus(0.203,  .15,  .10,  .08,  .12);
	}
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw office building                                          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding22(float * color)
    {
    makercubenobtm(0,  .75, 0,  .3, .75, .3, color);    
    makercubenobtmnotop(0,  .4, 0,  .307, .1, .307, colorblack);
    makercubenobtmnotop(0,  .8, 0,  .307, .1, .307, colorblack);
    makercubenobtmnotop(0,  1.2, 0,  .307, .1, .307, colorblack);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw smaller office building                                   */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding34(float * color)
    {
    makercubenobtm(0,  .3, 0,  .3, .3, .3, color);    
    makercubenobtmnotop(0,  .4, 0,  .307, .1, .307, colorblack);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw small office building                                    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding36(float * color)
    {
    makercubenobtm(0,  .5, 0,  .3, .5, .3, color);    
    makercubenobtmnotop(0,  .4, 0,  .307, .1, .307, colorblack);
    makercubenobtmnotop(0,  .8, 0,  .307, .1, .307, colorblack);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw office building with sign                                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding37(float * color, int detail)
    {
    static float tv1[2] = {0,1};
    static float tv2[2] = {1,1};
    static float tv3[2] = {1,0};
    static float tv4[2] = {0,0};

    static float vec1[3]={0,1,0};
    static float vec2[3]={1,1,0};
    static float vec3[3]={1,0,0};
    static float vec4[3]={0,0,0};

    makercubenobtm(0,  .75, 0,  .3, .75, .3, color);    
    makercubenobtmnotop(0,  .4, 0,  .307, .1, .307, colorblack);
    makercubenobtmnotop(0,  .8, 0,  .307, .1, .307, colorblack);
    makercubenobtmnotop(0, 1.2, -0.01,  .307, .1, .307, colorblack);
    
    glPushMatrix();
    glColor4fv(colorwhite);

    if ((detail >= 2) && (officeLogoData != NULL))
	{	
	glCallList(officeLogo);
	glEnable(GL_TEXTURE_2D);
	}	
	
    glTranslatef(0.25, 1.1, 0.31);
    glScalef(0.5, 0.3,  0.01);

    glRotatef(180, 0, 1, 0);

    glBegin(GL_QUADS);

    if ((detail >= 2) && (picleft != NULL))
	{	
	glTexCoord2fv(tv1);
	glVertex3fv(vec1);
	
	glTexCoord2fv(tv2);
	glVertex3fv(vec2);
	
	glTexCoord2fv(tv3);
	glVertex3fv(vec3);
	
	glTexCoord2fv(tv4);
	glVertex3fv(vec4);
	}
    else
	{
	glVertex3fv(vec1);
	glVertex3fv(vec2);
	glVertex3fv(vec3);
	glVertex3fv(vec4);
	} 
	      
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw satellite dish                                           */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding25()
    {
    long backNow;
    GLUquadricObj *qobj;
    
    /******************/
    /* satellite dish */
    /******************/

    float satSphere[4] = {0, 0.4, 0, 0.075};

    float sat0[3] = { 0.0,  0.35, 0.0};
    float sat1[3] = { 0.0,  0.0,  0.35};
    float sat2[3] = { 0.0, -0.35, 0.0};
    float sat3[3] = { 0.35, 0.0,  0.0};
    float sat4[3] = {-0.35, 0.0,  0.0};

    GLfloat lineWidthNow;
    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
  
    backNow = glIsEnabled(GL_CULL_FACE);

    /* shadow */
    
    glColor3fv(colorblack);
    
    glPushMatrix();
	glTranslatef(0,  0,   0);
	glRotatef(-90, 1, 0, 0);

	qobj = gluNewQuadric();
	gluDisk( qobj, 0.,   0.3, 32, 1);
	gluDeleteQuadric(qobj);

    glPopMatrix();

    /* support post */
    
    makercubenobtm(  0,  .2, 0,  .05, .2, .05, colorwhite);

        
    glColor3fv(colorgrey2);
    andysphdraw(satSphere, 4);
    
    /* if line widths are integral Mesa chokes in a large window */
    glLineWidth(3.01);    
    glColor3fv(colorwhite);
    
    glPushMatrix();
	glDisable(GL_CULL_FACE);
	
	glTranslatef(0,  .4,   0);
	glRotatef(-45, 1, 0, 0);

	qobj = gluNewQuadric();
	gluDisk( qobj, 0.,   0.35, 32, 1);
	gluDeleteQuadric(qobj);

    glPopMatrix();

    if (backNow)
	glEnable(GL_CULL_FACE);
    else
	glDisable(GL_CULL_FACE);

    glPushMatrix();	

	glTranslatef(0,  .4,   0);
	glRotatef(-45, 1, 0, 0);

	glColor3fv(colorgrey1);

	glBegin(GL_LINE_STRIP);
	    glVertex3fv(sat0);
	    glVertex3fv(sat1);
	    glVertex3fv(sat2);	
	glEnd();

	glBegin(GL_LINE_STRIP);
	    glVertex3fv(sat3);
	    glVertex3fv(sat1);
	    glVertex3fv(sat4);	
	glEnd();
    glPopMatrix();
    
    glLineWidth(lineWidthNow);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw drive in theatre screen                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
  
void drawBuilding26(int rorl, int detail)
    {
    /***************************/
    /* theatre screen supports */
    /***************************/

    float screen0[3] = {-0.39, 0.01, -0.28};
    float screen1[3] = {-0.39, 0.01,  0.28};
    float screen2[3] = { 0.39, 0.01,  0.28};
    float screen3[3] = { 0.39, 0.01, -0.28};
    float screen4[3] = {-0.39, 0.79,  0.28};
    float screen5[3] = { 0.39, 0.79,  0.28};
    float screen6[3] = { 0.39, 0.01, -0.28};


    static float vec1[3]={0,1,0};
    static float vec2[3]={1,1,0};
    static float vec3[3]={1,0,0};
    static float vec4[3]={0,0,0};
    
    static float tv1[2] = {0,1};
    static float tv2[2] = {1,1};
    static float tv3[2] = {1,0};
    static float tv4[2] = {0,0};

    GLfloat lineWidthNow;
    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);

    /* supports for the screen */
    
    glColor4fv(colorgrey2);
    /* if line widths are integral Mesa chokes in a large window */
    glLineWidth(3.01);
    
    glBegin(GL_LINE_LOOP);
	glVertex3fv(screen0);
	glVertex3fv(screen1);
	glVertex3fv(screen2);
	glVertex3fv(screen3);
    glEnd();

    glBegin(GL_LINE_LOOP);
	glVertex3fv(screen0);
	glVertex3fv(screen4);
	glVertex3fv(screen5);
	glVertex3fv(screen6);
    glEnd();


    /* back of the screen */    
    makercubenobtm( 0, 0.42, 0.28, 0.4,0.42, 0.01, colorwhite);

    if ((detail >= 2) &&  (picleft != NULL) && (picright != NULL))
	{	
	glPushMatrix();
	    glColor4fv(colorwhite);

	
	    if (rorl == 0)
		glCallList(leftScreen);
	    else
		glCallList(rightScreen);
		
	    glEnable(GL_TEXTURE_2D);
	
	
	    glTranslatef(0.4, 0, 0.3);
	    glScalef(0.8, 0.8,  0.01);
	
	    glRotatef(180, 0, 1, 0);
	
	    glBegin(GL_QUADS);

		glTexCoord2fv(tv1);
		glVertex3fv(vec1);
		
		glTexCoord2fv(tv2);
		glVertex3fv(vec2);
		
		glTexCoord2fv(tv3);
		glVertex3fv(vec3);
		
		glTexCoord2fv(tv4);
		glVertex3fv(vec4);
	    
	    glEnd();
	
	    glDisable(GL_TEXTURE_2D);


	glPopMatrix();
	}  
       
    glLineWidth(lineWidthNow);
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw fountain                                                 */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding29(int itsChristmas, int detail)
    {
    makercubenobtm(  0,  .05, 0,  .3, .05, .3, colorwhite);

    makercubenobtm(  .25,  .1, 0,  .05, .1, .3, colorwhite);
    makercubenobtm(  -.25,  .1, 0,  .05, .1, .3, colorwhite);
    makercubenobtm(  0,  .1, .25,  .3, .1, .05, colorwhite);
    makercubenobtm(  0,  .1, -.25,  .3, .1, .05, colorwhite);

    makeitPyr(3, colorgrey1,  0,  0.3, 0,  0.1, 0.3, 0.1);
    
    if (!itsChristmas)
	{
	if (detail > 0)	
	    glEnable(GL_BLEND);
	makercubenobtm(  0,  .1, 0,  .19, .11, .19, colormaserblue);
	glDisable(GL_BLEND);
	}
    }

   
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw hero beam in effect                                      */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBuilding33(int count, int detail)
    {
    float c[4], height;
   
    c[0] = colorred[0];
    c[1] = colorred[1] + (count/40.0);
    c[2] = colorred[2];
    c[3] = 1 - (count/20.0);
 
    height = .8 - 0.04*count;
   
    if (detail > 0)	
	glEnable(GL_BLEND);
    
    glPushMatrix();
	glTranslatef(-.2,  height,  -.2);
	glScalef(.2,  height,  .2);
	drawClosedCylinder(c,  c,  0, detail);
    glPopMatrix();
    
    glDisable(GL_BLEND);
    }
 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw power line tower                                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawTower(int death, int death2)
    {
    float v1[3], v2[3], v3[3], v4[3];
    float v5[3], v6[3], v7[3], v8[3];
    float va[3], vb[3], vc[3], vd[3];
    float ve[3], vf[3], vg[3];
    float vh[3], vi[3], vj[3];

    float amt,  amt2;
    float samt2,  samt,  camt2;
    float melt1, melt2;

    
    amt = 2 * death * DEG_TO_RAD;
    amt2 = death2 * DEG_TO_RAD;
       
    samt2   = sin(amt2);
    samt    = sin(amt);
    camt2   = cos(amt);
       
    melt1 = samt2 * 0.5*samt;
    melt2 = camt2 * 0.5*samt;
    
    if (death > 0)
	glColor3fv(colorwhite);
    else
	glColor3fv(colorgrey1);
    
    if (death == 0)
	v1[1] = v2[1] = v3[1] = v4[1] = 0.7;
    else
	v1[1] = v2[1] = v3[1] = v4[1] = 0.3 + 0.4 * camt2;

    v1[0] = v4[0] =  -0.06;   
    v1[2] = v2[2] =   0.06;  
    v2[0] = v3[0] =   0.06;
    v3[2] = v4[2] = - 0.06;
 
    v5[0] = v8[0] =  -0.3;
    v5[1] = v6[1] = v7[1] = v8[1] = 0.0;
    v5[2] = v6[2] =   0.3;    
    v6[0] = v7[0] =   0.3;
    v7[2] = v8[2] = - 0.3;
    
    if (death == 0)
	{
	va[1] = vb[1] = vc[1] = vd[1] = 1.5;
	va[0] = v1[0];
	va[2] = v1[2];

	vb[0] = v2[0];
	vb[2] = v2[2];

	vc[0] = v3[0];
	vc[2] = v3[2];

	vd[0] = v4[0];
	vd[2] = v4[2];
	}
    else
	{
	va[1] = vb[1] = vc[1] = vd[1] = 1.5 * camt2;
	va[0] = v1[0]+ melt1;
	va[2] = v1[2]+ melt2;

	vb[0] = v2[0]+ melt1;
	vb[2] = v2[2]+ melt2;

	vc[0] = v3[0]+ melt1;
	vc[2] = v3[2]+ melt2;

	vd[0] = v4[0]+ melt1;
	vd[2] = v4[2]+ melt2;
	}
  

    ve[1] = vf[1] = vc[1] - 0.2;
    ve[0] = vc[0];
    ve[2] = vc[2];

    vf[0] = vd[0];
    vf[2] = vd[2];
  
    vg[0] = (vc[0] + vd[0]) * 0.5;
    vg[1] = vc[1] - 0.1;
    vg[2] = vc[2] - .2;


    vh[0] = va[0];
    vh[1] = vi[1] = va[1] - 0.2;
    vh[2] = va[2];

    vi[0] = vb[0];
    vi[2] = vb[2];
  
    vj[0] = (va[0] + vb[0]) * 0.5;
    vj[1] = va[1] - 0.1;
    vj[2] = va[2] + .2;


    /* if line widths are integral Mesa chokes in a large window */
    glLineWidth(3.01);

    /********/
    /* legs */
    /********/
   
    glBegin(GL_LINE_LOOP);
	glVertex3fv(v1); glVertex3fv(v2); glVertex3fv(v3); glVertex3fv(v4);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
	glVertex3fv(v4); glVertex3fv(v5); glVertex3fv(v2); glVertex3fv(v7);
    glEnd();

    glBegin(GL_LINE_LOOP);
	glVertex3fv(v1); glVertex3fv(v6); glVertex3fv(v3); glVertex3fv(v8);
    glEnd();

 
    /* if line widths are integral Mesa chokes in a large window */
    glLineWidth(2.01);

    /*******/
    /* top */
    /*******/

    glBegin(GL_LINE_LOOP);
	glVertex3fv(va); glVertex3fv(vb); glVertex3fv(vc); glVertex3fv(vd);
    glEnd();

    /*************************/
    /* supports and verticals*/
    /*************************/

    glBegin(GL_LINE_STRIP);
	glVertex3fv(v7); glVertex3fv(v3); glVertex3fv(vc); glVertex3fv(vg); glVertex3fv(ve);
    glEnd();

    glBegin(GL_LINE_STRIP);
	glVertex3fv(v8); glVertex3fv(v4); glVertex3fv(vd); glVertex3fv(vg); glVertex3fv(vf);
    glEnd();

    glBegin(GL_LINE_STRIP);
	glVertex3fv(v5); glVertex3fv(v1); glVertex3fv(va); glVertex3fv(vj); glVertex3fv(vh);
    glEnd();

    glBegin(GL_LINE_STRIP);
	glVertex3fv(v6); glVertex3fv(v2); glVertex3fv(vb); glVertex3fv(vj); glVertex3fv(vi);
    glEnd();


    glBegin(GL_LINE_LOOP);
	glVertex3fv(ve); glVertex3fv(vf); glVertex3fv(vh); glVertex3fv(vi);
    glEnd();    

    }



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw the square playing field                                 */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBattlefield(struct road * roads,  float xshift,  float zshift, 
		    int detail, int itsChristmas, int view)
    {
    float theta, radius;
    float angle;

    /******************************/
    /* 'where is the town' arrow  */
    /******************************/

    static float arrow[4][3] =		{-0.2, PLANEY + 0.01, -1.0, 
				 	 -0.2, PLANEY + 0.01,  1.0, 
				  	  0.2, PLANEY + 0.01,  1.0, 
				  	  0.2, PLANEY + 0.01, -1.0};
			
    static float arrowhead[3][3] =	{0.0, PLANEY + 0.01, -1.75, 
					-0.5, PLANEY + 0.01, -1.0,
				 	 0.5, PLANEY + 0.01, -1.0};
         
    if (itsChristmas)
	glColor3fv(colorsnow);
    else
	glColor3fv(planeGreen);


    if (view == MAPVIEW)
	glCallList(bigPlane);    
    else if (detail <= 1)
	glCallList(lowDPlane);
    else
	glCallList(highDPlane);


    /***************/
    /* draw roads  */
    /***************/

    drawRoads(roads, xshift, zshift, itsChristmas, view, detail);
    
    
    radius = sqrt(xshift * xshift + zshift * zshift);
    
    if (radius > 36)
	{
        /**********************/
        /* draw town pointer  */
        /**********************/
	
	if (zshift == 0)
	    zshift = NEARZERO; 
		
	theta = atan(xshift / zshift);

	if (zshift > 0)
	    theta += PI;

	angle =  theta * RAD_TO_SMALL_DEG;
    
	glPushMatrix();
	    glRotatef(angle, 0, 1, 0);
    
	    glColor3fv(colorred);

	    glBegin(GL_QUADS);
		glVertex3fv(arrow[0]);
		glVertex3fv(arrow[1]);
		glVertex3fv(arrow[2]);
		glVertex3fv(arrow[3]);
	    glEnd();

	    glBegin(GL_TRIANGLES);
		glVertex3fv(arrowhead[0]);
		glVertex3fv(arrowhead[1]);
		glVertex3fv(arrowhead[2]);
	    glEnd();
	glPopMatrix();
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw square lake segment                                      */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawLake0(int itsChristmas)
    {   
static    float lake[4][3] =	{-0.3,  0.0, -0.3, 
				  0.3,  0.0, -0.3, 
				  0.3,  0.0,  0.3, 
				 -0.3,  0.0,  0.3};

    if (itsChristmas)
	glColor3fv(colorblue);
    else
        glColor3fv(colorwater);
        
    glBegin(GL_QUADS);
	glVertex3fv(lake[3]);
	glVertex3fv(lake[2]);
	glVertex3fv(lake[1]);
	glVertex3fv(lake[0]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw triangular lake segment                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawLake1(int itsChristmas)
    {    
    float lake2[3][3] =		{-0.3,  0.0, -0.3, 
				  0.3,  0.0, -0.3, 
				 -0.3,  0.0,  0.3};

    if (itsChristmas)
	glColor3fv(colorblue);
    else
        glColor3fv(colorwater);
    
    glBegin(GL_TRIANGLES);
	glVertex3fv(lake2[2]);
	glVertex3fv(lake2[1]);
	glVertex3fv(lake2[0]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw central hill segment                                     */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHill0(int itsChristmas)
    {   
static     float hill[4][3] =	{-0.3, 0.6, -0.3, 
				  0.3, 0.6, -0.3, 
				  0.3, 0.6,  0.3, 
				 -0.3, 0.6,  0.3};


    if (itsChristmas)
	glColor3fv(colorsnow);
    else
        glColor3fv(planeGreen2);
        
    glBegin(GL_QUADS);
	glVertex3fv(hill[3]);
	glVertex3fv(hill[2]);
	glVertex3fv(hill[1]);
	glVertex3fv(hill[0]);
    glEnd();
    
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw side of hill                                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHill1(int sidemod, int itsChristmas)
    {   
    float c[4];

static    float side[4][3] =	{-0.3, 0.6, -0.3, 
				  0.3, 0.6, -0.3, 
				  0.3, 0.0,  0.3, 
				 -0.3, 0.0,  0.3};
    
    if (itsChristmas)
	{
	c[0] =  colorsnow2[0];   
	c[1] =  colorsnow2[1];   
	c[2] =  colorsnow2[2];   
	}
    else
	{
	c[0] =  planeGreen3[0];   
	c[1] =  planeGreen3[1];   
	c[2] =  planeGreen3[2];  
	} 
	
    c[0] -= sidemod*0.04;
    c[1] -= sidemod*0.04;
    c[2] -= sidemod*0.04;

    if (c[0] < 0)
	c[0] = 0;
    if (c[1] < 0)
	c[1] = 0;
    if (c[2] < 0)
	c[2] = 0;
	    
    glColor3fv(c);
    
    glBegin(GL_QUADS);
	glVertex3fv(side[3]);
	glVertex3fv(side[2]);
	glVertex3fv(side[1]);
	glVertex3fv(side[0]);
    glEnd();

    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw corner of hill                                           */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHill2(int sidemod, int itsChristmas)
    {   
    float c[4];

static    float corner[3][3] =	{-0.3, 0.6, -0.3, 
				  0.3, 0.0, -0.3, 
				 -0.3, 0.0,  0.3};
 
    if (itsChristmas)
	{
	c[0] =  colorsnow2[0];   
	c[1] =  colorsnow2[1];   
	c[2] =  colorsnow2[2];   
	}
    else
	{
	c[0] =  planeGreen3[0];   
	c[1] =  planeGreen3[1];   
	c[2] =  planeGreen3[2];  
	} 
 
    c[0] -= (sidemod*0.04 + 0.02);
    c[1] -= (sidemod*0.04 + 0.02);
    c[2] -= (sidemod*0.04 + 0.02);

    if (c[0] < 0)
	c[0] = 0;
    if (c[1] < 0)
	c[1] = 0;
    if (c[2] < 0)
	c[2] = 0;
 
    glColor3fv(c);
   
    glBegin(GL_TRIANGLES);
	glVertex3fv(corner[2]);
	glVertex3fv(corner[1]);
	glVertex3fv(corner[0]);
    glEnd();

    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw inside corner of hill                                    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHill3(int sidemod, int itsChristmas)
    {
   float c[4];

static    float insidecorner[4][3] =	{-0.3, 0.6, -0.3, 
				  0.3, 0.6, -0.3, 
				 -0.3, 0.6,  0.3, 
				  0.3, 0.0,  0.3 };
 
    if (itsChristmas)
	glColor3fv(colorsnow);
    else
        glColor3fv(planeGreen2);

    glBegin(GL_TRIANGLES);
	glVertex3fv(insidecorner[2]);
	glVertex3fv(insidecorner[1]);
	glVertex3fv(insidecorner[0]);
    glEnd();

    if (itsChristmas)
	{
	c[0] =  colorsnow2[0];   
	c[1] =  colorsnow2[1];   
	c[2] =  colorsnow2[2];   
	}
    else
	{
	c[0] =  planeGreen3[0];   
	c[1] =  planeGreen3[1];   
	c[2] =  planeGreen3[2];  
	} 
 
    c[0] -= (sidemod*0.04 + 0.02);
    c[1] -= (sidemod*0.04 + 0.02);
    c[2] -= (sidemod*0.04 + 0.02);

    if (c[0] < 0)
	c[0] = 0;
    if (c[1] < 0)
	c[1] = 0;
    if (c[2] < 0)
	c[2] = 0;
 
    glColor3fv(c);
 
    glBegin(GL_TRIANGLES);
	glVertex3fv(insidecorner[2]);
	glVertex3fv(insidecorner[3]);
	glVertex3fv(insidecorner[1]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

 void drawWater(int shape,  int itsChristmas)
    {
    switch(shape){
	case 0:	    drawLake0(itsChristmas);
		    break;
		    
	case 1:	    drawLake1(itsChristmas);	/*   |/ */
		    break;
		    
	case 2:	    glRotatef(-90, 0, 1, 0);	/* \| */
		    drawLake1(itsChristmas);
		    break;
		    
	case 3:	    glRotatef(-180, 0, 1, 0);	/* /| */
		    drawLake1(itsChristmas);
		    break;
		    
	case 4:	    glRotatef(90, 0, 1, 0);	/* |\ */
		    drawLake1(itsChristmas);
		    break;
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

 void drawHills(int shape,  int itsChristmas)
    {
    switch(shape){
	case 0:	    drawHill0(itsChristmas);
		    break;
		    
	case 1:	    drawHill1(0, itsChristmas); /* up neg Z */
		    break;
		    
	case 2:	    glRotatef(-90, 0, 1, 0);	/* up pos x */
		    drawHill1(1, itsChristmas);
		    break;
		    
	case 3:	    glRotatef(-180, 0, 1, 0);	/* up pos z */
		    drawHill1(2, itsChristmas);
		    break;
		    
	case 4:	    glRotatef(90, 0, 1, 0);	/* up neg x */
		    drawHill1(1, itsChristmas);
		    break;
		    
		    
	case 5:	    drawHill2(0,  itsChristmas); /* +x,+z corner */
		    break;
		    
	case 6:	    glRotatef(-90, 0, 1, 0);	/* up pos x */
		    drawHill2(0, itsChristmas);
		    break;
		    
	case 7:	    glRotatef(-180, 0, 1, 0);	/* up pos z */
		    drawHill2(1, itsChristmas);
		    break;
		    
	case 8:	    glRotatef(90, 0, 1, 0);	/* up neg x */
		    drawHill2(1, itsChristmas);
		    break;
		    
		    
	case 9:	    drawHill3(0, itsChristmas); /* up +x,-z */
		    break;
		    
	case 10:    glRotatef(-90, 0, 1, 0);	/* up +x,+z */
		    drawHill3(0, itsChristmas);
		    break;
		    
	case 11:    glRotatef(-180, 0, 1, 0);	/* up pos z */
		    drawHill3(1, itsChristmas);
		    break;
		    
	case 12:    glRotatef(90, 0, 1, 0);	/* up neg x */
		    drawHill3(1, itsChristmas);
		    break;

	}
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw all structures on plane (buildings,trees,hills,lakes)    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawtrees(struct tree * allTreesOnPlane, int numTreesOnPlane, int counter, 
		int detail, int itsChristmas, int view)
    {
    
    float spheredat[4];
    float x, y, z;
    register int treeCounter;
    int sph;
    GLfloat lineWidthNow;
    GLint shadeNow;
    
    glGetIntegerv(GL_SHADE_MODEL, &shadeNow);
  
    if (detail >= 2)
	sph = 5;
    else if (detail == 1)
	sph = 4;
    else
	sph = 2;


    for (treeCounter=0; treeCounter < numTreesOnPlane; treeCounter++)
	{
	if (detail >= 2)
	    glShadeModel(GL_SMOOTH);
	else
	    glShadeModel(GL_FLAT);


	if (((fabs(allTreesOnPlane[treeCounter].x) <= PLANESIZE) && (fabs(allTreesOnPlane[treeCounter].z) <= PLANESIZE)) || (view == MAPVIEW))
	    {
	    x = allTreesOnPlane[treeCounter].x;
	    y = allTreesOnPlane[treeCounter].y;
	    z = allTreesOnPlane[treeCounter].z;

	    /**********************************/
	    /* tree                           */
	    /**********************************/

	    if (allTreesOnPlane[treeCounter].type == 0)
		{	    
		if ((allTreesOnPlane[treeCounter].treeshape == 0) || (itsChristmas))
		    {
		    /*************/
		    /* pine tree */
		    /*************/
		    
		    if (detail >= 2)
			{
			glCallList(treeWood);

			glEnable(GL_TEXTURE_2D);
			}


		    makercubenobtmnotopTEX( x, y+0.2, z, 0.075, 0.2, 0.075, colorbrown);
		    glDisable(GL_TEXTURE_2D);
    
		    /* regular pine tree colour is too dark in vector mode */
    
		    if (detail > -1)
			makeitPyr(1, treeColor, x, y+0.8, z, 0.2, 0.4, 0.2);
		    else
			makeitPyr(1, treeColor2, x, y+0.8, z, 0.2, 0.4, 0.2);
    
		    glColor4fv(colorblack);

		    if (detail > 0)		    
			shadow(x, z, 0.2, 0.2);
		    
		    if (itsChristmas)
			{
			makercube( x+0.09, y+0.9, z+0.09, 0.025, 0.025, 0.025, coloryellow);
			makercube( x-0.12, y+0.7, z+0.12, 0.025, 0.025, 0.025, colorred);
			makercube( x-0.1,  y+0.9, z-0.1,  0.025, 0.025, 0.025, colormaserblue);
			makercube( x+0.12, y+0.7, z-0.12, 0.025, 0.025, 0.025, colororange);
			}
		    }
		else
		    /**************/
		    /* round tree */
		    /**************/
		    {
		    if (detail >= 2)
			{
			glCallList(treeWood);

			glEnable(GL_TEXTURE_2D);
			}

		    makercubenobtmnotopTEX(x, y+0.4, z, 0.1, 0.4, 0.1, colorbrown);
		    glDisable(GL_TEXTURE_2D);
    
		    glColor3fv(treeColor2);
		    spheredat[0] = x;
		    spheredat[1] = y+1;
		    spheredat[2] = z;
		    spheredat[3] = 0.3;
		    andysphdraw(spheredat, sph);

		    if (detail > 0)	
			{
			glPushMatrix();
			    glColor3fv(colorblack);
			    glTranslatef(x,  SHADOWS,   z);
			    glCallList(roundTreeShadow);
			glPopMatrix();
			}
		    }
		}

	    /**********************************/
	    /* building                       */
	    /**********************************/
	    	    
	    if (allTreesOnPlane[treeCounter].type == 1)
		{
		glPushMatrix();

		    glTranslatef(x,  y,  z);
		    
		    if (allTreesOnPlane[treeCounter].treeshape <= 17)
			switch(allTreesOnPlane[treeCounter].treeshape){
			    case 0:	drawBuilding0(colorwhite, detail);
					break;
			    case 1:	if (detail == 0)
					    glCallList(building1ObjD0);
					else
					    glCallList(building1Obj);
					break;
			    case 2:	if (detail == 0)
					    glCallList(building2ObjD0);
					else
					    glCallList(building2Obj);
					break;
			    case 3:	glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
					if (allTreesOnPlane[treeCounter].deathCount && allTreesOnPlane[treeCounter].death2)
					    drawTower(allTreesOnPlane[treeCounter].deathCount, allTreesOnPlane[treeCounter].death2);
					else
					    glCallList(powerTower);
					glLineWidth(lineWidthNow);
					break;
			    case 4:	glPushAttrib(GL_LIGHTING_BIT);
					if (detail <= 0)
					    {
					    glShadeModel(GL_FLAT);
					    drawCoolingTower(detail);
					    }
					else
					    {
					    glShadeModel(GL_SMOOTH);
					    drawCoolingTower(detail);    /* cooling tower */
					    }
					glPopAttrib();
					break;
			    case 5:	if (detail == 0)	 /* home */
					    glCallList(building5ObjD0);
					else
					    glCallList(building5Obj);
					break;
			    case 6:	drawBuilding6(counter, colorred, coloryellow, detail); /* fast food */
					break;
			    case 7:	glCallList(building7Obj);
					break;
			    case 8:	drawBuilding8(colorbeige,  colorbrown, detail);
					break;
			    case 9:	glPushAttrib(GL_LIGHTING_BIT);
					if (detail < 0)
					    {
					    glShadeModel(GL_FLAT);
					    glCallList(building9ObjOO);
					    }
					else if (detail == 0)
					    {
					    glShadeModel(GL_FLAT);
					    glCallList(building9Obj);
					    }
					else
					    {
					    glShadeModel(GL_SMOOTH);
					    glCallList(building9Obj);	    /*water tower*/
					    }
					glPopAttrib();
					break;
			    case 10:    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
					glCallList(building10Obj);
					glLineWidth(lineWidthNow);
					break;
			    case 11:    glPushAttrib(GL_LIGHTING_BIT);
					if (detail <= 0)
					    glShadeModel(GL_FLAT);
					else
					    glShadeModel(GL_SMOOTH);
					drawBuilding11(detail);		    /* factory smokestacks*/
					glPopAttrib();
					break;
			    case 12:    if (detail == 0)
					    glCallList(building12ObjD0);
					else
					    glCallList(building12Obj);
					break;
			    case 13:    glRotatef(180, 0, 1, 0);
					if (detail == 0)
					    glCallList(building5ObjD0);
					else
					    glCallList(building5Obj);
					break;
			    case 14:    glCallList(building14Obj);
					break;
			    case 15:    glCallList(strip1Obj); 	/* strip mall */
					break;
			    case 16:    glCallList(strip2Obj); 	/* strip mall */
					break;
			    case 17:    glCallList(strip3Obj); 	/* strip mall */
					break;
			    }
		    else
			switch(allTreesOnPlane[treeCounter].treeshape){
			    case 18:    glRotatef(90, 0, 1, 0);
					drawBuilding0(colorgrey1, detail);
					break;
			    case 19:    if (detail == 0)
					    glCallList(building19ObjD0);
					else
					    glCallList(building19Obj);
					break;
			    case 20:    if (detail == 0)
					    glCallList(building20ObjD0);
					else
					    glCallList(building20Obj);
					break;
			    case 21:    if (detail == 0)
					    glCallList(building21ObjD0);
					else
					    glCallList(building21Obj);
					break;
			    case 22:    drawBuilding22(colorgrey1);
					break;
			    case 23:    drawBuilding22(colorgrey2);
					break;
			    case 24:    drawBuilding22(colorwhite);
					break;
			    case 25:    drawBuilding25();
					break;
			    case 26:    drawBuilding26(0, detail);
					break;
			    case 27:    drawBuilding26(1, detail);
					break;
			    case 28:    glRotatef(-90, 0, 1, 0);
					drawBuilding6(counter, colorgrey2, colorblue, detail);
					break;
			    case 29:    drawBuilding29(itsChristmas, detail);
					break;
			    case 30:    drawBuilding8(colorbeige,  colorgrey2, detail);
					break;
			    case 31:    glCallList(building31Obj); /* maser battery */
					break;
			    case 32:    glCallList(building32Obj); /* helo pad */
					break;
			    case 33:    drawBuilding33(allTreesOnPlane[treeCounter].deathCount, detail); /* hero entrance */
					break;
			    case 34:    drawBuilding34(colorblue2); /* smallest office building */
					break;
			    case 36:    drawBuilding36(colorblue2); /* small office building */
					break;
			    case 37:    drawBuilding37(colorblue2, detail);
					break;
			    default:    showError("Bogus Building in Tree List! (drawtrees)");
					break;
			}

		glPopMatrix();	
		}

	    /**********************************/
	    /* water                          */
	    /**********************************/
		
	    if (allTreesOnPlane[treeCounter].type == 2)
		{
		glPushMatrix();
		    glTranslatef(x,  ROADS,  z);
		    
		    drawWater(allTreesOnPlane[treeCounter].treeshape, itsChristmas);
		    
		glPopMatrix();
		}

	    /**********************************/
	    /* hills                          */
	    /**********************************/

	    if (allTreesOnPlane[treeCounter].type == 3)
		{
		glPushMatrix();
		    glTranslatef(x, PLANEY, z);		    
		    drawHills(allTreesOnPlane[treeCounter].treeshape, itsChristmas);		    
		glPopMatrix();
		}	    
	    }
	}
	glShadeModel(shadeNow);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw all tanks currently dying                                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawSlagTanks(struct tank * allSlags, int counter, int detail)
    {    
    int c;
    float angle2;
    struct tank * ttank;
    
    for(ttank = allSlags->next;ttank != NULL;ttank = ttank->next)
	{
	if ((fabs(ttank->x) <= PLANESIZE) && (fabs(ttank->z) <= PLANESIZE))
	    {
	    angle2 = ttank->theta * RAD_TO_SMALL_DEG;

	    c = ttank->count;
		    
	    glPushMatrix();
	
	    switch(ttank->type){
		case TANK:	glTranslatef(ttank->x, ttank->y-0.015, ttank->z);
				glScalef(1+0.015*c,  1-0.015*c,  1+0.015*c);
				glRotatef(angle2, 0, 1, 0);
				glCallList(slagtank);
				break;
	
		case LAUNCHER:	glTranslatef(ttank->x, ttank->y-0.015, ttank->z);
				glScalef(1+0.015*c,  1-0.015*c,  1+0.015*c);
				glRotatef(angle2, 0, 1, 0);
				glCallList(slaglaunchertank);
				break;
	
		    	    
		case MASERTANK:	glTranslatef(ttank->x, ttank->y-0.015, ttank->z);
				glScalef(0.15+0.002*c,  0.15-0.004*c,  0.15+0.002*c);
				glRotatef(angle2, 0, 1, 0);
				glCallList(slagmasertank);
				break;
  
		case HELO:	glTranslatef(ttank->x, ttank->y, ttank->z);
				glRotatef(c*4.0, 1, 0, 0);
				glRotatef(c*1.5, 0, 0, 1);
				glRotatef(angle2+180+(c*10), 0, 1, 0);
				drawHelo((counter*9) % 360, 1);
				break;

		case CHH:	glTranslatef(ttank->x, ttank->y, ttank->z);
				glRotatef(c*4.0, 1, 0, 0);
				glRotatef(c*1.5, 0, 0, 1);
				glRotatef(angle2+(c*10), 0, 1, 0);
				makeCHH(0);
				break;

		case MECHAG:	glTranslatef(ttank->x, 0, ttank->z);
				glRotatef(angle2, 0, 1, 0);
				drawMechaMonster(0, counter, detail);
				break;
				
		case HERO:	glTranslatef(ttank->x, 0, ttank->z);
				glRotatef(angle2, 0, 1, 0);
				if (ttank->subtype == 0)
				    drawHeroDude(0, ttank->walking, ttank->maserCount, c, detail);
				else
				    drawHeroDude2(0, ttank->walking, ttank->maserCount, c, detail);
				break;
				
		case AIRPLANE:	glTranslatef(ttank->x, ttank->y, ttank->z);
				glRotatef(c*1.5, 0, 0, 1);
				glRotatef(angle2+180+(c*10), 0, 1, 0);
				glScalef(3,  3,  3);
				drawAirplane((counter*2) % 360);
				break;

		case FIGHTER:	glTranslatef(ttank->x, ttank->y, ttank->z);
				glRotatef(c*1.5, 0, 0, 1);
				glRotatef(angle2+180+(c*10), 0, 1, 0);
				glScalef(2,  2,  2);
				drawFighter();
				break;
				
		default:	showError("Bogus Vehicle in Tank List! (drawSlagTanks)");
				break;
		}
	    	    
	    glPopMatrix();
	    }
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw maser beams                                              */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawMaser(float sourceX, float sourceY, float sourceZ,
		int shooter, float mX, float mZ, float mHeight, float mBottom, 
		float r1, float r2, float r3, int width, int view, int detail)

    {
    float beamLoc1[3],  beamLoc2[3];
    GLfloat lineWidthNow;

    beamLoc1[0] = sourceX;
    beamLoc1[1] = sourceY;
    beamLoc1[2] = sourceZ;

    beamLoc2[0] = mX + r1;
    beamLoc2[1] = 0.5 * (mHeight - mBottom) + mBottom + r2;
    beamLoc2[2] = mZ + r3;

    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);

    /* if line widths are integral Mesa chokes in a large window */
    if ((view == MONSTERVIEW) || (view == ARMYVIEW))
	glLineWidth(width * 0.0057);
    else
	glLineWidth(width * 0.0029);
    
    
    glColor3fv(colorwhite);

    glBegin(GL_LINES);
	glVertex3fv(beamLoc1);
	glVertex3fv(beamLoc2);

    glEnd();


    switch(shooter)
	{
	case MASERTANK:	    glColor3fv(colormaserblue);
			    break;
			    
	case CHH:	    glColor3fv(colormaseryellow);
			    break;
			    
	case MECHAG:	    glColor3fv(colorred);
			    break;
			    
	default:	    showError("Invalid Vehicle Type (drawMaser)");
			    break;
	}
	
    if (detail != -1)
	glEnable(GL_BLEND);
    
    /* if line widths are integral Mesa chokes in a large window */
    if ((view == MONSTERVIEW) || (view == ARMYVIEW))
	glLineWidth(width * 0.011);
    else
	glLineWidth(width * 0.0057);

    glBegin(GL_LINES);

	glVertex3fv(beamLoc1);
	glVertex3fv(beamLoc2);
    glEnd();
	
    glDisable(GL_BLEND);

    glLineWidth(lineWidthNow);
    } 

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw all tanks on the battlefield                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawTanks(struct tank * allTanks,  int counter, struct monsterInfo G,
		struct targetInfo * targs, int detail, int view, int wid)

    {
    struct tank cTank;
    struct tank * temptank;
    float angle2;
    int monsterIsDead;
    float height, bottom;
    float xloc,  zloc;
    float radToNearestTarget, rad;
    struct targetInfo * nearestTarget;
    struct monsterInfo * nearestMonster;
    struct targetInfo * temptarget;
    

    for(temptank = allTanks->next;temptank != NULL;temptank = temptank->next)
	{
	cTank = *temptank;
	
	if (((fabs(cTank.x) <= PLANESIZE) && (fabs(cTank.z) <= PLANESIZE)) || (view == MAPVIEW))
	    {
	    
	    
	/* need to find the nearest target */
	
	radToNearestTarget = 10000;
	nearestTarget = NULL;
    	for(temptarget = targs->next;temptarget != NULL;temptarget = temptarget->next)
	    {
	    rad = sqrt((cTank.x-temptarget->x) * (cTank.x-temptarget->x) + (cTank.z-temptarget->z) * (cTank.z-temptarget->z));
	    if (rad < radToNearestTarget)
		{
		radToNearestTarget = rad;
		nearestTarget = temptarget;
		nearestMonster = &(temptarget->monster);
		}
	    }

	/* need to compute radius to player's monster */

	rad = sqrt(cTank.x * cTank.x + cTank.z * cTank.z);

	if (rad < radToNearestTarget)
	    {
	    radToNearestTarget = rad;
	    nearestMonster = NULL;
	    nearestTarget = NULL;
	    }

	if (nearestMonster == NULL)
	    {
	    monsterIsDead = G.monsterIsDead;
	    height = G.height;
	    bottom = G.bottom;
	    xloc = 0;
	    zloc = 0;
	    }
	else
	    {
	    monsterIsDead = nearestMonster->monsterIsDead;
	    height = nearestMonster->height;
	    bottom = nearestMonster->bottom;
	    xloc = nearestTarget->x;
	    zloc = nearestTarget->z;
	    }


	    /**********************************/
	    /* aim vehicle                    */
	    /**********************************/

	    angle2 = cTank.theta * RAD_TO_SMALL_DEG;
	    
	    /**********************************/
	    /* draw vehicle                   */
	    /**********************************/
		    
	    glPushMatrix();

	    switch (cTank.type)
		{
		case TANK:	glTranslatef(cTank.x, cTank.y, cTank.z);
  				glRotatef(angle2, 0, 1, 0);
				glCallList(plaintank);
				break;

		case LAUNCHER:	glTranslatef(cTank.x, cTank.y, cTank.z);
  				glRotatef(angle2, 0, 1, 0);
				glCallList(launchertank);
				break;
			
		case MASERTANK:	glTranslatef(cTank.x, cTank.y, cTank.z);
  				glRotatef(angle2, 0, 1, 0);
				glScalef(0.15,  0.15,  0.15);
				glCallList(masertank);
				break;

		case HELO:	glTranslatef(cTank.x, cTank.y, cTank.z);
  				glRotatef(angle2+180, 0, 1, 0);
				drawHelo((counter*9) % 360,  0);
				break;

		case AIRPLANE:	glTranslatef(cTank.x, cTank.y, cTank.z);
  				glRotatef(angle2+180, 0, 1, 0);
				glScalef(3,  3,  3);
				drawAirplane((counter*2) % 360);
				break;

		case FIGHTER:	glTranslatef(cTank.x, cTank.y, cTank.z);
  				glRotatef(angle2+180, 0, 1, 0);
				glScalef(2,  2,  2);
				drawFighter();
				break;

		case CHH:	glTranslatef(cTank.x, cTank.y, cTank.z);
  				glRotatef(angle2, 0, 1, 0);
				makeCHH(cTank.damage);
				break;
				
		case MECHAG:	glTranslatef(cTank.x, 0, cTank.z);
  				glRotatef(angle2, 0, 1, 0);
				drawMechaMonster(cTank.damage, counter, detail);
				break;

		case HERO:	glTranslatef(cTank.x, 0, cTank.z);
  				glRotatef(angle2, 0, 1, 0);
				if (cTank.subtype == 0)
				    drawHeroDude(cTank.damage, cTank.walking, cTank.maserCount, 0, detail);
				else
				    drawHeroDude2(cTank.damage, cTank.walking, cTank.maserCount, 0, detail);
				break;
				
		default:	showError("Bogus Vehicle in Tank List! (drawTanks)");
				break;
		}
	    
	    glPopMatrix();	

	    if (detail > 0)  	
		{

		/**********************************/
		/* draw shadow                    */
		/**********************************/

		glPushMatrix();
		    glTranslatef(cTank.x, 0, cTank.z);
		    glRotatef(angle2, 0, 1, 0);

		    switch (cTank.type){
		    case TANK:
		    case LAUNCHER:
		    case MASERTANK:	glCallList(tankShadow);
					break;
		    
		    case HELO:	    	glColor4fv(colorblack);
					shadow (0, 0, 0.14, 0.18);
					shadow (0, -0.22, 0.04, 0.1);
					break;
		    
		    case MECHAG:	break;
		    
		    case CHH:		glColor4fv(colorblack);
					shadow (0, 0, 0.14, 0.22);
					break;
		    
		    case HERO:		glColor4fv(colorblack);
					shadow (0, 0, 0.12, 0.08);
					break;
		    
		    case AIRPLANE:	glCallList(planeShadow);
					break;

		    case FIGHTER:	glCallList(fighterShadow);	
					break;

		    default:		showError("Bogus Vehicle in Tank List! (drawTanks)");
					break;
		    }
		glPopMatrix();
		}
  
	    if ((cTank.maserCount > 0) && (cTank.rad <= cTank.range) && (cTank.rad >= 0.5) && (!monsterIsDead))
		{
		/**********************************/
		/* mechaGoogelon firing maser     */
		/**********************************/

		if (cTank.type == MECHAG)
		    drawMaser(cTank.x, cTank.y + 0.8, cTank.z, cTank.type, xloc, zloc, height,
			    bottom, cTank.rand1, cTank.rand2, cTank.rand3, wid, view, detail);
  
		/**********************************/
		/* 009CHH firing maser            */
		/**********************************/
	
		if (cTank.type == CHH)
		    drawMaser(cTank.x, cTank.y, cTank.z, cTank.type, xloc, zloc, height,
			    bottom, cTank.rand1, cTank.rand2, cTank.rand3, wid, view, detail);
  		
		/**********************************/
		/* tank firing maser              */
		/**********************************/

		if (cTank.type == MASERTANK)
		    drawMaser(cTank.x, cTank.y + 0.375, cTank.z, cTank.type, xloc, zloc, height,
			    bottom, cTank.rand1, cTank.rand2, cTank.rand3, wid, view, detail);
  
		/**********************************/
		/* hero firing its weapon         */
		/**********************************/

		if ((cTank.type == HERO) && (cTank.subtype == 1) && (cTank.maserCount > 10) && (cTank.maserCount < 30))
		    if (nearestTarget)
    			drawHeroWeapon(nearestTarget->x, nearestTarget->z, cTank.x, cTank.y + 0.275, cTank.z, colormaserblue, height, bottom);
		    else
    			drawHeroWeapon(0, 0, cTank.x, cTank.y + 0.275, cTank.z, colormaserblue, height, bottom);

  		} 
	    }  
	}  
    }

 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw hero energy beam                                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawHeroWeapon(float targetx, float targetz, float x, float y,
		    float z, float * color, float height, float bottom)
    {
    float loc1[3],  loc2[3];
    float rad,  angle,  r;
    float midPoint;
    GLboolean backNow;
    
    GLint shadeNow;
    
    glGetIntegerv(GL_SHADE_MODEL, &shadeNow);
    backNow = glIsEnabled(GL_CULL_FACE);
    
    rad = sqrt(x * x + z * z);
    
    if (rad == 0)
	rad = NEARZERO;
	
    r = 0.16 / rad;
    
    if (z == 0)
	z = NEARZERO;

    angle = atan(x / z);

    if (z > 0)
	angle += PI;
   
    angle += PI;
     
    midPoint = 0.5 * (height - bottom) + bottom;
    
    glShadeModel(GL_SMOOTH);
    glDisable(GL_CULL_FACE);
    
    glBegin(GL_QUADS);
	glColor3fv(color);
 	loc1[0] = (rad - 0.22) * sin(angle + r);
	loc1[1] = y;
	loc1[2] = (rad - 0.22) * cos(angle + r);
	glVertex3fv(loc1);
	    
 	loc1[0] = (rad - 0.22) * sin(angle - r);
	loc1[2] = (rad - 0.22) * cos(angle - r);
	glVertex3fv(loc1);
	    
	glColor3fv(colorwhite);	
	loc2[0] = targetx - 0.04;
	loc2[2] = targetz - 0.04;
	loc2[1] = midPoint;
	glVertex3fv(loc2);
	    
	loc2[0] = targetx + 0.04;
	loc2[2] = targetz + 0.04;
	glVertex3fv(loc2);
    glEnd();

    /* make beam viewable from side */

    glBegin(GL_QUADS);
	glColor3fv(color);
 	loc1[0] = (rad - 0.22) * sin(angle);
	loc1[1] = y + 0.03;
	loc1[2] = (rad - 0.22) * cos(angle);
	glVertex3fv(loc1);
	    
	loc1[1] = y - 0.03;
	glVertex3fv(loc1);
	    
	glColor3fv(colorwhite);	
	loc2[0] = targetx;
	loc2[2] = targetz;
	loc2[1] = midPoint - 0.02;
	glVertex3fv(loc2);
	    
	loc2[1] = midPoint + 0.02;
	glVertex3fv(loc2);
    glEnd();
	
    if (backNow)
	glEnable(GL_CULL_FACE);
    else
	glDisable(GL_CULL_FACE);
	
    glShadeModel(shadeNow);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makeBooms()
{
    int counter;
    GLuint O;

    float spheredat[4];
	spheredat[0] = 0;
	spheredat[1] = 0;
	spheredat[2] = 0;
    
    for(counter=1;counter<=10;counter++)
	{
	O = glGenLists(1);
	glNewList(O, GL_COMPILE);
	   
	spheredat[3] = 0.03 * counter;

	andysphdraw(spheredat, 3);

	glEndList();

	switch(counter)
	    {
	    case 1: boom1Obj = O;
		    break;
	    case 2: boom2Obj = O;
		    break;
	    case 3: boom3Obj = O;
		    break;
	    case 4: boom4Obj = O;
		    break;
	    case 5: boom5Obj = O;
		    break;
	    case 6: boom6Obj = O;
		    break;
	    case 7: boom7Obj = O;
		    break;
	    case 8: boom8Obj = O;
		    break;
	    case 9: boom9Obj = O;
		    break;
	    case 10: boom10Obj = O;
		    break;
	    }

	/* Build smaller booms for detail level 0 */

	O = glGenLists(1);
	glNewList(O, GL_COMPILE);
	   
	spheredat[3] = 0.02 * counter;

	andysphdraw(spheredat, 1);

	glEndList();

	switch(counter)
	    {
	    case 1: boom1ObjD0 = O;
		    break;
	    case 2: boom2ObjD0 = O;
		    break;
	    case 3: boom3ObjD0 = O;
		    break;
	    case 4: boom4ObjD0 = O;
		    break;
	    case 5: boom5ObjD0 = O;
		    break;
	    case 6: boom6ObjD0 = O;
		    break;
	    case 7: boom7ObjD0 = O;
		    break;
	    case 8: boom8ObjD0 = O;
		    break;
	    case 9: boom9ObjD0 = O;
		    break;
	    case 10: boom10ObjD0 = O;
		    break;
	    }
	}
}


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw explosions                                               */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBooms(struct boom * boomers, int detail)
    {
    struct boom  * tempboom;
    struct boom b;

    if (detail >= 2)
	glEnable(GL_BLEND);

    glColor3fv(coloryellow);

    for(tempboom = boomers->next;tempboom != NULL;tempboom = tempboom->next)
	{
	b = *tempboom;
		
	if (detail >= 2)
	    {
	    coloryellow[3] = (11 - b.count) * 0.1;
	    glColor4fv(coloryellow);
	    }
	
	glPushMatrix();
	    glTranslatef(b.x, b.y, b.z);

	    if (detail == 0) {
		/* Draw smaller 'flickering' explosions (Johan) */

		switch(b.count) {
		case 1: glCallList(boom1ObjD0);
			break;
		case 3: glCallList(boom3ObjD0);
			break;
		case 5: glCallList(boom5ObjD0);
			break;
		case 7: glCallList(boom7ObjD0);
			break;
		case 9: glCallList(boom9ObjD0);
			break;
		}

	    } else {

		switch(b.count) {
		case 1: glCallList(boom1Obj);
			break;
		case 2: glCallList(boom2Obj);
			break;
		case 3: glCallList(boom3Obj);
			break;
		case 4: glCallList(boom4Obj);
			break;
		case 5: glCallList(boom5Obj);
			break;
		case 6: glCallList(boom6Obj);
			break;
		case 7: glCallList(boom7Obj);
			break;
		case 8: glCallList(boom8Obj);
			break;
		case 9: glCallList(boom9Obj);
			break;
		case 10: glCallList(boom10Obj);
			break;
		}
	    }
	glPopMatrix();
	}
	
    if (detail >= 2)
	glDisable(GL_BLEND);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw googelon/Flutter's energy beam                           */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawBeam(float x, float z, int horz, int vert, int monsterName,
	int detail)
    {
    float loc1[3],  loc2[3],  loc3[3];
    float c[4] = {0, 0, 0, 0};
    float * col;
    float R;
    register int i, nlines;
    GLfloat lineWidthNow;

    GLint shadeNow;

    glGetIntegerv(GL_SHADE_MODEL, &shadeNow);

    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
    
    if (monsterName == FLUTTER)
	col = colororange;
    else
	col = colorblue;

	    
    /**********************************/
    /* draw beam                      */
    /**********************************/

    /* if line widths are integral Mesa chokes in a large window */
    glLineWidth(5.01);

    if (vert < 175)
	R = 4;
    else
	R = 1.2 / (cos((900 - vert) * BIG_DEG_TO_RAD));

    if (R < 0)
	R = 0;
    if (R > 4)
	R = 4;

    if (vert < 0)
	loc3[1] = PLANEY + 1.2 + R * sin(fabs(vert * BIG_DEG_TO_RAD));
    else
	loc3[1] = PLANEY + 1.2 - R * sin(fabs(vert * BIG_DEG_TO_RAD));

    loc1[0] = x;
    loc1[2] = z;
    loc1[1] = PLANEY + 1.2;

/* this doesnt really work ... beam has xz value of 4 no matter what y is (> plane)
 * so beam will be longer than 4 as it gets higher up in the sky
 */
 
    loc3[0] = x+R * -cos((900 + horz) * BIG_DEG_TO_RAD);
    loc3[2] = z+R * sin((900 + horz) * BIG_DEG_TO_RAD);

    if (loc3[1] < PLANEY)
	loc3[1] = PLANEY;

    if (monsterName == FLUTTER)
	c[0] = 0.95;
    else
	c[2] = 0.95;

    switch (detail)
	{
	case -1:
	case 0:	nlines = 4;
		break;
		
	case 1:	nlines = 25;
		glShadeModel(GL_SMOOTH);
		break;
		
	case 2:	nlines = 40;
		glShadeModel(GL_SMOOTH);
		break;
	}


    for (i = 0; i < nlines; i++)
	{
	loc2[0] = loc3[0] + randy(0.04);
	loc2[1] = loc3[1] + randy(0.04);
	loc2[2] = loc3[2] + randy(0.04);

	c[1] = 0.5 + randy(0.5);
	
	glBegin(GL_LINES);
	    glColor3fv(c);
	    glVertex3fv(loc2);
	    glColor3fv(col);
	    glVertex3fv(loc1);
	glEnd();
	}
	
    glShadeModel(shadeNow);

    if (detail > 0)
	{
	/**********************************/
	/* shadow of beam                 */
	/**********************************/

	glColor3fv(colorblack);
	loc1[1] = SHADOWS;
	loc3[1] = SHADOWS;

	glBegin(GL_LINES);
	    glVertex3fv(loc1);
	    glVertex3fv(loc3);
	glEnd();
	}

    glLineWidth(lineWidthNow);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw roads on the battlefield                                 */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawRoads(struct road * roads, float xshift, float zshift,
				int itsChristmas, int view, int detail)
    {
    register int i;
    float displaySize;
    float square[4][3];
    float v1[3];
    float v2[3];
    float v3[3];
    float v4[3];
    float xplus, xminus, zplus, zminus;
    int ropCounter;

    static float tv1[2] = {0,1};
    static float tv2[2] = {1,1};
    static float tv3[2] = {1,0};
    static float tv4[2] = {0,0};

    float c, d;
    float cprime,  dprime;

    float xlinemin, xlinemax, zlinemin, zlinemax;
    float xlinemin2, xlinemax2, zlinemin2, zlinemax2; 

    GLfloat lineWidthNow;
    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
    
    xplus   = xshift + 0.252;
    xminus  = xshift - 0.252;
    zplus   = zshift + 0.252;
    zminus  = zshift - 0.252;
    
    v1[1] = v2[1] = v3[1] = v4[1] = ROADS + 0.001;
    

	
    /***********************************/
    /* Draw 'motion' dots on the plane */
    /***********************************/

    if (view != MAPVIEW)
	{
	 c = xshift - (int) xshift;
	 d = zshift - (int) zshift;
    
	if (itsChristmas)
	    glColor3fv(colorblack);
	else
	    glColor3fv(coloryellow);
	    
	if (c > 0)
	    cprime = c-1;
	else
	    cprime = c;
	
	if (d > 0)
	    dprime = d-1;
	else
	    dprime = d;
    
	/* if line widths are integral Mesa chokes in a large window */
	glLineWidth(1.01);
	
	glPushMatrix();
	    glTranslatef(cprime, 0, dprime);
	    if (detail == 0)
		glCallList(planeDotsObjD0);
	    else
		glCallList(planeDotsObj);
	glPopMatrix();
	}


    if (view == MAPVIEW)
	displaySize = 50;
    else
	displaySize = PLANESIZE+0.25;


    if (roads == NULL)
	return;

    /***********************************/
    /* find all the roads on the plane */
    /***********************************/

    ropCounter = 0;
    for(i=0;roads[i].type != NULLROAD;i++)
	{
	if ((fabs(roads[i].x+xshift) <= displaySize) && (fabs(roads[i].y+zshift) <= displaySize))
	    {
	    roadsOnPlane[ropCounter] = roads[i];
	    ropCounter++;
	    
	    if (ropCounter >= MAXROADSONPLANE)
		ropCounter = MAXROADSONPLANE - 1;
	    }
	}

	
    square[0][1] = square[1][1] = square[2][1] = square[3][1] = ROADS;

    /********************/
    /* Draw black roads */
    /********************/

    if (ropCounter > 0)
	{
	glColor3fv(colorblack);

	if (detail >= 2) 
	    {
	    glColor3fv(colorwhite);
	    glCallList(roadtex);
	    glEnable(GL_TEXTURE_2D);
	    }


	glBegin(GL_QUADS);

    
	for(i=0; i < ropCounter; i++)
	    {
	    if (roadsOnPlane[i].type < 3)
		{
		square[0][0] = square[3][0] = roadsOnPlane[i].x+xplus;
		square[1][0] = square[2][0] = roadsOnPlane[i].x+xminus;
    
		square[0][2] = square[1][2] = roadsOnPlane[i].y+zplus;
		square[2][2] = square[3][2] = roadsOnPlane[i].y+zminus;

		if (detail <2)
		    {
		    glVertex3fv(square[3]);
		    glVertex3fv(square[2]);
		    glVertex3fv(square[1]);
		    glVertex3fv(square[0]);
		    }
		else
		    {
			glTexCoord2fv(tv1);
			glVertex3fv(square[3]);
			glTexCoord2fv(tv4);
			glVertex3fv(square[2]);
			glTexCoord2fv(tv3);
			glVertex3fv(square[1]);
			glTexCoord2fv(tv2);
			glVertex3fv(square[0]);
		    }
		}
	    }
	glEnd();

	glDisable(GL_TEXTURE_2D);

	}

    /*******************/
    /* Draw grey roads */
    /*******************/

    if (ropCounter > 0)
	{
	glColor3fv(colorgrey4);
    
	glBegin(GL_QUADS);
   
	for(i=0; i < ropCounter; i++)
	    {
	    if (roadsOnPlane[i].type >= 3)
		{
		square[0][0] = square[3][0] = roadsOnPlane[i].x+xplus;
		square[1][0] = square[2][0] = roadsOnPlane[i].x+xminus;
    
		square[0][2] = square[1][2] = roadsOnPlane[i].y+zplus;
		square[2][2] = square[3][2] = roadsOnPlane[i].y+zminus;
    	    
		glVertex3fv(square[3]);
		glVertex3fv(square[2]);
		glVertex3fv(square[1]);
		glVertex3fv(square[0]);
		}
	    }
	glEnd();
	}

    if (detail != 0) 
	{
	/**************************/
	/* draw they yellow lines */
	/**************************/
     
	xlinemin = xshift-ROADLINELENGTH;
	xlinemax = xshift+ROADLINELENGTH;
	zlinemin = zshift-ROADLINETHICKNESS;
	zlinemax = zshift+ROADLINETHICKNESS;
    
	xlinemin2 = xshift-ROADLINETHICKNESS;
	xlinemax2 = xshift+ROADLINETHICKNESS;
	zlinemin2 = zshift-ROADLINELENGTH;
	zlinemax2 = zshift+ROADLINELENGTH; 
    
	glColor3fv(coloryellow);
    
	glBegin(GL_QUADS);
	
	for(i=0; i < ropCounter; i++)
	    {
	    if(roadsOnPlane[i].type == 0)
		{
		v1[0] = v4[0] = roadsOnPlane[i].x + xlinemin;
		v2[0] = v3[0] = roadsOnPlane[i].x + xlinemax;
		
		v2[2] = v1[2] = roadsOnPlane[i].y + zlinemin;
		v3[2] = v4[2] = roadsOnPlane[i].y + zlinemax;
		
		glVertex3fv(v1);
		glVertex3fv(v4);
		glVertex3fv(v3);
		glVertex3fv(v2);
		}
					
	    else if(roadsOnPlane[i].type == 1)
		{			
		v1[2] = v4[2] = roadsOnPlane[i].y + zlinemin2;
		v2[2] = v3[2] = roadsOnPlane[i].y + zlinemax2;
		
		v2[0] = v1[0] = roadsOnPlane[i].x + xlinemin2;
		v3[0] = v4[0] = roadsOnPlane[i].x + xlinemax2;
    
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
		glVertex3fv(v4);
		
		}
	    else if(roadsOnPlane[i].type == 2)
		{			
		v1[2] = v4[2] = roadsOnPlane[i].y + zlinemin;
		v2[2] = v3[2] = roadsOnPlane[i].y + zlinemax;
		
		v2[0] = v1[0] = roadsOnPlane[i].x + xlinemin2;
		v3[0] = v4[0] = roadsOnPlane[i].x + xlinemax2;
    
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
		glVertex3fv(v4);
		
		}
	    }
	    
	glEnd();
	}

    glLineWidth(lineWidthNow);
    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw projectiles in flight                                    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawProjectiles(struct projectile * allProjs, int counter, 
		    struct fireType * fires, int fireCounter,
		    int itsChristmas, int detail)
    {
    struct projectile *temp;
    float col[4] = {1.0, 0, 0, 0};
    float v[3], v2[3];
    float x, y, z;
    float floatRatio;
    register int i;
    register int rotRatio;
    int beamCounter;

    static float beamhitx[MAXBEAMS], beamhitz[MAXBEAMS];

    GLfloat lineWidthNow;
    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);

    /***********************************/
    /* make standard projectile object */
    /***********************************/
  
    rotRatio = (counter*100) % 3600;
    
    floatRatio = rotRatio * 0.1;

    glDeleteLists( shellObj, 1);
    glNewList(shellObj, GL_COMPILE);

	if (detail <= 0)
	    makerrotcubexyflat(0.035, 0.035, 0.035, rotRatio, colorwhite);	
	else
	    makerrotcubexy(0.05,  0.05,  0.05, rotRatio, colorwhite);	

	if (itsChristmas)
	    {
            makerrotcubexy(0.01, 0.051, 0.051, rotRatio, colorred);
	    makerrotcubexy(0.051, 0.051, 0.01, rotRatio, colorred);
	    }
    glEndList();

    beamCounter = 0;
    for (temp = allProjs->next;temp != NULL;temp = temp->next)
	if ((fabs(temp->x) <= PLANESIZE) && (fabs(temp->z) <= PLANESIZE))
	    {
	    x = temp->x;
	    y = temp->y;
	    z = temp->z;
    
	    /**********************************/
	    /* draw bomb                      */
	    /**********************************/
		
	    switch(temp->type){
		case PROJTANK:
		case PROJROCKET:glPushMatrix();		/* white cube shells */
				    glTranslatef(x,  y,  z);
				    glCallList(shellObj);			
				glPopMatrix();
				if (detail > 0)
				    {
				    glColor4fv(colorblack);
				    shadow (x, z, 0.05, 0.05);
				    }
				break;
				
		case PROJTECHS: glPushMatrix();		/* techs shell */
				    glTranslatef(x,  y,  z);
				    glRotatef(floatRatio, 1, 0, 0);
				    glRotatef(floatRatio, 0, 1, 0);
				    glCallList(shell2Obj);
				glPopMatrix();
				if (detail > 0)
				    {
				    glColor4fv(colorblack);
				    shadow (x, z, 0.05, 0.05);
				    }
				break;
				
		case PROJFIRE:  break;			/* flames */
								
		case PROJSCAR:  beamhitx[beamCounter] = x;	/* monster beam scar */
				beamhitz[beamCounter] = z;
				beamCounter += 1;
				if (beamCounter >= MAXBEAMS)
				    beamCounter -= 1;
				break;
				    
		case PROJWATER: glPushMatrix();		/* water */
				    glTranslatef(x,  y,  z);
				    glCallList(watershellObj);
				glPopMatrix();
				break;

		case PROJHERO:  glPushMatrix();
				    glTranslatef(x,  y,  z);
				    glRotatef(floatRatio, 1, 0, 0);
				    glRotatef(floatRatio, 0, 1, 0);
				    glCallList(heroshellObj);
				glPopMatrix();
				if (detail > 0)
				    {
				    glColor4fv(colorblack);
				    shadow (x, z, 0.05, 0.05);
				    }
				break;
    
		default:	showError("Bogus Projectile in Projectile List! (drawProjectiles)");
				break;
		}
	    }


    /**********************************/
    /* draw fires                     */
    /**********************************/
	    
    for (i=0;i<fireCounter;i++)
	{
	col[1] = fires[i].col;
	if ((fabs(fires[i].x) <= PLANESIZE) && (fabs(fires[i].z) <= PLANESIZE))
	    makeitPyr(12, col, fires[i].x, PLANEY+fires[i].height, fires[i].z,
		fires[i].xwid, fires[i].height, fires[i].zwid);
	}

    /**********************************/
    /* draw scar from monster beam    */
    /**********************************/
    
    glColor3fv(colorblack);

    /* if line widths are integral Mesa chokes in a large window */
    glLineWidth(2.01);

    v[1] = v2[1] = SHADOWS;
    
    v2[0] = beamhitx[0];
    v2[2] = beamhitz[0];
    
    for(i=1; i<beamCounter; i++)
	{
	v[0] = beamhitx[i];
	v[2] = beamhitz[i];
	
	if ((fabs(v[0] - v2[0]) < 0.3) && (fabs(v[2] - v2[2]) < 0.3))
	    {
	    glBegin(GL_LINES);	
		glVertex3fv(v);
		glVertex3fv(v2);	
	    glEnd();
	    }
	    
	v2[0] = v[0];
	v2[2] = v[2];	
	}

    glLineWidth(lineWidthNow);
    }


/*
#define J_SPACE 32
#define J_DASH 34

#define J_1 50
#define J_2 51
#define J_3 52
#define J_4 53
#define J_5 54
#define J_6 55
#define J_7 56
#define J_8 57
#define J_9 58


#define J_H_A 65

#define J_K_A 145
#define J_K_I 146
#define J_K_U 147
#define J_K_E 148
#define J_K_O 149

#define J_K_KA 150
#define J_K_KI 151
#define J_K_KU 152
#define J_K_KE 153
#define J_K_KO 154

#define J_K_SA 155
#define J_K_SI 156
#define J_K_SU 157
#define J_K_SE 158
#define J_K_SO 159

#define J_K_TA 160
#define J_K_TI 161
#define J_K_TU 162
#define J_K_TE 163
#define J_K_TO 164

#define J_K_NA 165
#define J_K_NI 166
#define J_K_NU 167
#define J_K_NE 168
#define J_K_NO 169

#define J_K_HA 170
#define J_K_HI 171
#define J_K_HU 172
#define J_K_HE 173
#define J_K_HO 174

#define J_K_MA 175
#define J_K_MI 176
#define J_K_MU 177
#define J_K_ME 178
#define J_K_MO 179

#define J_K_YA 180
#define J_K_YU 182
#define J_K_YO 184

#define J_K_RA 185
#define J_K_RI 186
#define J_K_RU 187
#define J_K_RE 188
#define J_K_RO 189

#define J_K_GA 200
#define J_K_GI 201
#define J_K_GU 202
#define J_K_GE 203
#define J_K_GO 204

#define J_K_ZA 205
#define J_K_ZI 206
#define J_K_ZU 207
#define J_K_ZE 208
#define J_K_ZO 209

#define J_K_DA 210
#define J_K_DE 213
#define J_K_DO 214

#define J_K_BA 215
#define J_K_BI 216
#define J_K_BU 217
#define J_K_BE 218
#define J_K_BO 219

#define J_K_PA 220
#define J_K_PI 221
#define J_K_PU 222
#define J_K_PE 223
#define J_K_PO 224


    char energyJapanese[]	= {J_K_E, J_K_NE, J_K_RU, J_K_GI, 0};
    char googelonJapanese[]	= {J_K_GU, J_K_GE, J_K_RO, J_SPACE, J_6, 0};
    char techsJapanese[]	= {J_K_TE, J_K_TU, J_K_KU, J_K_SU, J_SPACE, J_7, 0};
    char flutterJapanese[]  	= {J_K_HU, J_K_RA, J_K_TU, J_K_TA, J_SPACE, J_9, 0};
    char vapourJapanese[]   	= {J_K_ZA, J_DASH, J_K_BE, J_DASH, J_K_PA, J_DASH, J_SPACE, J_8, 0};
*/

