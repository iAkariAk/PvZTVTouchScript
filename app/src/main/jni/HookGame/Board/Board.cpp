//
// Created by Administrator on 2023/10/22.
//

#ifndef PVZ_TV_1_1_5_BOARD_CPP
#define PVZ_TV_1_1_5_BOARD_CPP

#include "../GlobalVariable.h"
#include "Board.h"
#include "../Plant/Plant.h"
#include "../Music/Music.h"
#include "HookGame/SeedBank/SeedBank.cpp"
#include "../Graphics/Graphics.h"
#include "../GridItem/GridItem.h"
#include "../Zombie/Zombie.h"
#include "../Coin/Coin.h"
#include "HookGame/Coin/Coin.cpp"
#include "../Challenge/Challenge.h"
#include "../Projectile/Projectile.h"
#include "../Reanimation/Reanimation.h"
#include "../LawnApp/LawnApp.h"
#include "../GamepadControls/GamepadControls.h"
#include "HookGame/GamepadControls/GamepadControls.cpp"
#include "../SeedChooserScreen/SeedChooserScreen.h"
#include "../SeedPacket/SeedPacket.h"
#include "../Formation.h"
#include <cstddef>
#include <cstdio>
#include "HookGame/HookAddr.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void Board_SetGrids(Board *board) {
    //更换场地时需要，用于初始化每一个格子的类型。
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (board->mPlantRow[j] == PlantRowType::Dirt)
            {
                board->mGridSquareType[i][j] = GridSquareType::Dirt;
            }
            else if (board->mPlantRow[j] == PlantRowType::Pool && i >= 0 && i <= 8)
            {
                board->mGridSquareType[i][j] = GridSquareType::Pool;
            }
            else if (board->mPlantRow[j] == PlantRowType::HighGround && i >= 4 && i <= 8)
            {
                board->mGridSquareType[i][j] = GridSquareType::HighGround;
            }
        }
    }
}

void Board_ShovelDown(Board *board) {
    // 用于铲掉光标正下方的植物。
    requestDrawShovelInCursor = false;
    LawnApp *lawnApp = board->mApp;
    bool isInShovelTutorial = (unsigned int) (board->mTutorialState - 15) <= 2;
    if (isInShovelTutorial) {
        //如果正在铲子教学中(即冒险1-5的保龄球的开场前，戴夫要求你铲掉三个豌豆的这段时间),则发送铲除键来铲除。
        GamepadControls_OnKeyDown(board->mGamepadControls1, 49, 1112);
        Board_ClearCursor(board, 0);
        Board_RefreshSeedPacketFromCursor(board, 0);
        return;
    }
    // 下方就是自己写的铲除逻辑喽。
    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    float mGamePadX = gamepadControls1->mCursorPositionX;
    float mGamePadY = gamepadControls1->mCursorPositionY;
    Plant* plantUnderShovel = Board_ToolHitTest(board,mGamePadX , mGamePadY);
    if (plantUnderShovel != NULL) {
        LawnApp_PlayFoley(lawnApp, FoleyType::UseShovel); // 播放铲除音效
        Plant_Die(plantUnderShovel);// 让被铲的植物趋势
        SeedType::SeedType plantType = plantUnderShovel->mSeedType;
        int mPlantCol = plantUnderShovel->mPlantCol;
        int mRow = plantUnderShovel->mRow;
        if (plantType == SeedType::Cattail && Board_GetTopPlantAt(board, mPlantCol, mRow, TopPlant::OnlyPumpkin) != NULL) {
            // 如果铲的是南瓜套内的猫尾草,则再在原地种植一个荷叶
            Board_NewPlant(board, mPlantCol, mRow, SeedType::Lilypad, SeedType::None, -1);
        }
        if (lawnApp->mGameMode == GameMode::ChallengeLastStand) {
            Challenge *challenge = board->mChallenge;
            if (challenge->mChallengeState == ChallengeState::Normal && lawnApp->mGameScene == GameScenes::Playing) {
                int theCost = Plant_GetCost(plantType, plantUnderShovel->mImitaterType);
                int num = theCost / 25;
                if (plantType == SeedType::Garlic || plantType == SeedType::Wallnut ||
                    plantType == SeedType::Tallnut || plantType == SeedType::Pumpkinshell) {
                    int mPlantHealth =plantUnderShovel->mPlantHealth;
                    int mPlantMaxHealth = plantUnderShovel->mPlantMaxHealth;
                    num = (mPlantHealth * 3 > mPlantMaxHealth * 2) ? num : 0;
                }
                for (int i = 0; i < num; i++) {
                    Coin *coin = Board_AddCoin(board, mGamePadX, mGamePadY, 4, 2);
                    Coin_Collect(coin, 0);
                }
            }
        }
    }
    Board_ClearCursor(board, 0);
    Board_RefreshSeedPacketFromCursor(board, 0);
}

void Board_UpdateGame(Board *board) {
    if (requestPause) {
        board->mMainCounter--;
        if (board->mIceTrapCounter > 0) {
            board->mIceTrapCounter++;
        }
        if (board->mFogBlownCountDown > 0) {
            board->mFogBlownCountDown++;
            board->mFogBlownCountDown++;
        }
    }


    old_Board_UpdateGame(board);

    // 防止选卡界面浓雾遮挡僵尸
    if (board->mFogBlownCountDown > 0 && board->mApp->mGameScene == GameScenes::LevelIntro) {
        float thePositionStart = 1065.0 - 4 * 80.0 + 100; // 1065f - LeftFogColumn() * 80f + Constants.BOARD_EXTRA_ROOM;
        board->mFogOffset = TodAnimateCurveFloat(200, 0, board->mFogBlownCountDown, thePositionStart, 0.0, TodCurves::EaseOut);
    }

}
void Board_UpdateGameObjects(Board* board) {
    //修复过关后游戏卡住不动
    if (board->mBoardFadeOutCounter > 0) {
        //如果已经过关，则手动刷新植物，僵尸，子弹
        int* tmp = NULL;
        while (Board_IteratePlants(board, (Plant**)&tmp)) {
            Plant_Update((Plant*)tmp);
        }
        tmp = NULL;
        while (Board_IterateZombies(board, (Zombie**)&tmp)) {
            Zombie_Update((Zombie*)tmp);
        }
        tmp = NULL;
        while (Board_IterateProjectiles(board, (Projectile**)&tmp)) {
            Projectile_Update((Projectile*)tmp);
        }
    }
    old_Board_UpdateGameObjects(board);
}

bool drawDebugText = false;


void Board_DrawDebugText(Board *board, Sexy::Graphics *graphics) {
    //出僵DEBUG功能
    if (drawDebugText) {
        DebugTextMode::DebugTextMode tmp = board->mDebugTextMode;
        board->mDebugTextMode = DebugTextMode::ZombieSpawn;
        old_Board_DrawDebugText(board, graphics);
        board->mDebugTextMode = tmp;
        return;
    }
    old_Board_DrawDebugText(board, graphics);
}

bool drawDebugRects = false;



void Board_DrawDebugObjectRects(Board *board, Sexy::Graphics *graphics) {
    //碰撞体积绘制
    if (drawDebugRects) {
        DebugTextMode::DebugTextMode tmp = board->mDebugTextMode;
        board->mDebugTextMode = DebugTextMode::Collision;
        old_Board_DrawDebugObjectRects(board, graphics);
        board->mDebugTextMode = tmp;
        return;
    }
    old_Board_DrawDebugObjectRects(board, graphics);
}


