//
// Created by Administrator on 2024/4/8.
//

#ifndef PVZ_TV_1_1_5_MUSIC_CPP
#define PVZ_TV_1_1_5_MUSIC_CPP

#include "HookGame/Enums.h"
#include "Music.h"
#include "HookGame/HookAddr.h"

void (*old_Music_StartGameMusic)(Music *music, bool a2);

void Music_StartGameMusic(Music *music, bool a2) {
    old_Music_StartGameMusic(music, a2);
}

bool muteMusic = false;
int theCounter = 0;

void Music_SetupMusicFileForTune1(Music *music, MusicFile::MusicFile theMusicFile, MusicTune::MusicTune tune){

    int v7; // r7
    int v9; // r9
    int v10; // r8
    int v11; // r4
    int v8;
    float v13; // r3
    bool v14; // r2
    int v15; // r2

    if (tune == MusicTune::DayGrasswalk) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v8 = -1;
                v7 = 23;
                v9 = 0;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 26;
                v9 = 24;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v7 = 27;
                v8 = -1;
                v9 = 27;
                v10 = 29;
                break;
        }
    } else if (tune == MusicTune::PoolWaterygraves) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v8 = -1;
                v7 = 17;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 28;
                v9 = 18;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v8 = 29;
                v7 = 24;
                v10 = 29;
                v9 = 18;
                break;
        }
    } else if (tune == MusicTune::FogRigormormist) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v9 = 0;
                v8 = -1;
                v7 = 15;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 22;
                v9 = 16;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v7 = 23;
                v8 = -1;
                v9 = 23;
                v10 = 29;
                break;
        }
    } else if (tune == MusicTune::RoofGrazetheroof) {
        switch (theMusicFile) {
            case MusicFile::MUSIC_FILE_MAIN_MUSIC:
                v8 = -1;
                v7 = 17;
                v9 = 0;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_DRUMS:
                v8 = -1;
                v7 = 20;
                v9 = 18;
                v10 = 29;
                break;
            case MusicFile::MUSIC_FILE_HIHATS:
                v7 = 21;
                v8 = -1;
                v9 = 21;
                v10 = 29;
                break;
        }
    } else if ((unsigned int) (theMusicFile - 1) <= 2) {
        v7 = 29;
        v9 = 0;
        v10 = 29;
        v8 = -1;
    } else {
        v8 = -1;
        v10 = 0;
        v7 = -1;
        v9 = -1;
    }
    v11 = 0;
    do
    {
        v13 = 1.0;
        v14 = v11 <= v7;
        if ( v11 < v9 )
            v14 = 0;
        if ( !v14 )
        {
            if ( v8 == v11 )
                v13 = 1.0;
            else
                v13 = 0.0;
        }
        v15 = v11++;
        Sexy_AudiereMusicInterface_SetChannelVolume(music->mMusicInterface,theMusicFile,v15,v13);
    }
    while ( v10 >= v11 );
}


void Music_PlayFromOffset(Music *music, MusicFile::MusicFile theMusicFile, int theOffset, double theVolume) {
    Sexy_AudiereMusicInterface_StopMusic(music->mMusicInterface, theMusicFile);
    Music_SetupMusicFileForTune(music,theMusicFile,music->mCurMusicTune);
    Sexy_AudiereMusicInterface_PlayMusic(music->mMusicInterface, theMusicFile, theOffset, theMusicFile == MusicFile::MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN);
//    Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, theMusicFile, theVolume);

    if (theMusicFile == MusicFile::MUSIC_FILE_MAIN_MUSIC) {
        // 加90ms静音，用于去除莫名其妙的开头鼓点声
        muteMusic = true;
        // theCounter = (Sexy_SexyAppBase_GetDialog(music->mApp,Dialogs::DIALOG_STORE) == NULL || Sexy_SexyAppBase_GetDialog(music->mApp,Dialogs::DIALOG_ALMANAC) == NULL) ? 10 : 18;
        theCounter = 10;
        Sexy_AudiereMusicInterface_SetVolume(music->mMusicInterface, 0.0);
    }
}

