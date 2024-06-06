//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_LAWNAPP_H
#define PVZ_TV_1_1_5_LAWNAPP_H

#include "../Enums.h"

void (*LawnApp_KillChallengeScreen)(LawnApp* lawnApp);

void (*LawnApp_KillMainMenu)(LawnApp* lawnApp);

void (*LawnApp_KillNewOptionsDialog)(LawnApp* lawnApp);

void (*LawnApp_PreNewGame)(LawnApp* lawnApp, GameMode::GameMode a2, bool a3);

bool (*LawnApp_CanShowStore)(LawnApp *lawnApp);

bool (*LawnApp_CanShowAlmanac)(LawnApp *lawnApp);

bool LawnApp_CanShopLevel(LawnApp *lawnApp);

void (*LawnApp_PlayFoley)(LawnApp* lawnApp, FoleyType::FoleyType theFoleyType);

void (*LawnApp_PlayFoleyPitch)(LawnApp* lawnApp, FoleyType::FoleyType theFoleyType,float aPitch);

void (*LawnApp_DoCheatDialog)(LawnApp *lawnApp);

void (*LawnApp_DoCheatCodeDialog)(LawnApp *lawnApp);

void (*LawnApp_DoUserDialog)(LawnApp *lawnApp);

Reanimation* (*LawnApp_ReanimationTryToGet)(LawnApp* lawnApp, int a2);

void (*LawnApp_ClearSecondPlayer)(LawnApp *lawnApp);

bool (*LawnApp_IsScaryPotterLevel)(LawnApp *lawnApp);

bool (*LawnApp_IsWhackAZombieLevel)(LawnApp *lawnApp);

bool (*LawnApp_IsFirstTimeAdventureMode)(LawnApp *lawnApp);

bool (*LawnApp_IsAdventureMode)(LawnApp *lawnApp);

bool (*LawnApp_IsWallnutBowlingLevel)(LawnApp *lawnApp);

bool (*LawnApp_IsCoopMode)(LawnApp *lawnApp);

bool (*LawnApp_IsTwinSunbankMode)(LawnApp *lawnApp);

bool (*LawnApp_IsIZombieLevel)(LawnApp *lawnApp);

bool (*LawnApp_IsSurvivalMode)(LawnApp*);

bool (*LawnApp_IsPuzzleMode)(LawnApp*);

bool (*LawnApp_IsFinalBossLevel)(LawnApp *);

bool (*LawnApp_IsArtChallenge)(LawnApp *);

Reanimation* (*LawnApp_ReanimationGet)(LawnApp *lawnApp, int theReanimationId);

//阻塞式函数，能创建并立即展示一个带按钮的对话框。按钮个数由最后一个参数决定。其返回值就是用户按下的按钮ID，一般情况下只可能为1000或1001。
int (*LawnApp_LawnMessageBox)(LawnApp *lawnApp,
                               Dialogs::Dialogs theDialogId,//用于标识本对话框的ID，以便于用KillDialog(theDialogId)关闭此对话框。一般用不到，所以随便填个数字就可以。
                              const char *theHeaderName,
                              const char *theLinesName,
                              const char *theButton1Name,
                              const char *theButton2Name,
                              int theButtonMode);//取值为0，1，2，3。其中0就是无按钮；1和2会展示两个按钮，其ID分别为1000和1001；3只会展示一个按钮，其ID为1000。

TodParticleSystem* (*LawnApp_AddTodParticle)(LawnApp* lawnApp, float, float, int, ParticleEffect::ParticleEffect);

int (*LawnApp_ParticleGetID)(LawnApp* ,TodParticleSystem*);

Reanimation* (*LawnApp_AddReanimation)(LawnApp*,float ,float ,int ,ReanimationType::ReanimationType);

void (*LawnApp_ShowChallengeScreen)(LawnApp*, ChallengePage::ChallengePage);

bool (*LawnApp_HasFinishedAdventure)(LawnApp *);

void LawnApp_DoNewOptions(LawnApp *lawnApp, bool a2, unsigned int a3);

Sexy::Image *LawnApp_GetImageByFileName(LawnApp *lawnApp, const char *fileName);

int LawnApp_GetSoundByFileName(LawnApp *lawnApp, const char *fileName);

void LawnApp_PlaySample(LawnApp *lawnApp, int soundId);

void (*LawnApp_KillVSResultsScreen)(LawnApp*);

void(*LawnApp_HideHelpBarWidget)(LawnApp*);

void(*LawnApp_ShowHelpTextScreen)(LawnApp*,int);

int (*LawnApp_GetPottedPlantByIndex)(LawnApp*,int);

void (*LawnApp_CrazyDaveStopTalking)(LawnApp*);

void (*LawnApp_NextTestDialog)(LawnApp*);

void (*LawnApp_DoRetryAchievementsDialog)(LawnApp*);

bool (*LawnApp_EarnedGoldTrophy)(LawnApp *);

void (*LawnApp_RemoveReanimation)(LawnApp*,int);

int (*LawnApp_ReanimationGetID)(LawnApp*,Reanimation*);

bool (*LawnApp_IsSlotMachineLevel)(LawnApp*);

void (*LawnApp_KillAlmanacDialog)(LawnApp*);

void (*LawnApp_KillHelpTextScreen)(LawnApp*);

bool (*LawnApp_IsLittleTroubleLevel)(LawnApp*);

bool LawnApp_GrantAchievement(LawnApp* lawnApp,AchievementId::AchievementId theAchievementId);

void LawnApp_DoBackToMain(LawnApp *lawnApp);

int* (*Sexy_SexyAppBase_GetDialog)(LawnApp *lawnApp, Dialogs::Dialogs dialogId);

bool LawnApp_IsChallengeWithoutSeedBank(LawnApp*);

bool LawnApp_IsNight(LawnApp*);

int (*LawnApp_GetNumTrophies)(LawnApp*, ChallengePage::ChallengePage );

void LawnApp_SetFoleyVolume(LawnApp *lawnApp, FoleyType::FoleyType type, double theVolume);

bool (*LawnApp_IsSurvivalEndless)(LawnApp *lawnApp, GameMode::GameMode );

void LawnApp_KillDialog(LawnApp* lawnApp,Dialogs::Dialogs id);

void LawnApp_ShowLeaderboards(LawnApp *lawnApp);

void LawnApp_KillLeaderboards(LawnApp *lawnApp);

void LawnApp_SetHouseReanim(LawnApp *lawnApp, Reanimation *houseAnimation);

void (*LawnApp_ShowMainMenuScreen)(LawnApp* lawnApp);

TodParticleSystem * (*LawnApp_ParticleTryToGet)(LawnApp *lawnApp,int);

void LawnApp_LoadZombatarResources(LawnApp* lawnApp);
#endif //PVZ_TV_1_1_5_LAWNAPP_H
