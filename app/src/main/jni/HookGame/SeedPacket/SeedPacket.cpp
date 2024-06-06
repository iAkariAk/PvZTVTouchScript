//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_SEEDPACKET_CPP
#define PVZ_TV_1_1_5_SEEDPACKET_CPP

#include "../Graphics/Graphics.h"
#include "../SpecialConstraints.h"
#include "HookGame/GlobalVariable.h"
#include "SeedPacket.h"
#include "HookGame/HookAddr.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void (*old_SeedPacket_Update)(SeedPacket *seedPacket);

void SeedPacket_Update(SeedPacket *seedPacket) {

    if (seedPacket->mRefreshing && seedPacketFastCoolDown) {
        // 正在刷新的种子立即冷却完毕
        seedPacket->mActive = true;
        seedPacket->mRefreshing = false;
    }


    if (requestPause) {

        if (LawnApp_IsIZombieLevel(seedPacket->mApp)) {
            // 在IZ模式不暂停刷新种子卡片
            return old_SeedPacket_Update(seedPacket);
        }

        if (seedPacket->mApp->mGameScene == GameScenes::Playing && seedPacket->mPacketType != SeedType::None){
            seedPacket->mRefreshCounter--;
        }
        if (seedPacket->mSlotMachineCountDown > 0) {
            seedPacket->mSlotMachineCountDown++;
        }
    }
    return old_SeedPacket_Update(seedPacket);
}

void (*old_SeedPacket_UpdateSelected)(SeedPacket *seedPacket);

void SeedPacket_UpdateSelected(SeedPacket *seedPacket) {
    if (seedPacket->mApp->mGameMode == GameMode::TwoPlayerVS || LawnApp_IsCoopMode(seedPacket->mApp)) {
        //如果是双人模式关卡(对战或结盟)，则使用下面的逻辑来更新当前选中的卡片。用于修复1P和2P的卡片选择框同时出现在两个人各自的植物栏里(也就是植物栏一共出现四个选择框)的问题。
        int mSelectedSeedIndex1P = seedPacket->mBoard->mGamepadControls1->mSelectedSeedIndex;
        int mSelectedSeedIndex2P = seedPacket->mBoard->mGamepadControls2->mSelectedSeedIndex;
        bool playerIndex = SeedPacket_GetPlayerIndex(seedPacket);
        bool selectedBy1P = playerIndex == 0 && seedPacket->mIndex == mSelectedSeedIndex1P;
        bool selectedBy2P = playerIndex == 1 && seedPacket->mIndex == mSelectedSeedIndex2P;
        seedPacket->mSelectedBy1P = selectedBy1P || selectedBy2P;
        seedPacket->mSelectedBy2P = selectedBy2P;
        return;
    }
    return old_SeedPacket_UpdateSelected(seedPacket);
}

bool showCoolDown = false;

void (*old_SeedPacket_DrawOverlay)(SeedPacket *seedPacket, Sexy::Graphics *graphics);

void SeedPacket_DrawOverlay(SeedPacket *seedPacket, Sexy::Graphics *graphics) {
    //绘制卡片冷却进度倒计时
    old_SeedPacket_DrawOverlay(seedPacket, graphics);
    if (seedPacket->mRefreshing && showCoolDown) {
        //如果玩家开启了“显示冷却倒计时”，则绘制倒计时
        int holder[1];
        int coolDownRemaining = seedPacket->mRefreshTime - seedPacket->mRefreshCounter;
        Sexy_StrFormat(holder, "%1.1f", coolDownRemaining / 100.0f);
        Sexy_Graphics_SetColor(graphics, SeedPacket_GetPlayerIndex(seedPacket) ? &yellow : &blue);
        Sexy_Graphics_SetFont(graphics, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
        Sexy_Graphics_DrawString(graphics, holder, coolDownRemaining < 1000 ? 10 : 0, 39);
        Sexy_String_Delete(holder);
        Sexy_Graphics_SetFont(graphics, NULL);
    }
}

void (*old_SeedPacket_Draw)(SeedPacket *seedPacket, Sexy::Graphics *graphics);

void SeedPacket_Draw(SeedPacket *seedPacket, Sexy::Graphics *graphics) {
    //绘制卡片冷却进度倒计时
    old_SeedPacket_Draw(seedPacket, graphics);
}

void (*old_SeedPacket_MouseDown)(SeedPacket *seedPacket, int x, int y, int c, int unk);


void SeedPacket_MouseDown(SeedPacket *seedPacket, int x, int y, int c, int unk) {
//    LOGD("SeedPacket_MouseDown:%d %d %d %d", x, y, c, unk);
    old_SeedPacket_MouseDown(seedPacket, x, y, c, unk);
}

bool (*old_SeedPacket_BeginDraw)(SeedPacket*, Sexy::Graphics*);

bool SeedPacket_BeginDraw(SeedPacket* a, Sexy::Graphics* a2){
    return old_SeedPacket_BeginDraw(a,a2);
}

void (*old_SeedPacket_EndDraw)(SeedPacket*, Sexy::Graphics*);

void SeedPacket_EndDraw(SeedPacket* a, Sexy::Graphics* a2){
    old_SeedPacket_EndDraw(a,a2);
}
//void (*old_ShopSeedPacket_Update)(int *);
//
//void ShopSeedPacket_Update(int *a) {
//    if (elevenSeeds) { return; }
//    return old_ShopSeedPacket_Update(a);
//}

void (*old_SeedPacket_FlashIfReady)(SeedPacket *seedPacket);

void SeedPacket_FlashIfReady(SeedPacket *seedPacket) {
    // 去除对战模式下的闪光效果的缩放

    if (!SeedPacket_CanPickUp(seedPacket)) {
        return;
    }
    if (seedPacket->mApp->mEasyPlantingCheat) {
        return;
    }

    SeedBank *mSeedBank = seedPacket->mSeedBank;
    Board* mBoard = seedPacket->mBoard;
    int playerIndex = 0;
    if (mSeedBank != NULL) {
        playerIndex = mSeedBank->mPlayerIndex;
    }
    if (!Board_HasConveyorBeltSeedBank(mBoard, playerIndex) && mSeedBank != NULL) {
        LawnApp_AddTodParticle(seedPacket->mApp, mSeedBank->mX + seedPacket->mX, mSeedBank->mY + seedPacket->mY, 100000 + 2, ParticleEffect::SeedPacketFlash);
    }
    TutorialState::TutorialState tutorialState = seedPacket->mBoard->mTutorialState;
    if (tutorialState == TutorialState::Level1RefreshPeashooter) {
        Board_SetTutorialState(mBoard, TutorialState::Level1PickUpPeashooter);
        return;
    }
    if (tutorialState == TutorialState::Level2RefreshSunflower && seedPacket->mPacketType == SeedType::Sunflower) {
        Board_SetTutorialState(mBoard, TutorialState::Level2PickUpSunflower);
        return;
    }
    if (tutorialState == TutorialState::MoresunRefreshSunflower && seedPacket->mPacketType == SeedType::Sunflower) {
        Board_SetTutorialState(mBoard, TutorialState::MoresunPickUpSunflower);
        return;
    }

}

#endif //PVZ_TV_1_1_5_SEEDPACKET_CPP
