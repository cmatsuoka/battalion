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
/* gprim.c  v 1.3                                                      */
/* primitive graphics routines for battalion                           */
/***********************************************************************/

#include "battalion.h"

    GLUquadricObj *qobj;

    float   pt1[3] = {1, -1, 1};
    float   pt2[3] = {1, 1, 1};

    /*****************/
    /* damaged cubes */
    /*****************/

    float dcube[8][3] = {
	-1.0,  1.0,  0.6,
	-0.7, -0.9,  1.1,
	 0.8, -1.0,  0.9, 
	 1.0,  0.5,  1.0,
  	 0.9,  0.7, -1.0,
	 1.0, -1.1, -0.8,
	-1.0, -0.8, -0.7,
	-0.6,  1.0, -0.9 };

    float dcube2[8][3] = {
	-0.8,  0.9,  1.0,
	-1.0, -1.0,  0.5,
	 1.0, -0.9,  0.8, 
	 0.7,  1.0,  1.1,
  	 0.7,  0.9, -0.9,
	 1.1, -0.8, -1.0,
	-0.7, -0.9, -0.9,
	-0.9,  0.9, -1.0 };

    /************/
    /* pyramids */
    /************/

    float pyramid[8][3] = {
	-0.1,  1.0,  0.1,
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0, 
	 0.1,  1.0,  0.1,
  	 0.1,  1.0, -0.1,
	 1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	-0.1,  1.0, -0.1 };

    float pyramid2[8][3] = {
	-1.0,  1.0,  1.0,
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0, 
	 1.0,  1.0,  1.0,
  	 0.2,  0.2, -1.0,
	 0.2, -0.2, -1.0,
	-0.2, -0.2, -1.0,
	-0.2,  0.2, -1.0 };

    float pyramid3[8][3] = {
	-0.4,  1.0,  0.4,
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0, 
	 0.4,  1.0,  0.4,
  	 0.4,  1.0, -0.4,
	 1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	-0.4,  1.0, -0.4 };

    float pyramid4[8][3] = {
	-0.1,  1.0,  1.0,
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0, 
	 0.1,  1.0,  1.0,
  	 0.1,  1.0, -1.0,
	 1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	-0.1,  1.0, -1.0 };

    float pyramid5[8][3] = {
	-1,    1.0,  1,
	 0,   -1.0,  0,
	 0,   -1.0,  0, 
	 1,    1.0,  1,
  	 1,    1.0, -1,
	 0,   -1.0,  0,
	 0,   -1.0,  0,
	-1,    1.0, -1 };

    float pyramid6[8][3] = {
	-1.0,  1.0,  0.1,
	-1.0, -1.0,  1.0,
	 1.0, -1.0,  1.0, 
	 1.0,  1.0,  0.1,
  	 1.0,  1.0, -0.1,
	 1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	-1.0,  1.0, -0.1 };

    float pyramid7[8][3] = {
	0,     1,  1,
	0,    -1,  1,
	1,     0,  0, 
	1,     0,  0,
  	1,     0,  0,
	1,     0,  0,
	0,    -1, -1,
	0,     1, -1 };

    float pyramid8[8][3] = {
	-1,    0,  0,
	-1,    0,  0,
	 0,   -1,  1, 
	 0,    1,  1,
  	 0,    1, -1,
	 0,   -1, -1,
	-1,    0,  0,
	-1,    0,  0};

    float pyramid9[8][3] = {
	 0,    1,  1.0,
	 0,   -1,  1.0,
	 1,   -1,  0.3, 
	 1,    1,  0.3,
  	 1,    1, -0.3,
	 1,   -1, -0.3,
	 0,   -1, -1.0,
	 0,    1, -1.0 };

  float pyramid10[8][3] = {
	-1,    1,  0.3,
	-1,   -1,  0.3,
	 0,   -1,  1.0, 
	 0,    1,  1.0,
  	 0,    1, -1.0,
	 0,   -1, -1.0,
	-1,   -1, -0.3,
	-1,    1, -0.3};

    float pyramid11[8][3] = {
	-1.0,  1.0,  1.0,
	-1.0, -1.0,  0.8,
	 1.0, -1.0,  0.8, 
	 1.0,  1.0,  1.0,
  	 1.0,  1.0, -1.0,
	 1.0, -1.0, -0.8,
	-1.0, -1.0, -0.8,
	-1.0,  1.0, -1.0 };

    float pyramid13[8][3] = {
	-0.1,  1.0,  1.0,
	-0.1, -1.0,  1.0,
	 1.0, -1.0,  1.0, 
	 0.1,  1.0,  1.0,
  	 0.1,  1.0, -1.0,
	 1.0, -1.0, -1.0,
	-0.1, -1.0, -1.0,
	-0.1,  1.0, -1.0 };


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a vertical cylinder                                      */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawCylinder(float * outcol, float * topcol, float radius,
		    int nsides,  int top, int detail)
    {    
    float   v0[3], v1[3], v2[3], v3[3];
    float   theta, theta1;
    float   costheta, costheta1;
    float   costhetahalf, costheta1half;
    float   col[4], col2[4];
    float   curve;
    register int edge;
    
    v0[1] = v3[1] = -1;
    v1[1] = v2[1] = 1;

    if (nsides < 3)
	nsides = 3;
    
    curve = 2 * PI / nsides;
    col[3] = col2[3] = outcol[3];

    if (detail < 0)
	{
	col[0] = col2[0] = outcol[0];
	col[1] = col2[1] = outcol[1];
	col[2] = col2[2] = outcol[2];
	}
	
    for (edge = 0; edge < nsides; edge++)
	{
	theta = edge * curve;
	theta1 = (edge+1) * curve;
	
	costheta = cos(theta);
	costheta1 = cos(theta1);
	
	costhetahalf  = costheta * 0.5;
	costheta1half = costheta1 * 0.5;
	
	v0[0] = v1[0] = 1 - sin(theta) * radius;
	v2[0] = v3[0] = 1 - sin(theta1) * radius;

	v0[2] = v1[2] = 1 + costheta * radius;
	v2[2] = v3[2] = 1 + costheta1 * radius;

	if (detail >= 0)
	    {
	    col[0] = (outcol[0] + costhetahalf);
	    col[1] = (outcol[1] + costhetahalf);
	    col[2] = (outcol[2] + costhetahalf);
	    
	    if (col[0] > 1)
		col[0] = 1;
	    if (col[1] > 1)
		col[1] = 1;
	    if (col[2] > 1)
		col[2] = 1;
	    
	    col2[0] = (outcol[0] + costheta1half);
	    col2[1] = (outcol[1] + costheta1half);
	    col2[2] = (outcol[2] + costheta1half);
    
	    if (col2[0] > 1)
		col2[0] = 1;
	    if (col2[1] > 1)
		col2[1] = 1;
	    if (col2[2] > 1)
		col2[2] = 1;

	    glColor4fv(col);
	    }

	glBegin(GL_QUADS);
	    glVertex3fv(v0);
	    glVertex3fv(v1);
			    
	    glColor4fv(col2);

	    glVertex3fv(v2);
	    glVertex3fv(v3);
	glEnd();

	/*******/
	/* top */
	/*******/

	if (detail >= 0)
	    {
	    glColor4fv(topcol);
	    }
	    
	if (top)
	    {
	    glBegin(GL_TRIANGLES);
		glVertex3fv(pt2);
		glVertex3fv(v2);
		glVertex3fv(v1);
	    glEnd();
	    }

	/**********/
	/* bottom */
	/**********/
	    
	glBegin(GL_TRIANGLES);
	    glVertex3fv(pt1);
	    glVertex3fv(v0);
	    glVertex3fv(v3); 
	glEnd();
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawClosedCylinder(float * outcol, float * topcol,
			int top, int detail)
    {
    GLint shadeNow;
    long backNow;

    glGetIntegerv(GL_SHADE_MODEL, &shadeNow);
    backNow = glIsEnabled(GL_CULL_FACE);
    
/*    glShadeModel(GL_SMOOTH); */
    glDisable(GL_CULL_FACE);
    
    switch (detail)
	{
	case 2:	    drawCylinder(outcol, topcol, 1, MORECYLINDERSIDES, top, detail);
		    break;
	case 1:
	case 0:	    
	case -1:    drawCylinder(outcol, topcol, 1, CYLINDERSIDES, top, detail);
		    break;
	}
	
    if (backNow)
	glEnable(GL_CULL_FACE);
    else
	glDisable(GL_CULL_FACE);
	
    glShadeModel(shadeNow);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a vertical cone                                          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawCone(float * outcol, float * topcol, float radius, int nsides, int top)
    {
    float   n1a,  n1b,  n2a,  n2b;
    float   v0[3], v1[3], v2[3], v3[3];
    float   theta, theta1;
    float   costheta, costheta1;
    float   col[4], col2[4];
    float   curve;
    int	    edge;
    
    v0[1] = v3[1] = -1;
    v1[1] = v2[1] = 1;

  if (nsides < 3)
	nsides = 3;
     
    curve = 2 * PI / nsides;

	for (edge = 0;  edge < nsides; edge++)
	    {
	    theta = edge * curve;
	    theta1 = (edge+1) * curve;

	    costheta = cos(theta);
	    costheta1 = cos(theta1);

	    n1a = -sin(theta) * radius;
	    n2a = -sin(theta1) * radius;

	    n1b = costheta *radius;
	    n2b = costheta1 *radius;

	    col[0] = (outcol[0] + costheta * 0.1);
	    col[1] = (outcol[1] + costheta * 0.1);
	    col[2] = (outcol[2] + costheta * 0.1);

	    if (col[0] > 1)
		col[0] = 1;
	    if (col[1] > 1)
		col[1] = 1;
	    if (col[2] > 1)
		col[2] = 1;

	    col2[0] = (outcol[0] + costheta1 * 0.1);
	    col2[1] = (outcol[1] + costheta1 * 0.1);
	    col2[2] = (outcol[2] + costheta1 * 0.1);

	    if (col2[0] > 1)
		col2[0] = 1;
	    if (col2[1] > 1)
		col2[1] = 1;
	    if (col2[2] > 1)
		col2[2] = 1;

	    v0[0] = 1 + n1a;
	    v1[0] = 1 + n1a/6;
	    v0[2] = 1 + n1b;
	    v1[2] = 1 + n1b/6;

	    v2[0] = 1 + n2a/6;
	    v3[0] = 1 + n2a;
	    v2[2] = 1 + n2b/6;
	    v3[2] = 1 + n2b;

	    glColor3fv(col);

	    glBegin(GL_QUADS);
		glVertex3fv(v0);
		glVertex3fv(v1);
		       		
		glColor3fv(col2);

		glVertex3fv(v2);
		glVertex3fv(v3);
	    glEnd();

	    glColor3fv(topcol);
		
	    if (top)
		{
		glBegin(GL_TRIANGLES);
		    glVertex3fv(pt2);
		    glVertex3fv(v2);
		    glVertex3fv(v1);
		glEnd();
		}
		
	    glBegin(GL_TRIANGLES);
		glVertex3fv(pt1);
		glVertex3fv(v0);
		glVertex3fv(v3); 
	    glEnd();
	}
   }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void drawClosedCone(float * outcol, float * topcol,  int top)
    {
    GLint shadeNow;
    long backNow;
    
    glGetIntegerv(GL_SHADE_MODEL, &shadeNow);
    backNow = glIsEnabled(GL_CULL_FACE);

    glShadeModel(GL_SMOOTH);
    glDisable(GL_CULL_FACE);
 
    drawCone(outcol,  topcol,  1, MORECYLINDERSIDES,  top);
	
    if (backNow)
	glEnable(GL_CULL_FACE);
    else
	glDisable(GL_CULL_FACE);
	
    glShadeModel(shadeNow);
     }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a generic6 sided object (box, damaged box, pyramid)      */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void maker(float tail2[8][3], float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4],  float d1,  float d2,  float d3,  float d4)
    {
    float c1[4],  c2[4],  c3[4],  c4[4];
    float tail1[8][3];

    tail1[0][0] = tail2[0][0] * u + x;
    tail1[0][1] = tail2[0][1] * v + y;
    tail1[0][2] = tail2[0][2] * w + z;
    tail1[1][0] = tail2[1][0] * u + x;
    tail1[1][1] = tail2[1][1] * v + y;
    tail1[1][2] = tail2[1][2] * w + z;
    tail1[2][0] = tail2[2][0] * u + x;
    tail1[2][1] = tail2[2][1] * v + y;
    tail1[2][2] = tail2[2][2] * w + z;
    tail1[3][0] = tail2[3][0] * u + x;
    tail1[3][1] = tail2[3][1] * v + y;
    tail1[3][2] = tail2[3][2] * w + z;
    tail1[4][0] = tail2[4][0] * u + x;
    tail1[4][1] = tail2[4][1] * v + y;
    tail1[4][2] = tail2[4][2] * w + z;
    tail1[5][0] = tail2[5][0] * u + x;
    tail1[5][1] = tail2[5][1] * v + y;
    tail1[5][2] = tail2[5][2] * w + z;
    tail1[6][0] = tail2[6][0] * u + x;
    tail1[6][1] = tail2[6][1] * v + y;
    tail1[6][2] = tail2[6][2] * w + z;
    tail1[7][0] = tail2[7][0] * u + x;
    tail1[7][1] = tail2[7][1] * v + y;
    tail1[7][2] = tail2[7][2] * w + z;


    c1[3] = c2[3] = c3[3] = c4[3] = c[3];   
    c1[0] = c[0]*d1;
    c1[1] = c[1]*d1;
    c1[2] = c[2]*d1;

    c2[0] = c[0]*d2;
    c2[1] = c[1]*d2;
    c2[2] = c[2]*d2;

    c3[0] = c[0]*d3;
    c3[1] = c[1]*d3;
    c3[2] = c[2]*d3;

    c4[0] = c[0]*d4;
    c4[1] = c[1]*d4;
    c4[2] = c[2]*d4;

    glBegin(GL_QUAD_STRIP);
	glColor4fv(c2);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glColor4fv(c3);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glColor4fv(c4);
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glColor4fv(c3);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();		
    glColor4fv(c4);

    glBegin(GL_QUADS);
	glVertex3fv(tail1[6]); glVertex3fv(tail1[5]); glVertex3fv(tail1[2]); glVertex3fv(tail1[1]);

	glColor4fv(c1);

	glVertex3fv(tail1[0]); glVertex3fv(tail1[3]); glVertex3fv(tail1[4]); glVertex3fv(tail1[7]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makerVapour(float x,  float y,  float z,
		float u,  float v,  float w)
    {
    float tail1[8][3];

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
	glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();		

    glBegin(GL_QUADS);
	glVertex3fv(tail1[6]); glVertex3fv(tail1[5]);
	glVertex3fv(tail1[2]); glVertex3fv(tail1[1]);

	glVertex3fv(tail1[0]); glVertex3fv(tail1[3]);
	glVertex3fv(tail1[4]); glVertex3fv(tail1[7]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a damaged box                                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makeitd(int matrx,  float * color,  float x,  float y,  float z,
		float u,  float v,  float w)
    {
    if (matrx == 0)
	maker(dcube, x, y, z, u, v, w, color, 0.4, 0.3, 0.2, 0.1);
    else
	maker(dcube2, x, y, z, u, v, w, color, 0.4, 0.3, 0.2, 0.1);
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makerP(float tail2[8][3], float c[4], float x,  float y,  float z,
		float u,  float v,  float w)
    {
    float c1[4],  c2[4],  c3[4],  c4[4];
    float tail1[8][3];

    tail1[0][0] = tail2[0][0] * u + x;
    tail1[0][1] = tail2[0][1] * v + y;
    tail1[0][2] = tail2[0][2] * w + z;
    tail1[1][0] = tail2[1][0] * u + x;
    tail1[1][1] = tail2[1][1] * v + y;
    tail1[1][2] = tail2[1][2] * w + z;
    tail1[2][0] = tail2[2][0] * u + x;
    tail1[2][1] = tail2[2][1] * v + y;
    tail1[2][2] = tail2[2][2] * w + z;
    tail1[3][0] = tail2[3][0] * u + x;
    tail1[3][1] = tail2[3][1] * v + y;
    tail1[3][2] = tail2[3][2] * w + z;
    tail1[4][0] = tail2[4][0] * u + x;
    tail1[4][1] = tail2[4][1] * v + y;
    tail1[4][2] = tail2[4][2] * w + z;
    tail1[5][0] = tail2[5][0] * u + x;
    tail1[5][1] = tail2[5][1] * v + y;
    tail1[5][2] = tail2[5][2] * w + z;
    tail1[6][0] = tail2[6][0] * u + x;
    tail1[6][1] = tail2[6][1] * v + y;
    tail1[6][2] = tail2[6][2] * w + z;
    tail1[7][0] = tail2[7][0] * u + x;
    tail1[7][1] = tail2[7][1] * v + y;
    tail1[7][2] = tail2[7][2] * w + z;

    c1[3] = c2[3] = c3[3] = c4[3] = c[3];   
    c1[0] = c[0];
    c1[1] = c[1];
    c1[2] = c[2];

    c2[0] = c[0]*0.8;
    c2[1] = c[1]*0.8;
    c2[2] = c[2]*0.8;

    c3[0] = c[0]*0.66;
    c3[1] = c[1]*0.66;
    c3[2] = c[2]*0.66;

    c4[0] = c[0]*0.5;
    c4[1] = c[1]*0.5;
    c4[2] = c[2]*0.5;

    glBegin(GL_QUAD_STRIP);
	glColor4fv(c2);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glColor4fv(c3);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glColor4fv(c4);
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glColor4fv(c3);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();		
    glColor4fv(c4);

    glBegin(GL_QUADS);
	glVertex3fv(tail1[6]); glVertex3fv(tail1[5]); glVertex3fv(tail1[2]); glVertex3fv(tail1[1]);

	glColor4fv(c1);

	glVertex3fv(tail1[0]); glVertex3fv(tail1[3]); glVertex3fv(tail1[4]); glVertex3fv(tail1[7]);
    glEnd();
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makerFire(float c[4], float x,  float y,  float z,
		float u,  float v,  float w)
    {
    float tail1[8][3];

    tail1[0][0] = tail1[3][0] = tail1[4][0] = tail1[7][0] = x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;
    tail1[0][2] = tail1[3][2] = tail1[4][2] = tail1[7][2] = z;
    tail1[1][0] = tail1[6][0] = - u + x;
    tail1[1][1] = tail1[2][1] = - v + y;
    tail1[1][2] = tail1[2][2] = w + z;
    tail1[2][0] = tail1[5][0] = u + x;
    tail1[5][1] = tail1[6][1] = - v + y;
    tail1[5][2] = tail1[6][2] = - w + z;
    
    
    glColor4fv(c);

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();		
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a pyramid                                                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makeitPyr(int type,  float * color,  float x,  float y,  float z,
		float u,  float v,  float w)
    {
    switch(type){
 	case 12:makerFire(color, x, y, z, u, v, w);
		break;
	case 1:	makerP(pyramid, color, x, y, z, u, v, w);
		break;
	case 2:	makerP(pyramid2, color, x, y, z, u, v, w);
		break;
	case 3:	makerP(pyramid3, color, x, y, z, u, v, w);
		break;
	case 4:	makerP(pyramid4, color, x, y, z, u, v, w);
		break;
	case 5:	makerP(pyramid5, color, x, y, z, u, v, w);
		break;
	case 6:	makerP(pyramid6, color, x, y, z, u, v, w);
		break;
	case 7:	makerP(pyramid7, color, x, y, z, u, v, w);
		break;
 	case 8:	makerP(pyramid8, color, x, y, z, u, v, w);
		break;
 	case 9:	makerP(pyramid9, color, x, y, z, u, v, w);
		break;
 	case 10:makerP(pyramid10, color, x, y, z, u, v, w);
		break;
 	case 11:makerP(pyramid11, color, x, y, z, u, v, w);
		break;
 	case 13:makerP(pyramid13, color, x, y, z, u, v, w);
		break;

	default:showError("Bogus Pyramid Type! (makeitPyr)");
		break;
    }
}

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makerlogo(float x,  float y,  float z,
	       float u,  float v,  float w, int detail, int l, int r)
    {
    float c[3] = {1, 1, 1};
    float c3[3] = {0.7, 0.7, 0.7};
    float c5[3] ={0, 0, 0};
    float tail1[8][3];

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;
    

    glBegin(GL_QUADS);

	if (detail != -1)
	    {
	    glColor3fv(c);
    
	    /* right */
    
	    if (r)
		{
		glVertex3fv(tail1[3]); glVertex3fv(tail1[2]);
		glVertex3fv(tail1[5]); glVertex3fv(tail1[4]);
		}
    
	    /* left */
    
	    if (l)
		{
		glVertex3fv(tail1[7]); glVertex3fv(tail1[6]);
		glVertex3fv(tail1[1]); glVertex3fv(tail1[0]);
		}
    
	    if (detail > 0)
		glColor3fv(c3);
    
	    /* bottom */
		    
	    glVertex3fv(tail1[6]); glVertex3fv(tail1[5]);
	    glVertex3fv(tail1[2]); glVertex3fv(tail1[1]);
	    }
	    
	if (detail == -1)
	    glColor4fv(c3);
	else
	    glColor4fv(c5);

	/* front */

	glVertex3fv(tail1[0]); glVertex3fv(tail1[1]);
	glVertex3fv(tail1[2]); glVertex3fv(tail1[3]);

    glEnd();
    
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a cube                                                   */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makercube(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4])
    {
    float c2[4],  c3[4],  c4[4];
    float tail1[8][3];

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;
    
    c2[3] = c3[3] = c4[3] = c[3];   

    c2[0] = c[0]*0.8;
    c2[1] = c[1]*0.8;
    c2[2] = c[2]*0.8;

    c3[0] = c[0]*0.66;
    c3[1] = c[1]*0.66;
    c3[2] = c[2]*0.66;

    c4[0] = c[0]*0.5;
    c4[1] = c[1]*0.5;
    c4[2] = c[2]*0.5;

    glBegin(GL_QUAD_STRIP);
	glColor4fv(c2);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glColor4fv(c3);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glColor4fv(c4);
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glColor4fv(c3);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();	
    	
    glColor4fv(c4);

    glBegin(GL_QUADS);
	glVertex3fv(tail1[6]); glVertex3fv(tail1[5]); glVertex3fv(tail1[2]); glVertex3fv(tail1[1]);
    
	glColor4fv(c);

	glVertex3fv(tail1[0]); glVertex3fv(tail1[3]); glVertex3fv(tail1[4]); glVertex3fv(tail1[7]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makerbluecube(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4])
    {
    float tail1[8][3];

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;
    
    glColor4fv(c);

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();	
    	

    glBegin(GL_QUADS);
	glVertex3fv(tail1[6]); glVertex3fv(tail1[5]); glVertex3fv(tail1[2]); glVertex3fv(tail1[1]);
	glVertex3fv(tail1[0]); glVertex3fv(tail1[3]); glVertex3fv(tail1[4]); glVertex3fv(tail1[7]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a cube with only a back and a top (for monsterview goog) */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makercubeTopBack(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4])
    {
    float c4[4];
    float tail1[8][3];

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;
 
    c4[0] = c[0]*0.5;
    c4[1] = c[1]*0.5;
    c4[2] = c[2]*0.5;
    c4[3] = c[3];   

    glBegin(GL_QUAD_STRIP);
	glColor4fv(c);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[3]); 
	glVertex3fv(tail1[7]);glVertex3fv(tail1[4]);
	glColor4fv(c4);
	glVertex3fv(tail1[6]);glVertex3fv(tail1[5]);
    glEnd();	
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a cube with no bottom                                    */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makercubenobtm(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4])
    {
    float c2[4],  c3[4],  c4[4];
    float tail1[8][3];

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;


    c2[3] = c3[3] = c4[3] = c[3];   

    c2[0] = c[0]*0.8;
    c2[1] = c[1]*0.8;
    c2[2] = c[2]*0.8;

    c3[0] = c[0]*0.66;
    c3[1] = c[1]*0.66;
    c3[2] = c[2]*0.66;

    c4[0] = c[0]*0.5;
    c4[1] = c[1]*0.5;
    c4[2] = c[2]*0.5;

    glBegin(GL_QUAD_STRIP);
	glColor4fv(c2);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glColor4fv(c3);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glColor4fv(c4);
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glColor4fv(c3);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();	
    	
    glColor4fv(c);

    glBegin(GL_QUADS);
	glVertex3fv(tail1[0]); glVertex3fv(tail1[3]); glVertex3fv(tail1[4]); glVertex3fv(tail1[7]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a cube with no bottom and no top                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makercubenobtmnotop(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4])
    {
    float c2[4],  c3[4],  c4[4];
    float tail1[8][3];

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;


    c2[3] = c3[3] = c4[3] = c[3];   

    c2[0] = c[0]*0.8;
    c2[1] = c[1]*0.8;
    c2[2] = c[2]*0.8;

    c3[0] = c[0]*0.66;
    c3[1] = c[1]*0.66;
    c3[2] = c[2]*0.66;

    c4[0] = c[0]*0.5;
    c4[1] = c[1]*0.5;
    c4[2] = c[2]*0.5;

    glBegin(GL_QUAD_STRIP);
	glColor4fv(c2);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);glVertex3fv(tail1[3]);glVertex3fv(tail1[2]);
	glColor4fv(c3);
	glVertex3fv(tail1[4]);glVertex3fv(tail1[5]); 
	glColor4fv(c4);
	glVertex3fv(tail1[7]);glVertex3fv(tail1[6]);
	glColor4fv(c3);
	glVertex3fv(tail1[0]);glVertex3fv(tail1[1]);
    glEnd();		
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a cube with no bottom and no top assigning texture coords*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makercubenobtmnotopTEX(float x,  float y,  float z,
		float u,  float v,  float w, 
		float c[4])
    {
    float c2[4],  c3[4],  c4[4];
    float tail1[8][3];

    static float tv1[2] = {0,1};
    static float tv2[2] = {1,1};
    static float tv3[2] = {1,0};
    static float tv4[2] = {0,0};

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w + z;    
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u + x;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v + y;  
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = x - u;
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = y - v;
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = z - w;



    c2[3] = c3[3] = c4[3] = c[3];   

    c2[0] = c[0]*0.8;
    c2[1] = c[1]*0.8;
    c2[2] = c[2]*0.8;

    c3[0] = c[0]*0.66;
    c3[1] = c[1]*0.66;
    c3[2] = c[2]*0.66;

    c4[0] = c[0]*0.5;
    c4[1] = c[1]*0.5;
    c4[2] = c[2]*0.5;

    glBegin(GL_QUAD_STRIP);
    
	glColor4fv(c2);
	glTexCoord2fv(tv2);
	glVertex3fv(tail1[0]);
	glTexCoord2fv(tv3);
	glVertex3fv(tail1[1]);
	glTexCoord2fv(tv1);
	glVertex3fv(tail1[3]);
	glTexCoord2fv(tv4);
	glVertex3fv(tail1[2]);
	
	glColor4fv(c3);
	glTexCoord2fv(tv2);
	glVertex3fv(tail1[4]);
	glTexCoord2fv(tv3);
	glVertex3fv(tail1[5]); 
	
	glColor4fv(c4);
	glTexCoord2fv(tv1);
	glVertex3fv(tail1[7]);
	glTexCoord2fv(tv4);
	glVertex3fv(tail1[6]);
	
	glColor4fv(c3);
	glTexCoord2fv(tv2);
	glVertex3fv(tail1[0]);
	glTexCoord2fv(tv3);
	glVertex3fv(tail1[1]);
    glEnd();		
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a cube rotated around the x and y axis                   */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makerrotcubexy(float u,  float v,  float w, 
		float theta, float c[4])
    {
    float c2[4],  c3[4],  c4[4];

    float tail1[8][3];
    float tail2[8][3];
    register int i;
    float thetaRad, cthetarad, sthetarad;
    
    thetaRad = theta * BIG_DEG_TO_RAD;
    cthetarad = cos(thetaRad);
    sthetarad = sin(thetaRad);

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w;    
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = - w;
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u;
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = - u;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v;  
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = - v;
 
    for (i=0;i<8;i++)
	{
	tail2[i][0] = tail1[i][0]*cthetarad + sthetarad*(tail1[i][1]*sthetarad+tail1[i][2]*cthetarad);
	tail2[i][1] = tail1[i][1]*cthetarad - tail1[i][2]*sthetarad;
	tail2[i][2] = -tail1[i][0]*sthetarad + cthetarad*(tail1[i][1]*sthetarad+tail1[i][2]*cthetarad);
	}

    c2[3] = c3[3] = c4[3] = c[3];   

    c2[0] = c[0]*0.8;
    c2[1] = c[1]*0.8;
    c2[2] = c[2]*0.8;

    c3[0] = c[0]*0.66;
    c3[1] = c[1]*0.66;
    c3[2] = c[2]*0.66;

    c4[0] = c[0]*0.5;
    c4[1] = c[1]*0.5;
    c4[2] = c[2]*0.5;

    glBegin(GL_QUAD_STRIP);
	glColor4fv(c2);
	glVertex3fv(tail2[0]);glVertex3fv(tail2[1]);glVertex3fv(tail2[3]);glVertex3fv(tail2[2]);
	glColor4fv(c3);
	glVertex3fv(tail2[4]);glVertex3fv(tail2[5]); 
	glColor4fv(c4);
	glVertex3fv(tail2[7]);glVertex3fv(tail2[6]);
	glColor4fv(c3);
	glVertex3fv(tail2[0]);glVertex3fv(tail2[1]);
    glEnd();		
    glColor4fv(c4);

    glBegin(GL_QUADS);
	glVertex3fv(tail2[6]); glVertex3fv(tail2[5]); glVertex3fv(tail2[2]); glVertex3fv(tail2[1]);

	glColor4fv(c);

	glVertex3fv(tail2[0]); glVertex3fv(tail2[3]); glVertex3fv(tail2[4]); glVertex3fv(tail2[7]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* draw a 1 colour cube rotated around the x and y axis          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void makerrotcubexyflat(float u,  float v,  float w, 
		float theta, float c[4])
    {
    float tail1[8][3];
    float tail2[8][3];
    register int i;
    float thetaRad, cthetarad, sthetarad;
    
    thetaRad = theta * BIG_DEG_TO_RAD;
    cthetarad = cos(thetaRad);
    sthetarad = sin(thetaRad);

    tail1[0][2] = tail1[1][2] = tail1[2][2] = tail1[3][2] = w;    
    tail1[4][2] = tail1[5][2] = tail1[6][2] = tail1[7][2] = - w;
    tail1[2][0] = tail1[3][0] = tail1[4][0] = tail1[5][0] = u;
    tail1[0][0] = tail1[1][0] = tail1[6][0] = tail1[7][0] = - u;
    tail1[0][1] = tail1[3][1] = tail1[4][1] = tail1[7][1] = v;  
    tail1[1][1] = tail1[2][1] = tail1[5][1] = tail1[6][1] = - v;
 
    for (i=0;i<8;i++)
	{
	tail2[i][0] = tail1[i][0]*cthetarad + sthetarad*(tail1[i][1]*sthetarad+tail1[i][2]*cthetarad);
	tail2[i][1] = tail1[i][1]*cthetarad - tail1[i][2]*sthetarad;
	tail2[i][2] = -tail1[i][0]*sthetarad + cthetarad*(tail1[i][1]*sthetarad+tail1[i][2]*cthetarad);
	}

    glColor4fv(c);

    glBegin(GL_QUAD_STRIP);
	glVertex3fv(tail2[0]);glVertex3fv(tail2[1]);glVertex3fv(tail2[3]);glVertex3fv(tail2[2]);
	glVertex3fv(tail2[4]);glVertex3fv(tail2[5]); 
	glVertex3fv(tail2[7]);glVertex3fv(tail2[6]);
	glVertex3fv(tail2[0]);glVertex3fv(tail2[1]);
    glEnd();		

    glBegin(GL_QUADS);
	glVertex3fv(tail2[6]); glVertex3fv(tail2[5]); glVertex3fv(tail2[2]); glVertex3fv(tail2[1]);
	glVertex3fv(tail2[0]); glVertex3fv(tail2[3]); glVertex3fv(tail2[4]); glVertex3fv(tail2[7]);
    glEnd();
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void andysphdraw(float loc[4], int count)
    {
    if (count == 0)
	{
	float radius;
	
	radius = loc[3] / 1.5;
	makerVapour(loc[0], loc[1], loc[2], radius, radius, radius);	
	}
    else
	{
	qobj = gluNewQuadric();
    
	if (qobj != NULL)
	    {
	    glPushMatrix();
		glTranslatef(loc[0], loc[1], loc[2]);
		gluSphere( qobj, loc[3], count*3, count*3); /* was count*4 */
	    glPopMatrix();
	    gluDeleteQuadric(qobj);
	    }
	}
    }
