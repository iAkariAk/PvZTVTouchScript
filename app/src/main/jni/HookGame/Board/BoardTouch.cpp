//
// Created by Administrator on 2024/1/5.
//

#ifndef PVZ_TV_1_1_1_BOARDTOUCH_H
#define PVZ_TV_1_1_1_BOARDTOUCH_H

#include <cstddef>
#include "../GlobalVariable.h"
#include "Board.h"
#include "../Coin/Coin.h"
#include "../SpecialConstraints.h"
#include "HookGame/SeedBank/SeedBank.cpp"
#include "HookGame/SeedChooserScreen/SeedChooserScreen.cpp"
#include "HookGame/ZenGarden/ZenGarden.h"
#include "HookGame/SeedBank/SeedBank.h"
#include "HookGame/GamepadControls/GamepadControls.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Challenge/Challenge.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void Board_MouseMove(Board *board, int x, int y) {
    //无用。鼠标指针移动、但左键未按下时调用
    //LOGD("Move%d %d", x, y);
    old_Board_MouseMove(board, x, y);
//    positionAutoFix = false;
//    LawnApp *mApp = board->mApp;
//    GameMode::GameMode mGameMode = mApp->mGameMode;
//    GamepadControls* gamepadControls1 = board->mGamepadControls1;
//    CursorObject* cursorObject = board->mCursorObject1;
//    CursorType::CursorType mCursorType = cursorObject->mCursorType;
//    if (mGameMode == GameMode::ChallengeBeghouledTwist) {
//        gamepadControls1->mCursorPositionX = x - 40;
//        gamepadControls1->mCursorPositionY = y - 40;
//    } else if (mCursorType == CursorType::WateringCan && mApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_GOLD_WATERINGCAN] != 0) {
//        gamepadControls1->mCursorPositionX = x - 40;
//        gamepadControls1->mCursorPositionY = y - 40;
//    }else {
//        gamepadControls1->mCursorPositionX = x;
//        gamepadControls1->mCursorPositionY = y;
//    }
}



bool Board_MouseHitTest(Board *board, int x, int y, HitResult* hitResult, bool playerIndex) {
    LawnApp *mApp = board->mApp;
    GameMode::GameMode mGameMode = mApp->mGameMode;
    if (mGameMode == GameMode::TwoPlayerVS) {
        if (TRect_Contains(&mTouchVSShovelRect, x, y)) {
            hitResult->mObjectType = GameObjectType::Shovel;
            return true;
        }
    } else {
        TRect shovelButtonRect;
        Board_GetShovelButtonRect(&shovelButtonRect, board);
        if (board->mShowShovel && TRect_Contains(&shovelButtonRect, x, y)) {
            hitResult->mObjectType = GameObjectType::Shovel;
            return true;
        }
    }

    if (LawnApp_IsCoopMode(board->mApp)) {
        TRect butterButtonRect;
        Board_GetButterButtonRect(&butterButtonRect, board);
        if (board->mShowButter && TRect_Contains(&butterButtonRect, x, y)) {
            hitResult->mObjectType = GameObjectType::Butter;
            return true;
        }
    }


    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    SeedBank *mSeedBank = GamepadControls_GetSeedBank(gamepadControls1);
    if (SeedBank_ContainsPoint(mSeedBank, x, y)) {
        if (SeedBank_MouseHitTest(mSeedBank, x, y, hitResult)) {
            CursorObject* cursorObject = board->mCursorObject1;
            CursorType::CursorType mCursorType = cursorObject->mCursorType;
            if (mCursorType == CursorType::PlantFromBank) {
                Board_RefreshSeedPacketFromCursor(board, 0);
            }
            return true;
        }
        hitResult->mObjectType = GameObjectType::SeedBankBlank;
        return false;
    }


    if (mGameMode == GameMode::TwoPlayerVS || LawnApp_IsCoopMode(mApp)){
        GamepadControls* gamepadControls2 = board->mGamepadControls2;
        SeedBank *mSeedBank2 = GamepadControls_GetSeedBank(gamepadControls2);
        if (SeedBank_ContainsPoint(mSeedBank2, x, y)) {
            if (SeedBank_MouseHitTest(mSeedBank2, x, y, hitResult)) {
                CursorObject* cursorObject_2P = board->mCursorObject2;
                CursorType::CursorType mCursorType_2P = cursorObject_2P->mCursorType;
                if (mCursorType_2P == CursorType::PlantFromBank) {
                    Board_RefreshSeedPacketFromCursor(board, 1);
                }
                return true;
            }
            hitResult->mObjectType = GameObjectType::SeedBankBlank;
            return false;
        }
    }


    if (mGameMode == GameMode::ChallengeZenGarden || mGameMode == GameMode::ChallengeTreeOfWisdom) {
        TRect rect;
        for (int i = GameObjectType::WateringCan; i <= GameObjectType::TreeOfWisdomGarden ; i++) {
            if (Board_CanUseGameObject(board, (GameObjectType::GameObjectType)i)) {
                Board_GetZenButtonRect(&rect, board, (GameObjectType::GameObjectType)i);
                if (TRect_Contains(&rect, x, y)) {
                    hitResult->mObjectType = (GameObjectType::GameObjectType) i;
                    return true;
                }
            }
        }
    }

    if (old_Board_MouseHitTest(board, x, y, hitResult, playerIndex)) {
        if (hitResult->mObjectType == GameObjectType::TreeOfWisdomGarden) {
            hitResult->mObjectType = GameObjectType::None;
            return false;
        }
        return true;
    }
    return false;
}

int mTouchLastX = 0;
int mTouchLastY = 0;
int mTouchDownX = 0;
int mTouchDownY = 0;
bool mSendKeyWhenTouchUp = false;


TouchState::TouchState mTouchState = TouchState::None;

float mHeavyWeaponX = 0.0f;

//inline int seedBankHeight = 87;

inline int mTouchShovelRectWidth = 72;

inline int mTouchButterRectWidth = 72;

inline int mTouchTrigger = 40;

TRect slotMachineRect = {250, 0, 320, 100};

