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
/* objects.c v 1.3                                                     */
/* routines to build the objects for battalion                         */
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


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeMonsterLookat()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
   
    gluLookAt(0, PLANEY + 2.4, 0.1, 0, PLANEY, 1, 0, 1, 0);
   
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeOverviewLookat()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
   
    gluLookAt( 0,     0, 9 ,  0,     0, 0, 0,1,0);
   
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for tech's shell                                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeshell2()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makerbluecube(0, 0, 0, 0.04, 0.04, 0.04, colorred2);
    
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeWaterShell()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makerbluecube(0, 0, 0, 0.02, 0.02, 0.02, colormaserblue2);

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeHeroShell()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makerbluecube(0, 0, 0, 0.03, 0.03, 0.03, colormaserblue2);

    glEndList();
    return(O);
    }




/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeTankShadow()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glColor4fv(colorblack);
    
    shadow (0, 0 ,  0.16,  0.16);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makePlaneShadow()
    {
    GLuint O;

    float p1[3] = {0.12,  SHADOWS, 0.4};
    float p2[3] = {-0.12, SHADOWS, 0.4};
    float p3[3] = {0,     SHADOWS, 0.8};

    float p4[3] = {0.4,   SHADOWS, 0.1};
    float p5[3] = {-0.4,  SHADOWS, 0.1};
    float p6[3] = {0,     SHADOWS, 0.2};
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glColor4fv(colorblack);
    
    shadow (0, -0.1 ,  0.12,  0.5);
    shadow (0, 0 ,  0.4,  0.1);
    shadow (0, -.5 ,  0.2,  0.05);

    glBegin(GL_TRIANGLES);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);

	glVertex3fv(p4);
	glVertex3fv(p5);
	glVertex3fv(p6);
    glEnd();

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFighterShadow()
    {
    GLuint O;

    float p7[3] = {0.2,   SHADOWS, 0.13};
    float p8[3] = {-0.2,  SHADOWS, 0.13};
    float p9[3] = {0,     SHADOWS, 0.33};
 
    float p10[3] = {0,    SHADOWS, -0.33};
    float p11[3] = {-0.33, SHADOWS, 0};
    float p12[3] = {0.33,  SHADOWS, 0};

    float p13[3] = {0.08,  SHADOWS, 0.26};
    float p14[3] = {-0.08, SHADOWS, 0.26};
    float p15[3] = {0,     SHADOWS, 0.54};
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glColor4fv(colorblack);

    shadow (0, -0.066 ,  0.08,  0.33);
    shadow (0, -.33 ,  0.13,  0.033); 

    glBegin(GL_TRIANGLES);
	glVertex3fv(p13);
	glVertex3fv(p14);
	glVertex3fv(p15);

	glVertex3fv(p7);
	glVertex3fv(p8);
	glVertex3fv(p9);

	glVertex3fv(p10);
	glVertex3fv(p11);
	glVertex3fv(p12);
    glEnd();
    
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for an operational plain tank                   */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeTank()
    {
    GLuint O;

    /***************/
    /* tank barrel */
    /****************/

    float gun[8][3] = {
	-0.03, 0.280, 0.23,
	-0.03, 0.220, 0.24,
	 0.03, 0.220, 0.24, 
	 0.03, 0.280, 0.23,
  	 0.03, 0.225, 0.09,
	 0.03, 0.165, 0.09,
	-0.03, 0.165, 0.09,
	-0.03, 0.225, 0.09 };

    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makeitPyr(11, colorgrey2, -0.12, 0.075, 0.0, 0.075, 0.075, 0.18);
    makeitPyr(11, colorgrey2,  0.12, 0.075, 0.0, 0.075, 0.075, 0.18);

    makercubenobtm(0.0, 0.15,  0.0,  0.15, 0.03,  0.225, colorolive);
    makercubenobtm(0.0, 0.195, 0.0,  0.09, 0.045, 0.09,  colorgrey1);

    maker(gun, 0,  0,  0, 1, 1, 1, colorwhite, 1, 0.8, 0.66, 0.5);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for melting plain tank                          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeSlagTank()
    {
    GLuint O;

    /***************/
    /* tank barrel */
    /****************/

    float gun[8][3] = {
	-0.03, 0.280, 0.23,
	-0.03, 0.220, 0.24,
	 0.03, 0.220, 0.24, 
	 0.03, 0.280, 0.23,
  	 0.03, 0.225, 0.09,
	 0.03, 0.165, 0.09,
	-0.03, 0.165, 0.09,
	-0.03, 0.225, 0.09 };

    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makeitPyr(11, colorwhite, -0.12, 0.075, 0.0, 0.075, 0.075, 0.18);
    makeitPyr(11, colorwhite,  0.12, 0.075, 0.0, 0.075, 0.075, 0.18);

    makercubenobtm(0.0, 0.15,  0.0,  0.15, 0.03,  0.225, colorwhite);
    makercubenobtm(0.0, 0.195, 0.0,  0.09, 0.045, 0.09,  colorwhite);

    maker(gun, 0,  0,  0, 1, 1, 1, colorwhite, 1, 0.8, 0.66, 0.5);

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeLauncherTank()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makeitPyr(11, colorgrey2, -0.12, 0.075, 0.0, 0.075, 0.075, 0.18);
    makeitPyr(11, colorgrey2,  0.12, 0.075, 0.0, 0.075, 0.075, 0.18);

    makercubenobtm(0.0, 0.15,  0.0,  0.15, 0.03,  0.225, colorwhite);

    makercube(0.0, 0.26, 0.075,  0.12, 0.01, 0.075,  colorgrey2);

    makercubenobtm(-0.05, 0.2, 0.075,  0.01, 0.07, 0.01,  colorgrey2);
    makercubenobtm(0.05, 0.2, 0.075,  0.01, 0.07, 0.01,  colorgrey2);

    makercube(0.0, 0.28, 0.075,  0.02, 0.02, 0.1,  colorgrey1);
    makercube(-0.05, 0.28, 0.075,  0.02, 0.02, 0.1,  colorgrey1);
    makercube(0.05, 0.28, 0.075,  0.02, 0.02, 0.1,  colorgrey1);
    makercube(-0.1, 0.28, 0.075,  0.02, 0.02, 0.1,  colorgrey1);
    makercube(0.1, 0.28, 0.075,  0.02, 0.02, 0.1,  colorgrey1);

    makercube(0.0, 0.28, 0.05,  0.021, 0.021, 0.02,  colorred);
    makercube(-0.05, 0.28, 0.05,  0.021, 0.021, 0.02,  colorred);
    makercube(0.05, 0.28, 0.05,  0.021, 0.021, 0.02,  colorred);
    makercube(-0.1, 0.28, 0.05,  0.021, 0.021, 0.02,  colorred);
    makercube(0.1, 0.28, 0.05,  0.021, 0.021, 0.02,  colorred);

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeSlagLauncherTank()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makeitPyr(11, colorwhite, -0.12, 0.075, 0.0, 0.075, 0.075, 0.18);
    makeitPyr(11, colorwhite,  0.12, 0.075, 0.0, 0.075, 0.075, 0.18);

    makercubenobtm(0.0, 0.15,  0.0,  0.15, 0.03,  0.225, colorwhite);

    makercube(0.0, 0.26, 0.075,  0.12, 0.01, 0.075,  colorgrey2);

    makercubenobtm(-0.05, 0.2, 0.075,  0.01, 0.07, 0.01,  colorwhite);
    makercubenobtm(0.05, 0.2, 0.075,  0.01, 0.07, 0.01,  colorwhite);

    makercube(0.0, 0.28, 0.075,  0.02, 0.02, 0.1,  colorwhite);
    makercube(-0.05, 0.28, 0.075,  0.02, 0.02, 0.1,  colorwhite);
    makercube(0.05, 0.28, 0.075,  0.02, 0.02, 0.1,  colorwhite);
    makercube(-0.1, 0.28, 0.075,  0.02, 0.02, 0.1,  colorwhite);
    makercube(0.1, 0.28, 0.075,  0.02, 0.02, 0.1,  colorwhite);

    makercube(0.0, 0.28, 0.05,  0.021, 0.021, 0.02,  colorwhite);
    makercube(-0.05, 0.28, 0.05,  0.021, 0.021, 0.02,  colorwhite);
    makercube(0.05, 0.28, 0.05,  0.021, 0.021, 0.02,  colorwhite);
    makercube(-0.1, 0.28, 0.05,  0.021, 0.021, 0.02,  colorwhite);
    makercube(0.1, 0.28, 0.05,  0.021, 0.021, 0.02,  colorwhite);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for an operational maser tank                   */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeMaserTank()
    {
    GLuint O;
    
    /**********************/
    /* maser tank support */
    /**********************/

    float support1[8][3] = {
	-0.1,  1.8,  -1.3,
	-0.1,  1.2,   0.0,
	 0.1,  1.2,   0.0, 
	 0.1,  1.8,  -1.3,
  	 0.1,  1.8,  -1.7,
	 0.1,  1.2,  -0.4,
	-0.1,  1.2,  -0.4,
	-0.1,  1.8,  -1.7 };

    float support2[8][3] = {
	-0.1,  2.5,  -0.6,
	-0.1,  1.8,  -1.3,
	 0.1,  1.8,  -1.3, 
	 0.1,  2.5,  -0.6,
  	 0.1,  2.5,  -1.0,
	 0.1,  1.8,  -1.7,
	-0.1,  1.8,  -1.7,
	-0.1,  2.5,  -1.0 };


    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
   
    makercubenobtm(-0.8, 0.5,  0.0, 0.5, 0.5, 1.2, colorblue);
    makercubenobtm( 0.8, 0.5,  0.0, 0.5, 0.5, 1.2, colorblue);

    makercubenobtm( 0.0, 1.0,  0.0, 1.1, 0.2, 1.75, colorgrey2);
    makercubenobtm( 0.0, 1.0, -0.5, 0.5, 0.3, 0.5, colorwhite);
    makercube(0.0, 1.5, 1.25,  1.1, 0.3, 0.5, colorgrey3);

    makercube(0.0, 1.5, 1.752, 0.6, 0.1, 0.01, colorblack);

    makercube(0.0, 2.5,  0.0,  0.4, 0.4, 0.1, colorwhite);
    makercube(0.0, 2.5, -0.8,  0.2, 0.2, 0.91, colorblue);

    glColor3fv(colorgrey1);

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(support1[0]);glVertex3fv(support1[1]);glVertex3fv(support1[3]);glVertex3fv(support1[2]);
	glVertex3fv(support1[4]);glVertex3fv(support1[5]); 
	glVertex3fv(support1[7]);glVertex3fv(support1[6]);
	glVertex3fv(support1[0]);glVertex3fv(support1[1]);
    glEnd();

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(support2[0]);glVertex3fv(support2[1]);glVertex3fv(support2[3]);glVertex3fv(support2[2]);
	glVertex3fv(support2[4]);glVertex3fv(support2[5]); 
	glVertex3fv(support2[7]);glVertex3fv(support2[6]);
	glVertex3fv(support2[0]);glVertex3fv(support2[1]);
    glEnd();

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for melting maser tank                          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeSlagMaserTank()
    {
    GLuint O;

    /**********************/
    /* maser tank support */
    /**********************/

    float support1[8][3] = {
	-0.1,  1.8,  -1.3,
	-0.1,  1.2,   0.0,
	 0.1,  1.2,   0.0, 
	 0.1,  1.8,  -1.3,
  	 0.1,  1.8,  -1.7,
	 0.1,  1.2,  -0.4,
	-0.1,  1.2,  -0.4,
	-0.1,  1.8,  -1.7 };

    float support2[8][3] = {
	-0.1,  2.5,  -0.6,
	-0.1,  1.8,  -1.3,
	 0.1,  1.8,  -1.3, 
	 0.1,  2.5,  -0.6,
  	 0.1,  2.5,  -1.0,
	 0.1,  1.8,  -1.7,
	-0.1,  1.8,  -1.7,
	-0.1,  2.5,  -1.0 };

    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercubenobtm( -0.8, 0.5, 0,  0.5,0.5,1.2, colorwhite);
    makercubenobtm(0.8, 0.5 ,0,  0.5,0.5,1.2, colorwhite);

    makercubenobtm(  0, 1, 0,  1.1, 0.2, 1.75, colorwhite);
    makercubenobtm(  0, 1, -.5,  .5, 0.3, .5, colorwhite);
    makercube(0.0, 1.5, 1.25,  1.1, 0.3, 0.5, colorwhite);

    makercube(0.0, 1.5, 1.751, 0.6, 0.1, 0.01, colorwhite);

    makercube(0.0, 2.5,  0.0,  0.4, 0.4, 0.1, colorwhite);
    makercube(0.0, 2.5, -0.8,  0.2, 0.2, 0.91, colorwhite);
    
    glColor3fv(colorwhite);

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(support1[0]);glVertex3fv(support1[1]);glVertex3fv(support1[3]);glVertex3fv(support1[2]);
	glVertex3fv(support1[4]);glVertex3fv(support1[5]); 
	glVertex3fv(support1[7]);glVertex3fv(support1[6]);
	glVertex3fv(support1[0]);glVertex3fv(support1[1]);
    glEnd();

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(support2[0]);glVertex3fv(support2[1]);glVertex3fv(support2[3]);glVertex3fv(support2[2]);
	glVertex3fv(support2[4]);glVertex3fv(support2[5]); 
	glVertex3fv(support2[7]);glVertex3fv(support2[6]);
	glVertex3fv(support2[0]);glVertex3fv(support2[1]);
    glEnd();

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for an operational helicopter                   */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeHelo()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercube(0.0,  0.0,     0.0,    0.1, 0.1,    0.2, colorgrey2);
    makercube(0.0, -0.0375, -0.225,  0.1, 0.0625, 0.025, colorgrey2);

    makercubenobtm( -0.05, +0.0625, -0.2,  0.025, 0.025, 0.025, colorblack);
    makercubenobtm(  0.05, +0.0625, -0.2,  0.025, 0.025, 0.025, colorblack);

    makercube(0.0, 0.0,   0.3, 0.0375, 0.0375, 0.1, colorgrey1);
    makercubenobtmnotop( 0.0, 0.125, 0.0, 0.025,  0.05,   0.025, colorgrey1);

    /**************/
    /* draw skids */
    /**************/

    makercube( 0.075, -0.2, 0.0,  0.025, 0.0125, 0.175, colorwhite);
    makercube(-0.075, -0.2, 0.0,  0.025, 0.0125, 0.175, colorwhite);

    makercubenobtm(  0.075, -0.15, 0.025,  0.0125, 0.05, 0.05, colorgrey1);
    makercubenobtm( -0.075, -0.15, 0.025,  0.0125, 0.05, 0.05, colorgrey1);

    glEndList();
    return(O);
    }
 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for melting helicopter                          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeSlagHelo()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
	
    makercube(0.0,  0.0,     0.0,    0.1, 0.1,    0.2, colorwhite);
    makercube(0.0, -0.0375, -0.225,  0.1, 0.0625, 0.025, colorwhite);

    makercubenobtm( -0.05, +0.0625, -0.2, 0.025, 0.025, 0.025,colorwhite);
    makercubenobtm(  0.05, +0.0625, -0.2, 0.025, 0.025, 0.025, colorwhite);

    makercube(0.0, 0.0,   0.3, 0.0375, 0.0375, 0.1, colorwhite);
    makercubenobtmnotop( 0.0, 0.125, 0.0, 0.025,  0.05,   0.025, colorwhite);

    /**************/
    /* draw skids */
    /**************/

    makercube( 0.075, -0.2, 0.0,  0.025, 0.0125, 0.175, colorwhite);
    makercube(-0.075, -0.2, 0.0,  0.025, 0.0125, 0.175, colorwhite);

    makercubenobtm( 0.075, -0.15, 0.025, 0.0125, 0.05, 0.05, colorwhite);
    makercubenobtm(-0.075, -0.15, 0.025, 0.0125, 0.05, 0.05, colorwhite);

    glEndList();
    return(O);
    }
 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for main rotor of the helicopters               */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
  
GLuint makeBigRotor()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercube(0.0, 0.175, 0.0, 0.025, 0.01, 0.3, colorwhite);
    makercube(0.0, 0.175, 0.0, 0.3,   0.01, 0.025, colorwhite);
    
    glEndList();
    return(O);
    }

 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for small rotor of the helicopters              */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
  
GLuint makeSmallRotor()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercube(0.0, 0.0, 0.0, 0.0025, 0.15, 0.02, colorwhite);
    
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for propeller for bomber                        */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
  
GLuint makePropeller()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercube(0.0, 0.0, 0.0, 0.005, 0.05, 0.001, colorwhite);
    
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* make bomber body                                              */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeAirplaneBody()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

	/*************/
	/* draw body */
	/*************/

	makercube(0.0, 0.0, 0.0, 0.03, 0.03, 0.14, colorwhite);

	glPushMatrix();
		glTranslatef(0,  0,  -0.14);
		glRotatef(-90, 1, 0, 0);
		makeitPyr(1, colorwhite, 0.0, 0.08, 0.0, 0.03, 0.08, 0.03);
	glPopMatrix();

	/*************/
	/* draw tail */
	/*************/

	makercube(0.0, 0.07, 0.11, 0.002, 0.04 ,0.02, colorwhite);

	makeitPyr(1, colorwhite, 0.0, 0.03, 0.09, 0.002, 0.08, 0.02);

	/**************/
	/* draw wings */
	/**************/

	makercube(0.0, 0.0, -0.01, 0.16, 0.004, 0.02, colorgrey3);

	glPushMatrix();
		glTranslatef(0,  0,  -0.03);
		glRotatef(-90,1, 0, 0);
		makeitPyr(1, colorgrey2, 0.0, 0.03, 0, 0.16, 0.03, 0.004);
	glPopMatrix();

	makercube(0.0, 0.0, 0.11, 0.08, 0.004, 0.015, colorgrey3);

	glPushMatrix();
		glTranslatef(0,  0,  0.095);
		glRotatef(-90, 1, 0, 0);
		makeitPyr(1, colorgrey2, 0.0, 0.02, 0.0, 0.08, 0.02, 0.004);
	glPopMatrix();
    
    makercube(-0.09, -0.004-0.01, -0.07+0.02, 0.01, 0.01, 0.02, colorgrey1);

    makercube( 0.09, -0.004-0.01, -0.07+0.02, 0.01, 0.01, 0.02, colorgrey1);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* make fighter body                                              */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFighterBody()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

	/*************/
	/* draw body */
	/*************/

	makercube(0.0, 0.0, 0.0, 0.03, 0.03, 0.14, colorwhite);

	glPushMatrix();
		glTranslatef(0,  0,  -0.14);
		glRotatef(-90, 1, 0, 0);
		makeitPyr(1, colorwhite, 0.0, 0.08, 0.0, 0.03, 0.08, 0.03);
	glPopMatrix();

	/*************/
	/* draw tail */
	/*************/

	glPushMatrix();
		glTranslatef(-0.05, 0.05, 0.11);
		glRotatef(45, 0, 0, 1);
	    makercube(0.0, 0, 0, 0.002, 0.04 ,0.02, colorgrey3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.05, 0.05, 0.11);
		glRotatef(-45, 0, 0, 1);
	    makercube(0.0, 0, 0, 0.002, 0.04 ,0.02, colorgrey3);
	glPopMatrix();


	/**************/
	/* draw wings */
	/**************/

	glPushMatrix();
		glTranslatef(0,  0,  0.03);
		glRotatef(90, 1, 0, 0);
		makeitPyr(1, colorgrey3, 0.0, 0.01, 0, 0.16, 0.085, 0.004);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,  0,  0.03);
		glRotatef(-90, 1, 0, 0);
		makeitPyr(1, colorgrey3, 0.0, 0.2, 0, 0.1, 0.04, 0.004);
	glPopMatrix();

    
    makercube(-0.09, -0.004-0.01, 0.02, 0.01, 0.01, 0.04, colorred);

    makercube( 0.09, -0.004-0.01, 0.02, 0.01, 0.01, 0.04, colorred);

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for Googelon's leg                              */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeLeg()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercube( 0.0,   PLANEY+0.2,  0.0,   0.1,  0.2,  0.1,  colorred);
    makercube( 0.0,   PLANEY+0.06, 0.17,  0.1,  0.06, 0.08, colorred);
    makercube( 0.05,  PLANEY+0.05, 0.25,  0.03, 0.04, 0.05, colorwhite);
    makercube(-0.05,  PLANEY+0.05, 0.25,  0.03, 0.04, 0.05, colorwhite);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for Googelon's head                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeHead()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercube(0.0, PLANEY+1.15,  0.0,  0.22, 0.15, 0.1, colorred);
    makercube(0.0, PLANEY+1.15, -0.1,  0.1,  0.1,  0.1, colorred);

    /**********/
    /* pupils */
    /**********/

    makercube( 0.15, PLANEY+1.21, 0.1, 0.03, 0.03, 0.06, colorblack);
    makercube(-0.15, PLANEY+1.21, 0.1, 0.03, 0.03, 0.06, colorblack);

    /********/
    /* eyes */
    /********/

    makercube( 0.15, PLANEY+1.20, 0.1, 0.06, 0.06, 0.05, colorwhite);
    makercube(-0.15, PLANEY+1.20, 0.1, 0.06, 0.06, 0.05, colorwhite);


    glEndList();
    return(O);
    }


