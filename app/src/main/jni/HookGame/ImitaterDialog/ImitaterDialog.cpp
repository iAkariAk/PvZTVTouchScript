//
// Created by Administrator on 2024/4/7.
//

#ifndef PVZ_TV_1_1_5_IMITATERDIALOG_CPP
#define PVZ_TV_1_1_5_IMITATERDIALOG_CPP


#include "ImitaterDialog.h"
#include "HookGame/LawnApp/LawnApp.h"
#include "HookGame/Graphics/Graphics.h"
#include "HookGame/SeedChooserScreen/SeedChooserScreen.h"
#include "HookGame/GlobalVariable.h"

void (*old_ImitaterDialog_ImitaterDialog)(LawnDialog *instance, int a2);

void ImitaterDialog_ImitaterDialog(LawnDialog *instance, int playerIndex) {
    //记录当前游戏状态
    return old_ImitaterDialog_ImitaterDialog(instance, playerIndex);
}

void (*old_ImitaterDialog_ShowToolTip)(LawnDialog *instance);

void ImitaterDialog_ShowToolTip(LawnDialog *instance) {
    // 在触控模式下不显示ToolTip
    if (!keyboardMode) return;
    return old_ImitaterDialog_ShowToolTip(instance);
}

bool (*old_ImitaterDialog_KeyDown)(LawnDialog *a, int a2);

bool ImitaterDialog_KeyDown(LawnDialog *a, int a2) {
    // 修复不选择模仿者卡片并退出时的闪退
    if (a2 == Sexy::Back || a2 == Sexy::Back2) {
        LawnApp *lawnApp = a->mApp;
        SeedChooserScreen * seedChooserScreen = lawnApp->mSeedChooserScreen;
        (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))seedChooserScreen->vTable + 7))(seedChooserScreen, a); // RemoveWidget()
        (*(void (__fastcall **)(LawnApp *, Sexy::Widget *))(*(_DWORD *)lawnApp + 188))(lawnApp, a);
        seedChooserScreen->mImitaterDialogOpened = 0;
        return true;
    }
    return old_ImitaterDialog_KeyDown(a, a2);
}

void (*old_ImitaterDialog_MouseDown)(LawnDialog *a, int x, int y, int theCount);

void ImitaterDialog_MouseDown(LawnDialog *a, int x, int y, int theCount) {
    SeedType::SeedType seedType = ImitaterDialog_SeedHitTest(a, x, y);
    if (seedType == SeedType::None) {
        return;
    }
    LawnApp *lawnApp = a->mApp;
    SeedChooserScreen *seedChooserScreen = lawnApp->mSeedChooserScreen;

    if (!SeedChooserScreen_SeedNotAllowedToPick(seedChooserScreen, seedType)) {
        ChosenSeed *chosenSeed = &(seedChooserScreen->mChosenSeeds[SeedType::Imitater]);
        chosenSeed->mImitaterType = seedType;
        chosenSeed->mSeedState = ChosenSeedState::SEED_IN_CHOOSER;
        SeedChooserScreen_GetSeedPositionInChooser(seedChooserScreen, SeedType::Imitater,&chosenSeed->mX,&chosenSeed->mY);
//        SeedChooserScreen_ClickedSeedInChooser(*(_DWORD *) (a[184] + 2244), seedChooserScreen + 835, -1);//模仿者选种子闪退，就是因为这里参数为-1而不是0或者1
//        int mPlayerIndex = a[194];
        SeedChooserScreen_ClickedSeedInChooser(seedChooserScreen,chosenSeed,m1PChoosingSeeds ? 0 : 1);
        SeedChooserScreen_UpdateImitaterButton(seedChooserScreen);
//        (*(void (__fastcall **)(int, int)) (*(_DWORD *) a[184] + 428))(a[184], a[179]);
        (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))seedChooserScreen->vTable + 7))(seedChooserScreen, a); // RemoveWidget()
        (*(void (__fastcall **)(LawnApp*, Sexy::Widget *)) (*(_DWORD *) lawnApp + 188))(lawnApp, a);
        seedChooserScreen->mImitaterDialogOpened = 0;
    }
}


#endif //PVZ_TV_1_1_5_IMITATERDIALOG_CPP
