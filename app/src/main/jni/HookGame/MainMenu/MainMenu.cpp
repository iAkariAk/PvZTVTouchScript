//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_MAINMENU_CPP
#define PVZ_TV_1_1_5_MAINMENU_CPP


#include <cstddef>
#include "../GlobalVariable.h"
#include "MainMenu.h"
#include "HookGame/Graphics/Graphics.h"
#include "HookGame/Reanimation/Reanimation.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Board/Board.h"

bool isPatched = false;

int mMainMenuAchievementCounter = 0;

int mMainMenuAchievementsWidgetY = 0;

int mMainMenuAchievementsKeyboardScrollWidgetY = 0;
int mMainMenuAchievementKeyboardScrollCounter = 0;
bool mMainMenuAchievementKeyboardScrollDirection = false;

inline int mAchievementHoleLength = 136;
inline int mAchievementHoleWormPos = 0x10;
inline int mAchievementHoleGemsPos = 0x19;
inline int mAchievementHoleChuzzlePos = 0x26;
inline int mAchievementHoleBjornPos = 0x34;
inline int mAchievementHolePipePos = 0x45;
inline int mAchievementHoleTikiPos = 0x55;
inline int mAchievementHoleHeavyRocksPos = 0x65;
inline int mAchievementHoleDuWeiPos = 0x72;


inline int mKeyboardScrollTime = 20;

enum AchievementWidgetState {
    NOT_SHOWING = 0,
    SLIDING_IN = 1,
    SHOWING = 2,
    SLIDING_OUT = 3
};


inline int mMainMenuHeight = 720 - 2; // 作用：将成就界面上升2个像素点，以更紧密地贴合主界面。奇怪，理论上720是严丝合缝，为什么实际有2像素偏差呢？

AchievementWidgetState mAchievementState = NOT_SHOWING;

AchievementsWidget* mMainMenuAchievementsWidget = NULL;

Sexy::GameButton* mMainMenuAchievementsBack = NULL;

int mFoleyVolumeCounter = 0;

static FoleyType::FoleyType MainMenu_GetFoleyTypeByScene(int scene) {
    FoleyType::FoleyType theType = FoleyType::MenuCenter;
    switch (scene) {
        case 0:
            theType = FoleyType::MenuLeft;
            break;
        case 1:
            theType = FoleyType::MenuCenter;
            break;
        case 2:
            theType = FoleyType::MenuRight;
    }
    return theType;
}

void (*old_MainMenu_Update)(MainMenu *instance);

void MainMenu_Update(MainMenu *mainMenu) {
    //成就界面处理
    isMainMenu = true;
    requestDrawShovelInCursor = false;
    requestDrawButterInCursor = false;


    if (!isPatched) {
        GamePatches.UsefulSeedPacketAutoPickupDisable.Modify();
        isPatched = true;
    }


    // 白噪音播放和淡入淡出
    LawnApp *lawnApp = mainMenu->mApp;
    if (!mainMenu->mIsFading) {
        if (MainMenu_InTransition(mainMenu)) {
            mFoleyVolumeCounter++;
            FoleyType::FoleyType theType = MainMenu_GetFoleyTypeByScene(mainMenu->mScene);
            FoleyType::FoleyType theNextType = MainMenu_GetFoleyTypeByScene(mainMenu->mSceneNext);
            if (!TodFoley_IsFoleyPlaying(lawnApp->mSoundSystem, theNextType)) {
                LawnApp_PlayFoley(lawnApp, theNextType);
                LawnApp_SetFoleyVolume(lawnApp,theNextType,0);
            }
            float theVolume = TodAnimateCurveFloat(0,93,mFoleyVolumeCounter,lawnApp->mPlayerInfo->mSoundVolume,0,TodCurves::BounceSlowMiddle);
            if (mFoleyVolumeCounter >= 46) {
                LawnApp_SetFoleyVolume(lawnApp, theNextType, theVolume);
                if (TodFoley_IsFoleyPlaying(lawnApp->mSoundSystem, theType)) {
                    TodFoley_StopFoley(lawnApp->mSoundSystem, theType);
                }
            } else {
                LawnApp_SetFoleyVolume(lawnApp, theType, theVolume);
            }
        } else {
            mFoleyVolumeCounter = 0;
            FoleyType::FoleyType theType = MainMenu_GetFoleyTypeByScene(mainMenu->mScene);
            if (mAchievementState == NOT_SHOWING) {
                if (!TodFoley_IsFoleyPlaying(lawnApp->mSoundSystem, theType) && mainMenu->mExitCounter == 0) {
                    LawnApp_PlayFoley(lawnApp, theType);
                    LawnApp_SetFoleyVolume(lawnApp, theType, 0);
                }
                if (mainMenu->mEnterReanimationCounter > 0) {
                    float theVolume = TodAnimateCurveFloat(110, 0, mainMenu->mEnterReanimationCounter, 0,lawnApp->mPlayerInfo->mSoundVolume,TodCurves::Linear);
                    LawnApp_SetFoleyVolume(lawnApp, theType, theVolume);
                }
            }
            if (mAchievementState == SLIDING_IN) {
                float theVolume = TodAnimateCurveFloat(100, 0, mMainMenuAchievementCounter, lawnApp->mPlayerInfo->mSoundVolume,0,TodCurves::Linear);
                LawnApp_SetFoleyVolume(lawnApp, theType, theVolume);
            }
            if (mAchievementState == SLIDING_OUT && mMainMenuAchievementCounter <= 100) {
                float theVolume = TodAnimateCurveFloat(100, 0, mMainMenuAchievementCounter, 0, lawnApp->mPlayerInfo->mSoundVolume,TodCurves::Linear);
                LawnApp_SetFoleyVolume(lawnApp, theType, theVolume);
            }
        }
    }


    if (mMainMenuAchievementKeyboardScrollCounter != 0) {
        mMainMenuAchievementKeyboardScrollCounter--;
        if (mMainMenuAchievementsWidget != NULL) {
            int theY = TodAnimateCurve(mKeyboardScrollTime, 0, mMainMenuAchievementKeyboardScrollCounter, 0, 192, TodCurves::Linear);
            int theNewY = mMainMenuAchievementsKeyboardScrollWidgetY -(mMainMenuAchievementKeyboardScrollDirection ? theY : -theY);
            if (theNewY > mMainMenuHeight) theNewY = mMainMenuHeight;
            if (theNewY < 720 + mMainMenuHeight - (mAchievementHoleLength + 1) * Addon_Images.hole->mHeight) theNewY = 720 + mMainMenuHeight - (mAchievementHoleLength + 1) * Addon_Images.hole->mHeight;
            Sexy_Widget_Move(mMainMenuAchievementsWidget, mMainMenuAchievementsWidget->mX, theNewY);
        }
    }

    if (mAchievementState == SLIDING_IN) {
        mMainMenuAchievementCounter--;
        if (mMainMenuAchievementsWidget != NULL) {
            int theY = TodAnimateCurve(100, 0, mMainMenuAchievementCounter, 660, -60, TodCurves::EaseInOut);
            Sexy_Widget_Move(mainMenu, mainMenu->mX, - 720 + theY);
        }
        if (mMainMenuAchievementCounter == 0) {
            mAchievementState = SHOWING;
            int holder1[1];
            TodStringTranslate(holder1, "[CLOSE]");
            mMainMenuAchievementsBack = MakeButton(ACHIEVEMENTS_BACK_BUTTON, &mainMenu->mButtonListener, mainMenu, holder1);
            GameButton_Resize(mMainMenuAchievementsBack, 1000, 564 + 720, 170, 50);
            Sexy_String_Delete(holder1);
            (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mainMenu->vTable + 6))(mainMenu, mMainMenuAchievementsBack); // AddWidget()
        }
    }

    if (mAchievementState == SLIDING_OUT) {
        mMainMenuAchievementCounter--;
        if (mMainMenuAchievementsWidget != NULL) {
            if (mMainMenuAchievementCounter <= 100) {
                int theY = TodAnimateCurve(100, 0, mMainMenuAchievementCounter, -780, -60, TodCurves::EaseInOut);
                Sexy_Widget_Move(mainMenu, mainMenu->mX, theY);
            }
            else {
                int theAchievementsY = TodAnimateCurve(150, 100, mMainMenuAchievementCounter, mMainMenuAchievementsWidgetY, mMainMenuHeight, TodCurves::EaseInOut);
                Sexy_Widget_Move(mMainMenuAchievementsWidget, mMainMenuAchievementsWidget->mX, theAchievementsY);
            }
        }
        if (mMainMenuAchievementCounter == 0) {
            mAchievementState = NOT_SHOWING;
            (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mainMenu->vTable + 7))(mainMenu, mMainMenuAchievementsWidget); // RemoveWidget()
            MaskHelpWidget_Delete(mMainMenuAchievementsWidget);
            mMainMenuAchievementsWidget = NULL;
            if (mMainMenuAchievementsBack != NULL) {
                (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mainMenu->vTable + 7))(mainMenu, mMainMenuAchievementsBack); // RemoveWidget()
                GameButton_Delete(mMainMenuAchievementsBack);
                mMainMenuAchievementsBack = NULL;
            }
            Sexy::Widget* achievementsButton = (*((Sexy::Widget* (__fastcall **)(Sexy::Widget *, MainMenuButtonId))mainMenu->vTable + 9))(mainMenu, ACHIEVEMENTS_BUTTON); // FindWidget(mainMenu,ACHIEVEMENTS_BUTTON)
            mainMenu->mFocusedChildWidget = achievementsButton;
            if (!mainMenu->mIsFading) LawnApp_PlayFoley(lawnApp, FoleyType::MenuCenter);
        }
    }
    if (mAchievementState == SHOWING) {
        return;
    }

    return old_MainMenu_Update(mainMenu);
}


void MainMenu_ButtonPress(MainMenu *mainMenu, MainMenuButtonId mSelectedButton) {
    //按下按钮的声音
    LawnApp* lawnApp = (LawnApp*)*gLawnApp_Addr;
    if (MainMenu_InTransition(lawnApp->mGameSelector)) return;
    switch (mSelectedButton) {
        case HOUSE_BUTTON:
        case ACHIEVEMENTS_BUTTON:
        case HELP_AND_OPTIONS_BUTTON:
        case UNLOCK_BUTTON:
        case RETURN_TO_ARCADE_BUTTON:
        case MORE_BUTTON:
        case BACK_POT_BUTTON:
        case STORE_BUTTON:
        case ZEN_BUTTON:
        case ALMANAC_BUTTON:
        case MAIL_BUTTON:
//            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_CERAMIC_Addr);
            LawnApp_PlayFoley(lawnApp, FoleyType::Ceramic);
            break;
        default:
            LawnApp_PlaySample(lawnApp, *Sexy_SOUND_GRAVEBUTTON_Addr);
            break;
    }
}

void (*old_MainMenu_ButtonDepress)(MainMenu *mainMenu, MainMenuButtonId a2);

void MainMenu_ButtonDepress(MainMenu *mainMenu, MainMenuButtonId mSelectedButton) {
    //为1.1.5解锁触控或确认键进入“更多游戏模式”
    if (MainMenu_InTransition(mainMenu)) return;
    if (mainMenu->mIsFading) return;
    if (mainMenu->mEnterReanimationCounter > 0) return;
    if  (mAchievementState == SLIDING_IN || mAchievementState == SLIDING_OUT) return; // 在进入、退出成就时不允许玩家操作
    if (mSelectedButton == MORE_WAYS_BUTTON) {
        //如果当前选中的按钮为"更多游戏方式"
        MainMenu_SetScene(mainMenu, 0);
        return;
    }

    //为1.1.1添加触控或确认进入对战结盟模式，并检测是否解锁对战结盟
    LawnApp *lawnApp = mainMenu->mApp;
    switch (mSelectedButton) {
        case ADVENTURE_BUTTON:
        case START_ADVENTURE_BUTTON:
            MainMenu_StartAdventureMode(mainMenu);
            if (LawnPlayerInfo_GetFlag(lawnApp->mPlayerInfo, 4096) &&
                lawnApp->mPlayerInfo->mLevel == 35) {
                mainMenu->mPressedButtonId = STORE_BUTTON;
                mainMenu->unkBool3 = true;
                (*(void (__fastcall **)(MainMenu *)) (*(_DWORD *) mainMenu + 496))(mainMenu);
            } else {
                mainMenu->mPressedButtonId = ADVENTURE_BUTTON;
                lawnApp->mGameMode = GameMode::Adventure;
                (*(void (__fastcall **)(MainMenu *)) (*(_DWORD *) mainMenu + 496))(mainMenu);
            }
            return;
        case VS_BUTTON://如果按下了对战按钮
            if (mainMenu->mVSModeLocked) {
                //如果没解锁结盟（冒险2-1解锁）
                LawnApp_LawnMessageBox(
                        lawnApp,
                        Dialogs::DIALOG_MESSAGE,
                        "[MODE_LOCKED]",
                        "[VS_LOCKED_MESSAGE]",
                        "[DIALOG_BUTTON_OK]",
                        "",
                        3);
                return;
            }
            mainMenu->mPressedButtonId = mSelectedButton;
            (*(int (__fastcall **)(MainMenu *)) (*(_DWORD *) mainMenu + 496))(mainMenu);
            return;
        case VS_COOP_BUTTON://如果按下了结盟按钮
            if (mainMenu->mCoopModeLocked) {
                //如果没解锁结盟（冒险2-1解锁）
                LawnApp_LawnMessageBox(
                        lawnApp,
                        Dialogs::DIALOG_MESSAGE,
                        "[MODE_LOCKED]",
                        "[COOP_LOCKED_MESSAGE]",
                        "[DIALOG_BUTTON_OK]",
                        "",
                        3);
                return;
            }
            mainMenu->mPressedButtonId = mSelectedButton;
            (*(void (__fastcall **)(MainMenu *)) (*(_DWORD *) mainMenu + 496))(mainMenu);
            return;
        case ACHIEVEMENTS_BUTTON:
        case ACHIEVEMENTS_BACK_BUTTON:
            if (mMainMenuAchievementsWidget == NULL) {
                mAchievementState = SLIDING_IN;
                mMainMenuAchievementCounter = 100;
                mMainMenuAchievementsWidget = (AchievementsWidget *) operator new(264u);
                MaskHelpWidget_MaskHelpWidget(mMainMenuAchievementsWidget, mainMenu->mApp);
                Sexy_Widget_Resize(mMainMenuAchievementsWidget, 0, mMainMenuHeight, 1280, Addon_Images.hole->mHeight * (mAchievementHoleLength + 1));
                mMainMenuAchievementsWidget->mWidgetId = ACHIEVEMENTS_BUTTON;
                (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))mainMenu->vTable + 6))(mainMenu, mMainMenuAchievementsWidget); // AddWidget()
            } else {
                mAchievementState = SLIDING_OUT;
                mMainMenuAchievementCounter = mMainMenuAchievementsWidget->mY == mMainMenuHeight? 100 : 150;
                mMainMenuAchievementsWidgetY = mMainMenuAchievementsWidget->mY;
            }
            return;
        case HOUSE_BUTTON:
            mainMenu->mPressedButtonId = mSelectedButton;
            (*(void (__fastcall **)(MainMenu *)) (*(_DWORD *) mainMenu + 496))(mainMenu);
            return;
        case UNLOCK_BUTTON:
            mainMenu->mPressedButtonId = mSelectedButton;
            (*(void (__fastcall **)(MainMenu *)) (*(_DWORD *) mainMenu + 496))(mainMenu);
            return;
        default:
            old_MainMenu_ButtonDepress(mainMenu, mSelectedButton);
            return;
    }
}

void (*old_MainMenu_KeyDown)(MainMenu *mainMenu, int keyCode);

void MainMenu_KeyDown(MainMenu *mainMenu, Sexy::KeyCode keyCode) {
    //为1.1.5解锁左方向键进入“更多游戏模式”
    if (MainMenu_InTransition(mainMenu)) return;
    if (mainMenu->mIsFading) return;
    if (mainMenu->mEnterReanimationCounter > 0) return;

    if (mMainMenuAchievementsWidget != NULL) {
        if (mAchievementState != SHOWING) return;
        if (keyCode == Sexy::Back || keyCode == Sexy::Back2) {
            MainMenu_ButtonDepress(mainMenu, ACHIEVEMENTS_BUTTON);
        } else if (keyCode == Sexy::Up || keyCode == Sexy::Down) {
            if (mMainMenuAchievementKeyboardScrollCounter != 0) {
                return;
//                int theNewY = mMainMenuAchievementsKeyboardScrollWidgetY -(mMainMenuAchievementKeyboardScrollDirection ? 192 : -192);
//                if (theNewY > mMainMenuHeight) theNewY = mMainMenuHeight;
//                if (theNewY < 720 +mMainMenuHeight - (mAchievementHoleLength + 1) * Addon_Images.hole->mHeight) theNewY =  720 +mMainMenuHeight - (mAchievementHoleLength + 1) * Addon_Images.hole->mHeight;
//                Sexy_Widget_Move(mMainMenuAchievementsWidget, mMainMenuAchievementsWidget->mX, theNewY);
            }
            mMainMenuAchievementKeyboardScrollCounter = mKeyboardScrollTime;
            mMainMenuAchievementsKeyboardScrollWidgetY = mMainMenuAchievementsWidget->mY;
            mMainMenuAchievementKeyboardScrollDirection = keyCode == Sexy::Down;
        }
        return;
    }

    MainMenuButtonId mSelectedButton = (MainMenuButtonId) mainMenu->mFocusedChildWidget->mWidgetId;
    if ((mSelectedButton == ADVENTURE_BUTTON || mSelectedButton == MORE_WAYS_BUTTON || mSelectedButton == START_ADVENTURE_BUTTON) && keyCode == Sexy::Left) {
        //如果当前选中的按钮为"冒险模式"或者为"更多游戏方式"，同时玩家又按下了左方向键
        MainMenu_SetScene(mainMenu, 0);
        return;
    }

    old_MainMenu_KeyDown(mainMenu, keyCode);
}

void MainMenu_UpdateHouseReanim(MainMenu *mainMenu) {

    Reanimation *mMainMenuReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp,mainMenu->mMainMenuReanimID);
    if (mMainMenuReanim == NULL) return;
    Reanimation_SetImageDefinition(mMainMenuReanim, "leaderboards", Addon_Images.leaderboards);
    if (!showHouse) return;
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood1", Addon_Images.hood1_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood2", Addon_Images.hood2_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood3", Addon_Images.hood3_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "Hood4", Addon_Images.hood4_house);
    Reanimation_SetImageOrigin(mMainMenuReanim, "ground color copy", Addon_Images.house_hill_house);
    Reanimation *houseReanimation = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mUnkReanimID2);
    if (houseReanimation == NULL) return;
    LawnApp_SetHouseReanim(mainMenu->mApp, houseReanimation);
}

void (*old_MainMenu_SyncProfile)(MainMenu *a, bool a2);

void MainMenu_SyncProfile(MainMenu *a, bool a2) {
//    LOGD("MainMenu_SyncProfile");
    old_MainMenu_SyncProfile(a, a2);
    LawnApp *lawnApp = a->mApp;
    lawnApp->mNewIs3DAccelerated = lawnApp->mPlayerInfo == NULL || !lawnApp->mPlayerInfo->mIs3DAcceleratedClosed;
}

inline int mZombatarButtonX = 2800;
inline int mZombatarButtonY = -20;

