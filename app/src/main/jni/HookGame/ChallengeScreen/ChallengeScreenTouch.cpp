//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_CHALLENGESCREENTOUCH_CPP
#define PVZ_TV_1_1_5_CHALLENGESCREENTOUCH_CPP

#include "ChallengeScreen.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Misc/Misc.h"
#include "HookGame/LawnApp/LawnApp.h"

int mChallengeScreenTouchDownX = 0;
int mChallengeScreenTouchDownY = 0;
int mChallengeItemHeight = 0;
int mChallengeScreenGameIndex = 0;
bool mChallengeItemMoved = false;
bool mTouchOutSide = false;

inline int mPageTop = 75;
inline int mPageBottom = 555;


void (*old_ChallengeScreen_MouseDown)(ChallengeScreen *challengeScreen, int x, int y, int theClickCount);

void ChallengeScreen_MouseDown(ChallengeScreen *challengeScreen, int x, int y, int theClickCount) {
    if ( y > mPageBottom || y < mPageTop){
        mTouchOutSide = true;
    }
    mChallengeScreenTouchDownX = x;
    mChallengeScreenTouchDownY = y;
    mChallengeItemHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_CHALLENGE_NAME_BACK_Addr) + 2;//2为缝隙大小

    mChallengeScreenGameIndex = challengeScreen->mScreenTopChallengeIndex;

//    int totalGamesInThisPage = challengeScreen[376];//如果这个值是33
//    int currentSelectedGameIndex = ChallengeScreen_GetCurrentSelectedGameIndex(
//            challengeScreen);//这里取值就是0~32。种子雨是32。

//    int firstGameInPageIndex = challengeScreen->mScreenTopChallengeIndex;
//    int firstGameInPageIndex2 = challengeScreen[186];
//    challengeScreen->mSelectedMode = challengeScreen[currentSelectedGameIndex + 1 + 188];//向下移动绿色光标，不可循环滚动
//    challengeScreen->mSelectedMode = challengeScreen[currentSelectedGameIndex - 1 + 188];//向上移动绿色光标，不可循环滚动

//    LOGD("dOWN:%d %d %d %d", x, y, firstGameInPageIndex, firstGameInPageIndex2);
}

void (*old_ChallengeScreen_MouseDrag)(ChallengeScreen *challengeScreen, int x, int y);

void ChallengeScreen_MouseDrag(ChallengeScreen *challengeScreen, int x, int y) {
    if (mTouchOutSide) return;
    int triggerHeight = mChallengeItemHeight / 2;//调节此处以修改小游戏列表的滚动速度。滚动太快就会有BUG，好烦。
    if (mChallengeScreenTouchDownY - y > triggerHeight) {
        int totalGamesInThisPage = challengeScreen->mTotalGameInPage;
        mChallengeScreenGameIndex += 1;
        mChallengeScreenTouchDownY -= triggerHeight;
        int gameIndexToScroll = mChallengeScreenGameIndex >= totalGamesInThisPage - 4 ? totalGamesInThisPage - 4 : mChallengeScreenGameIndex;
        ChallengeScreen_SetScrollTarget(challengeScreen,gameIndexToScroll);
//        ChallengeScreen_UpdateButtons(challengeScreen);
        mChallengeItemMoved = true;
    } else if (y - mChallengeScreenTouchDownY > triggerHeight) {
        mChallengeScreenGameIndex -= 1;
        mChallengeScreenTouchDownY += triggerHeight;
        int gameIndexToScroll = mChallengeScreenGameIndex <= 0 ? 0 : mChallengeScreenGameIndex;
        ChallengeScreen_SetScrollTarget(challengeScreen,gameIndexToScroll);
//        ChallengeScreen_UpdateButtons(challengeScreen);
        mChallengeItemMoved = true;
    }
}

void (*old_ChallengeScreen_MouseUp)(ChallengeScreen *challengeScreen, int x, int y);

void ChallengeScreen_MouseUp(ChallengeScreen *challengeScreen, int x, int y) {
    if (!mTouchOutSide && !mChallengeItemMoved) {
        int gameIndex = challengeScreen->mScreenTopChallengeIndex + (y - mPageTop) / mChallengeItemHeight;
        if (challengeScreen->mSelectedMode == challengeScreen->mUnk1[gameIndex]) {
            ChallengeScreen_KeyDown(challengeScreen, 13);
        } else {
            LawnApp_PlaySample(challengeScreen->mApp, *Sexy_SOUND_BUTTONCLICK_Addr);
            challengeScreen->mSelectedMode = challengeScreen->mUnk1[gameIndex];
        }
    }
    mTouchOutSide = false;
    mChallengeItemMoved = false;
}

#endif //PVZ_TV_1_1_5_CHALLENGESCREENTOUCH_CPP