void Board_MouseDown(Board *board, int x, int y, int theClickCount) {
    //触控落下手指在此处理
    old_Board_MouseDown(board, x, y, theClickCount);
    mTouchDownX = x;
    mTouchDownY = y;
    mTouchLastX = x;
    mTouchLastY = y;
//    xx = x;
//    yy = y;
//    LOGD("%d %d",x,y);
    if (keyboardMode) {
        GamePatches.UsefulSeedPacketAutoPickupDisable.Modify();
    }
    keyboardMode = false;
    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
    int mGameState = gamepadControls1->mGamepadState;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

    GamepadControls* gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P  = gamepadControls2->mIsCobCannonSelected;
    HitResult hitResult;
    Board_MouseHitTest(board, x, y, &hitResult, false);
    GameObjectType::GameObjectType mObjectType = hitResult.mObjectType;
    Challenge *mChallenge = board->mChallenge;
    LawnApp *mApp = board->mApp;
    GameMode::GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::TwoPlayerVS || LawnApp_IsCoopMode(mApp));
    CutScene *mCutScene = board->mCutScene;
    GameScenes::GameScenes mGameScene = mApp->mGameScene;

    SeedChooserScreen* mSeedChooserScreen = mApp->mSeedChooserScreen;
    if (mGameScene == GameScenes::LevelIntro && mSeedChooserScreen != NULL && mSeedChooserScreen->mChooseState == SeedChooserState::ViewLawn) {
        SeedChooserScreen_GameButtonDown(mSeedChooserScreen, 6, 0);
        return;
    }
    if (mGameScene == GameScenes::LevelIntro) {
        CutScene_MouseDown(mCutScene, x, y);
    }


    if (mObjectType == GameObjectType::Seedpacket) {
        if (mGameScene == GameScenes::LevelIntro) return;
        SeedPacket *seedPacket = (SeedPacket*)hitResult.mObject;
        mPlayerIndex = (TouchPlayerIndex::TouchPlayerIndex) SeedPacket_GetPlayerIndex(seedPacket);//玩家1或玩家2
        if (mPlayerIndex == TouchPlayerIndex::Player1) {
            requestDrawShovelInCursor = false;//不再绘制铲子
            if (isCobCannonSelected) {//如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
            }
            if (mGameMode == GameMode::ChallengeHeavyWeapon ||
                mGameMode == GameMode::ChallengeBeghouled ||
                mGameMode == GameMode::ChallengeBeghouledTwist ||
                mGameMode == GameMode::ChallengeZombiquarium) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUp = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::ChallengeSlotMachine) {//拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
                return;
            }
            mTouchState = TouchState::SeedBank;//记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 0);
            int newSeedPacketIndex = seedPacket->mIndex;
            gamepadControls1->mSelectedSeedIndex = newSeedPacketIndex;
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用
            if (currentSeedBankIndex != newSeedPacketIndex || mGameState != 7) {
                gamepadControls1->mGamepadState = 7;
                gamepadControls1->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex == newSeedPacketIndex && mGameState == 7) {
                gamepadControls1->mGamepadState = 1;
                if(!isTwoSeedBankMode)
                    gamepadControls1->mIsInShopSeedBank = true;
            }
        }
        else{
            requestDrawButterInCursor = false;//不再绘制黄油
            SeedPacket *seedPacket = (SeedPacket*) hitResult.mObject;
            if (isCobCannonSelected_2P) {//如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
            }
            if (mGameMode == GameMode::ChallengeHeavyWeapon ||
                mGameMode == GameMode::ChallengeBeghouled ||
                mGameMode == GameMode::ChallengeBeghouledTwist ||
                mGameMode == GameMode::ChallengeZombiquarium) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUp = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::ChallengeSlotMachine) {//拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls2, 50, 1112);
                return;
            }
            mTouchState = TouchState::SeedBank;//记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 1);
            int newSeedPacketIndex_2P = seedPacket->mIndex;
            gamepadControls2->mSelectedSeedIndex = newSeedPacketIndex_2P;
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用

            if (currentSeedBankIndex_2P != newSeedPacketIndex_2P || mGameState_2P != 7) {
                gamepadControls2->mGamepadState = 7;
                gamepadControls2->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex_2P == newSeedPacketIndex_2P && mGameState_2P == 7) {
                gamepadControls2->mGamepadState = 1;
                if(!isTwoSeedBankMode)
                    gamepadControls2->mIsInShopSeedBank = true;
            }
        }
        return;
    }

    if (mObjectType == GameObjectType::SeedBankBlank){
        return;
    }

    CursorObject* cursorObject = board->mCursorObject1;
    CursorType::CursorType mCursorType = cursorObject->mCursorType;
    CursorObject* cursorObject_2P = board->mCursorObject2;
    CursorType::CursorType mCursorType_2P = cursorObject_2P->mCursorType;

    if (mObjectType == GameObjectType::Shovel) {
        mPlayerIndex = TouchPlayerIndex::Player1;//玩家1
        mTouchState = TouchState::ShovelRect;
        if (mGameState == 7) {
            gamepadControls1->mGamepadState = 1;
            if(!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用
        }
        if (mCursorType == CursorType::PlantFromUsableCoin) {
            Board_RefreshSeedPacketFromCursor(board, 0);
            Board_ClearCursor(board, 0);
        }
        if (isCobCannonSelected) {//如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 0);
        if (requestDrawShovelInCursor) {
            requestDrawShovelInCursor = false;
        } else {
            requestDrawShovelInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Shovel);
        }
        return;
    }
    if (mObjectType == GameObjectType::Butter) {
        mPlayerIndex = TouchPlayerIndex::Player2;//玩家2
        mTouchState = TouchState::ButterRect;
        if (mGameState == 7) {
            gamepadControls2->mGamepadState = 1;
            if(!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用
        }
        if (mCursorType_2P == CursorType::PlantFromUsableCoin) {
            Board_RefreshSeedPacketFromCursor(board, 1);
            Board_ClearCursor(board, 1);
        }
        if (isCobCannonSelected_2P) {//如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 1);
        if (requestDrawButterInCursor) {
            requestDrawButterInCursor = false;
        } else {
            requestDrawButterInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Floop);
        }
        return;
    }

    if (mGameMode == GameMode::TwoPlayerVS){
        mPlayerIndex = Board_PixelToGridX(board,x,y) > 5 ? TouchPlayerIndex::Player2 : TouchPlayerIndex::Player1;
    }else if (mGameMode >= GameMode::TwoPlayerCoopDay && mGameMode <= GameMode::TwoPlayerCoopEndless){
        mPlayerIndex = x > 400 ? TouchPlayerIndex::Player2 : TouchPlayerIndex::Player1;
    }else{
        mPlayerIndex = TouchPlayerIndex::Player1;
    }

    if (mPlayerIndexSecond != TouchPlayerIndex::None && mPlayerIndexSecond == mPlayerIndex){
        mPlayerIndex = TouchPlayerIndex::None;
        mTouchState = TouchState::None;
        return;
    }

    if (mObjectType == GameObjectType::Coin) {
        Coin *coin = (Coin *)hitResult.mObject;
        if (coin->mType == CoinType::UsableSeedPacket) {
            mTouchState = TouchState::UsefulSeedPacket;
            requestDrawShovelInCursor = false;
//            if (mCursorType == CursorType::PlantFromUsableCoin) {
//                LOGD("5656565656");
//                GamepadControls_OnKeyDown(gamepadCon
//               trols1, 27, 1096);//放下手上的植物卡片
//                mSendKeyWhenTouchUp = false;
//            }
            Board_RefreshSeedPacketFromCursor(board, 0);
            old_Coin_GamepadCursorOver(coin, 0);//捡起植物卡片
            //            Coin_Collect((int) coin, 0);
        }
    }

    if (mGameMode == GameMode::ChallengeSlotMachine) {//拉老虎机用
        if (TRect_Contains(&slotMachineRect, x, y)) {
            GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
            return;
        }
    }

    if (mGameMode == GameMode::ChallengeHeavyWeapon) {//移动重型武器
        mTouchState = TouchState::HeavyWeapon;
        mHeavyWeaponX = mChallenge->mHeavyWeaponX;
        return;
    }

    if (Challenge_MouseDown(mChallenge, x, y, 0, &hitResult, 0)) {
        if (LawnApp_IsScaryPotterLevel(mApp)) {
            requestDrawShovelInCursor = false;
        }
        if (mGameMode == GameMode::ChallengeBeghouledTwist) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
        if (!LawnApp_IsWhackAZombieLevel(mApp) || mGameState != 7)
            return;//这一行代码的意义：在锤僵尸关卡，手持植物时，允许拖动种植。
    }
    if (mObjectType == GameObjectType::WateringCan ||
        mObjectType == GameObjectType::Fertilizer || mObjectType == GameObjectType::BugSpray ||
        mObjectType == GameObjectType::Phonograph || mObjectType == GameObjectType::Chocolate ||
        mObjectType == GameObjectType::Glove || mObjectType == GameObjectType::MoneySign ||
        mObjectType == GameObjectType::Wheelbarrow || mObjectType == GameObjectType::TreeFood) {
        Board_PickUpTool(board, mObjectType, 0);
        ((ZenGardenControls*)gamepadControls1)->mObjectType = mObjectType;
        mTouchState = TouchState::ZenGardenTools;
        return;
    }

    if (mObjectType == GameObjectType::ZenGarden || mObjectType == GameObjectType::MushRoomGarden ||
        mObjectType == GameObjectType::QuariumGarden || mObjectType == GameObjectType::TreeOfWisdomGarden) {
        ((ZenGardenControls*)gamepadControls1)->mObjectType = mObjectType;
        Board_MouseDownWithTool(board, x, y, 0, mObjectType + 3, 0);
        return;
    }


    if (mCursorType == CursorType::WateringCan || mCursorType == CursorType::Fertilizer ||
        mCursorType == CursorType::BugSpray || mCursorType == CursorType::Phonograph ||
        mCursorType == CursorType::Chocolate || mCursorType == CursorType::Glove ||
        mCursorType == CursorType::MoneySign || mCursorType == CursorType::Wheelbarrow ||
            mCursorType == CursorType::TreeFood ||mCursorType == CursorType::PlantFromGlove) {
            mSendKeyWhenTouchUp = true;
    }

//    *(_DWORD *) (gamepadControls1 + 152) = 0;//疑似用于设置该gamepadControls1属于玩家1。可能的取值：-1，0，1
//    其中，1P恒为0，2P禁用时为-1，2P启用时为1。

    if (mPlayerIndex == TouchPlayerIndex::Player1){
        if (mGameMode == GameMode::ChallengeBeghouledTwist) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else if (mCursorType == CursorType::WateringCan && mApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_GOLD_WATERINGCAN] != 0){
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        }else{
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
    }else{
        if (mGameMode == GameMode::ChallengeBeghouledTwist) {
            gamepadControls2->mCursorPositionX = x - 40;
            gamepadControls2->mCursorPositionY = y - 40;
        } else {
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }


    int seekBankPosition = gamepadControls1->mSelectedSeedIndex;
    if (mPlayerIndex == TouchPlayerIndex::Player1){
        if (mGameState == 7 || isCobCannonSelected || requestDrawShovelInCursor ||
            (mCursorType == CursorType::PlantFromUsableCoin &&
             mTouchState != TouchState::UsefulSeedPacket)) {
            mTouchState = TouchState::PickingSomething;
            mSendKeyWhenTouchUp = true;
        }
    }else{
        if (mGameState_2P == 7 || isCobCannonSelected_2P || requestDrawButterInCursor ||
            (mCursorType_2P == CursorType::PlantFromUsableCoin &&
             mTouchState != TouchState::UsefulSeedPacket)) {
            mTouchState = TouchState::PickingSomething;
            mSendKeyWhenTouchUp = true;
        }
    }


    if (mObjectType == GameObjectType::Plant) {
        if (mPlayerIndex == TouchPlayerIndex::Player1 && requestDrawShovelInCursor) return;
        Plant *plant = (Plant*)hitResult.mObject;
        bool isValidCobCannon = plant->mSeedType == SeedType::Cobcannon && plant->mState == PlantState::CobcannonReady;
        if (isValidCobCannon) {
            if (mPlayerIndex == TouchPlayerIndex::Player1) {
                if (mGameState == 7) {
                    gamepadControls1->mGamepadState = 1;
                    mSendKeyWhenTouchUp = false;
                    if(!isTwoSeedBankMode)
                        gamepadControls1->mIsInShopSeedBank = true;
                    int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
                    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                    seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用
                }
                if (gamepadControls2->mIsCobCannonSelected && gamepadControls2->mCobCannonPlantIndexInList == plant->mPlantIndexInList){
                    // 不能同时选同一个加农炮！
                    mTouchState = TouchState::None;
                    return;
                }
                GamepadControls_pickUpCobCannon((int) gamepadControls1, (int) plant);
            }else{
                if (mGameState_2P == 7) {
                    gamepadControls2->mGamepadState = 1;
                    mSendKeyWhenTouchUp = false;
                    if(!isTwoSeedBankMode)
                        gamepadControls2->mIsInShopSeedBank = true;
                    int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
                    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                    seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用
                }
                if (gamepadControls1->mIsCobCannonSelected && gamepadControls1->mCobCannonPlantIndexInList == plant->mPlantIndexInList){
                    // 不能同时选同一个加农炮！
                    mTouchState = TouchState::None;
                    return;
                }
                GamepadControls_pickUpCobCannon((int) gamepadControls2, (int) plant);
            }
            mTouchState = TouchState::ValidCobCannon;
            return;
        }
    }
    if (mTouchState == TouchState::None)
        mTouchState = TouchState::Board;
}


void Board_MouseDrag(Board *board, int x, int y) {
    //Drag函数仅仅负责移动光标即可
    old_Board_MouseDrag(board, x, y);
//    xx = x;
//    yy = y;
//    LOGD("%d %d",x,y);
    if (mTouchState == TouchState::None) return;
    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;
    GamepadControls* gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P = gamepadControls2->mIsCobCannonSelected;
    int mGameState = gamepadControls1->mGamepadState;
    LawnApp *mApp = board->mApp;
    GameMode::GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::TwoPlayerVS || (mGameMode >= GameMode::TwoPlayerCoopDay && mGameMode <= GameMode::TwoPlayerCoopEndless));
    int seedBankHeight = LawnApp_IsChallengeWithoutSeedBank(mApp) ? 87 : seedBank->mY + seedBank->mHeight;
    if (mTouchState == TouchState::SeedBank && mTouchLastY < seedBankHeight &&
        y >= seedBankHeight) {
        mTouchState = TouchState::BoardMovedFromSeedBank;
        if (mPlayerIndex == TouchPlayerIndex::Player1){
            gamepadControls1->mGamepadState = 7;
            gamepadControls1->mIsInShopSeedBank = false;
            requestDrawShovelInCursor = false;
        }else{
            gamepadControls2->mGamepadState = 7;
            gamepadControls2->mIsInShopSeedBank = false;
            requestDrawButterInCursor = false;
        }
        mSendKeyWhenTouchUp = true;
    }

    if (mTouchState == TouchState::ShovelRect) {
        if (mGameMode == GameMode::TwoPlayerVS) {
            if (TRect_Contains(&mTouchVSShovelRect, mTouchLastX, mTouchLastY) &&
                !TRect_Contains(&mTouchVSShovelRect, x, y)) {
                mTouchState = TouchState::BoardMovedFromShovelRect;
                if (!requestDrawShovelInCursor) LawnApp_PlayFoley( mApp, FoleyType::Shovel);
                requestDrawShovelInCursor = true;
                gamepadControls1->mGamepadState = 1;
                mSendKeyWhenTouchUp = true;
            }
        } else if (mTouchLastY < mTouchShovelRectWidth && y >= mTouchShovelRectWidth) {
            mTouchState = TouchState::BoardMovedFromShovelRect;
            if (!requestDrawShovelInCursor) LawnApp_PlayFoley(mApp, FoleyType::Shovel);
            requestDrawShovelInCursor = true;
            gamepadControls1->mGamepadState = 1;
            mSendKeyWhenTouchUp = true;
        }
    }

    if (mTouchState == TouchState::ButterRect && mTouchLastY < mTouchButterRectWidth &&
        y >= mTouchButterRectWidth) {
        mTouchState = TouchState::BoardMovedFromButterRect;
        if (!requestDrawButterInCursor) LawnApp_PlayFoley(mApp, FoleyType::Floop);
        requestDrawButterInCursor = true;
        gamepadControls2->mGamepadState = 1;
        mSendKeyWhenTouchUp = true;
    }

    if (mTouchState == TouchState::ValidCobCannon || mTouchState == TouchState::UsefulSeedPacket) {
        if (!mSendKeyWhenTouchUp &&
            (abs(x - mTouchDownX) > mTouchTrigger || abs(y - mTouchDownY) > mTouchTrigger)) {
            mSendKeyWhenTouchUp = true;
        }
    }

    if (mTouchState == TouchState::ZenGardenTools && mTouchLastY < mTouchButterRectWidth &&
        y >= mTouchButterRectWidth){
        mTouchState = TouchState::BoardMovedFromZenGardenTools;
        mSendKeyWhenTouchUp = true;
    }

    if (mPlayerIndex == TouchPlayerIndex::Player1 && isCobCannonSelected && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);//退选加农炮
        mTouchState = TouchState::None;
        mSendKeyWhenTouchUp = false;
    }
    if (mPlayerIndex== TouchPlayerIndex::Player2 && isCobCannonSelected_2P && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);//退选加农炮
        mTouchState = TouchState::None;
        mSendKeyWhenTouchUp = false;
    }

    if (mPlayerIndex == TouchPlayerIndex::Player1){
        if (mGameState == 7 && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
            gamepadControls1->mGamepadState = 1;//退选植物
            if(!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用
            mTouchState = TouchState::None;
            mSendKeyWhenTouchUp = false;
        }
    }else{
        if (mGameState_2P == 7 && mTouchLastY > seedBankHeight && y <= seedBankHeight) {
            gamepadControls2->mGamepadState = 1;//退选植物
            if(!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用
            mTouchState = TouchState::None;
            mSendKeyWhenTouchUp = false;
        }
    }


    if (mGameMode == GameMode::ChallengeHeavyWeapon && mTouchState == TouchState::HeavyWeapon) {
        Challenge *mChallenge = board->mChallenge;
        mChallenge->mHeavyWeaponX = mHeavyWeaponX + x - mTouchDownX;//移动重型武器X坐标
        return;
    }

    if (mGameMode == GameMode::ChallengeBeghouledTwist) {
        return;
    }

    if (mTouchState != TouchState::SeedBank && mTouchState != TouchState::ZenGardenTools) {
        if (x > 770) x = 770;
        if (x < 40) x = 40;
        if (y > 580) y = 580;
        if (mPlayerIndex == TouchPlayerIndex::Player1) {
            CursorObject* cursorObject = board->mCursorObject1;
            CursorType::CursorType mCursorType = cursorObject->mCursorType;
            if (mCursorType == CursorType::WateringCan && mApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_GOLD_WATERINGCAN] != 0){
                gamepadControls1->mCursorPositionX = x - 40;
                gamepadControls1->mCursorPositionY = y - 40;
            }else{
                gamepadControls1->mCursorPositionX = x;
                gamepadControls1->mCursorPositionY = y;
            }
        }else{
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }
    mTouchLastX = x;
    mTouchLastY = y;
//    LOGD("%d %d",mPlayerIndex,mPlayerIndexSecond);
}

void Board_MouseUp(Board *board, int x, int y, int theClickCount) {
    old_Board_MouseUp(board, x, y, theClickCount);
    if (mTouchState != TouchState::None && mSendKeyWhenTouchUp) {
        GamepadControls* gamepadControls1 = board->mGamepadControls1;
        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
        int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
        int numSeedsInBank = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
        int mGameState = gamepadControls1->mGamepadState;
        bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

        GamepadControls* gamepadControls2 = board->mGamepadControls2;
        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
        int numSeedsInBank_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
        int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
        int mGameState_2P = gamepadControls2->mGamepadState;
        bool isCobCannonSelected_2P  = gamepadControls2->mIsCobCannonSelected;

        LawnApp *mApp = board->mApp;
        GameMode::GameMode mGameMode = mApp->mGameMode;
        CursorObject* cursorObject = board->mCursorObject1;
        CursorType::CursorType mCursorType = cursorObject->mCursorType;
        CursorObject* cursorObject_2P = board->mCursorObject2;
        CursorType::CursorType mCursorType_2P = cursorObject_2P->mCursorType;
        Challenge *mChallenge = board->mChallenge;
        ChallengeState::ChallengeState mChallengeState = mChallenge->mChallengeState;

        if (mPlayerIndex == TouchPlayerIndex::Player1) {
            if (requestDrawShovelInCursor) {
                Board_ShovelDown(board);
            } else if (mGameState == 7 || isCobCannonSelected || mCursorType == CursorType::PlantFromUsableCoin) {
                if (mGameMode == GameMode::ChallengeBeghouled || mGameMode == GameMode::ChallengeBeghouledTwist) {
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                } else if ((mGameMode == GameMode::ChallengeLastStand && mChallenge->mChallengeState == ChallengeState::Normal && mApp->mGameScene == GameScenes::Playing) || mGameMode == GameMode::TwoPlayerVS) {
                    GamepadControls_OnButtonDown(gamepadControls1, 6, 0, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                }
                int mGameStateNew = gamepadControls1->mGamepadState;
                int seedPacketIndexNew = gamepadControls1->mSelectedSeedIndex;
                int numSeedsInBankNew = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
                gamepadControls1->mIsInShopSeedBank = mGameStateNew != 7;
                if (mGameState != mGameStateNew) {
                    if (!Board_HasConveyorBeltSeedBank(board, 0) || numSeedsInBank == numSeedsInBankNew) {//修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                        seedBank->mSeedPackets[seedPacketIndexNew].mLastSelectedTime = 0.0f;//动画效果专用
                    }
                }
            }else if(mCursorType == CursorType::WateringCan || mCursorType == CursorType::Fertilizer ||
                     mCursorType == CursorType::BugSpray || mCursorType == CursorType::Phonograph ||
                     mCursorType == CursorType::Chocolate || mCursorType == CursorType::Glove ||
                     mCursorType == CursorType::MoneySign || mCursorType == CursorType::Wheelbarrow ||
                     mCursorType == CursorType::TreeFood ||mCursorType == CursorType::PlantFromGlove){
                if(!Board_ZenGardenItemNumIsZero(board, mCursorType)){
                    if (mCursorType == CursorType::WateringCan && mApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_GOLD_WATERINGCAN]  != 0){
                        Board_MouseDownWithTool(board, x - 40, y - 40, 0, mCursorType, 0);
                    }else{
                        Board_MouseDownWithTool(board, x, y, 0, mCursorType, 0);
                    }
                }
            }
        }else{
            if (requestDrawButterInCursor) {
                requestDrawButterInCursor = false;
            } else if (mGameState_2P == 7 || isCobCannonSelected_2P || mCursorType_2P == CursorType::PlantFromUsableCoin) {
                if (mGameMode == GameMode::ChallengeBeghouled || mGameMode == GameMode::ChallengeBeghouledTwist) {
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                } else if ((mGameMode == GameMode::ChallengeLastStand && mChallengeState == ChallengeState::Normal && mApp->mGameScene == GameScenes::Playing) || mGameMode == GameMode::TwoPlayerVS) {
                    GamepadControls_OnButtonDown(gamepadControls2, 6, 1, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                }
                int mGameStateNew_2P = gamepadControls2->mGamepadState;
                int seedPacketIndexNew_2P = gamepadControls2->mSelectedSeedIndex;
                int numSeedsInBankNew_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
                gamepadControls2->mIsInShopSeedBank = mGameStateNew_2P!= 7;
                if (mGameState_2P != mGameStateNew_2P) {
                    if (!Board_HasConveyorBeltSeedBank(board, 1) || numSeedsInBank_2P == numSeedsInBankNew_2P) {//修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                        seedBank_2P->mSeedPackets[seedPacketIndexNew_2P].mLastSelectedTime = 0.0f;//动画效果专用
                    }
                }
                if (mGameMode == GameMode::TwoPlayerVS) {
                    gamepadControls2->mGamepadState = 1;
                }
            }
        }
    }
    mPlayerIndex = TouchPlayerIndex::None;
    mSendKeyWhenTouchUp = false;
    mTouchState = TouchState::None;
}

int mTouchLastXSecond = 0;
int mTouchLastYSecond = 0;
int mTouchDownXSecond = 0;
int mTouchDownYSecond = 0;
bool mSendKeyWhenTouchUpSecond = false;


TouchState::TouchState mTouchStateSecond = TouchState::None;

void Board_MouseDownSecond(Board *board, int x, int y, int theClickCount) {
    //触控落下手指在此处理
    mTouchDownXSecond = x;
    mTouchDownYSecond = y;
    mTouchLastXSecond = x;
    mTouchLastYSecond = y;
    if (keyboardMode) {
        GamePatches.UsefulSeedPacketAutoPickupDisable.Modify();
    }
    keyboardMode = false;


    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
    int mGameState = gamepadControls1->mGamepadState;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

    GamepadControls* gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P  = gamepadControls2->mIsCobCannonSelected;
    HitResult hitResult;
    Board_MouseHitTest(board, x, y, &hitResult, false);
    GameObjectType::GameObjectType mObjectType = hitResult.mObjectType;
    Challenge *mChallenge = board->mChallenge;
    LawnApp *mApp = board->mApp;
    GameMode::GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::TwoPlayerVS || (mGameMode >= GameMode::TwoPlayerCoopDay && mGameMode <= GameMode::TwoPlayerCoopEndless));
    CutScene *mCutScene = board->mCutScene;
    GameScenes::GameScenes mGameScene = mApp->mGameScene;

    SeedChooserScreen* mSeedChooserScreen = mApp->mSeedChooserScreen;
    if (mGameScene == GameScenes::LevelIntro && mSeedChooserScreen != NULL && mSeedChooserScreen->mChooseState == SeedChooserState::ViewLawn) {
        SeedChooserScreen_GameButtonDown(mSeedChooserScreen, 6, 0);
        return;
    }
    if (mGameScene == GameScenes::LevelIntro) {
        CutScene_MouseDown(mCutScene, x, y);
    }

    if (mObjectType == GameObjectType::Seedpacket) {
        if (mGameScene == GameScenes::LevelIntro) return;
        SeedPacket *seedPacket = (SeedPacket*)hitResult.mObject;
        int newSeedPacketIndex = seedPacket->mIndex;
        mPlayerIndexSecond = (TouchPlayerIndex::TouchPlayerIndex) SeedPacket_GetPlayerIndex(seedPacket);//玩家1或玩家2

        if (mPlayerIndexSecond == TouchPlayerIndex::Player1){
            requestDrawShovelInCursor = false;//不再绘制铲子
            if (isCobCannonSelected) {//如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
            }
            if (mGameMode == GameMode::ChallengeHeavyWeapon ||
                mGameMode == GameMode::ChallengeBeghouled ||
                mGameMode == GameMode::ChallengeBeghouledTwist ||
                mGameMode == GameMode::ChallengeZombiquarium) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUpSecond = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::ChallengeSlotMachine) {//拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
                return;
            }
            mTouchStateSecond = TouchState::SeedBank;//记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 0);

            gamepadControls1->mSelectedSeedIndex = newSeedPacketIndex;
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用

            if (currentSeedBankIndex != newSeedPacketIndex || mGameState != 7) {
                gamepadControls1->mGamepadState = 7;
                gamepadControls1->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex == newSeedPacketIndex && mGameState == 7) {
                gamepadControls1->mGamepadState = 1;
                if(!isTwoSeedBankMode)
                    gamepadControls1->mIsInShopSeedBank = true;
            }
        }
        else{
            requestDrawButterInCursor = false;//不再绘制黄油
            SeedPacket *seedPacket = (SeedPacket*)hitResult.mObject;
            if (isCobCannonSelected_2P) {//如果拿着加农炮，将其放下
                GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
            }
            if (mGameMode == GameMode::ChallengeHeavyWeapon ||
                mGameMode == GameMode::ChallengeBeghouled ||
                mGameMode == GameMode::ChallengeBeghouledTwist ||
                mGameMode == GameMode::ChallengeZombiquarium) {
                if (SeedPacket_CanPickUp(seedPacket)) {
                    mSendKeyWhenTouchUpSecond = true;
                } else {
                    LawnApp_PlaySample(mApp, *Sexy_SOUND_BUZZER_Addr);
                    return;
                }
            }
            if (mGameMode == GameMode::ChallengeSlotMachine) {//拉老虎机用
                GamepadControls_OnKeyDown(gamepadControls2, 50, 1112);
                return;
            }
            mTouchStateSecond = TouchState::SeedBank;//记录本次触控的状态
            Board_RefreshSeedPacketFromCursor(board, 1);
            int newSeedPacketIndex_2P =seedPacket->mIndex;
            gamepadControls2->mSelectedSeedIndex = newSeedPacketIndex_2P;
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用

            if (currentSeedBankIndex_2P != newSeedPacketIndex_2P || mGameState_2P != 7) {
                gamepadControls2->mGamepadState = 7;
                gamepadControls2->mIsInShopSeedBank = false;
                LawnApp_PlaySample(mApp, *Sexy_SOUND_SEEDLIFT_Addr);
            } else if (currentSeedBankIndex_2P == newSeedPacketIndex_2P && mGameState_2P == 7) {
                gamepadControls2->mGamepadState = 1;
                if(!isTwoSeedBankMode)
                    gamepadControls2->mIsInShopSeedBank = true;
            }
        }
        return;
    }

    if (mObjectType == GameObjectType::SeedBankBlank){
        return;
    }

    CursorObject* cursorObject = board->mCursorObject1;
    CursorType::CursorType mCursorType = cursorObject->mCursorType;
    CursorObject* cursorObject_2P = board->mCursorObject2;
    CursorType::CursorType mCursorType_2P = cursorObject_2P->mCursorType;
//    if (mCursorType == CursorType::WateringCan || mCursorType == CursorType::Fertilizer ||
//        mCursorType == CursorType::BugSpray || mCursorType == CursorType::Phonograph ||
//        mCursorType == CursorType::Chocolate || mCursorType == CursorType::Glove ||
//        mCursorType == CursorType::MoneySign || mCursorType == CursorType::Wheelbarrow ||
//        mCursorType == CursorType::TreeFood) {
//        Board_MouseDownWithTool(board, x, y, 0, mCursorType, false);
//        return;
//    }

    if (mObjectType == GameObjectType::Shovel) {
        if (!useNewShovel){
            GamepadControls_OnKeyDown(board->mGamepadControls1, 49, 1112);
            return;
        }
        mPlayerIndexSecond = TouchPlayerIndex::Player1;//玩家1
        mTouchStateSecond = TouchState::ShovelRect;
        if (mGameState == 7) {
            gamepadControls1->mGamepadState = 1;
            if(!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用
        }
        if (mCursorType == CursorType::PlantFromUsableCoin) {
            Board_RefreshSeedPacketFromCursor(board, 0);
            Board_ClearCursor(board, 0);
        }
        if (isCobCannonSelected) {//如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 0);
        if (requestDrawShovelInCursor) {
            requestDrawShovelInCursor = false;
        } else {
            requestDrawShovelInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Shovel);
        }
        return;
    }

    if (mObjectType == GameObjectType::Butter) {
        mPlayerIndexSecond = TouchPlayerIndex::Player2;//玩家2
        mTouchStateSecond = TouchState::ButterRect;
        if (mGameState == 7) {
            gamepadControls2->mGamepadState = 1;
            if(!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用
        }
        if (mCursorType_2P == CursorType::PlantFromUsableCoin) {
            Board_RefreshSeedPacketFromCursor(board, 1);
            Board_ClearCursor(board, 1);
        }
        if (isCobCannonSelected_2P) {//如果拿着加农炮，将其放下
            GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
        }
        Board_RefreshSeedPacketFromCursor(board, 1);
        if (requestDrawButterInCursor) {
            requestDrawButterInCursor = false;
        } else {
            requestDrawButterInCursor = true;
            LawnApp_PlayFoley(mApp, FoleyType::Floop);
        }
        return;
    }

    if (mGameMode == GameMode::TwoPlayerVS) {
        mPlayerIndexSecond = Board_PixelToGridX(board,x,y) > 5 ? TouchPlayerIndex::Player2:TouchPlayerIndex::Player1;
    }else if (mGameMode >= GameMode::TwoPlayerCoopDay &&mGameMode <= GameMode::TwoPlayerCoopEndless){
        mPlayerIndexSecond = x > 400?TouchPlayerIndex::Player2:TouchPlayerIndex::Player1;
    }else{
        mPlayerIndexSecond = TouchPlayerIndex::Player1;
    }

    if (mPlayerIndex != TouchPlayerIndex::None && mPlayerIndexSecond == mPlayerIndex) {
        if (mObjectType == GameObjectType::Plant) {
            Plant *plant = (Plant *) hitResult.mObject;
            bool isValidCobCannon = plant->mSeedType == SeedType::Cobcannon && plant->mState == PlantState::CobcannonReady;
            if (!isValidCobCannon) {
                mPlayerIndexSecond = TouchPlayerIndex::None;
                mTouchStateSecond = TouchState::None;
                return;
            }
        } else {
            mPlayerIndexSecond = TouchPlayerIndex::None;
            mTouchStateSecond = TouchState::None;
            return;
        }
    }



    if (mObjectType == GameObjectType::Coin) {
        Coin *coin = (Coin*)hitResult.mObject;

        if (coin->mType == CoinType::UsableSeedPacket) {
            mTouchStateSecond = TouchState::UsefulSeedPacket;
            requestDrawShovelInCursor = false;
//            if (mCursorType == CursorType::PlantFromUsableCoin) {
//                LOGD("5656565656");
//                GamepadControls_OnKeyDown(gamepadCon
//               trols1, 27, 1096);//放下手上的植物卡片
//                mSendKeyWhenTouchUp = false;
//            }
            Board_RefreshSeedPacketFromCursor(board, 0);
            old_Coin_GamepadCursorOver(coin, 0);//捡起植物卡片
            //            Coin_Collect((int) coin, 0);
        }
    }

    if (mGameMode == GameMode::ChallengeSlotMachine) {//拉老虎机用
        if (TRect_Contains(&slotMachineRect, x, y)) {
            GamepadControls_OnKeyDown(gamepadControls1, 50, 1112);
            return;
        }
    }

    if (mGameMode == GameMode::ChallengeHeavyWeapon) {//移动重型武器
        mTouchStateSecond = TouchState::HeavyWeapon;
        mHeavyWeaponX = *((float *) mChallenge + 67);
        return;
    }

    if (Challenge_MouseDown(mChallenge, x, y, 0, &hitResult, 0)) {
        if (LawnApp_IsScaryPotterLevel(mApp)) {
            requestDrawShovelInCursor = false;
        }
        if (mGameMode == GameMode::ChallengeBeghouledTwist) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
        if (!LawnApp_IsWhackAZombieLevel(mApp) || mGameState != 7)
            return;//这一行代码的意义：在锤僵尸关卡，手持植物时，允许拖动种植。
    }


    if (mObjectType == GameObjectType::WateringCan ||
        mObjectType == GameObjectType::Fertilizer || mObjectType == GameObjectType::BugSpray ||
        mObjectType == GameObjectType::Phonograph || mObjectType == GameObjectType::Chocolate ||
        mObjectType == GameObjectType::Glove || mObjectType == GameObjectType::MoneySign ||
        mObjectType == GameObjectType::Wheelbarrow || mObjectType == GameObjectType::TreeFood) {
        Board_PickUpTool(board, mObjectType, 0);
        return;
    }

    float tmpX1, tmpY1;
    tmpX1 = gamepadControls1->mCursorPositionX;
    tmpY1 = gamepadControls1->mCursorPositionY;

    if (mPlayerIndexSecond == TouchPlayerIndex::Player1){
        if (mGameMode == GameMode::ChallengeBeghouledTwist) {
            gamepadControls1->mCursorPositionX = x - 40;
            gamepadControls1->mCursorPositionY = y - 40;
        } else {
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }
    }else{
        if (mGameMode == GameMode::ChallengeBeghouledTwist) {
            gamepadControls2->mCursorPositionX = x - 40;
            gamepadControls2->mCursorPositionY = y - 40;
        } else {
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }


    int seekBankPosition = gamepadControls1->mSelectedSeedIndex;
    if (mPlayerIndexSecond == TouchPlayerIndex::Player1){
        if (mGameState == 7 || isCobCannonSelected || requestDrawShovelInCursor ||
            (mCursorType == CursorType::PlantFromUsableCoin &&
             mTouchStateSecond != TouchState::UsefulSeedPacket)) {
            mTouchStateSecond = TouchState::PickingSomething;
            mSendKeyWhenTouchUpSecond = true;
        }
    }else{
        if (mGameState_2P == 7 || isCobCannonSelected_2P || requestDrawButterInCursor ||
            (mCursorType_2P == CursorType::PlantFromUsableCoin &&
             mTouchStateSecond != TouchState::UsefulSeedPacket)) {
            mTouchStateSecond = TouchState::PickingSomething;
            mSendKeyWhenTouchUpSecond = true;
        }
    }



    if (mObjectType == GameObjectType::Plant) {
        if (mPlayerIndexSecond == TouchPlayerIndex::Player1 && requestDrawShovelInCursor) return;
        Plant *plant = (Plant*)hitResult.mObject;
        bool isValidCobCannon = plant->mSeedType == SeedType::Cobcannon && plant->mState == PlantState::CobcannonReady;
        if (isValidCobCannon) {
            if (mPlayerIndex == TouchPlayerIndex::Player1 && gamepadControls2->mPlayerIndex2 == -1) {
                gamepadControls2->mCursorPositionX = x;
                gamepadControls2->mCursorPositionY = y;
                gamepadControls1->mCursorPositionX = tmpX1;
                gamepadControls1->mCursorPositionY = tmpY1;
                if (gamepadControls1->mIsCobCannonSelected && gamepadControls1->mCobCannonPlantIndexInList == plant->mPlantIndexInList){
                    // 不能同时选同一个加农炮！
                    mTouchStateSecond = TouchState::None;
                    return;
                }
                gamepadControls2->mIsInShopSeedBank = true;
                gamepadControls2->mPlayerIndex2 = 1;
                mPlayerIndexSecond = TouchPlayerIndex::Player2;
                GamepadControls_pickUpCobCannon((int) gamepadControls2, (int) plant);
                mTouchStateSecond = TouchState::ValidCobCannonSecond;
                return;
            } else
            if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
                if (mGameState == 7) {
                    gamepadControls1->mGamepadState = 1;
                    mSendKeyWhenTouchUpSecond = false;
                    if(!isTwoSeedBankMode)
                        gamepadControls1->mIsInShopSeedBank = true;
                    int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
                    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                    seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用
                }
                GamepadControls_pickUpCobCannon((int) gamepadControls1, (int) plant);
            }else{
                if (mGameState_2P == 7) {
                    gamepadControls2->mGamepadState = 1;
                    mSendKeyWhenTouchUpSecond = false;
                    if(!isTwoSeedBankMode)
                        gamepadControls2->mIsInShopSeedBank = true;
                    int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
                    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                    seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用
                }
                GamepadControls_pickUpCobCannon((int) gamepadControls2, (int) plant);
            }
            mTouchStateSecond = TouchState::ValidCobCannon;
            return;
        }
    }

    if (mTouchStateSecond == TouchState::None)
        mTouchStateSecond = TouchState::Board;
}

void Board_MouseDragSecond(Board *board, int x, int y) {
    //Drag函数仅仅负责移动光标即可
    if (mTouchStateSecond == TouchState::None) return;

    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;
    GamepadControls* gamepadControls2 = board->mGamepadControls2;
    SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
    SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
    int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
    int mGameState_2P = gamepadControls2->mGamepadState;
    bool isCobCannonSelected_2P  = gamepadControls2->mIsCobCannonSelected;
    int mGameState = gamepadControls1->mGamepadState;
    LawnApp *mApp = board->mApp;
    GameMode::GameMode mGameMode = mApp->mGameMode;
    bool isTwoSeedBankMode = (mGameMode == GameMode::TwoPlayerVS || (mGameMode >= GameMode::TwoPlayerCoopDay && mGameMode <= GameMode::TwoPlayerCoopEndless));
    int seedBankHeight = LawnApp_IsChallengeWithoutSeedBank(mApp) ? 87 : seedBank->mY + seedBank->mHeight;
    if (mTouchStateSecond == TouchState::SeedBank && mTouchLastYSecond < seedBankHeight &&
        y >= seedBankHeight) {
        mTouchStateSecond = TouchState::BoardMovedFromSeedBank;
        if (mPlayerIndexSecond == TouchPlayerIndex::Player1){
            gamepadControls1->mGamepadState = 7;
            gamepadControls1->mIsInShopSeedBank = false;
            requestDrawShovelInCursor = false;
        }else{
            gamepadControls2->mGamepadState = 7;
            gamepadControls2->mIsInShopSeedBank = false;
            requestDrawButterInCursor = false;
        }
        mSendKeyWhenTouchUpSecond = true;
    }

    if (mTouchState == TouchState::ShovelRect) {
        if (mGameMode == GameMode::TwoPlayerVS) {
            if (TRect_Contains(&mTouchVSShovelRect, mTouchLastX, mTouchLastY) &&
                !TRect_Contains(&mTouchVSShovelRect, x, y)) {
                mTouchState = TouchState::BoardMovedFromShovelRect;
                if (!requestDrawShovelInCursor) LawnApp_PlayFoley(mApp, FoleyType::Shovel);
                requestDrawShovelInCursor = true;
                gamepadControls1->mGamepadState = 1;
                mSendKeyWhenTouchUp = true;
            }
        } else if (mTouchLastY < mTouchShovelRectWidth && y >= mTouchShovelRectWidth) {
            mTouchState = TouchState::BoardMovedFromShovelRect;
            if (!requestDrawShovelInCursor) LawnApp_PlayFoley(mApp, FoleyType::Shovel);
            requestDrawShovelInCursor = true;
            gamepadControls1->mGamepadState = 1;
            mSendKeyWhenTouchUp = true;
        }
    }

    if (mTouchStateSecond == TouchState::ButterRect && mTouchLastYSecond < mTouchButterRectWidth &&
        y >= mTouchButterRectWidth) {
        mTouchStateSecond = TouchState::BoardMovedFromButterRect;
        if (!requestDrawButterInCursor) LawnApp_PlayFoley(mApp, FoleyType::Floop);
        requestDrawButterInCursor = true;
        gamepadControls2->mGamepadState = 1;
        mSendKeyWhenTouchUpSecond = true;
    }

    if (mTouchStateSecond == TouchState::ValidCobCannon || mTouchStateSecond == TouchState::ValidCobCannonSecond || mTouchStateSecond == TouchState::UsefulSeedPacket) {
        if (!mSendKeyWhenTouchUpSecond &&
            (abs(x - mTouchDownXSecond) > mTouchTrigger || abs(y - mTouchDownYSecond) > mTouchTrigger)) {
            mSendKeyWhenTouchUpSecond = true;
        }
    }


    if (mPlayerIndexSecond == TouchPlayerIndex::Player1 && isCobCannonSelected && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);//退选加农炮
        mTouchStateSecond = TouchState::None;
        mSendKeyWhenTouchUpSecond = false;
    }
    if (mPlayerIndexSecond == TouchPlayerIndex::Player2 && isCobCannonSelected_2P && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
        GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);//退选加农炮
        if (mTouchStateSecond == TouchState::ValidCobCannonSecond) {
            LawnApp_ClearSecondPlayer(mApp);
            gamepadControls2->mPlayerIndex2 = -1;
        }
        mTouchStateSecond = TouchState::None;
        mSendKeyWhenTouchUpSecond = false;
    }

    if (mPlayerIndexSecond == TouchPlayerIndex::Player1){
        if (mGameState == 7 && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
            gamepadControls1->mGamepadState = 1;//退选植物
            if(!isTwoSeedBankMode)
                gamepadControls1->mIsInShopSeedBank = true;
            int newSeedPacketIndex = gamepadControls1->mSelectedSeedIndex;
            SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
            seedBank->mSeedPackets[newSeedPacketIndex].mLastSelectedTime = 0.0f;//动画效果专用
            mTouchStateSecond = TouchState::None;
            mSendKeyWhenTouchUpSecond = false;
        }
    }else{
        if (mGameState_2P == 7 && mTouchLastYSecond > seedBankHeight && y <= seedBankHeight) {
            gamepadControls2->mGamepadState = 1;//退选植物
            if(!isTwoSeedBankMode)
                gamepadControls2->mIsInShopSeedBank = true;
            int newSeedPacketIndex_2P = gamepadControls2->mSelectedSeedIndex;
            SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
            seedBank_2P->mSeedPackets[newSeedPacketIndex_2P].mLastSelectedTime = 0.0f;//动画效果专用
            mTouchStateSecond = TouchState::None;
            mSendKeyWhenTouchUpSecond = false;
        }
    }


    if (mGameMode == GameMode::ChallengeHeavyWeapon && mTouchStateSecond == TouchState::HeavyWeapon) {
        Challenge *mChallenge = board->mChallenge;
        mChallenge->mHeavyWeaponX = mHeavyWeaponX + x - mTouchDownXSecond;//移动重型武器X坐标
        return;
    }

    if (mGameMode == GameMode::ChallengeBeghouledTwist) {
        return;
    }

    if (mTouchStateSecond != TouchState::SeedBank) {
        if (x > 770) x = 770;
        if (x < 40) x = 40;
        if (y > 580) y = 580;
        if (mPlayerIndexSecond == TouchPlayerIndex::Player1){
            gamepadControls1->mCursorPositionX = x;
            gamepadControls1->mCursorPositionY = y;
        }else{
            gamepadControls2->mCursorPositionX = x;
            gamepadControls2->mCursorPositionY = y;
        }
    }
    mTouchLastXSecond = x;
    mTouchLastYSecond = y;
}

