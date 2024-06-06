//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_BOARD_H
#define PVZ_TV_1_1_5_BOARD_H

#include "../Enums.h"
//检查加农炮用
Plant* (*Board_GetPlantsOnLawn)(Board* board, unsigned int a2, unsigned int a3, int *a4);

int (*Board_GridToPixelX)(Board *board, unsigned int a2, unsigned int a3);

int (*Board_GridToPixelY)(Board *board, unsigned int a2, unsigned int a3);

int (*Board_PixelToGridX)(Board *board, unsigned int a2, unsigned int a3);

int (*Board_PixelToGridY)(Board *board, unsigned int a2, unsigned int a3);

int (*Board_LoadBackgroundImages)(Board *board);

GridItem* (*Board_AddALadder)(Board *board, int x, int y);

bool Board_MouseHitTest(Board *board, int x, int y, HitResult *hitResult, bool playerIndex);

Plant* (*Board_ToolHitTest)(Board *board, int a2, int a3);

int (*Board_RefreshSeedPacketFromCursor)(Board *board, int a2);

int (*Board_CanUseGameObject)(Board *board, GameObjectType::GameObjectType a2);

int (*Board_NewPlant)(Board *board, int a2, int a3, SeedType::SeedType a4, SeedType::SeedType a5, int a6);

Plant* (*Board_GetTopPlantAt)(Board *board, unsigned int a2, unsigned int a3, TopPlant::TopPlant a4);

int (*Board_ClearCursor)(Board *board, int a2);

void Board_UpdateGridItems(Board *board);

int (*Board_MouseDownWithTool)(Board *board, int a2, int a3, int a4, int a5, int a6);

int (*Board_CountPlantByType)(Board *board, int a2);

int (*Board_SetTutorialState)(Board *board, int a2);

Zombie *(*Board_ZombieHitTest)(Board *board, int a2, int a3, int a4);

int (*Board_HasConveyorBeltSeedBank)(Board *board, int a2);

int (*Board_InitCoverLayer)(Board *board);

int (*Board_GameAxisMove)(Board *board, int buttonCode, int playerIndex, int isLongPress);
// isLongPress的数值为：首次按下为0，后续按下为1
// playerIndex为0或者1，代表玩家1或者2
// buttonCode和GameButton通用
// 上 0
// 下 1
// 左 2
// 右 3


Projectile* (*Board_AddProjectile)(Board*, int, int, int, int, ProjectileType::ProjectileType);

bool (*Board_IterateZombies)(Board *board, Zombie **zombie);

bool (*Board_IterateGridItems)(Board* board, GridItem **gridItem);

bool (*Board_IteratePlants)(Board* board,  Plant **plant);

bool (*Board_IterateProjectiles)(Board *board, Projectile **projectile);

bool (*Board_IterateCoins)(Board *board,  Coin **coin);

bool (*Board_IterateLawnMowers)(Board *board,  int **lawnMower);

bool (*Board_IterateParticles)(Board*,TodParticleSystem**);

bool (*Board_IsSurvivalStageWithRepick)(Board *board);

void (*Board_PickUpTool)(Board *board, GameObjectType::GameObjectType a2, int a3);

bool (*Board_ProgressMeterHasFlags)(Board *board);

//整体移动整个草坪，包括种子栏和铲子按钮等等。
void (*Board_Move)(Board *board, int newX, int newY);

void (*Board_DoFwoosh)(Board* board, int mRow);

void (*Board_ShakeBoard)(Board* board, int, int);

void (*Board_GetButterButtonRect)(TRect*,Board*);

void Board_GetShovelButtonRect(TRect*,Board*);

//void (*Board_DrawZenButtons)(Board*,int*);

Zombie *(*Board_ZombieTryToGet)(Board*,Zombie*);

void Board_ZombiesWon(Board *board, Zombie *zombie);

Zombie* Board_AddZombieInRow(Board *board, ZombieType::ZombieType theZombieType, int theRow, int theFromWave,bool playAnim);

static int (*Board_MakeRenderOrder)(int,int,int);

bool (*Board_PlantUsesAcceleratedPricing)(Board* board,SeedType::SeedType seedType);

bool(*Board_CanInteractWithBoardButtons)(Board*board);

bool(*Board_IsPlantInCursor)(Board*board);

void(*Board_MouseDownWithPlant)(Board*,int,int,int);

void (*Board_RemoveAllPlants)(Board*);

int (*Board_GetSeedBankExtraWidth)(Board*);

