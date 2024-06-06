
#include "HookAddr.h"
#include "HookGame/SeedBank/SeedBank.cpp"
#include "HookGame/Board/Board.cpp"
#include "Board/BoardTouch.cpp"
#include "HookGame/AlmanacDialog/AlmanacDialog.cpp"
#include "HookGame/ZenGarden/ZenGarden.cpp"
#include "ZenGarden/ZenGarden.h"
#include "StoreScreen/StoreScreenTouch.cpp"
#include "HouseChooserDialog/HouseChooserDialog.cpp"
#include "HouseChooserDialog/HouseChooserDialog.h"
#include "HookGame/StoreScreen/StoreScreen.cpp"
#include "HookGame/MailScreen/MailScreen.cpp"
#include "MailScreen/MailScreenTouch.cpp"
#include "SettingsDialog/SettingsDialog.cpp"
#include "ConfirmBackToMainDialog/ConfirmBackToMainDialog.cpp"
#include "ConfirmBackToMainDialog/ConfirmBackToMainDialog.h"
#include "AwardScreen/AwardScreen.h"
#include "AwardScreen/AwardScreenTouch.cpp"
#include "HookGame/ChallengeScreen/ChallengeScreen.cpp"
#include "ChallengeScreen/ChallengeScreen.h"
#include "ChallengeScreen/ChallengeScreenTouch.cpp"
#include "HookGame/HelpOptionsDialog/HelpOptionsDialog.cpp"
#include "HelpTextScreen/HelpTextScreenTouch.cpp"
#include "HelpTextScreen/HelpTextScreen.h"
#include "SeedChooserScreen/SeedChooserScreenTouch.cpp"
#include "HookGame/VSResultsMenu/VSResultsMenu.cpp"
#include "VSResultsMenu/VSResultsMenu.h"
#include "HookGame/CutScene/CutScene.cpp"
#include "CutScene/CutScene.h"
#include "HookGame/ImitaterDialog/ImitaterDialog.cpp"
#include "ImitaterDialog/ImitaterDialog.h"
#include "Graphics/Graphics.h"
#include "HookGame/LawnApp/LawnApp.cpp"
#include "HookGame/Challenge/Challenge.cpp"
#include "HookGame/Plant/Plant.cpp"
#include "HookGame/SeedPacket/SeedPacket.cpp"
#include "HookGame/SeedChooserScreen/SeedChooserScreen.cpp"
#include "HookGame/Reanimation/Reanimation.cpp"
#include "HookGame/Zombie/Zombie.cpp"
#include "HookGame/VSSetupMenu/VSSetupMenu.cpp"
#include "HookGame/MainMenu/MainMenu.cpp"
#include "HookGame/Projectile/Projectile.cpp"
#include "HookGame/Coin/Coin.cpp"
#include "HookGame/GamepadControls/GamepadControls.cpp"
#include "SeedPacket/SeedPacket.h"
#include "HookGame/Misc/Misc.cpp"
#include "HookGame/GridItem/GridItem.cpp"
#include "HookGame/SeedBank/SeedBank.h"
#include "HookGame/Graphics/Graphics.cpp"
#include "HookGame/Music/Music.cpp"
#include "HookGame/OpenSL/OpenSL.cpp"
#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>
#include <bits/sysconf.h>
#include <asm-generic/mman-common.h>
#include <sys/mman.h>


#define targetLibName "libGameMain.so"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;


