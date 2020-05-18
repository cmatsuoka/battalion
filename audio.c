/*****************************************************************/
/*                                                               */
/* This file has been included in the 2004 release of battalion  */
/* It contains the implementation of all sound related functions */
/*                                                               */
/*****************************************************************/
/*                                                               */
/*                                                               */
/*                                                               */
/*                                                               */
/*                                                               */
/*                                                               */
/* Author: J.Alemany Rubio                                       */
/*                                                               */
/*****************************************************************/

/*****************************************************************/
/* openAL headers*/

#include "audio.h"

#include <stdio.h>
#include <AL/al.h>
#include <AL/alut.h>

#include "battalion.h"

extern int noSound;

int soundOn = 1;
int musicOn = 1;

int maxSources = 0;


struct audioSource
{
    ALuint nsource;
    ALint state;
};

#define NUM_BUFFERS  15
#define NUM_SOURCES  30


/**************************************************************** 
           OpenAL 
*****************************************************************/
ALfloat listenerPos[] = {0.0,0.0,1.0};
ALfloat listenerVel[] = {0.0,0.0,0.0};
ALfloat	listenerOri[] = {0.0,0.0,-1.0, 0.0,1.0,0.0};

ALuint	buffers[NUM_BUFFERS];
ALuint  sources[NUM_SOURCES];

/****************************************************************/
/*              Functions used by the program                   */
/****************************************************************/

static int load_sound(ALuint *buffer, char *dataPath, char *asset)
{
    char *filename = alloca(strlen(dataPath) + strlen(asset) + 10);
    sprintf(filename, "%s/SOUNDS/%s", dataPath, asset);
    *buffer = alutCreateBufferFromFile(filename);

    if (alutGetError() != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "error: cannot load sound file %s\n", filename);
        return -1;
    }

    return 0;
}

static int load_music(ALuint *buffer, char *dataPath, char *asset)
{
    char *filename = alloca(strlen(dataPath) + strlen(asset) + 10);
    sprintf(filename, "%s/MUSIC/%s", dataPath, asset);
    *buffer = alutCreateBufferFromFile(filename);

    if (alutGetError() != ALUT_ERROR_NO_ERROR) {
        fprintf(stderr, "error: cannot load music file %s\n", filename);
        return -1;
    }

    return 0;
}

/****************************************************************/
/* Must be called first, at the beginning of the program        */
/****************************************************************/
int initSound(char *dataPath)
{
    register int i;
    
    if (!alutInit(NULL, NULL)) {
        ALenum err = alutGetError();
        if (err != ALUT_ERROR_NO_ERROR) {
            fprintf(stderr, "error: %s\n", alutGetErrorString(err));
        }
        return -1;
    };

    alGetError();
    
    /* Buffer generation */
    alGenBuffers(NUM_BUFFERS, buffers);
    
    if(alGetError() != AL_NO_ERROR)
	{
		printf("- Error creating buffers !!\n");
		return -1;
	}

	/* load samples in wav format*/
        load_sound(&buffers[0], dataPath, "beam.wav");
        load_sound(&buffers[1], dataPath, "boom.wav");
        load_sound(&buffers[2], dataPath, "crash.wav");
        load_sound(&buffers[3], dataPath, "monsterbeam.wav");
        load_sound(&buffers[4], dataPath, "rocket.wav");
        load_sound(&buffers[5], dataPath, "slag.wav");
        load_sound(&buffers[6], dataPath, "tank.wav");
        load_sound(&buffers[7], dataPath, "tech.wav");
        load_sound(&buffers[8], dataPath, "electrical.wav");
        load_sound(&buffers[9], dataPath, "teleporter.wav");
        load_music(&buffers[10], dataPath, "mbatt1.wav");
        load_music(&buffers[11], dataPath, "mbatt2.wav");
        load_music(&buffers[12], dataPath, "mbatt3.wav");
        load_music(&buffers[13], dataPath, "mbatt4.wav");
	
	/* Source generation */
	alGenSources(NUM_SOURCES, sources);
	
    if(alGetError() != AL_NO_ERROR)
    {
    
		printf("- Error creating sources !!\n");
		alGenSources(8, sources);
    		if(alGetError() != AL_NO_ERROR)
			maxSources = 0;		
		else
			maxSources = 8;
		
	}
    else
	    maxSources = NUM_SOURCES;
	
   /* source[0] is the monster source, source[1] is music source */
   float gain = 0.4f;  // TODO: make it configurable
   alSourcef(sources[1], AL_GAIN, gain);
   for(i=2; i<maxSources; i++)
   {
        alSourcef(sources[i],AL_GAIN, gain);
        alSourcef(sources[i],AL_PITCH,1.0f);
        alSource3f(sources[i],AL_POSITION,0,0,0);
        alSource3f(sources[i],AL_VELOCITY,0,0,0);
        alSourcei(sources[i],AL_LOOPING,AL_FALSE);
        
        /* distance model */
        alSourcef(sources[i],AL_ROLLOFF_FACTOR,0.8f);
        alSourcef(sources[i],AL_REFERENCE_DISTANCE,20.0f);
    }
	
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
    alListenerfv(AL_ORIENTATION,listenerOri);
	
    return 0;
}





