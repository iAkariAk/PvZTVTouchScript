//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_LAWNAPP_CPP
#define PVZ_TV_1_1_5_LAWNAPP_CPP

#include "../GlobalVariable.h"
#include "LawnApp.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Music/Music.h"
#include "HookGame/Board/Board.h"
#include "HookGame/MainMenu/MainMenu.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

Sexy::Image *LawnApp_GetImageByFileName(LawnApp *lawnApp, const char *fileName) {
    //爽啊，根据贴图文件路径获得贴图
    int holder[1];
    Sexy_StrFormat(holder, fileName);
    Sexy::Image *theImage = Sexy_SexyAppBase_GetImage(lawnApp, holder, 1);
    Sexy_String_Delete(holder);
    return theImage;
}

int LawnApp_GetSoundByFileName(LawnApp *lawnApp, const char *fileName){
    //爽啊，根据音频文件路径获得音频
    int holder[1];
    Sexy_StrFormat(holder, fileName);
    int theSoundId = Sexy_AudiereSoundManager_LoadSound(lawnApp->mSoundManager,holder);
    Sexy_String_Delete(holder);
    return theSoundId;
}

void LawnApp_DoConfirmBackToMain(LawnApp *lawnApp, bool save) {
    // 实现在花园直接退出而不是弹窗退出；同时实现新版暂停菜单
    GameMode::GameMode gameMode = lawnApp->mGameMode;
    if (gameMode == GameMode::ChallengeZenGarden) {
        lawnApp->mBoardResult = BoardResult::Quit;
//        if (save) Board_TryToSaveGame(lawnApp->mBoard);
        LawnApp_DoBackToMain(lawnApp);
        return;
    }
    if ((gameMode == GameMode::TwoPlayerVS || gameMode == GameMode::ChallengeTreeOfWisdom || enableNewOptionsDialog) && Sexy_SexyAppBase_GetDialog(lawnApp,Dialogs::DIALOG_NEWOPTIONS) == NULL) {
        LawnApp_DoNewOptions(lawnApp, 0, 0);
        return;
    }
    ConfirmBackToMainDialog *dialog = (ConfirmBackToMainDialog *)operator new(sizeof(ConfirmBackToMainDialog));
    ConfirmBackToMainDialog_ConfirmBackToMainDialog(dialog, save);
    (*(void (__fastcall **)(LawnApp *, int, Sexy::Widget *))(*(_DWORD *)lawnApp + 416))(lawnApp, Dialogs::DIALOG_CONFIRM_BACK_TO_MAIN, dialog);
    (*(void (__fastcall **)(_DWORD, Sexy::Widget *))(**((_DWORD **)lawnApp + 165) + 48))(*((_DWORD *)lawnApp + 165), dialog);
}

void (*old_LawnApp_DoBackToMain)(LawnApp *lawnApp);

void LawnApp_DoBackToMain(LawnApp *lawnApp) {
    // 实现每次退出游戏后都清空2P
    LawnApp_ClearSecondPlayer(lawnApp);
    return old_LawnApp_DoBackToMain(lawnApp);
}

void (*old_LawnApp_DoNewOptions)(LawnApp *lawnApp, bool a2, unsigned int a3);

void LawnApp_DoNewOptions(LawnApp *lawnApp, bool a2, unsigned int a3) {
    return old_LawnApp_DoNewOptions(lawnApp, a2, a3);
}

void (*old_LawnApp_ShowAwardScreen)(LawnApp* lawnApp, int a2);

void LawnApp_ShowAwardScreen(LawnApp* lawnApp, int a2) {
    //记录当前游戏状态
    return old_LawnApp_ShowAwardScreen(lawnApp, a2);
}

void (*old_LawnApp_KillAwardScreen)(LawnApp* lawnApp);

void LawnApp_KillAwardScreen(LawnApp* lawnApp) {
    //记录当前游戏状态
    return old_LawnApp_KillAwardScreen(lawnApp);
}

void LawnApp_OnSessionTaskFailed(LawnApp *lawnApp) {
    //用此空函数替换游戏原有的LawnApp_OnSessionTaskFailed()函数，从而去除启动游戏时的“网络错误：255”弹窗
}

int (*old_LawnApp_GamepadToPlayerIndex)(LawnApp *lawnApp, unsigned int a2);

int LawnApp_GamepadToPlayerIndex(LawnApp *lawnApp, unsigned int a2) {
    //实现双人结盟中1P选卡选满后自动切换为2P选卡
    if (LawnApp_IsCoopMode(lawnApp)) {
        return !m1PChoosingSeeds;
    }
    return old_LawnApp_GamepadToPlayerIndex(lawnApp, a2);
}

//菜单DoCheatDialog
bool doCheatDialog = false;
//菜单DoCheatCodeDialog
bool doCheatCodeDialog = false;

void (*old_LawnApp_UpDateApp)(LawnApp *lawnApp);