void InitInGameFunction() {
    Board_Move = (void (*)(Board *, int, int)) Board_MoveAddr;
    Board_ProgressMeterHasFlags = (bool (*)(Board *)) Board_ProgressMeterHasFlagsAddr;
    Board_IsSurvivalStageWithRepick = (bool (*)(Board *)) Board_IsSurvivalStageWithRepickAddr;
    Board_PickUpTool = (void (*)(Board *, GameObjectType::GameObjectType, int)) Board_PickUpToolAddr;
    Board_IteratePlants = (bool (*)(Board*,  Plant **)) Board_IteratePlantsAddr;
    Board_IterateProjectiles = (bool (*)(Board*,  Projectile **)) Board_IterateProjectilesAddr;
    Board_IterateCoins = (bool (*)(Board*,  Coin **)) Board_IterateCoinsAddr;
    Board_IterateLawnMowers = (bool (*)(Board*,  int **)) Board_IterateLawnMowersAddr;
    Board_IterateParticles=(bool (*)(Board*,TodParticleSystem**))Board_IterateParticlesAddr;
    Board_IterateGridItems = (bool (*)(Board*,  GridItem **)) Board_IterateGridItemsAddr;
    Board_IterateZombies = (bool (*)(Board*,  Zombie **)) Board_IterateZombiesAddr;
    Board_AddProjectile = (Projectile* (*)(Board*, int, int, int, int, ProjectileType::ProjectileType)) Board_AddProjectileAddr;
    Board_GameAxisMove = (int (*)(Board *, int, int, int)) Board_GameAxisMoveAddr;
    Board_InitCoverLayer = (int (*)(Board *)) Board_InitCoverLayerAddr;
    Board_LoadBackgroundImages = (int (*)(Board *)) Board_LoadBackgroundImagesAddr;
    Board_HasConveyorBeltSeedBank = (int (*)(Board *, int)) Board_HasConveyorBeltSeedBankAddr;
    //Board_UpdateGridItems = (int (*)(Board *)) Board_UpdateGridItemsAddr;
    Board_ZombieHitTest = (Zombie *(*)(Board *, int, int, int)) Board_ZombieHitTestAddr;
    Board_GetTopPlantAt = (Plant* (*)(Board *, unsigned int, unsigned int, TopPlant::TopPlant)) Board_GetTopPlantAtAddr;
    Board_NewPlant = (int (*)(Board *, int, int, SeedType::SeedType, SeedType::SeedType, int)) Board_NewPlantAddr;
    Board_CanUseGameObject = (int (*)(Board *, GameObjectType::GameObjectType)) Board_CanUseGameObjectAddr;
    Board_ToolHitTest = (Plant* (*)(Board *, int, int)) Board_ToolHitTestAddr;
    Board_RefreshSeedPacketFromCursor = (int (*)(Board *,int)) Board_RefreshSeedPacketFromCursorAddr;
    Board_GetPlantsOnLawn = (Plant* (*)(Board*, unsigned int, unsigned int,int *)) Board_GetPlantsOnLawnAddr;
    Board_GridToPixelX = (int (*)(Board *, unsigned int, unsigned int)) Board_GridToPixelXAddr;
    Board_GridToPixelY = (int (*)(Board *, unsigned int, unsigned int)) Board_GridToPixelYAddr;
    Board_PixelToGridY = (int (*)(Board *, unsigned int, unsigned int)) Board_PixelToGridYAddr;
    Board_PixelToGridX = (int (*)(Board *, unsigned int, unsigned int)) Board_PixelToGridXAddr;
    Board_AddALadder = (GridItem* (*)(Board *, int, int)) Board_AddALadderAddr;
    Board_ClearCursor = (int (*)(Board *, int)) Board_ClearCursorAddr;
    Board_MouseDownWithTool = (int (*)(Board *, int, int, int, int, int)) Board_MouseDownWithToolAddr;
    Board_CountPlantByType = (int (*)(Board *, int)) Board_CountPlantByTypeAddr;
    Board_SetTutorialState = (int (*)(Board *, int)) Board_SetTutorialStateAddr;
    Board_DoFwoosh = (void (*)(Board*, int)) Board_DoFwooshAddr;
    Board_ShakeBoard = (void (*)(Board*, int, int)) Board_ShakeBoardAddr;
    Board_GetButterButtonRect = (void (*)(TRect *, Board *)) Board_GetButterButtonRectAddr;
   // Board_GetShovelButtonRect = (void (*)(TRect *, Board *)) Board_GetShovelButtonRectAddr;
    Board_ZombieTryToGet = (Zombie *(*)(Board *, Zombie*)) Board_ZombieTryToGetAddr;
    Board_MakeRenderOrder = (int (*)(int, int, int)) Board_MakeRenderOrderAddr;
    Board_PlantUsesAcceleratedPricing = (bool (*)(Board*, SeedType::SeedType)) Board_PlantUsesAcceleratedPricingAddr;
    Board_IsPlantInCursor = (bool (*)(Board *)) Board_IsPlantInCursorAddr;
    Board_MouseDownWithPlant = (void (*)(Board *, int, int, int)) Board_MouseDownWithPlantAddr;
    Board_CanInteractWithBoardButtons = (bool (*)(Board *)) Board_CanInteractWithBoardButtonsAddr;
    Board_RemoveAllPlants = (void (*)(Board *)) Board_RemoveAllPlantsAddr;
    Board_GetSeedBankExtraWidth = (int (*)(Board *)) Board_GetSeedBankExtraWidthAddr;
    Board_GetSeedPacketPositionX=(int (*)(Board*,int,int,bool))Board_GetSeedPacketPositionXAddr;
    Board_AddCoin = (Coin *(*)(Board *, int, int, int, int)) Board_AddCoinAddr;
    Board_CanTakeSunMoney = (bool (*)(Board *, int, int)) Board_CanTakeSunMoneyAddr;
    Board_GetZenButtonRect = (void (*)(TRect *, Board *, GameObjectType::GameObjectType)) Board_GetZenButtonRectAddr;
    Board_GetGridItemAt = (GridItem* (*)(Board *, GridItemType::GridItemType, int, int)) Board_GetGridItemAtAddr;
    Board_GetLadderAt = (GridItem *(*)(Board *, int, int)) Board_GetLadderAtAddr;
    Board_PixelToGridXKeepOnBoard = (int (*)(Board *, int, int)) Board_PixelToGridXKeepOnBoardAddr;
    Board_PixelToGridYKeepOnBoard = (int (*)(Board *, int, int)) Board_PixelToGridYKeepOnBoardAddr;
    Board_IsValidCobCannonSpotHelper = (bool (*)(Board *, int, int)) Board_IsValidCobCannonSpotHelperAddr;
    Board_PickRowForNewZombie = (int (*)(Board *, int)) Board_PickRowForNewZombieAddr;
    Board_IsPoolSquare=(bool (*)(Board*,int,int))Board_IsPoolSquareAddr;
    Board_ZombiePickerInit= (void (*)(ZombiePicker*))Board_ZombiePickerInitAddr;
    Board_GetIntroducedZombieType=(ZombieType::ZombieType (*)(Board*))Board_GetIntroducedZombieTypeAddr;
    Board_ZombiePickerInitForWave=(void (*)(ZombiePicker*))Board_ZombiePickerInitForWaveAddr;
    Board_PutZombieInWave=(void (*)(Board*,ZombieType::ZombieType,int,ZombiePicker*))Board_PutZombieInWaveAddr;
    Board_PickZombieType=(ZombieType::ZombieType (*)(Board*,int,int,ZombiePicker*))Board_PickZombieTypeAddr;
    Board_HasLevelAwardDropped= (bool (*)(Board*))Board_HasLevelAwardDroppedAddr;
    Board_SpawnZombiesFromGraves=(void (*)(Board*))Board_SpawnZombiesFromGravesAddr;
    Board_ClearAdvice=(void (*)(Board*,int))Board_ClearAdviceAddr;
    Board_NextWaveComing=(void (*)(Board*))Board_NextWaveComingAddr;
    Board_TotalZombiesHealthInWave=(int (*)(Board*,int))Board_TotalZombiesHealthInWaveAddr;
    Board_ClearAdviceImmediately=(void (*)(Board*))Board_ClearAdviceImmediatelyAddr;
    Board_DisplayAdviceAgain=(void (*)(Board*,int*,MessageStyle::MessageStyle,AdviceType::AdviceType))Board_DisplayAdviceAgainAddr;
    Board_GridCellWidth=(int (*)(Board*,int,int))Board_GridCellWidthAddr;
    Board_GridCellHeight= (int (*)(Board*,int,int))Board_GridCellHeightAddr;
    //Board_GetPumpkinAt=(Plant* (*)(Board*,int,int))Board_GetPumpkinAtAddr;
    Board_GetSeedTypeInCursor=(SeedType::SeedType (*)(Board*,int))Board_GetSeedTypeInCursorAddr;
    Board_TryToSaveGame=(void (*)(Board *))Board_TryToSaveGameAddr;
    Board_KillAllZombiesInRadius=(int (*)(Board*,int,int,int,int,int,bool,int))Board_KillAllZombiesInRadiusAddr;
    Board_RemoveCutsceneZombies = (void (*)(Board *)) Board_RemoveCutsceneZombiesAddr;
    Board_CountZombiesOnScreen=(int(*)(Board*))Board_CountZombiesOnScreenAddr;
    Board_GetPosYBasedOnRow=(float (*)(Board* ,float,int))Board_GetPosYBasedOnRowAddr;
    Board_CanTakeDeathMoney=(bool (*)(Board *, int))Board_CanTakeDeathMoneyAddr;
    Board_GetBossZombie=(Zombie* (*)(Board*))Board_GetBossZombieAddr;
//    Board_GetFlowerPotAt=(int* (*)(int*,int,int))Board_GetFlowerPotAtAddr;
    Board_RemoveAllMowers = (void (*)(Board *)) Board_RemoveAllMowersAddr;
    Board_ResetLawnMowers = (void (*)(Board *)) Board_ResetLawnMowersAddr;
    Board_RemoveAllZombies = (void (*)(Board *)) Board_RemoveAllZombiesAddr;
    Board_GetGamepadControlsByPlayerIndex=(GamepadControls *(*)(Board*,int))Board_GetGamepadControlsByPlayerIndexAddr;


    LawnApp_ClearSecondPlayer = (void (*)(LawnApp *)) LawnApp_ClearSecondPlayerAddr;
    LawnApp_IsWhackAZombieLevel = (bool (*)(LawnApp *)) LawnApp_IsWhackAZombieLevelAddr;
    LawnApp_IsScaryPotterLevel = (bool (*)(LawnApp *)) LawnApp_IsScaryPotterLevelAddr;
    LawnApp_CanShowStore = (bool (*)(LawnApp *)) LawnApp_CanShowStoreAddr;
    LawnApp_CanShowAlmanac = (bool (*)(LawnApp *)) LawnApp_CanShowAlmanacAddr;
    LawnApp_KillNewOptionsDialog = (void (*)(LawnApp*)) LawnApp_KillNewOptionsDialogAddr;
    LawnApp_KillMainMenu = (void (*)(LawnApp*)) LawnApp_KillMainMenuAddr;
    LawnApp_KillChallengeScreen = (void (*)(LawnApp*)) LawnApp_KillChallengeScreenAddr;
    LawnApp_PreNewGame = (void (*)(LawnApp*, GameMode::GameMode, bool)) LawnApp_PreNewGameAddr;
    LawnApp_PlayFoley = (void (*)(LawnApp*, FoleyType::FoleyType)) LawnApp_PlayFoleyAddr;
    LawnApp_PlayFoleyPitch=(void (*)(LawnApp* , FoleyType::FoleyType ,float ))LawnApp_PlayFoleyPitchAddr;
    LawnApp_DoCheatDialog = (void (*)(LawnApp *)) LawnApp_DoCheatDialogAddr;
    LawnApp_DoCheatCodeDialog = (void (*)(LawnApp *)) LawnApp_DoCheatCodeDialogAddr;
    LawnApp_DoUserDialog = (void (*)(LawnApp *)) LawnApp_DoUserDialogAddr;
    LawnApp_ReanimationTryToGet = (Reanimation* (*)(LawnApp*, int)) LawnApp_ReanimationTryToGetAddr;
    LawnApp_IsFirstTimeAdventureMode = (bool (*)(LawnApp *)) LawnApp_IsFirstTimeAdventureModeAddr;
    LawnApp_IsAdventureMode = (bool (*)(LawnApp *)) LawnApp_IsAdventureModeAddr;
    LawnApp_IsWallnutBowlingLevel = (bool (*)(LawnApp *)) LawnApp_IsWallnutBowlingLevelAddr;
    LawnApp_IsCoopMode = (bool (*)(LawnApp *)) LawnApp_IsCoopModeAddr;
    LawnApp_IsTwinSunbankMode=(bool (*)(LawnApp *))LawnApp_IsTwinSunbankModeAddr;
    LawnApp_LawnMessageBox = (int (*)(LawnApp *, Dialogs::Dialogs, const char *, const char *, const char *, const char *, int)) LawnApp_LawnMessageBoxAddr;
    LawnApp_ReanimationGet = (Reanimation* (*)(LawnApp *, int)) LawnApp_ReanimationGetAddr;
    LawnApp_IsIZombieLevel = (bool (*)(LawnApp *)) LawnApp_IsIZombieLevelAddr;
    LawnApp_AddTodParticle = (TodParticleSystem* (*)(LawnApp*, float, float, int, ParticleEffect::ParticleEffect)) LawnApp_AddTodParticleAddr;
    LawnApp_ParticleGetID=(int (*)(LawnApp* ,TodParticleSystem*))LawnApp_ParticleGetIDAddr;
    LawnApp_AddReanimation = (Reanimation *(*)(LawnApp*, float, float, int, ReanimationType::ReanimationType)) LawnApp_AddReanimationAddr;
    LawnApp_IsSurvivalMode = (bool (*)(LawnApp *)) LawnApp_IsSurvivalModeAddr;
    LawnApp_IsPuzzleMode = (bool (*)(LawnApp *)) LawnApp_IsPuzzleModeAddr;
    LawnApp_HasFinishedAdventure = (bool (*)(LawnApp *)) LawnApp_HasFinishedAdventureAddr;
    LawnApp_IsFinalBossLevel = (bool (*)(LawnApp *)) LawnApp_IsFinalBossLevelAddr;
    LawnApp_IsArtChallenge = (bool (*)(LawnApp *)) LawnApp_IsArtChallengeAddr;
    LawnApp_KillVSResultsScreen = (void (*)(LawnApp *)) LawnApp_KillVSResultsScreenAddr;
    LawnApp_HideHelpBarWidget = (void (*)(LawnApp *)) LawnApp_HideHelpBarWidgetAddr;
    LawnApp_ShowHelpTextScreen = (void (*)(LawnApp *, int)) LawnApp_ShowHelpTextScreenAddr;
    LawnApp_ShowChallengeScreen = (void (*)(LawnApp *, ChallengePage::ChallengePage)) LawnApp_ShowChallengeScreenAddr;
    LawnApp_GetPottedPlantByIndex = (int (*)(LawnApp *, int)) LawnApp_GetPottedPlantByIndexAddr;
    LawnApp_CrazyDaveStopTalking = (void (*)(LawnApp *)) LawnApp_CrazyDaveStopTalkingAddr;
    LawnApp_DoRetryAchievementsDialog = (void (*)(LawnApp *)) LawnApp_DoRetryAchievementsDialogAddr;
    LawnApp_EarnedGoldTrophy = (bool (*)(LawnApp *)) LawnApp_EarnedGoldTrophyAddr;
    LawnApp_RemoveReanimation=(void (*)(LawnApp*,int))LawnApp_RemoveReanimationAddr;
    LawnApp_ReanimationGetID=(int (*)(LawnApp*,Reanimation*))LawnApp_ReanimationGetIDAddr;
    LawnApp_IsSlotMachineLevel=(bool (*)(LawnApp*))LawnApp_IsSlotMachineLevelAddr;
    LawnApp_KillAlmanacDialog=(void (*)(LawnApp*))LawnApp_KillAlmanacDialogAddr;
    LawnApp_IsLittleTroubleLevel=(bool (*)(LawnApp*))LawnApp_IsLittleTroubleLevelAddr;
    Sexy_SexyAppBase_GetDialog=(int* (*)(LawnApp *, Dialogs::Dialogs ))Sexy_SexyAppBase_GetDialogAddr;
    Sexy_SexyAppBase_EraseFile=(void (*)(SexyAppBase*, int*))Sexy_SexyAppBase_EraseFileAddr;
    LawnApp_GetNumTrophies=(int (*)(LawnApp*, ChallengePage::ChallengePage ))LawnApp_GetNumTrophiesAddr;
    LawnApp_IsSurvivalEndless=(bool (*)(LawnApp *, GameMode::GameMode ))LawnApp_IsSurvivalEndlessAddr;
    LawnApp_ShowMainMenuScreen=(void (*)(LawnApp* ))LawnApp_ShowMainMenuScreenAddr;
    LawnApp_ParticleTryToGet=(TodParticleSystem * (*)(LawnApp *,int))LawnApp_ParticleTryToGetAddr;
    LawnApp_KillHelpTextScreen=(void (*)(LawnApp*))LawnApp_KillHelpTextScreenAddr;
    LawnApp_NextTestDialog = (void (*)(LawnApp *)) LawnApp_NextTestDialogAddr;


    Sexy_Graphics_SetDrawMode = (void (*)(Sexy::Graphics*, DrawMode::DrawMode)) Sexy_Graphics_SetDrawModeAddr;
    Sexy_Graphics_SetColorizeImages = (void (*)(Sexy::Graphics*, bool)) Sexy_Graphics_SetColorizeImagesAddr;
    Sexy_Graphics_GetColorizeImages = (bool (*)(Sexy::Graphics *)) Sexy_Graphics_GetColorizeImagesAddr;
    Sexy_Graphics_SetFont = (void (*)(Sexy::Graphics*, Sexy::Font *)) Sexy_Graphics_SetFontAddr;
    Sexy_Graphics_FillRect = (void (*)(Sexy::Graphics *, TRect *)) Sexy_Graphics_FillRectAddr;
    Sexy_Graphics_DrawRect = (void (*)(Sexy::Graphics *, TRect *))Sexy_Graphics_DrawRectAddr;
    Sexy_Graphics_ClipRect = (void (*)(Sexy::Graphics *, int, int, int, int)) Sexy_Graphics_ClipRectAddr;
    Sexy_Graphics_SetClipRect=(void (*)(Sexy::Graphics* ,int,int,int,int))Sexy_Graphics_SetClipRectAddr;
    Sexy_Graphics_ClearClipRect=(void (*)(Sexy::Graphics*))Sexy_Graphics_ClearClipRectAddr;
    Sexy_Graphics_SetLinearBlend = (void (*)(Sexy::Graphics *, int)) Sexy_Graphics_SetLinearBlendAddr;
    Sexy_Graphics_PushState = (void (*)(Sexy::Graphics *)) Sexy_Graphics_PushStateAddr;
    Sexy_Graphics_PopState = (void (*)(Sexy::Graphics *)) Sexy_Graphics_PopStateAddr;
    Sexy_Graphics_DrawString = (void (*)(Sexy::Graphics *, int *, int, int)) Sexy_Graphics_DrawStringAddr;
    Sexy_Graphics_DrawImageCel = (void (*)(Sexy::Graphics *, Sexy::Image *, int, int, int, int)) Sexy_Graphics_DrawImageCelAddr;
    Sexy_Graphics_Graphics = (void *(*)(Sexy::Graphics *, const Sexy::Graphics *)) Sexy_Graphics_GraphicsAddr;
    Sexy_Graphics_Graphics2 = (void (*)(Sexy::Graphics *, Sexy::Image *)) Sexy_Graphics_Graphics2Addr;
    Sexy_Graphics_Delete2 = (void (*)(Sexy::Graphics *)) Sexy_Graphics_Delete2Addr;
    Sexy_Graphics_Translate=(void (*)(Sexy::Graphics *,int,int))Sexy_Graphics_TranslateAddr;
    Sexy_Graphics_ClearRect=(void (*)(Sexy::Graphics *,int ,int,int,int))Sexy_Graphics_ClearRectAddr;
    Sexy_Graphics_SetColor = (void (*)(Sexy::Graphics *, Color *)) Sexy_Graphics_SetColorAddr;
    Sexy_Graphics_DrawTrianglesTex=(void (*)(Sexy::Graphics *,Sexy::Image* ,SexyVertex2D (*)[3],int ))Sexy_Graphics_DrawTrianglesTexAddr;
    Sexy_Graphics_GetColor = (int *(*)(Sexy::Graphics *)) Sexy_Graphics_GetColorAddr;
    Sexy_Graphics_SetScale = (void (*)(Sexy::Graphics *, float, float, float, float)) Sexy_Graphics_SetScaleAddr;
    Sexy_Graphics_DrawImage = (void (*)(Sexy::Graphics *, Sexy::Image *, int, int)) Sexy_Graphics_DrawImageAddr;
    Sexy_Graphics_DrawImageF=(void (*)(Sexy::Graphics* , Sexy::Image *, float , float ))Sexy_Graphics_DrawImageFAddr;
    Sexy_Graphics_DrawImageMirror = (void (*)(Sexy::Graphics *, Sexy::Image *, int, int, bool)) Sexy_Graphics_DrawImageMirrorAddr;
    Sexy_Graphics_DrawImage2 = (void (*)(Sexy::Graphics *, Sexy::Image *, int, int, int *)) Sexy_Graphics_DrawImage2Addr;
    Sexy_Graphics_DrawImageCel2 = (void (*)(Sexy::Graphics *, Sexy::Image *, int, int, int)) Sexy_Graphics_DrawImageCel2Addr;
    Sexy_Graphics_DrawImageMatrix=(void (*)(Sexy::Graphics *,Sexy::Image *,Sexy::SexyMatrix3*,TRect*,float,float,bool))Sexy_Graphics_DrawImageMatrixAddr;
    Sexy_GLGraphics_SetWrapMode=(void (*)(Sexy::Graphics *, int ,int ))Sexy_GLGraphics_SetWrapModeAddr;
    TodDrawImageCelF=(void (*)(Sexy::Graphics*,Sexy::Image*,float,float,int,int))TodDrawImageCelFAddr;


    Plant_GetImage = (Sexy::Image *(*)(SeedType::SeedType)) Plant_GetImageAddr;
    Plant_GetPlantRect = (void (*)(TRect *,  Plant*)) Plant_GetPlantRectAddr;
    Plant_NotOnGround = (bool (*)( Plant*)) Plant_NotOnGroundAddr;
    Plant_IsOnBoard = (bool (*)(Plant *)) Plant_IsOnBoardAddr;
    Plant_UpdateAbilities = (void (*)(Plant *)) Plant_UpdateAbilitiesAddr;
    Plant_Animate = (void (*)(Plant *)) Plant_AnimateAddr;
    Plant_UpdateReanim = (void (*)(Plant *)) Plant_UpdateReanimAddr;
//    Plant_DrawSeedType = (void (*)(int *, SeedType::SeedType, SeedType::SeedType, DrawVariation::DrawVariation, float,float)) Plant_DrawSeedTypeAddr;
    Plant_IsFlying = (bool (*)(SeedType::SeedType)) Plant_IsFlyingAddr;
    Plant_IsNocturnal = (bool (*)(SeedType::SeedType)) Plant_IsNocturnalAddr;
    Plant_DrawShadow=(void (*)(Plant*,Sexy::Graphics*,float,float))Plant_DrawShadowAddr;
    Plant_IsPartOfUpgradableTo=(bool (*)(Plant*,SeedType::SeedType))Plant_IsPartOfUpgradableToAddr;
    Plant_GetDamageRangeFlags= (int (*)(Plant*,PlantWeapon::PlantWeapon))Plant_GetDamageRangeFlagsAddr;
    Plant_IsInPlay=(bool (*)(Plant*))Plant_IsInPlayAddr;
    Plant_DrawMagnetItemsOnTop=(bool (*)(Plant*))Plant_DrawMagnetItemsOnTopAddr;
    Plant_DrawMagnetItems=(void (*)(Plant*,Sexy::Graphics*))Plant_DrawMagnetItemsAddr;
    GetPlantDefinition = (PlantDefinition &(*)(SeedType::SeedType)) GetPlantDefinitionAddr;
//    Plant_GetCost = (int (*)(SeedType::SeedType, SeedType::SeedType)) Plant_GetCostAddr;
    Plant_Die = (void (*)(Plant *)) Plant_DieAddr;


    Zombie_GetZombieRect = (void (*)(TRect *, Zombie *)) Zombie_GetZombieRectAddr;
    Zombie_IsImmobilizied = (bool (*)(Zombie *)) Zombie_IsImmobiliziedAddr;
    Zombie_EffectedByDamage = (bool (*)( Zombie*, int)) Zombie_EffectedByDamageAddr;
    Zombie_RemoveColdEffects = (void (*)( Zombie*)) Zombie_RemoveColdEffectsAddr;
    Zombie_ApplyButter = (void (*)(Zombie *)) Zombie_ApplyButterAddr;
//    Zombie_DieNoLoot = (void (*)(Zombie*)) Zombie_DieNoLootAddr;
    Zombie_ApplyBurn = (void (*)(Zombie*)) Zombie_ApplyBurnAddr;
    Zombie_StartEating = (void (*)(Zombie *)) Zombie_StartEatingAddr;
    Zombie_TakeDamage = (void (*)(Zombie *, int, unsigned int)) Zombie_TakeDamageAddr;
    Zombie_IsWalkingBackwards = (bool (*)(Zombie *)) Zombie_IsWalkingBackwardsAddr;
    Zombie_AddAttachedParticle = (void (*)(Zombie *, int, int, int)) Zombie_AddAttachedParticleAddr;
    Zombie_CanBeFrozen = (bool (*)(Zombie *)) Zombie_CanBeFrozenAddr;
    Zombie_StopEating = (void (*)(Zombie *)) Zombie_StopEatingAddr;
    Zombie_DropArm = (void (*)(Zombie *, unsigned int)) Zombie_DropArmAddr;
    Zombie_PlayZombieReanim = (void (*)(Zombie *, char *, int, int, float)) Zombie_PlayZombieReanimAddr;
    Zombie_SetupReanimLayers=(void (*)(Reanimation*,ZombieType::ZombieType))Zombie_SetupReanimLayersAddr;
    Zombie_SetupShieldReanims=(void (*)(ZombieType::ZombieType,Reanimation*))Zombie_SetupShieldReanimsAddr;
    Zombie_UpdateReanim=(void (*)(Zombie*))Zombie_UpdateReanimAddr;
    Zombie_UpdateActions=(void (*)(Zombie*))Zombie_UpdateActionsAddr;
    Zombie_UpdatePlaying=(void (*)(Zombie*))Zombie_UpdatePlayingAddr;
    Zombie_IsDeadOrDying=(bool (*)(Zombie*))Zombie_IsDeadOrDyingAddr;
    Zombie_IsOnBoard=(bool (*)(Zombie*))Zombie_IsOnBoardAddr;
    Zombie_ReanimShowPrefix=(void (*)(Zombie*,const char*,int))Zombie_ReanimShowPrefixAddr;
    Zombie_ReanimShowTrack=(void (*)(Zombie*,const char*,int))Zombie_ReanimShowTrackAddr;
    Zombie_TakeHelmDamage=(void (*)(Zombie*,int,unsigned int))Zombie_TakeHelmDamageAddr;
    Zombie_IsFlying=(bool (*)(Zombie*))Zombie_IsFlyingAddr;
    Zombie_TakeFlyingDamage=(void (*)(Zombie*,int,unsigned int))Zombie_TakeFlyingDamageAddr;
    Zombie_TakeShieldDamage=(void (*)(Zombie*,int,unsigned int))Zombie_TakeShieldDamageAddr;
    Zombie_TakeBodyDamage=(void (*)(Zombie*,int,unsigned int))Zombie_TakeBodyDamageAddr;
    Zombie_UpdateDamageStates=(void (*)(Zombie*,unsigned int))Zombie_UpdateDamageStatesAddr;
    Zombie_GetShieldDamageIndex=(int (*)(Zombie*))Zombie_GetShieldDamageIndexAddr;
    Zombie_GetHelmDamageIndex=(int (*)(Zombie*))Zombie_GetHelmDamageIndexAddr;
    Zombie_GetBodyDamageIndex=(int (*)(Zombie*))Zombie_GetBodyDamageIndexAddr;
    Zombie_GetTrackPosition=(void (*)(Zombie*,const char*,float*,float*))Zombie_GetTrackPositionAddr;
    Zombie_UpdateAnimationSpeed=(void (*)(Zombie*))Zombie_UpdateAnimationSpeedAddr;
    Zombie_HitIceTrap=(void (*)(Zombie*))Zombie_HitIceTrapAddr;
    Zombie_Zombie=(void (*)(Zombie*))Zombie_ZombieAddr;
//    GetZombieDefinition=(ZombieDefinition & (*)(ZombieType::ZombieType type))GetZombieDefinitionAddr;


    Reanimation_OverrideScale = (void (*)(Reanimation*, float, float)) Reanimation_OverrideScaleAddr;
    Reanimation_SetPosition = (void (*)(Reanimation*, float, float)) Reanimation_SetPositionAddr;
    Reanimation_Reanimation = (void (*)(Reanimation *)) Reanimation_ReanimationAddr;
    Reanimation_ReanimationInitializeType = (void (*)(Reanimation *, float, float, ReanimationType::ReanimationType)) Reanimation_ReanimationInitializeTypeAddr;
    Reanimation_Draw = (bool *(*)(Reanimation *, Sexy::Graphics *)) Reanimation_DrawAddr;
    Reanimation_Delete2 = (void (*)(Reanimation *)) Reanimation_Delete2Addr;
    Reanimation_PlayReanim = (void (*)(Reanimation *, char *, ReanimLoopType::ReanimLoopType, int, float)) Reanimation_PlayReanimAddr;
    Reanimation_FindTrackIndexById = (int (*)(Reanimation *, char *)) Reanimation_FindTrackIndexByIdAddr;
    Reanimation_GetCurrentTransform = (void (*)(Reanimation *, int, ReanimatorTransform *)) Reanimation_GetCurrentTransformAddr;
    Reanimation_SetAnimRate = (void (*)(Reanimation*, float)) Reanimation_SetAnimRateAddr;
    Reanimation_DrawRenderGroup = (void (*)(Reanimation*, Sexy::Graphics *, int)) Reanimation_DrawRenderGroupAddr;
    Reanimation_SetImageOverride = (void (*)(Reanimation *, char *, Sexy::Image *)) Reanimation_SetImageOverrideAddr;
    Reanimation_FindTrackIndex = (int (*)(Reanimation *, const char *)) Reanimation_FindTrackIndexAddr;
    Reanimation_ReanimationDie=(void (*)(Reanimation* ))Reanimation_ReanimationDieAddr;
    Reanimation_GetTrackInstanceByName=(ReanimatorTrackInstance* (*)(Reanimation *,const char*))Reanimation_GetTrackInstanceByNameAddr;
    Reanimation_SetFramesForLayer=(void (*)(Reanimation*,const char*))Reanimation_SetFramesForLayerAddr;
    Reanimation_TrackExists=(bool (*)(Reanimation*,const char*))Reanimation_TrackExistsAddr;
    Reanimation_AttachToAnotherReanimation=(void (*)(Reanimation*,Reanimation* ,const char* ))Reanimation_AttachToAnotherReanimationAddr;
    Reanimation_Update=(void (*)(Reanimation*))Reanimation_UpdateAddr;
    Reanimation_AssignRenderGroupToTrack=(void  (*)(Reanimation*, const char *, int ))Reanimation_AssignRenderGroupToTrackAddr;
    Reanimation_MatrixFromTransform=(void (*)(ReanimatorTransform*,Sexy::SexyMatrix3*))Reanimation_MatrixFromTransformAddr;
    Reanimation_GetFrameTime=(void (*)(Reanimation*,ReanimatorFrameTime *))Reanimation_GetFrameTimeAddr ;
    Reanimation_ShowOnlyTrack = (void (*)(Reanimation *, const char *)) Reanimation_ShowOnlyTrackAddr;
    ReanimatorCache_DrawCachedZombie = (int (*)(ReanimatorCache*, Sexy::Graphics *, float, float, int)) ReanimatorCache_DrawCachedZombieAddr;
    ReanimatorTransform_ReanimatorTransform = (void (*)( ReanimatorTransform *)) ReanimatorTransform_ReanimatorTransformAddr;
    AttachReanim=(AttachEffect* (*)(unsigned short *,Reanimation*,float,float))AttachReanimAddr;
    TodScaleRotateTransformMatrix=(void (*)(Sexy::SexyMatrix3*,float,float,float,float,float))TodScaleRotateTransformMatrixAddr;
    Reanimation_GetTrackMatrix=(void (*)(Reanimation *, int , SexyTransform2D *))Reanimation_GetTrackMatrixAddr;


    StoreScreen_SetSelectedSlot = (int (*)(int, int)) StoreScreen_SetSelectedSlotAddr;
    StoreScreen_AdvanceCrazyDaveDialog = (void (*)(int *)) StoreScreen_AdvanceCrazyDaveDialogAddr;
    StoreScreen_CanInteractWithButtons = (bool (*)(int *)) StoreScreen_CanInteractWithButtonsAddr;
    StoreScreen_GetStoreItemType = (StoreItem::StoreItem (*)(int *, int)) StoreScreen_GetStoreItemTypeAddr;
    StoreScreen_GetStoreItemInfo = (void (*)(int *, int, StoreItem::StoreItem, Sexy::Image **, int *, int *, int *)) StoreScreen_GetStoreItemInfoAddr;
    StoreScreen_IsItemSoldOut = (bool (*)(int *, StoreItem::StoreItem)) StoreScreen_IsItemSoldOutAddr;
    StoreScreen_IsItemUnavailable = (bool (*)(int *, StoreItem::StoreItem)) StoreScreen_IsItemUnavailableAddr;
    StoreScreen_IsComingSoon = (bool (*)(int *, StoreItem::StoreItem)) StoreScreen_IsComingSoonAddr;
    StoreScreen_IsPottedPlant=(bool (*)(int*,StoreItem::StoreItem))StoreScreen_IsPottedPlantAddr;
//    StoreScreen_PurchaseItem = (void (*)(int *, StoreItem::StoreItem)) StoreScreen_PurchaseItemAddr;
    StoreScreen_IsPageShown = (bool (*)(int *, int)) StoreScreen_IsPageShownAddr;
    StoreScreen_EnableButtons = (void (*)(int *, bool)) StoreScreen_EnableButtonsAddr;


    CutScene_IsSurvivalRepick = (bool (*)(CutScene *)) CutScene_IsSurvivalRepickAddr;
    CutScene_ShouldRunUpsellBoard = (bool (*)(CutScene *)) CutScene_ShouldRunUpsellBoardAddr;
    CutScene_OnKeyDown = (bool (*)(CutScene *, int, int)) CutScene_OnKeyDownAddr;
    CutScene_MouseDown = (void (*)(CutScene *, int, int)) CutScene_MouseDownAddr;
    CutScene_IsBeforePreloading = (bool (*)(CutScene *)) CutScene_IsBeforePreloadingAddr;


    ChallengeScreen_SetScrollTarget = (void (*)(ChallengeScreen *, int)) ChallengeScreen_SetScrollTargetAddr;
    ChallengeScreen_KeyDown = (void (*)(ChallengeScreen *, int)) ChallengeScreen_KeyDownAddr;
//    ChallengeScreen_UpdateButtons=(void (*)(ChallengeScreen *))ChallengeScreen_UpdateButtonsAddr;


    GamepadControls_OnButtonUp = (void (*)(GamepadControls*, int, int, unsigned int)) GamepadControls_OnButtonUpAddr;
    GamepadControls_OnButtonDown = (void (*)(GamepadControls*, int, int, unsigned int)) GamepadControls_OnButtonDownAddr;
    GamepadControls_OnKeyDown = (void (*)(GamepadControls*, int, unsigned int)) GamepadControls_OnKeyDownAddr;
    GamepadControls_GetSeedBank = (SeedBank *(*)(GamepadControls*)) GamepadControls_GetSeedBankAddr;


    TodDrawImageCelCenterScaledF = (int (*)(Sexy::Graphics *, Sexy::Image *, float, float, int, float, float)) TodDrawImageCelCenterScaledFAddr;
    TodDrawImageScaledF = (void (*)(Sexy::Graphics *, Sexy::Image *, float, float, float, float)) TodDrawImageScaledFAddr;
    TodDrawImageCelScaledF = (void (*)(Sexy::Graphics *, Sexy::Image *, float, float, int, int, float, float)) TodDrawImageCelScaledFAddr;
    TodDrawImageCenterScaledF = (void (*)(Sexy::Graphics *, Sexy::Image *, float, float, float, float)) TodDrawImageCenterScaledFAddr;
    TodScaleTransformMatrix = (void (*)(int *, float, float, float, float)) TodScaleTransformMatrixAddr;
    TodDrawStringWrapped=(void (*)(Sexy::Graphics *, int* text, TRect *, Sexy::Font *, Color *, DrawStringJustification::DrawStringJustification , bool ))TodDrawStringWrappedAddr;
    TodDrawStringMatrix = (void (*)(Sexy::Graphics *, Sexy::Font *, int *, int *, Color *)) TodDrawStringMatrixAddr;
    TodDrawString = (void (*)(Sexy::Graphics *, int *, int, int, Sexy::Font *,Color, DrawStringJustification::DrawStringJustification)) TodDrawStringAddr;
    TodAnimateCurve = (int (*)(int, int, int, int, int, TodCurves::TodCurves)) TodAnimateCurveAddr;
    TodAnimateCurveFloat=(float (*)(int , int , int , float , float ,TodCurves::TodCurves ))TodAnimateCurveFloatAddr;
    TodAnimateCurveFloatTime=(float (*)(float , float , float , float , float , TodCurves::TodCurves ))TodAnimateCurveFloatTimeAddr;


    MainMenu_InTransition = (bool (*)(MainMenu *)) MainMenu_InTransitionAddr;
    MainMenu_SetScene = (void (*)(MainMenu *, int)) MainMenu_SetSceneAddr;
    MainMenu_StartAdventureMode = (void (*)(MainMenu *)) MainMenu_StartAdventureModeAddr;


    CursorObject_Draw = (int (*)(CursorObject *, Sexy::Graphics *)) CursorObject_DrawAddr;
    CursorObject_Update = (void (*)(int *)) CursorObject_UpdateAddr;


    ZenGarden_GetStinky = (int *(*)(int **)) ZenGarden_GetStinkyAddr;
    ZenGarden_IsStinkyHighOnChocolate = (bool (*)(int *)) ZenGarden_IsStinkyHighOnChocolateAddr;
    ZenGarden_OpenStore = (void (*)(int *)) ZenGarden_OpenStoreAddr;
    ZenGarden_GetPottedPlantInWheelbarrow = (int (*)(int *)) ZenGarden_GetPottedPlantInWheelbarrowAddr;
    ZenGarden_DrawPottedPlant = (void (*)(int *, Sexy::Graphics *, float, float, PottedPlant *, float, bool)) ZenGarden_DrawPottedPlantAddr;
    PlantFlowerPotHeightOffset=(float (*)(SeedType::SeedType,float))PlantFlowerPotHeightOffsetAddr;

    Challenge_IZombieGetBrainTarget = (GridItem *(*)(Challenge *, Zombie *)) Challenge_IZombieGetBrainTargetAddr;
    Challenge_GetArtChallengeSeed = (SeedType::SeedType (*)(Challenge *, int, int)) Challenge_GetArtChallengeSeedAddr;
    Challenge_TreeOfWisdomOpenStore = (void (*)(Challenge *)) Challenge_TreeOfWisdomOpenStoreAddr;
    Challenge_IZombieScoreBrain = (void (*)(Challenge *, GridItem *)) Challenge_IZombieScoreBrainAddr;
    Challenge_MouseDown = (bool (*)(Challenge *, int, int, int, HitResult *, int)) Challenge_MouseDownAddr;
    Challenge_IsZombieSeedType = (bool (*)(SeedType::SeedType)) Challenge_IsZombieSeedTypeAddr;
    Challenge_IsMPSeedType = (bool (*)(SeedType::SeedType)) Challenge_IsMPSeedTypeAddr;
    Challenge_IsMPSuddenDeath = (bool (*)(Challenge *)) Challenge_IsMPSuddenDeathAddr;
    Challenge_InitZombieWavesFromList=(void (*)(Challenge*,ZombieType::ZombieType*,int))Challenge_InitZombieWavesFromListAddr;
    //Challenge_IZombieSeedTypeToZombieType = (ZombieType::ZombieType (*)(SeedType::SeedType)) Challenge_IZombieSeedTypeToZombieTypeAddr;
    Challenge_ScaryPotterCountSunInPot = (int (*)(Challenge *, GridItem *)) Challenge_ScaryPotterCountSunInPotAddr;
    Challenge_IZombieSetupPlant = (void (*)(Challenge *, Plant *)) Challenge_IZombieSetupPlantAddr;
    Challenge_IZombiePlaceZombie = (void (*)(Challenge*,ZombieType::ZombieType,int,int)) Challenge_IZombiePlaceZombieAddr;
    Challenge_GraveDangerSpawnGraveAt = (void (*)(Challenge*,int,int)) Challenge_GraveDangerSpawnGraveAtAddr;
    Challenge_IZombieSetPlantFilterEffect=(void (*)(Challenge*,Plant*,FilterEffectType::FilterEffectType))Challenge_IZombieSetPlantFilterEffectAddr;


    Projectile_GetProjectileRect = (void (*)(TRect *, Projectile *)) Projectile_GetProjectileRectAddr;
    Projectile_Die = (void (*)(Projectile *)) Projectile_DieAddr;
    Projectile_FindCollisionTargetPlant = (Plant *(*)(Projectile *)) Projectile_FindCollisionTargetPlantAddr;
    Projectile_GetProjectileDef = (ProjectileDefinition &(*)(Projectile *)) Projectile_GetProjectileDefAddr;
    Projectile_CantHitHighGround = (bool (*)(Projectile *)) Projectile_CantHitHighGroundAddr;
    Projectile_FindCollisionTarget = (Zombie *(*)(Projectile *)) Projectile_FindCollisionTargetAddr;
    Projectile_FindCollisionTargetGridItem = (GridItem *(*)(Projectile *)) Projectile_FindCollisionTargetGridItemAddr;
    Projectile_DoImpactGridItem = (void (*)(Projectile *, GridItem *)) Projectile_DoImpactGridItemAddr;
    Projectile_PlayImpactSound = (void (*)(Projectile *, Zombie *)) Projectile_PlayImpactSoundAddr;
    Projectile_IsSplashDamage = (bool (*)(Projectile *, Zombie *)) Projectile_IsSplashDamageAddr;
    Projectile_DoSplashDamage = (void (*)(Projectile *, Zombie *, int)) Projectile_DoSplashDamageAddr;
    Projectile_GetDamageFlags = (unsigned int (*)(Projectile *, Zombie *)) Projectile_GetDamageFlagsAddr;
    Projectile_PeaAboutToHitTorchwood=(bool (*)(Projectile*))Projectile_PeaAboutToHitTorchwoodAddr;


    GameButton_IsMouseOver = (bool (*)(Sexy::GameButton *)) GameButton_IsMouseOverAddr;
    GameButton_OnPressed=(void (*)(Sexy::GameButton* ))GameButton_OnPressedAddr;
    GameButton_Delete=(void  (*)(Sexy::GameButton *))GameButton_DeleteAddr;
    GameButton_Resize = (void (*)(Sexy::GameButton *, int, int, int, int)) GameButton_ResizeAddr;
    GameButton_GameButton = (void (*)(Sexy::GameButton *, int, int *)) GameButton_GameButtonAddr;
    GameButton_SetLabel=(void (*)(Sexy::GameButton *,int*))GameButton_SetLabelAddr;
    GameButton_SetDisabled=(void (*)(Sexy::GameButton *, bool))GameButton_SetDisabledAddr;
    GameButton_Update = (void (*)(Sexy::GameButton *)) GameButton_UpdateAddr;
    GameButton_Draw = (void (*)(Sexy::GameButton *, Sexy::Graphics *)) GameButton_DrawAddr;
    MakeButton=(Sexy::GameButton* (*)(int , Sexy::ButtonListener *, Sexy::Widget *, int *))MakeButtonAddr;
    MakeNewCheckbox= (Sexy::Checkbox* (*)(int , int **, Sexy::Widget *, bool ))MakeNewCheckboxAddr;
    Sexy_ButtonWidget_ButtonWidget=(void (*)(Sexy::ButtonWidget *, int ,Sexy::ButtonListener *))Sexy_ButtonWidget_ButtonWidgetAddr;


    AlmanacDialog_SeedHitTest = (SeedType::SeedType (*)(AlmanacDialog *, int, int)) AlmanacDialog_SeedHitTestAddr;
    AlmanacDialog_ZombieHitTest = (ZombieType::ZombieType (*)(AlmanacDialog *, int, int)) AlmanacDialog_ZombieHitTestAddr;
    AlmanacDialog_SetupPlant = (void (*)(AlmanacDialog *)) AlmanacDialog_SetupPlantAddr;
    AlmanacDialog_SetupZombie = (void (*)(AlmanacDialog *)) AlmanacDialog_SetupZombieAddr;
    AlmanacDialog_KeyDown=(bool (*)(AlmanacDialog* , int))AlmanacDialog_KeyDownAddr;


    SeedChooserScreen_CancelLawnView = (bool (*)(SeedChooserScreen *)) SeedChooserScreen_CancelLawnViewAddr;
    SeedChooserScreen_GetNextSeedInDir = (void (*)(SeedChooserScreen *, int, int)) SeedChooserScreen_GetNextSeedInDirAddr;
    SeedChooserScreen_GetSeedPositionInChooser = (void (*)(SeedChooserScreen *, SeedType::SeedType, int *, int *)) SeedChooserScreen_GetSeedPositionInChooserAddr;
//    SeedChooserScreen_GetSeedPositionInBank=(void (*)(SeedChooserScreen*,int,int*,int*,int))SeedChooserScreen_GetSeedPositionInBankAddr;
    SeedChooserScreen_UpdateImitaterButton = (void (*)(SeedChooserScreen *)) SeedChooserScreen_UpdateImitaterButtonAddr;
    SeedChooserScreen_SeedHitTest = (SeedType::SeedType (*)(SeedChooserScreen *, int, int)) SeedChooserScreen_SeedHitTestAddr;
//    SeedChooserScreen_ButtonDePress = (void (*)(SeedChooserScreen *, int)) SeedChooserScreen_ButtonDepressAddr;
    SeedChooserScreen_LandFlyingSeed = (void (*)(SeedChooserScreen *, int *)) SeedChooserScreen_LandFlyingSeedAddr;
//    SeedChooserScreen_ClickedSeedInBank = (void (*)(int *, int *, unsigned int)) SeedChooserScreen_ClickedSeedInBankAddr;
//    SeedChooserScreen_GameButtonDown = (int (*)(int *, int, unsigned int)) SeedChooserScreen_GameButtonDownAddr;
    SeedChooserScreen_CloseSeedChooser = (void (*)(SeedChooserScreen *)) SeedChooserScreen_CloseSeedChooserAddr;
//    SeedChooserScreen_OnKeyDown = (void (*)(int *, int, unsigned int)) SeedChooserScreen_OnKeyDownAddr;
    SeedChooserScreen_HasPacket = (bool (*)(SeedChooserScreen *, int, bool)) SeedChooserScreen_HasPacketAddr;
    SeedChooserScreen_Has7Rows = (bool (*)(SeedChooserScreen *)) SeedChooserScreen_Has7RowsAddr;


    Sexy_SexyTransform2D_SexyTransform2D = (void (*)(SexyTransform2D *)) Sexy_SexyTransform2D_SexyTransform2DAddr;
    Sexy_SexyTransform2D_Scale = (void (*)(SexyTransform2D *, float, float)) Sexy_SexyTransform2D_ScaleAddr;
    Sexy_SexyTransform2D_Translate = (void (*)(SexyTransform2D *, float,float)) Sexy_SexyTransform2D_TranslateAddr;


    SeedPacket_DrawBackground = (void (*)(SeedPacket *, Sexy::Graphics *)) SeedPacket_DrawBackgroundAddr;
    //SeedPacket_MouseDown = (void (*)(int *, int, int, int)) SeedPacket_MouseDownAddr;
    SeedPacket_CanPickUp = (bool (*)(SeedPacket *)) SeedPacket_CanPickUpAddr;
    SeedPacket_MouseHitTest = (bool (*)(SeedPacket *, int, int, HitResult *)) SeedPacket_MouseHitTestAddr;
    SeedPacket_GetPlayerIndex = (bool (*)(SeedPacket *)) SeedPacket_GetPlayerIndexAddr;
    SeedPacket_DrawMiddle=(void (*)(SeedPacket *, Sexy::Graphics *))SeedPacket_DrawMiddleAddr;


    GameObject_BeginDraw = (bool (*)(int *, float *)) GameObject_BeginDrawAddr;
    GameObject_EndDraw = (void (*)(int *, float *)) GameObject_EndDrawAddr;


    Coin_MouseDown = (void (*)(Coin *, int, int, int)) Coin_MouseDownAddr;
    Coin_Collect = (void (*)(Coin*, int)) Coin_CollectAddr;
    Coin_Die = (void (*)(Coin*)) Coin_DieAddr;
    Coin_IsLevelAward=(bool (*)(Coin*))Coin_IsLevelAwardAddr;
    Coin_IsPresentWithAdvice=(bool (*)(Coin*))Coin_IsPresentWithAdviceAddr;
    Coin_IsMoney=(bool (*)(Coin*))Coin_IsMoneyAddr;
    Coin_PlayGroundSound=(void (*)(Coin*))Coin_PlayGroundSoundAddr;
    Coin_GetDisappearTime=(int (*)(Coin*))Coin_GetDisappearTimeAddr;
    Coin_StartFade=(void (*)(Coin*))Coin_StartFadeAddr;
    Coin_GetSunScale=(float (*)(Coin*))Coin_GetSunScaleAddr;


    GetRectOverlap = (int (*)(TRect *, TRect *)) GetRectOverlapAddr;
    Sexy_StrFormat = (void (*)(int *, const char *, ...)) Sexy_StrFormatAddr;
    TodStringTranslate=(void (*)(int *, const char *))TodStringTranslateAddr;
//    DrawSeedPacket = (void (*)(Sexy::Graphics *, int, int, int, int, float, int, bool, bool, bool,bool)) DrawSeedPacketAddr;
    VSSetupMenu_GameButtonDown = (void (*)(int *, int, unsigned int,int)) VSSetupMenu_GameButtonDownAddr;
    WaitForSecondPlayerDialog_GameButtonDown = (int (*)(int *, int,int)) WaitForSecondPlayerDialog_GameButtonDownAddr;
    HelpTextScreen_KeyDown=(void (*)(Sexy::Widget*,int))HelpTextScreen_KeyDownAddr;
    Attachment_AttachmentDie = (int (*)(int*)) AttachmentDieAddr;
    AwardScreen_StartButtonPressed=(void  (*)(int *))AwardScreen_StartButtonPressedAddr;
    CursorPreview_Update = (void (*)(int *)) CursorPreview_UpdateAddr;
    ShopSeedPacket_Update = (void (*)(int *)) ShopSeedPacket_UpdateAddr;
    GetFlashingColor = (void (*)(Color *, int, int)) GetFlashingColorAddr;
    LawnPlayerInfo_GetFlag = (int (*)(PlayerInfo *, int)) LawnPlayerInfo_GetFlagAddr;
    RandRangeInt = (int (*)(int, int)) RandRangeIntAddr;
//    DrawSeedType = (void (*)(float *, float, float, int, int, float, float,float)) DrawSeedTypeAddr;
    MailScreen_KeyDown=(void (*)(MailScreen *, int , int , int ))MailScreen_KeyDownAddr;
    Sexy_GamepadApp_HasGamepad = (bool (*)(LawnApp *)) Sexy_GamepadApp_HasGamepadAddr;
    Sexy_RandInt=(int (*)(int ))Sexy_RandIntAddr;
    Sexy_SexyMatrix3_SexyMatrix3 = (void (*)(int *)) Sexy_SexyMatrix3_SexyMatrix3Addr;
    GridItem_GridItemDie = (void (*)( GridItem*)) GridItem_GridItemDieAddr;
    Sexy_SexyAppBase_GetImage = (Sexy::Image *(*)(LawnApp *, int *, int)) Sexy_SexyAppBase_GetImageAddr;
    Sexy_Widget_Resize = (void (*)(Sexy::Widget *, int, int, int, int)) Sexy_Widget_ResizeAddr;
    Sexy_Widget_Widget=(void (*)(Sexy::Widget *))Sexy_Widget_WidgetAddr;
    Sexy_Widget_SetVisible=(void (*)(Sexy::Widget *, bool ))Sexy_Widget_SetVisibleAddr;
    Sexy_WidgetManager_SetFocus=(void (*)(int *,Sexy::Widget*))Sexy_WidgetManager_SetFocusAddr;
    Sexy_WidgetContainer_SetFocus=(void (*)(Sexy::WidgetContainer*,Sexy::Widget*))Sexy_WidgetContainer_SetFocusAddr;
    Sexy_WidgetManager_GetWidgetAt = (int *(*)(int *, int, int, int *, int *)) Sexy_WidgetManager_GetWidgetAtAddr;
    Sexy_Image_GetWidth = (int (*)(Sexy::Image *)) Sexy_Image_GetWidthAddr;
    Sexy_Image_GetHeight = (int (*)(Sexy::Image *)) Sexy_Image_GetHeightAddr;
    Sexy_Image_GetCelHeight=(int (*)(Sexy::Image *))Sexy_Image_GetCelHeightAddr;
    Sexy_Image_SetWrapMode=(void (*)(Sexy::Image*,int,int))Sexy_Image_SetWrapModeAddr;
    Sexy_WidgetContainer_MarkDirty=(void (*)(Sexy::WidgetContainer*))Sexy_WidgetContainer_MarkDirtyAddr;
    ImitaterDialog_SeedHitTest = (SeedType::SeedType (*)(LawnDialog *, int, int)) ImitaterDialog_SeedHitTestAddr;
    SaveGameContext_SyncInt=(void (*)(int*,int*))SaveGameContext_SyncIntAddr;
    PlantDrawHeightOffset = (float (*)(Board *, int, SeedType::SeedType, int, int)) PlantDrawHeightOffsetAddr;
//    GetChallengeDefinition = (ChallengeDefinition& (*)(int)) GetChallengeDefinitionAddr;
    TypingCheck_SetPhrase = (void (*)(int *, int *)) TypingCheck_SetPhraseAddr;
    Sexy_SexyAppBase_RegistryReadString = (int (*)(int *, int *, int *)) Sexy_SexyAppBase_RegistryReadStringAddr;
    Sexy_SexyAppBase_CopyImage = (Sexy::Image *(*)(LawnApp *, Sexy::Image *)) Sexy_SexyAppBase_CopyImageAddr;
    Sexy_SexyAppBase_CopyImage2=(Sexy::Image *(*)(LawnApp *, Sexy::Image *,TRect*))Sexy_SexyAppBase_CopyImage2Addr;
    Sexy_MemoryImage_MemoryImage = (void (*)(Sexy::Image *)) Sexy_MemoryImage_MemoryImageAddr;
    Sexy_MemoryImage_GetBits=(unsigned int* (*)(Sexy::Image *))Sexy_MemoryImage_GetBitsAddr;
    Sexy_MemoryImage_Create=(void (*)(Sexy::Image *, int , int ))Sexy_MemoryImage_CreateAddr;
    Sexy_MemoryImage_SetImageMode=(void (*)(Sexy::Image *, bool , bool ))Sexy_MemoryImage_SetImageModeAddr;
    Sexy_MemoryImage_Delete=(void (*)(Sexy::Image *))Sexy_MemoryImage_DeleteAddr;
    Sexy_MemoryImage_WriteToPng=(void (*)(Sexy::Image *,int*))Sexy_MemoryImage_WriteToPngAddr;
    Sexy_MemoryImage_WriteToJPEG=(void (*)(Sexy::Image *,int*))Sexy_MemoryImage_WriteToJPEGAddr;
    Sexy_MemoryImage_BitsChanged=(void (*)(Sexy::Image *))Sexy_MemoryImage_BitsChangedAddr;
    FilterEffectDoWashedOut = (void (*)(Sexy::Image *)) FilterEffectDoWashedOutAddr;
    FilterEffectDoLessWashedOut = (void (*)(Sexy::Image *)) FilterEffectDoLessWashedOutAddr;
    FilterEffectDoWhite = (void (*)(Sexy::Image *)) FilterEffectDoWhiteAddr;
    HouseChooserDialog_GameButtonDown = (void (*)(HouseChooserDialog *, int, int, bool)) HouseChooserDialog_GameButtonDownAddr;
    ReanimAtlas_GetEncodedReanimAtlas = (int **(*)(int *, int *)) ReanimAtlas_GetEncodedReanimAtlasAddr;
    ReanimatorEnsureDefinitionLoaded=(void (*)(ReanimationType::ReanimationType , bool ))ReanimatorEnsureDefinitionLoadedAddr;
    ReanimatorCache_GetPlantImageSize = (void (*)(ReanimatorCache*, int, int *, int *, int *, int *)) ReanimatorCache_GetPlantImageSizeAddr;
    ReanimatorCache_MakeCachedPlantFrame=(Sexy::Image* (*)(ReanimatorCache*,SeedType::SeedType,DrawVariation::DrawVariation))ReanimatorCache_MakeCachedPlantFrameAddr;
    FindGlobalAllocator=(TodAllocator * (*)(int ))FindGlobalAllocatorAddr;
    AttachParticle=(void (*)(int*,TodParticleSystem *,float,float))AttachParticleAddr;
    TodLoadResources=(void (*)(int*))TodLoadResourcesAddr;
    TodParticleSystem_Draw=(void (*)(TodParticleSystem*,Sexy::Graphics*))TodParticleSystem_DrawAddr;
//    Sexy_SexyAppBase_Is3DAccelerated = (bool (*)(LawnApp *)) Sexy_SexyAppBase_Is3DAcceleratedAddr;
//    Sexy_SexyAppBase_Set3DAccelerated=(void (*)(LawnApp*,bool))Sexy_SexyAppBase_Set3DAcceleratedAddr;
    Sexy_ResourceManager_GetSoundThrow=(int* (*)(int*,int*))Sexy_ResourceManager_GetSoundThrowAddr;
    ToolTipWidget_SetWarningText=(void (*)(int* , int*))ToolTipWidget_SetWarningTextAddr;
    TestMenuWidget_TestMenuWidget=(void (*)(ZombatarWidget* ))TestMenuWidget_TestMenuWidgetAddr;
    RandRangeFloat=(float (*)(float,float))RandRangeFloatAddr;
    PoolEffect_BilinearLookupFixedPoint= (unsigned int (*)(PoolEffect*,unsigned int,unsigned int))PoolEffect_BilinearLookupFixedPointAddr;
    Sexy_DefaultProfileMgr_GetAnyProfile=(PlayerInfo* (*)(int* ))Sexy_DefaultProfileMgr_GetAnyProfileAddr;
    //Sexy_WidgetManager_MouseDown=(int (*)(int *manager, int x, int y, int theClickCount))Sexy_WidgetManager_MouseDownAddr;
    SeedBank_GetNumSeedsOnConveyorBelt=(int (*)(SeedBank *))SeedBank_GetNumSeedsOnConveyorBeltAddr;
    //SeedBank_ContainsPoint=(bool (*)(SeedBank *, int x, int y))SeedBank_ContainsPointAddr;
    Music2_Delete=(void (*)(Music2* ))Music2_DeleteAddr;
    Music_Music=(void (*)(Music*))Music_MusicAddr;
//    Music2_Music2=(void (*)(Music2*))Music2_Music2Addr;
    Music_StopAllMusic=(void (*)(Music*))Music_StopAllMusicAddr;
//    Music_MusicResync=(void (*)(Music*))Music_MusicResyncAddr;
    Music_GetMusicOrder=(int (*)(Music*,MusicFile::MusicFile))Music_GetMusicOrderAddr;
    //Music_PlayFromOffset=(void (*)(Music*,MusicFile::MusicFile,int,double))Music_PlayFromOffsetAddr;
    Music_SetupMusicFileForTune=(void (*)(Music*,MusicFile::MusicFile,MusicTune::MusicTune))Music_SetupMusicFileForTuneAddr;
    Sexy_AudiereMusicInterface_SetVolume=(void (*)(int *, double ))Sexy_AudiereMusicInterface_SetVolumeAddr;
    Sexy_AudiereMusicInterface_SetSongVolume=(void (*)(int *, int , double ))Sexy_AudiereMusicInterface_SetSongVolumeAddr;
    Sexy_AudiereMusicInterface_PlayMusic=(void (*)(int* ,int,int,bool))Sexy_AudiereMusicInterface_PlayMusicAddr;
    Sexy_AudiereMusicInterface_StopMusic=(void (*)(int*,int))Sexy_AudiereMusicInterface_StopMusicAddr;
    Sexy_AudiereMusicInterface_SetChannelVolume=(void (*)(int*,int,int,float))Sexy_AudiereMusicInterface_SetChannelVolumeAddr;
    TodFoley_IsFoleyPlaying= (bool (*)(TodFoley* , FoleyType::FoleyType ))TodFoley_IsFoleyPlayingAddr;
    TodFoley_StopFoley=(void (*)(TodFoley*, FoleyType::FoleyType ))TodFoley_StopFoleyAddr;
    SoundSystemFindInstance=(FoleyInstance* (*)(TodFoley*,FoleyType::FoleyType))SoundSystemFindInstanceAddr;
    TodStringListLoad=(void (*)(const char*))TodStringListLoadAddr;
    TodReplaceString=(void (*)(int*,int*,const char*,int*))TodReplaceStringAddr;
    TodReplaceNumberString=(void (*)(int*,int*,const char*,int))TodReplaceNumberStringAddr;
    Sexy_AudiereSoundManager_LoadSound=(int (*)(int* , int* ))Sexy_AudiereSoundManager_LoadSoundAddr;
    MessageWidget_MessageWidget=(void (*)(MessageWidget *, LawnApp *))MessageWidget_MessageWidgetAddr;
    MessageWidget_Delete=(void (*)(MessageWidget *))MessageWidget_DeleteAddr;
    MessageWidget_GetFont=(Sexy::Font* (*)(MessageWidget *))MessageWidget_GetFontAddr;
    MaskHelpWidget_MaskHelpWidget=(void (*)(AchievementsWidget*,LawnApp*))MaskHelpWidget_MaskHelpWidgetAddr;
    MaskHelpWidget_Delete=(void (*)(AchievementsWidget*))MaskHelpWidget_DeleteAddr;
    DaveHelp_DaveHelp=(void (*)(LeaderboardsWidget *, LawnApp *))DaveHelp_DaveHelpAddr;
//    TrashBin_TrashBin=(void (*)(TrashBin *, int , float ))TrashBin_TrashBinAddr;
    TrashBin_Delete=(void (*)(TrashBin *))TrashBin_DeleteAddr;
    ConfirmBackToMainDialog_ConfirmBackToMainDialog=(void (*)(ConfirmBackToMainDialog*,bool))ConfirmBackToMainDialog_ConfirmBackToMainDialogAddr;
    Sexy_Widget_Move=(void (*)(Sexy::Widget *, int , int ))Sexy_Widget_MoveAddr;
    TodParticleSystem_OverrideColor=(void (*)(TodParticleSystem *, char *, Color *))TodParticleSystem_OverrideColorAddr;
    TodParticleSystem_OverrideImage=(void (*)(TodParticleSystem *,char *,Sexy::Image*))TodParticleSystem_OverrideImageAddr;
    DrawCheckboxText=(void (*)(Sexy::Graphics *, int* , Sexy::Checkbox* , const char *))DrawCheckboxTextAddr;
    Sexy_Checkbox_Delete=(void  (*)(Sexy::Checkbox* ))Sexy_Checkbox_DeleteAddr;
    CreditScreen_PauseCredits=(void (*)(Sexy::Widget*))CreditScreen_PauseCreditsAddr;
    Sexy_MenuWidget_Draw=(void (*)(Sexy::MenuWidget*,Sexy::Graphics*))Sexy_MenuWidget_DrawAddr;
    Sexy_Widget_DeferOverlay=(void (*)(Sexy::Widget*,int))Sexy_Widget_DeferOverlayAddr;
    Mailbox_GetNumUnseenMessages=(int (*)(int*))Mailbox_GetNumUnseenMessagesAddr;
    LawnMower_StartMower=(void (*)(int*))LawnMower_StartMowerAddr;
}


