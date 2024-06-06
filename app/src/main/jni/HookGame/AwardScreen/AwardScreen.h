//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_AWARDSCREEN_H
#define PVZ_TV_1_1_5_AWARDSCREEN_H

void  (*AwardScreen_StartButtonPressed)(int *);
void (*old_AwardScreen_MouseDown)(int *awardScreen, int x, int y, int theClickCount);
void AwardScreen_MouseDown(int *awardScreen, int x, int y, int theClickCount);
void (*old_AwardScreen_MouseUp)(int *awardScreen, int x, int y, int theClickCount);
void AwardScreen_MouseUp(int *awardScreen, int x, int y, int theClickCount);







#endif //PVZ_TV_1_1_5_AWARDSCREEN_H
