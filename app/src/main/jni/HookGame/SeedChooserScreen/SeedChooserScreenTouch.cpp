//
// Created by Administrator on 2024/3/2.
//

#ifndef PVZ_TV_1_1_5_SEEDCHOOSERSCREENTOUCH_CPP
#define PVZ_TV_1_1_5_SEEDCHOOSERSCREENTOUCH_CPP

#include <cstddef>
#include "HookGame/Enums.h"
#include "HookGame/LawnApp/LawnApp.h"
#include "HookGame/GlobalVariable.h"
#include "HookGame/CutScene/CutScene.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Board/Board.h"
#include "SeedChooserScreen.h"

SeedType::SeedType SeedChooserScreen_GetZombieIndexBySeedType(SeedType::SeedType seedType){
    return seedType - 61 < 0 ? SeedType::None : (SeedType::SeedType)(seedType - 61);
}

SeedChooserTouchState::SeedChooserTouchState mSeedChooserTouchState = SeedChooserTouchState::None;

inline int mSeedPacketWidth = 53;
inline int mSeedPacketHeight = 70;


void (*old_SeedChooserScreen_MouseMove)(SeedChooserScreen *seedChooserScreen, int x, int y);

void SeedChooserScreen_MouseMove(SeedChooserScreen *seedChooserScreen, int x, int y) {
        SeedType::SeedType seedType = SeedChooserScreen_SeedHitTest(seedChooserScreen, x, y);
        //该函数探测不到模仿者位置
        if (seedType == SeedType::None) {
            return;
        }
        if (seedChooserScreen->mIsZombieChooser) {
            SeedType::SeedType zombieSeedType = SeedChooserScreen_GetZombieIndexBySeedType(seedType);
            SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, zombieSeedType,
                                                       &seedChooserScreen->mCursorPositionX2,
                                                       &seedChooserScreen->mCursorPositionY2);
            seedChooserScreen->mSeedType2 = zombieSeedType;
        } else if (m1PChoosingSeeds) {
            if (seedChooserScreen->mApp->mGameMode == GameMode::TwoPlayerVS && seedType > SeedType::Melonpult) return;
            SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, seedType,
                                                       &seedChooserScreen->mCursorPositionX1,
                                                       &seedChooserScreen->mCursorPositionY1);
            seedChooserScreen->mSeedType1 = seedType;
        } else  {
            SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, seedType,
                                                       &seedChooserScreen->mCursorPositionX2,
                                                       &seedChooserScreen->mCursorPositionY2);
            seedChooserScreen->mSeedType2 = seedType;
        }
}

void (*old_SeedChooserScreen_MouseDown)(SeedChooserScreen *a, int x, int y, int theClickCount);

