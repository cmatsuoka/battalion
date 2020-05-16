/* SoundIt library 0.03

   Copyright 1994 Brad Pitzel  pitzel@cs.sfu.ca

   Feel free to use/distribute/modify as long as proper credits
   are included.
*/
 
/* Designed for digital sound effects in games.

   Will mix channels of mono 8-bit raw samples, & play back in "real-time".
   Each channel can only play one sample at a time, but all
   channels can play a different sample simultaneously.                 
   
   If you have sox, use the ' -t .ub ' option to make samples
   that this library will play properly.

   I wrote this in C, instead of C++, so hopefully a few more people will
   take a look and make it better :-)
*/

#ifndef SOUNDIT_VERS
#define SOUNDIT_VERS "0.03"

#include <stdlib.h>
#include <stdio.h>

/* 00002 = 2 fragments   */
/* 00007 = means each fragment is 2^7 or 128 bytes */
/* See voxware docs (in /usr/src/linux/drivers/sound) for more info */
#define FRAG_SPEC 0x00020007

/*==========================================================================*/
struct Sample
    {
    unsigned char *data;	/* unsigned 8-bit raw samples */
    int len;			/* length of sample in bytes  */
    };

typedef struct Sample Sample;

/* given the name of a .raw sound file, load it into the Sample struct */ 
/* pointed to by 'sample'                                              */
int
Snd_loadRawSample( const char *file, Sample *sample );


/*==========================================================================*/
/* init sound device, etc..                                                 */
/* num_snd  = the number of samples in the sample array *sa                 */
/* sa       = the sample array						    */
/* freq     = the rate (Hz) to play back the samples                        */
/* channels = # of channels to mix                                          */
/* sound_device = a char string for the sound device, eg, "/dev/dsp"        */
/* returns: 0=success, -1=failure.*/
int 
Snd_init( int num_snd, const Sample *sa, int freq, 
          int channels, const char *sound_device );


/* shutdown sample player, free mem, etc/etc..*/
int 
Snd_restore();


/* play a sound effect in the given channel 1..n*/
/* volume = integers from 0 (off) to 100 (full volume)*/
int 
Snd_effect( int nr, int channel );


/* stop a channel (1..n) from playing*/
/*void 
Snd_reset(enum snd_channel channel);*/
	

/* stop all channels from playing*/
/*void 
Snd_reset();*/
	
	
#endif
