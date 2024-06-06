//
// Created by Administrator on 2024/4/8.
//

#ifndef PVZ_TV_1_1_5_MUSIC_H
#define PVZ_TV_1_1_5_MUSIC_H
#include "../Enums.h"
void Music2_StopAllMusic(Music2* music);
void Music2_StartGameMusic(Music2* music, bool start);
void Music2_GameMusicPause(Music2* music,bool pause);
void Music2_FadeOut(Music2* music,int aFadeOutDuration);
void (*Music2_Delete)(Music2* music);
void (*Music_Music)(Music*);
void Music2_Music2(Music2*);
void (*Sexy_AudiereMusicInterface_SetVolume)(int *interface, double theVolume);
void (*Sexy_AudiereMusicInterface_SetSongVolume)(int *interface, int theSongId, double theVolume);
void (*Sexy_AudiereMusicInterface_PlayMusic)(int* interface,int,int,bool noLoop);
void (*Music_StopAllMusic)(Music*);
void Music_MusicResync(Music*);
int (*Music_GetMusicOrder)(Music*,MusicFile::MusicFile);
void Music_StartBurst(Music* music);
void Music_PlayFromOffset(Music*,MusicFile::MusicFile,int,double);
void (*Music_SetupMusicFileForTune)(Music*,MusicFile::MusicFile,MusicTune::MusicTune);
void (*Sexy_AudiereMusicInterface_StopMusic)(int*,int);
void (*Sexy_AudiereMusicInterface_SetChannelVolume)(int*,int,int,float);
void Music_UpdateMusicBurst1(Music*);
void Music_UpdateMusicBurst2(Music*);
#endif //PVZ_TV_1_1_5_MUSIC_H