void InitHookFunction() {
    MSHookFunction(LawnApp_LawnAppAddr, (void *) LawnApp_LawnApp, (void **) &old_LawnApp_LawnApp);
    MSHookFunction(LawnApp_InitAddr, (void *) LawnApp_Init,(void **) &old_LawnApp_Init);
    MSHookFunction(LawnApp_IsNightAddr, (void *) LawnApp_IsNight,(void **) &old_LawnApp_IsNight);
    MSHookFunction(LawnApp_HardwareInitAddr, (void *) LawnApp_HardwareInit,(void **) &old_LawnApp_HardwareInit);
    MSHookFunction(LawnApp_DoBackToMainAddr, (void *) LawnApp_DoBackToMain,(void **) &old_LawnApp_DoBackToMain);
    MSHookFunction(LawnApp_CanShopLevelAddr, (void *) LawnApp_CanShopLevel,(void **) &old_LawnApp_CanShopLevel);
    MSHookFunction(LawnApp_DoNewOptionsAddr, (void *) LawnApp_DoNewOptions,(void **) &old_LawnApp_DoNewOptions);
    MSHookFunction(LawnApp_DoConfirmBackToMainAddr, (void *) LawnApp_DoConfirmBackToMain,NULL);
    MSHookFunction(LawnApp_TrophiesNeedForGoldSunflowerAddr, (void *) LawnApp_TrophiesNeedForGoldSunflower,NULL);
    MSHookFunction(LawnApp_GamepadToPlayerIndexAddr, (void *) LawnApp_GamepadToPlayerIndex,(void **) &old_LawnApp_GamepadToPlayerIndex);
    MSHookFunction(LawnApp_ShowCreditScreenAddr, (void *) LawnApp_ShowCreditScreen,(void **) &old_LawnApp_ShowCreditScreen);
    MSHookFunction(LawnApp_OnSessionTaskFailedAddr, (void *) LawnApp_OnSessionTaskFailed, NULL);
    MSHookFunction(LawnApp_UpdateAppAddr, (void *) LawnApp_UpDateApp,(void **) &old_LawnApp_UpDateApp);
    MSHookFunction(LawnApp_ShowAwardScreenAddr, (void *) LawnApp_ShowAwardScreen,(void **) &old_LawnApp_ShowAwardScreen);
    MSHookFunction(LawnApp_KillAwardScreenAddr, (void *) LawnApp_KillAwardScreen,(void **) &old_LawnApp_KillAwardScreen);
    MSHookFunction(LawnApp_LoadLevelConfigurationAddr, (void *) LawnApp_LoadLevelConfiguration,(void **) &old_LawnApp_LoadLevelConfiguration);
    MSHookFunction(LawnApp_LoadingThreadProcAddr, (void *) LawnApp_LoadingThreadProc,(void **) &old_LawnApp_LoadingThreadProc);
    MSHookFunction(LawnApp_IsChallengeWithoutSeedBankAddr, (void *) LawnApp_IsChallengeWithoutSeedBank,(void **) &old_LawnApp_IsChallengeWithoutSeedBank);
    MSHookFunction(LawnApp_TryHelpTextScreenAddr, (void *) LawnApp_TryHelpTextScreen, NULL);
    MSHookFunction(LawnApp_KillSeedChooserScreenAddr, (void *) LawnApp_KillSeedChooserScreen,(void **) &old_LawnApp_KillSeedChooserScreen);




    MSHookFunction(Board_UpdateAddr, (void *) Board_Update, (void **) &old_Board_Update);
    MSHookFunction(Board_BoardAddr, (void *) Board_Board, (void **) &old_Board_Board);
    MSHookFunction(Board_InitLevelAddr, (void *) Board_InitLevel, (void **) &old_Board_InitLevel);
    MSHookFunction(Board_RemovedFromManagerAddr, (void *) Board_RemovedFromManager, (void **) &old_Board_RemovedFromManager);
    MSHookFunction(Board_Delete2Addr, (void *) Board_Delete2, (void **) &old_Board_Delete2);
    MSHookFunction(Board_FadeOutLevelAddr, (void *) Board_FadeOutLevel, (void **) &old_Board_FadeOutLevel);
    MSHookFunction(Board_AddPlantAddr, (void *) Board_AddPlant, (void **) &old_Board_AddPlant);
    MSHookFunction(Board_AddSunMoneyAddr, (void *) Board_AddSunMoney, (void **) &old_Board_AddSunMoney);
    MSHookFunction(Board_AddDeathMoneyAddr, (void *) Board_AddDeathMoney, (void **) &old_Board_AddDeathMoney);
    MSHookFunction(Board_CanPlantAtAddr, (void *) Board_CanPlantAt, (void **) &old_Board_CanPlantAt);
    MSHookFunction(Board_PlantingRequirementsMetAddr, (void *) Board_PlantingRequirementsMet,(void **) &old_Board_PlantingRequirementsMet);
    MSHookFunction(Board_GetFlowerPotAtAddr, (void *) Board_GetFlowerPotAt, NULL);
    MSHookFunction(Board_GetPumpkinAtAddr, (void *) Board_GetPumpkinAt, NULL);
    MSHookFunction(Board_ZombiesWonAddr, (void *) Board_ZombiesWon, (void **) &old_BoardZombiesWon);
    MSHookFunction(Board_DrawZenButtonsAddr, (void *) Board_DrawZenButtons,(void **) &old_Board_DrawZenButtons);
    MSHookFunction(Board_KeyDownAddr, (void *) Board_KeyDown, (void **) &old_Board_KeyDown);
//    MSHookFunction(Board_KeyUpAddr, (void *) Board_KeyUp, (void **) &old_Board_KeyUp);
    MSHookFunction(Board_UpdateSunSpawningAddr, (void *) Board_UpdateSunSpawning,(void **) &old_Board_UpdateSunSpawning);
    MSHookFunction(Board_UpdateZombieSpawningAddr, (void *) Board_UpdateZombieSpawning,(void **) &old_Board_UpdateZombieSpawning);
    MSHookFunction(Board_PickBackgroundAddr, (void *) Board_PickBackground,(void **) &old_Board_PickBackground);
    MSHookFunction(Board_DrawCoverLayerAddr, (void *) Board_DrawCoverLayer, NULL);
    MSHookFunction(Board_UpdateGameAddr, (void *) Board_UpdateGame,(void **) &old_Board_UpdateGame);
    MSHookFunction(Board_UpdateGameObjectsAddr, (void *) Board_UpdateGameObjects,(void **) &old_Board_UpdateGameObjects);
    MSHookFunction(Board_IsFlagWaveAddr, (void *) Board_IsFlagWave,(void **) &old_Board_IsFlagWave);
    MSHookFunction(Board_SpawnZombieWaveAddr, (void *) Board_SpawnZombieWave,(void **) &old_Board_SpawnZombieWave);
    MSHookFunction(Board_DrawProgressMeterAddr, (void *) Board_DrawProgressMeter,(void **) &old_Board_DrawProgressMeter);
    MSHookFunction(Board_GetNumWavesPerFlagAddr, (void *) Board_GetNumWavesPerFlag, NULL);
    MSHookFunction(Board_IsLevelDataLoadedAddr, (void *) Board_IsLevelDataLoaded,(void **) &old_Board_IsLevelDataLoaded);
    MSHookFunction(Board_NeedSaveGameAddr, (void *) Board_NeedSaveGame,(void **) &old_Board_NeedSaveGame);
    MSHookFunction(Board_UpdateFwooshAddr, (void *) Board_UpdateFwoosh,(void **) &old_Board_UpdateFwoosh);
    MSHookFunction(Board_UpdateFogAddr, (void *) Board_UpdateFog,(void **) &old_Board_UpdateFog);
    MSHookFunction(Board_DrawFogAddr, (void *) Board_DrawFog,(void **) &old_Board_DrawFog);
//    MSHookFunction(Board_UpdateCoverLayerAddr, (void *) Board_UpdateCoverLayer, (void **) &old_Board_UpdateCoverLayer);
    MSHookFunction(Board_UpdateIceAddr, (void *) Board_UpdateIce,(void **) &old_Board_UpdateIce);
    MSHookFunction(Board_DrawBackdropAddr, (void *) Board_DrawBackdrop,(void **) &old_Board_DrawBackdrop);
    MSHookFunction(Board_RowCanHaveZombieTypeAddr, (void *) Board_RowCanHaveZombieType,(void **) &old_Board_RowCanHaveZombieType);
    MSHookFunction(Board_DrawDebugTextAddr, (void *) Board_DrawDebugText,(void **) &old_Board_DrawDebugText);
    MSHookFunction(Board_DrawDebugObjectRectsAddr, (void *) Board_DrawDebugObjectRects,(void **) &old_Board_DrawDebugObjectRects);
    MSHookFunction(Board_DrawFadeOutAddr, (void *) Board_DrawFadeOut, NULL);
    MSHookFunction(Board_GetCurrentPlantCostAddr, (void *) Board_GetCurrentPlantCost,(void **) &old_Board_GetCurrentPlantCost);
    MSHookFunction(Board_PauseAddr, (void *) Board_Pause, (void **) &old_Board_Pause);
    MSHookFunction(Board_AddSecondPlayerAddr, (void *) Board_AddSecondPlayer, NULL);
    MSHookFunction(Board_IsLastStandFinalStageAddr, (void *) Board_IsLastStandFinalStage, NULL);
    MSHookFunction(Board_MouseHitTestAddr, (void *) Board_MouseHitTest, (void **) &old_Board_MouseHitTest);
    MSHookFunction(Board_DrawShovelAddr, (void *) Board_DrawShovel, NULL);
//    MSHookFunction(Board_StageIsNightAddr, (void *) Board_StageIsNight, NULL);
    MSHookFunction(Board_StageHasPoolAddr, (void *) Board_StageHasPool, NULL);
//    MSHookFunction(Board_StageHas6RowsAddr, (void *) Board_StageHas6Rows, NULL);
//    MSHookFunction(Board_GetNumSeedsInBankAddr, (void *) Board_GetNumSeedsInBank, (void **) &old_Board_GetNumSeedsInBank);
//    MSHookFunction(Board_GetSeedPacketPositionXAddr, (void *) Board_GetSeedPacketPositionX,(void **) &old_Board_GetSeedPacketPositionX);
//    MSHookFunction(Board_GetSeedBankExtraWidthAddr, (void *) Board_GetSeedBankExtraWidth,(void **) &old_Board_GetSeedBankExtraWidth);
    MSHookFunction(Board_AddZombieInRowAddr, (void *) Board_AddZombieInRow,(void **) &old_Board_AddZombieInRow);
    MSHookFunction(Board_DoPlantingEffectsAddr, (void *) Board_DoPlantingEffects, NULL);
    MSHookFunction(Board_InitLawnMowersAddr, (void *) Board_InitLawnMowers,(void **) &old_Board_InitLawnMowers);
    MSHookFunction(Board_PickZombieWavesAddr, (void *) Board_PickZombieWaves,(void **) &old_Board_PickZombieWaves);
    MSHookFunction(Board_DrawUITopAddr, (void *) Board_DrawUITop,(void **) &old_Board_DrawUITop);
    MSHookFunction(Board_GetShovelButtonRectAddr, (void *) Board_GetShovelButtonRect,(void **) &old_Board_GetShovelButtonRect);
    MSHookFunction(Board_DisplayAdviceAddr, (void *) Board_DisplayAdvice,(void **) &old_Board_DisplayAdvice);
    MSHookFunction(Board_UpdateLevelEndSequenceAddr, (void *) Board_UpdateLevelEndSequence,(void **) &old_Board_UpdateLevelEndSequence);
    MSHookFunction(Board_UpdateGridItemsAddr, (void *) Board_UpdateGridItems,(void **) &old_Board_UpdateGridItems);
    MSHookFunction(FixBoardAfterLoadAddr, (void *) FixBoardAfterLoad,(void **) &old_FixBoardAfterLoad);
    MSHookFunction(SyncReanimationAddr, (void *) SyncReanimation,(void **) &old_SyncReanimation);
    MSHookFunction(LawnSaveGameAddr, (void *) LawnSaveGame,(void **) &old_LawnSaveGame);


    MSHookFunction(Challenge_UpdateAddr, (void *) Challenge_Update,(void **) &old_Challenge_Update);
    MSHookFunction(Challenge_ChallengeAddr, (void *) Challenge_Challenge,(void **) &old_Challenge_Challenge);
    MSHookFunction(Challenge_HeavyWeaponFireAddr, (void *) Challenge_HeavyWeaponFire,(void **) &old_Challenge_HeavyWeaponFire);
    MSHookFunction(Challenge_IZombieDrawPlantAddr, (void *) Challenge_IZombieDrawPlant,NULL);
    MSHookFunction(Challenge_HeavyWeaponUpdateAddr, (void *) Challenge_HeavyWeaponUpdate,(void **) &old_Challenge_HeavyWeaponUpdate);
    MSHookFunction(Challenge_IZombieEatBrainAddr, (void *) Challenge_IZombieEatBrain, NULL);
    MSHookFunction(Challenge_DrawArtChallengeAddr, (void *) Challenge_DrawArtChallenge, NULL);
    MSHookFunction(Challenge_CanPlantAtAddr, (void *) Challenge_CanPlantAt, NULL);
    MSHookFunction(Challenge_DrawBackdropAddr, (void *) Challenge_DrawBackdrop, (void **) &old_Challenge_DrawBackdrop);
    MSHookFunction(Challenge_InitLevelAddr, (void *) Challenge_InitLevel, (void **) &old_Challenge_InitLevel);
    MSHookFunction(Challenge_InitZombieWavesAddr, (void *) Challenge_InitZombieWaves, (void **) &old_Challenge_InitZombieWaves);
    MSHookFunction(Challenge_LastStandCompletedStageAddr, (void *) Challenge_LastStandCompletedStage, (void **) &old_Challenge_LastStandCompletedStage);
    MSHookFunction(Challenge_TreeOfWisdomFertilizeAddr, (void *) Challenge_TreeOfWisdomFertilize, (void **) &old_Challenge_TreeOfWisdomFertilize);
    MSHookFunction(Challenge_LastStandUpdateAddr, (void *) Challenge_LastStandUpdate, NULL);
    MSHookFunction(Challenge_DrawHeavyWeaponAddr, (void *) Challenge_DrawHeavyWeapon, NULL);
    MSHookFunction(Challenge_UpdateZombieSpawningAddr, (void *) Challenge_UpdateZombieSpawning, (void **) &old_Challenge_UpdateZombieSpawning);
    MSHookFunction(Challenge_HeavyWeaponPacketClickedAddr, (void *) Challenge_HeavyWeaponPacketClicked, (void **) &old_Challenge_HeavyWeaponPacketClicked);
    MSHookFunction(Challenge_IZombieSeedTypeToZombieTypeAddr, (void *) Challenge_IZombieSeedTypeToZombieType, (void **) &old_Challenge_IZombieSeedTypeToZombieType);
    MSHookFunction(Challenge_StartLevelAddr, (void *) Challenge_StartLevel, (void **) &old_Challenge_StartLevel);


    MSHookFunction(ChallengeScreen_AddedToManagerAddr, (void *) ChallengeScreen_AddedToManager,(void **) &old_ChallengeScreen_AddedToManager);
    MSHookFunction(ChallengeScreen_RemovedFromManagerAddr,(void *) ChallengeScreen_RemovedFromManager,(void **) &old_ChallengeScreen_RemovedFromManager);
    MSHookFunction(ChallengeScreen_Delete2Addr, (void *) ChallengeScreen_Delete2,(void **) &old_ChallengeScreen_Delete2);
    MSHookFunction(ChallengeScreen_UpdateAddr, (void *) ChallengeScreen_Update,(void **) &old_ChallengeScreen_Update);
    MSHookFunction(ChallengeScreen_ChallengeScreenAddr, (void *) ChallengeScreen_ChallengeScreen,(void **) &old_ChallengeScreen_ChallengeScreen);
    MSHookFunction(ChallengeScreen_DrawAddr, (void *) ChallengeScreen_Draw,(void **) &old_ChallengeScreen_Draw);
    MSHookFunction(ChallengeScreen_ButtonPressAddr, (void *) ChallengeScreen_ButtonPress, NULL);
    MSHookFunction(ChallengeScreen_ButtonDepressAddr, (void *) ChallengeScreen_ButtonDepress, NULL);
    MSHookFunction(ChallengeScreen_UpdateButtonsAddr, (void *) ChallengeScreen_UpdateButtons, NULL);
    MSHookFunction(GetChallengeDefinitionAddr, (void *) GetChallengeDefinition,(void **) &old_GetChallengeDefinition);


    MSHookFunction(Coin_UpadteAddr, (void *) Coin_Update, (void **) &old_Coin_Update);
    MSHookFunction(Coin_GamepadCursorOverAddr, (void *) Coin_GamepadCursorOver,(void **) &old_Coin_GamepadCursorOver);
    MSHookFunction(Coin_MouseHitTestAddr, (void *) Coin_MouseHitTest,(void **) &old_Coin_MouseHitTest);
    MSHookFunction(Coin_TryAutoCollectAfterLevelAwardAddr, (void *) Coin_TryAutoCollectAfterLevelAward,(void **) &old_Coin_TryAutoCollectAfterLevelAward);
    MSHookFunction(Coin_UpdateFallAddr, (void *) Coin_UpdateFall,(void **) &old_Coin_UpdateFall);


    MSHookFunction(GamepadControls_ButtonDownFireCobcannonTestAddr,(void *) GamepadControls_ButtonDownFireCobcannonTest,(void **) &old_GamepadControls_ButtonDownFireCobcannonTest);
    MSHookFunction(GamepadControls_DrawAddr, (void *) GamepadControls_Draw,(void **) &old_GamepadControls_Draw);
    MSHookFunction(GamepadControls_GamepadControlsAddr, (void *) GamepadControls_GamepadControls,(void **) &old_GamepadControls_GamepadControls);
    MSHookFunction(GamepadControls_UpdateAddr,(void *) GamepadControls_Update,(void **) &old_GamepadControls_Update);
//    MSHookFunction(GamepadControls_InvalidatePreviewReanimAddr,(void *) GamepadControls_InvalidatePreviewReanim,NULL);
    MSHookFunction(GamepadControls_DrawPreviewAddr, (void *) GamepadControls_DrawPreview,(void **) &old_GamepadControls_DrawPreview);
//    MSHookFunction(GamepadControls_OnKeyDownAddr, (void *) GamepadControls_OnKeyDown,(void **) &old_GamepadControls_OnKeyDown);
    MSHookFunction(GamepadControls_UpdatePreviewReanimAddr, (void *) GamepadControls_UpdatePreviewReanim,(void **) &old_GamepadControls_UpdatePreviewReanim);


    MSHookFunction(GridItem_UpdateAddr, (void *) GridItem_Update,(void **) &old_GridItem_Update);
    MSHookFunction(GridItem_UpdateScaryPotAddr, (void *) GridItem_UpdateScaryPot,(void **) &old_GridItem_UpdateScaryPot);
    MSHookFunction(GridItem_DrawStinkyAddr, (void *) GridItem_DrawStinky,(void **) &old_GridItem_DrawStinky);
    MSHookFunction(GridItem_DrawSquirrelAddr, (void *) GridItem_DrawSquirrel, NULL);
    MSHookFunction(GridItem_DrawScaryPotAddr, (void *) GridItem_DrawScaryPot, NULL);


    MSHookFunction(AlmanacDialog_AddedToManagerAddr, (void *) AlmanacDialog_AddedToManager,(void **) &old_AlmanacDialog_AddedToManager);
    MSHookFunction(AlmanacDialog_RemovedFromManagerAddr, (void *) AlmanacDialog_RemovedFromManager,(void **) &old_AlmanacDialog_RemovedFromManager);
    MSHookFunction(AlmanacDialog_AlmanacDialogAddr, (void *) AlmanacDialog_AlmanacDialog,(void **) &old_AlmanacDialog_AlmanacDialog);
    MSHookFunction(AlmanacDialog_SetPageAddr, (void *) AlmanacDialog_SetPage,(void **) &old_AlmanacDialog_SetPage);
    MSHookFunction(AlmanacDialog_MouseDownAddr, (void *) AlmanacDialog_MouseDown, NULL);
    MSHookFunction(AlmanacDialog_MouseUpAddr, (void *) AlmanacDialog_MouseUp, NULL);
    MSHookFunction(AlmanacDialog_ButtonDepressAddr, (void *) AlmanacDialog_ButtonDepress, NULL);
    MSHookFunction(AlmanacDialog_Delete2Addr, (void *) AlmanacDialog_Delete2,(void **) &old_AlmanacDialog_Delete2);


    MSHookFunction(SeedChooserScreen_EnableStartButtonAddr,(void *) SeedChooserScreen_EnableStartButton,(void **) &old_SeedChooserScreen_EnableStartButton);
    MSHookFunction(SeedChooserScreen_RebuildHelpbarAddr, (void *) SeedChooserScreen_RebuildHelpbar,(void **) &old_SeedChooserScreen_RebuildHelpbar);
    MSHookFunction(SeedChooserScreen_SeedChooserScreenAddr,(void *) SeedChooserScreen_SeedChooserScreen,(void **) &old_SeedChooserScreen_SeedChooserScreen);
    MSHookFunction(SeedChooserScreen_GetZombieSeedTypeAddr,(void *) SeedChooserScreen_GetZombieSeedType, NULL);
    MSHookFunction(SeedChooserScreen_GetZombieTypeAddr, (void *) SeedChooserScreen_GetZombieType,NULL);
//    MSHookFunction(SeedChooserScreen_RemoveToolTipAddr, (void *) SeedChooserScreen_RemoveToolTip,NULL);
    MSHookFunction(SeedChooserScreen_ClickedSeedInChooserAddr, (void *) SeedChooserScreen_ClickedSeedInChooser,(void **) &old_SeedChooserScreen_ClickedSeedInChooser);
    MSHookFunction(SeedChooserScreen_CrazyDavePickSeedsAddr, (void *) SeedChooserScreen_CrazyDavePickSeeds,(void **) &old_SeedChooserScreen_CrazyDavePickSeeds);
    MSHookFunction(SeedChooserScreen_OnStartButtonAddr, (void *) SeedChooserScreen_OnStartButton,(void **) &old_SeedChooserScreen_OnStartButton);
    MSHookFunction(SeedChooserScreen_UpdateAddr, (void *) SeedChooserScreen_Update,(void **) &old_SeedChooserScreen_Update);
    MSHookFunction(SeedChooserScreen_SeedNotAllowedToPickAddr,(void *) SeedChooserScreen_SeedNotAllowedToPick,(void **) &old_SeedChooserScreen_SeedNotAllowedToPick);
    MSHookFunction(SeedChooserScreen_ClickedSeedInBankAddr,(void *) SeedChooserScreen_ClickedSeedInBank,(void **) &old_SeedChooserScreen_ClickedSeedInBank);
    MSHookFunction(SeedChooserScreen_GameButtonDownAddr,(void *) SeedChooserScreen_GameButtonDown,(void **) &old_SeedChooserScreen_GameButtonDown);
    MSHookFunction(SeedChooserScreen_OnKeyDownAddr,(void *) SeedChooserScreen_OnKeyDown,(void **) &old_SeedChooserScreen_OnKeyDown);
    MSHookFunction(SeedChooserScreen_DrawPacketAddr,(void *) SeedChooserScreen_DrawPacket,NULL);
    MSHookFunction(SeedChooserScreen_ButtonDepressAddr, (void *) SeedChooserScreen_ButtonDepress, (void **) &old_SeedChooserScreen_ButtonDepress);
    MSHookFunction(SeedChooserScreen_GetSeedPositionInBankAddr, (void *) SeedChooserScreen_GetSeedPositionInBank, (void **) &old_SeedChooserScreen_GetSeedPositionInBank);
    MSHookFunction(SeedChooserScreen_ShowToolTipAddr, (void *) SeedChooserScreen_ShowToolTip, (void **) &old_SeedChooserScreen_ShowToolTip);


    MSHookFunction(MainMenu_KeyDownAddr, (void *) MainMenu_KeyDown,(void **) &old_MainMenu_KeyDown);
    MSHookFunction(MainMenu_ButtonDepressAddr, (void *) MainMenu_ButtonDepress,(void **) &old_MainMenu_ButtonDepress);
    MSHookFunction(MainMenu_UpdateAddr, (void *) MainMenu_Update, (void **) &old_MainMenu_Update);
    MSHookFunction(MainMenu_SyncProfileAddr, (void *) MainMenu_SyncProfile, (void **) &old_MainMenu_SyncProfile);
    MSHookFunction(MainMenu_EnterAddr, (void *) MainMenu_Enter, (void **) &old_MainMenu_Enter);
    MSHookFunction(MainMenu_ExitAddr, (void *) MainMenu_Exit, (void **) &old_MainMenu_Exit);
    MSHookFunction(MainMenu_UpdateExitAddr, (void *) MainMenu_UpdateExit, (void **) &old_MainMenu_UpdateExit);
    MSHookFunction(MainMenu_OnExitAddr, (void *) MainMenu_OnExit, (void **) &old_MainMenu_OnExit);
//    MSHookFunction(MainMenu_SetSceneAddr, (void *) MainMenu_SetScene, (void **) &old_MainMenu_SetScene);
    MSHookFunction(MainMenu_OnSceneAddr, (void *) MainMenu_OnScene, (void **) &old_MainMenu_OnScene);
    MSHookFunction(MainMenu_SyncButtonsAddr, (void *) MainMenu_SyncButtons, (void **) &old_MainMenu_SyncButtons);
    MSHookFunction(MainMenu_MainMenuAddr, (void *) MainMenu_MainMenu, (void **) &old_MainMenu_MainMenu);
    MSHookFunction(MainMenu_UpdateCameraPositionAddr, (void *) MainMenu_UpdateCameraPosition, (void **) &old_MainMenu_UpdateCameraPosition);
    MSHookFunction(MainMenu_AddedToManagerAddr, (void *) MainMenu_AddedToManager, (void **) &old_MainMenu_AddedToManager);
    MSHookFunction(MainMenu_RemovedFromManagerAddr, (void *) MainMenu_RemovedFromManager, (void **) &old_MainMenu_RemovedFromManager);
    MSHookFunction(MainMenu_DrawOverlayAddr, (void *) MainMenu_DrawOverlay, (void **) &old_MainMenu_DrawOverlay);
    MSHookFunction(MainMenu_Delete2Addr, (void *) MainMenu_Delete2, (void **) &old_MainMenu_Delete2);
    MSHookFunction(MainMenu_DrawAddr, (void *) MainMenu_Draw, (void **) &old_MainMenu_Draw);


    MSHookFunction(StoreScreen_UpdateAddr, (void *) StoreScreen_Update,(void **) &old_StoreScreen_Update);
    MSHookFunction(StoreScreen_SetupPageAddr, (void *) StoreScreen_SetupPage,(void **) &old_StoreScreen_SetupPage);
    MSHookFunction(StoreScreen_ButtonDepressAddr, (void *) StoreScreen_ButtonDepress,(void **) &old_StoreScreen_ButtonDepress);
    MSHookFunction(StoreScreen_AddedToManagerAddr, (void *) StoreScreen_AddedToManager,(void **) &old_StoreScreen_AddedToManager);
    MSHookFunction(StoreScreen_RemovedFromManagerAddr, (void *) StoreScreen_RemovedFromManager,(void **) &old_StoreScreen_RemovedFromManager);
    MSHookFunction(StoreScreen_PurchaseItemAddr, (void *) StoreScreen_PurchaseItem,(void **) &old_StoreScreen_PurchaseItem);
    MSHookFunction(StoreScreen_DrawAddr, (void *) StoreScreen_Draw,(void **) &old_StoreScreen_Draw);
    MSHookFunction(StoreScreen_DrawItemAddr, (void *) StoreScreen_DrawItem,(void **) &old_StoreScreen_DrawItem);


    MSHookFunction(Plant_UpdateAddr, (void *) Plant_Update, (void **) &old_Plant_Update);
    MSHookFunction(Plant_GetRefreshTimeAddr, (void *) Plant_GetRefreshTime,(void **) &old_Plant_GetRefreshTime);
    MSHookFunction(Plant_DoSpecialAddr, (void *) Plant_DoSpecial, (void **) &old_Plant_DoSpecial);
    MSHookFunction(Plant_DrawAddr, (void *) Plant_Draw, (void **) &old_Plant_Draw);
    MSHookFunction(Plant_DrawSeedTypeAddr, (void *) Plant_DrawSeedType, NULL);
    MSHookFunction(Plant_IsUpgradeAddr, (void *) Plant_IsUpgrade, (void **) &old_Plant_IsUpgrade);
//    MSHookFunction(Plant_CobCannonFireAddr, (void *) Plant_CobCannonFire, (void **) &old_Plant_CobCannonFire);
    MSHookFunction(Plant_PlantInitializeAddr, (void *) Plant_PlantInitialize, (void **) &old_Plant_PlantInitialize);
    MSHookFunction(Plant_SetSleepingAddr, (void *) Plant_SetSleeping,(void **) &old_Plant_SetSleeping);
    MSHookFunction(Plant_UpdateReanimColorAddr, (void *) Plant_UpdateReanimColor,(void **) &old_Plant_UpdateReanimColor);
    MSHookFunction(Plant_FindTargetGridItemAddr, (void *) Plant_FindTargetGridItem, NULL);
    MSHookFunction(Plant_GetCostAddr, (void *) Plant_GetCost,(void **) &old_Plant_GetCost);
//    MSHookFunction(Plant_DieAddr, (void *) Plant_Die,(void **) &old_Plant_Die);
//    MSHookFunction(Plant_UpdateReanimAddr, (void *) Plant_UpdateReanim, (void **) &old_Plant_UpdateReanim);


    MSHookFunction(Projectile_ProjectileInitializeAddr, (void *) Projectile_ProjectileInitialize,(void **) &old_Projectile_ProjectileInitialize);
    MSHookFunction(Projectile_ConvertToFireballAddr, (void *) Projectile_ConvertToFireball,(void **) &old_Projectile_ConvertToFireball);
    MSHookFunction(Projectile_ConvertToPeaAddr, (void *) Projectile_ConvertToPea, (void **) &old_Projectile_ConvertToPea);
    MSHookFunction(Projectile_UpdateAddr, (void *) Projectile_Update,(void **) &old_Projectile_Update);
    MSHookFunction(Projectile_DoImpactAddr, (void *) Projectile_DoImpact,(void **) &old_Projectile_DoImpact);
    MSHookFunction(Projectile_CheckForCollisionAddr, (void *) Projectile_CheckForCollision, NULL);


    MSHookFunction(SeedPacket_UpdateAddr, (void *) SeedPacket_Update,(void **) &old_SeedPacket_Update);
    MSHookFunction(SeedPacket_UpdateSelectedAddr, (void *) SeedPacket_UpdateSelected,(void **) &old_SeedPacket_UpdateSelected);
    MSHookFunction(SeedPacket_DrawOverlayAddr, (void *) SeedPacket_DrawOverlay,(void **) &old_SeedPacket_DrawOverlay);
    MSHookFunction(SeedPacket_DrawAddr, (void *) SeedPacket_Draw,(void **) &old_SeedPacket_Draw);
    MSHookFunction(SeedPacket_FlashIfReadyAddr, (void *) SeedPacket_FlashIfReady,(void **) &old_SeedPacket_FlashIfReady);
//    MSHookFunction(SeedPacket_MouseDownAddr, (void *) SeedPacket_MouseDown, (void **) &old_SeedPacket_MouseDown);


    MSHookFunction(Zombie_UpdateAddr, (void *) Zombie_Update, (void **) &old_Zombie_Update);
    MSHookFunction(Zombie_UpdateZombiePeaHeadAddr, (void *) Zombie_UpdateZombiePeaHead,(void **) &old_Zombie_UpdateZombiePeaHead);
    MSHookFunction(Zombie_UpdateZombieGatlingHeadAddr, (void *) Zombie_UpdateZombieGatlingHead,(void **) &old_Zombie_UpdateZombieGatlingHead);
    MSHookFunction(Zombie_UpdateZombieJalapenoHeadAddr, (void *) Zombie_UpdateZombieJalapenoHead,(void **) &old_Zombie_UpdateZombieJalapenoHead);
    MSHookFunction(Zombie_GetDancerFrameAddr, (void *) Zombie_GetDancerFrame, NULL);
    MSHookFunction(Zombie_RiseFromGraveAddr, (void *) Zombie_RiseFromGrave,(void **) &old_Zombie_RiseFromGrave);
    MSHookFunction(Zombie_EatPlantAddr, (void *) Zombie_EatPlant,(void **) &old_Zombie_EatPlant);
    MSHookFunction(Zombie_DetachShieldAddr, (void *) Zombie_DetachShield,(void **) &old_Zombie_DetachShield);
    MSHookFunction(Zombie_CheckForBoardEdgeAddr, (void *) Zombie_CheckForBoardEdge, NULL);
    MSHookFunction(Zombie_DrawAddr, (void *) Zombie_Draw, (void **) &old_Zombie_Draw);
    MSHookFunction(Zombie_DrawBossPartAddr, (void *) Zombie_DrawBossPart,(void **) &old_Zombie_DrawBossPart);
    MSHookFunction(ZombieTypeCanGoInPoolAddr, (void *) ZombieTypeCanGoInPool,(void **) &old_ZombieTypeCanGoInPool);
    MSHookFunction(Zombie_BossSpawnAttackAddr, (void *) Zombie_BossSpawnAttack, NULL);
    MSHookFunction(Zombie_DrawBungeeCordAddr, (void *) Zombie_DrawBungeeCord, NULL);
    MSHookFunction(Zombie_IsTangleKelpTargetAddr, (void *) Zombie_IsTangleKelpTarget, NULL);
    MSHookFunction(Zombie_IsTangleKelpTarget2Addr, (void *) Zombie_IsTangleKelpTarget, NULL);
    MSHookFunction(Zombie_DrawReanimAddr, (void *) Zombie_DrawReanim, (void **) &old_Zombie_DrawReanim);
    MSHookFunction(Zombie_DropHeadAddr, (void *) Zombie_DropHead, (void **) &old_Zombie_DropHead);
    MSHookFunction(Zombie_ZombieInitializeAddr, (void *) Zombie_ZombieInitialize, (void **) &old_Zombie_ZombieInitialize);
    MSHookFunction(Zombie_DieNoLootAddr, (void *) Zombie_DieNoLoot, (void **) &old_Zombie_DieNoLoot);
    MSHookFunction(GetZombieDefinitionAddr, (void *) GetZombieDefinition,(void **) &old_GetZombieDefinition);


    MSHookFunction(Sexy_Dialog_AddedToManagerWidgetManagerAddr, (void *) SexyDialog_AddedToManager,(void **) &old_SexyDialog_AddedToManager);
    MSHookFunction(Sexy_Dialog_RemovedFromManagerAddr, (void *) SexyDialog_RemovedFromManager,(void **) &old_SexyDialog_RemovedFromManager);


    MSHookFunction(SeedBank_DrawAddr, (void *) SeedBank_Draw, (void **) &old_SeedBank_Draw);
    MSHookFunction(SeedBank_MouseHitTestAddr, (void *) SeedBank_MouseHitTest, NULL);
    MSHookFunction(SeedBank_SeedBankAddr, (void *) SeedBank_SeedBank, (void **) &old_SeedBank_SeedBank);
    MSHookFunction(SeedBank_UpdateWidthAddr, (void *) SeedBank_UpdateWidth, (void **) &old_SeedBank_UpdateWidth);
    MSHookFunction(SeedBank_MoveAddr, (void *) SeedBank_Move, NULL);


    MSHookFunction(AwardScreen_MouseDownAddr, (void *) AwardScreen_MouseDown,(void **) &old_AwardScreen_MouseDown);
    MSHookFunction(AwardScreen_MouseUpAddr, (void *) AwardScreen_MouseUp,(void **) &old_AwardScreen_MouseUp);


    MSHookFunction(VSSetupMenu_UpdateAddr, (void *) VSSetupMenu_Update,(void **) &old_VSSetupMenu_Update);
    MSHookFunction(VSSetupMenu_KeyDownAddr, (void *) VSSetupMenu_KeyDown,(void **) &old_VSSetupMenu_KeyDown);


    MSHookFunction(VSResultsMenu_UpdateAddr, (void *) VSResultsMenu_Update,(void **) &old_VSResultsMenu_Update);
    MSHookFunction(VSResultsMenu_OnExitAddr, (void *) VSResultsMenu_OnExit,(void **) &old_VSResultsMenu_OnExit);
    MSHookFunction(VSResultsMenu_DrawInfoBoxAddr, (void *) VSResultsMenu_DrawInfoBox,(void **) &old_VSResultsMenu_DrawInfoBox);
    MSHookFunction(VSResultsMenu_ButtonDepressAddr, (void *) VSResultsMenu_ButtonDepress, NULL);


    MSHookFunction(ImitaterDialog_ImitaterDialogAddr, (void *) ImitaterDialog_ImitaterDialog,(void **) &old_ImitaterDialog_ImitaterDialog);
    MSHookFunction(ImitaterDialog_MouseDownAddr, (void *) ImitaterDialog_MouseDown,(void **) &old_ImitaterDialog_MouseDown);
//    MSHookFunction(ImitaterDialog_OnKeyDownAddr, (void *) ImitaterDialog_OnKeyDown,(void **) &old_ImitaterDialog_OnKeyDown);
    MSHookFunction(ImitaterDialog_KeyDownAddr, (void *) ImitaterDialog_KeyDown,(void **) &old_ImitaterDialog_KeyDown);
    MSHookFunction(ImitaterDialog_ShowToolTipAddr, (void *) ImitaterDialog_ShowToolTip,(void **) &old_ImitaterDialog_ShowToolTip);


    MSHookFunction(MailScreen_MailScreenAddr, (void *) MailScreen_MailScreen, (void **) &old_MailScreen_MailScreen);
    MSHookFunction(MailScreen_AddedToManagerAddr, (void *) MailScreen_AddedToManager, (void **) &old_MailScreen_AddedToManager);
    MSHookFunction(MailScreen_RemovedFromManagerAddr, (void *) MailScreen_RemovedFromManager, (void **) &old_MailScreen_RemovedFromManager);
    MSHookFunction(MailScreen_Delete2Addr, (void *) MailScreen_Delete2, (void **) &old_MailScreen_Delete2);


    MSHookFunction(ZenGardenControls_UpdateAddr, (void *) ZenGardenControls_Update,(void **) &old_ZenGardenControls_Update);
    MSHookFunction(ZenGarden_DrawBackdropAddr, (void *) ZenGarden_DrawBackdrop, (void **) &old_ZenGarden_DrawBackdrop);
//    MSHookFunction(ZenGarden_MouseDownWithFeedingToolAddr, (void *) ZenGarden_MouseDownWithFeedingTool, (void **) &old_ZenGarden_MouseDownWithFeedingTool);
    //MSHookFunction(ZenGarden_DrawPottedPlantAddr, (void *) ZenGarden_DrawPottedPlant, NULL);

//    MSHookFunction( Sexy_GamepadApp_CheckGamepadAddr,(void *) Sexy_GamepadApp_CheckGamepad,NULL);
//    MSHookFunction( Sexy_GamepadApp_HasGamepadAddr,(void *) Sexy_GamepadApp_HasGamepad,NULL);


    MSHookFunction(CutScene_ShowShovelAddr, (void *) CutScene_ShowShovel, (void **) &old_CutScene_ShowShovel);
    MSHookFunction(BaseGamepadControls_GetGamepadVelocityAddr, (void *) BaseGamepadControls_GetGamepadVelocity, NULL);
    MSHookFunction(LookupFoleyAddr, (void *) LookupFoley, (void **) &old_LookupFoley);
//    MSHookFunction(TodDrawStringWrappedHelperAddr, (void *) TodDrawStringWrappedHelper, (void **) &old_TodDrawStringWrappedHelper);
    MSHookFunction(MessageWidget_ClearLabelAddr, (void *) MessageWidget_ClearLabel, (void **) &old_MessageWidget_ClearLabel);
    MSHookFunction(MessageWidget_SetLabelAddr, (void *) MessageWidget_SetLabel, (void **) &old_MessageWidget_SetLabel);
    MSHookFunction(MessageWidget_UpdateAddr, (void *) MessageWidget_Update, (void **) &old_MessageWidget_Update);
    MSHookFunction(MessageWidget_DrawAddr, (void *) MessageWidget_Draw, (void **) &old_MessageWidget_Draw);
    MSHookFunction(Sexy_ExtractLoadingSoundsResourcesAddr, (void *) Sexy_ExtractLoadingSoundsResources, (void **) &old_Sexy_ExtractLoadingSoundsResources);
    MSHookFunction(CutScene_UpdateAddr, (void *) CutScene_Update, (void **) &old_CutScene_Update);
//    MSHookFunction(Sexy_ScrollbarWidget_MouseDownAddr, (void *) Sexy_ScrollbarWidget_MouseDown,NULL);
    MSHookFunction(CustomScrollbarWidget_RemoveScrollButtonsAddr, (void *) CustomScrollbarWidget_RemoveScrollButtons,NULL);
    MSHookFunction(CreditScreen_CreditScreenAddr, (void *) CreditScreen_CreditScreen,(void **) &old_CreditScreen_CreditScreen);
    MSHookFunction(CreditScreen_RemovedFromManagerAddr, (void *) CreditScreen_RemovedFromManager,(void **) &old_CreditScreen_RemovedFromManager);
    MSHookFunction(CreditScreen_Delete2Addr, (void *) CreditScreen_Delete2,(void **) &old_CreditScreen_Delete2);

    MSHookFunction(HelpTextScreen_AddedToManagerAddr, (void *) HelpTextScreen_AddedToManager,(void **) &old_HelpTextScreen_AddedToManager);
    MSHookFunction(HelpTextScreen_RemovedFromManagerAddr, (void *) HelpTextScreen_RemovedFromManager,(void **) &old_HelpTextScreen_RemovedFromManager);
    MSHookFunction(HelpTextScreen_HelpTextScreenAddr, (void *) HelpTextScreen_HelpTextScreen, (void **) &old_HelpTextScreen_HelpTextScreen);
    MSHookFunction(HelpTextScreen_Delete2Addr, (void *) HelpTextScreen_Delete2,(void **) &old_HelpTextScreen_Delete2);
    MSHookFunction(HelpTextScreen_UpdateAddr, (void *) HelpTextScreen_Update, (void **) &old_HelpTextScreen_Update);
    MSHookFunction(HelpOptionsDialog_ButtonDepressAddr, (void *) HelpOptionsDialog_ButtonDepress,(void **) &old_HelpOptionsDialog_ButtonDepress);
    MSHookFunction(HelpOptionsDialog_HelpOptionsDialogAddr, (void *) HelpOptionsDialog_HelpOptionsDialog,(void **) &old_HelpOptionsDialog_HelpOptionsDialog);
    MSHookFunction(HelpOptionsDialog_ResizeAddr, (void *) HelpOptionsDialog_Resize,(void **) &old_HelpOptionsDialog_Resize);

    MSHookFunction(WaitForSecondPlayerDialog_WaitForSecondPlayerDialogAddr,(void *) WaitForSecondPlayerDialog_WaitForSecondPlayerDialog,(void **) &old_WaitForSecondPlayerDialog_WaitForSecondPlayerDialog);
//    MSHookFunction(Sexy_WidgetManager_MouseDownAddr, (void *) Sexy_WidgetManager_MouseDown,(void **) &old_Sexy_WidgetManager_MouseDown);
//    MSHookFunction(Sexy_WidgetManager_AxisMovedAddr, (void *) Sexy_WidgetManager_AxisMoved, NULL);
    MSHookFunction(LawnMower_UpdateAddr, (void *) LawnMower_Update,(void **) &old_LawnMower_Update);
    MSHookFunction(ConfirmBackToMainDialog_ButtonDepressAddr,(void *) ConfirmBackToMainDialog_ButtonDepress,(void **) &old_ConfirmBackToMainDialog_ButtonDepress);
    MSHookFunction(ConfirmBackToMainDialog_AddedToManagerAddr,(void *) ConfirmBackToMainDialog_AddedToManager,(void **) &old_ConfirmBackToMainDialog_AddedToManager);
//    MSHookFunction(FilterEffectDisposeForAppAddr,(void *) FilterEffectDisposeForApp,NULL);
//    MSHookFunction(FilterEffectGetImageAddr,(void *) FilterEffectGetImage,NULL);
    MSHookFunction(Reanimation_DrawTrackAddr,(void *) Reanimation_DrawTrack,(void **) &old_Reanimation_DrawTrack);
    MSHookFunction(ReanimatorCache_DrawCachedPlantAddr,(void *) ReanimatorCache_DrawCachedPlant,(void **) &old_ReanimatorCache_DrawCachedPlant);
    MSHookFunction(ReanimatorCache_UpdateReanimationForVariationAddr,(void *) ReanimatorCache_UpdateReanimationForVariation,(void **) &old_ReanimatorCache_UpdateReanimationForVariation);
    MSHookFunction(ReanimatorCache_LoadCachedImagesAddr,(void *) ReanimatorCache_LoadCachedImages,(void **) &old_ReanimatorCache_LoadCachedImages);
    MSHookFunction(HelpBarWidget_HelpBarWidgetAddr,(void *) HelpBarWidget_HelpBarWidget,(void **) &old_HelpBarWidget_HelpBarWidget);
    MSHookFunction(DrawSeedTypeAddr, (void *) DrawSeedType,NULL);
    MSHookFunction(DrawSeedPacketAddr, (void *) DrawSeedPacket, NULL);
    MSHookFunction(Music_PlayMusicAddr,(void *) Music_PlayMusic,NULL);
    MSHookFunction(Music_MusicUpdateAddr, (void *) Music_MusicUpdate, NULL);
    MSHookFunction(Music_UpdateMusicBurstAddr,(void *) Music_UpdateMusicBurst,(void **) &old_Music_UpdateMusicBurst);
    MSHookFunction(Music2_Music2Addr,(void *) Music2_Music2,(void **) &old_Music2_Music2);
    MSHookFunction(LawnPlayerInfo_AddCoinsAddr, (void *) LawnPlayerInfo_AddCoins, NULL);
    MSHookFunction(MaskHelpWidget_DrawAddr, (void *) MaskHelpWidget_Draw, NULL);
//    MSHookFunction(DaveHelp_DaveHelpAddr, (void *) DaveHelp_DaveHelp, (void **) &old_DaveHelp_DaveHelp);
    MSHookFunction(DaveHelp_UpdateAddr, (void *) DaveHelp_Update, NULL);
    MSHookFunction(DaveHelp_DrawAddr, (void *) DaveHelp_Draw, NULL);
    MSHookFunction(DaveHelp_Delete2Addr, (void *) DaveHelp_Delete2, (void **) &old_DaveHelp_Delete2);
    MSHookFunction(DaveHelp_DealClickAddr, (void *) DaveHelp_DealClick, NULL);
    MSHookFunction(TrashBin_TrashBinAddr, (void *) TrashBin_TrashBin, (void **) &old_TrashBin_TrashBin);
    MSHookFunction(Sexy_SexyAppBase_Is3DAcceleratedAddr, (void *) Sexy_SexyAppBase_Is3DAccelerated, NULL);
    MSHookFunction(Sexy_SexyAppBase_SexyAppBaseAddr,(void *) Sexy_SexyAppBase_SexyAppBase,(void **) &old_Sexy_SexyAppBase_SexyAppBase);
    MSHookFunction(SettingsDialog_AddedToManagerAddr,(void *) SettingsDialog_AddedToManager,(void **) &old_SettingsDialog_AddedToManager);
    MSHookFunction(SettingsDialog_RemovedFromManagerAddr,(void *) SettingsDialog_RemovedFromManager,(void **) &old_SettingsDialog_RemovedFromManager);
    MSHookFunction(SettingsDialog_DrawAddr,(void *) SettingsDialog_Draw,(void **) &old_SettingsDialog_Draw);
    MSHookFunction(SettingsDialog_Delete2Addr,(void *) SettingsDialog_Delete2,(void **) &old_SettingsDialog_Delete2);
    MSHookFunction(ReanimatorLoadDefinitionsAddr,(void *) ReanimatorLoadDefinitions,(void **) &old_ReanimatorLoadDefinitions);
    MSHookFunction(DefinitionGetCompiledFilePathFromXMLFilePathAddr,(void *) DefinitionGetCompiledFilePathFromXMLFilePath,(void **) &old_DefinitionGetCompiledFilePathFromXMLFilePath);
    MSHookFunction(TestMenuWidget_DeleteAddr,(void *) TestMenuWidget_Delete,(void **) &old_TestMenuWidget_Delete);
    MSHookFunction(TestMenuWidget_Delete2Addr,(void *) TestMenuWidget_Delete2,(void **) &old_TestMenuWidget_Delete2);
    MSHookFunction(SaveGameContext_SyncReanimationDefAddr,(void *) SaveGameContext_SyncReanimationDef,NULL);


}