void Board_DrawFadeOut(Board *board, Sexy::Graphics *graphics) {
    //修复关卡完成后的白色遮罩无法遮住整个屏幕
    int mBoardFadeOutCounter = board->mBoardFadeOutCounter;
    if (mBoardFadeOutCounter < 0) {
        return;
    }
    if (Board_IsSurvivalStageWithRepick(board)) {
        return;
    }
    int theAlpha = TodAnimateCurve(200, 0, mBoardFadeOutCounter, 0, 255,TodCurves::Linear);
    int mLevel = board->mLevel;
    if (mLevel == 9 || mLevel == 19 || mLevel == 29 || mLevel == 39 || mLevel == 49) {
        Color theColor = {0, 0, 0, theAlpha};
        Sexy_Graphics_SetColor(graphics, &theColor);
    } else {
        Color theColor = {255, 255, 255, theAlpha};
        Sexy_Graphics_SetColor(graphics, &theColor);
    }
    Sexy_Graphics_SetColorizeImages(graphics, true);
    TRect fullScreenRect = {-240, -60, 1280, 720};
    //修复BUG的核心原理，就是不要在此处PushState和PopState，而是直接FillRect。这将保留graphics的trans属性。
    Sexy_Graphics_FillRect(graphics, &fullScreenRect);
}

bool infiniteSun;//无限阳光


int Board_GetCurrentPlantCost(Board* board, SeedType::SeedType a2, SeedType::SeedType a3) {
    //无限阳光
    if (infiniteSun) return 0;
    return old_Board_GetCurrentPlantCost(board, a2, a3);
}

void (*old_Board_AddSunMoney)(Board* board, int theAmount, int playerIndex);

void Board_AddSunMoney(Board* board, int theAmount, int playerIndex) {
    //无限阳光
    if (infiniteSun) {
        if (playerIndex == 0) {
            board->mSunMoney1 = 9990;
        } else {
            board->mSunMoney2 = 9990;
        }
    } else {
        old_Board_AddSunMoney(board,theAmount,playerIndex);
    }
}

void (*old_Board_AddDeathMoney)(Board *board, int theAmount);

void Board_AddDeathMoney(Board *board, int theAmount) {
    //无限阳光
    if (infiniteSun) {
        board->mDeathMoney = 9990;
    } else {
        old_Board_AddDeathMoney(board, theAmount);
    }
}

bool FreePlantAt = false;


PlantingReason::PlantingReason Board_CanPlantAt(Board* board, int theGridX, int theGridY, SeedType::SeedType seedType) {
    //自由种植！
    if (FreePlantAt) {
        return PlantingReason::Ok;
    }
    return old_Board_CanPlantAt(board, theGridX, theGridY, seedType);
}



bool Board_PlantingRequirementsMet(Board *board, int a2) {
    //紫卡直接种植！
    if (FreePlantAt) {
        return 1;
    }
    return old_Board_PlantingRequirementsMet(board, a2);
}

bool ZombieCanNotWon = false;



void Board_ZombiesWon(Board *board, Zombie *zombie) {
    if (zombie == NULL) {//如果是IZ或者僵尸水族馆，第二个参数是NULL，此时就返回原函数。否则闪退
        return old_BoardZombiesWon(board, zombie);
    }
    if (ZombieCanNotWon) {
        Zombie_ApplyBurn(zombie);
        Zombie_DieNoLoot(zombie);
        return;
    }
    return old_BoardZombiesWon(board, zombie);
}

//Board_AddPlant
bool PumpkinWithLadder = false;


Plant *Board_AddPlant(Board *board, int x, int y, SeedType::SeedType seedType, SeedType::SeedType theImitaterType, int playerIndex , bool doPlantEffect) {
    if (PumpkinWithLadder && seedType == SeedType::Pumpkinshell) {
        Board_AddALadder(board, x, y);
    }
    // 检查成就！
    Board_DoPlantingAchievementCheck(board, seedType);
    return old_Board_AddPlant(board, x, y, seedType, theImitaterType, playerIndex, doPlantEffect);
}

//布阵用
void Board_parseFormationSegment(Board* board, char *segment) {

    SeedType::SeedType seedType = SeedType::Peashooter;
    bool isIZombieLevel = LawnApp_IsIZombieLevel(board->mApp);
    bool wakeUp = false;
    bool imitaterMorphed = false;
    bool addLadder = false;
    int damageState = 0;
    int offset = 0;

    if (sscanf(segment, "%d%n", &seedType, &offset) != 1) {
        return; // Failed to parse
    }

    // Move cursor to the next position after the parsed integer
    const char *cursor = segment + offset;
    while (*cursor != '\0') {
        if (*cursor == 'W') {
            wakeUp = true;
        } else if (*cursor == 'I') {
            imitaterMorphed = true;
        } else if (*cursor == 'L') {
            addLadder = true;
        }else if (*cursor == 'D') {
            damageState++;
            if (damageState > 2) {
                damageState = 2;
            }
        } else if (*cursor >= '0' && *cursor <= '9') {
            // Parse coordinates
            int x = 0, y = 0;
            if (!sscanf(cursor, "%d,%d", &x, &y)) {
                continue;
            }
            Plant *plant = old_Board_AddPlant(board, x, y, seedType, imitaterMorphed ? SeedType::Imitater : SeedType::None, 1,false);
            if (imitaterMorphed) {
                Plant_SetImitaterFilterEffect(plant);
            }
            if (wakeUp) {
                Plant_SetSleeping(plant, false);
            }
            if (addLadder && Board_GetLadderAt(board,x,y) == NULL) {
                Board_AddALadder(board, x, y);
            }
            if (damageState > 0) {
                plant->mPlantHealth = (plant->mPlantMaxHealth * (3 - damageState) / 3) - 1;
            }
            if (isIZombieLevel) {
                Challenge_IZombieSetupPlant(board->mChallenge,plant);
            }
            // Skip to next coordinate
            while (*cursor != ' ' && *cursor != '\0') {
                cursor++;
            }
            continue;
        }
        cursor++;
    }

}

//布阵用
void Board_LoadFormation(Board* board,char *formation) {
    Board_RemoveAllPlants(board);
    const char *segmentDelimiters = ";";
    char *segment = strtok(formation, segmentDelimiters);
    while (segment != NULL) {
        Board_parseFormationSegment(board, segment);
        segment = strtok(NULL, segmentDelimiters);
    }
}




bool Board_ZenGardenItemNumIsZero(Board *board, CursorType::CursorType cursorType) {
    //消耗性工具的数量是否为0个
    LawnApp * lawnApp = board->mApp;
    switch (cursorType) {
        case CursorType::Fertilizer:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_FERTILIZER] <= 1000;
        case CursorType::BugSpray:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_BUG_SPRAY] <= 1000;
        case CursorType::Chocolate:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_CHOCOLATE] <= 1000;
        case CursorType::TreeFood:
            return lawnApp->mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_TREE_FOOD] <= 1000;
    }
    return false;
}


void Board_DrawZenButtons(Board *board, Sexy::Graphics *a2) {

    return old_Board_DrawZenButtons(board, a2);
}



bool Board_KeyUp(Board *board, int keyCode) {
    return old_Board_KeyUp(board,keyCode);
}



void Board_KeyDown(Board *board, int keyCode) {
    //用于切换键盘模式，自动开关砸罐子老虎机种子雨关卡内的"自动拾取植物卡片"功能
    if (keyCode >= 37 && keyCode <= 40) {
        if (!keyboardMode) {
            GamePatches.UsefulSeedPacketAutoPickupDisable.Restore();
        }
        keyboardMode = true;
        requestDrawShovelInCursor = false;
    }
    return old_Board_KeyDown(board, keyCode);
}

void Board_UpdateSunSpawning(Board *board) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    if (board->mApp->mGameMode == GameMode::ChallengeButteredPopcorn) {
        return;
    }
    return old_Board_UpdateSunSpawning(board);
}

void Board_UpdateZombieSpawning(Board *board) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }

    // 在黄油爆米花关卡改变出怪倒计时。
    if (board->mApp->mGameMode == GameMode::ChallengeButteredPopcorn) {
        int mZombieCountDown = board->mZombieCountDown;
        if (mZombieCountDown >= 2500 && mZombieCountDown <= 3100) {
            board->mZombieCountDown = 750;
            board->mZombieCountDownStart = board->mZombieCountDown;
        }
    }