void Board_MouseUpSecond(Board *board, int x, int y, int theClickCount) {
    if (mTouchStateSecond != TouchState::None && mSendKeyWhenTouchUpSecond) {
        GamepadControls* gamepadControls1 = board->mGamepadControls1;
        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
        int numSeedsInBank = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
        int currentSeedBankIndex = gamepadControls1->mSelectedSeedIndex;
        int mGameState = gamepadControls1->mGamepadState;
        bool isCobCannonSelected = gamepadControls1->mIsCobCannonSelected;

        GamepadControls* gamepadControls2 = board->mGamepadControls2;
        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
        int numSeedsInBank_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
        int currentSeedBankIndex_2P = gamepadControls2->mSelectedSeedIndex;
        int mGameState_2P = gamepadControls2->mGamepadState;
        bool isCobCannonSelected_2P  = gamepadControls2->mIsCobCannonSelected;

        LawnApp *mApp = board->mApp;
        GameMode::GameMode mGameMode = mApp->mGameMode;
        CursorObject* cursorObject = board->mCursorObject1;
        CursorType::CursorType mCursorType = cursorObject->mCursorType;
        CursorObject* cursorObject_2P = board->mCursorObject2;
        CursorType::CursorType mCursorType_2P = cursorObject_2P->mCursorType;
        Challenge *mChallenge = board->mChallenge;
        ChallengeState::ChallengeState mChallengeState = mChallenge->mChallengeState;
        GameScenes::GameScenes mGameScene = mApp->mGameScene;
        if (mPlayerIndexSecond == TouchPlayerIndex::Player1) {
            if (requestDrawShovelInCursor) {
                Board_ShovelDown(board);
            } else if (mGameState == 7 || isCobCannonSelected || mCursorType == CursorType::PlantFromUsableCoin) {

                if (mGameMode == GameMode::ChallengeBeghouled || mGameMode == GameMode::ChallengeBeghouledTwist) {
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls1, 27, 1096);
                } else if ((mGameMode == GameMode::ChallengeLastStand && mChallengeState == ChallengeState::Normal && mGameScene == GameScenes::Playing) || mGameMode == GameMode::TwoPlayerVS) {
                    GamepadControls_OnButtonDown(gamepadControls1, 6, 0, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls1, 13, 1096);
                }
                int mGameStateNew = gamepadControls1->mGamepadState;
                int numSeedsInBankNew = SeedBank_GetNumSeedsOnConveyorBelt(seedBank);
                int seedPacketIndexNew = gamepadControls1->mSelectedSeedIndex;
                gamepadControls1->mIsInShopSeedBank = mGameStateNew != 7;
                if (mGameState != mGameStateNew) {
                    if (!Board_HasConveyorBeltSeedBank(board, 0) || numSeedsInBank == numSeedsInBankNew) {//修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank = GamepadControls_GetSeedBank(gamepadControls1);
                        seedBank->mSeedPackets[seedPacketIndexNew].mLastSelectedTime = 0.0f;//动画效果专用
                    }
                }
            }
        } else {
            if (requestDrawButterInCursor) {
                requestDrawButterInCursor = false;
            } else if (mGameState_2P == 7 || isCobCannonSelected_2P || mCursorType_2P == CursorType::PlantFromUsableCoin) {
                if (mGameMode == GameMode::ChallengeBeghouled || mGameMode == GameMode::ChallengeBeghouledTwist) {
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                    GamepadControls_OnKeyDown(gamepadControls2, 27, 1096);
                } else if ((mGameMode == GameMode::ChallengeLastStand && mChallengeState == ChallengeState::Normal && mGameScene == GameScenes::Playing) || mGameMode == GameMode::TwoPlayerVS) {
                    GamepadControls_OnButtonDown(gamepadControls2, 6, 1, 0);
                } else {
                    GamepadControls_OnKeyDown(gamepadControls2, 13, 1096);
                }
                int mGameStateNew_2P = gamepadControls2->mGamepadState;
                int numSeedsInBankNew_2P = SeedBank_GetNumSeedsOnConveyorBelt(seedBank_2P);
                int seedPacketIndexNew_2P = gamepadControls2->mSelectedSeedIndex;
                gamepadControls2->mIsInShopSeedBank = mGameStateNew_2P!= 7;
                if (mGameState_2P != mGameStateNew_2P) {
                    if (!Board_HasConveyorBeltSeedBank(board, 1) || numSeedsInBank_2P == numSeedsInBankNew_2P) {//修复传送带关卡种植之后SeedBank动画不正常
                        SeedBank *seedBank_2P = GamepadControls_GetSeedBank(gamepadControls2);
                        seedBank_2P->mSeedPackets[seedPacketIndexNew_2P].mLastSelectedTime = 0.0f;//动画效果专用
                    }
                }
                if (mGameMode == GameMode::TwoPlayerVS) {
                    gamepadControls2->mGamepadState = 1;
                }
                if (mTouchStateSecond == TouchState::ValidCobCannonSecond) {
                    LawnApp_ClearSecondPlayer(mApp);
                    gamepadControls2->mPlayerIndex2 = -1;
                }
            }
        }
    }
    mPlayerIndexSecond = TouchPlayerIndex::None;
    mSendKeyWhenTouchUpSecond = false;
    mTouchStateSecond = TouchState::None;
}




