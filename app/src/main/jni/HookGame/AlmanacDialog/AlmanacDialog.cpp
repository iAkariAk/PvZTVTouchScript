//
// Created by Administrator on 2024/3/8.
//

#ifndef PVZ_TV_1_1_5_ALMANACDIALOG_CPP
#define PVZ_TV_1_1_5_ALMANACDIALOG_CPP


#include <cstddef>
#include "AlmanacDialog.h"
#include "HookGame/Enums.h"
#include "HookGame/Misc/Misc.h"
#include "HookGame/HookAddr.h"
#include "HookGame/LawnApp/LawnApp.h"
#include "HookGame/Board/Board.h"

inline int theBackId = 110;
inline int theCloseId = 111;

inline int mAlmanacBackButtonX = -170;
inline int mAlmanacBackButtonY = 520;
inline int mAlmanacCloseButtonX = 800;
inline int mAlmanacCloseButtonY = 520;
// ButtonX和ButtonY是按钮的左上角坐标。

inline int mAlmanacButtonWidth = 170;
inline int mAlmanacButtonHeight = 50;
// 按钮长度和宽度为150和50，两个按钮都读取此长宽。

Sexy::GameButton* mAlmanacBackButton;
Sexy::GameButton* mAlmanacCloseButton;

void AlmanacDialog_SetPage(AlmanacDialog *almanacDialog, int targetPage) {
    //修复点击气球僵尸进植物图鉴、点击介绍文字进植物图鉴
    if (targetPage != 0) {
        //在前往其他图鉴页面时，显示返回按钮
        if (mAlmanacBackButton != NULL) {
            GameButton_Resize(mAlmanacBackButton, mAlmanacBackButtonX, mAlmanacBackButtonY, mAlmanacButtonWidth, mAlmanacButtonHeight);
            mAlmanacBackButton->mBtnNoDraw = false;
            mAlmanacBackButton->mDisabled = false;
        }
        //在前往其他图鉴页面时，将按钮缩小为0x0
        GameButton_Resize(almanacDialog->mViewPlantButton, 0, 0, 0, 0);
        GameButton_Resize(almanacDialog->mViewZombieButton, 0, 0, 0, 0);
    } else {
        //回到图鉴首页时，将返回按钮禁用
        if (mAlmanacBackButton != NULL) {
            GameButton_Resize(mAlmanacBackButton, 0, 0, 0, 0);
            mAlmanacBackButton->mBtnNoDraw = true;
            mAlmanacBackButton->mDisabled = true;
        }
        //回到图鉴首页时，将按钮恢复为正常大小
        GameButton_Resize(almanacDialog->mViewPlantButton, 130, 345, 156, 42);
        GameButton_Resize(almanacDialog->mViewZombieButton, 487, 345, 210, 48);
    }
    return old_AlmanacDialog_SetPage(almanacDialog, targetPage);
}

bool isTouchDownInTextRect = false;
TRect mTextRect = {482,360,258,173};
int mAlmanacDialogTouchDownY = 0;

void AlmanacDialog_MouseDown(AlmanacDialog *almanacDialog, int x, int y, int a4) {
    //修复点击气球僵尸进植物图鉴、点击介绍文字进植物图鉴
    if (almanacDialog->mOpenPage == 0) {
        //如果当前的Page是Index Page
        if (GameButton_IsMouseOver(almanacDialog->mViewPlantButton))
            LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        if (GameButton_IsMouseOver(almanacDialog->mViewZombieButton))
            LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
        return;
    } else if (TRect_Contains(&mTextRect, x, y)) {
        isTouchDownInTextRect = true;
        mAlmanacDialogTouchDownY = y;
    }

    SeedType::SeedType seedType = AlmanacDialog_SeedHitTest(almanacDialog, x, y);
    if (seedType != SeedType::None && seedType != almanacDialog->mSelectedSeed) {
        almanacDialog->mSelectedSeed = seedType;
        AlmanacDialog_SetupPlant(almanacDialog);
        LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_TAP_Addr);
    }
    ZombieType::ZombieType zombieType = AlmanacDialog_ZombieHitTest(almanacDialog, x, y);
    if (zombieType != -1 && zombieType != almanacDialog->mSelectedZombie) {
        almanacDialog->mSelectedZombie = zombieType;
        AlmanacDialog_SetupZombie(almanacDialog);
        LawnApp_PlaySample(almanacDialog->mApp, *Sexy_SOUND_TAP_Addr);
    }

}


