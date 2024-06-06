//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_ZOMBIE_CPP
#define PVZ_TV_1_1_5_ZOMBIE_CPP

#include "../Board/Board.h"
#include "Zombie.h"
#include "HookGame/LawnApp/LawnApp.h"
#include "HookGame/Reanimation/Reanimation.h"
#include "HookGame/GridItem/GridItem.h"
#include "HookGame/Misc/Misc.h"
#include "HookGame/SpecialConstraints.h"
#include "HookGame/GlobalVariable.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Plant/Plant.h"
#include "HookGame/Graphics/Graphics.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

bool zombieBloated = false;

void (*old_Zombie_Update)(Zombie* a1);

void Zombie_Update(Zombie* zombie) {

    if (zombieBloated) {
        //如果开启了“普僵必噎死”
        zombie->mBloated = zombie->mZombieType == ZombieType::Normal && !zombie->mInPool;
    }
//    if (requestPause && zombie->mZombiePhase == ZombiePhase::RisingFromGrave) {
//        // 试图修复高级暂停时IZ放僵尸只显示虚影。失败。
//        Zombie_UpdatePlaying(zombie);
//        return;
//    }
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    if (zombie->mZombieType == ZombieType::Flag && zombie->mBossFireBallReanimID != 0) {
        Reanimation* reanimation = LawnApp_ReanimationTryToGet(zombie->mApp,zombie->mBossFireBallReanimID);
        if (reanimation!= NULL)
            Reanimation_Update(reanimation);
    }
    return old_Zombie_Update(zombie);
}

void (*old_Zombie_UpdateZombiePeaHead)(Zombie *zombie);

void Zombie_UpdateZombiePeaHead(Zombie *zombie) {
    // 用于修复豌豆僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG、啃食时不发射子弹的BUG
    // 游戏原版逻辑是判断是否hasHead 且 是否isEating。这里去除对吃植物的判断

    if (!zombie->mMindControlled && !(zombie->mHasHead && zombie->mIsEating)) {
        return old_Zombie_UpdateZombiePeaHead(zombie);
    }

    if (zombie->mHasHead) {
        int mPhaseCounter = zombie->mPhaseCounter;
        LawnApp *lawnApp = zombie->mApp;
        if (mPhaseCounter == 35) {
            Reanimation *mSpecialHeadReanim =LawnApp_ReanimationGet(lawnApp, zombie->mSpecialHeadReanimID);
            Reanimation_PlayReanim(mSpecialHeadReanim, "anim_shooting", ReanimLoopType::PlayOnceAndHold, 20, 35.0f);
        } else if (mPhaseCounter <= 0) {
            Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(lawnApp, zombie->mSpecialHeadReanimID);
            Reanimation_PlayReanim(mSpecialHeadReanim, "anim_head_idle", ReanimLoopType::PlayOnceAndHold, 20, 15.0f);
            LawnApp_PlayFoley(lawnApp, FoleyType::Throw);
            Reanimation *mBodyReanim = LawnApp_ReanimationGet(lawnApp, zombie->mBodyReanimID);
            int index = Reanimation_FindTrackIndexById(mBodyReanim,*ReanimTrackId_anim_head1_Addr);
            ReanimatorTransform aTransForm;
            ReanimatorTransform_ReanimatorTransform(&aTransForm);
            Reanimation_GetCurrentTransform(mBodyReanim, index, &aTransForm);

            float aOriginX = zombie->mPosX + aTransForm.mTransX - 9.0f;
            float aOriginY = zombie->mPosY + aTransForm.mTransY + 6.0f - zombie->mAltitude;

            if (zombie->mMindControlled) {
                aOriginX += 90.0f * zombie->mScaleZombie;
                Projectile* projectile = Board_AddProjectile(zombie->mBoard,aOriginX,aOriginY,zombie->mRenderOrder,zombie->mRow, ProjectileType::Pea);
                projectile->mDamageRangeFlags = 1;
            } else {
                Projectile *projectile = Board_AddProjectile(zombie->mBoard,aOriginX,aOriginY,zombie->mRenderOrder,zombie->mRow, ProjectileType::ZombiePea);
                projectile->mMotionType = ProjectileMotion::Backwards;
            }
            zombie->mPhaseCounter = 150;
        }
    }
}

void (*old_Zombie_UpdateZombieGatlingHead)(Zombie *zombie);

