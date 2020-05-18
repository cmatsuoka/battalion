#ifndef BATTALION_AUDIO_H_
#define BATTALION_AUDIO_H_

#include <AL/al.h>

void turnSoundOff();
void turnSoundOn();
void toggleSound();
int getSoundOn();

void turnMusicOff();
void turnMusicOn();
void toggleMusic();
int getMusicOn();

int initSound();
void exitSound();

int doSound(ALuint nsource, int nbuffer, ALboolean loop);
int doSoundAt(ALuint nsource, int nbuffer, ALboolean loop, float x, float y, float z);
int stopSound(ALuint source);
int stopAllSounds();
ALuint getPlayersSource();
ALuint getFreeSource();

int playMusic(int source, ALboolean loop);
int stopMusic();

#endif  // BATTALION_AUDIO_H_