/****************************************************************/
/*              Functions used by the program                   */
/****************************************************************/

/*--------------------------------------------------------------*/


/********************************************
     Possible states:
           
                AL_INITIAL
                AL_PLAYING
                AL_PAUSED
                AL_STOPPED 
*********************************************/

ALuint getFreeSource()
{
    ALuint nsource;
    ALint state;
    int i;
    
    nsource = 0;
    
    /* there are three sources reserved to monster and music */
    for(i=2; i<maxSources  && nsource == 0; i++)
   	{
        alGetSourcei(sources[i], AL_SOURCE_STATE, &state);
   	
        if(state != AL_PLAYING)
        {
            nsource = sources[i];
            break;
        }
   	}
   	return nsource;
}


int isIdle(ALuint nsource)
{
    ALint state;
    alGetSourcei(nsource, AL_SOURCE_STATE, &state);
   	
    if(state != AL_PLAYING)
        return 1;
    
    /*else*/
    return 0; 
}

ALuint getPlayersSource()
{
    /* Our monster is always at 0,0,0 */
    alSource3f(sources[0],AL_POSITION, 0,0,0);
    return sources[0];
}

void exitSound()
{
    alDeleteSources( maxSources, sources );
    alDeleteBuffers( NUM_BUFFERS, buffers );
    
    alutExit();

    return;
}

/* adds a sound */
int doSound(ALuint nsource, int nbuffer, ALboolean loop)
{
    if(soundOn != 0 && maxSources > 0)
    {
        alSourceStop(nsource);
	alSourcei(nsource,AL_BUFFER, buffers[nbuffer]);
	alSourcei(nsource, AL_LOOPING, loop);
	alSourcePlay(nsource);
	return 0;
    }
    return -1;
}

int doSoundAt(ALuint nsource, int nbuffer, ALboolean loop,
              float x, float y, float z)
{
    ALfloat position[3];
    if(soundOn != 0 && maxSources > 0)
    {
        position[0] = x;
        position[1] = y;
        position[2] = z;

        alGetError();  
        alSourceStop(nsource); 
        alSourcei(nsource,AL_BUFFER, buffers[nbuffer]);
        alSourcefv(nsource,AL_POSITION, position);
        alSourcei(nsource, AL_LOOPING, loop);
        alSourcePlay(nsource);
   	return 0;
    }
    return -1;
}

int playMusic(int nmusic, ALboolean loop)
{
    if(maxSources>0)
    {
	alSourceStop(sources[ID_MUSIC]);
    	alSourcei(sources[ID_MUSIC],AL_BUFFER, buffers[MUSIC_OFFSET+nmusic]);
    	alSourcei(sources[ID_MUSIC], AL_LOOPING, loop);
	alSourcePlay(sources[ID_MUSIC]);
    
    	return 0;
    }
    return -1;
}

int stopMusic()
{
    alSourceStop(sources[ID_MUSIC]);
    
    return 0;
}

/*--------------------------------------------------------------*/
/*this is for removing loop-sounds */
int stopSound(ALuint source)
{
    alSourceStop(source);
    return 0;
}

int stopAllSounds()
{
   register int i;
   /* there are two sources reserved to monster and music */
    for(i=2; i<maxSources; i++)
    {
        alSourceStop(sources[i]);
    } 
    return 0;
}

/*--------------------------------------------------------------*/
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
    alSourceStop(sources[ID_MUSIC]);
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
    
/*--------------------------------------------------------------*/    