//    int *lawnApp = (int *) board[69];
//    GameMode::GameMode mGameMode = (GameMode::GameMode)*(lawnApp + LAWNAPP_GAMEMODE_OFFSET);
//    if(mGameMode == GameMode::ChallengeButteredPopcorn){
//        int mFinalWaveSoundCounter = board[5660];
//        if (mFinalWaveSoundCounter > 0) {
//            mFinalWaveSoundCounter--;
//            board[5660] = mFinalWaveSoundCounter;
//            if (mFinalWaveSoundCounter == 0) {
//                LawnApp_PlaySample(lawnApp,Sexy_SOUND_FINALWAVE_Addr);
//            }
//        }
//        if (Board_HasLevelAwardDropped(board)) {
//            return;
//        }
//
//        int mRiseFromGraveCounter = board[5540];
//        if (mRiseFromGraveCounter > 0) {
//            mRiseFromGraveCounter--;
//            board[5540] = mRiseFromGraveCounter;
//            if (mRiseFromGraveCounter == 0) {
//                Board_SpawnZombiesFromGraves(board);
//            }
//        }
//
//        int mHugeWaveCountDown = board[5552];
//        if (mHugeWaveCountDown > 0) {
//            mHugeWaveCountDown--;
//            board[5552] = mHugeWaveCountDown;
//            if (mHugeWaveCountDown == 0) {
//                Board_ClearAdvice(board, 42);
//                Board_NextWaveComing(board);
//                board[5550] = 1; //  mZombieCountDown = 1;
//            }else if(mHugeWaveCountDown == 725){
//                LawnApp_PlaySample(lawnApp,Sexy_SOUND_FINALWAVE_Addr);
//            }
//        }
//
//        int mZombieCountDown = board[5550];
//        mZombieCountDown--; //  mZombieCountDown--;
//        board[5550] = mZombieCountDown;
//
//        int mZombieCountDownStart = board[5551];
//        int mCurrentWave = board[5542];
//        int mZombieHealthToNextWave = board[5548];
//        int num2 = mZombieCountDownStart - mZombieCountDown;
//        if (mZombieCountDown > 5 && num2 > 400) {
//            int num3 = Board_TotalZombiesHealthInWave(board, mCurrentWave - 1);
//            if (num3 <= mZombieHealthToNextWave && mZombieCountDown > 200) {
//                board[5550] = 200;//  mZombieCountDown = 200;
//            }
//        }
//
//        if (mZombieCountDown == 5) {
//            if (Board_IsFlagWave(board, mCurrentWave)) {
//                Board_ClearAdviceImmediately(board);
//                int holder[1];
//                Sexy_StrFormat(holder,"[ADVICE_HUGE_WAVE]");
//                Board_DisplayAdviceAgain(board, holder, 15, 42);
//                Sexy_String_Delete(holder);
//                mHugeWaveCountDown = 750;
//                return;
//            }
//            Board_NextWaveComing(board);
//        }
//
//        if (mZombieCountDown != 0) {
//            return;
//        }
//        Board_SpawnZombieWave(board);
//        board[5549] = Board_TotalZombiesHealthInWave(board, mCurrentWave -1);
//        //mZombieHealthWaveStart = Board_TotalZombiesHealthInWave(board,mCurrentWave - 1);
//        if (Board_IsFlagWave(board, mCurrentWave)) {
//            board[5548] = 0;//  mZombieHealthToNextWave = 0;
//            board[5550] = 0;//  mZombieCountDown = 4500;
//        } else {
//            board[5548] = (int) (RandRangeFloat(0.5f, 0.65f) * board[5549]);
//            board[5550] = 750;//   mZombieCountDown = 750;
//        }
//        board[5551] = mZombieCountDown;
//        return;
//    }
    return old_Board_UpdateZombieSpawning(board);
}



void Board_UpdateIce(Board *board) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    return old_Board_UpdateIce(board);
}

bool hideCoverLayer = false;

void Board_DrawCoverLayer(Board *board, Sexy::Graphics *graphics, int theRow) {
    BackgroundType::BackgroundType mBackgroundType = board->mBackgroundType;
    if (mBackgroundType < BackgroundType::Num1Day || hideCoverLayer) {
        //如果背景非法，或玩家“隐藏草丛和电线杆”，则终止绘制函数
        return;
    }
    LawnApp *lawnApp = board->mApp;
    if (mBackgroundType <= BackgroundType::Num4Fog) {
        //如果是前院(0 1)或者泳池(2 3)，则绘制草丛。整个草丛都是动画而非贴图，没有僵尸来的时候草丛会保持在动画第一帧。
        Reanimation *reanimation = LawnApp_ReanimationTryToGet(lawnApp, board->mCoverLayerAnimIDs[theRow]);
        if (reanimation != NULL) {
            Reanimation_Draw(reanimation, graphics);
        }
    }
    if (theRow == 6) {
        //绘制栏杆和电线杆
        switch (mBackgroundType) {
            case BackgroundType::Num1Day://前院白天
                if (lawnApp->mGameMode == GameMode::ChallengeHeavyWeapon) {
                    //在重型武器关卡中不绘制栏杆。
                    return;
                }
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND1_COVER_Addr, 684,
                                        557);
                break;
            case BackgroundType::Num2Night://前院夜晚
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND2_COVER_Addr, 684,
                                        557);
                break;
            case BackgroundType::Num3Pool://泳池白天
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND3_COVER_Addr, 671,
                                        613);
                break;
            case BackgroundType::Num4Fog://泳池夜晚
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BACKGROUND4_COVER_Addr, 672,
                                        613);
                break;
            case BackgroundType::Num5Roof://屋顶白天
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ROOF_TREE_Addr,
                                        board->mOffsetMoved * 1.5f + 628, -60);
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ROOF_POLE_Addr,
                                        board->mOffsetMoved * 2.0f + 628, -60);
                break;
            case BackgroundType::Num6Boss:
                //可在此处添加代码绘制月夜电线杆喔
//                if(LawnApp_IsFinalBossLevel(lawnApp))  return;

                Sexy_Graphics_DrawImage(graphics, Addon_Images.trees_night,
                                        board->mOffsetMoved * 1.5f + 628, -60);
                Sexy_Graphics_DrawImage(graphics, Addon_Images.pole_night,
                                       board->mOffsetMoved * 2.0f + 628, -60);
                break;
            default:
                return;
        }
    }
}



