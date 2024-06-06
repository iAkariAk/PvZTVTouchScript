//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_MAILSCREENTOUCH_CPP
#define PVZ_TV_1_1_5_MAILSCREENTOUCH_CPP


#include "MailScreen.h"

int mMailTouchDownX = 0;
int mMailTouchDownY = 0;

inline int mMailTrigger = 20;

void (*old_MailScreen_MouseDown)(MailScreen *mailScreen, int x, int y, int theClickCount);

void MailScreen_MouseDown(MailScreen *mailScreen, int x, int y, int theClickCount) {
    mMailTouchDownX = x;
    mMailTouchDownY = y;
}

void (*old_MailScreen_MouseDrag)(MailScreen *mailScreen, int x, int y);

void MailScreen_MouseDrag(MailScreen *mailScreen, int x, int y) {

}

void (*old_MailScreen_MouseUp)(MailScreen *mailScreen, int x, int y);

void MailScreen_MouseUp(MailScreen *mailScreen, int x, int y) {
    if (mMailTouchDownX - x > mMailTrigger) {
        MailScreen_KeyDown(mailScreen, 39, 0, 0);
    } else if (x - mMailTouchDownX > mMailTrigger) {
        MailScreen_KeyDown(mailScreen, 37, 0, 0);
    } else if (mMailTouchDownX < 400) {
        MailScreen_KeyDown(mailScreen, 37, 0, 0);
    } else {
        MailScreen_KeyDown(mailScreen, 39, 0, 0);
    }
}

#endif //PVZ_TV_1_1_5_MAILSCREENTOUCH_CPP