void MainMenu_EnableButtons(MainMenu *mainMenu) {
    Sexy::Widget* achievementsButton = (*((Sexy::Widget* (__fastcall **)(Sexy::Widget *, MainMenuButtonId))mainMenu->vTable + 9))(mainMenu, ACHIEVEMENTS_BUTTON); // FindWidget(mainMenu,ACHIEVEMENTS_BUTTON)
    GameButton_SetDisabled((Sexy::GameButton*)achievementsButton,false);
    Sexy::Widget* leaderboardsButton = (*((Sexy::Widget* (__fastcall **)(Sexy::Widget *, MainMenuButtonId))mainMenu->vTable + 9))(mainMenu, HOUSE_BUTTON); // FindWidget(mainMenu,ACHIEVEMENTS_BUTTON)
    Sexy_Widget_SetVisible(leaderboardsButton,true);
    Sexy::Widget* helpButton = (*((Sexy::Widget* (__fastcall **)(Sexy::Widget *, MainMenuButtonId))mainMenu->vTable + 9))(mainMenu, HELP_AND_OPTIONS_BUTTON); // FindWidget(mainMenu,ACHIEVEMENTS_BUTTON)
    Sexy::Widget* backButton = (*((Sexy::Widget* (__fastcall **)(Sexy::Widget *, MainMenuButtonId))mainMenu->vTable + 9))(mainMenu, RETURN_TO_ARCADE_BUTTON); // FindWidget(mainMenu,ACHIEVEMENTS_BUTTON)
    helpButton->mFocusLinks[3] = backButton;
    backButton->mFocusLinks[2] = helpButton;
    Sexy::Widget* zombatarButton = (*((Sexy::Widget* (__fastcall **)(Sexy::Widget *, MainMenuButtonId))mainMenu->vTable + 9))(mainMenu, UNLOCK_BUTTON); // FindWidget(mainMenu,ACHIEVEMENTS_BUTTON)
    GameButton_SetDisabled((Sexy::GameButton*) zombatarButton, false);
    ((Sexy::GameButton*)zombatarButton)->mButtonImage = Addon_Images.SelectorScreen_WoodSign3;
    ((Sexy::GameButton*)zombatarButton)->mDownImage = Addon_Images.SelectorScreen_WoodSign3_press;
    ((Sexy::GameButton*)zombatarButton)->mOverImage = Addon_Images.SelectorScreen_WoodSign3_press;
    zombatarButton->mFocusLinks[0] = (*((Sexy::Widget* (__fastcall **)(Sexy::Widget *, MainMenuButtonId))mainMenu->vTable + 9))(mainMenu, BACK_POT_BUTTON);
    zombatarButton->mFocusLinks[1] = zombatarButton->mFocusLinks[0];
    zombatarButton->mFocusLinks[2] = zombatarButton->mFocusLinks[0];
    zombatarButton->mFocusLinks[3] = zombatarButton->mFocusLinks[0];
    Sexy_Widget_Resize(zombatarButton,Addon_Images.SelectorScreen_WoodSign3->mWidth / 2,0,Addon_Images.SelectorScreen_WoodSign3->mWidth,Addon_Images.SelectorScreen_WoodSign3->mHeight);
    Reanimation *mainMenuReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp,mainMenu->mMainMenuReanimID);
    if (mainMenuReanim == NULL) return;
    Reanimation_HideTrack(mainMenuReanim, "unlock stem", true);

    int index[3] = {Reanimation_FindTrackIndex(mainMenuReanim, "unlock"),
                    Reanimation_FindTrackIndex(mainMenuReanim, "unlock pressed"),
                    Reanimation_FindTrackIndex(mainMenuReanim, "unlock selected")};


    for (int i = 0; i < 3; ++i) {
        ReanimatorTrack *reanimatorTrack = mainMenuReanim->mDefinition->mTracks + index[i];
        int mTransformCount = reanimatorTrack->mTransformCount;
        for (int j = 0; j < mTransformCount; ++j) {
            reanimatorTrack->mTransforms[j].mTransX = mZombatarButtonX;
            reanimatorTrack->mTransforms[j].mTransY = mZombatarButtonY;
        }
    }


//    if (mainMenu->mPressedButtonId == UNLOCK_BUTTON) {
//        LOGD("123123213");
//        Reanimation *mainMenuReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mMainMenuReanimID);
//        if (mainMenuReanim != NULL) {
//            int index = Reanimation_FindTrackIndex(mainMenuReanim, "unlock");
//            ReanimatorTrack *reanimatorTrack = mainMenuReanim->mDefinition->mTracks + index;
//            int mTransformCount = reanimatorTrack->mTransformCount;
//            int theX = mZombatarButtonX + Addon_Images.SelectorScreen_WoodSign3->mWidth;
//            for (int j = 0; j < mTransformCount; ++j) {
//                reanimatorTrack->mTransforms[j].mTransX = theX;
//            }
//        }
//    }
}

void (*old_MainMenu_Enter)(MainMenu *mainMenu);

void MainMenu_Enter(MainMenu *mainMenu) {
//    LOGD("MainMenu_Enter");
    old_MainMenu_Enter(mainMenu);
    MainMenu_UpdateHouseReanim(mainMenu);
    // 解除成就按钮的禁用状态
    MainMenu_EnableButtons(mainMenu);
}

bool (*old_MainMenu_UpdateExit)(MainMenu *mainMenu);

bool MainMenu_UpdateExit(MainMenu *mainMenu) {
    //修复进排行榜时房子消失，不过感觉未来不需要这个玩意儿啦
//    if (mainMenu->mPressedButtonId == HOUSE_BUTTON && mainMenu->mExitCounter == 64) {
//        mainMenu->mExitCounter = 65;
//        return false;
//    }
    return old_MainMenu_UpdateExit(mainMenu);
}

void (*old_MainMenu_Exit)(MainMenu *mainMenu);

void MainMenu_Exit(MainMenu *mainMenu) {
//    LOGD("MainMenu_Exit");
    old_MainMenu_Exit(mainMenu);
    // 解除成就按钮的禁用状态
    MainMenu_EnableButtons(mainMenu);
}

void (*old_MainMenu_OnExit)(MainMenu *a);

void MainMenu_OnExit(MainMenu *mainMenu) {
//    LOGD("MainMenu_OnExit");
    LawnApp *lawnApp = mainMenu->mApp;
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuLeft);
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuCenter);
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuRight);

    if (mainMenu->mPressedButtonId == HOUSE_BUTTON) {
        LawnApp_KillMainMenu(lawnApp);
        LawnApp_ShowLeaderboards(lawnApp);
    }

    if (mainMenu->mPressedButtonId == UNLOCK_BUTTON) {
        LawnApp_KillMainMenu(lawnApp);
        LawnApp_ShowZombatarScreen(lawnApp);
    }
    old_MainMenu_OnExit(mainMenu);
}

void (*old_MainMenu_OnScene)(MainMenu *mainMenu, int scene);

void MainMenu_OnScene(MainMenu *mainMenu, int scene) {
    return old_MainMenu_OnScene(mainMenu, scene);
}

void (*old_MainMenu_SyncButtons)(MainMenu *mainMenu);

void MainMenu_SyncButtons(MainMenu *mainMenu) {
    // 解除成就按钮的禁用状态,同时刷新房子
    old_MainMenu_SyncButtons(mainMenu);
    MainMenu_UpdateHouseReanim(mainMenu);
    MainMenu_EnableButtons(mainMenu);
}

void (*old_MainMenu_MainMenu)(MainMenu* mainMenu,LawnApp *);

void MainMenu_MainMenu(MainMenu* mainMenu,LawnApp * mApp) {
    old_MainMenu_MainMenu(mainMenu,mApp);
}

int theOffsetX = 1792;
int theOffsetY = 220;

void (*old_MainMenu_UpdateCameraPosition)(MainMenu *mainMenu);

void MainMenu_UpdateCameraPosition(MainMenu *mainMenu) {
    old_MainMenu_UpdateCameraPosition(mainMenu);
    if (showHouse) {
        Reanimation *houseAnim = LawnApp_ReanimationTryToGet(mainMenu->mApp,mainMenu->mUnkReanimID2);
        if (houseAnim != NULL) {
            Reanimation_SetPosition(houseAnim, mainMenu->mCameraPositionX + theOffsetX,mainMenu->mCameraPositionY + theOffsetY);
        }
    }
}



void (*old_MainMenu_AddedToManager)(MainMenu *instance, int* a2);

void MainMenu_AddedToManager(MainMenu *mainMenu, int *a2) {
    old_MainMenu_AddedToManager(mainMenu,a2);
    if (!showHouse) return;
    Reanimation *reanimation = LawnApp_AddReanimation(mainMenu->mApp, mainMenu->mCameraPositionX + theOffsetX,mainMenu->mCameraPositionY + theOffsetY, 0, ReanimationType::LeaderboardsHouse);
    LawnApp_SetHouseReanim(mainMenu->mApp, reanimation);
    Reanimation_OverrideScale(reanimation, 0.8, 0.8);
    mainMenu->mUnkReanimID2 = LawnApp_ReanimationGetID(mainMenu->mApp, reanimation);
}

void (*old_MainMenu_RemovedFromManager)(MainMenu *instance, int* a2);

void MainMenu_RemovedFromManager(MainMenu *a, int* a2) {
    //记录当前游戏状态
    if (mMainMenuAchievementsWidget != NULL) {
        (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))a->vTable + 7))(a, mMainMenuAchievementsWidget); // RemoveWidget()
    }
    if (mMainMenuAchievementsBack != NULL) {
        (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))a->vTable + 7))(a, mMainMenuAchievementsBack); // RemoveWidget()
    }
    old_MainMenu_RemovedFromManager(a, a2);
}

void (*old_MainMenu_Delete2)(MainMenu *mainMenu);

void MainMenu_Delete2(MainMenu *mainMenu) {
    old_MainMenu_Delete2(mainMenu);
    if (mMainMenuAchievementsWidget != NULL) {
        MaskHelpWidget_Delete(mMainMenuAchievementsWidget);
        mMainMenuAchievementsWidget = NULL;
    }

    if (mMainMenuAchievementsBack != NULL) {
        GameButton_Delete(mMainMenuAchievementsBack);
        mMainMenuAchievementsBack = NULL;
    }
}

void (*old_MainMenu_Draw)(MainMenu *mainMenu, Sexy::Graphics *a2);

void MainMenu_Draw(MainMenu *mainMenu, Sexy::Graphics *graphics) {
    //实现绘制房子
    if (!showHouse) return old_MainMenu_Draw(mainMenu, graphics);

    if (mainMenu->mWidgetManager == NULL) return;
    if ((*(int (__fastcall **)(LawnApp *, int)) (*(_DWORD *) mainMenu->mApp + 412))(mainMenu->mApp, 6) ||
        (*(int (__fastcall **)(LawnApp *, int)) (*(_DWORD *) mainMenu->mApp + 412))(mainMenu->mApp, 5) ||
        (*(int (__fastcall **)(LawnApp *, int)) (*(_DWORD *) mainMenu->mApp + 412))(mainMenu->mApp, 60))
        return;

    Reanimation *mainMenuReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp,mainMenu->mMainMenuReanimID);
    if (mainMenuReanim == NULL) return;
    Reanimation *skyReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mSkyReanimID);
    Reanimation *sky2Reanim = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mSky2ReanimID);

    if (skyReanim != NULL && sky2Reanim != NULL) {
        Reanimation_DrawRenderGroup(skyReanim, graphics, 0);
        SexyTransform2D tmp = sky2Reanim->mOverlayMatrix;
        Sexy_SexyTransform2D_Scale(&sky2Reanim->mOverlayMatrix, 1.0, 0.4);
        sky2Reanim->mOverlayMatrix.m[0][1] = -0.4;
        Reanimation_DrawRenderGroup(sky2Reanim, graphics, 2);
        sky2Reanim->mOverlayMatrix = tmp;
    }
    Reanimation_DrawRenderGroup(mainMenuReanim, graphics, 1);
    Reanimation *houseAnim = LawnApp_ReanimationTryToGet(mainMenu->mApp,mainMenu->mUnkReanimID2);
    if (houseAnim != NULL) {
//        Sexy_Graphics_SetColorizeImages(graphics, true);
//        Color theColor = {255,255,255,225};
//        Sexy_Graphics_SetColor(graphics,&theColor);
        Reanimation_Draw(houseAnim, graphics);
//        Sexy_Graphics_SetColorizeImages(graphics, false);
    }
    Reanimation_DrawRenderGroup(mainMenuReanim, graphics, 0);
    if (mainMenu->mScene == 2) {
        Reanimation *butterFlyReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp,mainMenu->mButterflyReanimID);
        if (butterFlyReanim != NULL) {
            Reanimation_Draw(butterFlyReanim, graphics);
        }
    }
    Reanimation *crowReanim = LawnApp_ReanimationTryToGet(mainMenu->mApp, mainMenu->mCrowReanimID);
    if (crowReanim != NULL && (!mainMenu->unkBool5 || mainMenu->mExitCounter <= 65)) {
        Reanimation_Draw(crowReanim, graphics);
    }
    Sexy_MenuWidget_Draw(mainMenu, graphics);
    Sexy_Widget_DeferOverlay(mainMenu, 0);
    if (!MainMenu_InTransition(mainMenu))
        (*((void (__fastcall **)(MainMenu *, Sexy::Graphics *)) mainMenu->vTable + 129))(mainMenu, graphics);
    SexyTransform2D v42;
    ReanimatorTransform v43;
    int mailAlertTrackIndex = Reanimation_FindTrackIndex(mainMenuReanim, "mail alert");
    if (mailAlertTrackIndex > 0 && Mailbox_GetNumUnseenMessages(mainMenu->mApp->mMailBox) > 0) {
        PlayerInfo *mPlayerInfo = mainMenu->mApp->mPlayerInfo;
        if (mPlayerInfo->mLevel > 0 || LawnPlayerInfo_GetFlag(mPlayerInfo, 1)) {
            ReanimatorTransform_ReanimatorTransform(&v43);
            Reanimation_GetCurrentTransform(mainMenuReanim, mailAlertTrackIndex, &v43);
            Sexy::Image* mailAlertImage = v43.mImage;
            Sexy_SexyTransform2D_SexyTransform2D(&v42);
            Reanimation_MatrixFromTransform(&v43, &v42);
            Sexy_SexyTransform2D_Translate(&v42, mainMenu->mCameraPositionX,mainMenu->mCameraPositionY);
            int v14 = mailAlertImage->mWidth;
            int v15 = v14 + 3;
            int v16 = v14 < 0;
            int v17 = v14 & ~(v14 >> 31);
            if (v16)
                v17 = v15;
            Sexy_SexyTransform2D_Translate(&v42, v17 >> 2, 0.0);
            int v18 = mainMenu->unkMems3[3];
            if (v18 > 99)
                v18 = 0;
            mainMenu->unkMems3[3] = v18;
            TodAnimateCurveFloat(0, 100, v18, 0.75, 0.8, TodCurves::SinWave);
            TRect v38 = {0, 0, mailAlertImage->mWidth, mailAlertImage->mHeight};
            Sexy_Graphics_DrawImageMatrix(graphics, mailAlertImage, &v42, &v38, 0.0, 0.0, 1);
        }
    }
    int moreTrackIndex = Reanimation_FindTrackIndex(mainMenuReanim, "more");
    ReanimatorTransform_ReanimatorTransform(&v43);
    Reanimation_GetCurrentTransform(mainMenuReanim, moreTrackIndex, &v43);
    Sexy_SexyTransform2D_SexyTransform2D(&v42);
    Reanimation_MatrixFromTransform(&v43, &v42);
    Sexy_SexyTransform2D_Translate(&v42, mainMenu->mCameraPositionX, mainMenu->mCameraPositionY);
    Sexy_SexyTransform2D_Translate(&v42, 120.0, 200.0);
    Sexy::Image *m2DMarkImage = mainMenu->m2DMarkImage;
    TRect v37 = {0, 0, m2DMarkImage->mWidth, m2DMarkImage->mHeight};
    Sexy_Graphics_DrawImageMatrix(graphics, m2DMarkImage, &v42, &v37, 0.0, 0.0, 1);
    TRect v38 = {15, 15, 90, 90};
    Sexy_SexyTransform2D_Translate(&v42, -4.0, -16.0);
    Sexy_Graphics_DrawImageMatrix(graphics, mainMenu->mApp->mQRCodeImage, &v42, &v38, 0.0, 0.0, 1);
}





void (*old_MainMenu_DrawOverlay)(MainMenu *mainMenu, Sexy::Graphics *a2);

void MainMenu_DrawOverlay(MainMenu *mainMenu, Sexy::Graphics *a2) {
    // 在成就界面存在时，不显示冒险关卡数
    if (mMainMenuAchievementsWidget != NULL) {
        return;
    }
    old_MainMenu_DrawOverlay(mainMenu, a2);
}

void MaskHelpWidget_Draw(AchievementsWidget *achievementsWidget, Sexy::Graphics *graphics) {
    int theY = 0;
    int theDiffY = Addon_Images.hole->mHeight;
    for (int i = 0; i < mAchievementHoleLength; i++) {
        if (i == mAchievementHoleWormPos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_worm, 0, theY);
        } else if (i == mAchievementHoleGemsPos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_gems, 0, theY);
        } else if (i == mAchievementHoleChuzzlePos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_chuzzle, 0, theY);
        } else if (i == mAchievementHoleBjornPos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_bjorn, 0, theY);
        } else if (i == mAchievementHolePipePos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_pipe, 0, theY);
        } else if (i == mAchievementHoleTikiPos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_tiki, 0, theY);
        } else if (i == mAchievementHoleHeavyRocksPos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_heavyrocks, 0, theY);
        } else if (i == mAchievementHoleDuWeiPos) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_duwei, 0, theY);
        } else {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.hole, 0, theY);
        }
        theY += theDiffY;
    }
    Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_china, 0, theY);
    Sexy_Graphics_DrawImage(graphics, Addon_Images.hole_top, 0, 0);
    int theAchievementY = 300;
    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        if (!achievementsWidget->mApp->mPlayerInfo->mAchievements[i]) {
            Sexy_Graphics_SetColorizeImages(graphics, true);
            Sexy_Graphics_SetColor(graphics, &gray);
        }
        Sexy_Graphics_DrawImage(graphics, GetIconByAchievementId((AchievementId::AchievementId)i), 330, theAchievementY - 5);
        char *theAchievementName = GetNameByAchievementId((AchievementId::AchievementId)i);
        int holder[1];
        int holder1[1];
        Sexy_StrFormat(holder,"[%s]",theAchievementName);
        Sexy_StrFormat(holder1,"[%s_TEXT]",theAchievementName);
        Color theColor = {0,255,0,255};
        Color theColor1 = {255,255,255,255};
        TRect rect = {460,theAchievementY + 60,540,0};
        TodDrawString(graphics,holder,460,theAchievementY + 40,*Sexy_FONT_HOUSEOFTERROR28_Addr,theColor,DrawStringJustification::Left);
        if (i == AchievementId::ACHIEVEMENT_SHOP) {
            int holder2[1];
            TodReplaceNumberString(holder2,holder1,"{coin}",achievementsWidget->mApp->mPlayerInfo->mUsedCoins * 10);
            TodDrawStringWrapped(graphics,holder2,&rect,*Sexy_FONT_HOUSEOFTERROR20_Addr,&theColor1,DrawStringJustification::Left,false);
            Sexy_String_Delete(holder2);
        } else {
            TodDrawStringWrapped(graphics,holder1,&rect,*Sexy_FONT_HOUSEOFTERROR20_Addr,&theColor1,DrawStringJustification::Left,false);
        }
        Sexy_String_Delete(holder);
        Sexy_String_Delete(holder1);
        Sexy_Graphics_SetColorizeImages(graphics, false);
        theAchievementY += theDiffY * 2 / 3;
    }
    int theAccomplishedNum = 0;
    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        if (achievementsWidget->mApp->mPlayerInfo->mAchievements[i]) {
            theAccomplishedNum++;
        }
    }
    int holder[1];
    Sexy_StrFormat(holder,"%d/%d",theAccomplishedNum,AchievementId::MAX_ACHIEVEMENTS);
    Color theColor = {255,240,0,255};
    TodDrawString(graphics, holder, 1060, 173, *Sexy_FONT_DWARVENTODCRAFT18_Addr, theColor, DrawStringJustification::Center);
    Sexy_String_Delete(holder);
}