void Board_PickBackground(Board *board) {
    //用于控制关卡的场地选取。可选择以下场地：前院白天/夜晚，泳池白天/夜晚，屋顶白天/夜晚
    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::ChallengeButteredPopcorn) {
        board->mBackgroundType = BackgroundType::Num3Pool;
        Board_LoadBackgroundImages(board);
        board->mPlantRow[0] = PlantRowType::Normal;
        board->mPlantRow[1] = PlantRowType::Normal;
        board->mPlantRow[2] = PlantRowType::Pool;
        board->mPlantRow[3] = PlantRowType::Pool;
        board->mPlantRow[4] = PlantRowType::Normal;
        board->mPlantRow[5] = PlantRowType::Normal;
        Board_InitCoverLayer(board);
        Board_SetGrids(board);
    } else if (lawnApp->mGameMode == GameMode::ChallengePoolParty) {
        board->mBackgroundType = BackgroundType::Num3Pool;
        Board_LoadBackgroundImages(board);
        board->mPlantRow[0] = PlantRowType::Pool;
        board->mPlantRow[1] = PlantRowType::Pool;
        board->mPlantRow[2] = PlantRowType::Pool;
        board->mPlantRow[3] = PlantRowType::Pool;
        board->mPlantRow[4] = PlantRowType::Pool;
        board->mPlantRow[5] = PlantRowType::Normal;
        Board_InitCoverLayer(board);
        Board_SetGrids(board);
    } else {
        switch (VSBackGround) {
            case 1:
                board->mBackgroundType = BackgroundType::Num1Day;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Normal;
                board->mPlantRow[3] = PlantRowType::Normal;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Dirt;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 2:
                board->mBackgroundType = BackgroundType::Num2Night;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Normal;
                board->mPlantRow[3] = PlantRowType::Normal;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Dirt;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 3:
                board->mBackgroundType = BackgroundType::Num3Pool;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Pool;
                board->mPlantRow[3] = PlantRowType::Pool;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Normal;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 4:
                board->mBackgroundType = BackgroundType::Num4Fog;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Pool;
                board->mPlantRow[3] = PlantRowType::Pool;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Normal;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 5:
                board->mBackgroundType = BackgroundType::Num5Roof;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Normal;
                board->mPlantRow[3] = PlantRowType::Normal;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Dirt;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
                    Board_AddPlant(board, 0, 1, SeedType::Flowerpot, SeedType::None, 1, 0);
                    Board_AddPlant(board, 0, 3, SeedType::Flowerpot, SeedType::None, 1, 0);
                    for (int i = 3; i < 5; ++i) {
                        for (int j = 0; j < 5; ++j) {
                            Board_AddPlant(board, i, j, SeedType::Flowerpot, SeedType::None, 1, 0);
                        }
                    }
                }
                break;
            case 6:
                board->mBackgroundType = BackgroundType::Num6Boss;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Normal;
                board->mPlantRow[3] = PlantRowType::Normal;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Dirt;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
                    Board_AddPlant(board, 0, 1, SeedType::Flowerpot, SeedType::None, 1, 0);
                    Board_AddPlant(board, 0, 3, SeedType::Flowerpot, SeedType::None, 1, 0);
                    for (int i = 3; i < 4; ++i) {
                        for (int j = 0; j < 5; ++j) {
                            Board_AddPlant(board, i, j, SeedType::Flowerpot, SeedType::None, 1, 0);
                        }
                    }
                }
                break;
            case 7:
                board->mBackgroundType = BackgroundType::Greenhouse;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Normal;
                board->mPlantRow[3] = PlantRowType::Normal;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Dirt;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 8:
                board->mBackgroundType = BackgroundType::MushroomGarden;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Normal;
                board->mPlantRow[3] = PlantRowType::Normal;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Dirt;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            case 9:
                board->mBackgroundType = BackgroundType::Zombiquarium;
                Board_LoadBackgroundImages(board);
                board->mPlantRow[0] = PlantRowType::Normal;
                board->mPlantRow[1] = PlantRowType::Normal;
                board->mPlantRow[2] = PlantRowType::Pool;
                board->mPlantRow[3] = PlantRowType::Pool;
                board->mPlantRow[4] = PlantRowType::Normal;
                board->mPlantRow[5] = PlantRowType::Normal;
                Board_InitCoverLayer(board);
                Board_SetGrids(board);
                break;
            default:
                old_Board_PickBackground(board);
        };
    }
    mBoardBackground = board->mBackgroundType;
}

bool Board_StageIsNight(Board *board) {
    //关系到天上阳光掉落与否。
    BackgroundType::BackgroundType mBackground = board->mBackgroundType;
    return mBackground == BackgroundType::Num2Night || mBackground == BackgroundType::Num4Fog || mBackground == BackgroundType::MushroomGarden || mBackground == BackgroundType::Num6Boss;
}



bool Board_StageHasPool(Board *board) {
    //关系到泳池特有的僵尸，如救生圈僵尸、海豚僵尸、潜水僵尸在本关出现与否。此处我们添加水族馆场景。
    BackgroundType::BackgroundType mBackground = board->mBackgroundType;
//    return mBackground == BackgroundType::Zombiquarium || old_Board_StageHasPool(board);
    return (mBackground == BackgroundType::Zombiquarium && board->mApp->mGameMode != GameMode::ChallengeZombiquarium) || mBackground == BackgroundType::Num3Pool || mBackground == BackgroundType::Num4Fog;
}

bool Board_StageHas6Rows(Board *board) {
    //关系到第六路可否操控（比如种植植物）。
    BackgroundType::BackgroundType mBackground = board->mBackgroundType;
    return mBackground == BackgroundType::Num3Pool || mBackground == BackgroundType::Num4Fog;
}




void Board_UpdateFwoosh(Board *board) {
    if (requestPause) {
        return;
    }
    old_Board_UpdateFwoosh(board);
}



void Board_UpdateFog(Board *board) {
    if (requestPause) {
        return;
    }
    old_Board_UpdateFog(board);
}

void Board_DrawFog(Board *board, Sexy::Graphics* g) {
    if (noFog) {
        return;
    }
    old_Board_DrawFog(board, g);
}


Zombie* Board_AddZombieInRow(Board *board, ZombieType::ZombieType theZombieType, int theRow, int theFromWave, bool playAnim) {
    //修复蹦极僵尸出现时草丛也会摇晃
    if (theZombieType == ZombieType::Bungee) playAnim = false;
    return old_Board_AddZombieInRow(board, theZombieType, theRow, theFromWave, playAnim);
}

//void (*old_Board_UpdateCoverLayer)(Board *board);
//
//void Board_UpdateCoverLayer(Board *board) {
//    if (requestPause) {
//        return;
//    }
//    old_Board_UpdateCoverLayer(board);
//}

void Board_SpeedUpUpdate(Board *board) {
    Board_UpdateGridItems(board);
    Board_UpdateFwoosh(board);
    Board_UpdateGame(board);
    Board_UpdateFog(board);
//    Board_UpdateCoverLayer(board);
    Challenge_Update(board->mChallenge);
}

bool TRect_Contains(TRect *rect, int x, int y) {
    return rect->mX < x && rect->mY < y && rect->mX + rect->mWidth > x && rect->mY + rect->mHeight > y;
}

void Board_Update(Board *board) {
    isMainMenu = false;
    mBoardBackground = board->mBackgroundType;
    GamepadControls* gamepadControls1 = board->mGamepadControls1;
    GamepadControls* gamepadControls2 = board->mGamepadControls2;

    if (requestDrawButterInCursor) {
        Zombie *zombieUnderButter = Board_ZombieHitTest(board, gamepadControls2->mCursorPositionX,gamepadControls2->mCursorPositionY, 1);
        if (zombieUnderButter != NULL) {
            Zombie_AddButter(zombieUnderButter);
        }
    }

    if (requestDrawShovelInCursor) {
        Plant* plantUnderShovel = Board_ToolHitTest(board, gamepadControls1->mCursorPositionX,gamepadControls1->mCursorPositionY);
        if (plantUnderShovel != NULL) {
            // 让这个植物高亮
            plantUnderShovel->mEatenFlashCountdown = 1000;//1000是为了不和其他闪光效果冲突
        }
    }

    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::ChallengeButteredPopcorn && lawnApp->mGameScene == GameScenes::Playing) {
        Zombie *zombieUnderButter = Board_ZombieHitTest(board, gamepadControls1->mCursorPositionX,gamepadControls1->mCursorPositionY, 1);
        if (zombieUnderButter != NULL) {
            Zombie_AddButter(zombieUnderButter);
        }
        if (gamepadControls2->mPlayerIndex2 != -1) {
            Zombie *zombieUnderButter = Board_ZombieHitTest(board, gamepadControls2->mCursorPositionX, gamepadControls2->mCursorPositionY, 1);
            if (zombieUnderButter != NULL) {
                Zombie_AddButter(zombieUnderButter);
            }
        }
    }
