//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_STORESCREEN_H
#define PVZ_TV_1_1_5_STORESCREEN_H

#include "../GlobalVariable.h"
#include "../Enums.h"

void (*StoreScreen_AdvanceCrazyDaveDialog)(int*);

bool (*StoreScreen_CanInteractWithButtons)(int*);

StoreItem::StoreItem (*StoreScreen_GetStoreItemType)(int*,int);

void (*StoreScreen_GetStoreItemInfo)(int*,int,StoreItem::StoreItem,Sexy::Image**,int*,int*,int*);

bool (*StoreScreen_IsItemSoldOut)(int*,StoreItem::StoreItem);

bool (*StoreScreen_IsItemUnavailable)(int*,StoreItem::StoreItem);

bool (*StoreScreen_IsComingSoon)(int*,StoreItem::StoreItem);

void StoreScreen_PurchaseItem(int*,StoreItem::StoreItem);

bool (*StoreScreen_IsPageShown)(int*,int);

void (*StoreScreen_EnableButtons)(int*,bool);

bool (*StoreScreen_IsPottedPlant)(int*,StoreItem::StoreItem);

#endif //PVZ_TV_1_1_5_STORESCREEN_H