void SeedChooserScreen_MouseDown(SeedChooserScreen *seedChooserScreen, int x, int y, int theClickCount) {
    LawnApp *lawnApp = seedChooserScreen->mApp;
    GameMode::GameMode mGameMode = lawnApp->mGameMode;

    m1PChoosingSeeds = !LawnApp_IsCoopMode(lawnApp) || seedChooserScreen->mSeedsIn1PBank < 4;

    bool isZombieChooser = seedChooserScreen->mIsZombieChooser;

    Sexy::GameButton* mViewLawnButton = seedChooserScreen->mViewLawnButton;
    Sexy::GameButton* mStoreButton = seedChooserScreen->mStoreButton;
    Sexy::GameButton* mStartButton = seedChooserScreen->mStartButton;
    Sexy::GameButton* mAlmanacButton = seedChooserScreen->mAlmanacButton;

    bool mViewLawnButtonDisabled = mViewLawnButton == NULL || !CutScene_IsSurvivalRepick(seedChooserScreen->mBoard->mCutScene);
    bool mStoreButtonDisabled = mStoreButton == NULL || mStoreButton->mDisabled;
    bool mStartButtonDisabled = mStartButton == NULL || mStartButton->mDisabled;
    bool mAlmanacButtonDisabled = mAlmanacButton == NULL || mAlmanacButton->mDisabled;

    if (!mViewLawnButtonDisabled) { // !mDisabled
        TRect mViewLawnButtonRect = {mViewLawnButton->mX,mViewLawnButton->mY,mViewLawnButton->mWidth,50};
//        LOGD("mStoreButtonRect:%d %d %d %d",mStoreButtonRect[0],mStoreButtonRect[1],mStoreButtonRect[2],mStoreButtonRect[3]);
        if (TRect_Contains(&mViewLawnButtonRect, x, y)) {
            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::ViewLawnButton;
//            SeedChooserScreen_GameButtonDown(seedChooserScreen, 8, 0);
            return;
        }
    }

    if (!mStoreButtonDisabled) { // !mDisabled
        TRect mStoreButtonRect = {mStoreButton->mX,mStoreButton->mY,mStoreButton->mWidth,50};
//        LOGD("mStoreButtonRect:%d %d %d %d",mStoreButtonRect[0],mStoreButtonRect[1],mStoreButtonRect[2],mStoreButtonRect[3]);
        if (TRect_Contains(&mStoreButtonRect, x, y)) {
            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::StoreButton;
//            SeedChooserScreen_GameButtonDown(seedChooserScreen, 8, 0);
            return;
        }
    }

    if (!mStartButtonDisabled) { // !mDisabled
        TRect mStartButtonRect = {mStartButton->mX,mStartButton->mY,mStartButton->mWidth,50};
        if (TRect_Contains(&mStartButtonRect, x, y)) {
            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::StartButton;

//            SeedChooserScreen_OnStartButton(seedChooserScreen);
            return;
        }
    }

    if (!mAlmanacButtonDisabled) { // !mDisabled
        TRect mAlmanacButtonRect = {mAlmanacButton->mX,mAlmanacButton->mY,mAlmanacButton->mWidth,50};
        if (TRect_Contains(&mAlmanacButtonRect, x, y)) {
            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_TAP_Addr);
            mSeedChooserTouchState = SeedChooserTouchState::AlmanacButton;

//            SeedChooserScreen_GameButtonDown(seedChooserScreen, 9, 0);
            return;
        }
    }

    if (SeedChooserScreen_HasPacket(seedChooserScreen, SeedType::Imitater, 0) &&
        mGameMode != GameMode::TwoPlayerVS && !isZombieChooser) {
        int mImitaterPositionX = 0;
        int mImitaterPositionY = 0;
        SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, SeedType::Imitater,
                                                   &mImitaterPositionX, &mImitaterPositionY);
        TRect mImitaterPositionRect = {mImitaterPositionX, mImitaterPositionY, mSeedPacketWidth,
                                        mSeedPacketHeight};
        if (TRect_Contains(&mImitaterPositionRect, x, y)) {
            if (m1PChoosingSeeds){
                seedChooserScreen->mCursorPositionX1 = mImitaterPositionX;
                seedChooserScreen->mCursorPositionY1 = mImitaterPositionY;
                seedChooserScreen->mSeedType1 = SeedType::Imitater;
            }else{
                seedChooserScreen->mCursorPositionX2 = mImitaterPositionX;
                seedChooserScreen->mCursorPositionY2 = mImitaterPositionY;
                seedChooserScreen->mSeedType2 = SeedType::Imitater;
            }
            SeedChooserScreen_GameButtonDown(seedChooserScreen, 6, !m1PChoosingSeeds);
            return;
        }
    }
    SeedType::SeedType seedType = SeedChooserScreen_SeedHitTest(seedChooserScreen, x, y);
    //该函数探测不到模仿者位置

    if (seedType == SeedType::None) {
        return;
    }

    if (!isZombieChooser && seedChooserScreen->mChosenSeeds[seedType].mSeedState == ChosenSeedState::SEED_FLYING_TO_BANK || seedChooserScreen->mChosenSeeds[seedType].mSeedState == ChosenSeedState::SEED_FLYING_TO_CHOOSER){
        return;
    }
    if (isZombieChooser) {
        SeedType::SeedType zombieSeedType = SeedChooserScreen_GetZombieIndexBySeedType(seedType);
        SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, zombieSeedType,
                                                   &seedChooserScreen->mCursorPositionX2,
                                                   &seedChooserScreen->mCursorPositionY2);
        seedChooserScreen->mSeedType2 = zombieSeedType;
    } else if (m1PChoosingSeeds) {
        if (mGameMode == GameMode::TwoPlayerVS && seedType > SeedType::Melonpult) return;
        SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, seedType,
                                                   &seedChooserScreen->mCursorPositionX1,
                                                   &seedChooserScreen->mCursorPositionY1);
        seedChooserScreen->mSeedType1 = seedType;
    } else  {
        SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, seedType,
                                                   &seedChooserScreen->mCursorPositionX2,
                                                   &seedChooserScreen->mCursorPositionY2);
        seedChooserScreen->mSeedType2 = seedType;
    }
    mSeedChooserTouchState = SeedChooserTouchState::SeedChooser;
}