//    GameButton_Update(mBoardMenuButton);
    if (isKeyboardTwoPlayerMode) {
        gamepadControls1->mIsInShopSeedBank = false;
        gamepadControls2->mIsInShopSeedBank = false;
        gamepadControls1->mPlayerIndex2 = 0;
        gamepadControls2->mPlayerIndex2 = 1;
        gamepadControls1->mGamepadState = 7;
        gamepadControls2->mGamepadState = 7;
    }


    if (!board->mPaused && board->mTimeStopCounter <= 0) {
        switch (speedUpMode) {
            case 1:
                if (speedUpCounter++ % 5 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 2:
                if (speedUpCounter++ % 2 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 3:
                Board_SpeedUpUpdate(board);
                break;
            case 4:
                Board_SpeedUpUpdate(board);
                if (speedUpCounter++ % 2 == 0) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 5:
                for (int i = 0; i < 2; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 6:
                for (int i = 0; i < 4; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            case 7:
                for (int i = 0; i < 9; ++i) {
                    Board_SpeedUpUpdate(board);
                }
                break;
            default:
                break;
        }

        // 为夜晚泳池场景补全泳池反射闪光特效
//        if ( board->mBackgroundType == BackgroundType::Num4Fog && board->mPoolSparklyParticleID == 0 && board->mDrawCount > 0 ){
//            TodParticleSystem * poolSparklyParticle = LawnApp_AddTodParticle(board->mApp, 450.0, 295.0, 220000, ParticleEffect::PoolSparkly);
//            board->mPoolSparklyParticleID = LawnApp_ParticleGetID(board->mApp, poolSparklyParticle);
//        }
    }

    if (ClearAllPlant) {
        Board_RemoveAllPlants(board);
        ClearAllPlant = false;
    }

    if (clearAllZombies) {
        Board_RemoveAllZombies(board);
        clearAllZombies = false;
    }

    if (clearAllGraves) {
        GridItem* gridItem = nullptr;
        while (Board_IterateGridItems(board, &gridItem)) {
            if (gridItem->mGridItemType == GridItemType::Gravestone) {
                GridItem_GridItemDie(gridItem);
            }
        }
        clearAllGraves = false;
    }

    if (clearAllMowers) {
        if (lawnApp->mGameScene == GameScenes::Playing) {
            Board_RemoveAllMowers(board);
        }
        clearAllMowers = false;
    }

    if (recoverAllMowers) {
        if (lawnApp->mGameScene == GameScenes::Playing) {
//            Board_RemoveAllMowers(board);
            Board_ResetLawnMowers(board);
        }
        recoverAllMowers = false;
    }

    if (passNowLevel) {
        board->mLevelComplete = true;
        board->mApp->mBoardResult = board->mApp->mGameMode == GameMode::TwoPlayerVS ? BoardResult::VSPlantWon : BoardResult::Won;
        passNowLevel = false;
    }
    // 魅惑所有僵尸
    if (hypnoAllZombies) {
        Zombie* zombie = nullptr;
        while (Board_IterateZombies(board, &zombie)) {
            if (zombie->mZombieType != ZombieType::Boss) {
                zombie->mMindControlled = true;
            }
        }
        hypnoAllZombies = false;
    }

    if (freezeAllZombies) {
        for (Zombie* zombie = nullptr; Board_IterateZombies(board, &zombie); Zombie_HitIceTrap(zombie));
        freezeAllZombies = false;
    }

    if (startAllMowers) {
        if (lawnApp->mGameScene == GameScenes::Playing)
            for (int* lawnMower = nullptr; Board_IterateLawnMowers(board, &lawnMower); LawnMower_StartMower(lawnMower));
        startAllMowers = false;
    }

    // 修改卡槽
    if (setSeedPacket && choiceSeedType != SeedType::None) {
        if (targetSeedBank == 1) {
            if (choiceSeedType < SeedType::SeedTypeCount && !gamepadControls1->mIsZombie) {
                board->mSeedBank1->mSeedPackets[choiceSeedPacketIndex].mPacketType = isImitaterSeed ? SeedType::Imitater : choiceSeedType;
                board->mSeedBank1->mSeedPackets[choiceSeedPacketIndex].mImitaterType = isImitaterSeed ? choiceSeedType : SeedType::None;
            } else if (choiceSeedType > SeedType::ZombieTombsTone && gamepadControls1->mIsZombie) // IZ模式里用不了墓碑
                board->mSeedBank1->mSeedPackets[choiceSeedPacketIndex].mPacketType = choiceSeedType;
        }
        else if (targetSeedBank == 2 && board->mSeedBank2 != nullptr) {
            if (choiceSeedType < SeedType::SeedTypeCount && !gamepadControls2->mIsZombie) {
                board->mSeedBank2->mSeedPackets[choiceSeedPacketIndex].mPacketType = isImitaterSeed ? SeedType::Imitater : choiceSeedType;
                board->mSeedBank2->mSeedPackets[choiceSeedPacketIndex].mImitaterType = isImitaterSeed ? choiceSeedType : SeedType::None;
            } else if (Challenge_IsZombieSeedType(choiceSeedType) && gamepadControls2->mIsZombie)
                board->mSeedBank2->mSeedPackets[choiceSeedPacketIndex].mPacketType = choiceSeedType;
        }
        setSeedPacket = false;
    }

    if (passNowLevel) {
        board->mLevelComplete = true;
        board->mApp->mBoardResult = board->mApp->mGameMode == GameMode::TwoPlayerVS ? BoardResult::VSPlantWon : BoardResult::Won;
        passNowLevel = false;
    }

    // 布置选择阵型
    if (layChoseFormation) // 用按钮触发, 防止进入游戏时自动布阵
    {
        if (formationId != -1) {
            const char *formation = GetFormationByIndex(formationId);
            char *copiedStr = strdup(formation);
            Board_LoadFormation(board, copiedStr);
        }
        layChoseFormation = false;
    }

    // 布置粘贴阵型
    if (layPastedFormation) {
        if (customFormation != "") {
            char *copiedStr = strdup(customFormation.c_str());
            Board_LoadFormation(board, copiedStr);
        }
        layPastedFormation = false;
    }

    if (ladderBuild) {
        if (theBuildLadderX < 9 && theBuildLadderY < (Board_StageHas6Rows(board) ? 6 : 5))
            // 防止选“所有行”或“所有列”的时候放置到场外
            Board_AddALadder(board, theBuildLadderX, theBuildLadderY);
        ladderBuild = false;
    }


    // 植物放置
    if (plantBuild && theBuildPlantType != SeedType::None) {
        int colsCount = (theBuildPlantType == SeedType::Cobcannon) ? 8 : 9; // 玉米加农炮不种在九列
        int width = (theBuildPlantType == SeedType::Cobcannon) ? 2 : 1;     // 玉米加农炮宽度两列
        int rowsCount = Board_StageHas6Rows(board) ? 6 : 5;
        bool isIZMode = LawnApp_IsIZombieLevel(lawnApp);
        // 全场
        if (theBuildPlantX == 9 && theBuildPlantY == 6) {
            for (int x = 0; x < colsCount; x += width) {
                for (int y = 0; y < rowsCount; y++) {
                    Plant *theBuiltPlant = Board_AddPlant(board, x, y, theBuildPlantType,(isImitaterPlant ?  SeedType::Imitater : SeedType::None), 0, true);
                    if (isImitaterPlant) Plant_SetImitaterFilterEffect(theBuiltPlant);
                    if (isIZMode) Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
                }
            }
        }
            // 单行
        else if (theBuildPlantX == 9 && theBuildPlantY < 6) {
            for (int x = 0; x < colsCount; x += width) {
                Plant *theBuiltPlant = Board_AddPlant(board, x, theBuildPlantY, theBuildPlantType,(isImitaterPlant ?  SeedType::Imitater : SeedType::None), 0, true);
                if (isImitaterPlant) Plant_SetImitaterFilterEffect(theBuiltPlant);
                if (isIZMode) Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
            }
        }
            // 单列
        else if (theBuildPlantX < 9 && theBuildPlantY == 6) {
            for (int y = 0; y < rowsCount; y++) {
                Plant *theBuiltPlant = Board_AddPlant(board, theBuildPlantX, y, theBuildPlantType,(isImitaterPlant ?  SeedType::Imitater : SeedType::None), 0, true);
                if (isImitaterPlant) Plant_SetImitaterFilterEffect(theBuiltPlant);
                if (isIZMode) Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
            }
        }
            // 单格
        else if (theBuildPlantX < colsCount && theBuildPlantY < rowsCount) {
            Plant *theBuiltPlant = Board_AddPlant(board, theBuildPlantX, theBuildPlantY, theBuildPlantType,(isImitaterPlant ? SeedType::Imitater : SeedType::None), 0, true);
            if (isImitaterPlant) Plant_SetImitaterFilterEffect(theBuiltPlant);
            if (isIZMode) Challenge_IZombieSetupPlant(board->mChallenge, theBuiltPlant);
        }
        plantBuild = false;
    }

    // 僵尸放置
    if (zombieBuild && theBuildZombieType != ZombieType::Invalid) {
        if (theBuildZombieType == ZombieType::Boss)
            Board_AddZombieInRow(board, theBuildZombieType, 0, 0, true);
        else {
            int colsCount = 9;
            int rowsCount = Board_StageHas6Rows(board) ? 6 : 5;
            // 僵尸出生线
            if (BuildZombieX == 10 && BuildZombieY == 6)
                for (int y = 0; y < rowsCount; ++y)
                    Board_AddZombieInRow(board, theBuildZombieType, y, board->mCurrentWave, true);
                // 僵尸出生点
            else if (BuildZombieX == 10 && BuildZombieY < 6)
                Board_AddZombieInRow(board, theBuildZombieType, BuildZombieY, board->mCurrentWave, true);
                // 全场
            else if (BuildZombieX == 9 && BuildZombieY == 6)
                for (int x = 0; x < colsCount; ++x)
                    for (int y = 0; y < rowsCount; ++y)
                        Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, x, y);
                // 单行
            else if (BuildZombieX == 9 && BuildZombieY < 6)
                for (int x = 0; x < colsCount; ++x)
                    Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, x, BuildZombieY);
                // 单列
            else if (BuildZombieX < 9 && BuildZombieY == 6)
                for (int y = 0; y < rowsCount; ++y)
                    Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, BuildZombieX, y);
                // 单格
            else if (BuildZombieX < colsCount && BuildZombieY < rowsCount)
                Challenge_IZombiePlaceZombie(board->mChallenge, theBuildZombieType, BuildZombieX, BuildZombieY);
        }
        zombieBuild = false;
    }

    // 放置墓碑
    if (graveBuild) {
        int colsCount = 9;
        int rowsCount = Board_StageHas6Rows(board) ? 6 : 5;
        // 全场
        if (BuildZombieX == 9 && BuildZombieY == 6) {
            GridItem *gridItem = nullptr;
            while (Board_IterateGridItems(board, &gridItem)) {
                if (gridItem->mGridItemType == GridItemType::Gravestone) {
                    GridItem_GridItemDie(gridItem);
                }
            }
            for (int x = 0; x < colsCount; ++x) {
                for (int y = 0; y < rowsCount; ++y){
                    Challenge_GraveDangerSpawnGraveAt(board->mChallenge, x, y);
                }
            }
        }
            // 单行
        else if (BuildZombieX == 9 && BuildZombieY < 6) {
            GridItem *gridItem = nullptr;
            while (Board_IterateGridItems(board, &gridItem)) {
                if (gridItem->mGridItemType == GridItemType::Gravestone && gridItem->mGridY == BuildZombieY) {
                    GridItem_GridItemDie(gridItem);
                }
            }
            for (int x = 0; x < colsCount; ++x) {
                Challenge_GraveDangerSpawnGraveAt(board->mChallenge, x, BuildZombieY);
            }
        }
            // 单列
        else if (BuildZombieX < 9 && BuildZombieY == 6) {
            GridItem *gridItem = nullptr;
            while (Board_IterateGridItems(board, &gridItem)) {
                if (gridItem->mGridItemType == GridItemType::Gravestone && gridItem->mGridX == BuildZombieX) {
                    GridItem_GridItemDie(gridItem);
                }
            }
            for (int y = 0; y < rowsCount; ++y) {
                Challenge_GraveDangerSpawnGraveAt(board->mChallenge, BuildZombieX, y);
            }
        }
            // 单格
        else if (BuildZombieX < 9 && BuildZombieY < 6) {
            Challenge_GraveDangerSpawnGraveAt(board->mChallenge, BuildZombieX, BuildZombieY);
        }
        graveBuild = false;
    }

    // 出怪设置
    if (buttonSetSpawn && choiceSpawnMode != 0) {
        int typesCount = 0;                          // 已选僵尸种类数
        int typesList[ZombieType::ZombieTypesCount]; // 已选僵尸种类列表
        // 将僵尸代号放入种类列表, 并更新已选种类数
        for (int type = 0; type < ZombieType::ZombieTypesCount; ++type) {
            if (checkZombiesAllowed[type] && type != ZombieType::Bungee) // 飞贼僵尸不应作为正常僵尸出现在出怪列表中
            {
                typesList[typesCount] = type;
                ++typesCount;
            }
        }
        if (typesCount > 0) // 设置出怪需要选择至少 1 种除飞贼以外的僵尸
        {
            // 自然出怪
            if (choiceSpawnMode == 1) {
                // 清空出怪列表
                for (int wave = 0; wave < board->mNumWaves; ++wave) {
                    for (int index = 0; index < MAX_ZOMBIES_IN_WAVE; ++index)
                        board->mZombiesInWave[wave][index] = ZombieType::Invalid;
                }
                // 设置游戏中的僵尸允许类型
                for (int type = 0; type < ZombieType::ZombieTypesCount; ++type)
                    board->mZombieAllowed[type] = checkZombiesAllowed[type];
                board->mZombieAllowed[ZombieType::Normal] = true; // 自然出怪下必须含有普通僵尸
                // 由游戏生成出怪列表
                Board_PickZombieWaves(board);
            }
                // 极限出怪
            else if (choiceSpawnMode == 2) {
                int indexInLevel = 0;
                // 均匀填充出怪列表
                for (int wave = 0; wave < board->mNumWaves; ++wave) {
                    for (int indexInWave = 0; indexInWave < MAX_ZOMBIES_IN_WAVE; ++indexInWave) {
                        // 使用僵尸的“关内序号”遍历设置出怪可能会比使用“波内序号”更加均匀
                        board->mZombiesInWave[wave][indexInWave] = (ZombieType::ZombieType) typesList[indexInLevel % typesCount];
                        ++indexInLevel;
                    }
                    if (Board_IsFlagWave(board, wave)) {
                        board->mZombiesInWave[wave][0] = ZombieType::Flag; // 生成旗帜僵尸
                        if (checkZombiesAllowed[ZombieType::Bungee]) {
                            // 生成飞贼僵尸
                            for (int index: {1, 2, 3, 4})
                                board->mZombiesInWave[wave][index] = ZombieType::Bungee;
                        }
                    }
                }
                // 不能只出雪人僵尸, 在第一波生成 1 只普通僵尸
                if (checkZombiesAllowed[ZombieType::Yeti] && typesCount == 1)
                    board->mZombiesInWave[0][0] = ZombieType::Normal;
            }
            // 重新生成选卡预览僵尸
            if (lawnApp->mGameScene == GameScenes::LevelIntro) {
                Board_RemoveCutsceneZombies(board);
                board->mCutScene->mPlacedZombies = false;
            }
        }
        buttonSetSpawn = false;
    }

    Board_UpdateButtons(board);
    return old_Board_Update(board);
}

