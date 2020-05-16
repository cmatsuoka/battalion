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
/* audio.c  v 1.4                                                      */
/* audio routines for battalion                                        */
/* since audio is so machine dependant there is separate code for the  */
/*    various implementations ...                                      */
/***********************************************************************/

#include "battalion.h"
#include <sys/stat.h>

extern int noSound;
int soundOn;
int musicOn;
extern int showframes;
extern struct monsterInfo Googelon;

/***************/
/* music stuff */
/***************/

int playingTankFire, playingHeloRocket, playingTankMaser;
int playingExplosion, playingSlag, playingTech;

int musicCount, deadCount;

#ifdef SGIAUDIO

    struct sound * allSounds;
    struct aSound oneSound[MAXSOUNDS];

#endif
#ifdef SUNAUDIO

    char	*audio_buffer[MAXSOUNDS];
    int		buffer_counter[MAXSOUNDS];
    char	*audio_dev = "/dev/audio";
    int		audiofd;
    Audio_hdr   file_hdr;
    
    int playingBeam, playingMusic;

#endif

#ifdef MACVERSION

    int playingBeam, playingCrash, playingMusic, maserOn;

Boolean idleFlag;

		Handle  beamSound, boomSound, crashSound, monsterbeamSound,
				rocketSound, slagSound, tankSound, techSound, musicSound;
				
long musicRefNum, monsterbeamRefNum, maserbeamRefNum;
SndChannelPtr musicChan, monsterbeamChan, maserbeamChan;

#endif

#ifdef LINUXAUDIO

#include "soundIt.h"
#define	 NUM_SAMPLES	12
#define	 SAMPLE_RATE	11000
#define	 NUM_CHANNELS	8

    Sample	snd[NUM_SAMPLES];
    char	*audio_dev = "/dev/dsp";
    int		audiofd;
    int playingBeam, playingMusic;

#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* small sound routines to avoid having to use external variables*/

#ifdef LINUXAUDIO

void killSounds( void )
{
    Snd_restore();
}

#endif

#ifdef MACVERSION
void setSoundVolume(long vol)
	{
	SetDefaultOutputVolume(vol);
	}
#endif

void turnSoundOff()
    {
    soundOn = 0;
    }
    
void turnSoundOn()
    {
    soundOn = 1;
    }
    
void toggleSound()
    {
    soundOn = !soundOn;
    }
    
int getSoundOn()
    {
    return(soundOn);
    }
    
void turnMusicOff()
    {
    musicOn = 0;
    }
    
void turnMusicOn()
    {
    musicOn = 1;
    }
    
void toggleMusic()
    {
    musicOn = !musicOn;
    }
    