void (*old_SeedChooserScreen_MouseDrag)(SeedChooserScreen *seedChooserScreen, int x, int y);

void SeedChooserScreen_MouseDrag(SeedChooserScreen *seedChooserScreen, int x, int y) {

    if (mSeedChooserTouchState == SeedChooserTouchState::SeedChooser) {
        SeedType::SeedType seedType = SeedChooserScreen_SeedHitTest(seedChooserScreen, x, y);
        //该函数探测不到模仿者位置
        if (seedType == SeedType::None) {
            return;
        }
        if (seedChooserScreen->mIsZombieChooser) {
            SeedType::SeedType zombieSeedType = SeedChooserScreen_GetZombieIndexBySeedType(seedType);
            SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, zombieSeedType,
                                                       &seedChooserScreen->mCursorPositionX2,
                                                       &seedChooserScreen->mCursorPositionY2);
            seedChooserScreen->mSeedType2 = zombieSeedType;
        } else if (m1PChoosingSeeds) {
            if (seedChooserScreen->mApp->mGameMode == GameMode::TwoPlayerVS && seedType > SeedType::Melonpult) return;
            SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, seedType,
                                                       &seedChooserScreen->mCursorPositionX1,
                                                       &seedChooserScreen->mCursorPositionY1);
            seedChooserScreen->mSeedType1 = seedType;
        } else  {
            SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, seedType,
                                                       &seedChooserScreen->mCursorPositionX2,
                                                       &seedChooserScreen->mCursorPositionY2);
            seedChooserScreen->mSeedType2 = seedType;
        }
    }

}

void (*old_SeedChooserScreen_MouseUp)(SeedChooserScreen *seedChooserScreen, int x, int y);

void SeedChooserScreen_MouseUp(SeedChooserScreen *seedChooserScreen, int x, int y) {
    switch (mSeedChooserTouchState) {
        case SeedChooserTouchState::ViewLawnButton:
            SeedChooserScreen_ButtonDepress(seedChooserScreen, 102);
            break;
        case SeedChooserTouchState::SeedChooser:
            if (seedChooserScreen->mIsZombieChooser) {
                SeedChooserScreen_GameButtonDown(seedChooserScreen, 6, 1);
            } else if (m1PChoosingSeeds) {
                SeedChooserScreen_GameButtonDown(seedChooserScreen, 6, 0);
            } else {
                SeedChooserScreen_GameButtonDown(seedChooserScreen, 6, 1);
            }
            break;
        case SeedChooserTouchState::StoreButton:
            SeedChooserScreen_ButtonDepress(seedChooserScreen, 105);
            break;
        case SeedChooserTouchState::StartButton:
            SeedChooserScreen_ButtonDepress(seedChooserScreen, 100);
            break;
        case SeedChooserTouchState::AlmanacButton:
            SeedChooserScreen_ButtonDepress(seedChooserScreen, 103);
            break;
    }
    mSeedChooserTouchState = SeedChooserTouchState::None;
}

#endif //PVZ_TV_1_1_5_SEEDCHOOSERSCREENTOUCH_CPP
