//
// Created by Administrator on 2024/4/7.
//

#ifndef PVZ_TV_1_1_5_CUTSCENE_H
#define PVZ_TV_1_1_5_CUTSCENE_H

#include "../Enums.h"
bool (*CutScene_IsSurvivalRepick)(CutScene *instance);

bool (*CutScene_OnKeyDown)(CutScene *, int, int);

void (*CutScene_MouseDown)(CutScene *, int, int);

bool (*CutScene_IsBeforePreloading)(CutScene *);

bool (*CutScene_ShouldRunUpsellBoard)(CutScene *);

#endif //PVZ_TV_1_1_5_CUTSCENE_H