void LawnApp_UpDateApp(LawnApp *lawnApp) {
    // 去除道具教学关卡
    PlayerInfo *mPlayerInfo =lawnApp->mPlayerInfo;
    if (mPlayerInfo != NULL) {
        mPlayerInfo->mPassedShopSeedTutorial = true;//标记玩家已经通过1-1的道具教学关卡
    }
    if (doCheatDialog) {
        if (!isMainMenu) LawnApp_DoCheatDialog(lawnApp);
        doCheatDialog = false;
    }
    if (doCheatCodeDialog) {
        if (!isMainMenu) LawnApp_DoCheatCodeDialog(lawnApp);
        doCheatCodeDialog = false;
    }
    if (doKeyboardTwoPlayerDialog) {
        LawnApp_LawnMessageBox(lawnApp, Dialogs::DIALOG_MESSAGE, "双人模式已开启", "已经进入双人模式；再次按下切换键即可退出此模式。", "[DIALOG_BUTTON_OK]", "", 3);
        doKeyboardTwoPlayerDialog = false;
    }



    return old_LawnApp_UpDateApp(lawnApp);
}

bool disableShop = false;

bool (*old_LawnApp_CanShopLevel)(LawnApp *lawnApp);

bool LawnApp_CanShopLevel(LawnApp *lawnApp) {
    //决定是否在当前关卡显示道具栏
    if (disableShop) return false;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS || LawnApp_IsCoopMode(lawnApp))
        return false;
    return old_LawnApp_CanShopLevel(lawnApp);
}

void LawnApp_KillDialog(LawnApp *lawnApp, Dialogs::Dialogs id) {
    (*(void (__fastcall **)(LawnApp*, Dialogs::Dialogs)) (*(_DWORD *) lawnApp + 428))(lawnApp, id); // KillDialog(Dialogs::DIALOG_HELPOPTIONS)
}

void (*old_LawnApp_ShowCreditScreen)(LawnApp *lawnApp, bool isFromMainMenu);

void LawnApp_ShowCreditScreen(LawnApp *lawnApp, bool isFromMainMenu) {
    //用于一周目之后点击"制作人员"按钮播放MV
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuLeft);
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuCenter);
    TodFoley_StopFoley(lawnApp->mSoundSystem, FoleyType::MenuRight);
    if (isFromMainMenu && LawnApp_HasFinishedAdventure(lawnApp)) {
        isFromMainMenu = false;
        LawnApp_KillMainMenu(lawnApp);
        LawnApp_KillNewOptionsDialog(lawnApp);
        LawnApp_KillDialog(lawnApp,Dialogs::DIALOG_HELPOPTIONS);
    }
    return old_LawnApp_ShowCreditScreen(lawnApp, isFromMainMenu);
}

void (*old_LawnApp_LoadLevelConfiguration)(LawnApp *lawnApp, int a2, int a3);

void LawnApp_LoadLevelConfiguration(LawnApp *lawnApp, int a2, int a3) {
    //如果开启了恢复出怪，则什么都不做，以做到禁止从levels.xml加载出怪。
    if (normalLevel) return;
    old_LawnApp_LoadLevelConfiguration(lawnApp, a2, a3);
}

void LawnApp_TryHelpTextScreen(LawnApp *lawnApp, int a2) {
    //空函数替换，去除初次进入对战结盟模式时的操作提示。
}

void LawnApp_PlaySample(LawnApp *lawnApp, int soundAddr) {
    (*(void (__fastcall **)(LawnApp *, int, int)) (*(_DWORD *) lawnApp + LAWNAPP_PLAYSAMPLE_OFFSET))(
            lawnApp, soundAddr, 1);
}

void (*old_LawnApp_LawnApp)(LawnApp *lawnApp);

void LawnApp_LawnApp(LawnApp *lawnApp) {
    // 开启触控用
    old_LawnApp_LawnApp(lawnApp);
    lawnApp->mLawnMouseMode = true; // mLawnMouseMode = True,开启触控！！！
}

void (*old_LawnApp_Init)(LawnApp *lawnApp);

void LawnApp_Init(LawnApp *lawnApp) {
    //试图修复默认加载名为player用户的问题。

    old_LawnApp_Init(lawnApp);
    if (lawnApp->mPlayerInfo == NULL &&lawnApp->mProfileMgr[7] > 0) {
        lawnApp->mPlayerInfo = Sexy_DefaultProfileMgr_GetAnyProfile(lawnApp->mProfileMgr);
    }

    lawnApp->mNewIs3DAccelerated = lawnApp->mPlayerInfo == NULL || !lawnApp->mPlayerInfo->mIs3DAcceleratedClosed;
}

void LawnApp_Load(LawnApp* lawnApp,char* theGroupName){
    int holder[1];
    Sexy_StrFormat(holder,"%s",theGroupName);
    TodLoadResources(holder);
    Sexy_String_Delete(holder);
}