void Zombie_UpdateZombieGatlingHead(Zombie *zombie) {
    // 用于修复加特林僵尸被魅惑后依然向左发射会伤害植物的子弹的BUG、啃食时不发射子弹的BUG
    // 游戏原版逻辑是判断是否hasHead 且 是否isEating。这里去除对吃植物的判断

    if (!zombie->mMindControlled && !(zombie->mHasHead && zombie->mIsEating)) {
        return old_Zombie_UpdateZombieGatlingHead(zombie);
    }

    if (zombie->mHasHead) {//判断是否hasHead
        int mPhaseCounter = zombie->mPhaseCounter;
        LawnApp *lawnApp = zombie->mApp;
        if (mPhaseCounter == 100) {
            Reanimation *mSpecialHeadReanim = LawnApp_ReanimationGet(lawnApp,zombie->mSpecialHeadReanimID);
            Reanimation_PlayReanim(mSpecialHeadReanim, "anim_shooting", ReanimLoopType::PlayOnceAndHold, 20, 38.0f);
        } else if (mPhaseCounter == 18 || mPhaseCounter == 35 || mPhaseCounter == 51 || mPhaseCounter == 68) {
            LawnApp_PlayFoley(lawnApp, FoleyType::Throw);
            Reanimation *mBodyReanim = LawnApp_ReanimationGet(lawnApp, zombie->mBodyReanimID);
            int index = Reanimation_FindTrackIndexById(mBodyReanim, *ReanimTrackId_anim_head1_Addr);
            ReanimatorTransform aTransForm;
            ReanimatorTransform_ReanimatorTransform(&aTransForm);
            Reanimation_GetCurrentTransform(mBodyReanim, index, &aTransForm);

            float aOriginX = zombie->mPosX + aTransForm.mTransX - 9.0f;
            float aOriginY = zombie->mPosY + aTransForm.mTransY + 6.0f - zombie->mAltitude;

            if (zombie->mMindControlled) {//如果是mMindControlled
                aOriginX += 90.0f * zombie->mScaleZombie;
                Projectile* projectile = Board_AddProjectile(zombie->mBoard,aOriginX,aOriginY,zombie->mRenderOrder,zombie->mRow, ProjectileType::Pea);
                projectile->mDamageRangeFlags = 1;
            } else {
                Projectile*projectile = Board_AddProjectile(zombie->mBoard,aOriginX,aOriginY,zombie->mRenderOrder,zombie->mRow, ProjectileType::ZombiePea);
                projectile->mMotionType = ProjectileMotion::Backwards;
            }
        } else if (mPhaseCounter <= 0) {
            Reanimation *reanimation = LawnApp_ReanimationGet(lawnApp, zombie->mSpecialHeadReanimID);
            Reanimation_PlayReanim(reanimation, "anim_head_idle", ReanimLoopType::PlayOnceAndHold, 20, 15.0f);
            zombie->mPhaseCounter = 150;
        }
    }
}

void Zombie_BurnRow(Zombie* zombie, int theRow) {
    //辣椒僵尸被魅惑后的爆炸函数
    int theDamageRangeFlags = 127;
    Board *board = zombie->mBoard;
    Zombie* tmpZombie = NULL;
    while (Board_IterateZombies(board, &tmpZombie)) {
        if (tmpZombie != zombie && !tmpZombie->mDead) {
            int num = tmpZombie->mRow - theRow;
            if (tmpZombie->mZombieType == ZombieType::Boss) {
                num = 0;
            }
            if (num == 0 && Zombie_EffectedByDamage(tmpZombie, theDamageRangeFlags)) {
                Zombie_RemoveColdEffects(tmpZombie);
                Zombie_ApplyBurn(tmpZombie);
            }
        }
    }

     GridItem* tmpGridItem = NULL;
    while (Board_IterateGridItems(board, &tmpGridItem)) {
        if (tmpGridItem->mGridY == theRow && tmpGridItem->mGridItemType == GridItemType::Ladder) {
            GridItem_GridItemDie(tmpGridItem);
        }
    }
}

void (*old_Zombie_UpdateZombieJalapenoHead)(Zombie *zombie);

void Zombie_UpdateZombieJalapenoHead(Zombie *zombie) {
    //修复辣椒僵尸被魅惑后爆炸依然伤害植物的BUG
    if (!zombie->mMindControlled) return old_Zombie_UpdateZombieJalapenoHead(zombie);
    if (zombie->mHasHead && zombie->mPhaseCounter == 0) {
        LawnApp *lawnApp = zombie->mApp;
        Board *board = zombie->mBoard;
        int mRow = zombie->mRow;
        LawnApp_PlayFoley(lawnApp, FoleyType::JalapenoIgnite);
        LawnApp_PlayFoley(lawnApp, FoleyType::Juicy);
        Board_DoFwoosh(board, mRow);
        Board_ShakeBoard(board, 3, -4);
        Zombie_BurnRow(zombie, mRow);
        Zombie_DieNoLoot(zombie);
        return;
    }
}

bool showZombieBodyHealth = false;
bool showGargantuarHealth = false;
bool showHelmAndShieldHealth = false;



void (*old_Zombie_Draw)(Zombie *zombie, Sexy::Graphics *graphics);