int (*Board_GetSeedPacketPositionX)(Board*,int,int,bool);

Coin* (*Board_AddCoin)(Board*,int,int,int,int);

bool (*Board_CanTakeSunMoney)(Board*,int,int);

GridItem* (*Board_GetGridItemAt)(Board*,GridItemType::GridItemType,int,int);

void (*Board_GetZenButtonRect)(TRect*,Board*,GameObjectType::GameObjectType);

GridItem*(*Board_GetLadderAt)(Board*,int,int);

int (*Board_PixelToGridXKeepOnBoard)(Board*,int,int);

int (*Board_PixelToGridYKeepOnBoard)(Board*,int,int);

bool TRect_Contains(TRect *rect, int x, int y);

void Board_MouseDownSecond(Board *board, int x, int y, int theClickCount);

void Board_MouseDragSecond(Board *board, int x, int y);

void Board_MouseUpSecond(Board *board, int x, int y, int theClickCount);

void Board_LoadFormation(Board* board,const char *formation);

PlantingReason::PlantingReason Board_CanPlantAt(Board* , int a2, int a3, SeedType::SeedType a4);

bool (*Board_IsValidCobCannonSpotHelper)(Board*,int,int);

//int* (*Board_GetFlowerPotAt)(Board*,int,int);

int (*Board_PickRowForNewZombie)(Board*,int);

bool (*Board_IsPoolSquare)(Board*,int,int);

static void (*Board_ZombiePickerInit)(ZombiePicker*);

ZombieType::ZombieType (*Board_GetIntroducedZombieType)(Board*);

void (*Board_ZombiePickerInitForWave)(ZombiePicker*);

void (*Board_PutZombieInWave)(Board*,ZombieType::ZombieType,int,ZombiePicker*);

ZombieType::ZombieType (*Board_PickZombieType)(Board*,int,int,ZombiePicker*);

bool (*Board_HasLevelAwardDropped)(Board*);

void (*Board_SpawnZombiesFromGraves)(Board*);

void (*Board_ClearAdvice)(Board*,int);

void (*Board_NextWaveComing)(Board*);

int (*Board_TotalZombiesHealthInWave)(Board*,int);

void (*Board_ClearAdviceImmediately)(Board*);

void (*Board_DisplayAdviceAgain)(Board*,int*,MessageStyle::MessageStyle,AdviceType::AdviceType);

int (*Board_GridCellWidth)(Board*,int,int);

int (*Board_GridCellHeight)(Board*,int,int);

Plant* Board_GetPumpkinAt(Board*,int,int);

SeedType::SeedType (*Board_GetSeedTypeInCursor)(Board*,int);

int (*Board_KillAllZombiesInRadius)(Board*,int,int,int,int,int,bool,int);

bool Board_GrantAchievement(Board* board,AchievementId::AchievementId theAchievementId, bool show);

void Board_DoPlantingAchievementCheck(Board* board, SeedType::SeedType theType);

int Board_GetLiveZombiesCount(Board *board);

char* GetNameByAchievementId(AchievementId::AchievementId theAchievementId);

Sexy::Image* GetIconByAchievementId(AchievementId::AchievementId theAchievementId);

void Board_ShovelDown(Board*);

void (*Board_TryToSaveGame)(Board *board);

bool Board_ZenGardenItemNumIsZero(Board*,CursorType::CursorType);

bool Board_StageHas6Rows(Board*);

Plant *Board_AddPlant(Board *board, int x, int y, SeedType::SeedType seedType, SeedType::SeedType theImitaterType, int playerIndex , bool doPlantEffect);