void (*old_LawnApp_LoadingThreadProc)(LawnApp *lawnApp);

void LawnApp_LoadingThreadProc(LawnApp *lawnApp) {
    //加载新增资源用
    old_LawnApp_LoadingThreadProc(lawnApp);
    LawnApp_LoadAddonImages(lawnApp);
    LawnApp_LoadAddonSounds(lawnApp);
    TodStringListLoad("addonFiles/properties/AddonStrings.txt"); // 加载自定义字符串

    //加载三个主界面背景白噪音Foley
    *gFoleyParamArraySizeAddr += 3;
    gMenuLeftFoley.mSfxID[0] = Sexy_SOUND_MENU_L_ST_Addr;
    gMenuCenterFoley.mSfxID[0] = Sexy_SOUND_MENU_C_ST_Addr;
    gMenuRightFoley.mSfxID[0] = Sexy_SOUND_MENU_R_ST_Addr;

//    //试图修复偶现的地图错位现象。不知道是否有效
//    LawnApp_Load(lawnApp,"DelayLoad_Background1");
//    LawnApp_Load(lawnApp,"DelayLoad_BackgroundUnsodded");
//    LawnApp_Load(lawnApp,"DelayLoad_Background2");
//    LawnApp_Load(lawnApp,"DelayLoad_Background3");
//    LawnApp_Load(lawnApp,"DelayLoad_Background4");
//    LawnApp_Load(lawnApp,"DelayLoad_Background5");
//    LawnApp_Load(lawnApp,"DelayLoad_Background6");

    if (showHouse) ReanimatorEnsureDefinitionLoaded(ReanimationType::LeaderboardsHouse, true);
    ReanimatorEnsureDefinitionLoaded(ReanimationType::ZombatarHead, true);
}


bool (*old_LawnApp_IsChallengeWithoutSeedBank)(LawnApp* lawnApp);

bool LawnApp_IsChallengeWithoutSeedBank(LawnApp* lawnApp) {
    // 黄油爆米花专用
    return lawnApp->mGameMode == GameMode::ChallengeButteredPopcorn || old_LawnApp_IsChallengeWithoutSeedBank(lawnApp);
}

int (*old_LawnApp_GetSeedsAvailable)(LawnApp *lawnApp, int isZombieChooser);

int LawnApp_GetSeedsAvailable(LawnApp *lawnApp, int isZombieChooser) {
    //解锁僵尸方六张隐藏卡片
    if (isZombieChooser) {
        return 86;
    }
    return old_LawnApp_GetSeedsAvailable(lawnApp, isZombieChooser);
}

void (*old_LawnApp_HardwareInit)(LawnApp *lawnApp);

void LawnApp_HardwareInit(LawnApp *lawnApp) {

    old_LawnApp_HardwareInit(lawnApp);
//    if (useXboxMusic) {
//        Music2_Delete(lawnApp->mMusic);
//        lawnApp->mMusic = (Music2*) operator new(104u);
//        Music_Music(lawnApp->mMusic); // 使用Music而非Music2
//    }
}

bool LawnApp_GrantAchievement(LawnApp *lawnApp, AchievementId::AchievementId theAchievementId) {
    // 一些非Board的成就在这里处理
    PlayerInfo* playerInfo = lawnApp->mPlayerInfo;
    if (!playerInfo->mAchievements[theAchievementId]) {
        LawnApp_PlaySample(lawnApp, Addon_Sounds.achievement);
//    int holder[1];
//    Sexy_StrFormat(holder,"一二三四五六 成就达成！");
//    ((CustomMessageWidget*)board->mAdvice)->mIcon = GetIconByAchievementId(theAchievementId);
//    Board_DisplayAdviceAgain(board, holder, MessageStyle::Achievement, AdviceType::AchievementEarned);
//    Sexy_String_Delete(holder);
        playerInfo->mAchievements[theAchievementId] = true;
        return true;
    }
    return false;
}
bool (*old_LawnApp_IsNight)(LawnApp* lawnApp);

bool LawnApp_IsNight(LawnApp *lawnApp) {
    // 添加非冒险模式（如：小游戏、花园、智慧树）关卡内进商店的昼夜判定
    if (lawnApp->mBoard != NULL) {
        return Board_StageIsNight(lawnApp->mBoard);
    }
    return old_LawnApp_IsNight(lawnApp);
}

int LawnApp_TrophiesNeedForGoldSunflower(LawnApp* lawnApp){
    // 修复新增的小游戏不记入金向日葵达成条件
    int theNumMiniGames = 0;
    for (int i = 0; i < 94; ++i) {
        if (GetChallengeDefinition(i).mPage == ChallengePage::CHALLENGE_PAGE_CHALLENGE){
            theNumMiniGames++;
        }
    }
    return theNumMiniGames + 18 + 10 - LawnApp_GetNumTrophies(lawnApp, ChallengePage::CHALLENGE_PAGE_SURVIVAL) - LawnApp_GetNumTrophies(lawnApp, ChallengePage::CHALLENGE_PAGE_CHALLENGE) - LawnApp_GetNumTrophies(lawnApp, ChallengePage::CHALLENGE_PAGE_PUZZLE);
}