void Board_Board(Board* board,LawnApp* mApp) {
    old_Board_Board(board,mApp);

    if (mBoardMenuButton != NULL) {
        GameButton_Delete(mBoardMenuButton);
    }
    if (mBoardStoreButton != NULL) {
        GameButton_Delete(mBoardStoreButton);
    }
    int holder[1];
    TodStringTranslate(holder, (mApp->mGameMode == GameMode::ChallengeZenGarden || mApp->mGameMode == GameMode::ChallengeTreeOfWisdom)? "[MAIN_MENU_BUTTON]" : "[MENU_BUTTON]");
    mBoardMenuButton = MakeButton(1000, &board->mButtonListener, board, holder);
    GameButton_Resize(mBoardMenuButton, 705, -3, 120, 80);
    mBoardMenuButton->mBtnNoDraw = true;
    mBoardMenuButton->mDisabled = true;
    if (LawnApp_IsCoopMode(mApp) || mApp->mGameMode == GameMode::TwoPlayerVS) {
        GameButton_Resize(mBoardMenuButton, 880, -3, 120, 80);
    }else if(mApp->mGameMode == GameMode::ChallengeZenGarden || mApp->mGameMode == GameMode::ChallengeTreeOfWisdom) {
        GameButton_Resize(mBoardMenuButton, 650, 550, 170, 120);
    }
    Sexy_String_Delete(holder);


    if (mApp->mGameMode == GameMode::ChallengeLastStand) {
        int holder1[1];
        TodStringTranslate(holder1, "[START_ONSLAUGHT]");
        mBoardStoreButton = MakeButton(1001, &board->mButtonListener, board, holder1);
        GameButton_Resize(mBoardStoreButton, 0, 0, 0, 0);
        mBoardStoreButton->mBtnNoDraw = true;
        mBoardStoreButton->mDisabled = true;
        Sexy_String_Delete(holder1);
    } else {
        int holder1[1];
        TodStringTranslate(holder1, "[SHOP_BUTTON]");
        mBoardStoreButton = MakeButton(1001, &board->mButtonListener, board, holder1);
        Sexy_String_Delete(holder1);
        if (mApp->mGameMode == GameMode::ChallengeZenGarden || mApp->mGameMode == GameMode::ChallengeTreeOfWisdom) {
            GameButton_Resize(mBoardStoreButton, 0, 550, 170, 120);
        } else{
            GameButton_Resize(mBoardStoreButton, 0, 0, 0, 0);
            mBoardStoreButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = true;
        }
    }

    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))board->vTable + 6))(board, mBoardMenuButton); // AddWidget()
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))board->vTable + 6))(board, mBoardStoreButton); // AddWidget()
    MessageWidget_Delete(board->mAdvice);
    CustomMessageWidget* theAdvice = (CustomMessageWidget *)operator new(820u);
    MessageWidget_MessageWidget(theAdvice,board->mApp);
    theAdvice->mIcon = NULL;
    board->mAdvice = theAdvice;
}
void (*old_Board_startLevel)(Board* board);

