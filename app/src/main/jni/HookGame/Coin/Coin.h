//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_COIN_H
#define PVZ_TV_1_1_5_COIN_H
#include "../Enums.h"

void (*Coin_Die)(Coin *a);

void (*Coin_Collect)(Coin *a1, int a2);

void (*Coin_MouseDown)(Coin *coin, int x, int y, int);

void (*old_Coin_GamepadCursorOver)(Coin *coin, int a2);

bool (*Coin_IsLevelAward)(Coin*);

bool (*Coin_IsPresentWithAdvice)(Coin*);

bool (*Coin_IsMoney)(Coin*);

void (*Coin_PlayGroundSound)(Coin*);

int (*Coin_GetDisappearTime)(Coin*);

void (*Coin_StartFade)(Coin*);

float (*Coin_GetSunScale)(Coin*);
#endif //PVZ_TV_1_1_5_COIN_H