int Board_GetCurrentPlantCost(Board* board, SeedType::SeedType a2, SeedType::SeedType a3);
void Board_SetGrids(Board *board);
void (*old_Board_UpdateGame)(Board *board);
void Board_UpdateGame(Board *board);
void (*old_Board_UpdateGameObjects)(Board* board);
void Board_UpdateGameObjects(Board* board);
void (*old_Board_DrawDebugText)(Board *board, Sexy::Graphics *graphics);
void Board_DrawDebugText(Board *board, Sexy::Graphics *graphics);
void (*old_Board_DrawDebugObjectRects)(Board *board,  Sexy::Graphics *graphics);
void Board_DrawDebugObjectRects(Board *board, Sexy::Graphics *graphics);
void Board_DrawFadeOut(Board *board, Sexy::Graphics *graphics);
int (*old_Board_GetCurrentPlantCost)(Board* board, SeedType::SeedType a2, SeedType::SeedType a3);
int Board_GetCurrentPlantCost(Board* board, SeedType::SeedType a2, SeedType::SeedType a3) ;
void Board_AddSunMoney(Board* board, int theAmount, int playerIndex);
void Board_AddDeathMoney(Board *board, int theAmount);
PlantingReason::PlantingReason (*old_Board_CanPlantAt)(Board* board, int theGridX, int theGridY, SeedType::SeedType seedType);
PlantingReason::PlantingReason Board_CanPlantAt(Board* board, int theGridX, int theGridY, SeedType::SeedType seedType) ;
bool (*old_Board_PlantingRequirementsMet)(Board *board, int a2);
bool Board_PlantingRequirementsMet(Board *board, int a2);
void (*old_BoardZombiesWon)(Board *board, Zombie *zombie);
void Board_ZombiesWon(Board *board, Zombie *zombie);
Plant *(*old_Board_AddPlant)(Board *board, int x, int y, SeedType::SeedType seedType,
                             SeedType::SeedType theImitaterType,int playerIndex,bool doPlantEffect);
Plant *Board_AddPlant(Board *board, int x, int y, SeedType::SeedType seedType, SeedType::SeedType theImitaterType, int playerIndex , bool doPlantEffect) ;
void Board_parseFormationSegment(Board* board, char *segment);
void Board_LoadFormation(Board* board,char *formation);
//Board
int theBuildLadderX = 0;
int theBuildPlantX = 0;
int BuildZombieX = 0;
int theBuildLadderY = 0;
int theBuildPlantY = 0;
int BuildZombieY = 0;
bool ladderBuild;
bool graveBuild;
bool plantBuild;
bool zombieBuild;
SeedType::SeedType theBuildPlantType = SeedType::None;
ZombieType::ZombieType theBuildZombieType = ZombieType::Invalid;
bool isImitaterPlant;
int theBuildZombieCount = 1;
int theZombieBuildRow = 0;
int theZombieBuildi = 0;
bool uniformBuildZombie;
int theUniformZombieBuildRow = 0;
bool passNowLevel;
void (*old_Board_DrawZenButtons)(Board *board, Sexy::Graphics *a2);
void Board_DrawZenButtons(Board *board, Sexy::Graphics *a2);
bool (*old_Board_KeyUp)(Board *board, int keyCode);
bool Board_KeyUp(Board *board, int keyCode);
void (*old_Board_KeyDown)(Board *board, int keyCode);
void Board_KeyDown(Board *board, int keyCode);
void (*old_Board_UpdateSunSpawning)(Board *board);
void Board_UpdateSunSpawning(Board *board);
void (*old_Board_UpdateZombieSpawning)(Board *board);
void Board_UpdateZombieSpawning(Board *board);
void (*old_Board_UpdateIce)(Board *board);
void Board_UpdateIce(Board *board);
void Board_DrawCoverLayer(Board *board, Sexy::Graphics *graphics, int theRow);
void (*old_Board_PickBackground)(Board *board);
void Board_PickBackground(Board *board);
bool Board_StageIsNight(Board *board);
bool (*old_Board_StageHasPool)(Board *board);
bool Board_StageHasPool(Board *board);
bool Board_StageHas6Rows(Board *board);
void (*old_Board_UpdateFwoosh)(Board *board);
void Board_UpdateFwoosh(Board *board);
void (*old_Board_UpdateFog)(Board *board);
void Board_UpdateFog(Board *board);
void (*old_Board_DrawFog)(Board *board, Sexy::Graphics* g);
void Board_DrawFog(Board *board, Sexy::Graphics* g);
Zombie* (*old_Board_AddZombieInRow)(Board *board, ZombieType::ZombieType theZombieType, int theRow, int theFromWave,
                                    bool playAnim);
Zombie* Board_AddZombieInRow(Board *board, ZombieType::ZombieType theZombieType, int theRow, int theFromWave, bool playAnim) ;
void Board_SpeedUpUpdate(Board *board);

std::string customFormation = "";
int formationId = -1;
bool ClearAllPlant;
bool clearAllZombies;
bool hypnoAllZombies;
bool freezeAllZombies;
bool clearAllGraves;
bool clearAllMowers;
bool recoverAllMowers;
bool startAllMowers;
bool banMower;
bool layChoseFormation;
bool layPastedFormation;

