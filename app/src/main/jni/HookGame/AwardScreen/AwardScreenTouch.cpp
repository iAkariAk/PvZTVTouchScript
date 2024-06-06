//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_AWARDSCREENTOUCH_CPP
#define PVZ_TV_1_1_5_AWARDSCREENTOUCH_CPP


#include "../LawnApp/LawnApp.h"
#include "../HookAddr.h"
#include "AwardScreen.h"


void AwardScreen_MouseDown(int *awardScreen, int x, int y, int theClickCount) {
    Sexy::GameButton* gameButton = *((Sexy::GameButton **)awardScreen + 65);
    TRect rect = {gameButton->mX,gameButton->mY,gameButton->mWidth,gameButton->mHeight};
    if (TRect_Contains(&rect, x, y)) {
        LawnApp_PlaySample((LawnApp *) awardScreen[67], *Sexy_SOUND_TAP_Addr);
    }
}

void AwardScreen_MouseUp(int *awardScreen, int x, int y, int theClickCount) {
    Sexy::GameButton* gameButton = *((Sexy::GameButton **)awardScreen + 65);
    TRect rect = {gameButton->mX,gameButton->mY,gameButton->mWidth,gameButton->mHeight};
    if (TRect_Contains(&rect, x, y)) {
        AwardScreen_StartButtonPressed(awardScreen);
    }

}

#endif //PVZ_TV_1_1_5_AWARDSCREENTOUCH_CPP