int mAchievementMouseDownY;

void MaskHelpWidget_MouseDown(AchievementsWidget *achievementsWidget, int x, int y, int theClickCount) {
    mAchievementMouseDownY = y;
}

void MaskHelpWidget_MouseDrag(AchievementsWidget *achievementsWidget, int x, int y) {
    if (mAchievementState != SHOWING) return;
    int theNewY = achievementsWidget->mY + (y - mAchievementMouseDownY);
    if (theNewY > mMainMenuHeight) theNewY = mMainMenuHeight;
    if (theNewY < 720 + mMainMenuHeight - (mAchievementHoleLength + 1) * Addon_Images.hole->mHeight) theNewY = 720 + mMainMenuHeight - (mAchievementHoleLength + 1) * Addon_Images.hole->mHeight;
    Sexy_Widget_Resize(achievementsWidget,achievementsWidget->mX,theNewY,achievementsWidget->mWidth,achievementsWidget->mHeight);
}

void MaskHelpWidget_MouseUp(AchievementsWidget *achievementsWidget, int x, int y) {

}

Sexy::Image *TrashBin_GetZombieTrashPiece(TrashBin *trashBin, int level) {
    int v3; // r0
    int v4; // r2
    int v5; // r3
    int v6; // r3

    v3 = RandRangeInt(0, 100);
    v4 = *((_DWORD *)trashBin + 85);
    if ( v4 >= 3 )
        v5 = 3;
    else
        v5 = *((_DWORD *)trashBin + 85);
    if ( v3 >= *((_DWORD *)trashBin + v5 + 79) && v3 <= *((_DWORD *)trashBin + v5 + 82) )
    {
        while ( 1 )
        {
            v3 = RandRangeInt(0, 100);
            v4 = *((_DWORD *)trashBin + 85);
            v6 = v4 >= 3 ? 3 : *((_DWORD *)trashBin + 85);
            if ( *((_DWORD *)trashBin + v6 + 79) > v3 )
                break;
            if ( *((_DWORD *)trashBin + v6 + 82) < v3 )
            {
                if ( !v4 )
                    goto LABEL_11;
                goto LABEL_16;
            }
        }
    }
    if ( v4 )
    {
        LABEL_16:
        if ( v4 == 1 )
        {
            if ( v3 <= 29 )
            {
                *((_DWORD *)trashBin + 80) = 0;
                *((_DWORD *)trashBin + 83) = 30;
                return Addon_Images.zombie_pile02_stack02;
            }
            else if ( v3 > 59 )
            {
                *((_DWORD *)trashBin + 80) = 61;
                *((_DWORD *)trashBin + 83) = 100;
                return Addon_Images.zombie_pile02_stack03;
            }
            else
            {
                *((_DWORD *)trashBin + 80) = 31;
                *((_DWORD *)trashBin + 83) = 60;
                return Addon_Images.zombie_pile02_stack01;
            }
        }
        else if ( v3 <= 29 )
        {
            *((_DWORD *)trashBin + 81) = 0;
            *((_DWORD *)trashBin + 84) = 30;
            return Addon_Images.zombie_pile03_stack02;
        }
        else if ( v3 <= 59 )
        {
            *((_DWORD *)trashBin + 81) = 31;
            *((_DWORD *)trashBin + 84) = 60;
            return Addon_Images.zombie_pile03_stack03;
        }
        else
        {
            *((_DWORD *)trashBin + 81) = 61;
            *((_DWORD *)trashBin + 84) = 100;
            return Addon_Images.zombie_pile03_stack01;
        }
    }
    else
    {
        LABEL_11:
        if ( v3 <= 29 )
        {
            *((_DWORD *)trashBin + 82) = 30;
            *((_DWORD *)trashBin + 79) = v4;
            return Addon_Images.zombie_pile01_stack02;
        }
        else if ( v3 > 59 )
        {
            *((_DWORD *)trashBin + 79) = 61;
            *((_DWORD *)trashBin + 82) = 100;
            return Addon_Images.zombie_pile01_stack03;
        }
        else
        {
            *((_DWORD *)trashBin + 79) = 31;
            *((_DWORD *)trashBin + 82) = 60;
            return Addon_Images.zombie_pile01_stack01;
        }
    }
}

Sexy::Image *TrashBin_GetPlantTrashPiece(TrashBin *trashBin, int level) {
    int mPileNum; // r6

    mPileNum = trashBin->mPileNum;
    if ( mPileNum != 0)
    {
        if ( mPileNum == 1 )
        {
            if ( RandRangeInt(trashBin->mRandomPileWeight[1], trashBin->mRandomPileWeight[4]) > 49 )
            {
                trashBin->mRandomPileWeight[1] = 0;
                trashBin->mRandomPileWeight[4] = 50;
                return Addon_Images.plant_pile02_stack02;
            }
            else
            {
                trashBin->mRandomPileWeight[1] = 50;
                trashBin->mRandomPileWeight[4] = 100;
                return Addon_Images.plant_pile02_stack01;
            }
        }
        else if ( RandRangeInt(trashBin->mRandomPileWeight[2], trashBin->mRandomPileWeight[5]) <= 49 )
        {
            trashBin->mRandomPileWeight[2] = 50;
            trashBin->mRandomPileWeight[5] = 100;
            return Addon_Images.plant_pile03_stack01;
        }
        else
        {
            trashBin->mRandomPileWeight[2] = 0;
            trashBin->mRandomPileWeight[5] = 50;
            return Addon_Images.plant_pile03_stack02;
        }
    }
    else if ( RandRangeInt(trashBin->mRandomPileWeight[0], trashBin->mRandomPileWeight[3]) > 49 )
    {
        trashBin->mRandomPileWeight[3] = 50;
        trashBin->mRandomPileWeight[0] = 0;
        return Addon_Images.plant_pile01_stack02;
    }
    else
    {
        trashBin->mRandomPileWeight[0] = 50;
        trashBin->mRandomPileWeight[3] = 100;
        return Addon_Images.plant_pile01_stack01;
    }
}


inline int zombiePileHeight = 70;
inline int plantPileHeight = 100;

void (*old_TrashBin_TrashBin)(TrashBin *trashBin, TrashBin::TrashPileType theTrashPileType, float height);

void TrashBin_TrashBin(TrashBin *trashBin, TrashBin::TrashPileType theTrashPileType, float height) {
    old_TrashBin_TrashBin(trashBin, theTrashPileType, height);

    int thePileNum = height / (theTrashPileType == TrashBin::ZOMBIE_PILE ? zombiePileHeight : plantPileHeight) + 1;
    if (thePileNum >= 10)
        thePileNum = 10;
    PlayerInfo *mPlayerInfo = ((LawnApp *) *gLawnApp_Addr)->mPlayerInfo;
    int level = mPlayerInfo->mLevel;
    if (LawnPlayerInfo_GetFlag(mPlayerInfo, 1) || LawnPlayerInfo_GetFlag(mPlayerInfo, 0x8000))
        level = 50;
    trashBin->mPileNum = 0;
    for (int i = 0; i < thePileNum; ++i) {
        if (trashBin->mTrashPileType == TrashBin::PLANT_PILE) {
            trashBin->mPileImage[i] = TrashBin_GetPlantTrashPiece(trashBin, level);
        } else {
            trashBin->mPileImage[i] = TrashBin_GetZombieTrashPiece(trashBin, level);
        }
        trashBin->mMirrorPile[i] = RandRangeInt(0, 100) <= 49;
        trashBin->mPileNum++;
    }
}

void TrashBin_Draw(TrashBin *trashBin, Sexy::Graphics *a2) {

    int mTrashPileType = trashBin->mTrashPileType;
    int thePileHeight = mTrashPileType == TrashBin::ZOMBIE_PILE ? zombiePileHeight : plantPileHeight;
    int thePileNum = trashBin->mTrashHeight / thePileHeight;
    if (thePileNum >= 10 )
        thePileNum = 10;
    if (mTrashPileType == TrashBin::PLANT_PILE) {
        Sexy_Graphics_DrawImageF(a2,Addon_Images.plant_can,trashBin->mX - 22,trashBin->mY + 15);
    }else {
        Sexy_Graphics_DrawImageF(a2, Addon_Images.zombie_can, trashBin->mX, trashBin->mY);
    }

    if (thePileNum != 10) {
        Sexy_Graphics_DrawImageMirror(a2, trashBin->mPileImage[thePileNum], trashBin->mX,trashBin->mHeight % thePileHeight - thePileHeight + trashBin->mY -thePileHeight * thePileNum,trashBin->mMirrorPile[thePileNum]);
    }
    if (thePileNum <= 0)
        return;
    for (int i = 0; i < thePileNum; ++i) {
        Sexy_Graphics_DrawImageMirror(a2, trashBin->mPileImage[i], trashBin->mX,trashBin->mHeight % thePileHeight - thePileHeight + trashBin->mY -thePileHeight * i,trashBin->mMirrorPile[i]);
    }


//    int holder[1];
//    int holder1[1];
//    TodStringTranslate(holder,"[TRASH_HEIGHT]");
//    TodReplaceNumberString(holder1,holder,"{HEIGHT}",(int)trashBin->mTrashHeight);
//
//    if (mTrashPileType == TrashBin::PLANT_PILE) {
//        TRect theRect ={317,658,120,50};
//        Sexy::Font* theFont = *Sexy_FONT_CONTINUUMBOLD14_Addr;
//        TodDrawStringWrapped(a2, holder1, &theRect, theFont, &yellow, DrawStringJustification::Center, false);
//    }else {
//        Sexy_Graphics_DrawImageF(a2, Addon_Images.zombie_can, trashBin->mX, trashBin->mY);
//    }
}

int LeaderboardsWidget_GetAchievementIdByReanimationType(ReanimationType::ReanimationType type) {
    AchievementId::AchievementId id = AchievementId::ACHIEVEMENT_HOME_SECURITY;
    switch (type) {
        case ReanimationType::AchievementHomeSecurity:
            id = AchievementId::ACHIEVEMENT_HOME_SECURITY;
            break;
        case ReanimationType::AchievementMorticulturalist:
            id = AchievementId::ACHIEVEMENT_MORTICULTURALIST;
            break;
        case ReanimationType::AchievementSmartyBranches:
            id = AchievementId::ACHIEVEMENT_TREE;
            break;
        case ReanimationType::AchievementCrashOfTheTitan:
            id = AchievementId::ACHIEVEMENT_GARG;
            break;
        case ReanimationType::AchievementZffs4Evr:
            id = AchievementId::ACHIEVEMENT_COOP;
            break;
        case ReanimationType::AchievementAliveAndPlanting:
            id = AchievementId::ACHIEVEMENT_IMMORTAL;
            break;
        case ReanimationType::AchievementVersus:
            id = AchievementId::ACHIEVEMENT_VERSUS;
            break;
        case ReanimationType::AchievementSoilYourPlants:
            id = AchievementId::ACHIEVEMENT_SOILPLANTS;
            break;
        case ReanimationType::AchievementExplodonator:
            id = AchievementId::ACHIEVEMENT_EXPLODONATOR;
            break;
        case ReanimationType::AchievementCloseShave:
            id = AchievementId::ACHIEVEMENT_CLOSESHAVE;
            break;
        case ReanimationType::AchievementShop:
            id = AchievementId::ACHIEVEMENT_SHOP;
            break;
        case ReanimationType::AchievementNomNomNom:
            id = AchievementId::ACHIEVEMENT_CHOMP;
            break;
    }
    return id - AchievementId::ACHIEVEMENT_HOME_SECURITY;
}


int LeaderboardsWidget_GetAchievementIdByDrawOrder(int drawOrder) {
    ReanimationType::ReanimationType type = ReanimationType::AchievementHomeSecurity;
    switch (drawOrder) {
        case 0:
            type = ReanimationType::AchievementCloseShave;
            break;
        case 1:
            type = ReanimationType::AchievementShop;
            break;
        case 2:
            type = ReanimationType::AchievementExplodonator;
            break;
        case 3:
            type = ReanimationType::AchievementAliveAndPlanting;
            break;
        case 4:
            type = ReanimationType::AchievementSmartyBranches;
            break;
        case 5:
            type = ReanimationType::AchievementNomNomNom;
            break;
        case 6:
            type = ReanimationType::AchievementSoilYourPlants;
            break;
        case 7:
            type = ReanimationType::AchievementVersus;
            break;
        case 8:
            type = ReanimationType::AchievementZffs4Evr;
            break;
        case 9:
            type = ReanimationType::AchievementCrashOfTheTitan;
            break;
        case 10:
            type = ReanimationType::AchievementMorticulturalist;
            break;
        case 11:
            type = ReanimationType::AchievementHomeSecurity;
            break;
    }
    return type - ReanimationType::AchievementHomeSecurity;
}

void LeaderboardsWidget_ButtonDepress(Sexy::ButtonListener *listener, int id) {
    if (id == 1000){
        LawnApp* lawnApp = (LawnApp*)*gLawnApp_Addr;
        LawnApp_KillLeaderboards(lawnApp);
        LawnApp_ShowMainMenuScreen(lawnApp);
    }
}

void LeaderboardsWidget_ButtonPress(Sexy::ButtonListener *listener, int id, int theCount) {

}

void Sexy_ButtonListener_ButtonMouseEnter(Sexy::ButtonListener *listener, int id) {
}

void Sexy_ButtonListener_ButtonMouseMove(Sexy::ButtonListener *listener, int id, int x, int y) {
}

void Sexy_ButtonListener_ButtonMouseLeave(Sexy::ButtonListener *listener, int id) {
}

void Sexy_ButtonListener_ButtonDownTick(Sexy::ButtonListener *listener, int id) {
}


float gLeaderboardAchievementsPosition[12][2] = {{198, 496},
                                                 {210, 492},
                                                 {222, 306},
                                                 {405, 501},
                                                 {368, 500},
                                                 {690, 478},
                                                 {615, 487},
                                                 {524, 326},
                                                 {756, 373},
                                                 {678, 390},
                                                 {791, 278},
                                                 {430, 362}};

void LeaderboardsWidget_LeaderboardsWidget(LeaderboardsWidget *leaderboardsWidget, LawnApp *lawnApp) {
    DaveHelp_DaveHelp(leaderboardsWidget,lawnApp);
    Sexy_Widget_Resize(leaderboardsWidget, -240, -60, 1280, 720);
    leaderboardsWidget->mZombieTrashBin = (TrashBin*)operator new(sizeof(TrashBin));
    TrashBin_TrashBin(leaderboardsWidget->mZombieTrashBin,TrashBin::ZOMBIE_PILE,lawnApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::ZOMBIES_KILLED] / 125.0f);
    Sexy_Widget_Move(leaderboardsWidget->mZombieTrashBin, 134, 332);
    leaderboardsWidget->mPlantTrashBin = (TrashBin*)operator new(sizeof(TrashBin));
    TrashBin_TrashBin(leaderboardsWidget->mPlantTrashBin,TrashBin::PLANT_PILE,lawnApp->mPlayerInfo->mGameStats.mMiscStats[GameStats::PLANTS_KILLED] / 125.0f);
    Sexy_Widget_Move(leaderboardsWidget->mPlantTrashBin, 962, 351);
    leaderboardsWidget->mLeaderboardReanimations = (LeaderboardReanimations*)operator new(sizeof(LeaderboardReanimations));
    for (int i = 0; i < 5; ++i) {
        Reanimation* reanim = (Reanimation *) operator new(sizeof(Reanimation));
        Reanimation_Reanimation(reanim);
        Reanimation_ReanimationInitializeType(reanim, 0.0, 0.0, (ReanimationType::ReanimationType)(ReanimationType::LeaderboardsHouse + i));
        Reanimation_SetAnimRate(reanim, i == 4 ? 2.0f : 0.0f); // 云儿飘得慢一些
        reanim->mLoopType = ReanimLoopType::Loop;
        if (i == 1 || i == 2 || i == 3) {
            Reanimation_PlayReanim(reanim, "anim_idle", ReanimLoopType::Loop, 0, 12.0f);
        }
        if (i == 0) {
            LawnApp_SetHouseReanim(leaderboardsWidget->mApp, reanim);
            Reanimation_SetPosition(reanim, 456.9f, 129.3f);
        }
        Reanimation_Update(reanim); // 一次Update是必要的，否则绘制出来是Empty
        leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i] = reanim;
    }
    Reanimation_AssignRenderGroupToTrack(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1],"survival button 1",1); // 设置无尽模式按钮
    Reanimation_SetImageOverride(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1],"survival button 1",Addon_Images.survival_button); // 设置无尽模式按钮
    Reanimation_HideTrack(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1],"house 1",true); // 隐藏默认房屋
    Reanimation_HideTrack(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1],"house achievements 1",true); // 隐藏默认房屋
//    Reanimation_HideTrack(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1],"house 2",true); // 隐藏默认房屋
//    Reanimation_HideTrack(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1],"house achievements 2",true); // 隐藏默认房屋


    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        leaderboardsWidget->mAchievements[i] = lawnApp->mPlayerInfo->mAchievements[LeaderboardsWidget_GetAchievementIdByReanimationType((ReanimationType::ReanimationType)(ReanimationType::AchievementHomeSecurity+i))];
        Reanimation* reanim = (Reanimation *) operator new(sizeof(Reanimation));
        Reanimation_Reanimation(reanim);
        Reanimation_ReanimationInitializeType(reanim, 0.0, 0.0, (ReanimationType::ReanimationType)(ReanimationType::AchievementHomeSecurity + i));
        Reanimation_SetPosition(reanim,gLeaderboardAchievementsPosition[i][0],gLeaderboardAchievementsPosition[i][1]);
        reanim->mLoopType = ReanimLoopType::Loop;
        Reanimation_Update(reanim); // 一次Update是必要的，否则绘制出来是Empty
        leaderboardsWidget->mLeaderboardReanimations->achievementReanim[i] = reanim;
    }

    leaderboardsWidget->mLongestRecordPool = lawnApp->mPlayerInfo->mChallengeRecords[GameMode::SurvivalEndlessStage3 - 2];

    Sexy::ButtonListener* mLeaderboardsListener = (Sexy::ButtonListener*) operator new(sizeof (Sexy::ButtonListener));
    leaderboardsWidget->mButtonListener = mLeaderboardsListener;
    Sexy::ButtonListenerVTable* mVTable = (Sexy::ButtonListenerVTable*) operator new(sizeof (Sexy::ButtonListenerVTable));
    mLeaderboardsListener->vTable = mVTable;
