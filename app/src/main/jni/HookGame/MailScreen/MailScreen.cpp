//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_MAILSCREEN_CPP
#define PVZ_TV_1_1_5_MAILSCREEN_CPP

#include "MailScreen.h"
#include "HookGame/Misc/Misc.h"
#include "HookGame/Graphics/Graphics.h"

Sexy::GameButton *mMailScreenCloseButton;
Sexy::GameButton *mMailScreenReadButton;
Sexy::GameButton *mMailScreenSwitchButton;

void (*old_MailScreen_MailScreen)(MailScreen *mailScreen, LawnApp *lawnApp);

void MailScreen_MailScreen(MailScreen *mailScreen, LawnApp *lawnApp) {
    //修复MailScreen的可触控区域不为全屏。
    old_MailScreen_MailScreen(mailScreen, lawnApp);
    int holder2[1];
    TodStringTranslate(holder2, "[MARK_MESSAGE_READ]");
    mMailScreenReadButton = MakeButton(1002, &mailScreen->mButtonListener, mailScreen, holder2);
    GameButton_Resize(mMailScreenReadButton, -150, 450, 170, 80);
    Sexy_String_Delete(holder2);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mailScreen->vTable + 6))(mailScreen, mMailScreenReadButton); // AddWidget()

    int holder1[1];
    TodStringTranslate(holder1, "[GO_TO_READ_MAIL]");
    mMailScreenSwitchButton = MakeButton(1001, &mailScreen->mButtonListener, mailScreen, holder1);
    GameButton_Resize(mMailScreenSwitchButton,-150, 520, 170, 80);
    Sexy_String_Delete(holder1);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mailScreen->vTable + 6))(mailScreen, mMailScreenSwitchButton); // AddWidget()


    int holder[1];
    TodStringTranslate(holder, "[CLOSE]");
    mMailScreenCloseButton = MakeButton(1000, &mailScreen->mButtonListener, mailScreen, holder);
    GameButton_Resize(mMailScreenCloseButton, 800, 520, 170, 80);
    Sexy_String_Delete(holder);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mailScreen->vTable + 6))(mailScreen, mMailScreenCloseButton); // AddWidget()

    Sexy_Widget_Resize(mailScreen, 0, 0, 800, 600);
}

void (*old_MailScreen_AddedToManager)(MailScreen *mailScreen, int *widgetManager);

void MailScreen_AddedToManager(MailScreen *mailScreen, int *widgetManager) {
    old_MailScreen_AddedToManager(mailScreen, widgetManager);
//    Sexy_Widget_Resize(mailScreen, -240, -60, 1280, 720);
}

void (*old_MailScreen_RemovedFromManager)(MailScreen *mailScreen, int *widgetManager);

void MailScreen_RemovedFromManager(MailScreen *mailScreen, int *widgetManager) {
    //修复MailScreen的可触控区域不为全屏
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mailScreen->vTable + 7))(mailScreen, mMailScreenCloseButton); // RemoveWidget()
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mailScreen->vTable + 7))(mailScreen, mMailScreenReadButton); // RemoveWidget()
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mailScreen->vTable + 7))(mailScreen, mMailScreenSwitchButton); // RemoveWidget()
    old_MailScreen_RemovedFromManager(mailScreen, widgetManager);
}

void (*old_MailScreen_Delete2)(MailScreen *mailScreen);

void MailScreen_Delete2(MailScreen *mailScreen){
    old_MailScreen_Delete2(mailScreen);
    GameButton_Delete(mMailScreenCloseButton);
    mMailScreenCloseButton = NULL;
    GameButton_Delete(mMailScreenReadButton);
    mMailScreenReadButton = NULL;
    GameButton_Delete(mMailScreenSwitchButton);
    mMailScreenSwitchButton = NULL;
}

void (*old_MailScreen_ButtonPress)(MailScreen *mailScreen, int id);

void MailScreen_ButtonPress(MailScreen *mailScreen, int id) {
    old_MailScreen_ButtonPress(mailScreen, id);
}

void (*old_MailScreen_ButtonDepress)(MailScreen *mailScreen, int id);

void MailScreen_ButtonDepress(MailScreen *mailScreen, int id) {
    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
    MailScreen *theRealMailScreen = (MailScreen *)Sexy_SexyAppBase_GetDialog(lawnApp, Dialogs::DIALOG_MAIL);
    if (id == 1002) {
        MailScreen_KeyDown(theRealMailScreen, Sexy::Ok, 0, 0);
    } else if (id == 1001) {
        MailScreen_KeyDown(theRealMailScreen, 307, 0, 0);
        bool isAtInBox = theRealMailScreen->mPage == 0;
        mMailScreenReadButton->mDisabled = !isAtInBox;
        mMailScreenReadButton->mBtnNoDraw = !isAtInBox;
        int holder[1];
        TodStringTranslate(holder, isAtInBox ? "[GO_TO_READ_MAIL]" : "[GO_TO_INBOX]");
        GameButton_SetLabel(mMailScreenSwitchButton,holder);
        Sexy_String_Delete(holder);
    }else
    old_MailScreen_ButtonDepress(mailScreen, id);
}

#endif //PVZ_TV_1_1_5_MAILSCREEN_CPP