void Board_startLevel(Board *board) {
    old_Board_startLevel(board);
}


void Board_InitLevel(Board *board) {
    old_Board_InitLevel(board);
    board->mNewWallNutAndSunFlowerAndChomperOnly = !(LawnApp_IsScaryPotterLevel(board->mApp) || LawnApp_IsIZombieLevel(board->mApp) || LawnApp_IsWhackAZombieLevel(board->mApp) || Board_HasConveyorBeltSeedBank(board,0) || LawnApp_IsChallengeWithoutSeedBank(board->mApp));
    board->mNewPeaShooterCount = 0;
}

void Board_RemovedFromManager(Board *board, int *manager) {
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))board->vTable + 7))(board, mBoardMenuButton); // RemoveWidget()
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))board->vTable + 7))(board, mBoardStoreButton); // RemoveWidget()
    GameButton_Delete(mBoardMenuButton);
    GameButton_Delete(mBoardStoreButton);
    mBoardMenuButton = NULL;
    mBoardStoreButton = NULL;
    old_Board_RemovedFromManager(board, manager);
}

void (*old_Board_Delete2)(Board *board);

void Board_Delete2(Board *board){
    old_Board_Delete2(board);
}

void Board_UpdateButtons(Board* board){
    if (board->mApp->mGameMode == GameMode::TwoPlayerVS){
        mBoardMenuButton->mBtnNoDraw = false;
        mBoardMenuButton->mDisabled = false;
    }else {
        if (board->mApp->mGameScene == GameScenes::Playing) {
            mBoardMenuButton->mBtnNoDraw = false;
            mBoardMenuButton->mDisabled = false;
        } else {
            mBoardMenuButton->mBtnNoDraw = true;
            mBoardMenuButton->mDisabled = true;
        }
    }
    if (board->mBoardFadeOutCounter > 0) {
        mBoardMenuButton->mBtnNoDraw = true;
        mBoardMenuButton->mDisabled = true;
    }
}