//    mVTable->ButtonPress = (void *) LeaderboardsWidget_ButtonPress;
    mVTable->ButtonPress2 = (void *) LeaderboardsWidget_ButtonPress;
    mVTable->ButtonDepress = (void *) LeaderboardsWidget_ButtonDepress;
    mVTable->ButtonMouseEnter = (void *) Sexy_ButtonListener_ButtonMouseEnter;
    mVTable->ButtonMouseMove = (void *) Sexy_ButtonListener_ButtonMouseMove;
    mVTable->ButtonMouseLeave = (void *) Sexy_ButtonListener_ButtonMouseLeave;
    mVTable->ButtonDownTick = (void *) Sexy_ButtonListener_ButtonDownTick;
    int holder[1];
    TodStringTranslate(holder,"[CLOSE]");
    Sexy::GameButton* mBackButton = MakeButton(1000,mLeaderboardsListener,leaderboardsWidget,holder);
    Sexy_String_Delete(holder);
    Sexy_Widget_Resize(mBackButton, 1040, 590, 120, 50);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))leaderboardsWidget->vTable + 6))(leaderboardsWidget, mBackButton); // AddWidget()
    leaderboardsWidget->mBackButton = mBackButton;
    leaderboardsWidget->mFocusedAchievementIndex = 0;
    leaderboardsWidget->mHighLightAchievement = false;
}

void DaveHelp_Update(LeaderboardsWidget *leaderboardsWidget) {

    for (int i = 0; i < 5; ++i) {
        Reanimation_Update(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i]);
    }

    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        if (!leaderboardsWidget->mAchievements[i]) continue;
        Reanimation_Update(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[i]);
    }
    (*((void (__fastcall **)(Sexy::Widget *))leaderboardsWidget->vTable + 25))(leaderboardsWidget); // MarkDirty();
}

void DaveHelp_Draw(LeaderboardsWidget* leaderboardsWidget,Sexy::Graphics* graphics) {
    for (int i = 4; i >= 0 ; i--) {
        Reanimation_DrawRenderGroup(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i], graphics, 0);
    }

    TrashBin_Draw(leaderboardsWidget->mPlantTrashBin,graphics);
    TrashBin_Draw(leaderboardsWidget->mZombieTrashBin,graphics);

    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        int num = LeaderboardsWidget_GetAchievementIdByDrawOrder(i);
        if (!leaderboardsWidget->mAchievements[num]) continue;
        if (leaderboardsWidget->mHighLightAchievement && num == leaderboardsWidget->mFocusedAchievementIndex) {
            AchievementId::AchievementId id = (AchievementId::AchievementId) ( LeaderboardsWidget_GetAchievementIdByReanimationType((ReanimationType::ReanimationType)(num + ReanimationType::AchievementHomeSecurity)) +AchievementId::ACHIEVEMENT_HOME_SECURITY);
            Sexy::Image* image = GetIconByAchievementId(id);
            Color color;
            GetFlashingColor(&color,leaderboardsWidget->mApp->mAppCounter,120);
            Sexy_Graphics_SetColorizeImages(graphics, true);
            Sexy_Graphics_SetColor(graphics,&color);
            Reanimation_Draw(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[num], graphics);
            Sexy_Graphics_SetColorizeImages(graphics, false);
            int offsetX = gLeaderboardAchievementsPosition[num][0] + 20;
            int offsetY = gLeaderboardAchievementsPosition[num][1] - 200;
            Sexy_Graphics_DrawImage(graphics, image, offsetX, offsetY);
            int holder[1];
            Sexy_StrFormat(holder,"[%s]",GetNameByAchievementId(id));
            TRect rect = {offsetX - 42,offsetY + 125,200,200};
            Color theColor = {0,255,0,255};
            TodDrawStringWrapped(graphics,holder,&rect,*Sexy_FONT_HOUSEOFTERROR28_Addr,&theColor,DrawStringJustification::Center,false);
            Sexy_String_Delete(holder);
        } else {
            Reanimation_Draw(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[num],graphics);
        }
    }

    if (LawnApp_HasFinishedAdventure(leaderboardsWidget->mApp)) {
        Reanimation_DrawRenderGroup(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[1], graphics, 1);
        int holder[1];
        int holder1[1];
        TodStringTranslate(holder,"[LEADERBOARD_STREAK]");
        TodReplaceNumberString(holder1,holder,"{STREAK}", leaderboardsWidget->mLongestRecordPool);
        TRect theRect ={317,658,120,50};
        Sexy::Font* theFont = *Sexy_FONT_CONTINUUMBOLD14_Addr;
        TodDrawStringWrapped(graphics, holder1, &theRect, theFont, &yellow, DrawStringJustification::Center, false);
        Sexy_String_Delete(holder);
        Sexy_String_Delete(holder1);
    }

//    Sexy_Graphics_DrawImage(graphics, Addon_Images.survival_button, 270, 579);


    int holder2[1];
    int holder3[1];
    int holder4[1];
    TRect theRect1 = {240, 70, 800, 70};
    TodStringTranslate(holder2, "[PLAYERS_HOUSE]");
    Sexy_StrFormat(holder3, "%s", leaderboardsWidget->mApp->mPlayerInfo->mName);
    TodReplaceString(holder4, holder2, "{PLAYER}", holder3);
    Sexy::Font* theFont1 = *Sexy_FONT_HOUSEOFTERROR28_Addr;
    TodDrawStringWrapped(graphics, holder4, &theRect1, theFont1, &white, DrawStringJustification::Center, false);
    Sexy_String_Delete(holder2);
    Sexy_String_Delete(holder3);
    Sexy_String_Delete(holder4);

//    Sexy_Graphics_SetColor(graphics, &yellow);
//    TRect rect = {xx,yy,xw,yh};
//    Sexy_Graphics_DrawRect(graphics, &rect);
//
//    Sexy_Graphics_SetColor(graphics, &green);
//    TRect rect2 = {xx1,yy1,xw1,yh1};
//    Sexy_Graphics_DrawRect(graphics, &rect2);
//    if (LawnApp_EarnedGoldTrophy(leaderboardsWidget->mApp)) {
//        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SUNFLOWER_TROPHY_Addr, 1110, 290, 1, 0);
//    } else if (LawnApp_HasFinishedAdventure(leaderboardsWidget->mApp)) {
//        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SUNFLOWER_TROPHY_Addr, 1110, 290, 0, 0);
//    }

}

void (*old_DaveHelp_Delete2)(LeaderboardsWidget* leaderboardsWidget);

void DaveHelp_Delete2(LeaderboardsWidget *leaderboardsWidget) {
    TrashBin_Delete(leaderboardsWidget->mZombieTrashBin);
    TrashBin_Delete(leaderboardsWidget->mPlantTrashBin);
    for (int i = 0; i < 5; ++i) {
        Reanimation_Delete2(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i]);
        operator delete(leaderboardsWidget->mLeaderboardReanimations->backgroundReanim[i]);
    }
    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        Reanimation_Delete2(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[i]);
        operator delete(leaderboardsWidget->mLeaderboardReanimations->achievementReanim[i]);
    }
    GameButton_Delete(leaderboardsWidget->mBackButton);
    operator delete(leaderboardsWidget->mButtonListener->vTable);
    operator delete(leaderboardsWidget->mButtonListener);
    operator delete(leaderboardsWidget->mLeaderboardReanimations);
    old_DaveHelp_Delete2(leaderboardsWidget);
}

TRect gLeaderboardAchievementsRect[12][2] = {{{253, 594, 485, 62},  {833, 528, 198, 68}},
                                             {{209, 488, 91,  106}, {0,   0,   0,   0}},
                                             {{269, 330, 185, 122}, {298, 453, 91,  91}},
                                             {{452, 550, 151, 76},  {446, 512, 68,  37}},
                                             {{373, 504, 83,  34},  {389, 533, 63,  37}},
                                             {{744, 516, 86,  97},  {0,   0,   0,   0}},
                                             {{632, 490, 52,  40},  {636, 530, 60,  33}},
                                             {{561, 340, 77,  196}, {525, 404, 145, 56}},
                                             {{880, 384, 78,  82},  {891, 467, 26,  68}},
                                             {{715, 416, 104, 81},  {765, 384, 54,  35}},
                                             {{817, 332, 113, 171}, {850, 298, 46,  31}},
                                             {{456, 362, 43,  122}, {461, 484, 71,  30}}};


void DaveHelp_MouseDown(LeaderboardsWidget *leaderboardsWidget, int x, int y, int theClickCount) {


    for (int i = 0; i < AchievementId::MAX_ACHIEVEMENTS; ++i) {
        int num = LeaderboardsWidget_GetAchievementIdByDrawOrder(AchievementId::MAX_ACHIEVEMENTS - 1 - i);
        if (!leaderboardsWidget->mAchievements[num]) continue;
        if (TRect_Contains(&gLeaderboardAchievementsRect[num][0],x,y) || TRect_Contains(&gLeaderboardAchievementsRect[num][1],x,y)){
            if (leaderboardsWidget->mFocusedAchievementIndex == num && leaderboardsWidget->mHighLightAchievement) {
                leaderboardsWidget->mHighLightAchievement = false;
            }else {
                leaderboardsWidget->mFocusedAchievementIndex = num;
                leaderboardsWidget->mHighLightAchievement = true;
            }
            break;
        }
    }

//    tmp = !tmp;
//    if (tmp) {
//        xx = x;
//        yy = y;
//        xw = 0;
//        yh = 0;
//        LOGD("%d %d", x, y);
//    }else{
//        xx1 = x;
//        yy1 = y;
//        xw1 = 0;
//        yh1 = 0;
//        LOGD("%d %d", x, y);
//    }

//    TRect rect = {1066, 574, 72, 72};
//    if (TRect_Contains(&rect, x, y)) {
//        leaderboardsWidget->mTouchDownInBackRect = true;
//        LawnApp_PlaySample(leaderboardsWidget->mApp,*Sexy_SOUND_GRAVEBUTTON_Addr);
//    }
}

void DaveHelp_MouseDrag(LeaderboardsWidget *leaderboardsWidget, int x, int y) {
//    if (tmp) {
//        xw = x - xx;
//        yh = y - yy;
//        LOGD("%d: %d, %d, %d, %d",leaderboardsWidget->mFocusedAchievementIndex,xx,yy,xw,yh);
//    }else{
//        xw1 = x - xx1;
//        yh1 = y - yy1;
//        LOGD("%d: %d, %d, %d, %d",leaderboardsWidget->mFocusedAchievementIndex,xx1,yy1,xw1,yh1);
//    }

}

void DaveHelp_MouseUp(LeaderboardsWidget *leaderboardsWidget, int x, int y) {

}


void DaveHelp_DealClick(LeaderboardsWidget *leaderboardsWidget, int id) {

}

void DaveHelp_KeyDown(LeaderboardsWidget *leaderboardsWidget, int keyCode) {

    if (keyCode == Sexy::Back || keyCode == Sexy::Back2) {
        if (leaderboardsWidget->mHighLightAchievement) {
            leaderboardsWidget->mHighLightAchievement = false;
            return;
        }
        LawnApp_KillLeaderboards(leaderboardsWidget->mApp);
        LawnApp_ShowMainMenuScreen(leaderboardsWidget->mApp);
        return;
    }
    if (keyCode == Sexy::Up || keyCode == Sexy::Down || keyCode == Sexy::Left || keyCode == Sexy::Right) {
        bool flag = false;
        for (int i = 0; i < 12; ++i) {
            if (leaderboardsWidget->mAchievements[i]) flag = true;
        }
        if (!flag) return;

        leaderboardsWidget->mHighLightAchievement = true;
        int mFocusedIndex = leaderboardsWidget->mFocusedAchievementIndex;
        if (keyCode == Sexy::Up || keyCode == Sexy::Left) {
            do {
                mFocusedIndex++;
                if (mFocusedIndex > 11) {
                    mFocusedIndex = 0;
                }
            }
            while (!leaderboardsWidget->mAchievements[mFocusedIndex]);
        } else {
            do {
                mFocusedIndex--;
                if (mFocusedIndex < 0) {
                    mFocusedIndex = 11;
                }
            }
            while (!leaderboardsWidget->mAchievements[mFocusedIndex]);
        }
        leaderboardsWidget->mFocusedAchievementIndex = mFocusedIndex;
        return;
    }
}

void ZombatarWidget_SetDefault(ZombatarWidget* zombatarWidget) {
    zombatarWidget->mSelectedTab = 0;
    zombatarWidget->mSelectedSkinColor = 0;
    zombatarWidget->mSelectedHair = 255;
    zombatarWidget->mSelectedHairColor = 255;
    zombatarWidget->mSelectedFHair = 255;
    zombatarWidget->mSelectedFHairColor = 255;
    zombatarWidget->mSelectedFHairPage = 0;
    zombatarWidget->mSelectedTidBit = 255;
    zombatarWidget->mSelectedTidBitColor = 255;
    zombatarWidget->mSelectedEyeWear = 255;
    zombatarWidget->mSelectedEyeWearColor = 255;
    zombatarWidget->mSelectedCloth = 255;
    zombatarWidget->mSelectedAccessory = 255;
    zombatarWidget->mSelectedAccessoryColor = 255;
    zombatarWidget->mSelectedHat = 255;
    zombatarWidget->mSelectedHatColor = 255;
    zombatarWidget->mSelectedBackground = 0;
    zombatarWidget->mSelectedBackgroundColor = 255;
    zombatarWidget->mSelectedBackgroundPage = 0;
    Reanimation_SetZombatarReanim(zombatarWidget->mZombatarReanim);
}

void ZombatarWidget_ButtonPress(ZombatarWidget* zombatarWidget, int id) {

}

void ZombatarWidget_ButtonDepress(ZombatarWidget* zombatarWidget, int id) {
    if (id == 1000) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        LawnApp_KillZombatarScreen(lawnApp);
        LawnApp_ShowMainMenuScreen(lawnApp);
        return;
    }

    if (id == 1001) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        if (LawnApp_LawnMessageBox(lawnApp,Dialogs::DIALOG_MESSAGE,"[ZOMBATAR_FINISHED_WARNING_HEADER]","[ZOMBATAR_FINISHED_WARNING_TEXT]","[ZOMBATAR_FINISHED_BUTTON_TEXT]","[ZOMBATAR_BACK_BUTTON_TEXT]",1) == 1001)
            return;

        if (Addon_Images.zombatar_portrait != NULL) {
            Sexy_MemoryImage_Delete(Addon_Images.zombatar_portrait);
        }
        Sexy::Image* image = (Sexy::Image*) operator new(sizeof(Sexy::Image));
        Sexy_MemoryImage_MemoryImage(image);
        Sexy_MemoryImage_Create(image, Addon_Images.zombatar_background_blank->mWidth, Addon_Images.zombatar_background_blank->mHeight);
        Sexy_MemoryImage_SetImageMode(image, true, true);
        image->mVolatile = true;
        Sexy::Graphics graphics;
        Sexy_Graphics_Graphics2(&graphics, image);
        TestMenuWidget_DrawPortrait(mMainMenuZombatarWidget, &graphics, 0, 0);
        int holder[1];
        Sexy_StrFormat(holder, "ZOMBATAR.PNG");
        Sexy_MemoryImage_WriteToPng(image, holder);
        Sexy_String_Delete(holder);
        Addon_Images.zombatar_portrait = image;
        mMainMenuZombatarWidget->mShowExistingZombatarPortrait = true;
        mMainMenuZombatarWidget->mShowZombieTypeSelection = false;

        PlayerInfo* playerInfo = lawnApp->mPlayerInfo;
        playerInfo->mZombatarHat = mMainMenuZombatarWidget->mSelectedHat;
        playerInfo->mZombatarHatColor = mMainMenuZombatarWidget->mSelectedHatColor;
        playerInfo->mZombatarHair = mMainMenuZombatarWidget->mSelectedHair;
        playerInfo->mZombatarHairColor = mMainMenuZombatarWidget->mSelectedHairColor;
        playerInfo->mZombatarFacialHair = mMainMenuZombatarWidget->mSelectedFHair;
        playerInfo->mZombatarFacialHairColor = mMainMenuZombatarWidget->mSelectedFHairColor;
        playerInfo->mZombatarAccessory = mMainMenuZombatarWidget->mSelectedAccessory;
        playerInfo->mZombatarAccessoryColor = mMainMenuZombatarWidget->mSelectedAccessoryColor;
        playerInfo->mZombatarTidBit = mMainMenuZombatarWidget->mSelectedTidBit;
        playerInfo->mZombatarTidBitColor = mMainMenuZombatarWidget->mSelectedTidBitColor;
        playerInfo->mZombatarEyeWear = mMainMenuZombatarWidget->mSelectedEyeWear;
        playerInfo->mZombatarEyeWearColor = mMainMenuZombatarWidget->mSelectedEyeWearColor;


        playerInfo->mZombatarEnabled =
                playerInfo->mZombatarHat != 255 || playerInfo->mZombatarHair != 255 ||
                playerInfo->mZombatarFacialHair != 255 || playerInfo->mZombatarAccessory != 255 ||
                playerInfo->mZombatarTidBit != 255 || playerInfo->mZombatarEyeWear != 255;
        ZombatarWidget_SetDefault(mMainMenuZombatarWidget);
        return;
    }

    if (id == 1002) {
        if (Addon_Images.zombatar_portrait != NULL) {
            mMainMenuZombatarWidget->mShowExistingZombatarPortrait = true;
            ZombatarWidget_SetDefault(mMainMenuZombatarWidget);
        }
        return;
    }

    if (id == 1003) {
        mMainMenuZombatarWidget->mShowExistingZombatarPortrait = false;
        return;
    }

    if (id == 1004) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        if (LawnApp_LawnMessageBox(lawnApp,Dialogs::DIALOG_MESSAGE,"[ZOMBATAR_DELETE_HEADER]","[ZOMBATAR_DELETE_BODY]","[BUTTON_OK]","[BUTTON_CANCEL]",1) == 1001)
            return;
        mMainMenuZombatarWidget->mShowExistingZombatarPortrait = false;
        if (Addon_Images.zombatar_portrait != NULL) {
            Sexy_MemoryImage_Delete(Addon_Images.zombatar_portrait);
            Addon_Images.zombatar_portrait = NULL;
            int holder[1];
            Sexy_StrFormat(holder, "ZOMBATAR.PNG");
            Sexy_SexyAppBase_EraseFile(lawnApp, holder);
            Sexy_String_Delete(holder);
        }
        return;
    }
}