int getMusicOn()
    {
    return(musicOn);
    }
    
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void checkSound(char * dataPath)
    {
    char * garbage;

#ifdef SGIAUDIO
    long pvbuf[4];

    ALseterrorhandler(0);

    pvbuf[0] = AL_OUTPUT_COUNT;
    pvbuf[2] = AL_MONITOR_CTL;
    
    if (ALgetparams(AL_DEFAULT_DEVICE, pvbuf, 4) < 0)
	{
	noSound = 1;
	soundOn = 0;
	musicOn = 0;
	}
	
    if (!noSound)
	{  
	/******************************************/
	/* load all the sound effects into memory */
	/******************************************/

	InitAudio("SOUNDS/beam.aiff",        dataPath,  0);
	InitAudio("SOUNDS/boom.aiff",        dataPath,  1);
	InitAudio("SOUNDS/crash.aiff",       dataPath,  2);
	InitAudio("SOUNDS/monsterbeam.aiff", dataPath,  3);
	InitAudio("SOUNDS/rocket.aiff",      dataPath,  4);
	InitAudio("SOUNDS/slag.aiff",        dataPath,  5);
	InitAudio("SOUNDS/tank.aiff",        dataPath,  6);
	InitAudio("SOUNDS/tech.aiff",        dataPath,  7);

	/*********************************************/
	/* load all the background music into memory */
	/*********************************************/

	InitAudio("MUSIC/1.aiff",        dataPath,  10);
	InitAudio("MUSIC/2.aiff",        dataPath,  11);
	InitAudio("MUSIC/3.aiff",        dataPath,  12);
	InitAudio("MUSIC/4.aiff",        dataPath,  13);
	InitAudio("MUSIC/5.aiff",        dataPath,  14);

	InitAudio("MUSIC/d1.aiff",       dataPath,  15);
	InitAudio("MUSIC/d2.aiff",       dataPath,  16);
	InitAudio("MUSIC/d3.aiff",       dataPath,  17);
	InitAudio("MUSIC/d4.aiff",       dataPath,  18);
	InitAudio("MUSIC/d5.aiff",       dataPath,  19);

	}
#else
# ifdef SUNAUDIO
    /* Solaris audio support */

    noSound = 1;
    soundOn = 0;
    musicOn = 0;
    {
	/* Check if audio device is available and writable */
	struct stat st;
	
	if (stat(audio_dev, &st) >= 0) {
	    audiofd = open(audio_dev, O_WRONLY);
	    if (audiofd >= 0) {
		noSound = 0;
		close(audiofd);
	    }
	}
    }

    if (!noSound) {  
	/* Load all sound effects into memory */
	InitAudio("SOUNDS/beam.au",	    dataPath,  0);
	InitAudio("SOUNDS/boom.au",         dataPath,  1);
	InitAudio("SOUNDS/crash.au",        dataPath,  2);
	InitAudio("SOUNDS/monsterbeam.au",  dataPath,  3);
	InitAudio("SOUNDS/rocket.au",       dataPath,  4);
	InitAudio("SOUNDS/slag.au",         dataPath,  5);
	InitAudio("SOUNDS/tank.au",         dataPath,  6);
	InitAudio("SOUNDS/tech.au",         dataPath,  7);

	/* Load all background music into memory */
	InitAudio("MUSIC/1.au",        	    dataPath,  10);
	InitAudio("MUSIC/2.au",		    dataPath,  11);
	InitAudio("MUSIC/3.au",		    dataPath,  12);
	InitAudio("MUSIC/4.au",		    dataPath,  13);
	InitAudio("MUSIC/5.au",		    dataPath,  14);

	InitAudio("MUSIC/d1.au",	    dataPath,  15);
	InitAudio("MUSIC/d2.au",	    dataPath,  16);
	InitAudio("MUSIC/d3.au",	    dataPath,  17);
	InitAudio("MUSIC/d4.au",	    dataPath,  18);
	InitAudio("MUSIC/d5.au",	    dataPath,  19);
    }
#else
#ifdef MACVERSION

SndCommand testCommand;

	beamSound	= GetResource( 'snd ', 1000 );
	boomSound	= GetResource( 'snd ', 1001 );
	crashSound	= GetResource( 'snd ', 1002 );
	monsterbeamSound = GetResource( 'snd ', 1003 );
	rocketSound	= GetResource( 'snd ', 1004 );
	slagSound	= GetResource( 'snd ', 1005 );
	tankSound	= GetResource( 'snd ', 1006 );
	techSound	= GetResource( 'snd ', 1007 );
	musicSound	= GetResource( 'snd ', 1010 );
	
    noSound = 0;
    soundOn = 0;
    musicOn = 0;
    
    /* using the SoundHelper code to do asynch audio */
    
    SHInitSoundHelper(&idleFlag, 8);

SHPlayByHandle(musicSound, -1, &musicRefNum);
SHPlayPause(musicRefNum);
SHPlayByHandle(beamSound, -1, &maserbeamRefNum);
SHPlayPause(maserbeamRefNum);
SHPlayByHandle(monsterbeamSound, -1, &monsterbeamRefNum);
SHPlayPause(monsterbeamRefNum);


# else
#ifdef LINUXAUDIO
    /* Linux audio support */

    noSound = 1;
    soundOn = 0;
    musicOn = 0;
    {
	/* Check if audio device is available and writable */
	struct stat st;
	
	if (stat(audio_dev, &st) >= 0) {
	    audiofd = open(audio_dev, O_WRONLY);
	    if (audiofd >= 0) {
		noSound = 0;
		close(audiofd);
	    }
	}
    }

    if (!noSound) {  
	/* Load all sound effects into memory */
	Snd_loadRawSample("SOUNDS/beam.raw", &snd[0]);
	Snd_loadRawSample("SOUNDS/boom.raw", &snd[1]);
	Snd_loadRawSample("SOUNDS/crash.raw",&snd[2]);
	Snd_loadRawSample("SOUNDS/monsterbeam.raw",&snd[3]);
	Snd_loadRawSample("SOUNDS/rocket.raw",&snd[4]);
	Snd_loadRawSample("SOUNDS/slag.raw",&snd[5]);
	Snd_loadRawSample("SOUNDS/tank.raw",&snd[6]);
	Snd_loadRawSample("SOUNDS/tech.raw",&snd[7]);

	/* Load all background music into memory */

	Snd_loadRawSample("MUSIC/1.raw",&snd[10]);
	Snd_loadRawSample("MUSIC/2.raw",&snd[11]);
/*	Snd_loadRawSample("MUSIC/3.au",&snd[12]);
	Snd_loadRawSample("MUSIC/4.au",&snd[13]);
	Snd_loadRawSample("MUSIC/5.au",&snd[14]);

	Snd_loadRawSample("MUSIC/d1.au",&snd[15]);
	Snd_loadRawSample("MUSIC/d2.au",&snd[16]);
	Snd_loadRawSample("MUSIC/d3.au",&snd[17]);
	Snd_loadRawSample("MUSIC/d4.au",&snd[18]);
	Snd_loadRawSample("MUSIC/d5.au",&snd[19]);
*/
        if (Snd_init( NUM_SAMPLES, snd, SAMPLE_RATE, NUM_CHANNELS, audio_dev )==EXIT_FAILURE){
   	    printf("Can't init soundIt library. yech..\n");
   	    exit(0);
	}
    }
#else

    /*  Other than SGI or Solaris or Macintosh*/
    noSound = 1;
    soundOn = 0;
    musicOn = 0;

#endif
#endif
#endif
#endif

	garbage = dataPath; /* to avoid compiler warning */
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

#ifdef MACVERSION

void processIdleAppSounds(void)
{
	if (idleFlag)
	{
	SHIdle();
	}
}
#endif

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* initialize sound list to empty                                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void initSounds()
    {
#ifdef SGIAUDIO

    register int i;
    
    allSounds = NULL;
    allSounds = (struct sound *) calloc(1, sizeof(struct sound));
    allSounds->next = NULL;

    musicCount		= 0;
    deadCount		= 0;

    playingTankFire = playingHeloRocket = playingTankMaser = 0;
    playingExplosion = playingSlag = playingTech = 0;

    for (i=0; i<MAXSOUNDS; i++)
	{
	oneSound[i].samplesPerFrame	= 0;
	oneSound[i].numberSamples	= 0;
	oneSound[i].samplesPerBuffer	= 0;
	oneSound[i].audioRate		= 0;
	oneSound[i].sampleBuffer	= NULL;
	}

#endif
# ifdef SUNAUDIO

    int n;
    
    musicCount		= 0;
    deadCount		= 0;

    playingTankFire = playingHeloRocket = playingTankMaser = 0;
    playingExplosion = playingSlag = playingTech = 0;
    playingBeam = playingMusic = 0;

    /* Mark audio buffers as empty */
    
    for (n = 0; n < MAXSOUNDS; n++)
	audio_buffer[n] = NULL;

# endif

#ifdef MACVERSION

    musicCount		= 0;
    deadCount		= 0;

    playingTankFire = playingHeloRocket = playingTankMaser = 0;
    playingExplosion = playingSlag = playingTech = 0;
    playingBeam = playingMusic = maserOn = 0;
	playingCrash = 0;


#endif
#ifdef LINUXAUDIO

    int n;
    
    musicCount		= 0;
    deadCount		= 0;

    playingTankFire = playingHeloRocket = playingTankMaser = 0;
    playingExplosion = playingSlag = playingTech = 0;
    playingBeam = playingMusic = 0;

    /* Mark audio buffers as empty */
    
//    for (n = 0; n < MAXSOUNDS; n++)
//	audio_buffer[n] = NULL;

#endif

    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* clear all completed sounds from the sound list                */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void flushSounds()
    {
#ifdef SGIAUDIO

    struct sound *s, *t;

    playingHeloRocket = playingTech = playingTankMaser = playingSlag = 0;

    playingExplosion--;
    if (playingExplosion < 0)
	playingExplosion = 0;

    playingTankFire--;
    if (playingTankFire < 0)
	playingTankFire =  0;

    s = allSounds;
    while(s->next != NULL)
	{
	if(ALgetfilled(s->next->audio_port) <= 0)
	    {
	    ALcloseport(s->next->audio_port);
	    t = s->next;
	    s->next = s->next->next;
	    free(t);
	    }
	else
	    s = s->next;
	}
#endif
# ifdef SUNAUDIO

    playingHeloRocket = playingTech = playingTankMaser = playingSlag = 0;

    playingExplosion--;
    if (playingExplosion < 0)
	playingExplosion = 0;

    playingTankFire--;
    if (playingTankFire < 0)
	playingTankFire = 0;

    playingBeam--;
    if (playingBeam < 0)
	playingBeam = 0;

    playingMusic--;
    if (playingMusic < 0)
	playingMusic = 0;

# endif

#ifdef MACVERSION

	processIdleAppSounds();

    playingTankMaser = playingSlag = 0;

    playingHeloRocket--;
    if (playingHeloRocket < 0)
	playingHeloRocket = 0;

    playingCrash--;
    if (playingCrash < 0)
	playingCrash = 0;

    playingExplosion--;
    if (playingExplosion < 0)
	playingExplosion = 0;

    playingTech--;
    if (playingTech < 0)
	playingTech = 0;

    playingTankFire--;
    if (playingTankFire < 0)
	playingTankFire =  0;
#endif

#ifdef LINUXAUDIO

    playingHeloRocket = playingTech = playingTankMaser = playingSlag = 0;

    playingExplosion--;
    if (playingExplosion < 0)
	playingExplosion = 0;

    playingTankFire--;
    if (playingTankFire < 0)
	playingTankFire = 0;

    playingBeam--;
    if (playingBeam < 0)
	playingBeam = 0;

    playingMusic--;
    if (playingMusic < 0)
	playingMusic = 0;

#endif

    }



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* clear all sounds of a given type from the sound list          */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void soundKiller(int soundType)
    {
    int garbage;
    
#ifdef SGIAUDIO

    struct sound * s, *t;

    s = allSounds;
    
    while(s->next != NULL)
	{
	if (s->next->type == soundType)
	    {
	    ALcloseport(s->next->audio_port);
	    t = s->next;
	    s->next = s->next->next;
	    free(t);
	    }
	else
	    s = s->next;
	}
#endif

#ifdef MACVERSION

	/* stop the sound */

	switch (soundType) {
		case MUSIC: 
			/*if (playingMusic)*/
				{
				/* SHPlayStop(musicRefNum);*/
				SHPlayPause(musicRefNum);
				playingMusic = 0;
				}
			break;
		case MONSTERBEAM:
			/*if (playingBeam)*/
				{
				/*SHPlayStop(monsterbeamRefNum);*/
				SHPlayPause(monsterbeamRefNum);
				playingBeam = 0;
				}
			break;
	
		case TANKMASER:
		/*	if (maserOn)*/
				{
				/*SHPlayStop(maserbeamRefNum);*/
				SHPlayPause(maserbeamRefNum);
				maserOn = 0;
				}
			break;
				
}
#endif

#ifdef LINUXAUDIO
/*
printf("callkill %d... ", soundType);
    if (soundType == MUSIC) {
	Snd_effect( 10, -1 );
	Snd_effect( 11, -1 );
    }
*/
#endif

    garbage = soundType; /* to avoid compiler warning */
    }
 
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* process a request for a specific sound                        */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

void doSound(int theSound)
    {
    int garbage;

#ifdef SGIAUDIO

static int deadMusic[MAXDEADMUSIC] = {15, 16, 17, 18, 19};

static int theMusic[MAXMUSIC] = {10, 11, 12, 13, 14};


    struct sound * s, *t;
    int soundDelay;

    if (!noSound)
	{
	soundDelay = showframes;

	if (soundDelay <= 1)
	    soundDelay = 1;

	if (soundDelay > 30)
	    soundDelay = 30;
  
	if (((theSound == MUSIC) && musicOn) || ((theSound != MUSIC) && soundOn))
	    {
	    t = NULL;

	    switch (theSound){
	    case MUSIC:		s = allSounds->next;
				while ((s != NULL) && (t == NULL))
				    if (s->type == MUSIC)
					t = s;
				    else
					s = s->next;
					
				if (Googelon.monsterIsDead)
				    {
				    musicCount = 0;
				    if ((t != NULL) && (deadCount < MAXDEADMUSIC))
					{
					if ((ALgetfilled(t->audio_port)+oneSound[deadMusic[deadCount]].numberSamples < 2*oneSound[10].samplesPerBuffer) && (deadCount < 3))
					    {
					    ALwritesamps(t->audio_port,
							oneSound[deadMusic[deadCount]].sampleBuffer,
							oneSound[deadMusic[deadCount]].numberSamples);
					    deadCount = deadCount+1;
					    }
					}
				    else if (deadCount < MAXDEADMUSIC)
					{
					OutAudio(deadMusic[deadCount]);
					deadCount = deadCount+1;
					}
				    }
				else
				    {
				    deadCount = 0;
				    if (t != NULL)
					{
					if(ALgetfilled(t->audio_port)+oneSound[theMusic[musicCount]].numberSamples < 2*oneSound[10].samplesPerBuffer)
					    {
					    ALwritesamps(t->audio_port,
							oneSound[theMusic[musicCount]].sampleBuffer,
							oneSound[theMusic[musicCount]].numberSamples);
					    musicCount = (musicCount+1) % MAXMUSIC;
					    }
					}
				    else
					{
					OutAudio(theMusic[musicCount]);
					musicCount = (musicCount+1) % MAXMUSIC;
					}
					
				    }
				break;
				
	    case TANKFIRE:	if (!playingTankFire)
				    {
				    OutAudio(6);
				    playingTankFire = soundDelay / 5;
				    if (playingTankFire < 2)
					playingTankFire = 2;
				    }
				break;
				
	    case HELOROCKET:    if (!playingHeloRocket)
				    {
				    OutAudio(4);
				    playingHeloRocket = 1;
				    }
				break;
				
	    case TANKMASER:	s = allSounds->next;
				while ((s != NULL) && (t == NULL))
				    if (s->type == TANKMASER)
					t = s;
				    else
					s = s->next;
				if (t != NULL)
				    {
				    if(ALgetfilled(t->audio_port) <= oneSound[0].samplesPerBuffer)
					ALwritesamps(t->audio_port,
						    oneSound[0].sampleBuffer,
						    oneSound[0].numberSamples);
				    }
				else
				    OutAudio(0);
				break;
				
	    case EXPLOSION:	if (!playingExplosion)
				    {
				    OutAudio(1);
				    playingExplosion = soundDelay / 5; 
				    if (playingExplosion < 2)
					playingExplosion = 2;
				    }
				break;
				
	    case MONSTERBEAM:	s = allSounds->next;
				while ((s != NULL) && (t == NULL))
				    if (s->type == MONSTERBEAM)
					t = s;
				    else
					s = s->next;
				if (t != NULL)
				    {
				    if(ALgetfilled(t->audio_port) <= oneSound[3].samplesPerBuffer)
					ALwritesamps(t->audio_port,
						    oneSound[3].sampleBuffer,
						    oneSound[3].numberSamples);
				    }
				else
				    OutAudio(3);
				break;
				
	    case SLAG:		if (!playingSlag)
				    {
				    OutAudio(5);
				    playingSlag = 1;
				    }
				break;
				
	    case CRASH:		OutAudio(2);
				break;
				
	    case TECHSHOOT:    if (!playingTech)
				    {
				    OutAudio(7);
				    playingTech = 1;
				    }
				break;
	    }
	}
    }

#endif
# ifdef SUNAUDIO

static int deadMusic[MAXDEADMUSIC] = {15, 16, 17, 18, 19};

static int theMusic[MAXMUSIC] = {10, 11, 12, 13, 14};

    int soundDelay;

    if (!noSound) {
	soundDelay = showframes;

	if (soundDelay <= 1)
	    soundDelay = 1;

	if (soundDelay > 30)
	    soundDelay = 30;
  
	if (((theSound == MUSIC) && musicOn) ||
	    ((theSound != MUSIC) && soundOn)) {

	    switch (theSound) {
	    case MUSIC:
		if (!playingMusic) {
		    OutAudio(theMusic[musicCount]);
		    musicCount = (musicCount+1) % MAXMUSIC;

		    /* each music sample is 5 secs long */
		    playingMusic =  soundDelay * 5; ;
		}
		break;

	    case TANKFIRE:
		if (!playingTankFire) {
		    OutAudio(6);
		    playingTankFire = soundDelay / 5;
		    if (playingTankFire < 2)
			playingTankFire = 2;
		}
		break;
				
	    case HELOROCKET:
		if (!playingHeloRocket) {
		    OutAudio(4);
		    playingHeloRocket = 1;
		}
		break;
				
	    case TANKMASER:
		    OutAudio(0);
		break;
				
	    case EXPLOSION:
		if (!playingExplosion) {
		    OutAudio(1);
		    playingExplosion = soundDelay / 5; 
		    if (playingExplosion < 2)
			playingExplosion = 2;
		}
		break;
				
	    case MONSTERBEAM:
		if (!playingBeam) {
		    OutAudio(3);
		    playingBeam = 5 /*soundDelay / 5*/;
		}
		break;
				
	    case SLAG:
		if (!playingSlag) {
		    OutAudio(5);
		    playingSlag = 1;
		}
		break;
				
	    case CRASH:
		OutAudio(2);
		break;
				
	    case TECHSHOOT:
		if (!playingTech) {
		    OutAudio(7);
		    playingTech = 1;
		}
		break;
	    }
	}
    }

#endif
#ifdef LINUXAUDIO

static int deadMusic[MAXDEADMUSIC] = {15, 16};

static int theMusic[MAXMUSIC] = {10, 11};

    int soundDelay;
    
//    printf("doSound -> %d\n", theSound);

    if (!noSound) {
	soundDelay = showframes;

	if (soundDelay <= 1)
	    soundDelay = 1;

	if (soundDelay > 30)
	    soundDelay = 30;
  
	if (((theSound == MUSIC) && musicOn) ||
	    ((theSound != MUSIC) && soundOn)) {

	    switch (theSound) {
	    case MUSIC:
		if (!playingMusic) {
		    OutAudio(theMusic[musicCount]);
		    musicCount = (musicCount+1) % MAXMUSIC;
//printf("Music start\n");
		    /* each music sample is 5 secs long */
		    playingMusic =  soundDelay * 20; ;
		}
		break;

	    case TANKFIRE:
		if (!playingTankFire) {
		    OutAudio(6);
		    playingTankFire = soundDelay / 5;
		    if (playingTankFire < 2)
			playingTankFire = 2;
		}
		break;
				
	    case HELOROCKET:
		if (!playingHeloRocket) {
		    OutAudio(4);
		    playingHeloRocket = 1;
		}
		break;
				
	    case TANKMASER:
		    OutAudio(0);
		break;
				
	    case EXPLOSION:
		if (!playingExplosion) {
		    OutAudio(1);
		    playingExplosion = soundDelay / 5; 
		    if (playingExplosion < 2)
			playingExplosion = 2;
		}
		break;
				
	    case MONSTERBEAM:
		if (!playingBeam) {
		    OutAudio(3);
		    playingBeam = 5 /*soundDelay / 5*/;
		}
		break;
				
	    case SLAG:
		if (!playingSlag) {
		    OutAudio(5);
		    playingSlag = 1;
		}
		break;
				
	    case CRASH:
		OutAudio(2);
		break;
				
	    case TECHSHOOT:
		if (!playingTech) {
		    OutAudio(7);
		    playingTech = 1;
		}
		break;
	    }
	}
    }

#endif

/*------------------------ Mac Specific code --------------------*/

#ifdef MACVERSION
    int soundDelay;

    if (!noSound)
	{
	soundDelay = showframes;

	if (soundDelay <= 1)
	    soundDelay = 1;

	if (soundDelay > 30)
	    soundDelay = 30;
  
	if (((theSound == MUSIC) && musicOn) || ((theSound != MUSIC) && soundOn))
	    {    
	    switch (theSound){
	    case MUSIC: if (!playingMusic)
	    				{
	    				/*SHPlayByHandle(musicSound, &musicRefNum);*/
	    				SHPlayContinue(musicRefNum);
	    				playingMusic = 1;
	    				}
				break;
				
	    case TANKFIRE:if (!playingTankFire)
					    { /* different from sun version */
					    SHPlayByHandle(tankSound, 1, nil);

					    playingTankFire = soundDelay / 5;
					    if (playingTankFire < 3)
						playingTankFire = 3;
					    }
				break;
				
	    case HELOROCKET:
			if (!playingHeloRocket)
				{ /* different from sun version */
			    SHPlayByHandle(rocketSound, 1, nil);
			    
			    playingHeloRocket = soundDelay / 5;
			    if (playingHeloRocket < 3)
					playingHeloRocket = 3;
			    
				}
			break;
				

	    case TANKMASER:
	    			if (!maserOn)
	    		 		{
	    		 		/*SHPlayByHandle(beamSound, &maserbeamRefNum);*/
	    		 		SHPlayContinue(maserbeamRefNum);

	    		 		maserOn = 1;
	    		 		}
				break;
				
	    case EXPLOSION:
				if (!playingExplosion)
					{ /* different from sun version */
				     SHPlayByHandle(boomSound, 1, nil);
				     
				    playingExplosion = soundDelay / 5; 
				    if (playingExplosion < 3)
					playingExplosion = 3;
					}   
				break;
				
	    case MONSTERBEAM:
	    		if (!playingBeam)
	    			{
	    			/*SHPlayByHandle(monsterbeamSound, &monsterbeamRefNum);*/
	    			SHPlayContinue(monsterbeamRefNum);
	    			
	    			playingBeam = 1;
	    			}
				break;
				
	    case SLAG:
				if (!playingSlag) {
				    SHPlayByHandle(slagSound, 1, nil);
				    
				    playingSlag = 1;
				}		    
				break;
				
	    case CRASH:	
	    		if (!playingCrash)
	    			{
	    			SHPlayByHandle(crashSound, 1, nil);

				    playingCrash = 2;
				    }
				break;
				
	    case TECHSHOOT:
				if (!playingTech)
					{ /* different from sun version */
				    SHPlayByHandle(techSound, 1, nil);
				    
				    playingTech = 2;
					}		    
				break;
	    }
	}
    }
#endif
    garbage = theSound;
}



/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* output a particular sound                                     */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


void OutAudio(int sCounter)
    {
    int garbage;
    
#ifdef SGIAUDIO

    ALconfig audioPortConfig;
    long pvbuf[4];
    long outputRate;
    struct sound * s;
        
    pvbuf[0] = AL_OUTPUT_RATE;
    ALgetparams(AL_DEFAULT_DEVICE, pvbuf, 2);

    if (pvbuf[1] > 0) 
	outputRate = pvbuf[1];
    else 
	outputRate = AL_RATE_UNDEFINED;
    
    pvbuf[0] = AL_OUTPUT_COUNT;
    pvbuf[2] = AL_MONITOR_CTL;
    ALgetparams(AL_DEFAULT_DEVICE, pvbuf, 4);
    
    if ((outputRate != oneSound[sCounter].audioRate) || ((pvbuf[1] == 0) && (pvbuf[3] == AL_MONITOR_OFF)))
	{
	outputRate = oneSound[sCounter].audioRate;
	pvbuf[0] = AL_OUTPUT_RATE;
	pvbuf[1] = outputRate;
	ALsetparams(AL_DEFAULT_DEVICE, pvbuf, 2);
	}
  
    audioPortConfig = ALnewconfig();
    ALsetwidth(audioPortConfig, AL_SAMPLE_16);
    ALsetchannels(audioPortConfig, oneSound[sCounter].samplesPerFrame);
    
     switch(sCounter){
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
	case 7:	    ALsetqueuesize(audioPortConfig, oneSound[sCounter].samplesPerBuffer);
		    break;
	case 0:
	case 3:	    ALsetqueuesize(audioPortConfig, 2*oneSound[sCounter].samplesPerBuffer);
		    break;
	default:    ALsetqueuesize(audioPortConfig, 3*oneSound[sCounter].samplesPerBuffer);
		    break;
    }
    
    s = (struct sound *) calloc(1, sizeof(struct sound));
	
    if (s != NULL)
	{
        if (sCounter == 3)
	    s->type = MONSTERBEAM;
	else if (sCounter == 0)
	    s->type = TANKMASER;
	else if (sCounter >= 10)
	    s->type = MUSIC;
	else
	    s->type = -1;

	s->next = allSounds->next;
	allSounds->next = s;

	s->audio_port = ALopenport("battalion", "w", audioPortConfig);
	if (s->audio_port == 0)
	    {
	    showError("too many simultaneous sounds");
	    allSounds->next = s->next;
	    free(s);
	    }
	else
	    ALwritesamps(s->audio_port, oneSound[sCounter].sampleBuffer, oneSound[sCounter].numberSamples);
	}

#endif
# ifdef SUNAUDIO

    static int first = 1;

    /* Check if a valid buffer and buffer contains a sample */
    
    if (sCounter < 0 || sCounter >= MAXSOUNDS ||
		audio_buffer[sCounter] == NULL)
	return;

    if (first) {
	first = 0;

	/* Open audio device */
	
	audiofd = open(audio_dev, O_WRONLY /*| O_NDELAY | O_NONBLOCK*/);
	if (audiofd < 0)
	    return;
    }
	
    audio_flush_play(audiofd);

    if (write(audiofd, audio_buffer[sCounter], buffer_counter[sCounter]) < 0)
	fprintf(stderr, "audio_play: buffer %d failed\n", sCounter);

    
# endif
#ifdef LINUXAUDIO

    static int first = 1;
    
    /* Check if a valid buffer and buffer contains a sample */
    
//    printf("Sound N --> %d \n", sCounter);
    
    if (sCounter < 0 || sCounter >= NUM_SAMPLES) return;


    Snd_effect( sCounter, sCounter );
    
# endif

    garbage = sCounter; /* to avoid compiler warning */
    }

/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
/* load a particular sound into memory                           */
/*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


void InitAudio(char * fileName,  char * dataPath, int sCounter)
    {
    char * garbName,  * garbPath;
    int garbCount;
    
#ifdef SGIAUDIO

    /* IRIX 6 compilers want these next two to be integers 
     * while IRIS 5 compilers want them to be long ... sheesh */

    int bitsPerSample;
    int garbage;

    long framesPerBuffer;
    long framesRead;
    FILE * sndtest;
    AFfilehandle audioFile;
    char textBuffer[80];
    char fullPath[MAXPATH];
    
    
    bitsPerSample   = 0;
    framesPerBuffer = 0;
    garbage	    = 0;
    framesRead	    = 0;
    
    strcpy(fullPath, dataPath);
    strcat(fullPath, fileName);
    
    sndtest = fopen(fullPath, "rb");
    if (sndtest == NULL)
	{
	sprintf(textBuffer, "Could not load %s", fullPath);
	showError(textBuffer);
	}
    else
	{	
	fclose(sndtest);
	
	audioFile = AFopenfile(fullPath, "r", AF_NULL_FILESETUP);
    
	oneSound[sCounter].samplesPerFrame = AFgetchannels(audioFile, AF_DEFAULT_TRACK);
    
	AFgetsampfmt(audioFile, AF_DEFAULT_TRACK, &garbage, &bitsPerSample);
    
	oneSound[sCounter].audioRate  = (long) (AFgetrate(audioFile, AF_DEFAULT_TRACK));
       
	if (bitsPerSample != 16)
	    {
	    sprintf(textBuffer, "incorrect sound format for %s - should be 16-bits", fileName);
	    showError(textBuffer);
	    }
	
	framesPerBuffer = AFgetframecnt(audioFile, AF_DEFAULT_TRACK);
    
	oneSound[sCounter].samplesPerBuffer = framesPerBuffer * oneSound[sCounter].samplesPerFrame;
    
	oneSound[sCounter].sampleBuffer = (short *) calloc((unsigned) oneSound[sCounter].samplesPerBuffer, sizeof(short));
    
	AFseekframe(audioFile, AF_DEFAULT_TRACK, 0);
    
	framesRead = AFreadframes(audioFile, AF_DEFAULT_TRACK, oneSound[sCounter].sampleBuffer, framesPerBuffer);

	AFclosefile(audioFile);

	oneSound[sCounter].numberSamples = framesRead * oneSound[sCounter].samplesPerFrame;
	}

#endif
# ifdef SUNAUDIO
	   
    int	    error;
    int	    count;
    char    audioFile[MAXPATH];

    strcpy(audioFile, dataPath);
    strcat(audioFile, fileName);

    if ((audiofd = open(audioFile, O_RDONLY, 0)) < 0) {
	fprintf(stderr, "audio_load: cannot open %s\n", audioFile);
	exit(1);
    }

    error = audio_read_filehdr(audiofd, &file_hdr, (char *)NULL, 0);

    if (error != AUDIO_SUCCESS) {
	fprintf(stderr, "audio_load: %s is not a valid audio file\n",
		audioFile);
	exit(-1);
    }

    if (audio_buffer[sCounter]) {
	free(audio_buffer[sCounter]);
	audio_buffer[sCounter] = NULL;
    }

    audio_buffer[sCounter] = (char *)malloc(file_hdr.data_size);

    if ((count = read(audiofd, audio_buffer[sCounter],
			  file_hdr.data_size)) < 0) {
	fprintf(stderr, "audio_load: error reading\n");
	close(audiofd);
    }

    buffer_counter[sCounter] = count;
    close(audiofd);

# endif

#ifdef LINUXAUDIO

#endif

    garbName  = fileName;
    garbPath  = dataPath;
    garbCount = sCounter;

    }