void AlmanacDialog_MouseDrag(AlmanacDialog *almanacDialog, int x, int y) {
    //滚动图鉴文字

    if (isTouchDownInTextRect && mAlmanacDialogTouchDownY != y) {
        (*(void (__fastcall **)(Sexy::Widget *, _DWORD, double))(*(_DWORD *)almanacDialog->mScrollTextView + 500))(
                almanacDialog->mScrollTextView,
                *(_DWORD *)(*(_DWORD *)almanacDialog->mScrollTextView + 500),
                *((double *)almanacDialog->mScrollTextView + 35) + 0.6 * (mAlmanacDialogTouchDownY - y));
        mAlmanacDialogTouchDownY = y;
    }
}

void AlmanacDialog_MouseUp(AlmanacDialog *almanacDialog, int x, int y, int a4) {
    //空函数替换，修复点击图鉴Index界面中任何位置都会跳转植物图鉴的问题
    isTouchDownInTextRect = false;
}




void AlmanacDialog_AddedToManager(AlmanacDialog *almanacDialog, int *manager) {
    //记录当前游戏状态
    old_AlmanacDialog_AddedToManager(almanacDialog, manager);
}


void AlmanacDialog_RemovedFromManager(AlmanacDialog *almanacDialog, int *manager) {
    //记录当前游戏状态
    old_AlmanacDialog_RemovedFromManager(almanacDialog, manager);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))almanacDialog->vTable + 7))(almanacDialog, mAlmanacBackButton); // RemoveWidget()
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))almanacDialog->vTable + 7))(almanacDialog, mAlmanacCloseButton); // RemoveWidget()
}

void (*old_AlmanacDialog_Delete2)(AlmanacDialog *almanacDialog);

void AlmanacDialog_Delete2(AlmanacDialog *almanacDialog) {
    old_AlmanacDialog_Delete2(almanacDialog);
    GameButton_Delete(mAlmanacBackButton);
    GameButton_Delete(mAlmanacCloseButton);
    mAlmanacBackButton = NULL;
    mAlmanacCloseButton = NULL;
}

void AlmanacDialog_AlmanacDialog(AlmanacDialog *almanacDialog, LawnApp *lawnApp) {
    old_AlmanacDialog_AlmanacDialog(almanacDialog, lawnApp);
    int holder[1];
    TodStringTranslate(holder, "[ALMANAC_INDEX]");
    mAlmanacBackButton = MakeButton(theBackId, &almanacDialog->mButtonListener, almanacDialog, holder);
    GameButton_Resize(mAlmanacBackButton, 0, 0, 0, 0);
    mAlmanacBackButton->mBtnNoDraw = true;
    mAlmanacBackButton->mDisabled = true;
    Sexy_String_Delete(holder);
    int holder1[1];
    TodStringTranslate(holder1, "[CLOSE]");
    mAlmanacCloseButton = MakeButton(theCloseId, &almanacDialog->mButtonListener, almanacDialog, holder1);
    GameButton_Resize(mAlmanacCloseButton, mAlmanacCloseButtonX, mAlmanacCloseButtonY, mAlmanacButtonWidth, mAlmanacButtonHeight);
    Sexy_String_Delete(holder1);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))almanacDialog->vTable + 6))(almanacDialog, mAlmanacBackButton); // AddWidget()
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))almanacDialog->vTable + 6))(almanacDialog, mAlmanacCloseButton); // AddWidget()
}

void AlmanacDialog_ButtonDepress(AlmanacDialog *almanacDialog, int id) {
    if (id == 0) {
        AlmanacDialog_SetPage(almanacDialog, 1);
    } else if (id == 1) {
        AlmanacDialog_SetPage(almanacDialog, 2);
    } else if (id == theBackId) {
        AlmanacDialog_KeyDown(almanacDialog, 27);
    } else if (id == theCloseId) {
        LawnApp_KillAlmanacDialog(almanacDialog->mApp);
    }
}


#endif //PVZ_TV_1_1_5_ALMANACDIALOG_CPP
