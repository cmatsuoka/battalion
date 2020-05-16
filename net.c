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
/* net.c  v 1.3                                                        */
/* network routines for battalion                                      */
/***********************************************************************/

/* the network coding is pretty much alpha-stage stuff. It seems
 * to generally work though the monster positions are slightly off
 * in the remote versions making it hard to hit the other person.
 * 
 * the vapour also has a problem getting kills on the other monsters
 * 
 * ocassionally wehn switching from demo to game mode the screen goes
 * black and everything stops
 */
#include "battalion.h"

/*****************/
/* network stuff */
/*****************/

struct sockaddr_in serv_addr;
struct sockaddr_in clients[MAXCLIENTS];
struct sockaddr_in cli_addr;

long clientsFrom[MAXCLIENTS];
int lastClientMonsterUpdate[MAXCLIENTS];

time_t clientsAlive[MAXCLIENTS];
time_t lastRecvTime;
time_t lastNotDeadYetTime;
int lastMonsterUpdate;

int numClients;
int sockfd;
int portNumber;
int connected;

int waitCounter	    = 0;
int beamOnSinceLast = 0;
int tankModulator   = 0;

char hostAddr[40];

extern float globalxshift;
extern float globalzshift;

extern struct targetInfo * targets;


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void turnBeamOnSinceLast()
    {
    beamOnSinceLast = 1;
    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void setUnconnected()
    {
    connected = 0;
    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void setPortNumber(int val)
    {
    portNumber = val;
    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void setHostAddr(char * val)
    {
    strcpy(hostAddr, val);
    }
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int HostnameToIP(char *hostname, char *hostIP)
    {
    struct hostent* host;

    host = gethostbyname(hostname);

    if (host)
	{
	sprintf(hostIP,"%d.%d.%d.%d",(int) host->h_addr_list[0][0],
	(int) host->h_addr_list[0][1],
	(int) host->h_addr_list[0][2],
	(int) host->h_addr_list[0][3]);
	}
    else
	return(0);

    return (1);
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int setUpClient()
    {
    char hostIP[40];

    lastMonsterUpdate = -1;
    lastRecvTime = lastNotDeadYetTime = 0;

    /************************/
    /* Open datagram socket */
    /************************/
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM,0)) < 0)
	{
	printf("battalion client cannot open datagram socket\n");
	return(0);
        }

    /*****************************/
    /* Prepare client to connect */
    /*****************************/
    
    bzero((char *) &cli_addr, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    cli_addr.sin_port = htons(0);

    if (bind(sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0)
	{
	printf("battalion client cannot bind local address\n");
	return(0);
	}

    /****************************************************************/
    /* Set up data structure to indicate which server to connect to */
    /****************************************************************/
    
    if ((hostAddr[0] >= '0') && (hostAddr[0] <= '9'))
	{
	strcpy (hostIP, hostAddr);
	}
    else
	{
	if(!HostnameToIP(hostAddr, hostIP))
	    {
	    strcpy (hostIP, hostAddr);
	    }
	}
	
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(hostIP);
    serv_addr.sin_port = htons(portNumber);

    printf("battalion client running - looking for server on %s (%s) on port %d\n\n", hostAddr, hostIP, portNumber);

    /*******************/
    /* set nonblocking */
    /*******************/
    
    fcntl(sockfd,F_SETFL,FNDELAY);


    return(1);
    }


/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int setUpNetwork()
    {
    int i;
    char host[MAXHOSTNAMELEN];
    char hostIP[MAXHOSTNAMELEN];


    /************************/
    /* Open datagram socket */
    /************************/
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
	printf("Server cannot open datagram socket\n");
	return(0);
	}

    /******************************************************/
    /* Set up server to allow connection from any address */
    /******************************************************/
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    
    serv_addr.sin_port = htons(portNumber);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
	printf("battalion server cannot bind to local address\n");
	return(0);
	}

    gethostname(host,MAXHOSTNAMELEN);
    HostnameToIP(host, hostIP);

    printf("battalion server running on %s (%s) on port %d\n\n", host, hostIP, portNumber);

    /*******************/
    /* set nonblocking */
    /*******************/
    
    fcntl(sockfd,F_SETFL,FNDELAY);

    /******************/
    /* no clients yet */
    /******************/
    
    numClients = 0;

    for (i=0; i<MAXCLIENTS;i++)
	{
	clientsAlive[i] = 0;
	lastClientMonsterUpdate[i] = -1;
	}

    return(1);
    }
   
 /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void updateNetworkBuildings(char * recvline, struct tree * treelist)
    {
    char command[MAXLINE];
    char mesg[MAXLINE];
    int buildingNumber;
    int i;
    struct tree * temptree;
   
    /*****************************************************/
    /* find out which building was destroyed by a client */
    /*****************************************************/
    
    sscanf(recvline, "%s %d", command, &buildingNumber);

    for (temptree = treelist->next; temptree != NULL; temptree = temptree->next)
	if (temptree->number == buildingNumber)
	    temptree->intact = 0;

    /***********************************************************************/
    /* tell all the clients about the building destroyed by another client */
    /***********************************************************************/
    
    sprintf(mesg, "%s %d #", MESG_BUILDING, buildingNumber);

    for(i=0; i<numClients; i++)
	sendMessage(mesg, &clients[i], sizeof(clients[i]));
    
    }

 /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void addNewNetworkTank(char * recvline, struct tank * tanklist, 
    void * arena, int sizeTank)
    {
    char command[MAXLINE];
    float x, z;
    int type, number;
    float finRange, speed;
    struct tank * temptank;
    int foundIt;
    
    sscanf(recvline, "%s %d %f %f %f %f %d",
	command, &number, &x, &z, &finRange, &speed, &type);


       foundIt = 0;
    for (temptank = tanklist->next; temptank != NULL; temptank = temptank->next)
	{
	if (number == temptank->number)
	    foundIt = 1;
	}

    if (!foundIt)
	{
    fprintf(stderr, "ADDING A NEW TANK %d %f %f %f %f %d \n", number, x, z, finRange, speed, type);

	temptank = (struct tank *) amalloc(sizeTank, arena);

	temptank->goforit	= NULL;
	
	temptank->number	= number;
	temptank->x		= x + globalxshift;;
	temptank->y		= -1;
	temptank->z		= z + globalxshift;;

	temptank->xv		= 0;
	temptank->zv		= 0;
	temptank->range		= 3;
	temptank->rad		= 0;
	temptank->theta		= 0;
	temptank->count		= 0;

	temptank->finalR	= finRange;
	temptank->damage	= 1;
	
	temptank->minrange	= 0.5;
	temptank->speed		= speed;
	temptank->type		= (char) type;
    
	temptank->next	= tanklist->next;
	tanklist->next	= temptank;
	}
    }

 /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void updateNetworkTank(char * recvline, struct tank * tanklist)
    {
    char command[MAXLINE];
    float x, z;
    int number, maserCount;
    struct tank * temptank, * foundtank;
    int foundIt;
    
    sscanf(recvline, "%s %d %f %f %d",
	command, &number, &x, &z, &maserCount);

/* this should have somethin that uses the monsters current location to modify the
 * location of the tank
 */
    
    foundIt = 0;
    for (temptank = tanklist->next; (temptank != NULL) && (!foundIt); temptank = temptank->next)
	{
	if (number == temptank->number)
	    {
	    foundIt = 1;
	    foundtank = temptank;
	    }
	}

    if (foundIt)
	{
/*
	fprintf(stderr, "%s \n", recvline);
	fprintf(stderr, "UPDATING TANK %d %f %f %f %d \n", number, x, y, z, maserCount);
*/
	foundtank->x	= x + globalxshift;
	foundtank->z	= z + globalzshift;
	
	if (maserCount > 1)
	    foundtank->maserCount = 10;
	}
    }

 
  /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void tellAboutAllTanks(struct sockaddr_in * cli, int length
    , struct tank * tanklist)
    {
    char mesg[MAXLINE];
    
    struct tank * tempTank;

    for (tempTank = tanklist->next; tempTank != NULL; tempTank = tempTank->next)
	{
	fprintf(stderr, "sending FULL data on tank %d to a new client\n", tempTank->number);

/* nother copy of this elsewhere */

	sprintf(mesg, "%s %d %3.1f %3.1f %3.1f %3.1f %0.3f %d %d #", MESG_NEW_TANK,
						 tempTank->number, 
						 tempTank->x-globalxshift, 
						 tempTank->z-globalzshift, 
						 tempTank->finalR,
						 tempTank->speed,
						 tempTank->type, 
						 tempTank->maserCount
						 );

	sendMessage(mesg, cli, length);
	}
    }

 /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void updateNetworkMonsters(char * recvline, long clientFrom, void * arena)
    {
    struct targetInfo * tempTarget,  *thaOne;
    
    float n_energy, n_x, n_z;
    int n_frame;
    int n_monsterType, n_dead, n_beamOn;
    int n_horzrot, n_vertrot, n_timeDead; 
    int exists;
    char command[MAXLINE];

    sscanf(recvline, "%s %d %d %f %d %d %d %f %f %d %d",
	    command,
	    &n_frame,
	    &n_monsterType, 
	    &n_energy, 
	    &n_horzrot, 
	    &n_vertrot, 
	    &n_dead, 
	    &n_x, 
	    &n_z, 
	    &n_beamOn,
	    &n_timeDead 
	    );
    
    exists = 0;
    for(tempTarget = targets; tempTarget != NULL; tempTarget=tempTarget->next)
	{
	if (tempTarget->net_clientFrom == clientFrom)
	    {
	    exists = 1;
	    thaOne = tempTarget;
	    }
	}

    if (exists && (thaOne->monster.monster == n_monsterType))
	{	
	/*****************************************************************/
	/* update the values in the currently existing networked monster */
	/*****************************************************************/

	thaOne->net_headHorzRotate	= n_horzrot;
	thaOne->net_headVertRotate	= n_vertrot;
	thaOne->net_energyRemaining	= n_energy;
	thaOne->net_x			= n_x + globalxshift;
	thaOne->net_z			= n_z + globalzshift;
	thaOne->net_beamOn		= n_beamOn;
	}
    else if (n_timeDead < 40)
	{
	/*******************************/
	/* add a new networked monster */
	/*******************************/
	
	addNetworkTarget(clientFrom, n_monsterType, n_horzrot, n_vertrot, 
	    n_energy, n_x + globalxshift, n_z + globalzshift, n_beamOn, arena);
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void addNetworkTarget(long fromNum, int monsterType, float horz, float vert, 
			float energy, float x, float z, int beamOn, void * arena)
    {
    struct monsterInfo newMonster;
    struct targetInfo * nother, *temp;
    int alreadyExists;
    int i;

    alreadyExists = 0;
    for (i=0, temp=targets->next; temp != NULL; i++,temp=temp->next)
	{
	if (temp->net_clientFrom == fromNum)
	    {
	    alreadyExists = 1;
	    
	    /******************************/
	    /* monster type has changed ! */
	    /******************************/
	    
	    newMonster.monster	= monsterType;
	    newMonster		= resetMonsterParameters(newMonster);
	    
	    temp->monster		= newMonster;

	    temp->net_clientFrom	= fromNum;
	    temp->net_headHorzRotate	= horz;
	    temp->net_headVertRotate	= vert;
	    temp->net_energyRemaining	= energy;
	    temp->net_x			= x;
	    temp->net_z			= z;
	    temp->net_beamOn		= beamOn;

	    temp->monster.headHorzRotate = horz;
	    temp->monster.headVertRotate = vert;
	    temp->x = x;
	    temp->z = z;

	    printf("updating a remote monster that has changed its type\n");
	    }
	}

    /************************************/
    /* add a new monster into this game */
    /************************************/

    if (!alreadyExists)
	{
	newMonster.monster  = monsterType;
	newMonster	    = resetMonsterParameters(newMonster);
    
	nother = (struct targetInfo *) amalloc(sizeof(struct targetInfo), arena);
	
	if (nother != NULL)
	    {
	    nother->monster		= newMonster;
	    nother->net_clientFrom	= fromNum;
	    nother->net_headHorzRotate	= horz;
	    nother->net_headVertRotate	= vert;
	    nother->net_energyRemaining = energy;
	    nother->net_x		= x;
	    nother->net_z		= z;
	    nother->net_beamOn		= beamOn;

	    nother->monster.headHorzRotate = horz;
	    nother->monster.headVertRotate = vert;
	    nother->x = x;
	    nother->z = z;

	    nother->next    = targets->next;
	    targets->next   = nother;
	    }
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void updateClientMonster(char * recvline, void * arena)
    {
    struct targetInfo * tempTarget,  *thaOne;
    
    float n_energy, n_x, n_z;
    int n_frame;
    int n_monsterType, n_dead, n_beamOn;
    int n_horzrot, n_vertrot, n_timeDead; 
    int exists;
    long recvfrom;
    char command[MAXLINE];
    char orig_command[MAXLINE];

    sscanf(recvline, "%s %ld %s %d %d %f %d %d %d %f %f %d %d",
	    command,
	    &recvfrom,
	    orig_command, 
	    &n_frame,
	    &n_monsterType, 
	    &n_energy, 
	    &n_horzrot, 
	    &n_vertrot, 
	    &n_dead, 
	    &n_x, 
	    &n_z, 
	    &n_beamOn,
	    &n_timeDead 
	    );
    
    exists = 0;
    for(tempTarget = targets; tempTarget != NULL; tempTarget=tempTarget->next)
	{                                 /* note difference here ! */
	if (tempTarget->net_clientFrom == recvfrom)
	    {
	    exists = 1;
	    thaOne = tempTarget;
	    }
	}

    if (exists && (thaOne->monster.monster == n_monsterType))
	{	
	/*****************************************************************/
	/* update the values in the currently existing networked monster */
	/*****************************************************************/

	thaOne->net_headHorzRotate	= n_horzrot;
	thaOne->net_headVertRotate	= n_vertrot;
	thaOne->net_energyRemaining	= n_energy;
	thaOne->net_x			= n_x + globalxshift;
	thaOne->net_z			= n_z + globalzshift;
	thaOne->net_beamOn		= n_beamOn;
	}
    else if (n_timeDead < 40)
	{
	/*******************************/
	/* add a new networked monster */
	/*******************************/
	
	addNetworkTarget(recvfrom, n_monsterType, n_horzrot, n_vertrot, 
	    n_energy, n_x + globalxshift, n_z + globalzshift, n_beamOn, arena);
	}
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

int sendMessage(char * mesg,  struct sockaddr_in * cli, int length)
    {
    int n;
      
    n = strlen(mesg)+1;

    if (sendto(sockfd, mesg, n, 0, (struct sockaddr *) cli, length) != n)
	{
	printf("Sendto error\n");
	return(1);
	}
    else
	return(0);
    }
    
 /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
   
void processClient(time_t now, int mainCounter, int totalCounter,
    struct tree * treelist, struct tank * tanklist, void * arena,
    int sizeTank, struct monsterInfo Googelon,
    int buildingBoomThisFrameCounter, int buildingBoomThisFrame[20])
    {
    char recvline[MAXLINE];
    char mesg[MAXLINE];
    char command[MAXLINE];
    int n;
    int servlen;
    long clientFrom;
    int j;
    int frameNum;

    extern int errno;
     

    /* send a request every once in a while until connection established */
    /* if I haven't seen any data from the server in a while try to reconnect */
    /* this may be a bit harsh to say connected = 0 */

    if (now > (lastRecvTime + RECONNECT_TIME))
	connected = 0;

    if (!connected) 
	{
	sprintf(mesg,MESG_REQUEST);
	sendMessage(mesg, &serv_addr, sizeof(serv_addr));
	}

    if (now > (lastNotDeadYetTime + IM_NOT_DEAD_SEND_TIME))
	{
	lastNotDeadYetTime = now;

	sprintf(mesg,MESG_NOTDEADYET);
	sendMessage(mesg, &serv_addr, sizeof(serv_addr));
	}

	/*******************************************************/
	/* tell all the clients when a tree has been destroyed */
	/*******************************************************/


	for(j=0;j<buildingBoomThisFrameCounter;j++)
	    {
	    sprintf(mesg, "%s %d #", MESG_BUILDING, buildingBoomThisFrame[j]);

	    sendMessage(mesg, &serv_addr, sizeof(serv_addr));
	    }

	/***********************************/
	/* ocassionally send to the server */
	/***********************************/

	if (!(mainCounter % MONSTER_UPDATE_RATE))
	    {
	    sprintf(mesg, "%s %1d %1d %1.0f %1d %1d %1d %1.1f %1.1f %1d %1d#",
			    MESG_UPDATE, 
			    totalCounter, 
			    Googelon.monster, 
			    Googelon.energyRemaining, 
			    Googelon.headHorzRotate,
			    Googelon.headVertRotate,
			    Googelon.monsterIsDead, 
			    -globalxshift, 
			    -globalzshift, 
			    beamOnSinceLast, 
			    Googelon.timeDead
			    );

	    beamOnSinceLast = 0;
	    sendMessage(mesg, &serv_addr, sizeof(serv_addr));
	    }

    
	/*************************************/
	/* wait for messages from the server */
	/*************************************/

	 servlen = sizeof(serv_addr);
	 n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *) &serv_addr, (int *)& servlen);
	 if ((n < 0)  && (errno != EWOULDBLOCK))
	    {
	    printf("Client receive error\n");
	    }
	else if (n >= 0)
	    {
	    clientFrom = ntohl(serv_addr.sin_addr.s_addr);
/*
	    printf("RECEIVED: %s",recvline);
	    printf("FROM: %ld\n\n",clientFrom);
*/
	    connected = 1;
	    lastRecvTime = now;
	    
	    sscanf(recvline, "%s %d", command, &frameNum);
	    if (strcmp(command, MESG_UPDATE) == 0)
		{
		/*if (frameNum > lastMonsterUpdate) */
		/* took this out since there can be > 1 monster being sent
		 * to the client
		 */
		    {
		    updateNetworkMonsters(recvline, clientFrom, arena);
		    lastMonsterUpdate = frameNum;
		    }
		}

	    if (strcmp(command, MESG_NEW_TANK) == 0)
		{
		addNewNetworkTank(recvline, tanklist, arena, sizeTank);
		}

	    if (strcmp(command, MESG_UPDATE_TANK) == 0)
		{
		updateNetworkTank(recvline, tanklist);
		}
	    if (strcmp(command, MESG_BUILDING) == 0)
		{
		updateNetworkBuildings(recvline, treelist);
		}
	    if (strcmp(command, MESG_CLIENT_CLIENT_UPDATE) == 0)
		{
		updateClientMonster(recvline, arena);
		}
	    }
		    
/*	close(sockfd); */

    }

 /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void tellAboutAllDeadBuildings(struct sockaddr_in * cli, int length, 
			       int buildingBoomSoFarCounter, 
			       int buildingBoomSoFar[800])
    {
    int j;
    char mesg[MAXLINE];

    for(j=0; j<buildingBoomSoFarCounter; j++)
	{
	sprintf(mesg, "%s %d #", MESG_BUILDING,  buildingBoomSoFar[j]);

	sendMessage(mesg, cli, length);
	}
    }
    
 /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
  
  /* there is now a connected = 0 in setPlayConditions!!! */
   
void processNetwork(time_t now, int mainCounter, int totalCounter,
    struct tree * treelist, struct tank * tanklist, void * arena, 
    struct monsterInfo Googelon, int buildingBoomSoFarCounter, 
    int buildingBoomThisFrameCounter, int buildingBoomSoFar[800], 
    int buildingBoomThisFrame[20])
    {
    long recvFrom;
    struct sockaddr_in cli_addr;
    char recvline[MAXLINE];
    char mesg[MAXLINE];
    char command[MAXLINE];

    struct targetInfo * tempTarget;
    extern int errno;
    
    int clilen;
    int oldClient;
    int n;
    int i, j;
    int gotOne;
    int noMore;
    int thisClient;
    int frameNumber;
    
    clilen = sizeof(cli_addr);

    noMore = 0;
    
    tankModulator = (tankModulator + 1) % MONSTER_UPDATE_RATE;
    
    while(!noMore)
	{
	/**********************/
	/* Read incoming data */
	/**********************/
	 
	n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr *) &cli_addr, (int *)& clilen);
    
	if (n < 0)
	    if(errno != EWOULDBLOCK)
		{
		printf("Server recvfrom error\n");
		noMore = 1;
		}
	    else
		{
		noMore = 1;
		}
	else
	    {
	    recvFrom = ntohl(cli_addr.sin_addr.s_addr);
/*
	    printf("RECEIVED: %s",recvline);
	    printf(" FROM: %ld\n\n",recvFrom);
*/

	    thisClient = -1;
	    
	    for(i=0; i<numClients; i++)
		if (recvFrom == clientsFrom[i])
		    {
		    thisClient = i;
		    }

	    /* its possible we are getting an update message from a
	    client we didn't know we had (if server crashes) so we
	    ignore all of these messages until it establishes a
	    'proper' connection */
	        
	    if (thisClient != -1)
		{
		if (strcmp(recvline,MESG_NOTDEADYET) == 0)	
		    {
		    clientsAlive[thisClient] = now;
		    }
    
		sscanf(recvline, "%s %d", command, &frameNumber);
		if (strcmp(command, MESG_UPDATE) == 0)
		    {
		    if (frameNumber > lastClientMonsterUpdate[thisClient])
			{
			updateNetworkMonsters(recvline, recvFrom, arena);
			lastClientMonsterUpdate[thisClient] = frameNumber;
			
			/*******************************************/
			/* send this info to all the other clients */
			/*******************************************/
			
			sprintf(mesg, "%s %ld %s", MESG_CLIENT_CLIENT_UPDATE, recvFrom, recvline);
			
			for(i=0; i<numClients; i++)
			    if (i != thisClient)
				{
				sendMessage(mesg, &clients[i], sizeof(clients[i]));
				/* fprintf(stderr, "%s\n", mesg); */
				}
			}
		    }
		}
    
	    if (strcmp(command, MESG_BUILDING) == 0)
		{
		updateNetworkBuildings(recvline, treelist);
		}

    
	    if (strcmp(recvline,MESG_REQUEST) == 0)
		{
		/*********************************************/
		/* need to see if this client already exists */
		/*********************************************/
		
		oldClient = 0;
		
		for(i=0; i<numClients; i++)
		    {  
		    if (recvFrom == clientsFrom[i])
			{
			clients[i] 	= cli_addr;
			clientsAlive[i] = now;
			oldClient 	= 1;
			}
		    }

		if (oldClient)
		    {
		    sprintf(mesg,MESG_REAQUIRE);
		    sendMessage(mesg, &cli_addr, clilen);

		    tellAboutAllDeadBuildings(&cli_addr, clilen, buildingBoomSoFarCounter, buildingBoomSoFar);
		    tellAboutAllTanks(&cli_addr, clilen, tanklist);

		    }
		    
		if (!oldClient)
		    {
		    clients[numClients] 	= cli_addr;
		    clientsFrom[numClients] 	= recvFrom;
		    clientsAlive[numClients]	= now;
		    
		    numClients++;
		    
		    sprintf(mesg, MESG_ACKNOWLEDGE);
		    sendMessage(mesg, &cli_addr, clilen);

		    tellAboutAllDeadBuildings(&cli_addr, clilen, buildingBoomSoFarCounter, buildingBoomSoFar);
		    tellAboutAllTanks(&cli_addr, clilen, tanklist);
		    }
		}
    
	    }

	}
    
	/****************************************************************/
	/* kill any client connection that has not responded in a while */
	/****************************************************************/

	i = 0;
	gotOne = 0;
	
	while ((i < numClients) && (!gotOne))
	    {  
	    if ((clientsAlive[i]+IM_NOT_DEAD_YET_TIME) < now)
		{
		printf("killing client %d\n", i);

		/* remove the appropriate target */
		for(tempTarget = targets; tempTarget != NULL; tempTarget=tempTarget->next)
		    {
		    if (tempTarget->net_clientFrom == clientsFrom[i])
			tempTarget->net_energyRemaining = 0;
		    }

		for (j=i+1; j < numClients; j++)
		    {
		    clients[j-1]	= clients[j];
		    clientsFrom[j-1]	= clientsFrom[j];
		    clientsAlive[j-1]	= clientsAlive[j];
		    gotOne = 1;
		    }
		numClients -= 1;
		
		}
	    else
		i++;
	    }

	/*******************************************************/
	/* tell all the clients when a tree has been destroyed */
	/*******************************************************/

	for(j=0;j<buildingBoomThisFrameCounter;j++)
	    {
	    sprintf(mesg, "%s %d #", MESG_BUILDING, buildingBoomThisFrame[j]);

	    for(i=0; i<numClients; i++)
		sendMessage(mesg, &clients[i], sizeof(clients[i]));
	    }



	/*************************************************************/
	/* ocassionally broadcast to all currently connected clients */
	/*************************************************************/

	if (!(mainCounter % MONSTER_UPDATE_RATE))
	    {
	    sprintf(mesg, "%s %1d %1d %1.0f %1d %1d %1d %1.1f %1.1f %1d %1d#",
			    MESG_UPDATE, 
			    totalCounter, 
			    Googelon.monster, 
			    Googelon.energyRemaining, 
			    Googelon.headHorzRotate,
			    Googelon.headVertRotate,
			    Googelon.monsterIsDead, 
			    -globalxshift, 
			    -globalzshift, 
			    beamOnSinceLast, 
			    Googelon.timeDead
			    );

	    beamOnSinceLast = 0;

	    for(i=0;i<numClients;i++)
		sendMessage(mesg, &clients[i], sizeof(clients[i]));
	    }
}
