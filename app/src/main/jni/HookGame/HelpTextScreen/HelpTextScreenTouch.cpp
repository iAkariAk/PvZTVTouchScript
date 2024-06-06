//
// Created by Administrator on 2024/3/3.
//

#ifndef PVZ_TV_1_1_5_HELPOPTIONSDIALOGTOUCH_H
#define PVZ_TV_1_1_5_HELPOPTIONSDIALOGTOUCH_H


#include "HelpTextScreen.h"
#include "HookGame/Enums.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Graphics/Graphics.h"
#include "HookGame/Misc/Misc.h"
#include "HookGame/Board/Board.h"

inline int nextPageButtonX = 836;
inline int nextPageButtonY = 318;

inline int prevPageButtonX = 2540;
inline int prevPageButtonY = 318;

Sexy::GameButton* mHelpTextScreenCloseButton;

void (*old_HelpTextScreen_Update)(Sexy::Widget *helpTextScreen);

void HelpTextScreen_Update(Sexy::Widget *helpTextScreen) {
    if (mHelpTextScreenCloseButton == NULL) {
        int holder[1];
        TodStringTranslate(holder, "[CLOSE]");
        mHelpTextScreenCloseButton = MakeButton(1000, (Sexy::ButtonListener *) helpTextScreen + 64, helpTextScreen,holder);
        Sexy_String_Delete(holder);
        (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))helpTextScreen->vTable + 6))(helpTextScreen, mHelpTextScreenCloseButton); // AddWidget()
    }
    GameButton_Resize(mHelpTextScreenCloseButton, 650 - helpTextScreen->mX, 540 - helpTextScreen->mY, 170, 50);
    old_HelpTextScreen_Update(helpTextScreen);
}

void (*old_HelpTextScreen_Draw)(Sexy::Widget *helpTextScreen, Sexy::Graphics *graphics);

void HelpTextScreen_Draw(Sexy::Widget *helpTextScreen, Sexy::Graphics *graphics) {
    old_HelpTextScreen_Draw(helpTextScreen, graphics);
    Sexy_Graphics_DrawImage(graphics,  *Sexy_IMAGE_ZEN_NEXTGARDEN_Addr, nextPageButtonX, nextPageButtonY);
    Sexy_Graphics_DrawImageMirror(graphics,  *Sexy_IMAGE_ZEN_NEXTGARDEN_Addr, prevPageButtonX, prevPageButtonY, true);
}



void (*old_HelpTextScreen_HelpTextScreen)(Sexy::Widget *helpTextScreen, int *lawnApp, int pageIndex);

void HelpTextScreen_HelpTextScreen(Sexy::Widget *helpTextScreen, int *lawnApp, int pageIndex) {
    old_HelpTextScreen_HelpTextScreen(helpTextScreen, lawnApp, pageIndex);
    //这个HelpTextScreen是全屏的，但触控事件并不会分发到此处，而是发给子控件。只有内容外侧的点击事件才能收到。

    Sexy_Widget_Resize(helpTextScreen,helpTextScreen->mX,helpTextScreen->mY,3000,helpTextScreen->mHeight);
}

void (*old_HelpTextScreen_AddedToManager)(Sexy::Widget *helpTextScreen, int *manager);

void HelpTextScreen_AddedToManager(Sexy::Widget *helpTextScreen, int *manager) {
    // 创建按钮

    old_HelpTextScreen_AddedToManager(helpTextScreen, manager);
}
void (*old_HelpTextScreen_MouseDown)(Sexy::Widget *helpTextScreen, int x, int y, int theClickCount);

void HelpTextScreen_MouseDown(Sexy::Widget *helpTextScreen, int x, int y, int theClickCount) {
//    LOGD("D%d %d", x, y);
//    prevPageButtonX = x;
//    prevPageButtonY = y;

    int imageWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_ZEN_NEXTGARDEN_Addr);
    int imageHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_ZEN_NEXTGARDEN_Addr);

    TRect nextPageRect = {nextPageButtonX, nextPageButtonY,imageWidth,imageHeight};
    if (TRect_Contains(&nextPageRect, x, y)) {
        HelpTextScreen_KeyDown(helpTextScreen, 39);
        return;
    }

    TRect prevPageRect = {prevPageButtonX, prevPageButtonY,imageWidth,imageHeight};
    if (TRect_Contains(&prevPageRect, x, y)) {
        HelpTextScreen_KeyDown(helpTextScreen, 37);
        return;
    }
}

void (*old_HelpTextScreen_RemovedFromManager)(Sexy::Widget *helpTextScreen, int *widgetManager);

void HelpTextScreen_RemovedFromManager(Sexy::Widget *helpTextScreen, int *widgetManager) {
    //修复MailScreen的可触控区域不为全屏
    if (mHelpTextScreenCloseButton != NULL) {
        (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))helpTextScreen->vTable + 7))(helpTextScreen, mHelpTextScreenCloseButton); // RemoveWidget()
    }
    old_HelpTextScreen_RemovedFromManager(helpTextScreen, widgetManager);
}

void (*old_HelpTextScreen_Delete2)(Sexy::Widget *helpTextScreen);

void HelpTextScreen_Delete2(Sexy::Widget *helpTextScreen) {
    old_HelpTextScreen_Delete2(helpTextScreen);
    if (mHelpTextScreenCloseButton != NULL) {
        GameButton_Delete(mHelpTextScreenCloseButton);
        mHelpTextScreenCloseButton = NULL;
    }
}
//void (*old_HelpTextScreen_MouseDrag)(int *helpTextScreen, int x, int y);
//
//void HelpTextScreen_MouseDrag(int *helpTextScreen, int x, int y) {
////    prevPageButtonX = x;
////    prevPageButtonY = y;
////    LOGD("DR%d %d", x, y);
//}
//
//void (*old_HelpTextScreen_MouseUp)(int *helpTextScreen, int a2, int a3, int a4);
//
//void HelpTextScreen_MouseUp(int *helpTextScreen, int x, int y, int theClickCount) {
//}

void (*old_HelpTextScreen_ButtonDepress)(Sexy::Widget *helpTextScreen, int );

void HelpTextScreen_ButtonDepress(Sexy::Widget *helpTextScreen, int id) {
    if (id == 1000) {
        LawnApp_KillHelpTextScreen((LawnApp*)*gLawnApp_Addr);
    } else
        return old_HelpTextScreen_ButtonDepress(helpTextScreen, id);

}

#endif //PVZ_TV_1_1_5_HELPOPTIONSDIALOGTOUCH_H