void LawnApp_SetFoleyVolume(LawnApp *lawnApp, FoleyType::FoleyType type, double theVolume) {
    TodFoley* mSoundSystem = lawnApp->mSoundSystem;
    FoleyTypeData* foleyTypeData = &mSoundSystem->mTypeData[type];
    for (int j = 0; j < 8; j++) {
        FoleyInstance* foleyInstance = &foleyTypeData->mFoleyInstances[j];
        if (foleyInstance->mRefCount != 0) {
            int* mInstance = foleyInstance->mInstance;
            (*(void (__fastcall **)(int*, _DWORD, double))(*mInstance + 28))(mInstance,*(_DWORD *)(*mInstance + 28),theVolume);
        }
    }
}

void (*old_Sexy_SexyAppBase_SexyAppBase)(SexyAppBase *appBase);

void Sexy_SexyAppBase_SexyAppBase(SexyAppBase *appBase) {
    old_Sexy_SexyAppBase_SexyAppBase(appBase);
//    LOGD("%d",*((_DWORD *)appBase + 464));
//    *((_DWORD *)appBase + 464) = 30;
}


void LawnApp_ShowLeaderboards(LawnApp *lawnApp) {
    mMainMenuLeaderboardsWidget = (LeaderboardsWidget *) operator new(sizeof(LeaderboardsWidget));
    LeaderboardsWidget_LeaderboardsWidget(mMainMenuLeaderboardsWidget, lawnApp);
    (*(void (__fastcall **)(int *, Sexy::Widget*))(*lawnApp->mWidgetManager + 24))(lawnApp->mWidgetManager,mMainMenuLeaderboardsWidget); // AddWidget()
    (*(void (__fastcall **)(int *, Sexy::Widget*))(*lawnApp->mWidgetManager + 48))(lawnApp->mWidgetManager,mMainMenuLeaderboardsWidget); // SetFocusedWidget()
}

void LawnApp_KillLeaderboards(LawnApp *lawnApp) {
    if (mMainMenuLeaderboardsWidget == NULL) return;
    (*(void (__fastcall **)(int *, Sexy::Widget*))(*lawnApp->mWidgetManager + 28))(lawnApp->mWidgetManager,mMainMenuLeaderboardsWidget); // RemoveWidget()
    (*((void (__fastcall **)(LawnApp *, Sexy::Widget *))lawnApp->vTable + 47))(lawnApp,mMainMenuLeaderboardsWidget); // MSGBOX()
    mMainMenuLeaderboardsWidget = NULL;
}

void LawnApp_ShowZombatarScreen(LawnApp *lawnApp) {
    mMainMenuZombatarWidget = (ZombatarWidget *) operator new(sizeof(ZombatarWidget));
    ZombatarWidget_ZombatarWidget(mMainMenuZombatarWidget, lawnApp);
//    Sexy_Widget_Resize(mMainMenuZombatarWidget,-80,-60,960,720);
    (*(void (__fastcall **)(int *, Sexy::Widget*))(*lawnApp->mWidgetManager + 24))(lawnApp->mWidgetManager,mMainMenuZombatarWidget); // AddWidget()
    (*(void (__fastcall **)(int *, Sexy::Widget*))(*lawnApp->mWidgetManager + 48))(lawnApp->mWidgetManager,mMainMenuZombatarWidget); // SetFocusedWidget()
}

void LawnApp_KillZombatarScreen(LawnApp *lawnApp) {
    if (mMainMenuZombatarWidget == NULL) return;
    (*(void (__fastcall **)(int *, Sexy::Widget*))(*lawnApp->mWidgetManager + 28))(lawnApp->mWidgetManager,mMainMenuZombatarWidget); // RemoveWidget()
    (*((void (__fastcall **)(LawnApp *, Sexy::Widget *))lawnApp->vTable + 47))(lawnApp,mMainMenuZombatarWidget); // MSGBOX()
    mMainMenuZombatarWidget = NULL;
}

char houseControl[6][15] = {"anim_house_1_1","anim_house_1_1","anim_house_1_2","anim_house_1_3","anim_house_1_4","anim_house_1_5"};

char housePrefix[5][8] = {"house_1","house_2","house_3","house_4","house_5"};

