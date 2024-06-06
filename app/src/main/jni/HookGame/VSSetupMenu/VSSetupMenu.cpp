//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_VSSETUPMENU_CPP
#define PVZ_TV_1_1_5_VSSETUPMENU_CPP

#include "../GlobalVariable.h"
#include "VSSetupMenu.h"
#include "HookGame/LawnApp/LawnApp.cpp"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void (*old_VSSetupMenu_Update)(int *a);

void VSSetupMenu_Update(int *a) {
    if (a) {
        //记录当前游戏状态
        int VSSetupState = *((_DWORD *) a + 74);
        if (VSSetupState == 1) {
            //自动分配阵营
            VSSetupMenu_GameButtonDown(a, 18, 0, 0);
            VSSetupMenu_GameButtonDown(a, 19, 1, 0);
            VSSetupMenu_GameButtonDown(a, 6, 0, 0);
            VSSetupMenu_GameButtonDown(a, 6, 1, 0);
        }
    }
    return old_VSSetupMenu_Update(a);
}


void (*old_VSSetupMenu_KeyDown)(int *a, int a2);

void VSSetupMenu_KeyDown(int *a, int a2) {
    //修复在对战的阵营选取界面无法按返回键退出的BUG。
    if (a2 == 27) {
        int VSSetupState = *((_DWORD *) a + 74);
        switch (VSSetupState) {
            case 1:
            case 2:
                LawnApp_DoBackToMain(*((LawnApp **) a + 73));
                return;
            case 3:
                LawnApp_DoNewOptions(*((LawnApp **) a + 73), 0, 0);
                return;
        }
    }
    return old_VSSetupMenu_KeyDown(a, a2);
}

#endif //PVZ_TV_1_1_5_VSSETUPMENU_CPP