Sexy::Image *ZombatarWidget_GetTabButtonImageByIndex(int index) {
    switch (index) {
        case ZombatarWidget::SKIN:
            return Addon_Images.zombatar_skin_button;
        case ZombatarWidget::HAIR:
            return Addon_Images.zombatar_hair_button;
        case ZombatarWidget::FHAIR:
            return Addon_Images.zombatar_fhair_button;
        case ZombatarWidget::TIDBIT:
            return Addon_Images.zombatar_tidbits_button;
        case ZombatarWidget::EYEWEAR:
            return Addon_Images.zombatar_eyewear_button;
        case ZombatarWidget::CLOTHES:
            return Addon_Images.zombatar_clothes_button;
        case ZombatarWidget::ACCESSORY:
            return Addon_Images.zombatar_accessory_button;
        case ZombatarWidget::HAT:
            return Addon_Images.zombatar_hats_button;
        case ZombatarWidget::BACKGROUND:
            return Addon_Images.zombatar_backdrops_button;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetTabButtonDownImageByIndex(int index) {
    switch (index) {
        case ZombatarWidget::SKIN:
            return Addon_Images.zombatar_skin_button_highlight;
        case ZombatarWidget::HAIR:
            return Addon_Images.zombatar_hair_button_highlight;
        case ZombatarWidget::FHAIR:
            return Addon_Images.zombatar_fhair_button_highlight;
        case ZombatarWidget::TIDBIT:
            return Addon_Images.zombatar_tidbits_button_highlight;
        case ZombatarWidget::EYEWEAR:
            return Addon_Images.zombatar_eyewear_button_highlight;
        case ZombatarWidget::CLOTHES:
            return Addon_Images.zombatar_clothes_button_highlight;
        case ZombatarWidget::ACCESSORY:
            return Addon_Images.zombatar_accessory_button_highlight;
        case ZombatarWidget::HAT:
            return Addon_Images.zombatar_hats_button_highlight;
        case ZombatarWidget::BACKGROUND:
            return Addon_Images.zombatar_backdrops_button_highlight;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetHairImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_hair_1;
        case 1:
            return Addon_Images.zombatar_hair_2;
        case 2:
            return Addon_Images.zombatar_hair_3;
        case 3:
            return Addon_Images.zombatar_hair_4;
        case 4:
            return Addon_Images.zombatar_hair_5;
        case 5:
            return Addon_Images.zombatar_hair_6;
        case 6:
            return Addon_Images.zombatar_hair_7;
        case 7:
            return Addon_Images.zombatar_hair_8;
        case 8:
            return Addon_Images.zombatar_hair_9;
        case 9:
            return Addon_Images.zombatar_hair_10;
        case 10:
            return Addon_Images.zombatar_hair_11;
        case 11:
            return Addon_Images.zombatar_hair_12;
        case 12:
            return Addon_Images.zombatar_hair_13;
        case 13:
            return Addon_Images.zombatar_hair_14;
        case 14:
            return Addon_Images.zombatar_hair_15;
        case 15:
            return Addon_Images.zombatar_hair_16;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetHairMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_hair_1_mask;
        case 1:
            return Addon_Images.zombatar_hair_2_mask;
        case 10:
            return Addon_Images.zombatar_hair_11_mask;
        case 11:
            return Addon_Images.zombatar_hair_12_mask;
        case 12:
            return Addon_Images.zombatar_hair_13_mask;
        case 13:
            return Addon_Images.zombatar_hair_14_mask;
        case 14:
            return Addon_Images.zombatar_hair_15_mask;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetFHairImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_facialhair_1;
        case 1:
            return Addon_Images.zombatar_facialhair_2;
        case 2:
            return Addon_Images.zombatar_facialhair_3;
        case 3:
            return Addon_Images.zombatar_facialhair_4;
        case 4:
            return Addon_Images.zombatar_facialhair_5;
        case 5:
            return Addon_Images.zombatar_facialhair_6;
        case 6:
            return Addon_Images.zombatar_facialhair_7;
        case 7:
            return Addon_Images.zombatar_facialhair_8;
        case 8:
            return Addon_Images.zombatar_facialhair_9;
        case 9:
            return Addon_Images.zombatar_facialhair_10;
        case 10:
            return Addon_Images.zombatar_facialhair_11;
        case 11:
            return Addon_Images.zombatar_facialhair_12;
        case 12:
            return Addon_Images.zombatar_facialhair_13;
        case 13:
            return Addon_Images.zombatar_facialhair_14;
        case 14:
            return Addon_Images.zombatar_facialhair_15;
        case 15:
            return Addon_Images.zombatar_facialhair_16;
        case 16:
            return Addon_Images.zombatar_facialhair_17;
        case 17:
            return Addon_Images.zombatar_facialhair_18;
        case 18:
            return Addon_Images.zombatar_facialhair_19;
        case 19:
            return Addon_Images.zombatar_facialhair_20;
        case 20:
            return Addon_Images.zombatar_facialhair_21;
        case 21:
            return Addon_Images.zombatar_facialhair_22;
        case 22:
            return Addon_Images.zombatar_facialhair_23;
        case 23:
            return Addon_Images.zombatar_facialhair_24;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetFHairMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_facialhair_1_mask;
        case 3:
            return Addon_Images.zombatar_facialhair_4_mask;
        case 7:
            return Addon_Images.zombatar_facialhair_8_mask;
        case 8:
            return Addon_Images.zombatar_facialhair_9_mask;
        case 9:
            return Addon_Images.zombatar_facialhair_10_mask;
        case 10:
            return Addon_Images.zombatar_facialhair_11_mask;
        case 11:
            return Addon_Images.zombatar_facialhair_12_mask;
        case 13:
            return Addon_Images.zombatar_facialhair_14_mask;
        case 14:
            return Addon_Images.zombatar_facialhair_15_mask;
        case 15:
            return Addon_Images.zombatar_facialhair_16_mask;
        case 17:
            return Addon_Images.zombatar_facialhair_18_mask;
        case 20:
            return Addon_Images.zombatar_facialhair_21_mask;
        case 21:
            return Addon_Images.zombatar_facialhair_22_mask;
        case 22:
            return Addon_Images.zombatar_facialhair_23_mask;
        case 23:
            return Addon_Images.zombatar_facialhair_24_mask;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetTidBitImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_tidbits_1;
        case 1:
            return Addon_Images.zombatar_tidbits_2;
        case 2:
            return Addon_Images.zombatar_tidbits_3;
        case 3:
            return Addon_Images.zombatar_tidbits_4;
        case 4:
            return Addon_Images.zombatar_tidbits_5;
        case 5:
            return Addon_Images.zombatar_tidbits_6;
        case 6:
            return Addon_Images.zombatar_tidbits_7;
        case 7:
            return Addon_Images.zombatar_tidbits_8;
        case 8:
            return Addon_Images.zombatar_tidbits_9;
        case 9:
            return Addon_Images.zombatar_tidbits_10;
        case 10:
            return Addon_Images.zombatar_tidbits_11;
        case 11:
            return Addon_Images.zombatar_tidbits_12;
        case 12:
            return Addon_Images.zombatar_tidbits_13;
        case 13:
            return Addon_Images.zombatar_tidbits_14;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetEyeWearImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_eyewear_1;
        case 1:
            return Addon_Images.zombatar_eyewear_2;
        case 2:
            return Addon_Images.zombatar_eyewear_3;
        case 3:
            return Addon_Images.zombatar_eyewear_4;
        case 4:
            return Addon_Images.zombatar_eyewear_5;
        case 5:
            return Addon_Images.zombatar_eyewear_6;
        case 6:
            return Addon_Images.zombatar_eyewear_7;
        case 7:
            return Addon_Images.zombatar_eyewear_8;
        case 8:
            return Addon_Images.zombatar_eyewear_9;
        case 9:
            return Addon_Images.zombatar_eyewear_10;
        case 10:
            return Addon_Images.zombatar_eyewear_11;
        case 11:
            return Addon_Images.zombatar_eyewear_12;
        case 12:
            return Addon_Images.zombatar_eyewear_13;
        case 13:
            return Addon_Images.zombatar_eyewear_14;
        case 14:
            return Addon_Images.zombatar_eyewear_15;
        case 15:
            return Addon_Images.zombatar_eyewear_16;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetEyeWearMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_eyewear_1_mask;
        case 1:
            return Addon_Images.zombatar_eyewear_2_mask;
        case 2:
            return Addon_Images.zombatar_eyewear_3_mask;
        case 3:
            return Addon_Images.zombatar_eyewear_4_mask;
        case 4:
            return Addon_Images.zombatar_eyewear_5_mask;
        case 5:
            return Addon_Images.zombatar_eyewear_6_mask;
        case 6:
            return Addon_Images.zombatar_eyewear_7_mask;
        case 7:
            return Addon_Images.zombatar_eyewear_8_mask;
        case 8:
            return Addon_Images.zombatar_eyewear_9_mask;
        case 9:
            return Addon_Images.zombatar_eyewear_10_mask;
        case 10:
            return Addon_Images.zombatar_eyewear_11_mask;
        case 11:
            return Addon_Images.zombatar_eyewear_12_mask;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetClothImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_clothes_1;
        case 1:
            return Addon_Images.zombatar_clothes_2;
        case 2:
            return Addon_Images.zombatar_clothes_3;
        case 3:
            return Addon_Images.zombatar_clothes_4;
        case 4:
            return Addon_Images.zombatar_clothes_5;
        case 5:
            return Addon_Images.zombatar_clothes_6;
        case 6:
            return Addon_Images.zombatar_clothes_7;
        case 7:
            return Addon_Images.zombatar_clothes_8;
        case 8:
            return Addon_Images.zombatar_clothes_9;
        case 9:
            return Addon_Images.zombatar_clothes_10;
        case 10:
            return Addon_Images.zombatar_clothes_11;
        case 11:
            return Addon_Images.zombatar_clothes_12;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetAccessoryImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_accessory_1;
        case 1:
            return Addon_Images.zombatar_accessory_2;
        case 2:
            return Addon_Images.zombatar_accessory_3;
        case 3:
            return Addon_Images.zombatar_accessory_4;
        case 4:
            return Addon_Images.zombatar_accessory_5;
        case 5:
            return Addon_Images.zombatar_accessory_6;
        case 6:
            return Addon_Images.zombatar_accessory_8;
        case 7:
            return Addon_Images.zombatar_accessory_9;
        case 8:
            return Addon_Images.zombatar_accessory_10;
        case 9:
            return Addon_Images.zombatar_accessory_11;
        case 10:
            return Addon_Images.zombatar_accessory_12;
        case 11:
            return Addon_Images.zombatar_accessory_13;
        case 12:
            return Addon_Images.zombatar_accessory_14;
        case 13:
            return Addon_Images.zombatar_accessory_15;
        case 14:
            return Addon_Images.zombatar_accessory_16;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetHatImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_hats_1;
        case 1:
            return Addon_Images.zombatar_hats_2;
        case 2:
            return Addon_Images.zombatar_hats_3;
        case 3:
            return Addon_Images.zombatar_hats_4;
        case 4:
            return Addon_Images.zombatar_hats_5;
        case 5:
            return Addon_Images.zombatar_hats_6;
        case 6:
            return Addon_Images.zombatar_hats_7;
        case 7:
            return Addon_Images.zombatar_hats_8;
        case 8:
            return Addon_Images.zombatar_hats_9;
        case 9:
            return Addon_Images.zombatar_hats_10;
        case 10:
            return Addon_Images.zombatar_hats_11;
        case 11:
            return Addon_Images.zombatar_hats_12;
        case 12:
            return Addon_Images.zombatar_hats_13;
        case 13:
            return Addon_Images.zombatar_hats_14;
        default:
            return NULL;
    }
}

Sexy::Image *ZombatarWidget_GetHatMaskImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_hats_1_mask;
        case 2:
            return Addon_Images.zombatar_hats_3_mask;
        case 5:
            return Addon_Images.zombatar_hats_6_mask;
        case 6:
            return Addon_Images.zombatar_hats_7_mask;
        case 7:
            return Addon_Images.zombatar_hats_8_mask;
        case 8:
            return Addon_Images.zombatar_hats_9_mask;
        case 10:
            return Addon_Images.zombatar_hats_11_mask;
        default:
            return NULL;
    }
}
Sexy::Image *ZombatarWidget_GetBackgroundImageByIndex(int index) {
    switch (index) {
        case 0:
            return Addon_Images.zombatar_background_blank;
        case 1:
            return Addon_Images.zombatar_background_hood;
        case 2:
            return Addon_Images.zombatar_background_hood_blue;
        case 3:
            return Addon_Images.zombatar_background_hood_brown;
        case 4:
            return Addon_Images.zombatar_background_hood_yellow;
        case 5:
            return Addon_Images.zombatar_background_crazydave;
        case 6:
            return Addon_Images.zombatar_background_crazydave_night;
        case 7:
            return Addon_Images.zombatar_background_menu_dos;
        case 8:
            return Addon_Images.zombatar_background_menu;
        case 9:
            return Addon_Images.zombatar_background_sky_day;
        case 10:
            return Addon_Images.zombatar_background_sky_night;
        case 11:
            return Addon_Images.zombatar_background_mausoleum;
        case 12:
            return Addon_Images.zombatar_background_day_RV;
        case 13:
            return Addon_Images.zombatar_background_night_RV;
        case 14:
            return Addon_Images.zombatar_background_pool_sunshade;
        case 15:
            return Addon_Images.zombatar_background_fog_sunshade;
        case 16:
            return Addon_Images.zombatar_background_roof;
        case 17:
            return Addon_Images.zombatar_background_roof_distant;
        case 18:
            return Addon_Images.zombatar_background_moon;
        case 19:
            return Addon_Images.zombatar_background_moon_distant;
        case 20:
            return Addon_Images.zombatar_background_aquarium;
        case 21:
            return Addon_Images.zombatar_background_garden_moon;
        case 22:
            return Addon_Images.zombatar_background_garden_mushrooms;
        case 23:
            return Addon_Images.zombatar_background_garden_hd;
        case 24:
            return Addon_Images.zombatar_background_sky_purple;
        case 25:
            return Addon_Images.zombatar_background_7;
        case 26:
            return Addon_Images.zombatar_background_8;
        case 27:
            return Addon_Images.zombatar_background_9;
        case 28:
            return Addon_Images.zombatar_background_10;
        case 29:
            return Addon_Images.zombatar_background_11;
        case 30:
            return Addon_Images.zombatar_background_11_1;
        case 31:
            return Addon_Images.zombatar_background_12;
        case 32:
            return Addon_Images.zombatar_background_12_1;
        case 33:
            return Addon_Images.zombatar_background_13;
        case 34:
            return Addon_Images.zombatar_background_13_1;
        case 35:
            return Addon_Images.zombatar_background_14;
        case 36:
            return Addon_Images.zombatar_background_14_1;
        case 37:
            return Addon_Images.zombatar_background_15;
        case 38:
            return Addon_Images.zombatar_background_15_1;
        case 39:
            return Addon_Images.zombatar_background_16;
        case 40:
            return Addon_Images.zombatar_background_16_1;
        case 41:
            return Addon_Images.zombatar_background_17;
        case 42:
            return Addon_Images.zombatar_background_17_1;
        case 43:
            return Addon_Images.zombatar_background_bej3_bridge_shroom_castles;
        case 44:
            return Addon_Images.zombatar_background_bej3_canyon_wall;
        case 45:
            return Addon_Images.zombatar_background_bej3_crystal_mountain_peak;
        case 46:
            return Addon_Images.zombatar_background_bej3_dark_cave_thing;
        case 47:
            return Addon_Images.zombatar_background_bej3_desert_pyramids_sunset;
        case 48:
            return Addon_Images.zombatar_background_bej3_fairy_cave_village;
        case 49:
            return Addon_Images.zombatar_background_bej3_floating_rock_city;
        case 50:
            return Addon_Images.zombatar_background_bej3_horse_forset_tree;
        case 51:
            return Addon_Images.zombatar_background_bej3_jungle_ruins_path;
        case 52:
            return Addon_Images.zombatar_background_bej3_lantern_plants_world;
        case 53:
            return Addon_Images.zombatar_background_bej3_lightning;
        case 54:
            return Addon_Images.zombatar_background_bej3_lion_tower_cascade;
        case 55:
            return Addon_Images.zombatar_background_bej3_pointy_ice_path;
        case 56:
            return Addon_Images.zombatar_background_bej3_pointy_ice_path_purple;
        case 57:
            return Addon_Images.zombatar_background_bej3_rock_city_lake;
        case 58:
            return Addon_Images.zombatar_background_bej3_snowy_cliffs_castle;
        case 59:
            return Addon_Images.zombatar_background_bej3_treehouse_waterfall;
        case 60:
            return Addon_Images.zombatar_background_bej3_tube_forest_night;
        case 61:
            return Addon_Images.zombatar_background_bej3_water_bubble_city;
        case 62:
            return Addon_Images.zombatar_background_bej3_water_fall_cliff;
        case 63:
            return Addon_Images.zombatar_background_bejblitz_6;
        case 64:
            return Addon_Images.zombatar_background_bejblitz_8;
        case 65:
            return Addon_Images.zombatar_background_bejblitz_main_menu;
        case 66:
            return Addon_Images.zombatar_background_peggle_bunches;
        case 67:
            return Addon_Images.zombatar_background_peggle_fever;
        case 68:
            return Addon_Images.zombatar_background_peggle_level1;
        case 69:
            return Addon_Images.zombatar_background_peggle_level4;
        case 70:
            return Addon_Images.zombatar_background_peggle_level5;
        case 71:
            return Addon_Images.zombatar_background_peggle_menu;
        case 72:
            return Addon_Images.zombatar_background_peggle_nights_bjorn3;
        case 73:
            return Addon_Images.zombatar_background_peggle_nights_bjorn4;
        case 74:
            return Addon_Images.zombatar_background_peggle_nights_claude5;
        case 75:
            return Addon_Images.zombatar_background_peggle_nights_kalah1;
        case 76:
            return Addon_Images.zombatar_background_peggle_nights_kalah4;
        case 77:
            return Addon_Images.zombatar_background_peggle_nights_master5;
        case 78:
            return Addon_Images.zombatar_background_peggle_nights_renfield5;
        case 79:
            return Addon_Images.zombatar_background_peggle_nights_tut5;
        case 80:
            return Addon_Images.zombatar_background_peggle_nights_warren3;
        case 81:
            return Addon_Images.zombatar_background_peggle_paperclips;
        case 82:
            return Addon_Images.zombatar_background_peggle_waves;
        default:
            return NULL;
    }
}

int ZombatarWidget_GetTidBitImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 35;
        case 1:
            return 35;
        case 2:
            return 55;
        case 3:
            return 38;
        case 4:
            return 40;
        case 5:
            return 34;
        case 6:
            return 33;
        case 7:
            return 40;
        case 8:
            return 26;
        case 9:
            return 44;
        case 10:
            return 43;
        case 11:
            return 103;
        case 12:
            return 106;
        case 13:
            return 136;
        default:
            return 0;
    }
}

int ZombatarWidget_GetTidBitImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 76;
        case 1:
            return 76;
        case 2:
            return 133;
        case 3:
            return 74;
        case 4:
            return 70;
        case 5:
            return 79;
        case 6:
            return 86;
        case 7:
            return 66;
        case 8:
            return 91;
        case 9:
            return 86;
        case 10:
            return 84;
        case 11:
            return 110;
        case 12:
            return 60;
        case 13:
            return 137;
        default:
            return 0;
    }
}

int ZombatarWidget_GetEyeWearImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 34;
        case 1:
            return 38;
        case 2:
            return 34;
        case 3:
            return 34;
        case 4:
            return 37;
        case 5:
            return 36;
        case 6:
            return 61;
        case 7:
            return 39;
        case 8:
            return 44;
        case 9:
            return 37;
        case 10:
            return 37;
        case 11:
            return 46;
        case 12:
            return 36;
        case 13:
            return 41;
        case 14:
            return 50;
        case 15:
            return 41;
        default:
            return 0;
    }
}

int ZombatarWidget_GetEyeWearImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 87;
        case 1:
            return 101;
        case 2:
            return 84;
        case 3:
            return 94;
        case 4:
            return 91;
        case 5:
            return 92;
        case 6:
            return 107;
        case 7:
            return 84;
        case 8:
            return 120;
        case 9:
            return 89;
        case 10:
            return 80;
        case 11:
            return 113;
        case 12:
            return 97;
        case 13:
            return 77;
        case 14:
            return 78;
        case 15:
            return 78;
        default:
            return 0;
    }
}