GLuint makeSimpleHead()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtm(0.0, PLANEY+1.15,  0.0,  0.22, 0.15, 0.1, colorred);
    makercubeTopBack(0.0, PLANEY+1.15, -0.1,  0.1,  0.1,  0.1, colorred);
    
    /********/
    /* eyes */
    /********/
    
    makercubenobtm( 0.15, PLANEY+1.20, 0.1, 0.06, 0.06, 0.05, colorwhite);
    makercubenobtm(-0.15, PLANEY+1.20, 0.1, 0.06, 0.06, 0.05, colorwhite);
    
    /**********/
    /* pupils */
    /**********/
    
    makercubenobtm( 0.15, PLANEY+1.21, 0.1, 0.03, 0.03, 0.06, colorblack);
    makercubenobtm(-0.15, PLANEY+1.21, 0.1, 0.03, 0.03, 0.06, colorblack);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for Googelon's tail                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeTail()
    {	
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
   
    makercube(0.0, PLANEY+0.23, -0.2,   0.1, 0.15, 0.2, colorred);
    makercube(0.0, PLANEY+0.13, -0.35,  0.1, 0.1,  0.15, colorred);
    makeitPyr(2, colorred, 0, PLANEY+0.13, -0.6,  0.1, 0.1, 0.1);

    /****************/
    /* dorsal spine */
    /****************/

    makercubenobtm(0.0, PLANEY+0.4, -0.20, 0.02, 0.06, 0.08, colorwhite);
    makercube(     0.0, PLANEY+0.7, -0.19, 0.02, 0.06, 0.07, colorwhite);
    
    glEndList();
    return(O);
    }