int Board_GetNumWavesPerFlag(Board *board) {
    //修改此函数，以做到在进度条上正常绘制旗帜波的旗帜。
    LawnApp *lawnApp =board->mApp;
    int mNumWaves = board->mNumWaves;
    if (LawnApp_IsFirstTimeAdventureMode(lawnApp) && mNumWaves < 10) {
        return mNumWaves;
    }
    //额外添加一段判断逻辑，判断关卡代码20且波数少于10的情况
    if (lawnApp->mGameMode == GameMode::ChallengeHeavyWeapon && mNumWaves < 10) {
        return mNumWaves;
    }
    return 10;
}



bool Board_IsFlagWave(Board *board, int currentWave) {
    //修改此函数，以做到正常出旗帜波僵尸。
    if (!normalLevel) {
        return old_Board_IsFlagWave(board, currentWave);
    }
    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS)
        return true;
    if (LawnApp_IsFirstTimeAdventureMode(lawnApp) && board->mLevel == 1)
        return false;
    int mNumWavesPerFlag = Board_GetNumWavesPerFlag(board);
    return currentWave % mNumWavesPerFlag == mNumWavesPerFlag - 1;
}



void Board_SpawnZombieWave(Board *board) {
    //在对战模式中放出一大波僵尸时播放大波僵尸音效
    LawnApp *lawnApp = board->mApp;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
        LawnApp_PlaySample(lawnApp, *Sexy_SOUND_HUGE_WAVE_Addr);
    }
    old_Board_SpawnZombieWave(board);
}