void Music_PlayMusic(Music *music, MusicTune::MusicTune tune, int theOffset, int theDrumsOffset) {

    if (music->mMusicDisabled) return;
    music->mLastMusicTune = tune;
    music->mCurMusicTune = tune;
    music->mCurMusicFileMain = MusicFile::MUSIC_FILE_NONE;
    music->mCurMusicFileDrums = MusicFile::MUSIC_FILE_NONE;
    music->mCurMusicFileHihats = MusicFile::MUSIC_FILE_NONE;
    switch (tune) {
        case MusicTune::DayGrasswalk:
            if (theOffset == -1) {
                theOffset = 0;
            }
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            music->mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            music->mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(music, music->mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(music, music->mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::NightMoongrains:
            if (theOffset == -1) {
                theDrumsOffset = 0;
                theOffset = 48;
            }
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            music->mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS_NIGHTMOONGRAINS;
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(music, music->mCurMusicFileDrums, theDrumsOffset, 0.0);
            break;
        case MusicTune::PoolWaterygraves:
            if (theOffset == -1) {
                theOffset = 94;
            }
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            music->mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            music->mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(music, music->mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(music, music->mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::FogRigormormist:
            if (theOffset == -1) {
                theOffset = 125;
            }
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            music->mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            music->mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(music, music->mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(music, music->mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::RoofGrazetheroof:
            if (theOffset == -1) {
                theOffset = 184;
            }
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            music->mCurMusicFileDrums = MusicFile::MUSIC_FILE_DRUMS;
            music->mCurMusicFileHihats = MusicFile::MUSIC_FILE_HIHATS;
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            Music_PlayFromOffset(music, music->mCurMusicFileDrums, theOffset, 0.0);
            Music_PlayFromOffset(music, music->mCurMusicFileHihats, theOffset, 0.0);
            break;
        case MusicTune::ChooseYourSeeds:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 122;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::TitleCrazyDaveMainTheme:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 152;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::ZenGarden:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 221;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::PuzzleCerebrawl:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 177;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::MinigameLoonboon:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 166;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::Conveyer:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 212;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::FinalBossBrainiacManiac:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_MAIN_MUSIC;
            if (theOffset == -1) {
                theOffset = 158;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        case MusicTune::ZombiesOnYourLawn:
            music->mCurMusicFileMain = MusicFile::MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN;
            if (theOffset == -1) {
                theOffset = 0;
            }
            Music_PlayFromOffset(music, music->mCurMusicFileMain, theOffset, 1.0);
            break;
        default:
            break;
    }
}
void  (*old_Music_UpdateMusicBurst)(Music *music);

void Music_UpdateMusicBurst(Music *music) {
    // 加90ms静音，用于去除莫名其妙的开头鼓点声
    if (muteMusic) {
        theCounter--;
        if (theCounter == 0) {
            muteMusic = false;
            PlayerInfo* playerInfo = music->mApp->mPlayerInfo;
            float theVolume = playerInfo == NULL ? 1.0f : playerInfo->mMusicVolume / 0.8f;
            Sexy_AudiereMusicInterface_SetVolume(music->mMusicInterface, theVolume);
        }
    }
//    LOGD("UpdateMusicBurst:%d %d",music->mPlayerIndex[0],music->mPlayerIndex[1]);
    Music_UpdateMusicBurst2(music);
}


#define HIWORD(a) ((a) >> 16)
#define LOWORD(a) ((a) & 0xFFFF)

void Music_UpdateMusicBurst1(Music *music) {
    MusicTune::MusicTune mCurMusicTune; // eax
    unsigned int MusicOrder; // ebp
    int mBurstStateCounter; // eax
    int mDrumsStateCounter; // eax
    double v6; // st7
    MusicBurstState::MusicBurstState mMusicBurstState; // eax
    double v8; // st6
    int v9; // eax
    bool v10; // zf
    MusicDrumsState::MusicDrumsState mMusicDrumsState; // eax
    int v12; // ebx
    int v13; // ecx
    int mQueuedDrumTrackPackedOrder_low; // edx
    MusicDrumsState::MusicDrumsState v15; // eax
    double v16; // st7
    unsigned int BassMusicHandle; // eax
    float thePositionEnd; // [esp+8h] [ebp-2Ch]
    float v19; // [esp+Ch] [ebp-28h]
    float aBurstScheme; // [esp+20h] [ebp-14h]
    int aFadeTrackVolume; // [esp+24h] [ebp-10h]
    float aMainTrackVolume; // [esp+28h] [ebp-Ch]
    float aPackedOrderMain; // [esp+2Ch] [ebp-8h]

    if ( music->mApp->mBoard )
    {
        mCurMusicTune = music->mCurMusicTune;
        if ( mCurMusicTune == MusicTune::DayGrasswalk
             || mCurMusicTune == MusicTune::PoolWaterygraves
             || mCurMusicTune == MusicTune::FogRigormormist
             || mCurMusicTune == MusicTune::RoofGrazetheroof )
        {
            aFadeTrackVolume = 1;
        }
        else
        {
            if ( mCurMusicTune != MusicTune::NightMoongrains )
                return;
            aFadeTrackVolume = 2;
        }
        MusicOrder = Music_GetMusicOrder(music, music->mCurMusicFileMain);
        mBurstStateCounter = music->mBurstStateCounter;
        if ( mBurstStateCounter > 0 )
            music->mBurstStateCounter = mBurstStateCounter - 1;
        mDrumsStateCounter = music->mDrumsStateCounter;
        if ( mDrumsStateCounter > 0 )
            music->mDrumsStateCounter = mDrumsStateCounter - 1;
        v6 = 0.0;
        mMusicBurstState = music->mMusicBurstState;
        aMainTrackVolume = 0.0;
        aBurstScheme = 0.0;
        v8 = 1.0;
        aPackedOrderMain = 1.0;
        if ( mMusicBurstState )
        {
            switch ( mMusicBurstState )
            {
                case MusicBurstState::MUSIC_BURST_STARTING:
                    if ( aFadeTrackVolume == 1 )
                    {
                        aMainTrackVolume = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
                        v9 = music->mBurstStateCounter;
                        if ( v9 == 100 )
                        {
                            music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON_QUEUED;
                            music->mQueuedDrumTrackPackedOrder = MusicOrder;
                        }
                        v10 = v9 == 0;
                    }
                    else
                    {
                        mMusicDrumsState = music->mMusicDrumsState;
                        if ( mMusicDrumsState == MusicDrumsState::MUSIC_DRUMS_OFF )
                        {
                            music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON_QUEUED;
                            music->mQueuedDrumTrackPackedOrder = MusicOrder;
                            music->mBurstStateCounter = 400;
                            goto LABEL_48;
                        }
                        if ( mMusicDrumsState == MusicDrumsState::MUSIC_DRUMS_ON_QUEUED )
                        {
                            music->mBurstStateCounter = 400;
                            goto LABEL_48;
                        }
                        aPackedOrderMain = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 1.0, 0.0, TodCurves::Linear);
                        v10 = music->mBurstStateCounter == 0;
                    }
                    if ( v10 )
                    {
                        music->mMusicBurstState = MusicBurstState::MUSIC_BURST_ON;
                        music->mBurstStateCounter = 800;
                    }
                    break;
                case MusicBurstState::MUSIC_BURST_ON:
                    aMainTrackVolume = 1.0;
                    if ( aFadeTrackVolume == 2 )
                        aPackedOrderMain = 0.0;
                    if ( music->mBurstStateCounter )
                    {
                        LABEL_48:
                        v12 = -1;
                        if ( aFadeTrackVolume == 1 )
                        {
                            v13 = (int)HIWORD(MusicOrder) / 128;
                            mQueuedDrumTrackPackedOrder_low = HIWORD(music->mQueuedDrumTrackPackedOrder) / 128;
                        }
                        else
                        {
                            v13 = LOWORD(MusicOrder);
                            mQueuedDrumTrackPackedOrder_low = LOWORD(music->mQueuedDrumTrackPackedOrder);
                            if ( HIWORD(MusicOrder) > 252u )
                                v13 = LOWORD(MusicOrder) + 1;
                            if ( HIWORD(music->mQueuedDrumTrackPackedOrder) > 252u )
                                ++mQueuedDrumTrackPackedOrder_low;
                        }
                        v15 = music->mMusicDrumsState;
                        switch ( v15 )
                        {
                            case MusicDrumsState::MUSIC_DRUMS_ON_QUEUED:
                                if ( v13 != mQueuedDrumTrackPackedOrder_low )
                                {
                                    aBurstScheme = v8;
                                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON;
                                    if ( aFadeTrackVolume == 2 )
                                    {
                                        v12 = (v13 % 2 != 0) + 76;
                                        goto LABEL_72;
                                    }
                                }
                                break;
                            case MusicDrumsState::MUSIC_DRUMS_ON:
                                aBurstScheme = v8;
                                break;
                            case MusicDrumsState::MUSIC_DRUMS_OFF_QUEUED:
                                aBurstScheme = v8;
                                if ( v13 != mQueuedDrumTrackPackedOrder_low )
                                {
                                    if ( aFadeTrackVolume == 1 )
                                    {
                                        music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_FADING;
                                        music->mDrumsStateCounter = 50;
                                        LABEL_71:
                                        Sexy_AudiereMusicInterface_SetSongVolume(
                                                music->mMusicInterface,
                                                music->mCurMusicFileHihats,
                                                aMainTrackVolume);
                                        Sexy_AudiereMusicInterface_SetSongVolume(
                                                music->mMusicInterface,
                                                music->mCurMusicFileDrums,
                                                aBurstScheme);
                                        return;
                                    }
                                    LABEL_72:
                                    Sexy_AudiereMusicInterface_SetSongVolume(
                                            music->mMusicInterface,
                                            music->mCurMusicFileMain,
                                            aPackedOrderMain);
                                    Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, music->mCurMusicFileDrums, aBurstScheme);
                                    if ( v12 != -1 )
                                    {
                                        Sexy_AudiereMusicInterface_PlayMusic(music->mMusicInterface, music->mCurMusicFileDrums, aPackedOrderMain, 0);
                                    }
                                    return;
                                }
                                break;
                            case MusicDrumsState::MUSIC_DRUMS_FADING:
                                v19 = v6;
                                thePositionEnd = v8;
                                if ( aFadeTrackVolume == 2 )
                                    v16 = TodAnimateCurveFloat(800, 0, music->mDrumsStateCounter, thePositionEnd, v19, TodCurves::Linear);
                                else
                                    v16 = TodAnimateCurveFloat(50, 0, music->mDrumsStateCounter, thePositionEnd, v19, TodCurves::Linear);
                                aBurstScheme = v16;
                                if ( !music->mDrumsStateCounter )
                                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_OFF;
                                break;
                        }
                        if ( aFadeTrackVolume == 1 )
                            goto LABEL_71;
                        goto LABEL_72;
                    }
                    if ( Board_CountZombiesOnScreen(music->mApp->mBoard) < 4 && music->mBurstOverride == -1
                         || music->mBurstOverride == 2 )
                    {
                        music->mMusicBurstState = MusicBurstState::MUSIC_BURST_FINISHING;
                        if ( aFadeTrackVolume == 1 )
                        {
                            music->mBurstStateCounter = 800;
                            music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_OFF_QUEUED;
                            music->mQueuedDrumTrackPackedOrder = MusicOrder;
                        }
                        else
                        {
                            music->mBurstStateCounter = 1100;
                            music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_FADING;
                            music->mDrumsStateCounter = 800;
                        }
                    }
                    break;
                case MusicBurstState::MUSIC_BURST_FINISHING:
                    if ( aFadeTrackVolume == 1 )
                        aMainTrackVolume = TodAnimateCurveFloat(800, 0, music->mBurstStateCounter, 1.0, 0.0, TodCurves::Linear);
                    else
                        aPackedOrderMain = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
                    if ( !music->mBurstStateCounter && music->mMusicDrumsState == MusicDrumsState::MUSIC_DRUMS_OFF )
                        music->mMusicBurstState = MusicBurstState::MUSIC_BURST_OFF;
                    break;
                default:
                    goto LABEL_48;
            }
        }
        else if ( (Board_CountZombiesOnScreen(music->mApp->mBoard) >= 10 || music->mBurstOverride == 1)
                  && music->mMusicBurstState == MusicBurstState::MUSIC_BURST_OFF )
        {
            music->mMusicBurstState = MusicBurstState::MUSIC_BURST_STARTING;
            music->mBurstStateCounter = 400;
        }
        v8 = 1.0;
        v6 = 0.0;
        goto LABEL_48;
    }
}


void Music_UpdateMusicBurst2(Music *music) {
    LawnApp *mApp; // ecx
    MusicTune::MusicTune mCurMusicTune; // eax
    int MusicOrder; // ebx
    int mBurstStateCounter; // eax
    int mDrumsStateCounter; // eax
    double v7; // st7
    MusicBurstState::MusicBurstState mMusicBurstState; // eax
    double v9; // st6
    int v11; // eax
    MusicDrumsState::MusicDrumsState mMusicDrumsState; // eax
    unsigned int v14; // eax
    MusicTune::MusicTune v15; // ebx
    int v16; // edi
    int mQueuedDrumTrackPackedOrder_low; // ecx
    int v18; // eax
    float thePositionStart; // [esp+4h] [ebp-2Ch]
    float thePositionEnd; // [esp+8h] [ebp-28h]
    float aFadeTrackVolume; // [esp+1Ch] [ebp-14h]
    float aMainTrackVolume; // [esp+20h] [ebp-10h]
    float aDrumsJumpOrder; // [esp+24h] [ebp-Ch]
    unsigned int aPackedOrderMain; // [esp+28h] [ebp-8h]
    unsigned short v29; // [esp+2Ch] [ebp-4h]

    mApp = music->mApp;
    if (mApp->mBoard == NULL || mApp->mGameMode == GameMode::Intro) {
        return;
    }
    if (music->mCurMusicTune > MusicTune::RoofGrazetheroof) {
        return;
    }
    mCurMusicTune = music->mCurMusicTune;
    bool isNightMoonGrainsMode = mCurMusicTune == MusicTune::NightMoongrains;
    MusicOrder = Music_GetMusicOrder(music,music->mCurMusicFileMain);
    mBurstStateCounter = music->mBurstStateCounter;
    v29 = MusicOrder;
    if ( mBurstStateCounter > 0 )
        music->mBurstStateCounter = mBurstStateCounter - 1;
    mDrumsStateCounter = music->mDrumsStateCounter;
    if ( mDrumsStateCounter > 0 )
        music->mDrumsStateCounter = mDrumsStateCounter - 1;
    v7 = 0.0;
    mMusicBurstState = music->mMusicBurstState;
    aMainTrackVolume = 0.0;
    aFadeTrackVolume = 0.0;
    v9 = 1.0;
    aDrumsJumpOrder = 1.0;
    switch ( mMusicBurstState )
    {
        case MusicBurstState::MUSIC_BURST_OFF:
            if ( Board_CountZombiesOnScreen(music->mApp->mBoard) > 10 || music->mBurstOverride == 1)
            {
                music->mMusicBurstState = MusicBurstState::MUSIC_BURST_STARTING;
                music->mBurstStateCounter = 400;
            }
            break;
        case MusicBurstState::MUSIC_BURST_STARTING:
            if ( !isNightMoonGrainsMode )
            {
                aMainTrackVolume = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
                v11 = music->mBurstStateCounter;
                if ( v11 == 300 )
                {
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON_QUEUED;
                    music->mQueuedDrumTrackPackedOrder = MusicOrder;
                }
                if ( v11 == 0 )
                {
                    music->mMusicBurstState = MusicBurstState::MUSIC_BURST_ON;
                    music->mBurstStateCounter = 800;
                }
                break;
            }
            if ( isNightMoonGrainsMode )
            {
                mMusicDrumsState = music->mMusicDrumsState;
                if ( mMusicDrumsState != MusicDrumsState::MUSIC_DRUMS_OFF)
                {
                    if ( mMusicDrumsState != MusicDrumsState::MUSIC_DRUMS_ON_QUEUED )
                    {
                        aDrumsJumpOrder = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 1.0, 0.0, TodCurves::Linear);
                        if ( !music->mBurstStateCounter )
                        {
                            music->mMusicBurstState = MusicBurstState::MUSIC_BURST_ON;
                            music->mBurstStateCounter = 800;
                        }
                        break;
                    }
                    music->mBurstStateCounter = 400;
                }
                else
                {
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON_QUEUED;
                    music->mQueuedDrumTrackPackedOrder = MusicOrder;
                    music->mBurstStateCounter = 400;
                }
            }
            break;
        case MusicBurstState::MUSIC_BURST_ON:
            aMainTrackVolume = 1.0;
            if ( isNightMoonGrainsMode)
                aDrumsJumpOrder = 0.0;
            if ( music->mBurstStateCounter )
                break;
            if ( Board_CountZombiesOnScreen(music->mApp->mBoard) < 4 && music->mBurstOverride == -1
                 || music->mBurstOverride == 2 )
            {
                if ( !isNightMoonGrainsMode )
                {
                    music->mMusicBurstState = MusicBurstState::MUSIC_BURST_FINISHING;
                    music->mBurstStateCounter = 800;
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_OFF_QUEUED;
                    music->mQueuedDrumTrackPackedOrder = MusicOrder;
                }
                else if ( isNightMoonGrainsMode)
                {
                    music->mMusicBurstState = MusicBurstState::MUSIC_BURST_FINISHING;
                    music->mBurstStateCounter = 1100;
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_FADING;
                    music->mDrumsStateCounter = 800;
                }
            }
            break;
        case MusicBurstState::MUSIC_BURST_FINISHING:
            if ( !isNightMoonGrainsMode )
                aMainTrackVolume = TodAnimateCurveFloat(800, 0, music->mBurstStateCounter, 1.0, 0.0, TodCurves::Linear);
            else
                aDrumsJumpOrder = TodAnimateCurveFloat(400, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
            if ( !music->mBurstStateCounter && music->mMusicDrumsState == MusicDrumsState::MUSIC_DRUMS_OFF )
                music->mMusicBurstState = MusicBurstState::MUSIC_BURST_OFF;
            break;
    }
    v14 = MusicOrder;
    v15 = music->mCurMusicTune;
    v16 = 0;
    mQueuedDrumTrackPackedOrder_low = 0;
    v18 = HIWORD(v14);
    aPackedOrderMain = -1;
    if ( !isNightMoonGrainsMode )
    {
        v16 = v18 / 128;
        mQueuedDrumTrackPackedOrder_low = HIWORD(music->mQueuedDrumTrackPackedOrder) / 128;
    }
    else if ( isNightMoonGrainsMode )
    {
        v16 = v29;
        mQueuedDrumTrackPackedOrder_low = LOWORD(music->mQueuedDrumTrackPackedOrder);
        if ( v18 > 252 )
            v16 = v29 + 1;
        if ( HIWORD(music->mQueuedDrumTrackPackedOrder) > 252u )
            ++mQueuedDrumTrackPackedOrder_low;
    }

    switch ( music->mMusicDrumsState )
    {
        case MusicDrumsState::MUSIC_DRUMS_ON_QUEUED:
            if (isNightMoonGrainsMode) {
                if ( v16 != mQueuedDrumTrackPackedOrder_low )
                {
                    aFadeTrackVolume = v9;
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON;
                    aPackedOrderMain = (v16 % 2 != 0) + 74;
                }
            } else {
                aFadeTrackVolume = TodAnimateCurveFloat(300, 0, music->mBurstStateCounter, 0.0, 1.0, TodCurves::Linear);
                if (music->mBurstStateCounter == 1){
                    music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_ON;
                }
            }

            break;
        case MusicDrumsState::MUSIC_DRUMS_ON:
            aFadeTrackVolume = v9;
            break;
        case MusicDrumsState::MUSIC_DRUMS_OFF_QUEUED:
            aFadeTrackVolume = v9;
            if ( !isNightMoonGrainsMode )
            {
                music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_FADING;
                music->mDrumsStateCounter = 50;
            }
            break;
        case MusicDrumsState::MUSIC_DRUMS_FADING:
            thePositionEnd = v7;
            thePositionStart = v9;
            aFadeTrackVolume = TodAnimateCurveFloat(isNightMoonGrainsMode ? 800 : 50, 0, music->mDrumsStateCounter, thePositionStart, thePositionEnd, TodCurves::Linear);
            if ( music->mDrumsStateCounter == 0 )
                music->mMusicDrumsState = MusicDrumsState::MUSIC_DRUMS_OFF;
            break;
    }
    if ( !isNightMoonGrainsMode )
    {
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_HIHATS, aMainTrackVolume);
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_DRUMS, aFadeTrackVolume);
    }
    else if ( isNightMoonGrainsMode )
    {
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_MAIN_MUSIC, aDrumsJumpOrder);
        Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, MusicFile::MUSIC_FILE_DRUMS_NIGHTMOONGRAINS, aFadeTrackVolume);
        if ( aPackedOrderMain != -1 )
        {
            Sexy_AudiereMusicInterface_PlayMusic(music->mMusicInterface, music->mCurMusicFileDrums, aPackedOrderMain, 0);
        }
    }
}

void Music_StartBurst(Music *music) {
    if (music->mMusicBurstState == MusicBurstState::MUSIC_BURST_OFF) {
        music->mMusicBurstState = MusicBurstState::MUSIC_BURST_STARTING;
        music->mBurstStateCounter = 400;
    }
}

void Music_MusicUpdate(Music *music) {
    if (music->mFadeOutCounter <= 0) {
        if (music->mVolume2 != music->mVolume1) {
            music->mVolume2 = music->mVolume1;
            Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, music->mCurMusicFileMain,music->mVolume1);
        }
    } else {
        music->mFadeOutCounter--;
        if (music->mFadeOutCounter > 0) {
            float theVolume = TodAnimateCurveFloat(music->mFadeOutDuration, 0, music->mFadeOutCounter, 1.0, 0.0, TodCurves::Linear);
            Sexy_AudiereMusicInterface_SetSongVolume(music->mMusicInterface, music->mCurMusicFileMain, theVolume * music->mVolume1);
        } else {
            Music_StopAllMusic(music);
        }
    }
    Music_UpdateMusicBurst(music);
    Board *board = music->mApp->mBoard;
    if ((board == NULL || !board->mPaused) && music->mCurMusicFileMain != MusicFile::MUSIC_FILE_NONE) {
        Music_MusicResync(music);
    }
}

