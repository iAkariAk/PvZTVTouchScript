//
// Created by Administrator on 2024/3/1.
//

#ifndef PVZ_TV_1_1_5_STORESCREENTOUCH_CPP
#define PVZ_TV_1_1_5_STORESCREENTOUCH_CPP

#include "StoreScreen.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Board/Board.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

StoreScreenTouchState::StoreScreenTouchState mStoreScreenTouchState = StoreScreenTouchState::None;

void (*old_StoreScreen_MouseDown)(int *storeScreen, int x, int y, int theClickCount);

void StoreScreen_MouseDown(int *storeScreen, int x, int y, int theClickCount) {
    bool mBubbleClickToContinue = *((_BYTE *) storeScreen + 756);
    StoreItem::StoreItem mSelectedStoreItemType = *((StoreItem::StoreItem *) storeScreen + 194);
    if (mBubbleClickToContinue) {
        //初次捡到戴夫车钥匙时会进入商店并且有一段戴夫对话，这里用于识别戴夫对话
        StoreScreen_AdvanceCrazyDaveDialog(storeScreen);
        return;
    }
    if (!StoreScreen_CanInteractWithButtons(storeScreen)) {
        //翻页过程中无法触控
        return;
    }
    int mPrevButtonWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_STORE_PREVBUTTON_Addr);
    int mPrevButtonHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_STORE_PREVBUTTON_Addr);
    int mNextButtonWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_STORE_NEXTBUTTON_Addr);
    int mNextButtonHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_STORE_NEXTBUTTON_Addr);
    int mBackButtonWidth = Sexy_Image_GetWidth(*Sexy_IMAGE_STORE_MAINMENUBUTTON_Addr);
    int mBackButtonHeight = Sexy_Image_GetHeight(*Sexy_IMAGE_STORE_MAINMENUBUTTON_Addr);
    TRect mPrevButtonRect = {storeScreen[198] + 172,storeScreen[199] + 375,mPrevButtonWidth,mPrevButtonHeight};
    TRect mNextButtonRect = {storeScreen[198] + 573,storeScreen[199] + 373,mNextButtonWidth,mNextButtonHeight};
    TRect mBackButtonRect = {storeScreen[198] + 305, storeScreen[199] + 510,mBackButtonWidth,mBackButtonHeight};

    if (TRect_Contains(&mBackButtonRect, x, y)) {
        mStoreScreenTouchState = StoreScreenTouchState::Back;
        return;
    }


    bool isPageShown = StoreScreen_IsPageShown(storeScreen, 1);
    if (isPageShown) {

        if (TRect_Contains(&mPrevButtonRect, x, y)) {
            mStoreScreenTouchState = StoreScreenTouchState::Prev;
            return;
        }

        if (TRect_Contains(&mNextButtonRect, x, y)) {
            mStoreScreenTouchState = StoreScreenTouchState::Next;
            return;
        }
    }

//    StoreScreen_PurchaseItem(storeScreen, StoreItem::STORE_ITEM_BLUEPRINT_CHANGE);

    for (int i = 0; i < 8; i++) {
        StoreItem::StoreItem storeItemType = StoreScreen_GetStoreItemType(storeScreen, i);
        if (storeItemType != StoreItem::STORE_ITEM_INVALID) {
            int theX = 0;
            int theY = 0;
            int theCount = 0;
            Sexy::Image *theImage = NULL;
            StoreScreen_GetStoreItemInfo(storeScreen, i, storeItemType, &theImage, &theX, &theY,
                                         &theCount);
            int theImageWidth = 80;
            int theImageHeight = 80;
            if (theImage != NULL) {
                theImageWidth = Sexy_Image_GetWidth(theImage);
                theImageHeight = Sexy_Image_GetHeight(theImage);
            }

//            LOGD("i:%d storeItemType:%d theX:%d theY:%d x:%d y:%d theImageWidth:%d theImageHeight:%d", i, storeItemType, theX, theY, x, y, theImageWidth,
//                 theImageHeight);
//            int theImageWidth = 80;
//            int theImageHeight = 80;
            TRect itemRect = {theX - theImageWidth / 2, theY - theImageHeight, theImageWidth,
                               theImageHeight};
            if (TRect_Contains(&itemRect, x, y)) {
                if (mSelectedStoreItemType != storeItemType) {
                    StoreScreen_SetSelectedSlot((int) storeScreen, i);
                } else {
                    if (StoreScreen_IsItemSoldOut(storeScreen, storeItemType) ||
                        StoreScreen_IsItemUnavailable(storeScreen, storeItemType) ||
                        StoreScreen_IsComingSoon(storeScreen, storeItemType)) {
                        return;
                    }
                    StoreScreen_PurchaseItem(storeScreen, storeItemType);
                }
            }
        }
    }
}


void (*old_StoreScreen_MouseUp)(int *storeScreen, int x, int y, int theClickCount);

void StoreScreen_MouseUp(int *storeScreen, int x, int y, int theClickCount) {
    switch (mStoreScreenTouchState) {
        case StoreScreenTouchState::Back:
            (*(void (__fastcall **)(int *, int)) (*storeScreen + 516))(storeScreen, 100);//StoreScreen_ButtonDepress(storeScreen,100)
            break;
        case StoreScreenTouchState::Prev:
            (*(void (__fastcall **)(int *, int)) (*storeScreen + 516))(storeScreen, 101);//StoreScreen_ButtonDepress(storeScreen,101)
            break;
        case StoreScreenTouchState::Next:
            (*(void (__fastcall **)(int *, int)) (*storeScreen + 516))(storeScreen, 102);//StoreScreen_ButtonDepress(storeScreen,102)
            break;
    }
    mStoreScreenTouchState = StoreScreenTouchState::None;
}



#endif //PVZ_TV_1_1_5_STORESCREENTOUCH_CPP