void Board_DrawProgressMeter(Board *board, Sexy::Graphics *graphics, int a3, int a4) {
    //修改此函数，以做到在进度条上正常绘制旗帜波的旗帜。
    if (normalLevel) {
        LawnApp *lawnApp = board->mApp;
        if (LawnApp_IsAdventureMode(lawnApp) && Board_ProgressMeterHasFlags(board)) {
            lawnApp->mGameMode = GameMode::ChallengeHeavyWeapon;//修改关卡信息为非冒险模式
            old_Board_DrawProgressMeter(board, graphics, a3, a4);
            lawnApp->mGameMode = GameMode::Adventure;//再把关卡信息改回冒险模式
            return;
        }
        old_Board_DrawProgressMeter(board, graphics, a3, a4);
    } else {
        old_Board_DrawProgressMeter(board, graphics, a3, a4);
    }
}


bool Board_IsLevelDataLoaded(Board *board) {
    //确保在开启原版难度时，所有用到levels.xml的地方都不生效
    if (normalLevel) return false;
    return old_Board_IsLevelDataLoaded(board);
}



bool Board_NeedSaveGame(Board *board) {
    //可以让结盟关卡存档，但是好多BUG啊
//    if (LawnApp_IsCoopMode(*((int **) board + 69))) {
//        return true;
//    }
    return old_Board_NeedSaveGame(board);
}


void Board_DrawHammerButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) {
    if (!keyboardMode) return;
    float tmp = graphics->mTransY;
    TRect rect;
    Board_GetButterButtonRect(&rect, board);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, rect.mX, rect.mY);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_HAMMER_ICON_Addr, rect.mX - 7,
                            rect.mY - 3);

    if (Sexy_GamepadApp_HasGamepad(lawnApp) || (lawnApp->mGamePad1IsOn && lawnApp->mGamePad2IsOn)) {
        Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr,
                                    rect.mX + 36, rect.mY + 40, 2);
    } else {
        Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS2_Addr,
                                    rect.mX + 36, rect.mY + 40, 2);
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
    graphics->mTransY = tmp;
}

void Board_DrawButterButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) {
    if (!LawnApp_IsCoopMode(lawnApp)) {
        if (!LawnApp_IsAdventureMode(lawnApp))
            return;
        if (lawnApp->mTwoPlayerState == -1)
            return;
    }
    float tmp = graphics->mTransY;
    TRect rect;
    Board_GetButterButtonRect(&rect, board);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, rect.mX, rect.mY);
    if (board->mChallenge->mChallengeState == ChallengeState::ShovelFlashing) {
        Color color;
        GetFlashingColor(&color, board->mMainCounter, 75);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        Sexy_Graphics_SetColor(graphics, &color);
    }
    //实现拿着黄油的时候不在栏内绘制黄油
    if (!requestDrawButterInCursor) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_BUTTER_ICON_Addr, rect.mX - 7,
                                rect.mY - 3);
    }
    if (keyboardMode) {
        Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr, rect.mX + 36,
                                    rect.mY + 40, 2);
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
    graphics->mTransY = tmp;
}

void Board_DrawShovelButton(Board *board, Sexy::Graphics *graphics, LawnApp *lawnApp) {
    //实现玩家拿着铲子时不在ShovelBank中绘制铲子、实现在对战模式中添加铲子按钮

    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
//        LOGD("%d %d",rect[0],rect[1]);
        //return;  原版游戏在此处就return了，所以对战中不绘制铲子按钮。
        if(keyboardMode) return;
        TodDrawImageScaledF(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, mTouchVSShovelRect.mX,mTouchVSShovelRect.mY,0.8f,0.8f);
        if(!requestDrawShovelInCursor)TodDrawImageScaledF(graphics, *Sexy_IMAGE_SHOVEL_Addr, -6,78,0.8f,0.8f);
        return;
    }
    float tmp = graphics->mTransY;
    TRect rect;
    Board_GetShovelButtonRect(&rect, board);
    Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVELBANK_Addr, rect.mX,
                            rect.mY);
    if (board->mChallenge->mChallengeState == ChallengeState::ShovelFlashing) {
        Color color;
        GetFlashingColor(&color, board->mMainCounter, 75);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        Sexy_Graphics_SetColor(graphics, &color);
    }
    //实现拿着铲子的时候不在栏内绘制铲子
    if (!requestDrawShovelInCursor) {
        if (lawnApp->mGameMode == GameMode::ChallengeLastStand) {
            Challenge *challenge = board->mChallenge;
            if (challenge->mChallengeState == ChallengeState::Normal && lawnApp->mGameScene == GameScenes::Playing) {
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ZEN_MONEYSIGN_Addr,
                                        rect.mX - 7, rect.mY - 3);
            } else {
                Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVEL_Addr, rect.mX - 7,
                                        rect.mY - 3);
            }
        } else {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SHOVEL_Addr, rect.mX - 7,
                                    rect.mY - 3);
        }
    }
    if (keyboardMode) {
        if (LawnApp_IsCoopMode(lawnApp)) {
            Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr,
                                        rect.mX + 40, rect.mY + 40, 1);
        } else {
            if (Sexy_GamepadApp_HasGamepad(lawnApp) || (lawnApp->mGamePad1IsOn && lawnApp->mGamePad2IsOn)) {
                Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS_Addr,
                                            rect.mX + 50, rect.mY + 40, 1);
            } else {
                Sexy_Graphics_DrawImageCel2(graphics, *Sexy_IMAGE_HELP_BUTTONS2_Addr,
                                            rect.mX + 50, rect.mY + 40, 1);
            }
        }
    }
    Sexy_Graphics_SetColorizeImages(graphics, false);
    graphics->mTransY = tmp;
}


void Board_DrawShovel(Board *board, Sexy::Graphics *graphics) {

    //实现拿着铲子、黄油的时候不在栏内绘制铲子、黄油，同时为对战模式添加铲子按钮
    LawnApp *lawnApp = board->mApp;
    GameMode::GameMode mGameMode = lawnApp->mGameMode;
    if (mGameMode == GameMode::ChallengeHeavyWeapon)
        return;
    if (mGameMode == GameMode::ChallengeTreeOfWisdom || mGameMode == GameMode::ChallengeZenGarden) {//如果是花园或智慧树
        return Board_DrawZenButtons(board, graphics);
    }
    if (board->mShowHammer) {//绘制锤子按钮
        Board_DrawHammerButton(board, graphics, lawnApp);
    }
    if (board->mShowButter) {//绘制黄油按钮
        Board_DrawButterButton(board, graphics, lawnApp);
    }
    if (board->mShowShovel) {//绘制铲子按钮
        Board_DrawShovelButton(board, graphics, lawnApp);
    }
}



void Board_Pause(Board* board, bool a2) {
//  能在这里得知游戏是否暂停
//    if (a2) Music2_StopAllMusic((Music2*)board->mApp->mMusic);
//    else Music2_StartGameMusic((Music2*)board->mApp->mMusic, true);
    old_Board_Pause(board, a2);
}

void Board_AddSecondPlayer(Board *board, int a2) {
    //去除加入2P时的声音

//    (*(void (__fastcall **)(int, int, int))(*(_DWORD *)this[69] + 680))(this[69], Sexy::SOUND_CHIME, 1);
//    ((void (__fastcall *)(int *, const char *, int))loc_2F098C)(v2 + 25, "[P2_JOINED]", 11);
    board->mUnkIntSecondPlayer1 = 3;
    board->mUnkBoolSecondPlayer = false;
    board->mUnkIntSecondPlayer2 = 0;
}

bool endlessLastStand = false;

bool Board_IsLastStandFinalStage(Board *board) {
    //无尽坚不可摧
    if (endlessLastStand) return false;
    return board->mApp->mGameMode == GameMode::ChallengeLastStand && board->mChallenge->mSurvivalStage == 4;
}

