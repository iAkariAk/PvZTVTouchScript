//
// Created by Administrator on 2024/4/2.
//

#ifndef PVZ_TV_1_1_5_SEEDBANK_H
#define PVZ_TV_1_1_5_SEEDBANK_H
#include "../Enums.h"

int (*SeedBank_GetNumSeedsOnConveyorBelt)(SeedBank *);

bool SeedBank_ContainsPoint(SeedBank *, int x, int y);

bool SeedBank_BeginDraw(SeedBank* seedBank,Sexy::Graphics* graphics);

void SeedBank_EndDraw(SeedBank*seedBank,Sexy::Graphics* graphics);
#endif //PVZ_TV_1_1_5_SEEDBANK_H