int ZombatarWidget_GetAccessoryImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 124;
        case 1:
            return 130;
        case 2:
            return 103;
        case 3:
            return 157;
        case 4:
            return 158;
        case 5:
            return 158;
        case 6:
            return 126;
        case 7:
            return 144;
        case 8:
            return 74;
        case 9:
            return 52;
        case 10:
            return 163;
        case 11:
            return 94;
        case 12:
            return 83;
        case 13:
            return 160;
        case 14:
            return 16;
        default:
            return 0;
    }
}

int ZombatarWidget_GetAccessoryImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 132;
        case 1:
            return 132;
        case 2:
            return 135;
        case 3:
            return 115;
        case 4:
            return 120;
        case 5:
            return 120;
        case 6:
            return 132;
        case 7:
            return 80;
        case 8:
            return 141;
        case 9:
            return 119;
        case 10:
            return 110;
        case 11:
            return 157;
        case 12:
            return 174;
        case 13:
            return 84;
        case 14:
            return 48;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 42;
        case 1:
            return 61;
        case 2:
            return 54;
        case 3:
            return 46;
        case 4:
            return 85;
        case 5:
            return 59;
        case 6:
            return 16;
        case 7:
            return 54;
        case 8:
            return 51;
        case 9:
            return 54;
        case 10:
            return 52;
        case 11:
            return 35;
        case 12:
            return 52;
        case 13:
            return 23;
        case 14:
            return 76;
        case 15:
            return 76;
        case 16:
            return 52;
        case 17:
            return 71;
        case 18:
            return 55;
        case 19:
            return 137;
        case 20:
            return 141;
        case 21:
            return 18;
        case 22:
            return 71;
        case 23:
            return 46;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 129;
        case 1:
            return 132;
        case 2:
            return 132;
        case 3:
            return 126;
        case 4:
            return 174;
        case 5:
            return 135;
        case 6:
            return 128;
        case 7:
            return 125;
        case 8:
            return 126;
        case 9:
            return 134;
        case 10:
            return 105;
        case 11:
            return 125;
        case 12:
            return 131;
        case 13:
            return 122;
        case 14:
            return 174;
        case 15:
            return 168;
        case 16:
            return 132;
        case 17:
            return 115;
        case 18:
            return 110;
        case 19:
            return 96;
        case 20:
            return 102;
        case 21:
            return 104;
        case 22:
            return 174;
        case 23:
            return 129;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairMaskImageOffsetXByIndex(int index) {
    switch (index) {
        case 3:
            return 3;
        case 7:
            return 1;
        case 10:
            return 1;
        case 11:
            return 9;
        case 13:
            return 2;
        case 14:
            return 2;
        case 17:
            return 2;
        case 21:
            return 4;
        case 22:
            return 1;
        case 23:
            return 4;
        default:
            return 0;
    }
}

int ZombatarWidget_GetFHairMaskImageOffsetYByIndex(int index) {
    switch (index) {
        case 3:
            return 1;
        case 9:
            return 1;
        case 10:
            return 3;
        case 11:
            return 1;
        case 13:
            return 1;
        case 17:
            return 2;
        case 21:
            return 3;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 28;
        case 1:
            return 29;
        case 2:
            return 28;
        case 3:
            return 35;
        case 4:
            return 44;
        case 5:
            return 47;
        case 6:
            return 61;
        case 7:
            return 33;
        case 8:
            return 154;
        case 9:
            return 27;
        case 10:
            return 30;
        case 11:
            return 60;
        case 12:
            return 39;
        case 13:
            return 9;
        case 14:
            return 55;
        case 15:
            return 31;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 0;
        case 1:
            return 31;
        case 2:
            return 36;
        case 3:
            return 17;
        case 4:
            return 45;
        case 5:
            return 16;
        case 6:
            return 26;
        case 7:
            return 17;
        case 8:
            return 66;
        case 9:
            return 37;
        case 10:
            return 22;
        case 11:
            return -5;
        case 12:
            return 16;
        case 13:
            return -2;
        case 14:
            return 4;
        case 15:
            return 23;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairMaskImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 10;
        case 1:
            return 2;
        case 10:
            return 2;
        case 11:
            return 2;
        case 12:
            return 2;
        case 13:
            return 2;
        case 14:
            return -1;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHairMaskImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 2;
        case 1:
            return 3;
        case 10:
            return 2;
        case 11:
            return 2;
        case 12:
            return 1;
        case 13:
            return 5;
        default:
            return 0;
    }
}

int ZombatarWidget_GetClothImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return  - Addon_Images.zombatar_clothes_1->mWidth + 2;
        case 1:
            return  - Addon_Images.zombatar_clothes_2->mWidth + 11;
        case 2:
            return  - Addon_Images.zombatar_clothes_3->mWidth + 1;
        case 3:
            return  - Addon_Images.zombatar_clothes_4->mWidth + 1;
        case 4:
            return  - Addon_Images.zombatar_clothes_5->mWidth + 0;
        case 5:
            return  - Addon_Images.zombatar_clothes_6->mWidth - 20;
        case 6:
            return  - Addon_Images.zombatar_clothes_7->mWidth + 3;
        case 7:
            return  - Addon_Images.zombatar_clothes_8->mWidth + 2;
        case 8:
            return  - Addon_Images.zombatar_clothes_9->mWidth + 10;
        case 9:
            return  - Addon_Images.zombatar_clothes_10->mWidth + 3;
        case 10:
            return  - Addon_Images.zombatar_clothes_11->mWidth + 1;
        case 11:
            return  - Addon_Images.zombatar_clothes_12->mWidth + 3;
        default:
            return 0;
    }
}

int ZombatarWidget_GetClothImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return  - Addon_Images.zombatar_clothes_1->mHeight + 0;
        case 1:
            return  - Addon_Images.zombatar_clothes_2->mHeight + 6;
        case 2:
            return  - Addon_Images.zombatar_clothes_3->mHeight + 0;
        case 3:
            return  - Addon_Images.zombatar_clothes_4->mHeight + 2;
        case 4:
            return  - Addon_Images.zombatar_clothes_5->mHeight + 2;
        case 5:
            return  - Addon_Images.zombatar_clothes_6->mHeight - 24;
        case 6:
            return  - Addon_Images.zombatar_clothes_7->mHeight + 2;
        case 7:
            return  - Addon_Images.zombatar_clothes_8->mHeight + 4;
        case 8:
            return  - Addon_Images.zombatar_clothes_9->mHeight + 3;
        case 9:
            return  - Addon_Images.zombatar_clothes_10->mHeight + 2;
        case 10:
            return  - Addon_Images.zombatar_clothes_11->mHeight + 2;
        case 11:
            return  - Addon_Images.zombatar_clothes_12->mHeight + 3;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 33;
        case 1:
            return 58;
        case 2:
            return 44;
        case 3:
            return 12;
        case 4:
            return 49;
        case 5:
            return 22;
        case 6:
            return 64;
        case 7:
            return 4;
        case 8:
            return 45;
        case 9:
            return 17;
        case 10:
            return 76;
        case 11:
            return 51;
        case 12:
            return 22;
        case 13:
            return 28;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 5;
        case 1:
            return 14;
        case 2:
            return 25;
        case 3:
            return 12;
        case 4:
            return 20;
        case 5:
            return 5;
        case 6:
            return 21;
        case 7:
            return -1;
        case 8:
            return -1;
        case 9:
            return 56;
        case 10:
            return 10;
        case 11:
            return 16;
        case 12:
            return 0;
        case 13:
            return 6;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatMaskImageOffsetXByIndex(int index) {
    switch (index) {
        case 0:
            return 1;
        case 2:
            return 18;
        case 5:
            return 5;
        case 7:
            return -3;
        case 8:
            return -1;
        case 10:
            return 1;
        default:
            return 0;
    }
}

int ZombatarWidget_GetHatMaskImageOffsetYByIndex(int index) {
    switch (index) {
        case 0:
            return 1;
        case 5:
            return -2;
        case 6:
            return 17;
        case 7:
            return -3;
        case 8:
            return -2;
        case 10:
            return 16;
        default:
            return 0;
    }
}

bool ZombatarWidget_AccessoryIsColorized(int tab, int accessory) {
    switch (tab) {
        case ZombatarWidget::HAIR:
            return accessory != 2;
        case ZombatarWidget::FHAIR:
            return true;
        case ZombatarWidget::TIDBIT:
            return accessory == 0 || accessory == 1 || accessory == 2 || accessory == 9 || accessory == 10 || accessory == 11;
        case ZombatarWidget::EYEWEAR:
            return accessory <= 11;
        case ZombatarWidget::CLOTHES:
            return false;
        case ZombatarWidget::ACCESSORY:
            return accessory == 7 || accessory == 9 || accessory == 11 || accessory == 12;
        case ZombatarWidget::HAT:
            return accessory != 12;
        case ZombatarWidget::BACKGROUND:
            return accessory == 0;
        default:
            return false;
    }
}



void ZombatarWidget_ZombatarWidget(ZombatarWidget* zombatarWidget, LawnApp* lawnApp) {
    TestMenuWidget_TestMenuWidget(zombatarWidget);
    LawnApp_LoadZombatarResources(lawnApp);
    LawnApp_Load(lawnApp,"DelayLoad_Almanac");
    zombatarWidget->mApp = lawnApp;
    Sexy::ButtonListener* mZombatarListener = (Sexy::ButtonListener*) operator new(sizeof (Sexy::ButtonListener));
    zombatarWidget->mButtonListener = mZombatarListener;
    Sexy::ButtonListenerVTable* mVTable = (Sexy::ButtonListenerVTable*) operator new(sizeof (Sexy::ButtonListenerVTable));
    mZombatarListener->vTable = mVTable;
//    mVTable->ButtonPress = (void *) ZombatarWidget_ButtonPress;
    mVTable->ButtonPress2 = (void *) ZombatarWidget_ButtonPress;
    mVTable->ButtonDepress = (void *) ZombatarWidget_ButtonDepress;
    mVTable->ButtonMouseEnter = (void *) Sexy_ButtonListener_ButtonMouseEnter;
    mVTable->ButtonMouseMove = (void *) Sexy_ButtonListener_ButtonMouseMove;
    mVTable->ButtonMouseLeave = (void *) Sexy_ButtonListener_ButtonMouseLeave;
    mVTable->ButtonDownTick = (void *) Sexy_ButtonListener_ButtonDownTick;

    int holder[1];
    Sexy_StrFormat(holder,"[CLOSE]");
    Sexy::GameButton *backButton = MakeButton(1000,mZombatarListener,zombatarWidget,holder);
    Sexy_String_Delete(holder);
    Sexy_Widget_Resize(backButton,471,628,Addon_Images.zombatar_mainmenuback_highlight->mWidth,Addon_Images.zombatar_mainmenuback_highlight->mHeight);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 6))(zombatarWidget, backButton); // AddWidget()
    backButton->mDrawStoneButton = false;
    backButton->mButtonImage = *Sexy_IMAGE_BLANK_Addr;
    backButton->mDownImage = Addon_Images.zombatar_mainmenuback_highlight;
    backButton->mOverImage = Addon_Images.zombatar_mainmenuback_highlight;
    zombatarWidget->mBackButton = backButton;

    int holder1[1];
    Sexy_StrFormat(holder1,"[OK]");
    Sexy::GameButton *finishButton = MakeButton(1001,mZombatarListener,NULL,holder1);
    Sexy_String_Delete(holder1);
    Sexy_Widget_Resize(finishButton,160 + 523,565,Addon_Images.zombatar_finished_button->mWidth,Addon_Images.zombatar_finished_button->mHeight);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 6))(zombatarWidget, finishButton); // AddWidget()
    finishButton->mDrawStoneButton = false;
    finishButton->mButtonImage = Addon_Images.zombatar_finished_button;
    finishButton->mDownImage = Addon_Images.zombatar_finished_button_highlight;
    finishButton->mOverImage = Addon_Images.zombatar_finished_button_highlight;
    zombatarWidget->mFinishButton = finishButton;


    int holder2[1];
    Sexy_StrFormat(holder2,"[OK]");
    Sexy::GameButton *viewPortraitButton = MakeButton(1002,mZombatarListener,NULL,holder2);
    Sexy_String_Delete(holder2);
    Sexy_Widget_Resize(viewPortraitButton,160 + 75,565,Addon_Images.zombatar_view_button->mWidth,Addon_Images.zombatar_view_button->mHeight);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 6))(zombatarWidget, viewPortraitButton); // AddWidget()
    viewPortraitButton->mDrawStoneButton = false;
    viewPortraitButton->mButtonImage = Addon_Images.zombatar_view_button;
    viewPortraitButton->mDownImage = Addon_Images.zombatar_view_button_highlight;
    viewPortraitButton->mOverImage = Addon_Images.zombatar_view_button_highlight;
    zombatarWidget->mViewPortraitButton = viewPortraitButton;

    int holder3[1];
    Sexy_StrFormat(holder3,"[ZOMBATAR_NEW_BUTTON]");
    Sexy::GameButton *newButton = MakeButton(1003,mZombatarListener,NULL,holder3);
    Sexy_String_Delete(holder3);
    Sexy_Widget_Resize(newButton,578,490,170,50);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 6))(zombatarWidget, newButton); // AddWidget()
    zombatarWidget->mNewButton = newButton;


    int holder4[1];
    Sexy_StrFormat(holder4,"[ZOMBATAR_DELETE_BUTTON]");
    Sexy::GameButton *deleteButton = MakeButton(1004,mZombatarListener,NULL,holder4);
    Sexy_String_Delete(holder4);
    Sexy_Widget_Resize(deleteButton,314,490,170,50);
    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 6))(zombatarWidget, deleteButton); // AddWidget()
    zombatarWidget->mDeleteButton = deleteButton;


    Zombie* zombie = (Zombie*) operator new(sizeof(Zombie));
    Zombie_Zombie(zombie);
    zombie->mBoard = NULL;
    Zombie_ZombieInitialize(zombie,0,ZombieType::Flag,false,NULL,-3,true);
    Reanimation* aBodyReanim = LawnApp_ReanimationGet(zombie->mApp,zombie->mBodyReanimID);
    ReanimatorTrackInstance* aHeadTrackInstance = Reanimation_GetTrackInstanceByName(aBodyReanim, "anim_head1");
    aHeadTrackInstance->mImageOverride = *Sexy_IMAGE_BLANK_Addr;

    Reanimation *aZombatarHeadReanim = LawnApp_AddReanimation(lawnApp, 0, 0, 0, ReanimationType::ZombatarHead);
    Reanimation_PlayReanim(aZombatarHeadReanim, "anim_head_idle", ReanimLoopType::Loop, 0, 15.0);
    Reanimation_AssignRenderGroupToTrack(aZombatarHeadReanim, "anim_hair", -1);
    zombie->mBossFireBallReanimID = LawnApp_ReanimationGetID(zombie->mApp, aZombatarHeadReanim);
    AttachEffect* attachEffect = AttachReanim(&aHeadTrackInstance->mAttachmentID, aZombatarHeadReanim, 0.0f, 0.0f);
    TodScaleRotateTransformMatrix(&attachEffect->mOffset, -20.0, -1.0, 0.2, 1.0, 1.0);
    zombatarWidget->mZombatarReanim = aZombatarHeadReanim;
    Zombie_ReanimShowPrefix(zombie, "anim_hair", -1);
    Zombie_ReanimShowPrefix(zombie, "anim_head2", -1);
    Zombie_Update(zombie);
    zombatarWidget->mPreviewZombie = zombie;

    zombatarWidget->mShowExistingZombatarPortrait = Addon_Images.zombatar_portrait != NULL;
    mMainMenuZombatarWidget->mShowZombieTypeSelection = false;

    ZombatarWidget_SetDefault(zombatarWidget);

}

void TestMenuWidget_Update(ZombatarWidget* zombatarWidget) {
    (*((void (__fastcall **)(Sexy::Widget *))zombatarWidget->vTable + 25))(zombatarWidget); // MarkDirty();
    Zombie_Update(zombatarWidget->mPreviewZombie);
    zombatarWidget->mFinishButton->mDisabled = zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mFinishButton->mBtnNoDraw = zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mViewPortraitButton->mDisabled = zombatarWidget->mShowExistingZombatarPortrait || Addon_Images.zombatar_portrait == NULL;
    zombatarWidget->mViewPortraitButton->mBtnNoDraw = zombatarWidget->mShowExistingZombatarPortrait || Addon_Images.zombatar_portrait == NULL;
    zombatarWidget->mNewButton->mDisabled = !zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mNewButton->mBtnNoDraw = !zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mDeleteButton->mDisabled = !zombatarWidget->mShowExistingZombatarPortrait;
    zombatarWidget->mDeleteButton->mBtnNoDraw = !zombatarWidget->mShowExistingZombatarPortrait;

}

void TestMenuWidget_DrawZombieSelection(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    //  TODO:做僵尸选择功能
    ZombieType::ZombieType types[] = {ZombieType::Normal, ZombieType::Flag, ZombieType::TrafficCone,
                                      ZombieType::Door, ZombieType::TrashBin, ZombieType::Pail,
                                      ZombieType::DuckyTube};
}

void TestMenuWidget_DrawSkin(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 285 + (i % 9) * 30;
        int theY = 432 + i / 9 * 30;
        Color color = gZombatarSkinColor[i];
        if (zombatarWidget->mSelectedSkinColor != i) {
            color.mAlpha = 64;
        }
        Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_colorpicker, &color, theX, theY);
    }

    int holder[1];
    TodStringTranslate(holder,"[ZOMBATAR_START_TEXT]");
    TRect rect = {160 + 295,211,250,100};
    Sexy::Font* font = *Sexy_FONT_DWARVENTODCRAFT18_Addr;
    TodDrawStringWrapped(graphics,holder,&rect,font,&yellow,DrawStringJustification::Center,false);
    Sexy_String_Delete(holder);
}