Plant *Board_GetFlowerPotAt(Board *board, int theGridX, int theGridY) {
    //修复 屋顶关卡加农炮无法种植在第三第四列的组合上
    Plant *plant = NULL;
    while (Board_IteratePlants(board, &plant)) {
        if (plant->mSeedType == SeedType::Flowerpot &&plant->mRow == theGridY && plant->mPlantCol == theGridX && !Plant_NotOnGround(plant)) {
                return plant;
        }
    }
    return NULL;
}

Plant *Board_GetPumpkinAt(Board *board, int theGridX, int theGridY) {
    Plant *plant = NULL;
    while (Board_IteratePlants(board, &plant)) {
        if (plant->mSeedType == SeedType::Pumpkinshell &&plant->mRow == theGridY && plant->mPlantCol == theGridX && !Plant_NotOnGround(plant)) {
            return plant;
        }
    }
    return NULL;
}

void Board_DoPlantingEffects(Board *board, int theGridX, int theGridY, Plant *plant) {
    int num = Board_GridToPixelX(board,theGridX, theGridY) + 41;
    int num2 = Board_GridToPixelY(board,theGridX, theGridY) + 74;
    SeedType::SeedType mSeedType = plant->mSeedType;
    LawnApp *lawnApp = board->mApp;
    if (mSeedType == SeedType::Lilypad) {
        num2 += 15;
    } else if (mSeedType == SeedType::Flowerpot) {
        num2 += 30;
    }
    BackgroundType::BackgroundType mBackground = board->mBackgroundType;
    if (mBackground == BackgroundType::Greenhouse) {
        LawnApp_PlayFoley(lawnApp, FoleyType::Ceramic);
        return;
    }
    if (mBackground == BackgroundType::Zombiquarium) {
        LawnApp_PlayFoley(lawnApp, FoleyType::PlantWater);
        return;
    }

    if (Plant_IsFlying(mSeedType)) {
        LawnApp_PlayFoley(lawnApp, FoleyType::Plant);
        return;
    }
    if (Board_IsPoolSquare(board, theGridX, theGridY)) {
        LawnApp_PlayFoley(lawnApp, FoleyType::PlantWater);
        LawnApp_AddTodParticle(lawnApp, num, num2, 400000, ParticleEffect::PlantingPool);
        return;
    }

    LawnApp_PlayFoley(lawnApp, FoleyType::Plant);
//    switch (mSeedType) {
//        case SeedType::Sunflower:
//            LawnApp_PlaySample(lawnApp, Addon_Sounds.achievement);
//            break;
//        default:
//            LawnApp_PlayFoley(lawnApp, FoleyType::Plant);
//            break;
//    }
    LawnApp_AddTodParticle(lawnApp,num, num2, 400000, ParticleEffect::Planting);
}



void Board_InitLawnMowers(Board *board) {
    if (banMower) return;
    if (board->mApp->mGameMode == GameMode::ChallengeButteredPopcorn) return;
    return old_Board_InitLawnMowers(board);
}


void Board_PickZombieWaves(Board *board) {
    //有问题，在111和115里，冒险中锤僵尸的mNumWaves从8变6了
    if (board->mApp->mGameMode == GameMode::ChallengeButteredPopcorn && !Board_IsLevelDataLoaded(board)) {
        board->mNumWaves = 20;
        ZombiePicker zombiePicker;
        Board_ZombiePickerInit(&zombiePicker);
//        ZombieType::ZombieType introducedZombieType = Board_GetIntroducedZombieType(board);
        for (int i = 0; i < board->mNumWaves; i++)
        {
            Board_ZombiePickerInitForWave(&zombiePicker);
            board->mZombiesInWave[i][0] = ZombieType::Invalid;
            bool isFlagWave = Board_IsFlagWave(board,i);
//            bool isBeforeLastWave = i == mNumWaves - 1;
            int &aZombiePoints = zombiePicker.mZombiePoints;
            aZombiePoints = i * 4 / 5 + 1;
            if (isFlagWave)
            {
                int num2 = std::min(zombiePicker.mZombiePoints, 8);
                zombiePicker.mZombiePoints = (int)(zombiePicker.mZombiePoints * 2.5f);
                for (int k = 0; k < num2; k++) {
                    Board_PutZombieInWave(board,ZombieType::Normal, i, &zombiePicker);
                }
                Board_PutZombieInWave(board,ZombieType::Flag, i, &zombiePicker);
            }
            if(i == board->mNumWaves - 1) Board_PutZombieInWave(board,ZombieType::Gargantuar, i, &zombiePicker);
            while (aZombiePoints > 0 && zombiePicker.mZombieCount < MAX_ZOMBIES_IN_WAVE) {
                ZombieType::ZombieType aZombieType = Board_PickZombieType(board,aZombiePoints, i, &zombiePicker);
                Board_PutZombieInWave(board,aZombieType, i, &zombiePicker);
            }
        }
        return;
    }
    if (board->mApp->mGameMode == GameMode::ChallengePoolParty && !Board_IsLevelDataLoaded(board)) {
        board->mNumWaves = 20;
        ZombiePicker zombiePicker;
        Board_ZombiePickerInit(&zombiePicker);
//        ZombieType::ZombieType introducedZombieType = Board_GetIntroducedZombieType(board);
        for (int i = 0; i < board->mNumWaves; i++)
        {
            Board_ZombiePickerInitForWave(&zombiePicker);
            board->mZombiesInWave[i][0] = ZombieType::Invalid;
            bool isFlagWave = Board_IsFlagWave(board,i);
//            bool isBeforeLastWave = i == mNumWaves - 1;
            int &aZombiePoints = zombiePicker.mZombiePoints;
            aZombiePoints = i * 4 / 5 + 1;
            if (isFlagWave)
            {
                int num2 = std::min(zombiePicker.mZombiePoints, 8);
                zombiePicker.mZombiePoints = (int)(zombiePicker.mZombiePoints * 2.5f);
                for (int k = 0; k < num2; k++) {
                    Board_PutZombieInWave(board,ZombieType::Normal, i, &zombiePicker);
                }
                Board_PutZombieInWave(board,ZombieType::Flag, i, &zombiePicker);
            }
            while (aZombiePoints > 0 && zombiePicker.mZombieCount < MAX_ZOMBIES_IN_WAVE) {
                ZombieType::ZombieType aZombieType = Board_PickZombieType(board,aZombiePoints, i, &zombiePicker);
                Board_PutZombieInWave(board,aZombieType, i, &zombiePicker);
            }
        }
        return;
    }
    return old_Board_PickZombieWaves(board);
}

int Board_GetLiveGargantuarCount(Board *board) {
    int num = 0;
    Zombie *zombie = NULL;
    while (Board_IterateZombies(board, (Zombie **) &zombie)) {
        if (!zombie->mDead && zombie->mHasHead && !Zombie_IsDeadOrDying(zombie) &&
            Zombie_IsOnBoard(zombie) && (zombie->mZombieType == ZombieType::Gargantuar || zombie->mZombieType == ZombieType::RedeyeGargantuar)) {
            num++;
        }
    }
    return num;
}

int Board_GetLiveZombiesCount(Board *board) {
    int num = 0;
    Zombie *zombie = NULL;
    while (Board_IterateZombies(board, (Zombie **) &zombie)) {
        if (!zombie->mDead && zombie->mHasHead && !Zombie_IsDeadOrDying(zombie) && Zombie_IsOnBoard(zombie)) {
            num++;
        }
    }
    return num;
}

void (*old_Board_UpdateLevelEndSequence)(Board *board);

void Board_UpdateLevelEndSequence(Board *board) {
    if (requestPause) return;
    return old_Board_UpdateLevelEndSequence(board);
}

void (*old_Board_UpdateGridItems)(Board *board);

void Board_UpdateGridItems(Board *board) {
    if (requestPause) return;
    return old_Board_UpdateGridItems(board);
}

#endif //PVZ_TV_1_1_5_BOARD_CPP