void Board_ButtonDepress(Board *board, int id) {
    if (id == 1000) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        if (lawnApp->mGameMode == GameMode::ChallengeZenGarden || lawnApp->mGameMode == GameMode::ChallengeTreeOfWisdom){
            LawnApp_DoBackToMain(lawnApp);
            return;
        }
        LawnApp_PlaySample(lawnApp,*Sexy_SOUND_PAUSE_Addr);
        LawnApp_DoNewOptions(lawnApp, false, 0);
        return;
    }
    if (id = 1001) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        if (lawnApp->mGameMode == GameMode::ChallengeLastStand) {
            Board* mBoard = lawnApp->mBoard;
            mBoard->mChallenge->mChallengeState = ChallengeState::LastStandOnslaught;
            mBoardStoreButton->mBtnNoDraw = true;
            mBoardStoreButton->mDisabled = true;
            GameButton_Resize(mBoardStoreButton, 0, 0, 0, 0);
            mBoard->mZombieCountDown = 9;
            mBoard->mZombieCountDownStart = mBoard->mZombieCountDown;
        }else if (lawnApp->mGameMode == GameMode::ChallengeZenGarden){
            ZenGarden_OpenStore(lawnApp->mZenGarden);
        }else if (lawnApp->mGameMode == GameMode::ChallengeTreeOfWisdom){
            Challenge_TreeOfWisdomOpenStore(lawnApp->mBoard->mChallenge);
        }
    }
    old_Board_ButtonDepress(board, id);
}

