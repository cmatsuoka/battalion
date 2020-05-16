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
/* update.c  v 1.2                                                     */
/* update routines for battalion                                       */
/***********************************************************************/

#include "battalion.h"

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* output an error message                                       */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void showError(char * theString)
    {
    fprintf(stderr, "BATTALION ERROR: %s\n", theString);
    fflush(stderr);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* compute height of a building                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

float buildingHeight(int type,  int shape)
    {
    float height;
    
    switch(type){
	case 0:	    height = 0.5;
		    break;
		    
	case 1:	    switch(shape){
			case 1:	
			case 11:
			case 14:
			case 22:
			case 23:
			case 24:
			case 37:    height = 0.8;
				    break;
				    
			case 9:	    height = 0.2;
				    break; 
				     
			case 5:
			case 6:
			case 13:
			case 28:    height = -0.2;
				    break;
				    
			case 31:
			case 32:    height = -0.4;
				    break;
				    
			default:    height = 0.0;
				    break;
		    }
		    break;
		    
	case 2:	    height = -0.8;
		    break;
		    
	case 3:	    if (shape == 0)
			height = -0.4;   
		    else
			height = -0.6;
		    break;
		    
	default:    showError("invalid building type (buildingHeight)");
		    break;
	}
	
    return(height);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int same(char * first,  char * second)
    {
    if (strcmp(first, second) == 0)
	return(1);
    else
	return(0);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int different(char * first,  char * second)
    {
    if (strcmp(first, second) != 0)
	return(1);
    else
	return(0);
    }
    

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

struct monsterInfo resetMonsterParameters(struct monsterInfo Googelon)
    {
    register int i;

    /************************************/
    /* reset general monster parmeters  */
    /************************************/

    Googelon.monsterScore	= 0;
    Googelon.monsterIsDead	= 0;
    Googelon.deadCount		= 0;
    Googelon.timeDead		= 0;

    Googelon.energyRemaining	= MAXLIFE;

    Googelon.moveCount		= 0;

    Googelon.headHorzRotate	= 0;
    Googelon.headVertRotate	= 150;
    Googelon.beamOn		= 0;

    Googelon.monsterID		= rand();

    for(i=0; i<MAXTRIBUTES; i++)
	{	
	Googelon.a[i][0] = randy(0.2);
	Googelon.a[i][1] = PLANEY + 0.55 + randy(0.5);
	Googelon.a[i][2] = randy(0.2);

	Googelon.a[i][3] = 0;

	Googelon.a[i][4] = (rand() % 32) * 0.1;
	}

    /*************************************/
    /* reset specific monster parameters */
    /*************************************/
    
    switch(Googelon.monster){
	case GOOGELON:	Googelon.speed	    = 0.08;
			Googelon.xspeed	    = 30;
			Googelon.moveCost   = 0.1;
			Googelon.height	    = PLANEY + 1.3;
			Googelon.width	    = 0.3;
			Googelon.bottom	    = PLANEY;
			Googelon.regenRate  = 0.1;
			break;
			
	case VAPOUR:	Googelon.speed	    = 0.12;
			Googelon.xspeed	    = 40;
			Googelon.moveCost   = 0.05;
			Googelon.height	    = PLANEY + 1.3;
			Googelon.width	    = 0.3;
			Googelon.bottom	    = PLANEY;
			Googelon.regenRate  = 0.14;
			break;
			
	case TECHS:	Googelon.speed	    = 0.06;
			Googelon.xspeed	    = 35;
			Googelon.moveCost   = 0.1;
			Googelon.height	    = PLANEY + 1.3;
			Googelon.width	    = 0.3;
			Googelon.bottom	    = PLANEY;
			Googelon.regenRate  = 0.1;
			break;
			
	case FLUTTER:	Googelon.speed	    = 0.12;
			Googelon.xspeed	    = 40;
			Googelon.moveCost   = 0.06;
			Googelon.height	    = PLANEY + 1.4;
			Googelon.width	    = 0.5;
			Googelon.bottom	    = PLANEY + 0.9;
			Googelon.regenRate  = 0.1;
			break;
			
	default:	showError("Bogus Monster! (setPlayConditions)");
			break;
    }
    
    return(Googelon);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* techs is firing a projectile                                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void updateGun(float xhead, float zhead, int horz, int vert, int counter, struct monsterInfo *m)
    {
    float x, y, z;
    
    if (counter % 2)
	{
	x = 0.2* -cos((900+horz) * BIG_DEG_TO_RAD);
	y = 0.2*  cos((900+vert) * BIG_DEG_TO_RAD);
	z = 0.2*  sin((900+horz) * BIG_DEG_TO_RAD);

	addProjectile(xhead, PLANEY+1.2, zhead, PROJTECHS, x, y, z, 1000, m);
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* the vapour is leaving a fire trail                            */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void updateVap(float x,  float z, int counter, struct monsterInfo *m)
    {
    if (counter % 2)
	addProjectile( x, PLANEY+0.12, z, PROJFIRE, 0, -0.0005, 0, 10000, m);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* googelon/flutter is firing their energy beam                  */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void updateBeam(struct monsterInfo * g,  struct targetInfo * t, float x, float z, struct tank * allTanks,  
		struct tree ** allTreePtrs, int numTrees, struct monsterInfo * m)
    {
    struct targetInfo * temptarget;
    struct tank * ttank, * temptank;
    struct tree * ttree;
    float loc1[3],  loc3[3];
    float rtankhorz,  rtankvert;
    float atankhorz,  atankvert;
    float abeamhorz,  abeamvert;
    float rbeamhorz,  rbeamvert;
    float hdiff,  vdiff;
    float tankx,  tanky,  tankz;
    float beamx,  beamy,  beamz;
    float height;
    float R;
    int itsDead;
    int i;
    int horz, vert;
    
    
    horz = m->headHorzRotate;
    vert = m->headVertRotate;


    doSound(MONSTERBEAM);
        
    if (vert < 175)
	R = 4;
    else
	R = 1.2 / (cos((900 - vert) * BIG_DEG_TO_RAD));
	
    loc3[0] = x + R * -cos((900 + horz) * BIG_DEG_TO_RAD);
    loc3[2] = z + R * sin((900 + horz) * BIG_DEG_TO_RAD);

    if (vert < 0)
	loc3[1] = PLANEY+1.2 + R * sin(fabs(vert* BIG_DEG_TO_RAD));
    else
	loc3[1] = PLANEY+1.2 - R * sin(fabs(vert* BIG_DEG_TO_RAD));


    loc1[0] = x;
    loc1[1] = PLANEY + 1.2;
    loc1[2] = z;


    /**********************************/
    /* does beam touch ground         */
    /**********************************/

    if (loc3[1] <= PLANEY + 0.1)
	{
	addProjectile(loc3[0], PLANEY + 0.175, loc3[2], PROJSCAR, 0, -0.0075, 0, 0, NULL);
	}
	
    /******************************/
    /* what does beam hit         */
    /******************************/
    
    if ((loc3[2] - loc1[2]) == 0)
	loc1[2] += NEARZERO;
	    
    rbeamhorz = fabs(sqrt(pow(loc3[0] - loc1[0], 2) + pow(loc3[2] - loc1[2], 2)));
    abeamhorz = atan((loc3[0] - loc1[0]) / (loc3[2] - loc1[2]));

    if ((loc3[2] - loc1[2]) < 0)
	abeamhorz += PI;

    hdiff = - abeamhorz;

    beamx = 0;		/* rbeamhorz * sin(abeamhorz + hdiff); */
    beamz = rbeamhorz;	/* rbeamhorz * cos(abeamhorz + hdiff); */
    
    if (beamz == 0)
	beamz = NEARZERO;

    rbeamvert = fabs(sqrt(pow(loc3[1] - loc1[1], 2) + beamz*beamz));
    abeamvert = atan( (loc3[1] - loc1[1]) / beamz);

    vdiff = -abeamvert;
    beamy = 0;		/* rbeamvert * sin(abeamvert + vdiff); */
    beamz = rbeamvert;	/* rbeamvert * cos(abeamvert + vdiff); */
    
    if (beamz < 0)
	abeamvert += PI;

    /**********************************/
    /* does beam touch a tank         */
    /**********************************/
	    
    temptank	= allTanks;

    while(temptank->next != NULL)
	{
	ttank = temptank->next;

	if ((ttank->z - loc1[2]) == 0)
	    loc1[2] += NEARZERO; 

	rtankhorz = fabs(sqrt((pow(ttank->x - loc1[0], 2) + pow(ttank->z - loc1[2], 2))));
	atankhorz = atan( (ttank->x - loc1[0]) / (ttank->z - loc1[2]));

	if ((ttank->z - loc1[2]) < 0)
	    atankhorz += PI;
    
	tankx = rtankhorz * sin(atankhorz + hdiff);
	tankz = rtankhorz * cos(atankhorz + hdiff);

	if (tankz == 0)
	    tankz = NEARZERO;

	if ((ttank->type == HELO) || (ttank->type == CHH))
	    {
	    rtankvert = fabs(sqrt(pow(ttank->y - loc1[1], 2) + tankz*tankz));
	    atankvert = atan( (ttank->y - loc1[1]) / tankz);
	    }
	else /* tanks are positioned IN the ground so raise them up a bit */
	    {
	    rtankvert = fabs(sqrt(pow(ttank->y+0.2 - loc1[1], 2) + tankz*tankz));
	    atankvert = atan( (ttank->y+0.2 - loc1[1]) / tankz);
	    }

	if (tankz < 0)
	    atankvert += PI;

	tanky = rtankvert * sin(atankvert + vdiff);
	tankz = rtankvert * cos(atankvert + vdiff);

	itsDead = 0;

	switch(ttank->type){
	    case TANK:
	    case LAUNCHER:
	    case MASERTANK: if ((fabs(ttank->z - loc3[2]) <= BEAMKILL) &&
				(fabs(ttank->y - loc3[1]) <= 0.3) &&
				(fabs(ttank->x - loc3[0]) <= BEAMKILL))
				itsDead = 1;
			    break;
			    
	    case HELO:
	    case CHH:	    if ((tankz >= 0) && (tankz <= (beamz + 0.2)) &&
				(fabs(tankx) < 0.15) && (fabs(tanky) < 0.15))  
				itsDead = 1;
			    break;

	    case AIRPLANE: if ((tankz >= 0) && (tankz <= (beamz + 0.2)) &&
				(fabs(tankx) < 0.50) && (fabs(tanky) < 0.40))
				itsDead = 1;
			    break;

	    case FIGHTER: if ((tankz >= 0) && (tankz <= (beamz + 0.2)) &&
				(fabs(tankx) < 0.40) && (fabs(tanky) < 0.30))
				itsDead = 1;
			    break;
		    
	    case MECHAG:    if ((tankz >= 0) && (tankz <= (beamz+0.2)) &&
				(fabs(tankx) < 0.25) && (fabs(tanky) < 0.55))
				itsDead = 1;
			    break;

	    case HERO:	    if ((tankz >= 0) && (tankz <= (beamz+0.2)) &&
				(fabs(tankx) < 0.2) && (fabs(tanky) < 0.55))
				itsDead = 1;
			    break;
			        
	    default:	    showError("Bogus Vehicle in Tank List! (updateBeam)");
			    break;
	    }

	if (itsDead)
	    {
	    ttank->damage -= 1;

	    switch (ttank->type)
		{
		case TANK:
		case LAUNCHER:
		case MASERTANK:
		case AIRPLANE:
		case FIGHTER:
		case HELO:	    addScore(ttank->type, m);
				    break;
				    
		case MECHAG:	    addScore(PARTIALM, m);
				    break;
				    
		case CHH:	    addScore(PARTIALC, m);
				    break;
				    
		case HERO:	    addScore(PARTIALH, m);
				    break;
		}
	    
	    if (ttank->damage <= 0)
		{
		/**********************************/
		/* if so, slag it!                */
		/**********************************/

		doSound(SLAG);
	    
		ttank->damage = -99;
		}		
	    }
	    
	temptank = temptank->next;
	}

/***********************/
/* check other targets */
/***********************/

    temptarget = t->next;

    while(temptarget != NULL)
	{
	if (temptarget->monster.monsterID != m->monsterID)
	    {
	    if ((temptarget->z - loc1[2]) == 0)
		loc1[2] += NEARZERO; 
    
	    rtankhorz = fabs(sqrt((pow(temptarget->x - loc1[0], 2) + pow(temptarget->z - loc1[2], 2))));
	    atankhorz = atan( (temptarget->x - loc1[0]) / (temptarget->z - loc1[2]));
    
	    if ((temptarget->z - loc1[2]) < 0)
		atankhorz += PI;
	
	    tankx = rtankhorz * sin(atankhorz + hdiff);
	    tankz = rtankhorz * cos(atankhorz + hdiff);
    
	    if (tankz == 0)
		tankz = NEARZERO;
    
	    rtankvert = fabs(sqrt(pow(((temptarget->monster.height * 0.5 + temptarget->monster.bottom * 0.5) - loc1[1]), 2) + tankz*tankz));
	    atankvert = atan( ((temptarget->monster.height * 0.5 + temptarget->monster.bottom * 0.5) - loc1[1]) / tankz);


    
	    if (tankz < 0)
		atankvert += PI;
    
	    tanky = rtankvert * sin(atankvert + vdiff);
	    tankz = rtankvert * cos(atankvert + vdiff);
    
	    itsDead = 0;
    
	    switch(temptarget->monster.monster){
    
		case FLUTTER: if ((tankz >= 0) && (tankz <= (beamz + 0.2)) &&
				    (fabs(tankx) < 0.40) && (fabs(tanky) < 0.30))
				    itsDead = 1;
				break;
			
		case GOOGELON:
		case VAPOUR:
		case TECHS:    if ((tankz >= 0) && (tankz <= (beamz+0.2)) &&
				    (fabs(tankx) < 0.25) && (fabs(tanky) < 0.55))
				    itsDead = 1;
				break;
    				    
		default:	    showError("Bogus Monster in Target List! (updateBeam)");
				break;
		}
    
	    if (itsDead)
		{
/* 		addScore(MONSTER, m); */
		temptarget->monster.energyRemaining -= 1;
		}
		
	    }
	    temptarget = temptarget->next;
	}


/**************************/
/* check player's monster */
/**************************/

	if (g != m)
	    {
	    if ((0 - loc1[2]) == 0)
		loc1[2] += NEARZERO; 
    
	    rtankhorz = fabs(sqrt(loc1[0]*loc1[0] + loc1[2]*loc1[2]));
	    atankhorz = atan( loc1[0] / loc1[2]);
    
	    if (-loc1[2] < 0)
		atankhorz += PI;
	
	    tankx = rtankhorz * sin(atankhorz + hdiff);
	    tankz = rtankhorz * cos(atankhorz + hdiff);
    
	    if (tankz == 0)
		tankz = NEARZERO;
    
	    rtankvert = fabs(sqrt(pow(((g->height * 0.5 + g->bottom * 0.5) - loc1[1]), 2) + tankz*tankz));
	    atankvert = atan( ((g->height * 0.5 + g->bottom * 0.5) - loc1[1]) / tankz);


    
	    if (tankz < 0)
		atankvert += PI;
    
	    tanky = rtankvert * sin(atankvert + vdiff);
	    tankz = rtankvert * cos(atankvert + vdiff);
    
	    itsDead = 0;
    
	    switch(g->monster){
    
		case FLUTTER: if ((tankz >= 0) && (tankz <= (beamz + 0.2)) &&
				    (fabs(tankx) < 0.40) && (fabs(tanky) < 0.30))
				    itsDead = 1;
				break;
			
		case GOOGELON:
		case VAPOUR:
		case TECHS:    if ((tankz >= 0) && (tankz <= (beamz+0.2)) &&
				    (fabs(tankx) < 0.25) && (fabs(tanky) < 0.55))
				    itsDead = 1;
				break;
    				    
		default:	    showError("Bogus Monster in Target List! (updateBeam)");
				break;
		}
    
	    if (itsDead)
		{
		addScore(MONSTER, m);
		g->energyRemaining -= 1;
		}
		
	    }





	
        /**********************************/
        /* does beam touch a tree         */
        /**********************************/
 
    for (i=0;i<numTrees;i++)
	{
	ttree = allTreePtrs[i];
	
	if ((ttree->z - loc1[2]) == 0)
	    loc1[2] += NEARZERO; 

	rtankhorz = fabs(sqrt(pow(ttree->x - loc1[0], 2) + pow(ttree->z - loc1[2], 2)));
	atankhorz = atan( (ttree->x - loc1[0]) / (ttree->z - loc1[2]));

	if ((ttree->z - loc1[2]) < 0)
	    atankhorz += PI;
    
	tankx = rtankhorz * sin(atankhorz + hdiff);
	tankz = rtankhorz * cos(atankhorz + hdiff);
	
	/* y of building is located on the plane*/

	if (ttree->type == 1)
	    switch(ttree->treeshape){
		case 1:	
		case 11:
		case 14:
		case 22:
		case 23:
		case 24:    height = 0.8;
			    break;
		case 5:
		case 6:
		case 13:
		case 28:
		case 31:
		case 32:    height = 0.3;
			    break;
		default:    height = 0.5;
			    break;
		}
	else
	    height = 0.5;
	
	if (tankz == 0)
	    tankz = NEARZERO;

	rtankvert = fabs(sqrt(pow(ttree->y + height - loc1[1], 2) + tankz * tankz));
	atankvert = atan( (ttree->y + height - loc1[1]) / tankz);

	if (tankz < 0)
	    atankvert += PI;

	tanky = rtankvert * sin(atankvert + vdiff);
	tankz = rtankvert * cos(atankvert + vdiff);

	if ((tankz >= 0) && (tankz <= (beamz + 0.2)) &&
	    (fabs(tankx) < 0.4) && (fabs(tanky) < height))
		{
		if ((ttree->intact) && (ttree->type == 1))
		    addScore(BUILDING, m);
		ttree->intact = 0;
		}
	}
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* decide whether a vehicle has been hit                         */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int tankHit(struct tank * ttank, float xloc, float yloc, float zloc)
    {
    float blastx, blasty, blastz;
    
     switch(ttank->type){
	case TANK:
	case LAUNCHER:
	case MASERTANK:	    blastx = blasty = blastz = BLASTRX05;
			    break;

	case HELO:	    blastx = blastz = BLASTRX075;
			    blasty = BLASTRX07;
			    break;

	case AIRPLANE:	    blastx = blastz = BLASTR;
			    blasty = BLASTRX07;
			    break;

	case FIGHTER:	    blastx = blastz = BLASTR;
			    blasty = BLASTRX05;
			    break;

	case CHH:	    blastx = blastz = BLASTRX06;
			    blasty = BLASTRX04;
			    break;

	case MECHAG:	    blastx = blastz = BLASTR;
			    blasty = BLASTRX2;
			    break;

	case HERO:	    blastx = blastz = BLASTRX04;
			    blasty = BLASTRX2;
			    break;

	default:	    showError("Bogus Vehicle in Tank List! (tankHit)");
			    break;
	}
		
    if ((fabs(ttank->x - xloc) < blastx) &&
	(fabs(ttank->z - zloc) < blastz) &&
	(fabs(ttank->y - yloc) < blasty))
	    return(1);
    else
	    return(0);
    }