bool noFog;
bool checkZombiesAllowed[ZombieType::ZombieTypesCount] = {false}; // 僵尸选中情况
int choiceSpawnMode = 0; // 刷怪模式
bool buttonSetSpawn;     // 设置出怪

int targetSeedBank = 1;
int choiceSeedPacketIndex = 0;
SeedType::SeedType choiceSeedType = SeedType::None;
bool isImitaterSeed;
bool setSeedPacket;


TRect mTouchVSShovelRect = {0,85,56,56};

void (*old_Board_Update)(Board *board);
void Board_Update(Board *board);
int Board_GetNumWavesPerFlag(Board *board);
bool (*old_Board_IsFlagWave)(Board *board, int currentWave);
bool Board_IsFlagWave(Board *board, int currentWave);
void (*old_Board_SpawnZombieWave)(Board *board);
void Board_SpawnZombieWave(Board *board);
void (*old_Board_DrawProgressMeter)(Board *board, Sexy::Graphics *graphics, int a3, int a4);
void Board_DrawProgressMeter(Board *board, Sexy::Graphics *graphics, int a3, int a4) ;
bool (*old_Board_IsLevelDataLoaded)(Board *board);
bool Board_IsLevelDataLoaded(Board *board);
bool (*old_Board_NeedSaveGame)(Board *board);
bool Board_NeedSaveGame(Board *board);
void (*old_Board_DrawBackdrop)(Board *board, Sexy::Graphics *graphics);
void Board_DrawBackdrop(Board *board, Sexy::Graphics *graphics);
void Board_DrawHammerButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) ;
void Board_DrawButterButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) ;
void Board_DrawShovelButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) ;
void Board_DrawStartButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp);
void Board_DrawShovel(Board *board, Sexy::Graphics *graphics);
void (*old_Board_Pause)(Board* board, bool a2);
void Board_Pause(Board* board, bool a2);
void Board_AddSecondPlayer(Board *board, int a2);
bool Board_IsLastStandFinalStage(Board *board);
Plant *Board_GetFlowerPotAt(Board *board, int theGridX, int theGridY);
void Board_DoPlantingEffects(Board *board, int theGridX, int theGridY, Plant *plant);
void (*old_Board_InitLawnMowers)(Board* board);
void Board_InitLawnMowers(Board *board);
void (*old_Board_PickZombieWaves)(Board *board);
#define MAX_ZOMBIES_IN_WAVE 50
void Board_PickZombieWaves(Board *board);
int Board_GetLiveGargantuarCount(Board *board);
void (*old_Board_RemovedFromManager)(Board *board, int *manager);
void Board_RemovedFromManager(Board *board, int *manager);
void (*old_Board_InitLevel)(Board *board);
void Board_InitLevel(Board *board);
void (*old_Board_ButtonDepress)(Board *board, int id);
void Board_ButtonDepress(Board *board, int id);
void (*old_Board_Board)(Board* board,LawnApp* mApp);
void Board_Board(Board* board,LawnApp* mApp);
void (*old_Board_MouseUp)(Board *board, int a2, int a3, int a4);
void Board_MouseUp(Board *board, int x, int y, int theClickCount);
void (*old_Board_MouseDrag)(Board *board, int x, int y);
void Board_MouseDrag(Board *board, int x, int y);
void (*old_Board_MouseDown)(Board *board, int x, int y, int theClickCount);
void Board_MouseDown(Board *board, int x, int y, int theClickCount);
void (*old_Board_MouseMove)(Board *board, int x, int y);
void Board_MouseMove(Board *board, int x, int y);
bool (*old_Board_MouseHitTest)(Board *board, int x, int y, HitResult* hitResult, bool posScaled);
void (*old_Board_FadeOutLevel)(Board *board);
void Board_FadeOutLevel(Board *board);
void (*Board_RemoveCutsceneZombies)(Board*);
int(*Board_CountZombiesOnScreen)(Board*);
void Board_UpdateButtons(Board* board);
float (*Board_GetPosYBasedOnRow)(Board* board,float,int);
bool  (*Board_CanTakeDeathMoney)(Board *, int );
Zombie* (*Board_GetBossZombie)(Board*);
void (*Board_RemoveAllMowers)(Board*);
void (*Board_ResetLawnMowers)(Board* board);
void (*Board_RemoveAllZombies)(Board*);
GamepadControls *(*Board_GetGamepadControlsByPlayerIndex)(Board*,int);





#endif //PVZ_TV_1_1_5_BOARD_H