Sexy::Image* GetIconByAchievementId(AchievementId::AchievementId theAchievementId){
    switch (theAchievementId) {
        case AchievementId::ACHIEVEMENT_HOME_SECURITY:
            return Addon_Images.achievement_homeLawnsecurity;
        case AchievementId::ACHIEVEMENT_MORTICULTURALIST:
            return Addon_Images.achievement_morticulturalist;
        case AchievementId::ACHIEVEMENT_IMMORTAL:
            return Addon_Images.achievement_immortal;
        case AchievementId::ACHIEVEMENT_SOILPLANTS:
            return Addon_Images.achievement_soilplants;
        case AchievementId::ACHIEVEMENT_CLOSESHAVE:
            return Addon_Images.achievement_closeshave;
        case AchievementId::ACHIEVEMENT_CHOMP:
            return Addon_Images.achievement_chomp;
        case AchievementId::ACHIEVEMENT_VERSUS:
            return Addon_Images.achievement_versusz;
        case AchievementId::ACHIEVEMENT_GARG:
            return Addon_Images.achievement_garg;
        case AchievementId::ACHIEVEMENT_COOP:
            return Addon_Images.achievement_coop;
        case AchievementId::ACHIEVEMENT_SHOP:
            return Addon_Images.achievement_shop;
        case AchievementId::ACHIEVEMENT_EXPLODONATOR:
            return Addon_Images.achievement_explodonator;
        case AchievementId::ACHIEVEMENT_TREE:
            return Addon_Images.achievement_tree;
    }
    return NULL;
}

char* GetNameByAchievementId(AchievementId::AchievementId theAchievementId){
    switch (theAchievementId) {
        case AchievementId::ACHIEVEMENT_HOME_SECURITY:
            return "ACHIEVEMENT_HOME_SECURITY";
        case AchievementId::ACHIEVEMENT_MORTICULTURALIST:
            return "ACHIEVEMENT_MORTICULTURALIST";
        case AchievementId::ACHIEVEMENT_IMMORTAL:
            return "ACHIEVEMENT_IMMORTAL";
        case AchievementId::ACHIEVEMENT_SOILPLANTS:
            return "ACHIEVEMENT_SOILPLANTS";
        case AchievementId::ACHIEVEMENT_CLOSESHAVE:
            return "ACHIEVEMENT_CLOSESHAVE";
        case AchievementId::ACHIEVEMENT_CHOMP:
            return "ACHIEVEMENT_CHOMP";
        case AchievementId::ACHIEVEMENT_VERSUS:
            return "ACHIEVEMENT_VERSUS";
        case AchievementId::ACHIEVEMENT_GARG:
            return "ACHIEVEMENT_GARG";
        case AchievementId::ACHIEVEMENT_COOP:
            return "ACHIEVEMENT_COOP";
        case AchievementId::ACHIEVEMENT_SHOP:
            return "ACHIEVEMENT_SHOP";
        case AchievementId::ACHIEVEMENT_EXPLODONATOR:
            return "ACHIEVEMENT_EXPLODONATOR";
        case AchievementId::ACHIEVEMENT_TREE:
            return "ACHIEVEMENT_TREE";
    }
    return "";
}

bool Board_GrantAchievement(Board *board, AchievementId::AchievementId theAchievementId, bool show) {
    LawnApp *lawnApp = board->mApp;
    PlayerInfo *playerInfo = lawnApp->mPlayerInfo;
    if (!playerInfo->mAchievements[theAchievementId]) {
        LawnApp_PlaySample(lawnApp, Addon_Sounds.achievement);
        Board_ClearAdviceImmediately(board);
        char *theAchievementName = GetNameByAchievementId(theAchievementId);
        int holder[1];
        int holder1[1];
        int holder2[1];
        TodStringTranslate(holder, "[ACHIEVEMENT_GRANTED]");
        Sexy_StrFormat(holder1, "[%s]", theAchievementName);
        TodReplaceString(holder2, holder, "{achievement}", holder1);
        Board_DisplayAdviceAgain(board, holder2, MessageStyle::Achievement,AdviceType::AchievementEarned);
        ((CustomMessageWidget *) board->mAdvice)->mIcon = GetIconByAchievementId(theAchievementId);
        Sexy_String_Delete(holder);
        Sexy_String_Delete(holder1);
        Sexy_String_Delete(holder2);
        playerInfo->mAchievements[theAchievementId] = true;
        return true;
    }
    return false;
}

void Board_FadeOutLevel(Board *board) {
    old_Board_FadeOutLevel(board);

    if (LawnApp_IsSurvivalMode(board->mApp) && board->mChallenge->mSurvivalStage >= 19) {
        Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_IMMORTAL, true);
    }

    if (!LawnApp_IsSurvivalMode(board->mApp)) {
        int theNumLawnMowers = 0;
        for (int i = 0; i < 6; ++i) {
            if (board->mPlantRow[i] != PlantRowType::Dirt) {
                theNumLawnMowers++;
            }
        }
        if (board->mTriggeredLawnMowers == theNumLawnMowers) {
            Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_CLOSESHAVE, true);
        }
    }
    if (board->mLevel == 50) {
        Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_HOME_SECURITY, true);
    }

    if (board->mApp->mGameMode == GameMode::TwoPlayerCoopBowling) {
        Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_COOP, true);
    }

    if (board->mApp->mGameMode == GameMode::TwoPlayerVS) {
        if ((VSResultsMenu_msPlayerRecords_Addr[3] == 4 && board->mApp->mBoardResult == BoardResult::VSPlantWon) ||( VSResultsMenu_msPlayerRecords_Addr[8] == 4 && board->mApp->mBoardResult == BoardResult::VSZombieWon)){
            Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_VERSUS, true);
        }
    }

    if (board->mNewWallNutAndSunFlowerAndChomperOnly && !LawnApp_IsSurvivalMode(board->mApp) && !Board_HasConveyorBeltSeedBank(board,0)) {
        int num = board->mSeedBank1->mNumPackets;
        for (int i = 0; i < num; ++i) {
            SeedType::SeedType theType = board->mSeedBank1->mSeedPackets[i].mPacketType;
            if  (theType==SeedType::Chomper || theType == SeedType::Wallnut || theType == SeedType::Sunflower){
                Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_CHOMP, true);
                break;
            }
        }

    }
}

void Board_DoPlantingAchievementCheck(Board* board, SeedType::SeedType theType) {
    if (theType != SeedType::Chomper && theType != SeedType::Sunflower && theType != SeedType::Wallnut) {
        board->mNewWallNutAndSunFlowerAndChomperOnly = false;
    }
    if (theType == SeedType::Peashooter && !Board_HasConveyorBeltSeedBank(board,0)) {
        board->mNewPeaShooterCount++;
        if (board->mNewPeaShooterCount >= 10) {
            Board_GrantAchievement(board, AchievementId::ACHIEVEMENT_SOILPLANTS, true);
        }
    }
}