void TestMenuWidget_DrawHair(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255,255,255,64};
    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image* image = ZombatarWidget_GetHairImageByIndex(i);
        Sexy::Image* image1 = ZombatarWidget_GetHairMaskImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth,mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3) ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedHair == i) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
            if (image1 != NULL) {
                int widthOffset2 = ZombatarWidget_GetHairMaskImageOffsetXByIndex(i);
                int heightOffset2 = ZombatarWidget_GetHairMaskImageOffsetYByIndex(i);
                TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
            }
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            if (image1 != NULL) {
                int widthOffset2 = ZombatarWidget_GetHairMaskImageOffsetXByIndex(i);
                int heightOffset2 = ZombatarWidget_GetHairMaskImageOffsetYByIndex(i);
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image1,&theAlphaColor,  theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
            }
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        }

    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedHair == 255) {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedHair)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor[i];
            if (zombatarWidget->mSelectedHairColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? Addon_Images.zombatar_colorpicker_none : Addon_Images.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawFHair(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    if (zombatarWidget->mSelectedFHairPage == 0) {
        Color theAlphaColor = {255,255,255,64};
        for (int i = 0; i < 17; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            Sexy::Image* image = ZombatarWidget_GetFHairImageByIndex(i);
            Sexy::Image* image1 = ZombatarWidget_GetFHairMaskImageByIndex(i);
            int mWidth = image->mWidth;
            int mHeight = image->mHeight;
            int max = std::max(mWidth,mHeight);
            float ratio = 58.0 / max;
            if (ratio > 1.3) ratio = 1.3;
            float widthOffset = (58 - ratio * mWidth) / 2;
            float heightOffset = (58 - ratio * mHeight) / 2;

            if (zombatarWidget->mSelectedFHair == i) {
                Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
                if (image1 != NULL) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i);
                    TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
                if (image1 != NULL) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i);
                    Sexy_Graphics_DrawImageColorizedScaled(graphics, image1,&theAlphaColor,  theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
        }
        int theX = 160 + 198 + (17 % 6) * 73;
        int theY = 162 + 17 / 6 * 79;
        Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);
        Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_prev_button, &theAlphaColor, 160 + 209, 436);
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_next_button, 160 + 588, 436);
    } else if (zombatarWidget->mSelectedFHairPage == 1) {
        Color theAlphaColor = {255,255,255,64};
        for (int i = 0; i < 7; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            Sexy::Image* image = ZombatarWidget_GetFHairImageByIndex(i + 17);
            Sexy::Image* image1 = ZombatarWidget_GetFHairMaskImageByIndex(i + 17);
            int mWidth = image->mWidth;
            int mHeight = image->mHeight;
            int max = std::max(mWidth,mHeight);
            float ratio = 58.0 / max;
            if (ratio > 1.3) ratio = 1.3;
            float widthOffset = (58 - ratio * mWidth) / 2;
            float heightOffset = (58 - ratio * mHeight) / 2;

            if (zombatarWidget->mSelectedFHair == i + 17) {
                Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
                if (image1 != NULL) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i + 17);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i + 17);
                    TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
                if (image1 != NULL) {
                    int widthOffset2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(i + 17);
                    int heightOffset2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(i + 17);
                    Sexy_Graphics_DrawImageColorizedScaled(graphics, image1,&theAlphaColor,  theX + 12 + widthOffset + widthOffset2 * ratio, theY + 12 + heightOffset + heightOffset2 * ratio, ratio, ratio);
                }
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
        }
        int theX = 160 + 198 + (7 % 6) * 73;
        int theY = 162 + 7 / 6 * 79;
        Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_prev_button,160 + 209,436);
        Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_next_button,&theAlphaColor,160 + 588,436);
    }

    if (zombatarWidget->mSelectedFHair == 255) {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedFHair)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor[i];
            if (zombatarWidget->mSelectedFHairColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? Addon_Images.zombatar_colorpicker_none : Addon_Images.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }

    int holder[1];
    Sexy_StrFormat(holder, "PAGE %d/%d", zombatarWidget->mSelectedFHairPage + 1 , 2);
    TodDrawString(graphics, holder, 160 + 410, 525, *Sexy_FONT_BRIANNETOD16_Addr, black, DrawStringJustification::Center);
    Sexy_String_Delete(holder);
}

void TestMenuWidget_DrawTidBit(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255,255,255,64};
    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image* image = ZombatarWidget_GetTidBitImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth,mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3) ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedTidBit == i) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            if (i == 0) {
                TodDrawImageScaledF(graphics, ZombatarWidget_GetTidBitImageByIndex(2), theX + 23, theY + 44, ratio, ratio);
            }
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            if (i == 0) {
                Sexy_Graphics_DrawImageColorizedScaled(graphics, ZombatarWidget_GetTidBitImageByIndex(2), &theAlphaColor,theX + 23, theY + 44, ratio, ratio);
            }
        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedTidBit == 255) {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedTidBit)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedTidBitColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? Addon_Images.zombatar_colorpicker_none : Addon_Images.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawEyeWear(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255,255,255,64};
    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image* image = ZombatarWidget_GetEyeWearImageByIndex(i);
        Sexy::Image* image1 = ZombatarWidget_GetEyeWearMaskImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth,mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3) ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedEyeWear == i) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
            if (image1 != NULL) {
                TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            if (image1 != NULL) {
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image1,&theAlphaColor,  theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            }
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedEyeWear == 255) {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedEyeWear)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedEyeWearColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? Addon_Images.zombatar_colorpicker_none : Addon_Images.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawCloth(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255,255,255,64};
    Color theAlphaColor2 = {255,255,255,128};
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image* image = Addon_Images.zombatar_zombie_blank_part;
        Sexy::Image* image1 = ZombatarWidget_GetClothImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth,mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3) ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;
        int offsetX = Addon_Images.zombatar_zombie_blank_part->mWidth + ZombatarWidget_GetClothImageOffsetXByIndex(i);
        int offsetY = Addon_Images.zombatar_zombie_blank_part->mHeight + ZombatarWidget_GetClothImageOffsetYByIndex(i);
        if (zombatarWidget->mSelectedCloth == i) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics,Addon_Images.zombatar_zombie_blank_skin_part, &gZombatarSkinColor[zombatarWidget->mSelectedSkinColor],theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            TodDrawImageScaledF(graphics,image1 ,theX + 12 + ratio * offsetX, theY + 12 + ratio * offsetY, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics,Addon_Images.zombatar_zombie_blank_skin_part, &gZombatarSkinColor[zombatarWidget->mSelectedSkinColor],theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
            Sexy_Graphics_DrawImageColorizedScaled(graphics,image1 ,&theAlphaColor2,theX + 12 + ratio * offsetX, theY + 12 + ratio * offsetY, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (12 % 6) * 73;
    int theY = 162 + 12 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedCloth == 255) {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawAccessory(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255,255,255,64};
    for (int i = 0; i < 15; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image* image = ZombatarWidget_GetAccessoryImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth,mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3) ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;

        if (zombatarWidget->mSelectedAccessory == i) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        }
    }
    int theX = 160 + 198 + (15 % 6) * 73;
    int theY = 162 + 15 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedAccessory == 255) {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedAccessory)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedAccessoryColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? Addon_Images.zombatar_colorpicker_none : Addon_Images.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawHat(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255,255,255,64};
    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        Sexy::Image* image = ZombatarWidget_GetHatImageByIndex(i);
        Sexy::Image* image1 = ZombatarWidget_GetHatMaskImageByIndex(i);
        int mWidth = image->mWidth;
        int mHeight = image->mHeight;
        int max = std::max(mWidth,mHeight);
        float ratio = 58.0 / max;
        if (ratio > 1.3) ratio = 1.3;
        float widthOffset = (58 - ratio * mWidth) / 2;
        float heightOffset = (58 - ratio * mHeight) / 2;
        float widthOffset2 = ZombatarWidget_GetHatMaskImageOffsetXByIndex(i) * ratio;
        float heightOffset2 = ZombatarWidget_GetHatMaskImageOffsetYByIndex(i) * ratio;

        if (zombatarWidget->mSelectedHat == i) {
            Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
            if (image1 != NULL) {
                TodDrawImageScaledF(graphics, image1, theX + 12 + widthOffset + widthOffset2, theY + 12 + heightOffset + heightOffset2, ratio, ratio);
            }
            TodDrawImageScaledF(graphics, image, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);
        } else {
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            if (image1 != NULL) {
                Sexy_Graphics_DrawImageColorizedScaled(graphics, image1,&theAlphaColor,  theX + 12 + widthOffset + widthOffset2, theY + 12 + heightOffset + heightOffset2, ratio, ratio);
            }
            Sexy_Graphics_DrawImageColorizedScaled(graphics, image, &theAlphaColor, theX + 12 + widthOffset, theY + 12 + heightOffset, ratio, ratio);

        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg_none, &theAlphaColor, theX, theY);

    if (zombatarWidget->mSelectedHat == 255) {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_ITEM_NOT_CHOSEN]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    } else if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedHat)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedHatColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? Addon_Images.zombatar_colorpicker_none : Addon_Images.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }
}

void TestMenuWidget_DrawBackground(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Color theAlphaColor = {255,255,255,64};
    if (zombatarWidget->mSelectedBackgroundPage == 0) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            if (zombatarWidget->mSelectedBackground == i) {
                Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
                TodDrawImageScaledF(graphics, ZombatarWidget_GetBackgroundImageByIndex(i), theX + 12,theY + 12,58.0/216.0,58.0/216.0);
            }
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, ZombatarWidget_GetBackgroundImageByIndex(i),&theAlphaColor, theX + 12,theY + 12,58.0/216.0,58.0/216.0);
        }
        Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_prev_button,&theAlphaColor,160 + 209,436);
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_next_button,160 + 588,436);
    } else if (zombatarWidget->mSelectedBackgroundPage == 4) {
        for (int i = 0; i < 11; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            if (zombatarWidget->mSelectedBackground == i + 18 * zombatarWidget->mSelectedBackgroundPage) {
                Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
                TodDrawImageScaledF(graphics, ZombatarWidget_GetBackgroundImageByIndex(i + 18 * zombatarWidget->mSelectedBackgroundPage), theX + 12,theY + 12,58.0/216.0,58.0/216.0);
            }
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, ZombatarWidget_GetBackgroundImageByIndex(i + 18 * zombatarWidget->mSelectedBackgroundPage),&theAlphaColor, theX + 12,theY + 12,58.0/216.0,58.0/216.0);
        }
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_prev_button,160 + 209,436);
        Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_next_button,&theAlphaColor,160 + 588,436);
    } else {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            if (zombatarWidget->mSelectedBackground == i + zombatarWidget->mSelectedBackgroundPage * 18) {
                Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_accessory_bg_highlight, theX, theY);
                TodDrawImageScaledF(graphics, ZombatarWidget_GetBackgroundImageByIndex(i + zombatarWidget->mSelectedBackgroundPage * 18), theX + 12,theY + 12,58.0/216.0,58.0/216.0);
            }
            Sexy_Graphics_DrawImageColorized(graphics, Addon_Images.zombatar_accessory_bg,&theAlphaColor, theX, theY);
            Sexy_Graphics_DrawImageColorizedScaled(graphics, ZombatarWidget_GetBackgroundImageByIndex(i + zombatarWidget->mSelectedBackgroundPage * 18),&theAlphaColor, theX + 12,theY + 12,58.0/216.0,58.0/216.0);
        }
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_prev_button,160 + 209,436);
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_next_button,160 + 588,436);
    }


    if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedBackground)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            Color color = gZombatarAccessoryColor2[i];
            if (zombatarWidget->mSelectedBackgroundColor != i) {
                color.mAlpha = 64;
            }
            Sexy_Graphics_DrawImageColorized(graphics, i == 17 ? Addon_Images.zombatar_colorpicker_none : Addon_Images.zombatar_colorpicker, &color, theX, theY);
        }
    } else {
        int holder[1];
        TodStringTranslate(holder,"[ZOMBATAR_COLOR_NOT_APPLICABLE]");
        TRect rect = {160 + 288,445,250,100};
        Sexy::Font* font = *Sexy_FONT_BRIANNETOD12_Addr;
        TodDrawStringWrapped(graphics,holder,&rect,font,&white,DrawStringJustification::Left,false);
        Sexy_String_Delete(holder);
    }

    int holder[1];
    Sexy_StrFormat(holder, "PAGE %d/%d", zombatarWidget->mSelectedBackgroundPage + 1 , 5);
    TodDrawString(graphics, holder, 160 + 410, 525, *Sexy_FONT_BRIANNETOD16_Addr, black, DrawStringJustification::Center);
    Sexy_String_Delete(holder);
}

void TestMenuWidget_DrawPortrait(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics,int x,int y) {
    Sexy::Image* backgroundImage = ZombatarWidget_GetBackgroundImageByIndex(zombatarWidget->mSelectedBackground);
    if (zombatarWidget->mSelectedBackground == 4 && zombatarWidget->mSelectedBackgroundColor != 255) {
        Sexy_Graphics_DrawImageColorized(graphics, backgroundImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedBackgroundColor], x, y);
    } else {
        Sexy_Graphics_DrawImage(graphics, backgroundImage, x, y);
    }
    Sexy_Graphics_DrawImageColorized(graphics,Addon_Images.zombatar_zombie_blank_skin, &gZombatarSkinColor[zombatarWidget->mSelectedSkinColor],x + 46, y + 48);
    Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_zombie_blank, x + 46, y + 48);

    Sexy::Image* clothImage = ZombatarWidget_GetClothImageByIndex(zombatarWidget->mSelectedCloth);
    if (clothImage != NULL) {
        int offsetX = Addon_Images.zombatar_background_blank->mWidth + ZombatarWidget_GetClothImageOffsetXByIndex(zombatarWidget->mSelectedCloth);
        int offsetY = Addon_Images.zombatar_background_blank->mHeight + ZombatarWidget_GetClothImageOffsetYByIndex(zombatarWidget->mSelectedCloth);
        Sexy_Graphics_DrawImage(graphics,clothImage ,x + offsetX, y + offsetY);
    }

    Sexy::Image* tidBitImage = ZombatarWidget_GetTidBitImageByIndex(zombatarWidget->mSelectedTidBit);
    if (tidBitImage != NULL) {
        int offsetX = ZombatarWidget_GetTidBitImageOffsetXByIndex(zombatarWidget->mSelectedTidBit);
        int offsetY = ZombatarWidget_GetTidBitImageOffsetYByIndex(zombatarWidget->mSelectedTidBit);
        if (zombatarWidget->mSelectedTidBitColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::TIDBIT,zombatarWidget->mSelectedTidBit) && zombatarWidget->mSelectedTidBit != 0) {
            Sexy_Graphics_DrawImageColorized(graphics,tidBitImage ,&gZombatarAccessoryColor2[zombatarWidget->mSelectedTidBitColor], x + offsetX, y + offsetY);
        } else {
            Sexy_Graphics_DrawImage(graphics,tidBitImage ,x + offsetX, y + offsetY);
        }
    }
    if (zombatarWidget->mSelectedTidBit == 0) {
        Sexy::Image* tidBitImage = ZombatarWidget_GetTidBitImageByIndex(2);
        if (tidBitImage != NULL) {
            int offsetX = ZombatarWidget_GetTidBitImageOffsetXByIndex(2);
            int offsetY = ZombatarWidget_GetTidBitImageOffsetYByIndex(2);
            if (zombatarWidget->mSelectedTidBitColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::TIDBIT,2)) {
                Sexy_Graphics_DrawImageColorized(graphics,tidBitImage ,&gZombatarAccessoryColor2[zombatarWidget->mSelectedTidBitColor], x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics,tidBitImage ,x + offsetX, y + offsetY);
            }
        }
    }

    Sexy::Image* eyeWearImage = ZombatarWidget_GetEyeWearImageByIndex(zombatarWidget->mSelectedEyeWear);
    if (eyeWearImage != NULL) {
        int offsetX = ZombatarWidget_GetEyeWearImageOffsetXByIndex(zombatarWidget->mSelectedEyeWear);
        int offsetY = ZombatarWidget_GetEyeWearImageOffsetYByIndex(zombatarWidget->mSelectedEyeWear);
        Sexy::Image* eyeWearMaskImage = ZombatarWidget_GetEyeWearMaskImageByIndex(zombatarWidget->mSelectedEyeWear);
        if (zombatarWidget->mSelectedEyeWearColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::EYEWEAR,zombatarWidget->mSelectedEyeWear)) {
            if (eyeWearMaskImage != NULL) {
                Sexy_Graphics_DrawImageColorized(graphics, eyeWearMaskImage ,&gZombatarAccessoryColor2[zombatarWidget->mSelectedEyeWearColor], x + offsetX, y + offsetY);
                Sexy_Graphics_DrawImage(graphics,eyeWearImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, eyeWearImage ,&gZombatarAccessoryColor2[zombatarWidget->mSelectedEyeWearColor], x + offsetX, y + offsetY);
            }
        } else {
            if (eyeWearMaskImage != NULL) {
                Sexy_Graphics_DrawImage(graphics, eyeWearMaskImage , x + offsetX, y + offsetY);
                Sexy_Graphics_DrawImage(graphics,eyeWearImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, eyeWearImage , x + offsetX, y + offsetY);
            }
        }
    }

    Sexy::Image* accessoryImage = ZombatarWidget_GetAccessoryImageByIndex(zombatarWidget->mSelectedAccessory);
    if (accessoryImage != NULL) {
        int offsetX = ZombatarWidget_GetAccessoryImageOffsetXByIndex(zombatarWidget->mSelectedAccessory);
        int offsetY = ZombatarWidget_GetAccessoryImageOffsetYByIndex(zombatarWidget->mSelectedAccessory);
        if (zombatarWidget->mSelectedAccessoryColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::ACCESSORY,zombatarWidget->mSelectedAccessory)) {
            Sexy_Graphics_DrawImageColorized(graphics, accessoryImage ,&gZombatarAccessoryColor2[zombatarWidget->mSelectedAccessoryColor], x + offsetX, y + offsetY);
        } else {
            Sexy_Graphics_DrawImage(graphics, accessoryImage , x + offsetX, y + offsetY);
        }
    }

    Sexy::Image* fHairImage = ZombatarWidget_GetFHairImageByIndex(zombatarWidget->mSelectedFHair);
    if (fHairImage != NULL) {
        int offsetX = ZombatarWidget_GetFHairImageOffsetXByIndex(zombatarWidget->mSelectedFHair);
        int offsetY = ZombatarWidget_GetFHairImageOffsetYByIndex(zombatarWidget->mSelectedFHair);
        int offsetX2 = ZombatarWidget_GetFHairMaskImageOffsetXByIndex(zombatarWidget->mSelectedFHair);
        int offsetY2 = ZombatarWidget_GetFHairMaskImageOffsetYByIndex(zombatarWidget->mSelectedFHair);
        Sexy::Image* fHairMaskImage = ZombatarWidget_GetFHairMaskImageByIndex(zombatarWidget->mSelectedFHair);
        if (zombatarWidget->mSelectedFHairColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::FHAIR,zombatarWidget->mSelectedFHair)) {
            if (fHairMaskImage != NULL) {
                Sexy_Graphics_DrawImageColorized(graphics, fHairMaskImage, &gZombatarAccessoryColor[zombatarWidget->mSelectedFHairColor], x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics,fHairImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, fHairImage ,&gZombatarAccessoryColor[zombatarWidget->mSelectedFHairColor], x + offsetX, y + offsetY);
            }
        } else {
            if (fHairMaskImage != NULL) {
                Sexy_Graphics_DrawImage(graphics, fHairMaskImage , x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics,fHairImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, fHairImage , x + offsetX, y + offsetY);
            }
        }
    }


    Sexy::Image* hairImage = ZombatarWidget_GetHairImageByIndex(zombatarWidget->mSelectedHair);
    if (hairImage != NULL) {
        int offsetX = ZombatarWidget_GetHairImageOffsetXByIndex(zombatarWidget->mSelectedHair);
        int offsetY = ZombatarWidget_GetHairImageOffsetYByIndex(zombatarWidget->mSelectedHair);
        int offsetX2 = ZombatarWidget_GetHairMaskImageOffsetXByIndex(zombatarWidget->mSelectedHair);
        int offsetY2 = ZombatarWidget_GetHairMaskImageOffsetYByIndex(zombatarWidget->mSelectedHair);
        Sexy::Image* hairMaskImage = ZombatarWidget_GetHairMaskImageByIndex(zombatarWidget->mSelectedHair);
        if (zombatarWidget->mSelectedHairColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::HAIR,zombatarWidget->mSelectedHair)) {
            if (hairMaskImage != NULL) {
                Sexy_Graphics_DrawImageColorized(graphics, hairMaskImage, &gZombatarAccessoryColor[zombatarWidget->mSelectedHairColor], x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics,hairImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, hairImage ,&gZombatarAccessoryColor[zombatarWidget->mSelectedHairColor], x + offsetX, y + offsetY);
            }
        } else {
            if (hairMaskImage != NULL) {
                Sexy_Graphics_DrawImage(graphics, hairMaskImage , x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics,hairImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, hairImage , x + offsetX, y + offsetY);
            }
        }
    }

    Sexy::Image* hatImage = ZombatarWidget_GetHatImageByIndex(zombatarWidget->mSelectedHat);
    if (hatImage != NULL) {
        int offsetX = ZombatarWidget_GetHatImageOffsetXByIndex(zombatarWidget->mSelectedHat);
        int offsetY = ZombatarWidget_GetHatImageOffsetYByIndex(zombatarWidget->mSelectedHat);
        int offsetX2 = ZombatarWidget_GetHatMaskImageOffsetXByIndex(zombatarWidget->mSelectedHat);
        int offsetY2 = ZombatarWidget_GetHatMaskImageOffsetYByIndex(zombatarWidget->mSelectedHat);
        Sexy::Image* hatMaskImage = ZombatarWidget_GetHatMaskImageByIndex(zombatarWidget->mSelectedHat);
        if (zombatarWidget->mSelectedHatColor != 255 && ZombatarWidget_AccessoryIsColorized(ZombatarWidget::HAT,zombatarWidget->mSelectedHat)) {
            if (hatMaskImage != NULL) {
                Sexy_Graphics_DrawImageColorized(graphics, hatMaskImage, &gZombatarAccessoryColor2[zombatarWidget->mSelectedHatColor], x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics,hatImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImageColorized(graphics, hatImage ,&gZombatarAccessoryColor2[zombatarWidget->mSelectedHatColor], x + offsetX, y + offsetY);
            }
        } else {
            if (hatMaskImage != NULL) {
                Sexy_Graphics_DrawImage(graphics, hatMaskImage , x + offsetX + offsetX2, y + offsetY + offsetY2);
                Sexy_Graphics_DrawImage(graphics,hatImage ,x + offsetX, y + offsetY);
            } else {
                Sexy_Graphics_DrawImage(graphics, hatImage , x + offsetX, y + offsetY);
            }
        }
    }
}