bool VTableHookFunction(void *vTableAddress, int sequenceNumber, void *theFunction, void **result) {
    void **theRealAddress = ((void **) vTableAddress + sequenceNumber);
    //获取vTable加偏移后的内存地址
    size_t page_size = sysconf(_SC_PAGESIZE);
    //获取操作系统的内存分页大小
    void *page_start = (void *) ((uintptr_t) theRealAddress & ~(page_size - 1));
    // 计算此地址所在的内存页的起始地址
    int returnValue = mprotect(page_start, page_size, PROT_READ | PROT_WRITE);
    // 修改该内存页为可读写
    if (returnValue == -1) return false;
    //如果修改成功(返回值不为-1就是修改成功)，就能读写了。
    if (result != NULL) {
        //将原虚函数赋值给result
        *result = *theRealAddress;
    }
    //修改虚函数为指定函数
    *theRealAddress = theFunction;
    return true;
}

void InitVTableHookFunction() {
    VTableHookFunction(vTableForCursorObjectAddr, 4, (void *) CursorObject_BeginDraw,(void **) &old_CursorObject_BeginDraw);
    VTableHookFunction(vTableForCursorObjectAddr,5, (void *) CursorObject_EndDraw,(void **) &old_CursorObject_EndDraw);

    VTableHookFunction(vTableForBoardAddr, 77, (void *) Board_MouseMove,(void **) &old_Board_MouseMove);
    VTableHookFunction(vTableForBoardAddr, 78, (void *) Board_MouseDown,(void **) &old_Board_MouseDown);
    VTableHookFunction(vTableForBoardAddr, 81, (void *) Board_MouseUp,(void **) &old_Board_MouseUp);
    VTableHookFunction(vTableForBoardAddr, 83, (void *) Board_MouseDrag,(void **) &old_Board_MouseDrag);
    VTableHookFunction(vTableForBoardAddr, 133, (void *) Board_ButtonDepress,(void **) &old_Board_ButtonDepress);

    VTableHookFunction(vTableForStoreScreenAddr, 78, (void *) StoreScreen_MouseDown,(void **) &old_StoreScreen_MouseDown);
    VTableHookFunction(vTableForStoreScreenAddr, 81, (void *) StoreScreen_MouseUp,(void **) &old_StoreScreen_MouseUp);
//    VTableHookFunction(vTableForStoreScreenAddr, 83, (void *) StoreScreen_MouseDrag,(void **) &old_StoreScreen_MouseDrag);

    VTableHookFunction(vTableForMailScreenAddr, 78, (void *) MailScreen_MouseDown,(void **) &old_MailScreen_MouseDown);
    VTableHookFunction(vTableForMailScreenAddr, 81, (void *) MailScreen_MouseUp,(void **) &old_MailScreen_MouseUp);
    VTableHookFunction(vTableForMailScreenAddr, 83, (void *) MailScreen_MouseDrag,(void **) &old_MailScreen_MouseDrag);
    VTableHookFunction(vTableForMailScreenAddr, 140, (void *) MailScreen_ButtonPress,(void **) &old_MailScreen_ButtonPress);
    VTableHookFunction(vTableForMailScreenAddr, 141, (void *) MailScreen_ButtonDepress,(void **) &old_MailScreen_ButtonDepress);

    VTableHookFunction(vTableForChallengeScreenAddr, 78, (void *) ChallengeScreen_MouseDown,(void **) &old_ChallengeScreen_MouseDown);
    VTableHookFunction(vTableForChallengeScreenAddr, 81, (void *) ChallengeScreen_MouseUp,(void **) &old_ChallengeScreen_MouseUp);
    VTableHookFunction(vTableForChallengeScreenAddr, 83, (void *) ChallengeScreen_MouseDrag,(void **) &old_ChallengeScreen_MouseDrag);

//    VTableHookFunction(vTableForVSResultsMenuAddr, 78, (void *) VSResultsMenu_MouseDown,(void **) &old_VSResultsMenu_MouseDown);
//    VTableHookFunction(vTableForVSResultsMenuAddr, 81, (void *) VSResultsMenu_MouseUp,(void **) &old_VSResultsMenu_MouseUp);
//    VTableHookFunction(vTableForVSResultsMenuAddr, 83, (void *) VSResultsMenu_MouseDrag,(void **) &old_VSResultsMenu_MouseDrag);

    VTableHookFunction(vTableForSeedChooserScreenAddr, 77, (void *) SeedChooserScreen_MouseMove,(void **) &old_SeedChooserScreen_MouseMove);
    VTableHookFunction(vTableForSeedChooserScreenAddr, 78, (void *) SeedChooserScreen_MouseDown,(void **) &old_SeedChooserScreen_MouseDown);
    VTableHookFunction(vTableForSeedChooserScreenAddr, 81, (void *) SeedChooserScreen_MouseUp,(void **) &old_SeedChooserScreen_MouseUp);
    VTableHookFunction(vTableForSeedChooserScreenAddr, 83, (void *) SeedChooserScreen_MouseDrag,(void **) &old_SeedChooserScreen_MouseDrag);
    VTableHookFunction(vTableForSeedChooserScreenAddr, 135, (void *) SeedChooserScreen_ButtonPress,NULL);


    VTableHookFunction(vTableForHelpTextScreenAddr, 38, (void *) HelpTextScreen_Draw,(void **) &old_HelpTextScreen_Draw);
    VTableHookFunction(vTableForHelpTextScreenAddr, 78, (void *) HelpTextScreen_MouseDown,(void **) &old_HelpTextScreen_MouseDown);
//    VTableHookFunction(vTableForHelpTextScreenAddr, 81, (void *) HelpTextScreen_MouseUp,(void **) &old_HelpTextScreen_MouseUp);
//    VTableHookFunction(vTableForHelpTextScreenAddr, 83, (void *) HelpTextScreen_MouseDrag,(void **) &old_HelpTextScreen_MouseDrag);
    VTableHookFunction(vTableForHelpTextScreenAddr, 136, (void *) HelpTextScreen_ButtonDepress,(void **) &old_HelpTextScreen_ButtonDepress);

    VTableHookFunction(vTableForAlmanacDialogAddr, 83, (void *) AlmanacDialog_MouseDrag,(void **) &old_AlmanacDialog_MouseDrag);

    VTableHookFunction(vTableForHouseChooserDialogAddr, 73, (void *) HouseChooserDialog_KeyDown,(void **) &old_HouseChooserDialog_KeyDown);
    VTableHookFunction(vTableForHouseChooserDialogAddr, 78, (void *) HouseChooserDialog_MouseDown,(void **) &old_HouseChooserDialog_MouseDown);

    VTableHookFunction(vTableForSeedPacketAddr, 4, (void *) SeedPacket_BeginDraw,(void **) &old_SeedPacket_BeginDraw);
    VTableHookFunction(vTableForSeedPacketAddr,5, (void *) SeedPacket_EndDraw,(void **) &old_SeedPacket_EndDraw);

    VTableHookFunction(vTableForSeedBankAddr, 4, (void *) SeedBank_BeginDraw,(void **) &old_SeedBank_BeginDraw);
    VTableHookFunction(vTableForSeedBankAddr,5, (void *) SeedBank_EndDraw,(void **) &old_SeedBank_EndDraw);

    VTableHookFunction(vTableForGraphicsAddr, 4, (void *) Sexy_Graphics_PushTransform,(void **) &old_Sexy_Graphics_PushTransform);
    VTableHookFunction(vTableForGraphicsAddr,5, (void *) Sexy_Graphics_PopTransform,(void **) &old_Sexy_Graphics_PopTransform);


    VTableHookFunction(vTableForImageAddr, 37, (void *) Sexy_Image_PushTransform,(void **) &old_Sexy_Image_PushTransform);
    VTableHookFunction(vTableForImageAddr,38, (void *) Sexy_Image_PopTransform,(void **) &old_Sexy_Image_PopTransform);

    VTableHookFunction(vTableForGLImageAddr, 37, (void *) Sexy_GLImage_PushTransform,(void **) &old_Sexy_GLImage_PushTransform);
    VTableHookFunction(vTableForGLImageAddr,38, (void *) Sexy_GLImage_PopTransform,(void **) &old_Sexy_GLImage_PopTransform);

    VTableHookFunction(vTableForMemoryImageAddr, 37, (void *) Sexy_MemoryImage_PushTransform,(void **) &old_Sexy_MemoryImage_PushTransform);
    VTableHookFunction(vTableForMemoryImageAddr,38, (void *) Sexy_MemoryImage_PopTransform,(void **) &old_Sexy_MemoryImage_PopTransform);


    VTableHookFunction(vTableForMusic2Addr, 7, (void *) Music2_StopAllMusic,(void **) &old_Music2_StopAllMusic);
    VTableHookFunction(vTableForMusic2Addr,8, (void *) Music2_StartGameMusic,(void **) &old_Music2_StartGameMusic);
    VTableHookFunction(vTableForMusic2Addr, 11, (void *) Music2_GameMusicPause,(void **) &old_Music2_GameMusicPause);
//    VTableHookFunction(vTableForMusic2Addr, 12, (void *) Music2_UpdateMusicBurst,(void **) &old_Music2_UpdateMusicBurst);
//    VTableHookFunction(vTableForMusic2Addr, 13, (void *) Music2_StartBurst,(void **) &old_Music2_StartBurst);
    VTableHookFunction(vTableForMusic2Addr,17, (void *) Music2_FadeOut,(void **) &old_Music2_FadeOut);


//    VTableHookFunction(vTableForMaskHelpWidgetAddr, 71, (void *) MaskHelpWidget_KeyDown,NULL);
    VTableHookFunction(vTableForMaskHelpWidgetAddr, 78, (void *) MaskHelpWidget_MouseDown,NULL);
    VTableHookFunction(vTableForMaskHelpWidgetAddr, 81, (void *) MaskHelpWidget_MouseUp,NULL);
    VTableHookFunction(vTableForMaskHelpWidgetAddr, 83, (void *) MaskHelpWidget_MouseDrag,NULL);


    VTableHookFunction(vTableForDaveHelpAddr, 78, (void *) DaveHelp_MouseDown,NULL);
    VTableHookFunction(vTableForDaveHelpAddr, 81, (void *) DaveHelp_MouseUp,NULL);
    VTableHookFunction(vTableForDaveHelpAddr, 83, (void *) DaveHelp_MouseDrag,NULL);
    VTableHookFunction(vTableForDaveHelpAddr, 73, (void *) DaveHelp_KeyDown,NULL);


    VTableHookFunction(vTableForTestMenuWidgetAddr, 33, (void *) TestMenuWidget_Update,NULL);
    VTableHookFunction(vTableForTestMenuWidgetAddr, 38, (void *) TestMenuWidget_Draw,NULL);
    VTableHookFunction(vTableForTestMenuWidgetAddr, 78, (void *) TestMenuWidget_MouseDown,NULL);
    VTableHookFunction(vTableForTestMenuWidgetAddr, 81, (void *) TestMenuWidget_MouseUp,NULL);
    VTableHookFunction(vTableForTestMenuWidgetAddr, 83, (void *) TestMenuWidget_MouseDrag,NULL);
    VTableHookFunction(vTableForTestMenuWidgetAddr, 73, (void *) TestMenuWidget_KeyDown,NULL);


    VTableHookFunction(vTableForTrashBinAddr, 38, (void *) TrashBin_Draw,NULL);

    VTableHookFunction(vTableForConfirmBackToMainDialogAddr, 83, (void *) ConfirmBackToMainDialog_MouseDrag,(void **) &old_ConfirmBackToMainDialog_MouseDrag);

    VTableHookFunction(vTableForSettingsDialogAddr, 153, (void *) SettingsDialog_CheckboxChecked,NULL);

    VTableHookFunction(vTableForCreditScreenAddr, 133, (void *) CreditScreen_ButtonDepress,NULL);

    VTableHookFunction(vTableForMainMenuAddr, 139, (void *) MainMenu_ButtonPress,NULL);

}

void InitOpenSL() {

    MSHookFunction(Native_AudioOutput_setupAddr,(void *) Native_AudioOutput_setup,(void **) &old_Native_AudioOutput_setup);
    MSHookFunction(Native_AudioOutput_shutdownAddr,(void *) Native_AudioOutput_shutdown,(void **) &old_Native_AudioOutput_shutdown);
    //MSHookFunction(Native_AudioOutput_writeAddr,(void *) Native_AudioOutput_write,(void **) &old_Native_AudioOutput_write);
    MSHookFunction(j_AGAudioWriteAddr,(void *) AudioWrite,NULL);
}


void CallHook() {
    InitInGameFunction();
    InitHookFunction();
    InitVTableHookFunction();

}

