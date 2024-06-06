//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_CHALLENGESCREEN_H
#define PVZ_TV_1_1_5_CHALLENGESCREEN_H

#include "../Enums.h"

void (*ChallengeScreen_SetScrollTarget)(ChallengeScreen *instance, int a);

void (*ChallengeScreen_KeyDown)(ChallengeScreen*,int);

//void (*ChallengeScreen_UpdateButtons)(int *);

static ChallengeDefinition& GetChallengeDefinition(int);

#endif //PVZ_TV_1_1_5_CHALLENGESCREEN_H