void TestMenuWidget_DrawPreView(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ALMANAC_GROUNDDAY_Addr, 160 + 729, 376);
    float tmpX = graphics->mTransX;
    float tmpY = graphics->mTransY;
    graphics->mTransX += 160 + 778;
    graphics->mTransY += 434;
    Zombie_Draw(zombatarWidget->mPreviewZombie, graphics);
    graphics->mTransX = tmpX;
    graphics->mTransY = tmpY;
}

void TestMenuWidget_Draw(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics) {

    Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_main_bg, 0, 0);
    Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_widget_bg, 160 + 26, 27);

    if (zombatarWidget->mShowExistingZombatarPortrait && Addon_Images.zombatar_portrait != NULL) {
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_portrait, 160 + 260, 210);
        int holder[1];
        TodStringTranslate(holder, "[ZOMBATAR_VIEW_PORTRAIT]");
        TRect rect = {160 + 178,450,400,100};
        TodDrawStringWrapped(graphics, holder, &rect, *Sexy_FONT_BRIANNETOD16_Addr, &white, DrawStringJustification::Center,false);
        Sexy_String_Delete(holder);
    } else if (zombatarWidget->mShowZombieTypeSelection) {
        TestMenuWidget_DrawZombieSelection(zombatarWidget, graphics);
    } else {
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_widget_inner_bg, 160 + 179, 148);
        for (int i = 0; i < ZombatarWidget::MaxTabNum; ++i) {
            Sexy_Graphics_DrawImage(graphics,i == zombatarWidget->mSelectedTab ? ZombatarWidget_GetTabButtonDownImageByIndex(i) : ZombatarWidget_GetTabButtonImageByIndex(i),160 + 67, 152 + i * 43);
        }
        Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_colors_bg, 160 + 260, 394);
        switch (zombatarWidget->mSelectedTab) {
            case ZombatarWidget::SKIN:
                TestMenuWidget_DrawSkin(zombatarWidget, graphics);
                break;
            case ZombatarWidget::HAIR:
                TestMenuWidget_DrawHair(zombatarWidget, graphics);
                break;
            case ZombatarWidget::FHAIR:
                TestMenuWidget_DrawFHair(zombatarWidget, graphics);
                break;
            case ZombatarWidget::TIDBIT:
                TestMenuWidget_DrawTidBit(zombatarWidget, graphics);
                break;
            case ZombatarWidget::EYEWEAR:
                TestMenuWidget_DrawEyeWear(zombatarWidget, graphics);
                break;
            case ZombatarWidget::CLOTHES:
                TestMenuWidget_DrawCloth(zombatarWidget, graphics);
                break;
            case ZombatarWidget::ACCESSORY:
                TestMenuWidget_DrawAccessory(zombatarWidget, graphics);
                break;
            case ZombatarWidget::HAT:
                TestMenuWidget_DrawHat(zombatarWidget, graphics);
                break;
            case ZombatarWidget::BACKGROUND:
                TestMenuWidget_DrawBackground(zombatarWidget, graphics);
                break;
        }
    }

    TestMenuWidget_DrawPortrait(zombatarWidget, graphics, 160 + 708, 140);
    TestMenuWidget_DrawPreView(zombatarWidget, graphics);

    Sexy_Graphics_DrawImage(graphics, Addon_Images.zombatar_display_window, 160 + 0, 0);
}

void (*old_TestMenuWidget_Delete2)(ZombatarWidget *zombatarWidget);

void TestMenuWidget_Delete2(ZombatarWidget *zombatarWidget) {

    // TODO:解决五个按钮的内存泄露问题。GameButton_Delete会闪退，暂不清楚原因。
    Zombie_DieNoLoot(zombatarWidget->mPreviewZombie);
    (*((void (__fastcall **)(Zombie *))zombatarWidget->mPreviewZombie->vTable + 1))(zombatarWidget->mPreviewZombie); // Delete();

    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 7))(zombatarWidget, zombatarWidget->mBackButton);
    zombatarWidget->mBackButton->mDrawStoneButton = true;
    zombatarWidget->mBackButton->mButtonImage = NULL;
    zombatarWidget->mBackButton->mDownImage = NULL;
    zombatarWidget->mBackButton->mOverImage = NULL;
    //GameButton_Delete(zombatarWidget->mBackButton);

    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 7))(zombatarWidget, zombatarWidget->mFinishButton);
    zombatarWidget->mFinishButton->mDrawStoneButton = true;
    zombatarWidget->mFinishButton->mButtonImage = NULL;
    zombatarWidget->mFinishButton->mDownImage = NULL;
    zombatarWidget->mFinishButton->mOverImage = NULL;
    //GameButton_Delete(zombatarWidget->mFinishButton);


    (*((void (__fastcall **)(Sexy::Widget *, Sexy::Widget *))zombatarWidget->vTable + 7))(zombatarWidget, zombatarWidget->mViewPortraitButton);
    zombatarWidget->mViewPortraitButton->mDrawStoneButton = true;
    zombatarWidget->mViewPortraitButton->mButtonImage = NULL;
    zombatarWidget->mViewPortraitButton->mDownImage = NULL;
    zombatarWidget->mViewPortraitButton->mOverImage = NULL;
    //GameButton_Delete(zombatarWidget->mViewPortraitButton);

    // GameButton_Delete(zombatarWidget->mNewButton);
    // GameButton_Delete(zombatarWidget->mDeleteButton);
    operator delete(zombatarWidget->mButtonListener->vTable);
    operator delete(zombatarWidget->mButtonListener);
    old_TestMenuWidget_Delete2(zombatarWidget);
}

void (*old_TestMenuWidget_Delete)(ZombatarWidget *zombatarWidget);

void TestMenuWidget_Delete(ZombatarWidget *zombatarWidget) {
    TestMenuWidget_Delete2(zombatarWidget);
    operator delete(zombatarWidget);
}

void TestMenuWidget_MouseDownSkin(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 285 + (i % 9) * 30;
        int theY = 432 + i / 9 * 30;
        TRect rect = {theX, theY, 30, 30};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedSkinColor = i;
            return;
        }
    }
}

void TestMenuWidget_MouseDownHair(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedHair = i;
            Reanimation_SetZombatarHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHair, zombatarWidget->mSelectedHairColor);
            return;
        }
    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedHair = 255;
        Reanimation_SetZombatarHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHair, zombatarWidget->mSelectedHairColor);
        return;
    }
    if (zombatarWidget->mSelectedHair != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedHair)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedHairColor = i;
                Reanimation_SetZombatarHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedHair, zombatarWidget->mSelectedHairColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownFHair(ZombatarWidget *zombatarWidget, int x, int y) {
    if (zombatarWidget->mSelectedFHairPage == 0) {
        for (int i = 0; i < 17; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedFHair = i;
                Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
                return;
            }
        }
        int theX = 160 + 198 + (17 % 6) * 73;
        int theY = 162 + 17 / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedFHair = 255;
            Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
            return;
        }
        TRect next = {160 + 588, 436, Addon_Images.zombatar_next_button->mWidth, Addon_Images.zombatar_next_button->mHeight};
        if (TRect_Contains(&next, x, y)) {
            zombatarWidget->mSelectedFHairPage ++;
            return;
        }
    }else if (zombatarWidget->mSelectedFHairPage == 1) {
        for (int i = 0; i < 7; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedFHair = i + 17;
                Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
                return;
            }
        }
        int theX = 160 + 198 + (7 % 6) * 73;
        int theY = 162 + 7 / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedFHair = 255;
            Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
            return;
        }
        TRect prev = {160 + 209, 436, Addon_Images.zombatar_next_button->mWidth, Addon_Images.zombatar_next_button->mHeight};
        if (TRect_Contains(&prev, x, y)) {
            zombatarWidget->mSelectedFHairPage --;
            return;
        }
    }

    if (zombatarWidget->mSelectedFHair != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedFHair)){
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedFHairColor = i;
                Reanimation_SetZombatarFHair(zombatarWidget->mZombatarReanim, zombatarWidget->mSelectedFHair, zombatarWidget->mSelectedFHairColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownTidBit(ZombatarWidget *zombatarWidget, int x, int y) {

    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedTidBit = i;
            Reanimation_SetZombatarTidBits(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedTidBit,zombatarWidget->mSelectedTidBitColor);
            return;
        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedTidBit = 255;
        Reanimation_SetZombatarTidBits(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedTidBit,zombatarWidget->mSelectedTidBitColor);
        return;
    }

    if (zombatarWidget->mSelectedTidBit != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedTidBit)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedTidBitColor = i;
                Reanimation_SetZombatarTidBits(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedTidBit,zombatarWidget->mSelectedTidBitColor);
                return;
            }
        }
    }

}

void TestMenuWidget_MouseDownEyeWear(ZombatarWidget *zombatarWidget, int x, int y) {

    for (int i = 0; i < 16; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedEyeWear = i;
            Reanimation_SetZombatarEyeWear(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedEyeWear,zombatarWidget->mSelectedEyeWearColor);
            return;
        }
    }
    int theX = 160 + 198 + (16 % 6) * 73;
    int theY = 162 + 16 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedEyeWear = 255;
        Reanimation_SetZombatarEyeWear(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedEyeWear,zombatarWidget->mSelectedEyeWearColor);
        return;
    }

    if (zombatarWidget->mSelectedEyeWear != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedEyeWear)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedEyeWearColor = i;
                Reanimation_SetZombatarEyeWear(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedEyeWear,zombatarWidget->mSelectedEyeWearColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownCloth(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 12; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedCloth = i;
            return;
        }
    }
    int theX = 160 + 198 + (12 % 6) * 73;
    int theY = 162 + 12 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedCloth = 255;
        return;
    }
}

void TestMenuWidget_MouseDownAccessory(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 15; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedAccessory = i;
            Reanimation_SetZombatarAccessories(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedAccessory,zombatarWidget->mSelectedAccessoryColor);
            return;
        }
    }
    int theX = 160 + 198 + (15 % 6) * 73;
    int theY = 162 + 15 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedAccessory = 255;
        Reanimation_SetZombatarAccessories(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedAccessory,zombatarWidget->mSelectedAccessoryColor);
        return;
    }

    if (zombatarWidget->mSelectedAccessory != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedAccessory)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedAccessoryColor = i;
                Reanimation_SetZombatarAccessories(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedAccessory,zombatarWidget->mSelectedAccessoryColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownHat(ZombatarWidget *zombatarWidget, int x, int y) {
    for (int i = 0; i < 14; ++i) {
        int theX = 160 + 198 + (i % 6) * 73;
        int theY = 162 + i / 6 * 79;
        TRect rect = {theX, theY, 73, 79};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedHat = i;
            Reanimation_SetZombatarHats(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedHat,zombatarWidget->mSelectedHatColor);
            return;
        }
    }
    int theX = 160 + 198 + (14 % 6) * 73;
    int theY = 162 + 14 / 6 * 79;
    TRect rect = {theX, theY, 73, 79};
    if (TRect_Contains(&rect, x, y)) {
        zombatarWidget->mSelectedHat = 255;
        Reanimation_SetZombatarHats(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedHat,zombatarWidget->mSelectedHatColor);
        return;
    }

    if (zombatarWidget->mSelectedHat != 255 && ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedHat)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedHatColor = i;
                Reanimation_SetZombatarHats(zombatarWidget->mZombatarReanim,zombatarWidget->mSelectedHat,zombatarWidget->mSelectedHatColor);
                return;
            }
        }
    }
}

void TestMenuWidget_MouseDownBackground(ZombatarWidget *zombatarWidget, int x, int y) {
    if (zombatarWidget->mSelectedBackgroundPage == 0) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackground = i;
                return;
            }
        }
        TRect next = {160 + 588, 436, Addon_Images.zombatar_next_button->mWidth, Addon_Images.zombatar_next_button->mHeight};
        if (TRect_Contains(&next, x, y)) {
            zombatarWidget->mSelectedBackgroundPage++;
            return;
        }
    } else if (zombatarWidget->mSelectedBackgroundPage == 4) {
        for (int i = 0; i < 11; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackground = i + 18 * zombatarWidget->mSelectedBackgroundPage;
                return;
            }
        }
        TRect prev = {160 + 209, 436, Addon_Images.zombatar_next_button->mWidth, Addon_Images.zombatar_next_button->mHeight};
        if (TRect_Contains(&prev, x, y)) {
            zombatarWidget->mSelectedBackgroundPage--;
            return;
        }
    } else  {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 198 + (i % 6) * 73;
            int theY = 162 + i / 6 * 79;
            TRect rect = {theX, theY, 73, 79};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackground = i + 18 * zombatarWidget->mSelectedBackgroundPage;
                return;
            }
        }
        TRect next = {160 + 588, 436, Addon_Images.zombatar_next_button->mWidth, Addon_Images.zombatar_next_button->mHeight};
        if (TRect_Contains(&next, x, y)) {
            zombatarWidget->mSelectedBackgroundPage++;
            return;
        }
        TRect prev = {160 + 209, 436, Addon_Images.zombatar_next_button->mWidth, Addon_Images.zombatar_next_button->mHeight};
        if (TRect_Contains(&prev, x, y)) {
            zombatarWidget->mSelectedBackgroundPage--;
            return;
        }
    }


    if (ZombatarWidget_AccessoryIsColorized(zombatarWidget->mSelectedTab,zombatarWidget->mSelectedBackground)) {
        for (int i = 0; i < 18; ++i) {
            int theX = 160 + 285 + (i % 9) * 30;
            int theY = 432 + i / 9 * 30;
            TRect rect = {theX, theY, 30, 30};
            if (TRect_Contains(&rect, x, y)) {
                zombatarWidget->mSelectedBackgroundColor = i;
                return;
            }
        }
    }

}

void TestMenuWidget_MouseDown(ZombatarWidget *zombatarWidget, int x, int y) {
    xx = x;
    yy = y;
//    Sexy_Widget_Move(zombatarWidget->mBackButton,xx,yy);
//    zombatarWidget->mPreviewZombie->mX = x;
//    zombatarWidget->mPreviewZombie->mY = y;
    LOGD("%d %d",x,y);

    if (mMainMenuZombatarWidget->mShowExistingZombatarPortrait) {
        return;
    }
    for (char i = 0; i < ZombatarWidget::MaxTabNum; ++i) {
        TRect rect = {160 + 67, 152 + i * 43, 125, 47};
        if (TRect_Contains(&rect, x, y)) {
            zombatarWidget->mSelectedTab = i;
            zombatarWidget->mSelectedFHairPage = 0;
            zombatarWidget->mSelectedBackgroundPage = 0;
            return;
        }
    }

    switch (zombatarWidget->mSelectedTab) {
        case ZombatarWidget::SKIN:
            TestMenuWidget_MouseDownSkin(zombatarWidget,x,y);
            break;
        case ZombatarWidget::HAIR:
            TestMenuWidget_MouseDownHair(zombatarWidget,x,y);
            break;
        case ZombatarWidget::FHAIR:
            TestMenuWidget_MouseDownFHair(zombatarWidget,x,y);
            break;
        case ZombatarWidget::TIDBIT:
            TestMenuWidget_MouseDownTidBit(zombatarWidget,x,y);
            break;
        case ZombatarWidget::EYEWEAR:
            TestMenuWidget_MouseDownEyeWear(zombatarWidget,x,y);
            break;
        case ZombatarWidget::CLOTHES:
            TestMenuWidget_MouseDownCloth(zombatarWidget, x,y);
            break;
        case ZombatarWidget::ACCESSORY:
            TestMenuWidget_MouseDownAccessory(zombatarWidget, x,y);
            break;
        case ZombatarWidget::HAT:
            TestMenuWidget_MouseDownHat(zombatarWidget, x,y);
            break;
        case ZombatarWidget::BACKGROUND:
            TestMenuWidget_MouseDownBackground(zombatarWidget,x,y);
            break;
    }

}

void TestMenuWidget_MouseDrag(ZombatarWidget *zombatarWidget, int x, int y) {

    xx = x;
    yy = y;
//    Sexy_Widget_Move(zombatarWidget->mBackButton,xx,yy);
//    zombatarWidget->mPreviewZombie->mX = x;
//    zombatarWidget->mPreviewZombie->mY = y;
    LOGD("%d %d",x,y);
}

void TestMenuWidget_MouseUp(ZombatarWidget *zombatarWidget, int x, int y) {

}

void TestMenuWidget_KeyDown(ZombatarWidget *zombatarWidget,int keyCode) {
    if (keyCode == Sexy::Back || keyCode == Sexy::Back2) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        LawnApp_KillZombatarScreen(lawnApp);
        LawnApp_ShowMainMenuScreen(lawnApp);
        return;
    }
    if (keyCode == Sexy::Up) {
        yy--;
        LOGD("%d %d",xx,yy);
    }
    if (keyCode == Sexy::Down) {
        yy++;
        LOGD("%d %d",xx,yy);
    }
    if (keyCode == Sexy::Left) {
        xx--;
        LOGD("%d %d",xx,yy);
    }
    if (keyCode == Sexy::Right) {
        xx++;
        LOGD("%d %d",xx,yy);
    }
    if (keyCode == Sexy::Up || keyCode == Sexy::Down || keyCode == Sexy::Left || keyCode == Sexy::Right) {

        return;
    }
}
#endif //PVZ_TV_1_1_5_MAINMENU_CPP
