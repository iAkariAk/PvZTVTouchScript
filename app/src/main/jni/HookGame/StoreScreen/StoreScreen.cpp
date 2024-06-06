//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_STORESCREEN_CPP
#define PVZ_TV_1_1_5_STORESCREEN_CPP

#include "HookGame/GlobalVariable.h"
#include "HookGame/HookAddr.h"
#include "StoreScreen.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;


void (*old_StoreScreen_AddedToManager)(int *a, int a2);

void StoreScreen_AddedToManager(int *a, int a2) {
    return old_StoreScreen_AddedToManager(a, a2);
}

void (*old_StoreScreen_RemovedFromManager)(int *a, int a2);

void StoreScreen_RemovedFromManager(int *a, int a2) {
    return old_StoreScreen_RemovedFromManager(a, a2);
}

void (*old_StoreScreen_Update)(int a);

void StoreScreen_Update(int a) {
    return old_StoreScreen_Update(a);
}

void (*old_StoreScreen_SetupPage)(int *a);

void StoreScreen_SetupPage(int *a) {
    old_StoreScreen_SetupPage(a);
//    for (int i = 0; i < 8; ++i) {
//        StoreItem::StoreItem StoreItemType = StoreScreen_GetStoreItemType(a, i);
//        if (StoreScreen_IsPottedPlant(a, StoreItemType)) {
//            Sexy::Image *theImage = *((Sexy::Image **) a + i + 217);
//            Sexy::Graphics g;
//            Sexy_Graphics_Graphics2(&g, theImage);
//            Sexy_Graphics_ClearRect(&g, 0, 0, 100, 70);
//            Sexy_Graphics_Translate(&g, -10, -50);
//            Sexy_Graphics_DrawImage(&g, Addon_Images.seed_cached_52, 0, 0);
//            Sexy_Graphics_Delete2(&g);
//        }
//    }
}

void (*old_StoreScreen_DrawItem)(int* a1, Sexy::Graphics *a2, int a3, StoreItem::StoreItem item);

void StoreScreen_DrawItem(int* a1, Sexy::Graphics *a2, int a3, StoreItem::StoreItem item){
//    if (StoreScreen_IsItemUnavailable(a1, item)) return;
//    if (StoreScreen_IsPottedPlant(a1, item)){
//        int theX = 0;
//        int theY = 0;
//        int theCount = 0;
//        Sexy::Image *theImage = NULL;
//        StoreScreen_GetStoreItemInfo(a1, 0, item, &theImage, &theX, &theY, &theCount);
//        Sexy_Graphics_DrawImage(a2,Addon_Images.seed_cached_52,theX,theY);
//    }
    old_StoreScreen_DrawItem(a1,a2,a3,item);
}

void (*old_StoreScreen_ButtonDepress)(int*,int);

void StoreScreen_ButtonDepress(int *storeScreen, int buttonId) {
//    if (!showHouse) return old_StoreScreen_ButtonDepress(storeScreen, buttonId);
    LawnApp *lawnApp = (LawnApp*)storeScreen[184];
    int newPageIndex;
    switch ( buttonId ) {
        case 100:
            storeScreen[181] = 1000;
            break;
        case 101:
            storeScreen[195] = 50;
            storeScreen[197] = 1;
            LawnApp_PlaySample(lawnApp,*Sexy_SOUND_HATCHBACK_CLOSE_Addr);
            storeScreen[188] = 0;
            LawnApp_CrazyDaveStopTalking(lawnApp);
            StoreScreen_EnableButtons(storeScreen, false);
            do {
                newPageIndex = storeScreen[192] - 1;
                if (newPageIndex < 0) {
                    newPageIndex = 5;
                    storeScreen[192] = 5;
                } else if (newPageIndex == 4) {
                    newPageIndex = 3;
                    storeScreen[192] = 3;
                } else {
                    storeScreen[192] = newPageIndex;
                }
            } while (!StoreScreen_IsPageShown(storeScreen, newPageIndex));
            break;
        case 102:
            storeScreen[195] = 50;
            storeScreen[197] = 2;
            LawnApp_PlaySample(lawnApp,*Sexy_SOUND_HATCHBACK_CLOSE_Addr);
            storeScreen[188] = 0;
            LawnApp_CrazyDaveStopTalking(lawnApp);
            StoreScreen_EnableButtons(storeScreen, false);
            do {
                newPageIndex = storeScreen[192] + 1;
                if (newPageIndex == 4) {
                    newPageIndex = 5;
                    storeScreen[192] = 5;
                } else if (newPageIndex > 4) {
                    newPageIndex = 0;
                    storeScreen[192] = 0;
                } else {
                    storeScreen[192] = newPageIndex;
                }
            } while (!StoreScreen_IsPageShown(storeScreen, newPageIndex));
            break;
    }
}

void (*old_StoreScreen_PurchaseItem)(int *, StoreItem::StoreItem);

void StoreScreen_PurchaseItem(int *storeScreen, StoreItem::StoreItem item) {
    old_StoreScreen_PurchaseItem(storeScreen, item);
    LawnApp *lawnApp = (LawnApp*)storeScreen[184];
    PlayerInfo* mPlayerInfo = lawnApp->mPlayerInfo;

    // 检查植物全收集成就
    for (int i = StoreItem::STORE_ITEM_PLANT_GATLINGPEA; i <= StoreItem::STORE_ITEM_PLANT_IMITATER; ++i) {
        if (mPlayerInfo->mPurchases[i] == 0) {
            return;
        }
    }
    LawnApp_GrantAchievement(lawnApp,AchievementId::ACHIEVEMENT_MORTICULTURALIST);
}

void (*old_StoreScreen_Draw)(int *storeScreen, Sexy::Graphics *a2);

void StoreScreen_Draw(int *storeScreen, Sexy::Graphics *a2) {
    // 绘制商店页数字符串
    old_StoreScreen_Draw(storeScreen, a2);
    int theTotalPages = 0;
    if (LawnApp_HasFinishedAdventure((LawnApp *) storeScreen[184]) && showHouse) {
        theTotalPages = 5;
    } else {
        for (int i = 0; i < 4; ++i) {
            if (StoreScreen_IsPageShown(storeScreen, i)) {
                theTotalPages++;
            }
        }
    }

    if (theTotalPages <= 1) return;
    int mPage = storeScreen[192] == 5 ? 5 : storeScreen[192] + 1;
    int holder[1];
    Sexy_StrFormat(holder, "%d/%d", mPage, theTotalPages);
    Color theColor = {200, 200, 200, 255};
    TodDrawString(a2, holder, 410, 512, *Sexy_FONT_BRIANNETOD16_Addr, theColor,DrawStringJustification::Center);
    Sexy_String_Delete(holder);
}
#endif //PVZ_TV_1_1_5_STORESCREEN_CPP
