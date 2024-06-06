//
// Created by Administrator on 2024/4/7.
//

#ifndef PVZ_TV_1_1_5_CUTSCENE_CPP
#define PVZ_TV_1_1_5_CUTSCENE_CPP


#include "HookGame/Enums.h"

void (*old_CutScene_ShowShovel)(CutScene *cutScene);

void CutScene_ShowShovel(CutScene *cutScene) {
    LawnApp *lawnApp =  cutScene->mApp;
    if (lawnApp->mGameMode == GameMode::ChallengeButteredPopcorn) {
        // 不绘制锤子铲子黄油按钮
        Board* board = cutScene->mBoard;
        board->mShowShovel = false;
        board->mShowButter = false;
        board->mShowHammer = false;
        return;
    }
    return old_CutScene_ShowShovel(cutScene);
}

void (*old_CutScene_Update)(CutScene *instance);

void CutScene_Update(CutScene *cutScene) {
    return old_CutScene_Update(cutScene);
}


#endif //PVZ_TV_1_1_5_CUTSCENE_CPP
