//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_CHALLENGESCREEN_CPP
#define PVZ_TV_1_1_5_CHALLENGESCREEN_CPP

#include "ChallengeScreen.h"
#include "../Misc/Misc.h"
Sexy::GameButton *mChallengeScreenCloseButton;

void (*old_ChallengeScreen_ChallengeScreen)(ChallengeScreen *challengeScreen, LawnApp *lawnApp, ChallengePage::ChallengePage page);

void ChallengeScreen_ChallengeScreen(ChallengeScreen *challengeScreen, LawnApp *lawnApp, ChallengePage::ChallengePage page) {
    // 去除按钮对触控的遮挡
    old_ChallengeScreen_ChallengeScreen(challengeScreen, lawnApp, page);
    for (int i = 0; i < 94; ++i) {
        // 把按钮全部缩小至长宽为0
        Sexy::ButtonWidget *button = challengeScreen->mButtons[i];
        Sexy_Widget_Resize(button, button->mX, button->mY, 0, 0);
    }
}

void (*old_ChallengeScreen_Draw)(ChallengeScreen *challengeScreen,Sexy::Graphics* graphics);

void ChallengeScreen_Draw(ChallengeScreen *challengeScreen,Sexy::Graphics* graphics){
    // 修复小游戏界面显示奖杯数不正确
    old_ChallengeScreen_Draw(challengeScreen,graphics);
    int mTotalTrophiesInPage = 0;
    switch (challengeScreen->mPage) {
        case ChallengePage::CHALLENGE_PAGE_SURVIVAL:
            mTotalTrophiesInPage = 10;
            break;
        case ChallengePage::CHALLENGE_PAGE_CHALLENGE:
            for (int i = 0; i < 94; ++i) {
                if (GetChallengeDefinition(i).mPage == ChallengePage::CHALLENGE_PAGE_CHALLENGE) {
                    mTotalTrophiesInPage++;
                }
            }
            break;
        case ChallengePage::CHALLENGE_PAGE_COOP:
            mTotalTrophiesInPage = 10;
            break;
        case ChallengePage::CHALLENGE_PAGE_PUZZLE:
            mTotalTrophiesInPage = 18;
            break;
    }

    int holder[1];
    Sexy_StrFormat(holder,"%d/%d",LawnApp_GetNumTrophies(challengeScreen->mApp, challengeScreen->mPage),mTotalTrophiesInPage);
    Color theColor = {255,240,0,255};
    TodDrawString(graphics, holder, 711, 62, *Sexy_FONT_BRIANNETOD16_Addr, theColor, DrawStringJustification::Center);
    Sexy_String_Delete(holder);
}

void (*old_ChallengeScreen_AddedToManager)(ChallengeScreen *a, int a2);

void ChallengeScreen_AddedToManager(ChallengeScreen *challengeScreen, int a2) {
    //记录当前游戏状态
    int holder[1];
    TodStringTranslate(holder, "[CLOSE]");
    mChallengeScreenCloseButton = MakeButton(1000, &challengeScreen->mButtonListener, challengeScreen, holder);
    GameButton_Resize(mChallengeScreenCloseButton, 800, 520, 170, 50);
    Sexy_String_Delete(holder);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))challengeScreen->vTable + 6))(challengeScreen, mChallengeScreenCloseButton); // AddWidget()
    return old_ChallengeScreen_AddedToManager(challengeScreen, a2);
}

void (*old_ChallengeScreen_Update)(ChallengeScreen *a);

void ChallengeScreen_Update(ChallengeScreen *a) {
    //记录当前游戏状态
    return old_ChallengeScreen_Update(a);
}

void (*old_ChallengeScreen_RemovedFromManager)(ChallengeScreen *a, int a2);

void ChallengeScreen_RemovedFromManager(ChallengeScreen *challengeScreen, int a2) {
    //记录当前游戏状态
    old_ChallengeScreen_RemovedFromManager(challengeScreen, a2);
    if (mChallengeScreenCloseButton != NULL) {
        (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))challengeScreen->vTable + 7))(challengeScreen, mChallengeScreenCloseButton); // RemoveWidget()
    }
}
void (*old_ChallengeScreen_Delete2)(ChallengeScreen *challengeScreen);

void ChallengeScreen_Delete2(ChallengeScreen *challengeScreen){
    // 删除按钮
    old_ChallengeScreen_Delete2(challengeScreen);
    if (mChallengeScreenCloseButton != NULL) {
        GameButton_Delete(mChallengeScreenCloseButton);
        mChallengeScreenCloseButton = NULL;
    }
}

void ChallengeScreen_ButtonPress(ChallengeScreen *challengeScreen, int buttonId) {
    //空函数替换，去除原有的点击进入关卡的功能
}

void ChallengeScreen_ButtonDepress(ChallengeScreen *challengeScreen, int buttonId) {
    //去除原有的点击进入关卡的功能
    if (buttonId == 1000) {
        LawnApp_KillChallengeScreen(challengeScreen->mApp);
        LawnApp_DoBackToMain(challengeScreen->mApp);
    }
}

void ChallengeScreen_UpdateButtons(ChallengeScreen *challengeScreen) {
    //空函数替换，去除默认选取第一个游戏的功能
}

ChallengeDefinition gButteredPopcornDef = {GameMode::ChallengeButteredPopcorn, 37,
                                           ChallengePage::CHALLENGE_PAGE_CHALLENGE, 6, 1,
                                           "[BUTTERED_POPCORN]"};

ChallengeDefinition gPoolPartyDef = {GameMode::ChallengePoolParty, 37,
                                     ChallengePage::CHALLENGE_PAGE_CHALLENGE, 6, 2,
                                     "[POOL_PARTY]"};

ChallengeDefinition &(*old_GetChallengeDefinition)(int index);

ChallengeDefinition &GetChallengeDefinition(int index) {
    switch (index + 2) {
        case GameMode::ChallengeButteredPopcorn:
            return gButteredPopcornDef;
//        case GameMode::ChallengePoolParty:
//            return gPoolPartyDef;
        default:
            return old_GetChallengeDefinition(index);
    }
}
#endif //PVZ_TV_1_1_5_CHALLENGESCREEN_CPP