void Music_ResyncChannel(Music *music,MusicFile::MusicFile theFile1, MusicFile::MusicFile theFile2){

}

void (*old_Music2_Music2)(Music2 *music);

void Music2_Music2(Music2 *music) {
    //选择使用哪一版本的音乐。xbox版是xm格式，有鼓点；TV版则是ogg格式，无鼓点。
    if (useXboxMusic){
       return Music_Music(music);
    }
    return old_Music2_Music2(music);
}

void Music_MusicResync(Music *music) {
    if (music->mCurMusicFileMain != MusicFile::MUSIC_FILE_NONE) {
        if (music->mCurMusicFileDrums != MusicFile::MUSIC_FILE_NONE)
            Music_ResyncChannel(music,music->mCurMusicFileMain,music->mCurMusicFileDrums);
        if (music->mCurMusicFileHihats != MusicFile::MUSIC_FILE_NONE)
            Music_ResyncChannel(music,music->mCurMusicFileMain,music->mCurMusicFileHihats);
    }
}

void (*old_Music2_StopAllMusic)(Music2 *music);

void Music2_StopAllMusic(Music2 *music) {
    old_Music2_StopAllMusic(music);
}

void (*old_Music2_StartGameMusic)(Music2 *music, bool start);

void Music2_StartGameMusic(Music2 *music, bool start) {
    old_Music2_StartGameMusic(music, start);
}

void (*old_Music2_GameMusicPause)(Music2 *music, bool pause);

void Music2_GameMusicPause(Music2 *music, bool pause) {
    old_Music2_GameMusicPause(music, pause);
}

void (*old_Music2_FadeOut)(Music2 *music, int aFadeOutDuration);

void Music2_FadeOut(Music2 *music, int aFadeOutDuration) {
    old_Music2_FadeOut(music, aFadeOutDuration);
}

#endif //PVZ_TV_1_1_5_MUSIC_CPP