GLuint makeSimpleTail()
    {	
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercubenobtm(0.0, PLANEY+0.23, -0.2,   0.1, 0.15, 0.2, colorred);

    /****************/
    /* dorsal spine */
    /****************/

    makercubenobtm(0.0, PLANEY+0.4, -0.20, 0.02, 0.06, 0.08, colorwhite);
    makercube(     0.0, PLANEY+0.7, -0.19, 0.02, 0.06, 0.07, colorwhite);
     
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for an Googelon's body                          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeBody()
    {    
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercube(     0.0, PLANEY+0.5, 0.0,  0.2,  0.3, 0.2,  colorred);
    makercubenobtm(0.0, PLANEY+0.9, 0.0,  0.15, 0.2, 0.15, colorred);
   
    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for flutter's head                              */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFlutterHead()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

	makercube( 0.0,  PLANEY+1.15, 0.05, 0.1,  0.1,  0.05, colorbrown);
	makercube( 0.07, PLANEY+1.23, 0.11, 0.02, 0.02, 0.02, colorblack);
	makercube(-0.07, PLANEY+1.23, 0.11, 0.02, 0.02, 0.02, colorblack);
	makercube( 0.07, PLANEY+1.23, 0.08, 0.04, 0.04, 0.04, colorwhite);
	makercube(-0.07, PLANEY+1.23, 0.08, 0.04, 0.04, 0.04, colorwhite);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFlutterShadow()
    {
    GLuint O;

    /********************/
    /* flutter's shadow */
    /********************/

    float flutshad1[3]	= { 0.1,  SHADOWS, -0.1};   
    float flutshad2[3]	= {-0.1,  SHADOWS, -0.1};   
    float flutshad3[3]	= { 0.1,  SHADOWS,  0.1};   
    float flutshad4[3]	= {-0.1,  SHADOWS,  0.1};   
    float flutshad5[3]	= {   0,  SHADOWS, -0.3};   
    float flutshad6[3]	= {0.25,  SHADOWS,  0.5};   
    float flutshad7[3]	= {0.25,  SHADOWS, -0.5};   
    float flutshad8[3]	= {-0.25, SHADOWS, -0.5};   
    float flutshad9[3]	= {-0.25, SHADOWS,  0.5};   
    float flutshad10[3]	= { 0.5,  SHADOWS,  0.0};   
    float flutshad11[3]	= {-0.5,  SHADOWS,  0.0};   
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glColor4fv(colorblack);
    
    shadow (0,  0,  0.1,  0.1);

    glBegin(GL_TRIANGLES);
	glVertex3fv(flutshad1);
	glVertex3fv(flutshad5);
	glVertex3fv(flutshad2);

	glVertex3fv(flutshad6);
	glVertex3fv(flutshad10);
	glVertex3fv(flutshad7);

	glVertex3fv(flutshad8);
	glVertex3fv(flutshad11);
	glVertex3fv(flutshad9);
    glEnd();

    glBegin(GL_QUADS);
	glVertex3fv(flutshad3);
	glVertex3fv(flutshad6);
	glVertex3fv(flutshad7);
	glVertex3fv(flutshad1);

	glVertex3fv(flutshad2);
	glVertex3fv(flutshad8);
	glVertex3fv(flutshad9);
	glVertex3fv(flutshad4);
    glEnd();


    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFlutterXMas()
    {
    float v[4];

    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

		glPushMatrix();
		    glTranslatef(0, PLANEY+1.25, -0.1);
		    glScalef(1.2,  0.45,  1.2);
			glColor3fv(colorwhite);
			v[0] = v[1] = v[2] = 0;
			v[3] = 0.14;
			andysphdraw(v, 4);
		glPopMatrix();

		glPushMatrix();
		    glTranslatef(-0.15,  PLANEY+1.45,  -0.25);
		    glScalef(0.15,  0.2,  0.15);
		    drawClosedCone(healthGreen, healthGreen, 1);
		glPopMatrix();

		glPushMatrix();
		    glTranslatef(-0.09,  PLANEY+1.65,  -0.06);
		    glRotatef(.1*(1100), 1, 0, 0);
		    glRotatef(.1*(450), 0, 0, 1);
		    glScalef(0.04,  0.11,  0.1);
		    drawClosedCone(healthGreen, healthGreen, 1);
		glPopMatrix();

		glColor3fv(colorwhite);
		v[0] = -0.15;
		v[1] = PLANEY+1.50;
		v[2] = -0.0;
		v[3] = 0.05;
		andysphdraw(v, 4);		    

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFlutterWing1()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makeitPyr(10, colorbrown, 0.25, 0, 0, 0.15, 0.03, 0.5);
    makeitPyr(7, colorbrown, 0.25, 0, 0, 0.25, 0.03, 0.5);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFlutterWing2()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makeitPyr(9, colorbrown, -0.25, 0, 0, 0.15, 0.03, 0.5);
    makeitPyr(8, colorbrown, -0.25, 0, 0, 0.25, 0.03, 0.5);

    glEndList();
    return(O);
    }
  
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeFlutterBody()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

	    makercube(0.0, PLANEY+1.15, 0.0, 0.1, 0.08, 0.1, colorbrown);
	    
	    makeitPyr(2, coloryellow, 0.0, PLANEY+1.15, -0.2, 0.1, 0.1, 0.1);

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for tech's body                                 */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeTechsBody()
    {
    int sph;
    GLuint O;
    float sp[4];
    
    sph =3;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glColor3fv(colorgrey1);

    sp[0] = sp[2] = 0;
    sp[1] = PLANEY+ 0.2;
    sp[3] = 0.15;
    andysphdraw(sp, sph);

    makercubenobtm(0, PLANEY+0.6, 0, 0.07, 0.5, 0.07, colorgrey1);

    makercube( 0, PLANEY+0.5, 0, 0.2, 0.05, 0.05, colorgrey3);

    makercube( 0.22,  PLANEY+0.5, 0, 0.025, 0.2, 0.15, colorblack);
    makercube( 0.2,    PLANEY+0.5, 0, 0.03, 0.25, 0.2, colorgrey2);

    makercube(-0.22, PLANEY+0.5, 0, 0.025, 0.2, 0.15, colorblack);
    makercube(-0.2,   PLANEY+0.5, 0, 0.03, 0.25, 0.2, colorgrey2);

    glEndList();
    return(O);
    }

GLuint makeTechsSimpleBody()
    {
    int sph;
    GLuint O;
    float sp[4];
    
    sph =3;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glColor3fv(colorgrey1);

    sp[0] = sp[2] = 0;
    sp[1] = PLANEY+ 0.2;
    sp[3] = 0.15;
    andysphdraw(sp, sph);

    makercubeTopBack(0, PLANEY+0.6, 0, 0.07, 0.5, 0.07, colorgrey1);
    makercubeTopBack( 0, PLANEY+0.5, 0, 0.2, 0.05, 0.05, colorgrey3);

    makercubenobtm( 0.2,    PLANEY+0.5, 0, 0.03, 0.25, 0.2, colorgrey2);
    makercubenobtm(-0.2,   PLANEY+0.5, 0, 0.03, 0.25, 0.2, colorgrey2);

    glEndList();
    return(O);
    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeTechsHead()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

	makercube(0, PLANEY+1.2, 0, 0.15, 0.15, 0.1, colorgrey3);
	makercube(0, PLANEY+1.2, 0.13, 0.06, 0.06, 0.04, colorblack);
	makercube(0, PLANEY+1.2, -0.15, 0.075, 0.11, 0.1, colorgrey2);

    glEndList();
    return(O);
    }

GLuint makeTechsSimpleHead()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

	makercube(0, PLANEY+1.2, 0, 0.15, 0.15, 0.1, colorgrey3);
	makercubenobtm(0, PLANEY+1.2, 0.13, 0.06, 0.06, 0.04, colorblack);
	makercubeTopBack(0, PLANEY+1.2, -0.15, 0.075, 0.11, 0.1, colorgrey2);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeTechsShadow()
    {
    GLuint O;
    GLUquadricObj *qobj;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glPushMatrix();
	glColor3fv(colorblack);
	glTranslatef(0,  SHADOWS,   0);
	glRotatef(-90, 1, 0, 0);

	qobj = gluNewQuadric();
	gluDisk( qobj, 0.,   0.13, 32, 1);
	gluDeleteQuadric(qobj);

    glPopMatrix();

    glColor4fv(colorblack);
    
    shadow (0,  0,  0.2,  0.05);

    shadow (0.2,   0,  0.03,  0.2);
    shadow (-0.2,  0,  0.03,  0.2);

    glEndList();
    return(O);
    }



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw intact power line tower                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makePowerTower()
    {
    GLuint O;
    GLfloat lineWidthNow;
    glGetFloatv(GL_LINE_WIDTH, &lineWidthNow);
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    drawTower(0, 0);
        
    glEndList();

    glLineWidth(lineWidthNow);

    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeGenericWindows()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glColor3fv(colorblack);
    
    wzminus(-0.15, 0.6,  -0.303,  0.05,  0.1);
    wzminus( 0.0,  0.6,  -0.303,  0.05,  0.1);
    wzminus( 0.15, 0.6,  -0.303,  0.05,  0.1);
    wzminus(-0.15, 0.3,  -0.303,  0.05,  0.1);
    wzminus( 0.0,  0.3,  -0.303,  0.05,  0.1);
    wzminus( 0.15, 0.3,  -0.303,  0.05,  0.1);

    wzplus(-0.15, 0.6,  0.303,  0.05,  0.1);
    wzplus( 0.0,  0.6,  0.303,  0.05,  0.1);
    wzplus(-0.15, 0.3,  0.303,  0.05,  0.1);
    wzplus( 0.0,  0.3,  0.303,  0.05,  0.1);

    wxplus( 0.303,  0.6,  -0.15, 0.1, 0.05);
    wxplus( 0.303,  0.6,   0.0,  0.1, 0.05);
    wxplus( 0.303,  0.6,   0.15, 0.1, 0.05);

    wxminus(-0.303, 0.6,  -0.15, 0.1, 0.05);
    wxminus(-0.303, 0.6,   0.0,  0.1, 0.05);
    wxminus(-0.303, 0.6,   0.15, 0.1, 0.05);
    
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw high-rise building                                       */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding1(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtmnotop(  0,  .7, 0,  .3, .7, .3, colorwhite);
    makercubenobtm(  0,  1.5, 0,  .3, .1, .3, colorgrey1);

    if (detail > 0)    
	{
	glColor3fv(colorblack);
	wzminus(-0.15, 1.2,  -0.303,  0.05,  0.1);
	wzminus( 0.0,  1.2,  -0.303,  0.05,  0.1);
	wzminus( 0.15, 1.2,  -0.303,  0.05,  0.1);
	wzminus(-0.15, 0.9,  -0.303,  0.05,  0.1);
	wzminus( 0.0,  0.9,  -0.303,  0.05,  0.1);
	wzminus( 0.15, 0.9,  -0.303,  0.05,  0.1);
	wzminus(-0.15, 0.6,  -0.303,  0.05,  0.1);
	wzminus( 0.0,  0.6,  -0.303,  0.05,  0.1);
	wzminus( 0.15, 0.6,  -0.303,  0.05,  0.1);
	wzminus(-0.15, 0.3,  -0.303,  0.05,  0.1);
	wzminus( 0.0,  0.3,  -0.303,  0.05,  0.1);
	wzminus( 0.15, 0.3,  -0.303,  0.05,  0.1);

	wzplus(-0.15, 1.2,  0.303,  0.05,  0.1);
	wzplus( 0.0,  1.2,  0.303,  0.05,  0.1);
	wzplus( 0.15, 1.2,  0.303,  0.05,  0.1);
	wzplus(-.15,  0.9,  0.303,  0.05,  0.1);
	wzplus( 0.0,  0.9,  0.303,  0.05,  0.1);
	wzplus( 0.15, 0.9,  0.303,  0.05,  0.1);
	wzplus(-0.15, 0.6,  0.303,  0.05,  0.1);
	wzplus( 0.0,  0.6,  0.303,  0.05,  0.1);
	wzplus( 0.15, 0.6,  0.303,  0.05,  0.1);
	wzplus(-0.15, 0.3,  0.303,  0.05,  0.1);
	wzplus( 0.0,  0.3,  0.303,  0.05,  0.1);
	wzplus( 0.15, 0.3,  0.303,  0.05,  0.1);

	wxplus(0.303,  0.6,  -0.15,  0.1,  0.05);
	wxplus(0.303,  0.3,  -0.15,  0.1,  0.05);

	wxminus(-0.303,  0.6,  -0.15, 0.1,  0.05);
	wxminus(-0.303,  0.6,   0.0,  0.1,  0.05);
	wxminus(-0.303,  0.3,  -0.15, 0.1,  0.05);
	wxminus(-0.303,  0.3,   0.0,  0.1,  0.05);
	}    
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw generic beige building                                   */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
   
GLuint makebuilding2(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtm(  0.0,  0.4, 0.0,  0.3, 0.4, 0.3, colorbeige);

    if (detail > 0)
	{
	glColor3fv(colorblack);

	wzminus(-0.15, 0.6, -0.303,  0.05,  0.15);
	wzminus( 0.0,  0.6, -0.303,  0.05,  0.15);
	wzminus( 0.15, 0.6, -0.303,  0.05,  0.15);

	wzplus(-0.15,  0.6,  0.303,  0.05,  0.15);
	wzplus( 0.0,   0.6,  0.303,  0.05,  0.15);
	wzplus( 0.15,  0.6,  0.303,  0.05,  0.15);

	wxplus( 0.303, 0.6,  -0.15,  0.15,  0.05);
	wxplus( 0.303, 0.6,   0.0,   0.15,  0.05);
	wxplus( 0.303, 0.6,   0.15,  0.15,  0.05);

	wxminus(-0.303, 0.6,  -0.15, 0.15,  0.05);
	wxminus(-0.303, 0.6,   0.0,  0.15,  0.05);
	wxminus(-0.303, 0.6,   0.15, 0.15,  0.05);
	}    
    
    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw generic suburban home                                    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding5(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtmnotop(  0,  .2, 0,  .3, .2, .35, colorwhite);
    makeitPyr(1, colorgrey2,  0,  .5, 0,  .35, .1, .45);
    makercubenobtm(  .2,  .4, 0,  .03, .2, .05, colorwhite);

    if (detail > 0)
	{    
	glColor3fv(colorblack);

	wxminus(-0.303,  0.15, -0.15,  0.15,  0.05);
	wxplus(  0.303,  0.25,  0.15,  0.05,  0.05);
	wzminus(-0.15,   0.25, -0.352, 0.05,  0.05);
	wzminus( 0.0,    0.25, -0.352, 0.05,  0.05);
	wzplus(  0.15,   0.25,  0.352, 0.05,  0.05);
	}
    
    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw granite monument                                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding7()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makeitPyr(3, colorgrey2, 0.0, 0.4, 0.0, 0.3, 0.4, 0.3);
    
    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw water tower                                              */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding9(int lowDetail)
    {
    GLuint O;
    GLUquadricObj *qobj;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

     
    glPushMatrix();
	glTranslatef(-0.3,  1,  -0.3);
	glScalef(.3,  .2,  .3);
	
	if (lowDetail)
	    drawClosedCylinder(colorgrey1,  colorwhite,  1, -1);
	else
	    drawClosedCylinder(colorgrey1,  colorwhite,  1, 1);

    glPopMatrix();
  
    glPushMatrix();
	glTranslatef(-0.1,  0.5,  -0.1);
	glScalef(0.1,  0.5,  0.1);

	if (lowDetail)
	    drawClosedCylinder(colorgrey3,  colorwhite,  1, -1);
	else
	    drawClosedCylinder(colorgrey3,  colorwhite,  1, 1);
   glPopMatrix();
  
    makercubenobtm(-0.22,  0.5, -0.22,  0.025, 0.5, 0.025, colorgrey2);
    makercubenobtm( 0.22,  0.5, -0.22,  0.025, 0.5, 0.025, colorgrey2);
    makercubenobtm(-0.22,  0.5,  0.22,  0.025, 0.5, 0.025, colorgrey2);
    makercubenobtm( 0.22,  0.5,  0.22,  0.025, 0.5, 0.025, colorgrey2);
     
    makercube(-0.2,  0.4,  0.0,  0.015, 0.015, 0.2, colorgrey3);
    makercube( 0.2,  0.4,  0.0,  0.015, 0.015, 0.2, colorgrey3);
    makercube( 0.0,  0.4,  0.2,  0.2,   0.015, 0.015, colorgrey3);
    makercube( 0.0,  0.4, -0.2,  0.2,   0.015, 0.015, colorgrey3);
   
    glPushMatrix();
	glColor3fv(colorblack);
	glRotatef(-90, 1, 0, 0);

	qobj = gluNewQuadric();
	gluDisk( qobj, 0.,   0.3, 32, 1);
	gluDeleteQuadric(qobj);

    glPopMatrix();
     
    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw construction                                             */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding10()
    {
    GLuint O;

    /****************/
    /* construction */
    /****************/

    float cons1[3] = {-0.29, 0.1, -0.29};
    float cons2[3] = {-0.29, 0.8, -0.29};
    float cons3[3] = { 0.29, 0.1, -0.29};
    float cons4[3] = { 0.29, 0.8, -0.29};
    float cons5[3] = { 0.29, 0.1,  0.29};
    float cons6[3] = { 0.29, 0.8,  0.29};
    float cons7[3] = {-0.29, 0.1,  0.29};
    float cons8[3] = {-0.29, 0.8,  0.29};

    float cons9[3] = {-0.29, 0.45, -0.29};
    float cons10[3] ={-0.29, 0.45,  0.29};
    float cons11[3] ={ 0.29, 0.45,  0.29};
    float cons12[3] ={ 0.29, 0.45, -0.29};

    float cons13[3] ={ 0.0, 0.45, -0.29};
    float cons14[3] ={ 0.0, 0.45,  0.29};
    float cons15[3] ={ 0.0, 0.8,   0.29};
    float cons16[3] ={ 0.0, 0.8,  -0.29};

    float cons17[3] ={-0.29, 0.45, 0.0};
    float cons18[3] ={ 0.29, 0.45, 0.0};
    float cons19[3] ={ 0.29, 0.8,  0.0};
    float cons20[3] ={-0.29, 0.8,  0.0};
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtm(  0,  .05, 0,  .3, .05, .3, colorwhite);

    glColor3fv(colorgrey1);
    glLineWidth(2.01);
    
    glBegin(GL_LINES);
	glVertex3fv(cons1);
	glVertex3fv(cons2);

	glVertex3fv(cons3);
	glVertex3fv(cons4);

	glVertex3fv(cons5);
	glVertex3fv(cons6);

	glVertex3fv(cons7);
	glVertex3fv(cons8);
    glEnd();


    glBegin(GL_LINE_LOOP);
	glVertex3fv(cons2);
	glVertex3fv(cons8);
	glVertex3fv(cons6);
	glVertex3fv(cons4);
    glEnd();

    glBegin(GL_LINE_LOOP);
	glVertex3fv(cons9);
	glVertex3fv(cons10);
	glVertex3fv(cons11);
	glVertex3fv(cons12);
    glEnd();

    glBegin(GL_LINE_LOOP);
	glVertex3fv(cons13);
	glVertex3fv(cons14);
	glVertex3fv(cons15);
	glVertex3fv(cons16);
    glEnd();

    glBegin(GL_LINE_LOOP);
	glVertex3fv(cons17);
	glVertex3fv(cons18);
	glVertex3fv(cons19);
	glVertex3fv(cons20);
    glEnd();

    glEndList();    

    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw factory                                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
   
GLuint makebuilding12(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercubenobtm(  0,  .4, 0,  .3, .4, .3, colorbrown);
    makercubenobtmnotop(  0,  .5, 0.02,  .302, .1, .3, colorblack);

    if (detail > 0)
	{
	glColor3fv(colorblack);

	wxplus(0.303,  .15,  -.15,  .15,  .05);
	wxminus(-0.303,  .15,  -.15,  .15,  .05);
	}

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw control tower                                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding14()
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    makercubenobtmnotop(  0,  .55, 0,  .15, .55, .15, colorbeige);
    makercubenobtm(  0,  1.55, 0,  .3, .05, .3, colorbeige);
    
    makeitPyr(5, colorbrown,  0,  1.1, 0,  .3, .4, .3);
    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw end of city hall                                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding19(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtmnotop(  0,  .3, 0,  .3, .3, .3, colorbrown);
    makeitPyr(4, colorbeige,  0,  .7, 0,  .3, .1, .3);

    if (detail > 0)
	{    
	glColor3fv(colorblack);

	wxplus(.303,  .4,  -.15,  .08,  .05);
	wxplus(.303,  .2,  -.15,  .08,  .05);
	wxplus(.303,  .4,  +.15,  .08,  .05);
	wxplus(.303,  .2,  +.15,  .08,  .05);

	wxminus(-.303,  .4,  -.15,  .08,  .05);
	wxminus(-.303,  .2,  -.15,  .08,  .05);
	wxminus(-.303,  .4,  +.15,  .08,  .05);
	wxminus(-.303,  .2,  +.15,  .08,  .05);
	}

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw middle of city hall                                      */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
   
GLuint makebuilding20(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    makercubenobtmnotop(  0,  .3, 0,  .3, .3, .3, colorbrown);
    makeitPyr(4, colorbeige,  0,  .7, 0,  .3, .1, .3);
    makeitPyr(6, colorbeige,  0,  .7, 0,  .3, .1, .3);

    if (detail > 0)
	{    
	glColor3fv(colorblack);

	wxplus(.303,  .4,  -.15,  .08,  .05);
	wxplus(.303,  .2,  -.15,  .08,  .05);
	wxplus(.303,  .4,  +.15,  .08,  .05);
	wxplus(.303,  .2,  +.15,  .08,  .05);

	wxminus(-.303,  .4,  -.15,  .08,  .05);
	wxminus(-.303,  .2,  -.15,  .08,  .05);
	wxminus(-.303,  .4,  +.15,  .08,  .05);
	wxminus(-.303,  .2,  +.15,  .08,  .05);
	}

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw front of city hall                                       */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding21(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtmnotop(  -.2,  .3, 0,  .1, .3, .3, colorbrown);
    makeitPyr(6, colorbeige,  0,  .7, 0,  .3, .1, .3);
    makercubenobtm(  0,  .05, 0,  .29, .05, .29, colorgrey1);

    if (detail > 0)
	{    
	glColor3fv(colorblack);

	wxplus(-.098,  .22,  -.10,  .12,  .05);
	wxplus(-.098,  .22,  +.10,  .12,  .05);

	wxminus(-.303,  .4,  -.15,  .08,  .05);
	wxminus(-.303,  .2,  -.15,  .08,  .05);
	wxminus(-.303,  .4,  +.15,  .08,  .05);
	wxminus(-.303,  .2,  +.15,  .08,  .05);
	}

    makercubenobtmnotop(  0.25,  .3, 0.25,  .03, .3, .03, colorwhite);
    makercubenobtmnotop(  0.25,  .3, -0.25,  .03, .3, .03, colorwhite);

    makercubenobtmnotop(  0.0,  .3, 0.25,  .03, .3, .03, colorwhite);
    makercubenobtmnotop(  0.0,  .3, -0.25,  .03, .3, .03, colorwhite);

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw maser emplacement                                        */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding31()
    {
    GLUquadricObj *qobj;
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    makercubenobtm(  0,  .095, 0,  .36, .095, .36, colorgrey1);

    makercubenobtm(  .35,  .1, .35,  .03, .1, .03, colorblue);
    makercubenobtm(  -.35,  .1, .35,  .03, .1, .03, colorblue);
    makercubenobtm(  .35,  .1, -.35,  .03, .1, .03, colorblue);
    makercubenobtm(  -.35,  .1, -.35,  .03, .1, .03, colorblue);

    glColor3fv(colorwhite);
    
    glPushMatrix();
	glTranslatef(0,  .2,   0);
	glRotatef(-90, 1, 0, 0);

	qobj = gluNewQuadric();
	gluDisk( qobj, 0.,   0.3, 32, 1);
	gluDeleteQuadric(qobj);
    glPopMatrix();

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw helicopter pad                                           */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makebuilding32()
    {
    GLUquadricObj *qobj;
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);
    
    
    makercubenobtm(  0,  .095, 0,  .36, .095, .36, colorgrey1);

    glColor3fv(coloryellow);
    
    glPushMatrix();
	glTranslatef(0,  .2,   0);
	glRotatef(-90, 1, 0, 0);

	qobj = gluNewQuadric();
	gluDisk( qobj, 0.,   0.3, 32, 1);
	gluDeleteQuadric(qobj);
    glPopMatrix();

    glColor3fv(colorgrey1);
    
    glPushMatrix();
	glTranslatef(0,  .21,   0);
	glRotatef(-90, 1, 0, 0);

	qobj = gluNewQuadric();
	gluDisk( qobj, 0.,   0.2, 32, 1);
	gluDeleteQuadric(qobj);
    glPopMatrix();

    glEndList();
    return(O);
    }



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for strip mall store                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeStrip1(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    drawBuilding15(colorwhite,  colorred, detail);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for strip mall store                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeStrip2(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    drawBuilding15(colorgrey2, coloryellow, detail);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* create object for strip mall store                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeStrip3(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    drawBuilding15(colorbeige, colorblue, detail);

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* make object for battalion title                               */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeTitles(int detail)
    {
    GLuint O;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    /*****/
    /* b */
    /*****/

    makerlogo(-3.5,  3.5,  0,  .35, .1,  .2, detail, 0, 1);
    makerlogo(-3.75, 3.75, 0,  .1,  .25, .2, detail, 0, 1);
    makerlogo(-3.25, 3.25, 0,  .1,  .25, .2, detail, 0, 1);
    makerlogo(-3.5,  3.,   0,  .35, .1,  .2, detail, 0, 1);

    /*****/
    /* a */
    /*****/

    makerlogo(-2.5,  3.5,  0,  .35,  .1,  .2, detail, 0, 1);
    makerlogo(-2.75, 3.25, 0,  .1,   .3,  .2, detail, 0, 1);
    makerlogo(-2.25, 3.25, 0,  .1,   .3,  .2, detail, 0, 1);
    makerlogo(-2.65, 3.,   0,  .20,  .1,  .2, detail, 0, 1);

    /*****/
    /* t */
    /*****/

    makerlogo(-1.5,  3.5, 0,  .3,  .1,  .2, detail, 0, 1);
    makerlogo(-1.75, 3.5, 0,  .1,  .6,  .2, detail, 0, 1);
	
    /*****/
    /* t */
    /*****/
	
    makerlogo(-0.5,  3.5, 0,  .3,  .1,  .2, detail, 0, 1);
    makerlogo(-0.75, 3.5, 0,  .1,  .6,  .2, detail, 0, 1);

    /*****/
    /* a */
    /*****/
	
    makerlogo(0.5,  3.5,  0,  .35,  .1,  .2, detail, 1, 0);
    makerlogo(0.25, 3.25, 0,  .1,   .3,  .2, detail, 1, 0);
    makerlogo(0.75, 3.25, 0,  .1,   .3,  .2, detail, 1, 0);
    makerlogo(0.35, 3.,   0,  .20,  .1,  .2, detail, 1, 0);

    /*****/
    /* l */
    /*****/

    makerlogo(1.25, 3.5, 0,  .1,  .6,  .2, detail, 1, 0);
	
    /*****/
    /* i */
    /*****/

    makerlogo(1.75, 3.25, 0,  .1,  .35,  .2, detail, 1, 0);
	
    /*****/
    /* o */
    /*****/

    makerlogo(2.5,  3.5,  0,  .35,  .1,  .2, detail, 1, 0);
    makerlogo(2.25, 3.25, 0,  .1,   .3,  .2, detail, 1, 0);
    makerlogo(2.75, 3.25, 0,  .1,   .3,  .2, detail, 1, 0);
    makerlogo(2.5,  3,    0,  .35,  .1,  .2, detail, 1, 0);
	
    /*****/
    /* n */
    /*****/

    makerlogo(3.5,  3.5,  0,  .35,  .1,   .2, detail, 1, 0);
    makerlogo(3.25, 3.25, 0,  .1,   .35,  .2, detail, 1, 0);
    makerlogo(3.75, 3.25, 0,  .1,   .35,  .2, detail, 1, 0);

    glEndList();
    return(O);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeBigPlane()
    {
    GLuint O;

    /*******************************/
    /* the battlefield in map view */
    /*******************************/

    float Bplane[4][3] = {
	- 200,  PLANEY,  - 200, 
	- 200,  PLANEY,  + 200, 
	+ 200,  PLANEY,  + 200, 
	+ 200,  PLANEY,  - 200};

    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glBegin(GL_QUADS);
	glVertex3fv(Bplane[0]);
	glVertex3fv(Bplane[1]);
	glVertex3fv(Bplane[2]);
	glVertex3fv(Bplane[3]);
    glEnd();

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeLowDPlane()
    {
    GLuint O;

    /********************/
    /* the battlefield  */
    /********************/

    float Gplane[4][3] = {
	- PLANESIZE,  PLANEY,  - PLANESIZE, 
	- PLANESIZE,  PLANEY,  + PLANESIZE, 
	+ PLANESIZE,  PLANEY,  + PLANESIZE, 
	+ PLANESIZE,  PLANEY,  - PLANESIZE};

    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glBegin(GL_QUADS);
	glVertex3fv(Gplane[0]);
	glVertex3fv(Gplane[1]);
	glVertex3fv(Gplane[2]);
	glVertex3fv(Gplane[3]);
    glEnd();

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeHighDPlane()
    {
    GLuint O;
    float ratio;
    register int i, j;
    float plane[4][3];

    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

	ratio = PLANESIZE * 0.1;
	plane[0][1] = plane[1][1] = plane[2][1] = plane[3][1] = PLANEY;

	for (i=0;i<=19;i++)
	    for(j=0;j<=19;j++)
		{
		plane[0][0] = plane[1][0] = (i*ratio) - PLANESIZE;
		plane[2][0] = plane[3][0] = ((i+1)*ratio) - PLANESIZE;

		plane[0][2] = plane[3][2] = (j*ratio) - PLANESIZE;
		plane[1][2] = plane[2][2] = ((j+1)*ratio) - PLANESIZE;
		
		glBegin(GL_QUADS);
		    glVertex3fv(plane[0]);
		    glVertex3fv(plane[1]);
		    glVertex3fv(plane[2]);
		    glVertex3fv(plane[3]);
		glEnd();
		}

    glEndList();
    return(O);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makePlaneDots(int detail)
    {
    GLuint O;
    float grass1[3], grass2[3], grass3[3], grass4[3];
    register int j, i;

    grass1[1] = grass2[1] = grass3[1] = grass4[1] = PLANEY;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    if (detail == 0)
	{
	glBegin(GL_POINTS);
	for(i=-PLANESIZE+1; i<=PLANESIZE; i+=1)
	    {
	    grass1[0] = i;

	    for(j=-PLANESIZE + 1; j <= PLANESIZE; j += 1)
		{
		grass1[2] = j;

		glVertex3fv(grass1); 	/* a single point */
		}
	    }
	}
    else
	{
	glBegin(GL_LINES);
	for(i=-PLANESIZE+1; i<=PLANESIZE; i+=1)
	    {
	    grass1[0] = grass3[0] = i - 0.015;
	    grass2[0] = grass4[0] = i + 0.015;

	    for(j=-PLANESIZE + 1; j <= PLANESIZE; j += 1)
		{
		grass1[2] = grass4[2] = j - 0.015;
		grass2[2] = grass3[2] = j + 0.015;

		glVertex3fv(grass1);
		glVertex3fv(grass2);

		glVertex3fv(grass3);
		glVertex3fv(grass4);
		}
	    }
	}    
    glEnd();

    glEndList();
    return(O);
    }



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

GLuint makeRoundTreeShadow()
    {
    GLuint O;
    GLUquadricObj *qobj;
    
    O = glGenLists(1);
    glNewList(O, GL_COMPILE);

    glRotatef(-90, 1, 0, 0);

    qobj = gluNewQuadric();
    gluDisk( qobj, 0.,  0.3, 32, 1);
    gluDeleteQuadric(qobj);

    glEndList();
    return(O);
    }

