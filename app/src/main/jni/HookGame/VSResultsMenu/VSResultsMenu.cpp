//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_VSRESULTSMENU_CPP
#define PVZ_TV_1_1_5_VSRESULTSMENU_CPP

#include "HookGame/LawnApp/LawnApp.cpp"


void (*old_VSResultsMenu_Update)(int *a);

void VSResultsMenu_Update(int *a) {
    //记录当前游戏状态
    return old_VSResultsMenu_Update(a);
}

void (*old_VSResultsMenu_OnExit)(int *a);

void VSResultsMenu_OnExit(int *a) {
    return old_VSResultsMenu_OnExit(a);
}

void VSResultsMenu_ButtonDepress(int *vsResultsScreen, int buttonId) {

    if (!*((_BYTE *)vsResultsScreen + 260))
    {
        vsResultsScreen[75] = buttonId;
        VSResultsMenu_OnExit(vsResultsScreen);
    }
//    if (buttonId == 1) {
//        LawnApp_DoBackToMain((int *) *gLawnApp_Addr);
//        LawnApp_KillVSResultsScreen((int *) *gLawnApp_Addr);
//    } else if (buttonId == 0) {
//        LawnApp_PreNewGame(*gLawnApp_Addr, 76, 0);
//        LawnApp_KillVSResultsScreen((int *) *gLawnApp_Addr);
//    }
}




void (*old_VSResultsMenu_DrawInfoBox)(int *a, Sexy::Graphics *a2, int a3);

void VSResultsMenu_DrawInfoBox(int *a, Sexy::Graphics *a2, int a3) {
//    Sexy::Image* tmp = *Sexy_IMAGE_NO_GAMERPIC_Addr;
//    if (Addon_Images.gamerpic == NULL && Addon_Images.zombatar_portrait != NULL) {
//        int width = tmp->mWidth;
//        int height = tmp->mHeight;
//        Addon_Images.gamerpic = (Sexy::Image*) operator new(sizeof(Sexy::Image));
//        Sexy_MemoryImage_MemoryImage(Addon_Images.gamerpic);
//        Sexy_MemoryImage_Create(Addon_Images.gamerpic,width,height);
//        Sexy::Graphics graphics;
//        Sexy_Graphics_Graphics2(&graphics,Addon_Images.gamerpic);
//        TodDrawImageScaledF(&graphics,Addon_Images.zombatar_portrait,0,0,width / Addon_Images.zombatar_portrait->mWidth,height / Addon_Images.zombatar_portrait->mHeight);
//        Sexy_Graphics_Delete2(&graphics);
//        *Sexy_IMAGE_NO_GAMERPIC_Addr = Addon_Images.gamerpic;
//    }
    old_VSResultsMenu_DrawInfoBox(a, a2, a3);
//    *Sexy_IMAGE_NO_GAMERPIC_Addr = tmp;
}
#endif //PVZ_TV_1_1_5_VSRESULTSMENU_CPP
