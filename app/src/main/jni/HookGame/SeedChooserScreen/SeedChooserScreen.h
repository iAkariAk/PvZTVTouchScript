//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_SEEDCHOOSERSCREEN_H
#define PVZ_TV_1_1_5_SEEDCHOOSERSCREEN_H
#include "../Enums.h"
void SeedChooserScreen_ClickedSeedInBank(SeedChooserScreen *a1, ChosenSeed *a2, unsigned int a3);

void SeedChooserScreen_GameButtonDown(SeedChooserScreen *seedChooserScreen, int buttonCode, unsigned int playerIndex);

void (*SeedChooserScreen_CloseSeedChooser)(SeedChooserScreen *a);

int (*SeedChooserScreen_FindSeedInBank)(SeedChooserScreen *a1, int a2, int a3);

bool (*SeedChooserScreen_HasPacket)(SeedChooserScreen *a, int a2, bool a3);

bool (*SeedChooserScreen_Has7Rows)(SeedChooserScreen *instance);

bool (*SeedChooserScreen_CancelLawnView)(SeedChooserScreen *seedChooserScreen);

void (*SeedChooserScreen_GetNextSeedInDir)(SeedChooserScreen* seedChooserScreen,int a2,int a3);

void (*SeedChooserScreen_GetSeedPositionInChooser)(SeedChooserScreen*,SeedType::SeedType,int*,int*);

void SeedChooserScreen_GetSeedPositionInBank(SeedChooserScreen*,int,int*,int*,int);

void (*SeedChooserScreen_UpdateImitaterButton)(SeedChooserScreen*);

SeedType::SeedType (*SeedChooserScreen_SeedHitTest)(SeedChooserScreen*,int,int);

void SeedChooserScreen_ButtonDepress(SeedChooserScreen*,int);

void (*SeedChooserScreen_LandFlyingSeed)(SeedChooserScreen*,int*);

void SeedChooserScreen_LandAllFlyingSeeds(SeedChooserScreen *a);

void SeedChooserScreen_ClickedSeedInChooser(SeedChooserScreen *a1, ChosenSeed *chosenSeed, int playerIndex);

void SeedChooserScreen_EnableStartButton(SeedChooserScreen *seedChooserScreen, int isEnabled);

bool SeedChooserScreen_SeedNotAllowedToPick(SeedChooserScreen *seedChooserScreen, SeedType::SeedType theSeedType);

void SeedChooserScreen_OnStartButton(SeedChooserScreen *seedChooserScreen);

void SeedChooserScreen_ShowToolTip(SeedChooserScreen *seedChooserScreen, unsigned int playerIndex);
#endif //PVZ_TV_1_1_5_SEEDCHOOSERSCREEN_H