void Board_FixReanimErrorAfterLoad(Board *board) {
    // 修复读档后的各种问题
    Zombie *zombie = NULL;
    while (Board_IterateZombies(board, &zombie)) {
        ZombieType::ZombieType zombieType = zombie->mZombieType;
        Reanimation *mBodyReanim = LawnApp_ReanimationGet(board->mApp, zombie->mBodyReanimID);
        if (mBodyReanim == NULL) return;

        if (!zombie->mHasArm) {
            Zombie_SetupLostArmReanim(zombie);
        }
        // 修复读档后豌豆、机枪、倭瓜僵尸头部变为普通僵尸
        if (zombieType == ZombieType::PeaHead || zombieType == ZombieType::GatlingHead || zombieType == ZombieType::SquashHead) {
            Reanimation_SetImageOverride(mBodyReanim, "anim_head1", *Sexy_IMAGE_BLANK_Addr);
        }

        // 修复读档后盾牌贴图变为满血盾牌贴图、垃圾桶变为铁门
        if (zombie->mShieldType != ShieldType::None) {
            int shieldDamageIndex = Zombie_GetShieldDamageIndex(zombie);
            switch (zombie->mShieldType) {
                case ShieldType::Door:
                    switch (shieldDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_SCREENDOOR2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_SCREENDOOR3_Addr);
                            break;
                    }
                    break;
                case ShieldType::Newspaper:
                    switch (shieldDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_paper_paper", *Sexy_IMAGE_REANIM_ZOMBIE_PAPER_PAPER2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_paper_paper", *Sexy_IMAGE_REANIM_ZOMBIE_PAPER_PAPER3_Addr);
                            break;
                    }
                    break;
                case ShieldType::Ladder:
                    switch (shieldDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_ladder_1", *Sexy_IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_ladder_1", *Sexy_IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2_Addr);
                            break;
                    }
                    break;
                case ShieldType::TrashBin:
                    switch (shieldDamageIndex) {
                        case 0:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_TRASHCAN1_Addr);
                            break;
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_TRASHCAN2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_screendoor", *Sexy_IMAGE_REANIM_ZOMBIE_TRASHCAN3_Addr);
                            break;
                    }
                    break;
            }
        }


        // 修复读档后头盔贴图变为满血头盔贴图
        if (zombie->mHelmType != HelmType::None) {
            int helmDamageIndex = Zombie_GetHelmDamageIndex(zombie);
            switch (zombie->mHelmType) {
                case HelmType::TrafficCone:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_cone",*Sexy_IMAGE_REANIM_ZOMBIE_CONE2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_cone",*Sexy_IMAGE_REANIM_ZOMBIE_CONE3_Addr);
                            break;
                    }
                    break;
                case HelmType::Pail:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_bucket",*Sexy_IMAGE_REANIM_ZOMBIE_BUCKET2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "anim_bucket",*Sexy_IMAGE_REANIM_ZOMBIE_BUCKET3_Addr);
                            break;
                    }
                    break;
                case HelmType::Football:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "zombie_football_helmet",*Sexy_IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "zombie_football_helmet",*Sexy_IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3_Addr);
                            break;
                    }
                    break;
                case HelmType::Digger:
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_digger_hardhat",*Sexy_IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mBodyReanim, "Zombie_digger_hardhat",*Sexy_IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3_Addr);
                            break;
                    }
                    break;
                case HelmType::Wallnut:
                {
                    Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(board->mApp,zombie->mSpecialHeadReanimID);
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face",*Sexy_IMAGE_REANIM_WALLNUT_CRACKED1_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face",*Sexy_IMAGE_REANIM_WALLNUT_CRACKED2_Addr);
                            break;
                    }
                }
                    break;
                case HelmType::Tallnut:
                {
                    Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(board->mApp,zombie->mSpecialHeadReanimID);
                    switch (helmDamageIndex) {
                        case 1:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face",*Sexy_IMAGE_REANIM_TALLNUT_CRACKED1_Addr);
                            break;
                        case 2:
                            Reanimation_SetImageOverride(mSpecialHeadReanim, "anim_face",*Sexy_IMAGE_REANIM_TALLNUT_CRACKED2_Addr);
                            break;
                    }
                }
                    break;
            }
        }

        // 修复读档后巨人僵尸创可贴消失、红眼巨人变白眼巨人
        if (zombieType == ZombieType::Gargantuar || zombieType == ZombieType::RedeyeGargantuar) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 0:
                    if (zombieType == ZombieType::RedeyeGargantuar) Reanimation_SetImageOverride(mBodyReanim, "anim_head1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_Addr);
                    break;
                case 1:
                    if (zombieType == ZombieType::RedeyeGargantuar) Reanimation_SetImageOverride(mBodyReanim, "anim_head1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantua_body1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantuar_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2_Addr);
                    break;
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantua_body1", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_gargantuar_outerleg_foot", *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim,"Zombie_gargantuar_outerarm_lower",*Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "anim_head1", zombieType == ZombieType::RedeyeGargantuar ? *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE_Addr : *Sexy_IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_Addr);
            }
        }

        // 修复读档后僵尸博士机甲变全新机甲
        if (zombieType == ZombieType::Boss) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 1:
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_head", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_jaw", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_hand", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_thumb2", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_innerleg_foot", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1_Addr);
                    break;
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_head", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_jaw", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_hand", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerarm_thumb2", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Boss_outerleg_foot", *Sexy_IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2_Addr);
                    break;
            }
        }

        // 修复读档后冰车变全新冰车
        if (zombieType == ZombieType::Zamboni) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 1:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_1", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_2", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1_Addr);
                    break;
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_1", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2_Addr);
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_zamboni_2", *Sexy_IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2_Addr);
                    break;
            }
        }

        // 修复读档后投篮车变全新投篮车
        if (zombieType == ZombieType::Catapult) {
            int bodyDamageIndex = Zombie_GetBodyDamageIndex(zombie);
            switch (bodyDamageIndex) {
                case 1:
                case 2:
                    Reanimation_SetImageOverride(mBodyReanim, "Zombie_catapult_siding", *Sexy_IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE_Addr);
                    break;
            }
        }

    }


    // 修复读档后雏菊、糖果变色、泳池闪光消失
    TodParticleSystem *particle = NULL;
    Color white = {255, 255, 255, 255};
    while (Board_IterateParticles(board, &particle)) {
        if (particle->mEffectType == ParticleEffect::Daisy || particle->mEffectType == ParticleEffect::Pinata || particle->mEffectType == ParticleEffect::PoolSparkly) {
            TodParticleSystem_OverrideColor(particle, NULL, &white);
        }
    }

    if (board->mBackgroundType == BackgroundType::Num3Pool && (board->mPoolSparklyParticleID == 0 || LawnApp_ParticleTryToGet(board->mApp,board->mPoolSparklyParticleID) == NULL)) {
        TodParticleSystem *poolSparklyParticle = LawnApp_AddTodParticle(board->mApp, 450.0, 295.0,220000,ParticleEffect::PoolSparkly);
        board->mPoolSparklyParticleID = LawnApp_ParticleGetID(board->mApp, poolSparklyParticle);
    }
}

void (*old_FixBoardAfterLoad)(Board *board);

void FixBoardAfterLoad(Board *board) {
    // 修复读档后的各种问题
    old_FixBoardAfterLoad(board);
    Board_FixReanimErrorAfterLoad(board);
}

void (*old_SyncReanimation)(Board *a1, Reanimation *a2, int *theSaveGameContext);

void SyncReanimation(Board *a1, Reanimation *a2, int *theSaveGameContext) {
//    if (a2->mReanimationType == ReanimationType::ZombatarHead) return;
    return old_SyncReanimation(a1, a2, theSaveGameContext);
}

int (*old_LawnSaveGame)(Board *a1, int* a2);

int LawnSaveGame(Board *board, int* a2) {
//    Zombie *zombie = NULL;
//    while (Board_IterateZombies(board, &zombie)) {
//        if (zombie->mZombieType == ZombieType::Flag) {
//            LawnApp_RemoveReanimation(zombie->mApp, zombie->mBossFireBallReanimID);
//            zombie->mBossFireBallReanimID = 0;
//        }
//    }
   return old_LawnSaveGame(board,a2);
}

void (*old_Board_DrawUITop)(Board *board, Sexy::Graphics *graphics);

void Board_DrawUITop(Board *board, Sexy::Graphics *graphics) {
    if (seedBankPin && !LawnApp_IsSlotMachineLevel(board->mApp)) {
        if (board->mApp->mGameScene != GameScenes::Leaderboard &&
            board->mApp->mGameScene != GameScenes::ZombiesWon) {
            if (SeedBank_BeginDraw(board->mSeedBank1, graphics)) {
                SeedBank_Draw(board->mSeedBank1, graphics);
                SeedBank_EndDraw(board->mSeedBank1, graphics);
            }

            if (board->mSeedBank2 != NULL) {
                if (SeedBank_BeginDraw(board->mSeedBank2, graphics)) {
                    SeedBank_Draw(board->mSeedBank2, graphics);
                    SeedBank_EndDraw(board->mSeedBank2, graphics);
                }
            }
        }
    }
    old_Board_DrawUITop(board,graphics);
}

void (*old_Board_GetShovelButtonRect)(TRect* rect,Board* board);

void Board_GetShovelButtonRect(TRect *rect, Board *board) {
    old_Board_GetShovelButtonRect(rect, board);
}

void (*old_Board_DisplayAdvice)(Board* board,int* text,MessageStyle::MessageStyle theStyle,AdviceType::AdviceType theType);

void Board_DisplayAdvice(Board* board,int* text,MessageStyle::MessageStyle theStyle,AdviceType::AdviceType theType){
    old_Board_DisplayAdvice(board,text,theStyle,theType);
}

void Board_DrawBackdrop(Board *board, Sexy::Graphics *graphics) {
    //实现泳池动态效果、实现对战结盟分界线
    old_Board_DrawBackdrop(board, graphics);
    BackgroundType::BackgroundType mBackground = board->mBackgroundType;

    if (mBackground == BackgroundType::Num3Pool || mBackground == BackgroundType::Num4Fog) {
        PoolEffect_PoolEffectDraw(board->mApp->mPoolEffect, graphics, Board_StageIsNight(board));
    }

    LawnApp *lawnApp = board->mApp;
    BackgroundType::BackgroundType mBackgroundType = board->mBackgroundType;
    GameMode::GameMode mGameMode = lawnApp->mGameMode;
    if (mGameMode == GameMode::TwoPlayerVS) {
        switch (mBackgroundType) {
            case BackgroundType::Num1Day:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::Num2Night:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::Num3Pool:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::Num4Fog:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::Num5Roof:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            case BackgroundType::Num6Boss:
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_WALLNUT_BOWLINGSTRIPE_Addr, 512, 73);
                break;
            default:
                break;
        }
        return;
    }
    if (mGameMode >= GameMode::TwoPlayerCoopDay && mGameMode <= GameMode::TwoPlayerCoopEndless && mGameMode != GameMode::TwoPlayerCoopBowling) {
        switch (mBackgroundType) {
            case BackgroundType::Num1Day:
                Sexy_Graphics_DrawImage(graphics, Addon_Images.stripe_day_coop, 384, 69);
                break;
            case BackgroundType::Num2Night:
                Sexy_Graphics_DrawImage(graphics, Addon_Images.stripe_day_coop, 384, 69);
                break;
            case BackgroundType::Num3Pool:
                Sexy_Graphics_DrawImage(graphics, Addon_Images.stripe_pool_coop, 348, 72);
                break;
            case BackgroundType::Num4Fog:
                Sexy_Graphics_DrawImage(graphics, Addon_Images.stripe_pool_coop, 348, 72);
                break;
            case BackgroundType::Num5Roof:
                Sexy_Graphics_DrawImage(graphics, Addon_Images.stripe_roof_left, 365, 82);
                break;
            case BackgroundType::Num6Boss:
                Sexy_Graphics_DrawImage(graphics, Addon_Images.stripe_roof_left, 365, 82);
                break;
            default:
                break;
        }
    }
}

bool (*old_Board_RowCanHaveZombieType)(Board *board,int theRow, ZombieType::ZombieType theZombieType);

bool Board_RowCanHaveZombieType(Board *board,int theRow, ZombieType::ZombieType theZombieType) {
    if (board->mApp->mGameMode == GameMode::ChallengePoolParty) {
        return ZombieTypeCanGoInPool(theZombieType);
    }
    return old_Board_RowCanHaveZombieType(board,theRow,theZombieType);
}

//int (*old_Board_GetNumSeedsInBank)(Board *board, bool theIsZombie);
//
//int Board_GetNumSeedsInBank(Board *board, bool theIsZombie) {
//    if (board->mApp->mGameMode == GameMode::TwoPlayerVS) {
//        return 7;
//    }
//    return old_Board_GetNumSeedsInBank(board, theIsZombie);
//}
//
//int (*old_Board_GetSeedBankExtraWidth)(Board *board);
//
//int Board_GetSeedBankExtraWidth(Board *board) {
//    if (board->mApp->mGameMode == GameMode::TwoPlayerVS && Board_GetNumSeedsInBank(board,false) == 7) {
//        return 0;
//    }
//    return old_Board_GetSeedBankExtraWidth(board);
//}
//
//int (*old_Board_GetSeedPacketPositionX)(Board*,int,int,bool);
//
//int Board_GetSeedPacketPositionX(Board*board, int packetIndex, int seedBankIndex, bool playerIndex) {
//    if (board->mApp->mGameMode == GameMode::TwoPlayerVS && Board_GetNumSeedsInBank(board,false) == 7) {
//        return 50 * packetIndex + 81 - 70 * playerIndex;
//    }
//    return old_Board_GetSeedPacketPositionX(board, packetIndex, seedBankIndex, playerIndex);
//}
#endif //PVZ_TV_1_1_1_BOARDTOUCH_H