void LawnApp_SetHouseReanim(LawnApp *lawnApp, Reanimation *houseAnimation) {
    PlayerInfo *mPlayerInfo = lawnApp->mPlayerInfo;
    if (mPlayerInfo == NULL) return;
    HouseType::HouseType currentHouseType = mPlayerInfo->mGameStats.mHouseType;
    int currentHouseLevel = mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_BLUEPRINT_BLING + currentHouseType];
    if (currentHouseType == HouseType::BLUEPRINT_BLING) {
        if (LawnApp_CanShowStore(lawnApp)) {
            currentHouseLevel += 3;
        } else if (LawnApp_CanShowAlmanac(lawnApp)) {
            currentHouseLevel += 2;
        } else {
            currentHouseLevel += 1;
        }
    }

    Reanimation_PlayReanim(houseAnimation, houseControl[currentHouseLevel], ReanimLoopType::Loop, 0, 12.0f);

    for (int i = 0; i < 5; ++i) {
        Reanimation_HideTrackByPrefix(houseAnimation, housePrefix[i], i != currentHouseType);
    }

    Reanimation_HideTrackByPrefix(houseAnimation,"achievement",true);
}

bool zombatarResLoaded = false;

void LawnApp_LoadZombatarResources(LawnApp* lawnApp) {
    if (zombatarResLoaded) return;
    Addon_Images.zombatar_main_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_main_bg");
    Addon_Images.zombatar_widget_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_widget_bg");
    Addon_Images.zombatar_widget_inner_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_widget_inner_bg");
    Addon_Images.zombatar_display_window = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_display_window");
    Addon_Images.zombatar_mainmenuback_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_mainmenuback_highlight");
    Addon_Images.zombatar_finished_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_finished_button");
    Addon_Images.zombatar_finished_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_finished_button_highlight");
    Addon_Images.zombatar_view_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_view_button");
    Addon_Images.zombatar_view_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_view_button_highlight");
    Addon_Images.zombatar_skin_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_skin_button");
    Addon_Images.zombatar_skin_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_skin_button_highlight");
    Addon_Images.zombatar_hair_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_button");
    Addon_Images.zombatar_hair_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_button_highlight");
    Addon_Images.zombatar_fhair_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_fhair_button");
    Addon_Images.zombatar_fhair_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_fhair_button_highlight");
    Addon_Images.zombatar_tidbits_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_button");
    Addon_Images.zombatar_tidbits_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_button_highlight");
    Addon_Images.zombatar_eyewear_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_button");
    Addon_Images.zombatar_eyewear_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_button_highlight");
    Addon_Images.zombatar_clothes_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_button");
    Addon_Images.zombatar_clothes_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_button_highlight");
    Addon_Images.zombatar_accessory_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_button");
    Addon_Images.zombatar_accessory_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_button_highlight");
    Addon_Images.zombatar_hats_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_button");
    Addon_Images.zombatar_hats_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_button_highlight");
    Addon_Images.zombatar_next_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_next_button");
    Addon_Images.zombatar_prev_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_prev_button");
    Addon_Images.zombatar_backdrops_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_backdrops_button");
    Addon_Images.zombatar_backdrops_button_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_backdrops_button_highlight");
    Addon_Images.zombatar_background_crazydave = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_crazydave");
    Addon_Images.zombatar_background_menu = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_menu");
    Addon_Images.zombatar_background_menu_dos = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_menu_dos");
    Addon_Images.zombatar_background_roof = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_roof");
    Addon_Images.zombatar_background_blank = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_blank");
    Addon_Images.zombatar_background_aquarium = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_aquarium");
    Addon_Images.zombatar_background_crazydave_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_crazydave_night");
    Addon_Images.zombatar_background_day_RV = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_day_RV");
    Addon_Images.zombatar_background_fog_sunshade = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_fog_sunshade");
    Addon_Images.zombatar_background_garden_hd = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_garden_hd");
    Addon_Images.zombatar_background_garden_moon = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_garden_moon");
    Addon_Images.zombatar_background_garden_mushrooms = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_garden_mushrooms");
    Addon_Images.zombatar_background_hood = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood");
    Addon_Images.zombatar_background_hood_blue = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood_blue");
    Addon_Images.zombatar_background_hood_brown = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood_brown");
    Addon_Images.zombatar_background_hood_yellow = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_hood_yellow");
    Addon_Images.zombatar_background_mausoleum = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_mausoleum");
    Addon_Images.zombatar_background_moon = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_moon");
    Addon_Images.zombatar_background_moon_distant = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_moon_distant");
    Addon_Images.zombatar_background_night_RV = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_night_RV");
    Addon_Images.zombatar_background_pool_sunshade = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_pool_sunshade");
    Addon_Images.zombatar_background_roof_distant = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_roof_distant");
    Addon_Images.zombatar_background_sky_day = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_sky_day");
    Addon_Images.zombatar_background_sky_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_sky_night");
    Addon_Images.zombatar_background_sky_purple = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_sky_purple");
    Addon_Images.zombatar_background_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_7");
    Addon_Images.zombatar_background_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_8");
    Addon_Images.zombatar_background_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_9");
    Addon_Images.zombatar_background_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_10");
    Addon_Images.zombatar_background_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_11");
    Addon_Images.zombatar_background_11_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_11_1");
    Addon_Images.zombatar_background_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_12");
    Addon_Images.zombatar_background_12_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_12_1");
    Addon_Images.zombatar_background_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_13");
    Addon_Images.zombatar_background_13_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_13_1");
    Addon_Images.zombatar_background_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_14");
    Addon_Images.zombatar_background_14_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_14_1");
    Addon_Images.zombatar_background_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_15");
    Addon_Images.zombatar_background_15_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_15_1");
    Addon_Images.zombatar_background_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_16");
    Addon_Images.zombatar_background_16_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_16_1");
    Addon_Images.zombatar_background_17 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_17");
    Addon_Images.zombatar_background_17_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_17_1");
    Addon_Images.zombatar_background_bej3_bridge_shroom_castles = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_bridge_shroom_castles");
    Addon_Images.zombatar_background_bej3_canyon_wall = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_canyon_wall");
    Addon_Images.zombatar_background_bej3_crystal_mountain_peak = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_crystal_mountain_peak");
    Addon_Images.zombatar_background_bej3_dark_cave_thing = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_dark_cave_thing");
    Addon_Images.zombatar_background_bej3_desert_pyramids_sunset = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_desert_pyramids_sunset");
    Addon_Images.zombatar_background_bej3_fairy_cave_village = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_fairy_cave_village");
    Addon_Images.zombatar_background_bej3_floating_rock_city = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_floating_rock_city");
    Addon_Images.zombatar_background_bej3_horse_forset_tree = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_horse_forset_tree");
    Addon_Images.zombatar_background_bej3_jungle_ruins_path = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_jungle_ruins_path");
    Addon_Images.zombatar_background_bej3_lantern_plants_world = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_lantern_plants_world");
    Addon_Images.zombatar_background_bej3_lightning = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_lightning");
    Addon_Images.zombatar_background_bej3_lion_tower_cascade = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_lion_tower_cascade");
    Addon_Images.zombatar_background_bej3_pointy_ice_path = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_pointy_ice_path");
    Addon_Images.zombatar_background_bej3_pointy_ice_path_purple = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_pointy_ice_path_purple");
    Addon_Images.zombatar_background_bej3_rock_city_lake = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_rock_city_lake");
    Addon_Images.zombatar_background_bej3_snowy_cliffs_castle = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_snowy_cliffs_castle");
    Addon_Images.zombatar_background_bej3_treehouse_waterfall = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_treehouse_waterfall");
    Addon_Images.zombatar_background_bej3_tube_forest_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_tube_forest_night");
    Addon_Images.zombatar_background_bej3_water_bubble_city = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_water_bubble_city");
    Addon_Images.zombatar_background_bej3_water_fall_cliff = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bej3_water_fall_cliff");
    Addon_Images.zombatar_background_bejblitz_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bejblitz_6");
    Addon_Images.zombatar_background_bejblitz_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bejblitz_8");
    Addon_Images.zombatar_background_bejblitz_main_menu = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_bejblitz_main_menu");
    Addon_Images.zombatar_background_peggle_bunches = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_bunches");
    Addon_Images.zombatar_background_peggle_fever = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_fever");
    Addon_Images.zombatar_background_peggle_level1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_level1");
    Addon_Images.zombatar_background_peggle_level4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_level4");
    Addon_Images.zombatar_background_peggle_level5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_level5");
    Addon_Images.zombatar_background_peggle_menu = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_menu");
    Addon_Images.zombatar_background_peggle_nights_bjorn3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_bjorn3");
    Addon_Images.zombatar_background_peggle_nights_bjorn4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_bjorn4");
    Addon_Images.zombatar_background_peggle_nights_claude5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_claude5");
    Addon_Images.zombatar_background_peggle_nights_kalah1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_kalah1");
    Addon_Images.zombatar_background_peggle_nights_kalah4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_kalah4");
    Addon_Images.zombatar_background_peggle_nights_master5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_master5");
    Addon_Images.zombatar_background_peggle_nights_renfield5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_renfield5");
    Addon_Images.zombatar_background_peggle_nights_tut5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_tut5");
    Addon_Images.zombatar_background_peggle_nights_warren3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_nights_warren3");
    Addon_Images.zombatar_background_peggle_paperclips = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_paperclips");
    Addon_Images.zombatar_background_peggle_waves = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_background_peggle_waves");
    Addon_Images.zombatar_hair_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_1");
    Addon_Images.zombatar_hair_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_1_mask");
    Addon_Images.zombatar_hair_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_2");
    Addon_Images.zombatar_hair_2_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_2_mask");
    Addon_Images.zombatar_hair_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_3");
    Addon_Images.zombatar_hair_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_4");
    Addon_Images.zombatar_hair_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_5");
    Addon_Images.zombatar_hair_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_6");
    Addon_Images.zombatar_hair_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_7");
    Addon_Images.zombatar_hair_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_8");
    Addon_Images.zombatar_hair_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_9");
    Addon_Images.zombatar_hair_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_10");
    Addon_Images.zombatar_hair_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_11");
    Addon_Images.zombatar_hair_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_11_mask");
    Addon_Images.zombatar_hair_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_12");
    Addon_Images.zombatar_hair_12_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_12_mask");
    Addon_Images.zombatar_hair_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_13");
    Addon_Images.zombatar_hair_13_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_13_mask");
    Addon_Images.zombatar_hair_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_14");
    Addon_Images.zombatar_hair_14_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_14_mask");
    Addon_Images.zombatar_hair_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_15");
    Addon_Images.zombatar_hair_15_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_15_mask");
    Addon_Images.zombatar_hair_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hair_16");
    Addon_Images.zombatar_facialhair_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_1");
    Addon_Images.zombatar_facialhair_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_1_mask");
    Addon_Images.zombatar_facialhair_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_2");
    Addon_Images.zombatar_facialhair_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_3");
    Addon_Images.zombatar_facialhair_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_4");
    Addon_Images.zombatar_facialhair_4_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_4_mask");
    Addon_Images.zombatar_facialhair_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_5");
    Addon_Images.zombatar_facialhair_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_6");
    Addon_Images.zombatar_facialhair_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_7");
    Addon_Images.zombatar_facialhair_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_8");
    Addon_Images.zombatar_facialhair_8_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_8_mask");
    Addon_Images.zombatar_facialhair_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_9");
    Addon_Images.zombatar_facialhair_9_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_9_mask");
    Addon_Images.zombatar_facialhair_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_10");
    Addon_Images.zombatar_facialhair_10_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_10_mask");
    Addon_Images.zombatar_facialhair_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_11");
    Addon_Images.zombatar_facialhair_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_11_mask");
    Addon_Images.zombatar_facialhair_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_12");
    Addon_Images.zombatar_facialhair_12_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_12_mask");
    Addon_Images.zombatar_facialhair_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_13");
    Addon_Images.zombatar_facialhair_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_14");
    Addon_Images.zombatar_facialhair_14_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_14_mask");
    Addon_Images.zombatar_facialhair_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_15");
    Addon_Images.zombatar_facialhair_15_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_15_mask");
    Addon_Images.zombatar_facialhair_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_16");
    Addon_Images.zombatar_facialhair_16_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_16_mask");
    Addon_Images.zombatar_facialhair_17 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_17");
    Addon_Images.zombatar_facialhair_18 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_18");
    Addon_Images.zombatar_facialhair_18_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_18_mask");
    Addon_Images.zombatar_facialhair_19 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_19");
    Addon_Images.zombatar_facialhair_20 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_20");
    Addon_Images.zombatar_facialhair_21 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_21");
    Addon_Images.zombatar_facialhair_21_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_21_mask");
    Addon_Images.zombatar_facialhair_22 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_22");
    Addon_Images.zombatar_facialhair_22_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_22_mask");
    Addon_Images.zombatar_facialhair_23 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_23");
    Addon_Images.zombatar_facialhair_23_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_23_mask");
    Addon_Images.zombatar_facialhair_24 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_24");
    Addon_Images.zombatar_facialhair_24_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_facialhair_24_mask");
    Addon_Images.zombatar_eyewear_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_1");
    Addon_Images.zombatar_eyewear_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_1_mask");
    Addon_Images.zombatar_eyewear_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_2");
    Addon_Images.zombatar_eyewear_2_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_2_mask");
    Addon_Images.zombatar_eyewear_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_3");
    Addon_Images.zombatar_eyewear_3_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_3_mask");
    Addon_Images.zombatar_eyewear_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_4");
    Addon_Images.zombatar_eyewear_4_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_4_mask");
    Addon_Images.zombatar_eyewear_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_5");
    Addon_Images.zombatar_eyewear_5_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_5_mask");
    Addon_Images.zombatar_eyewear_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_6");
    Addon_Images.zombatar_eyewear_6_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_6_mask");
    Addon_Images.zombatar_eyewear_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_7");
    Addon_Images.zombatar_eyewear_7_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_7_mask");
    Addon_Images.zombatar_eyewear_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_8");
    Addon_Images.zombatar_eyewear_8_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_8_mask");
    Addon_Images.zombatar_eyewear_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_9");
    Addon_Images.zombatar_eyewear_9_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_9_mask");
    Addon_Images.zombatar_eyewear_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_10");
    Addon_Images.zombatar_eyewear_10_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_10_mask");
    Addon_Images.zombatar_eyewear_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_11");
    Addon_Images.zombatar_eyewear_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_11_mask");
    Addon_Images.zombatar_eyewear_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_12");
    Addon_Images.zombatar_eyewear_12_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_12_mask");
    Addon_Images.zombatar_eyewear_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_13");
    Addon_Images.zombatar_eyewear_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_14");
    Addon_Images.zombatar_eyewear_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_15");
    Addon_Images.zombatar_eyewear_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_eyewear_16");
    Addon_Images.zombatar_accessory_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_1");
    Addon_Images.zombatar_accessory_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_2");
    Addon_Images.zombatar_accessory_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_3");
    Addon_Images.zombatar_accessory_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_4");
    Addon_Images.zombatar_accessory_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_5");
    Addon_Images.zombatar_accessory_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_6");
    Addon_Images.zombatar_accessory_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_8");
    Addon_Images.zombatar_accessory_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_9");
    Addon_Images.zombatar_accessory_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_10");
    Addon_Images.zombatar_accessory_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_11");
    Addon_Images.zombatar_accessory_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_12");
    Addon_Images.zombatar_accessory_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_13");
    Addon_Images.zombatar_accessory_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_14");
    Addon_Images.zombatar_accessory_15 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_15");
    Addon_Images.zombatar_accessory_16 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_16");
    Addon_Images.zombatar_hats_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_1");
    Addon_Images.zombatar_hats_1_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_1_mask");
    Addon_Images.zombatar_hats_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_2");
    Addon_Images.zombatar_hats_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_3");
    Addon_Images.zombatar_hats_3_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_3_mask");
    Addon_Images.zombatar_hats_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_4");
    Addon_Images.zombatar_hats_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_5");
    Addon_Images.zombatar_hats_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_6");
    Addon_Images.zombatar_hats_6_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_6_mask");
    Addon_Images.zombatar_hats_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_7");
    Addon_Images.zombatar_hats_7_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_7_mask");
    Addon_Images.zombatar_hats_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_8");
    Addon_Images.zombatar_hats_8_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_8_mask");
    Addon_Images.zombatar_hats_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_9");
    Addon_Images.zombatar_hats_9_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_9_mask");
    Addon_Images.zombatar_hats_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_10");
    Addon_Images.zombatar_hats_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_11");
    Addon_Images.zombatar_hats_11_mask = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_11_mask");
    Addon_Images.zombatar_hats_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_12");
    Addon_Images.zombatar_hats_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_13");
    Addon_Images.zombatar_hats_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_hats_14");
    Addon_Images.zombatar_tidbits_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_1");
    Addon_Images.zombatar_tidbits_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_2");
    Addon_Images.zombatar_tidbits_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_3");
    Addon_Images.zombatar_tidbits_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_4");
    Addon_Images.zombatar_tidbits_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_5");
    Addon_Images.zombatar_tidbits_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_6");
    Addon_Images.zombatar_tidbits_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_7");
    Addon_Images.zombatar_tidbits_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_8");
    Addon_Images.zombatar_tidbits_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_9");
    Addon_Images.zombatar_tidbits_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_10");
    Addon_Images.zombatar_tidbits_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_11");
    Addon_Images.zombatar_tidbits_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_12");
    Addon_Images.zombatar_tidbits_13 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_13");
    Addon_Images.zombatar_tidbits_14 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_tidbits_14");
    Addon_Images.zombatar_clothes_1 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_1");
    Addon_Images.zombatar_clothes_2 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_2");
    Addon_Images.zombatar_clothes_3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_3");
    Addon_Images.zombatar_clothes_4 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_4");
    Addon_Images.zombatar_clothes_5 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_5");
    Addon_Images.zombatar_clothes_6 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_6");
    Addon_Images.zombatar_clothes_7 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_7");
    Addon_Images.zombatar_clothes_8 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_8");
    Addon_Images.zombatar_clothes_9 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_9");
    Addon_Images.zombatar_clothes_10 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_10");
    Addon_Images.zombatar_clothes_11 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_11");
    Addon_Images.zombatar_clothes_12 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_clothes_12");
    Addon_Images.zombatar_zombie_blank = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_zombie_blank");
    Addon_Images.zombatar_zombie_blank_skin = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_zombie_blank_skin");
    int xClip = 130;
    int yClip = 130;
    TRect rect = {Addon_Images.zombatar_zombie_blank->mWidth - xClip,Addon_Images.zombatar_zombie_blank->mHeight - yClip,xClip,yClip};
    Addon_Images.zombatar_zombie_blank_part = Sexy_SexyAppBase_CopyImage2(lawnApp,Addon_Images.zombatar_zombie_blank,&rect);
    Addon_Images.zombatar_zombie_blank_skin_part = Sexy_SexyAppBase_CopyImage2(lawnApp,Addon_Images.zombatar_zombie_blank_skin,&rect);
    Addon_Images.zombatar_colors_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_colors_bg");
    Addon_Images.zombatar_colorpicker = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_colorpicker");
    Addon_Images.zombatar_colorpicker_none = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_colorpicker_none");
    Addon_Images.zombatar_accessory_bg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_bg");
    Addon_Images.zombatar_accessory_bg_highlight = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_bg_highlight");
    Addon_Images.zombatar_accessory_bg_none = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/zombatar_accessory_bg_none");
    zombatarResLoaded = true;
}


#endif //PVZ_TV_1_1_5_LAWNAPP_CPP