void Zombie_Draw(Zombie *zombie, Sexy::Graphics *graphics) {
    //根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_Draw函数执行完后额外绘制血量文本。
    old_Zombie_Draw(zombie, graphics);
    int drawHeightOffset = 0;
    int holder[1];
    ZombieType::ZombieType mZombieType = zombie->mZombieType;
    if (showZombieBodyHealth || (showGargantuarHealth && (mZombieType == ZombieType::Gargantuar || mZombieType == ZombieType::RedeyeGargantuar))) {//如果玩家开了"僵尸显血"
        Sexy_StrFormat(holder, "%d/%d", zombie->mBodyHealth, zombie->mBodyMaxHealth);
        Sexy_Graphics_SetColor(graphics, &white);
        Sexy_Graphics_SetFont(graphics, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
        if (mZombieType == ZombieType::Boss) {
            // 如果是僵王,将血量绘制到僵王头顶。从而修复图鉴中僵王血量绘制位置不正确。
            // 此处仅在图鉴中生效,实战中僵王绘制不走Zombie_Draw()，走Zombie_DrawBossPart()
            graphics->mTransX = 780.0f;
            graphics->mTransY = 240.0f;
        }
        Sexy_Graphics_DrawString(graphics, holder, 0, drawHeightOffset);
        Sexy_String_Delete(holder);
        Sexy_Graphics_SetFont(graphics, NULL);
        drawHeightOffset += 20;
    }
    if (showHelmAndShieldHealth){
        int mHelmHealth = zombie->mHelmHealth;
        int mHelmMaxHealth = zombie->mHelmMaxHealth;
        if (mHelmHealth > 0) {//如果有头盔，绘制头盔血量
            Sexy_StrFormat(holder, "%d/%d", mHelmHealth, mHelmMaxHealth);
            Sexy_Graphics_SetColor(graphics, &yellow);
            Sexy_Graphics_SetFont(graphics, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            Sexy_Graphics_DrawString(graphics, holder, 0, drawHeightOffset);
            Sexy_String_Delete(holder);
            Sexy_Graphics_SetFont(graphics, NULL);
            drawHeightOffset += 20;
        }
        int mShieldHealth = zombie->mShieldHealth;
        int mShieldMaxHealth = zombie->mShieldMaxHealth;
        if (mShieldHealth > 0) {//如果有盾牌，绘制盾牌血量
            Sexy_StrFormat(holder, "%d/%d", mShieldHealth, mShieldMaxHealth);
            Sexy_Graphics_SetColor(graphics, &blue);
            Sexy_Graphics_SetFont(graphics, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            Sexy_Graphics_DrawString(graphics, holder, 0, drawHeightOffset);
            Sexy_String_Delete(holder);
            Sexy_Graphics_SetFont( graphics, NULL);
        }
    }
}

void (*old_Zombie_DrawBossPart)(Zombie *a1, Sexy::Graphics *graphics, int theBossPart);

void Zombie_DrawBossPart(Zombie *zombie, Sexy::Graphics *graphics, int theBossPart) {
    //根据玩家的“僵尸显血”功能是否开启，决定是否在游戏的原始old_Zombie_DrawBossPart函数执行完后额外绘制血量文本。
    old_Zombie_DrawBossPart(zombie, graphics, theBossPart);
    if (theBossPart == 3) {
        // 每次绘制Boss都会调用四次本函数，且theBossPart从0到3依次增加，代表绘制Boss的不同Part。
        // 我们只在theBossPart==3时(绘制最后一个部分时)绘制一次血量，免去每次都绘制。
        if (showZombieBodyHealth) {//如果玩家开了"僵尸显血"
            int holder[1];
            Sexy_StrFormat(holder, "%d/%d", zombie->mBodyHealth, zombie->mBodyMaxHealth);
            Sexy_Graphics_SetColor(graphics, &white);
            Sexy_Graphics_SetFont(graphics, *Sexy_FONT_DWARVENTODCRAFT18_Addr);
            float tmpTransX = graphics->mTransX;
            float tmpTransY = graphics->mTransY;
            graphics->mTransX = 800.0f;
            graphics->mTransY = 200.0f;
            Sexy_Graphics_DrawString(graphics, holder, 0, 0);
            Sexy_String_Delete(holder);
            graphics->mTransX = tmpTransX;
            graphics->mTransY = tmpTransY;
            Sexy_Graphics_SetFont(graphics, NULL);
        }
    }
}

int maidCheats = 0; // 女仆秘籍

int Zombie_GetDancerFrame(Zombie *zombie) {
    if (zombie->mFromWave == -3 || Zombie_IsImmobilizied(zombie))
        return 0;

    // 女仆秘籍
    switch (maidCheats) {
        case 1:
            return 11; // 保持前进 (DancerDancingLeft)
        case 2:
            return 18; // 跳舞 (DancerRaiseLeft1)
        case 3:
            return 12; // 召唤舞伴 (DancerWalkToRaise)
        default:
            break;
    }

    //修复女仆秘籍问题、修复舞王和舞者的跳舞时间不吃高级暂停也不吃倍速
    ZombiePhase::ZombiePhase mZombiePhase = zombie->mZombiePhase;
    int num1 = mZombiePhase == ZombiePhase::DancerDancingIn ? 10 : 20;
    int num2 = mZombiePhase == ZombiePhase::DancerDancingIn ? 110 : 460;
//    return *(_DWORD *) (lawnApp + 2368) % num2 / num1;
    return zombie->mBoard->mMainCounter % num2 / num1;  // 修复女仆秘籍问题
    // 关键就是用mBoard.mMainCounter代替mApp.mAppCounter做计时
}

bool (*old_ZombieTypeCanGoInPool)(ZombieType::ZombieType zombieType);

bool ZombieTypeCanGoInPool(ZombieType::ZombieType zombieType) {
    //修复泳池对战的僵尸们走水路时不攻击植物
    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS && (VSBackGround == 3 || VSBackGround == 4 || VSBackGround == 9)) {
        return true;
    }
    return old_ZombieTypeCanGoInPool(zombieType);
}

void (*old_Zombie_RiseFromGrave)(Zombie *zombie, int gridX, int gridY);

void Zombie_RiseFromGrave(Zombie *zombie, int gridX, int gridY) {
    //修复对战切换场地为泳池后的闪退BUG。但是仅仅是修复闪退，泳池对战还谈不上能玩的程度
    if (zombie->mApp->mGameMode == GameMode::TwoPlayerVS) {

        Board *board = zombie->mBoard;
        if (board->mPlantRow[gridY] == PlantRowType::Pool) {
//                if (old_ZombieTypeCanGoInPool(mZombieType)) {
            Zombie_DieNoLoot(zombie);
            Board_AddZombieInRow(board, zombie->mZombieType, gridY, board->mCurrentWave, 1);
            return;
//                }
        }

        BackgroundType::BackgroundType tmp = board->mBackgroundType;
        board->mBackgroundType = BackgroundType::Num1Day;
        old_Zombie_RiseFromGrave(zombie, gridX, gridY);
        board->mBackgroundType = tmp;
        return;

    }
    old_Zombie_RiseFromGrave(zombie, gridX, gridY);
}

int boardEdgeAdjust = 0;

void Zombie_CheckForBoardEdge(Zombie *zombie) {
    //修复僵尸正常进家、支持调整僵尸进家线
    if (Zombie_IsWalkingBackwards(zombie) && zombie->mPosX > 850.0f) {
        Zombie_DieNoLoot(zombie);
        return;
    }
    int boardEdge;
    ZombieType::ZombieType mZombieType = zombie->mZombieType;
    if (mZombieType == ZombieType::Polevaulter || mZombieType == ZombieType::Gargantuar || mZombieType == ZombieType::RedeyeGargantuar) {
        //如果是撑杆、巨人、红眼巨人
        boardEdge = -100;
    } else if (mZombieType == ZombieType::Football || mZombieType == ZombieType::Zamboni || mZombieType == ZombieType::Catapult) {
        //如果是橄榄球、冰车、篮球
        boardEdge = -125;
    } else if (mZombieType == ZombieType::Dancer || mZombieType == ZombieType::BackupDancer || mZombieType == ZombieType::Snorkel) {
        //如果是舞王、伴舞、潜水
        boardEdge = -80;
    } else {
        //如果是除上述僵尸外的僵尸
        boardEdge = -50;
    }
    boardEdge -= boardEdgeAdjust;//支持任意调整进家线
    int mX = zombie->mX;
    bool mHasHead = zombie->mHasHead;
    if (mX <= boardEdge && mHasHead) {
        if (LawnApp_IsIZombieLevel(zombie->mApp)) {
            Zombie_DieNoLoot(zombie);
        } else {
            Board_ZombiesWon(zombie->mBoard, zombie);
        }
    }
    if (mX <= boardEdge + 70 && !mHasHead) {
        Zombie_TakeDamage(zombie, 1800, 9u);
    }
}

void (*old_Zombie_EatPlant)(Zombie *a, Plant *a2);

void Zombie_EatPlant(Zombie *zombie, Plant *plant) {
    //修复正向出土的矿工不上梯子
    ZombiePhase::ZombiePhase mZombiePhase = zombie->mZombiePhase;
    if (mZombiePhase == ZombiePhase::DancerDancingIn) {
        zombie->mPhaseCounter = 1;
        return;
    }
    if (zombie->mYuckyFace) {
        return;
    }
    int mPlantCol = plant->mPlantCol;
    int mRow = plant->mRow;
    if (Board_GetLadderAt(zombie->mBoard, mPlantCol, mRow) != NULL && zombie->mZombieType == ZombieType::Digger && mZombiePhase == ZombiePhase::DiggerWalkingWithoutAxe && !Zombie_IsWalkingBackwards(zombie)) {
        Zombie_StopEating(zombie);
        if (zombie->mZombieHeight == ZombieHeight::ZombieNormal && zombie->mUseLadderCol != mPlantCol) {
            zombie->mZombieHeight = ZombieHeight::UpLadder;
            zombie->mUseLadderCol = mPlantCol;
        }
        return;
    }
    return old_Zombie_EatPlant(zombie, plant);
}

void (*old_Zombie_DetachShield)(Zombie *zombie);

void Zombie_DetachShield(Zombie *zombie) {
    //修复梯子僵尸断手后掉梯子时手会恢复的BUG。
    bool mHasArm = zombie->mHasArm;
    ShieldType::ShieldType mShieldType = zombie->mShieldType;
    old_Zombie_DetachShield(zombie);
    if (mShieldType == ShieldType::Ladder && !mHasArm) {
        Zombie_ReanimShowPrefix(zombie,"Zombie_outerarm", -1);
    }
}

void Zombie_BossSpawnAttack(Zombie *zombie) {
    //修复泳池僵王为六路放僵尸时闪退
    Zombie_RemoveColdEffects(zombie);
    zombie->mZombiePhase = ZombiePhase::BossSpawning;
    int mBossMode = zombie->mBossMode;
    if (mBossMode == 0) {
        zombie->mSummonCounter = RandRangeInt(450, 550);
    } else if (mBossMode == 1) {
        zombie->mSummonCounter = RandRangeInt(350, 450);
    } else if (mBossMode == 2) {
        zombie->mSummonCounter = RandRangeInt(150, 250);
    }
    zombie->mTargetRow = Board_PickRowForNewZombie(zombie->mBoard, 0);
    switch (zombie->mTargetRow) {
        case 0:
            Zombie_PlayZombieReanim(zombie, "anim_spawn_1", 3, 20, 12.0);
            break;
        case 1:
            Zombie_PlayZombieReanim(zombie, "anim_spawn_2", 3, 20, 12.0);
            break;
        case 2:
            Zombie_PlayZombieReanim(zombie, "anim_spawn_3", 3, 20, 12.0);
            break;
        case 3:
            Zombie_PlayZombieReanim(zombie, "anim_spawn_4", 3, 20, 12.0);
            break;
        default:
            Zombie_PlayZombieReanim(zombie, "anim_spawn_5", 3, 20, 12.0);
            break;
    }
    LawnApp_PlayFoley(zombie->mApp, FoleyType::HydraulicShort);
}

void Zombie_AddButter(Zombie* zombieUnderButter){
    if (Zombie_CanBeFrozen(zombieUnderButter) && zombieUnderButter->mZombieType != ZombieType::Boss) {
        //Ban冰车 跳跳 僵王 飞翔的气球 跳跃的撑杆 即将跳水的潜水 等等
        if (zombieUnderButter->mButteredCounter <= 100) {
            if (zombieUnderButter->mButteredCounter == 0) {
                LawnApp_PlayFoley(zombieUnderButter->mApp, FoleyType::Butter);
            }
            Zombie_ApplyButter(zombieUnderButter);
        }
    }
}

void Zombie_SetZombatarReanim(Zombie* zombie) {
    PlayerInfo* playerInfo = zombie->mApp->mPlayerInfo;
    if (!playerInfo->mZombatarEnabled) return;
    Reanimation* aBodyReanim = LawnApp_ReanimationGet(zombie->mApp,zombie->mBodyReanimID);
    ReanimatorTrackInstance* aHeadTrackInstance = Reanimation_GetTrackInstanceByName(aBodyReanim, "anim_head1");
    aHeadTrackInstance->mImageOverride = *Sexy_IMAGE_BLANK_Addr;
    Reanimation *aZombatarHeadReanim = LawnApp_AddReanimation(zombie->mApp, 0, 0, 0, ReanimationType::ZombatarHead);
    Reanimation_SetZombatarHats(aZombatarHeadReanim, playerInfo->mZombatarHat,playerInfo->mZombatarHatColor);
    Reanimation_SetZombatarHair(aZombatarHeadReanim,playerInfo->mZombatarHair,playerInfo->mZombatarHairColor);
    Reanimation_SetZombatarFHair(aZombatarHeadReanim,playerInfo->mZombatarFacialHair,playerInfo->mZombatarFacialHairColor);
    Reanimation_SetZombatarAccessories(aZombatarHeadReanim,playerInfo->mZombatarAccessory,playerInfo->mZombatarAccessoryColor);
    Reanimation_SetZombatarEyeWear(aZombatarHeadReanim,playerInfo->mZombatarEyeWear,playerInfo->mZombatarEyeWearColor);
    Reanimation_SetZombatarTidBits(aZombatarHeadReanim, playerInfo->mZombatarTidBit, playerInfo->mZombatarTidBitColor);
    Reanimation_PlayReanim(aZombatarHeadReanim, "anim_head_idle", ReanimLoopType::Loop, 0, 15.0);
    Reanimation_AssignRenderGroupToTrack(aZombatarHeadReanim, "anim_hair", -1);
    zombie->mBossFireBallReanimID = LawnApp_ReanimationGetID(zombie->mApp, aZombatarHeadReanim);
    AttachEffect* attachEffect = AttachReanim(&aHeadTrackInstance->mAttachmentID, aZombatarHeadReanim, 0.0f, 0.0f);
    TodScaleRotateTransformMatrix(&attachEffect->mOffset, -20.0, -1.0, 0.2, 1.0, 1.0);
    Zombie_ReanimShowPrefix(zombie, "anim_hair", -1);
    Zombie_ReanimShowPrefix(zombie, "anim_head2", -1);
}

inline bool Zombie_IsZombatarZombie(ZombieType::ZombieType type) {
    // return type == ZombieType::Flag || type == ZombieType::Normal || type == ZombieType::TrafficCone || type == ZombieType::Door || type == ZombieType::TrashBin || type == ZombieType::Pail || type == ZombieType::DuckyTube;
    return type == ZombieType::Flag;
}

int zombieSetScale = 0;

void (*old_Zombie_ZombieInitialize)(Zombie *zombie,int theRow,ZombieType::ZombieType theType,bool theVariant,Zombie *theParentZombie,int theFromWave,bool isVisible);

void Zombie_ZombieInitialize(Zombie *zombie,int theRow,ZombieType::ZombieType theType,bool theVariant,Zombie *theParentZombie,int theFromWave, bool isVisible) {
    // TODO: 修复高级暂停时放的IZ僵尸只显示虚影
    old_Zombie_ZombieInitialize(zombie,theRow,theType,theVariant,theParentZombie,theFromWave,isVisible);
//    if (requestPause) {
//        old_Zombie_Update(zombie);
//    }
    if (zombieSetScale != 0 && zombie->mZombieType != ZombieType::Boss) {
        zombie->mScaleZombie = 0.2 * zombieSetScale;
        Zombie_UpdateAnimationSpeed(zombie);
        float theRatio = zombie->mScaleZombie * zombie->mScaleZombie;
        zombie->mBodyHealth *= theRatio;
        zombie->mHelmHealth *= theRatio;
        zombie->mShieldHealth *= theRatio;
        zombie->mFlyingHealth *= theRatio;
        zombie->mBodyMaxHealth = zombie->mBodyHealth;
        zombie->mHelmMaxHealth = zombie->mHelmHealth;
        zombie->mShieldMaxHealth = zombie->mShieldHealth;
        zombie->mFlyingMaxHealth = zombie->mFlyingHealth;
    }

    if (Zombie_IsZombatarZombie(theType) && theFromWave != -3) {
        Zombie_SetZombatarReanim(zombie);
    }
}

ZombieDefinition gZombieTrashBinDef = {ZombieType::TrashBin,ReanimationType::Zombie,1,99,1,4000,"TRASHCAN_ZOMBIE"};

ZombieDefinition & (*old_GetZombieDefinition)(ZombieType::ZombieType type);

ZombieDefinition &GetZombieDefinition(ZombieType::ZombieType type) {
    if (type == ZombieType::TrashBin) return gZombieTrashBinDef;
    return old_GetZombieDefinition(type);
}

void (*old_Zombie_DieNoLoot)(Zombie*);

void Zombie_DieNoLoot(Zombie* zombie) {
    if (zombie->mZombieType == ZombieType::Gargantuar && zombie->mBoard != NULL && zombie->mApp->mGameScene == GameScenes::Playing) {
        Board_GrantAchievement(zombie->mBoard ,AchievementId::ACHIEVEMENT_GARG, true);
    }

    if (Zombie_IsZombatarZombie(zombie->mZombieType)) {
        // 大头贴
        LawnApp_RemoveReanimation(zombie->mApp, zombie->mBossFireBallReanimID);
    }
    old_Zombie_DieNoLoot(zombie);
}

void Zombie_DrawBungeeCord(Zombie *zombie, Sexy::Graphics *graphics, int theOffsetX, int theOffsetY) {
    // 修复在Boss关的蹦极绳子不绑在Boss手上
    int aCordCelHeight = Sexy_Image_GetCelHeight(*Sexy_IMAGE_BUNGEECORD_Addr) * zombie->mScaleZombie;
    float aPosX = 0.0f;
    float aPosY = 0.0f;
    Zombie_GetTrackPosition(zombie,"Zombie_bungi_body", &aPosX, &aPosY);
    bool aSetClip = false;
    if (Zombie_IsOnBoard(zombie) && LawnApp_IsFinalBossLevel(zombie->mApp)) {
        Zombie *bossZombie = Board_GetBossZombie(zombie->mBoard);
        int aClipAmount = 55;
        if (bossZombie->mZombiePhase == ZombiePhase::BossBungeesLeave) {
            Reanimation *reanimation = LawnApp_ReanimationGet(zombie->mApp, bossZombie->mBodyReanimID);
            aClipAmount = TodAnimateCurveFloatTime(0.0f, 0.2f, reanimation->mAnimTime, 55.0f, 0.0f, TodCurves::Linear);
        }
        if (zombie->mTargetCol >= bossZombie->mTargetCol) { // ">" ------ > ">="，修复第一根手指蹦极不绑在手上
            if (zombie->mTargetCol > bossZombie->mTargetCol) {
                aClipAmount += 60;     // 55 ---- > 115，修复第2、3根手指蹦极不绑在手上
            }
            Sexy_Graphics_SetClipRect(graphics, -graphics->mTransX, aClipAmount - graphics->mTransY, 800, 600);
            aSetClip = true;
        }
    }

    for (float y = aPosY - aCordCelHeight; y > - 60 - aCordCelHeight; y -= aCordCelHeight) {
        float thePosX = theOffsetX + 61.0f - 4.0f / zombie->mScaleZombie;
        float thePosY = y - zombie->mPosY;
        TodDrawImageScaledF(graphics, *Sexy_IMAGE_BUNGEECORD_Addr, thePosX, thePosY, zombie->mScaleZombie, zombie->mScaleZombie);
    }
    if (aSetClip) {
        Sexy_Graphics_ClearClipRect(graphics);
    }
}

bool Zombie_IsTangleKelpTarget(Zombie *zombie) {
    // 修复水草拉僵尸有概率失效

    if (!Board_StageHasPool(zombie->mBoard)) {
        return false;
    }
    if (zombie->mZombieHeight == ZombieHeight::DraggedUnder) {
        return true;
    }
    Plant *aPlant = NULL;
    while (Board_IteratePlants(zombie->mBoard, &aPlant)) {
        if (!aPlant->mDead && aPlant->mSeedType == SeedType::Tanglekelp && aPlant->mTargetZombieID == zombie->mZombieID) {
            return true;
        }
    }
    return false;
}

void (*old_Zombie_DrawReanim)(Zombie *zombie, Sexy::Graphics *graphics, ZombieDrawPosition* zombieDrawPosition,int theBaseRenderGroup);

void Zombie_DrawReanim(Zombie *zombie, Sexy::Graphics *graphics, ZombieDrawPosition* zombieDrawPosition,int theBaseRenderGroup) {
    //大头贴专门Draw一下
    old_Zombie_DrawReanim(zombie,graphics,zombieDrawPosition,theBaseRenderGroup);
    if (zombie->mZombieType == ZombieType::Flag) {
        Reanimation *reanimation = LawnApp_ReanimationTryToGet(zombie->mApp, zombie->mBossFireBallReanimID);
        if (reanimation != NULL) {
            Reanimation_Draw(reanimation, graphics);
        }
    }
}

void (*old_Zombie_DropHead)(Zombie *zombie,unsigned int a2);

void Zombie_DropHead(Zombie *zombie, unsigned int a2) {
    // 负责 大头贴掉头
    // TODO:大头贴僵尸掉头时掉饰品(掉hat和eyeWear)
    old_Zombie_DropHead(zombie, a2);
    if (Zombie_IsZombatarZombie(zombie->mZombieType)) {
        Reanimation *reanimation = LawnApp_ReanimationTryToGet(zombie->mApp, zombie->mBossFireBallReanimID);
        if (reanimation != NULL) {
            int index[2] = {Reanimation_GetZombatarHatTrackIndex(reanimation),
                            Reanimation_GetZombatarEyeWearTrackIndex(reanimation)};
            for (int i = 0; i < 2; ++i) {
                if (index[i] == -1) continue;
                ReanimatorTrackInstance* reanimatorTrackInstance = reanimation->mTrackInstances + index[i];
                ReanimatorTrack *reanimatorTrack = reanimation->mDefinition->mTracks + index[i];
                SexyTransform2D aSexyTransform2D;
                Reanimation_GetTrackMatrix(reanimation,index[i], &aSexyTransform2D);
                float aPosX = zombie->mPosX + aSexyTransform2D.m[0][2];
                float aPosY = zombie->mPosY + aSexyTransform2D.m[1][2];
                TodParticleSystem* todParticleSystem = LawnApp_AddTodParticle(zombie->mApp, aPosX, aPosY, zombie->mRenderOrder + 1, ParticleEffect::ZombieHead);
                TodParticleSystem_OverrideColor(todParticleSystem, NULL, &reanimatorTrackInstance->mTrackColor);
                TodParticleSystem_OverrideImage(todParticleSystem, NULL, reanimatorTrack->mTransforms[0].mImage);
            }
            LawnApp_RemoveReanimation(zombie->mApp, zombie->mBossFireBallReanimID);
            zombie->mBossFireBallReanimID = 0;
        }
    }
}

void Zombie_SetupLostArmReanim(Zombie* zombie) {
    switch (zombie->mZombieType)
    {
        case ZombieType::Football:
            Zombie_ReanimShowPrefix(zombie,"Zombie_football_leftarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie,"Zombie_football_leftarm_hand", -1);
            break;
        case ZombieType::Newspaper:
            Zombie_ReanimShowTrack(zombie,"Zombie_paper_hands", -1);
            Zombie_ReanimShowTrack(zombie,"Zombie_paper_leftarm_lower", -1);
            break;
        case ZombieType::Polevaulter:
            Zombie_ReanimShowTrack(zombie,"Zombie_polevaulter_outerarm_lower", -1);
            Zombie_ReanimShowTrack(zombie,"Zombie_outerarm_hand", -1);
            break;
        case ZombieType::Dancer:
            Zombie_ReanimShowPrefix(zombie,"Zombie_disco_outerarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie,"Zombie_disco_outerhand_point", -1);
            Zombie_ReanimShowPrefix(zombie,"Zombie_disco_outerhand", -1);
            Zombie_ReanimShowPrefix(zombie,"Zombie_disco_outerarm_upper", -1);
            break;
        case ZombieType::BackupDancer:
            Zombie_ReanimShowPrefix(zombie,"Zombie_disco_outerarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie,"Zombie_disco_outerhand", -1);
            break;
        default:
            Zombie_ReanimShowPrefix(zombie,"Zombie_outerarm_lower", -1);
            Zombie_ReanimShowPrefix(zombie,"Zombie_outerarm_hand", -1);
            break;
    }
    Reanimation* reanimation = LawnApp_ReanimationTryToGet(zombie->mApp,zombie->mBodyReanimID);
    if (reanimation != NULL)
    {
        switch (zombie->mZombieType)
        {
            case ZombieType::Football:
                Reanimation_SetImageOverride(reanimation,"zombie_football_leftarm_hand", *Sexy_IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2_Addr);
                break;
            case ZombieType::Newspaper:
                Reanimation_SetImageOverride(reanimation,"Zombie_paper_leftarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2_Addr);
                break;
            case ZombieType::Polevaulter:
                Reanimation_SetImageOverride(reanimation,"Zombie_polevaulter_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::Balloon:
                Reanimation_SetImageOverride(reanimation,"zombie_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::Imp:
                Reanimation_SetImageOverride(reanimation,"Zombie_imp_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE_Addr);
                break;
            case ZombieType::Digger:
                Reanimation_SetImageOverride(reanimation,"Zombie_digger_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::Bobsled:
                Reanimation_SetImageOverride(reanimation,"Zombie_dolphinrider_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::JackInTheBox:
                Reanimation_SetImageOverride(reanimation,"Zombie_jackbox_outerarm_lower", *Sexy_IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2_Addr);
                break;
            case ZombieType::Snorkel:
                Reanimation_SetImageOverride(reanimation,"Zombie_snorkle_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::DolphinRider:
                Reanimation_SetImageOverride(reanimation,"Zombie_dolphinrider_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::Pogo:
                Reanimation_SetImageOverride(reanimation,"Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2_Addr);
                Reanimation_SetImageOverride(reanimation,"Zombie_pogo_stickhands", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2_Addr);
                Reanimation_SetImageOverride(reanimation,"Zombie_pogo_stick", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2_Addr);
                Reanimation_SetImageOverride(reanimation,"Zombie_pogo_stick2", *Sexy_IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2_Addr);
                break;
            case ZombieType::Flag:
            {
                Reanimation_SetImageOverride(reanimation,"Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_Addr);
                Reanimation* reanimation2 = LawnApp_ReanimationTryToGet(zombie->mApp,zombie->mSpecialHeadReanimID);
                if (reanimation2 != NULL)
                {
                    Reanimation_SetImageOverride(reanimation2,"Zombie_flag", *Sexy_IMAGE_REANIM_ZOMBIE_FLAG3_Addr);
                }
                break;
            }
            case ZombieType::Dancer:
                Reanimation_SetImageOverride(reanimation,"Zombie_disco_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::BackupDancer:
                Reanimation_SetImageOverride(reanimation,"Zombie_disco_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::Ladder:
                Reanimation_SetImageOverride(reanimation,"Zombie_ladder_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2_Addr);
                break;
            case ZombieType::Yeti:
                Reanimation_SetImageOverride(reanimation,"Zombie_yeti_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2_Addr);
                break;
            default:
                Reanimation_SetImageOverride(reanimation,"Zombie_outerarm_upper", *Sexy_IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_Addr);
                break;
        }
    }
}
#endif //PVZ_TV_1_1_5_ZOMBIE_CPP
