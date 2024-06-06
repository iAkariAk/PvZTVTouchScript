//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_PLANT_CPP
#define PVZ_TV_1_1_5_PLANT_CPP

#include "../Graphics/Graphics.h"
#include "Plant.h"
#include "../Board/Board.h"
#include "../SpecialConstraints.h"
#include "HookGame/Misc/Misc.h"
#include "HookGame/LawnApp/LawnApp.h"
#include "HookGame/HookAddr.h"
#include "HookGame/Reanimation/Reanimation.h"
#include "HookGame/Challenge/Challenge.h"
#include "HookGame/GlobalVariable.h"
#include "HookGame/CutScene/CutScene.h"

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

void Plant_DrawSeedType(Sexy::Graphics *graphics, SeedType::SeedType theSeedType,
                        SeedType::SeedType theImitaterType,
                        DrawVariation::DrawVariation drawVariation,
                        float thePosX, float thePosY) {
    // 用于绘制卡槽内的模仿者SeedPacket变白效果、模仿者变身后的植物被压扁的白色效果、模仿者变身前被压扁后绘制模仿者自己而非变身后的植物。
    int v38 = ((int*)graphics)[9];
    int v10 = ((int*)graphics)[8];
    int v11 = ((int*)graphics)[4];
    int v39 = ((int*)graphics)[10];
    int v12 = ((int*)graphics)[5];
    int v13 = ((int*)graphics)[6];
    int v40 = ((int*)graphics)[11];
    int v14 = ((int*)graphics)[7];
    int v15 = ((int*)graphics)[2];
    int v16 = ((int*)graphics)[3];
    int *theColor = Sexy_Graphics_GetColor(graphics);
    int v18 = theColor[1];
    int v19 = theColor[2];
    int v20 = theColor[3];
    Color color;
    color.mRed = *theColor;
    color.mGreen = v18;
    color.mBlue = v19;
    color.mAlpha = v20;
    bool ColorizeImages = Sexy_Graphics_GetColorizeImages(graphics);
    SeedType::SeedType theSeedType2 = theSeedType;

    if ((theSeedType == theImitaterType && theImitaterType != SeedType::None) || // seedPacket中的灰色模仿者卡片在冷却完成后
        (theImitaterType == SeedType::Imitater && theSeedType != SeedType::None)) {// 模仿者变身之后的植物被压扁
        switch (theSeedType2) {
            case SeedType::Potatomine:
            case SeedType::Hypnoshroom:
            case SeedType::Lilypad:
            case SeedType::Squash:
            case SeedType::Garlic:
                drawVariation = DrawVariation::ImitaterLess;
                break;
            case SeedType::Imitater:
                drawVariation = DrawVariation::Normal;
                break;
            default:
                drawVariation = DrawVariation::Imitater;
                break;
        }
    }
    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
    float v24, v25;
    if (lawnApp->mGameMode == GameMode::ChallengeBigTime &&
        (theSeedType2 == SeedType::Sunflower || theSeedType2 == SeedType::Wallnut ||
         theSeedType2 == SeedType::Marigold)) {
        v24 = -40.0;
        v25 = -20.0;
        graphics->mScaleX = graphics->mScaleX * 1.5;
        graphics->mScaleY = graphics->mScaleY * 1.5;
    } else {
        v24 = 0.0;
        v25 = 0.0;
    }
    if (theSeedType2 == SeedType::Leftpeater) {
        v25 = v25 + graphics->mScaleX * 80.0;
        graphics->mScaleX = -graphics->mScaleX;
    }
    if (Challenge_IsZombieSeedType(theSeedType2)) {
        ZombieType::ZombieType theZombieType = Challenge_IZombieSeedTypeToZombieType(theSeedType2);
        if (theZombieType != ZombieType::Invalid) {
            ReanimatorCache_DrawCachedZombie(lawnApp->mReanimatorCache, graphics,thePosX, thePosY, theZombieType);
        }
        return;
    } else {
        PlantDefinition plantDefinition = GetPlantDefinition(theSeedType2);
        if (theSeedType2 == SeedType::GiantWallnut) {
            graphics->mScaleX = graphics->mScaleX * 1.4;
            graphics->mScaleY = graphics->mScaleY * 1.4;
            TodDrawImageScaledF(graphics,*Sexy_IMAGE_REANIM_WALLNUT_BODY_Addr,
                                thePosX - 53.0, thePosY - 56.0, graphics->mScaleX,
                                graphics->mScaleY);
        } else if (plantDefinition.mReanimationType == -1) {
            int v29;
            if (theSeedType2 == SeedType::Kernelpult)
                v29 = 2;
            else
                v29 = theSeedType2 == SeedType::Twinsunflower;

            Sexy::Image *Image = Plant_GetImage(theSeedType2);
            int v31 = Image->mNumCols;
            int v32;
            if (v31 > 2)
                v32 = 2;
            else
                v32 = v31 - 1;
            TodDrawImageCelScaledF(graphics, Image, v25 + thePosX, v24 + thePosY, v32, v29,
                                   graphics->mScaleX, graphics->mScaleY);
        } else {
            ReanimatorCache_DrawCachedPlant(lawnApp->mReanimatorCache, graphics,v25 + thePosX, v24 + thePosY, theSeedType2, drawVariation);
        }
    }
    ((int*)graphics)[8] = v10;
    ((int*)graphics)[4] = v11;
    ((int*)graphics)[9] = v38;
    ((int*)graphics)[5] = v12;
    ((int*)graphics)[6] = v13;
    ((int*)graphics)[10] = v39;
    ((int*)graphics)[7] = v14;
    ((int*)graphics)[2] = v15;
    ((int*)graphics)[11] = v40;
    ((int*)graphics)[3] = v16;
    Sexy_Graphics_SetColor(graphics, &color);
    Sexy_Graphics_SetColorizeImages(graphics, ColorizeImages);
}

bool showPlantHealth = false;
bool showNutGarlicSpikeHealth = false;

void (*old_Plant_Draw)(Plant *plant, Sexy::Graphics *graphics);

void Plant_Draw(Plant *plant, Sexy::Graphics *graphics) {
    //根据玩家的“植物显血”功能是否开启，决定是否在游戏的原始old_Plant_Draw函数执行完后额外绘制血量文本。

    SeedType::SeedType mSeedType = plant->mSeedType;
    Sexy_Graphics_SetDrawMode(graphics, DrawMode::DRAWMODE_NORMAL);
    int theCelRow = 0;
    float num = 0.0f;
    float num2 = PlantDrawHeightOffset(plant->mBoard, 0, mSeedType,plant->mPlantCol, plant->mRow);
    if (Plant_IsFlying(mSeedType) && plant->mSquished)
    {
        num2 += 30.0f;
    }
    int theCelCol = plant->mFrame;
    Sexy::Image* image = Plant_GetImage(mSeedType);
    if (plant->mSquished)
    {
        if (mSeedType == SeedType::Flowerpot)
        {
            num2 -= 15.0f;
        }
        if (mSeedType == SeedType::InstantCoffee)
        {
            num2 -= 20.0f;
        }
        float ratioSquished = 0.5f;
        Sexy_Graphics_SetScale(graphics, 1.0f, ratioSquished, 0.0f, 0.0f);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        Color color = {255, 255, 255, (int)(255.0f * std::min(1.0f, plant->mDisappearCountdown / 100.0f))};
        Sexy_Graphics_SetColor(graphics, &color);
        Plant_DrawSeedType(graphics, mSeedType, plant->mImitaterType, DrawVariation::Normal, num, num2 + 85.0f * (1 - ratioSquished));
        Sexy_Graphics_SetScale(graphics, 1.0f, 1.0f, 0.0f, 0.0f);
        Sexy_Graphics_SetColorizeImages(graphics, false);
        return;
    }
    bool flag = false;
    Plant* thePlant = NULL;
    if (Plant_IsOnBoard(plant))
    {
        thePlant = Board_GetPumpkinAt(plant->mBoard, plant->mPlantCol, plant->mRow);
        if (thePlant != NULL)
        {
            Plant* plant2 = Board_GetTopPlantAt(plant->mBoard, plant->mPlantCol, plant->mRow, TopPlant::OnlyNormalPosition);
            if (plant2 != NULL && plant2->mRenderOrder > thePlant->mRenderOrder)
            {
                plant2 = NULL;
            }
            if (plant2 != NULL && plant2->mOnBungeeState == PlantOnBungeeState::GettingGrabbedByBungee)
            {
                plant2 = NULL;
            }
            if (plant2 == plant)
            {
                flag = true;
            }
            if (plant2 == NULL && mSeedType == SeedType::Pumpkinshell)
            {
                flag = true;
            }
        }
        else if (mSeedType == SeedType::Pumpkinshell)
        {
            flag = true;
            thePlant = plant;
        }
    }
    else if (mSeedType == SeedType::Pumpkinshell)
    {
        flag = true;
        thePlant = plant;
    }

    Plant_DrawShadow(plant,graphics, num, num2);

    if (Plant_IsFlying(mSeedType))
    {
        int num3;
        if (Plant_IsOnBoard(plant))
        {
            num3 = plant->mBoard->mMainCounter;
        }
        else
        {
            num3 = plant->mApp->mAppCounter;
        }
        float num4 = (num3 + plant->mRow * 97 + plant->mPlantCol * 61) * 0.03f;
        float num5 = sin(num4) * 2.0f;
        num2 += num5;
    }
    if (flag)
    {
        Reanimation* reanimation = LawnApp_ReanimationGet(plant->mApp,thePlant->mBodyReanimID);
        Sexy::Graphics newGraphics;
        Sexy_Graphics_Graphics(&newGraphics, graphics);
        newGraphics.mTransX += thePlant->mX - plant->mX;
        newGraphics.mTransY += thePlant->mY - plant->mY;
        Reanimation_DrawRenderGroup(reanimation, &newGraphics, 1);
        Sexy_Graphics_Delete2(&newGraphics);
    }
    num += plant->mShakeOffsetX;
    num2 += plant->mShakeOffsetY;
    if (Plant_IsInPlay(plant) && LawnApp_IsIZombieLevel(plant->mApp))
    {
       Challenge_IZombieDrawPlant(plant->mBoard->mChallenge,graphics, plant);
    }
    else if (plant->mBodyReanimID != NULL)
    {
        Reanimation* reanimation2 = LawnApp_ReanimationTryToGet(plant->mApp,plant->mBodyReanimID);
        if (reanimation2 != NULL)
        {
//            if (plant->mGloveGrabbed)
//            {
//                Sexy_Graphics_SetColorizeImages(graphics,true);
//                Color color = {150, 255, 150, 255};
//                Sexy_Graphics_SetColor(graphics,&color);
//            }
            Reanimation_DrawRenderGroup(reanimation2, graphics, 0);
//            if (plant->mGloveGrabbed)
//            {
//                Sexy_Graphics_SetColorizeImages(graphics,false);
//            }
        }
    }
    else
    {
        SeedType::SeedType seedType = SeedType::None;
        SeedType::SeedType seedType2 = SeedType::None;
        if (plant->mBoard != NULL)
        {
            seedType = Board_GetSeedTypeInCursor(plant->mBoard, 0);
            seedType2 = Board_GetSeedTypeInCursor(plant->mBoard, 1);
        }
        if ((Plant_IsPartOfUpgradableTo(plant,seedType) && Board_CanPlantAt(plant->mBoard,plant->mPlantCol, plant->mRow, seedType) == PlantingReason::Ok) || (Plant_IsPartOfUpgradableTo(plant,seedType2) && Board_CanPlantAt(plant->mBoard,plant->mPlantCol, plant->mRow, seedType2) == PlantingReason::Ok))
        {
            Sexy_Graphics_SetColorizeImages(graphics,true);
            Color color;
            GetFlashingColor(&color, plant->mBoard->mMainCounter, 90);
            Sexy_Graphics_SetColor(graphics, &color);
        }
        else if ((seedType == SeedType::Cobcannon && Board_CanPlantAt(plant->mBoard,plant->mPlantCol - 1, plant->mRow, seedType) == PlantingReason::Ok) || (seedType2 == SeedType::Cobcannon && Board_CanPlantAt(plant->mBoard,plant->mPlantCol - 1, plant->mRow, seedType2) == PlantingReason::Ok))
        {
            Sexy_Graphics_SetColorizeImages(graphics,true);
            Color color;
            GetFlashingColor(&color, plant->mBoard->mMainCounter, 90);
            Sexy_Graphics_SetColor(graphics, &color);
        }
        else if (plant->mBoard != NULL && plant->mBoard->mTutorialState == TutorialState::ShovelDig)
        {
            Sexy_Graphics_SetColorizeImages(graphics,true);
            Color color;
            GetFlashingColor(&color, plant->mBoard->mMainCounter, 90);
            Sexy_Graphics_SetColor(graphics, &color);
        }
        if (image != NULL)
        {
            TodDrawImageCelF(graphics, image, num, num2, theCelCol, theCelRow);
        }
//        if (mSeedType == SeedType::Sprout)
//        {
//            if (plant->mGloveGrabbed)
//            {
//                Sexy_Graphics_SetColorizeImages(graphics,true);
//                Color color ={150, 255, 150, 255};
//                Sexy_Graphics_SetColor(graphics, &color);
//            }
//            TodDrawImageCelF(graphics, AtlasResources.IMAGE_CACHED_MARIGOLD, Constants.ZenGarden_Marigold_Sprout_Offset.X, Constants.ZenGarden_Marigold_Sprout_Offset.Y, 0, 0);
//            if (plant->mGloveGrabbed)
//            {
//                Sexy_Graphics_SetColorizeImages(graphics,false);
//            }
//        }
        Sexy_Graphics_SetColorizeImages(graphics,false);
        if (plant->mHighlighted)
        {
            Sexy_Graphics_SetDrawMode(graphics,DrawMode::DRAWMODE_ADDITIVE);
            Sexy_Graphics_SetColorizeImages(graphics,true);
            Color color ={255, 255, 255, 196};
            Sexy_Graphics_SetColor(graphics, &color);
            if (image != NULL)
            {
                TodDrawImageCelF(graphics, image, num, num2, theCelCol, theCelRow);
            }
            Sexy_Graphics_SetDrawMode(graphics,DrawMode::DRAWMODE_NORMAL);
            Sexy_Graphics_SetColorizeImages(graphics,false);
        }
        else if (plant->mEatenFlashCountdown > 0)
        {
            Sexy_Graphics_SetDrawMode(graphics,DrawMode::DRAWMODE_ADDITIVE);
            Sexy_Graphics_SetColorizeImages(graphics,true);
            int theAlpha = ClampInt(plant->mEatenFlashCountdown * 3, 0, 255);
            Color color ={255, 255, 255, theAlpha};
            Sexy_Graphics_SetColor(graphics, &color);
            if (image != NULL)
            {
                TodDrawImageCelF(graphics, image, num, num2, theCelCol, theCelRow);
            }
            Sexy_Graphics_SetDrawMode(graphics,DrawMode::DRAWMODE_NORMAL);
            Sexy_Graphics_SetColorizeImages(graphics,false);
        }
    }
    if (mSeedType == SeedType::Magnetshroom && !Plant_DrawMagnetItemsOnTop(plant)) {
        Plant_DrawMagnetItems(plant, graphics);
    }


    if (showPlantHealth || (showNutGarlicSpikeHealth &&
                            (mSeedType == SeedType::Wallnut || mSeedType == SeedType::Tallnut ||
                             mSeedType == SeedType::Pumpkinshell || mSeedType == SeedType::Garlic ||
                             mSeedType == SeedType::Spikerock))) {//如果玩家开了 植物显血
        int holder[1];
        Sexy_StrFormat(holder, "%d/%d", plant->mPlantHealth, plant->mPlantMaxHealth);
        Sexy_Graphics_SetFont(graphics, *Sexy_FONT_DWARVENTODCRAFT12_Addr);
        if (mSeedType == SeedType::Pumpkinshell) {
            Sexy_Graphics_SetColor(graphics, &yellow);
            Sexy_Graphics_DrawString(graphics, holder, 0, 52);
        } else if (mSeedType == SeedType::Flowerpot) {
            Sexy_Graphics_SetColor(graphics, &brown);
            Sexy_Graphics_DrawString(graphics, holder, 0, 93);
        } else if (mSeedType == SeedType::Lilypad) {
            Sexy_Graphics_SetColor(graphics, &green);
            Sexy_Graphics_DrawString(graphics, holder, 0, 100);
        } else if (mSeedType == SeedType::Cobcannon) {
            Sexy_Graphics_SetColor(graphics, &white);
            Sexy_Graphics_DrawString(graphics, holder, 40, 34);
        } else {
            Sexy_Graphics_SetColor(graphics, &white);
            Sexy_Graphics_DrawString(graphics, holder, 0, 34);
        }
        Sexy_String_Delete(holder);
        Sexy_Graphics_SetFont(graphics, NULL);
    }
}

//int (*old_Plant_GetRefreshTime)(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType);
//
//int Plant_GetRefreshTime(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType) {
//    if (seedPacketFastCoolDown) {
//        return 0;
//    }
//    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
//    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
//        int refreshTime;
//        if (theSeedType == SeedType::Imitater && theImitaterType != SeedType::None) {
//            theSeedType = theImitaterType;
//        }
//        if (Challenge_IsMPSeedType(theSeedType)) {  // 判断是否为僵尸方
//            switch (theSeedType) {
//                case SeedType::ZombieFlag:  // 旗帜调整：30 --> 60
//                case SeedType::Zomboni:
//                case SeedType::ZombiePogo:
//                case SeedType::ZombieCatapult:
//                case SeedType::ZombieGargantuar:
//                    refreshTime = 6000;
//                    break;
//                case SeedType::ZombieTrashBin:
//                case SeedType::ZombieTrafficCone:
//                case SeedType::ZombiePolevaulter:
//                case SeedType::ZombiePail:
//                case SeedType::ZombieFootball:
//                case SeedType::ZombieDancer:
//                case SeedType::ZombieDigger:
//                case SeedType::ZombieBungee:
//                case SeedType::ZombieLadder:
//                case SeedType::ZombieBalloon:
//                    refreshTime = 3000;
//                    break;
//                case SeedType::ZombieNewsPaper:
//                case SeedType::ZombieScreenDoor:
//                case SeedType::ZombieJackInTheBox:  // 小丑调整：30 --> 15
//                    refreshTime = 1500;
//                    break;
//                default:
//                    refreshTime = 750;
//                    break;
//            }
//        } else {
//            switch (theSeedType) {
//                case SeedType::Cherrybomb:
//                case SeedType::Iceshroom:
//                case SeedType::Doomshroom:
//                case SeedType::Jalapeno:
//                case SeedType::Tallnut:  // 高坚果：30 --> 60
//                    refreshTime = 6000;
//                    break;
//                case SeedType::Snowpea:  // 冰豆：7.5 --> 30
//                case SeedType::Chomper:  // 大嘴花：7.5 --> 30
//                case SeedType::Gravebuster:
//                case SeedType::Spikeweed:  // 地刺：7.5 --> 30
//                case SeedType::Squash:
//                case SeedType::Torchwood:  // 火炬：7.5 --> 30
//                case SeedType::Splitpea:  // 裂夹：7.5 --> 30
//                case SeedType::Magnetshroom:  // 磁力菇：7.5 --> 30
//                case SeedType::Kernelpult:  // 玉米：7.5 --> 30
//                case SeedType::Garlic:  // 大蒜：7.5 --> 30
//                case SeedType::Umbrella:  // 伞：7.5 --> 30
//                    refreshTime = 3000;
//                    break;
//                case SeedType::Repeater:  // 双发：7.5 --> 15
//                case SeedType::Sunshroom:  // 阳光菇：7.5 --> 15
//                case SeedType::Threepeater:
//                case SeedType::Starfruit:
//                case SeedType::Melonpult:
//                    refreshTime = 1500;
//                    break;
//                default:
//                    refreshTime = GetPlantDefinition(theSeedType).mRefreshTime;
//                    break;
//            }
//        }
//        if (Challenge_IsMPSuddenDeath(lawnApp->mBoard->mChallenge) && *Challenge_gVSSuddenDeathMode_Addr == 1) {
//            switch (theSeedType) {  // 此处用switch-case替换旧的if-else，方便后续增删
//                // 墓碑和向日葵，sd用不到
//                case SeedType::ZombieTombsTone:
//                case SeedType::Sunflower:
//                    // 默认五个不减cd的
//                case SeedType::Tallnut:
//                case SeedType::Wallnut:
//                case SeedType::Pumpkinshell:
//                case SeedType::ZombieTrashBin:
//                case SeedType::ZombieScreenDoor:
//                    // 新增大蒜和咖啡豆在cd模式不减cd
//                case SeedType::Garlic:
//                case SeedType::InstantCoffee:
//                    return refreshTime;
//                default:
//                    return refreshTime / 3;
//            }
//        }
//        return refreshTime;
//    }
//    return old_Plant_GetRefreshTime(theSeedType, theImitaterType);
//}
//
//int (*old_Plant_GetCost)(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType);
//
//int Plant_GetCost(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType) {
//    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
//    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
//        if (theSeedType == SeedType::Imitater && theImitaterType != SeedType::None) {
//            theSeedType = theImitaterType;
//        }
//        switch (theSeedType) {
//            case SeedType::Sunshroom:  // 阳光菇：25 --> 0
//            case SeedType::InstantCoffee:  // 咖啡豆：25 --> 0
//                return 0;
//            case SeedType::Puffshroom:  // 小喷：0 --> 25
//            case SeedType::ZombieNormal:
//            case SeedType::ZombieTrashBin:  // 垃圾桶：50 --> 25
//                return 25;
//            case SeedType::Gravebuster:  // 墓被吞噬者：75 --> 50（回调）
//            case SeedType::Scaredyshroom:  // 胆小菇：25 --> 50
//            case SeedType::ZombieTombsTone:
//            case SeedType::ZombieNewsPaper:
//            case SeedType::ZombieImp:
//                return 50;
//            case SeedType::Squash:
//            case SeedType::Spikeweed:  // 地刺：100 --> 75
//            case SeedType::Kernelpult:  // 玉米：100 --> 75
//            case SeedType::Garlic:
//            case SeedType::Umbrella:  // 伞：100 --> 75
//            case SeedType::ZombieTrafficCone:
//            case SeedType::ZombieJackInTheBox:  // 小丑调整：100 --> 75
//                return 75;
//            case SeedType::Fumeshroom:  // 大喷：75 --> 100
//            case SeedType::Hypnoshroom:  // 迷惑菇：75 --> 100
//            case SeedType::Iceshroom:  // 冰：75 --> 100
//            case SeedType::Torchwood:  // 火炬：125 --> 100
//            case SeedType::Tallnut:  // 高坚果：125 --> 100
//            case SeedType::Cactus:
//            case SeedType::Splitpea:  // 裂夹：125 --> 100
//            case SeedType::Pumpkinshell:  // 南瓜头：125 --> 100
//            case SeedType::Cabbagepult:  // 卷心菜，原费用就是100，不知道为什么这里还判断
//            case SeedType::ZombiePolevaulter:
//            case SeedType::ZombiePail:
//            case SeedType::ZombieScreenDoor:
//            case SeedType::ZombieDuckyTube:
//                return 100;
//            case SeedType::Snowpea:  // 冰豆：150 --> 125
//            case SeedType::Chomper:  // 大嘴花：150 --> 125
//            case SeedType::Jalapeno:
//            case SeedType::Magnetshroom:  // 磁力菇：125 --> 100
//            case SeedType::ZombieDigger:  // 矿工：150 --> 125
//            case SeedType::ZombieBungee:
//            case SeedType::ZombieSnorkel:
//                return 125;
//            case SeedType::Cherrybomb:
//            case SeedType::Repeater:
//            case SeedType::ZombieFootball:
//            case SeedType::ZombieDancer:
//            case SeedType::ZombieLadder:
//                return 150;
//            case SeedType::Doomshroom:  // 核：125 --> 175
//            case SeedType::Starfruit:
//            case SeedType::Zomboni:
//            case SeedType::ZombieCatapult:  // 投篮：200 --> 175
//                return 175;
//            case SeedType::Threepeater:
//            case SeedType::ZombieFlag:  // 旗帜：175 --> 200（回调）
//            case SeedType::ZombiePogo:  // 跳跳：225 --> 200
//                return 200;
//            case SeedType::Melonpult:  // 西瓜：300 --> 225
//            case SeedType::ZombieGargantuar:  // 巨人：250 --> 225
//                return 225;
//            case SeedType::ZombieDolphinRider:
//                return 250;
//            case SeedType::ZombieBalloon:  // 🎈僵尸
//                return 300;
//            default:
//                return GetPlantDefinition(theSeedType).mSeedCost;
//        }
//    }
//    return old_Plant_GetCost(theSeedType, theImitaterType);
//}

int (*old_Plant_GetRefreshTime)(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType);

int Plant_GetRefreshTime(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType) {
    if (seedPacketFastCoolDown) {
        return 0;
    }
    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
        int refreshTime;
        if (theSeedType == SeedType::Imitater && theImitaterType != SeedType::None) {
            theSeedType = theImitaterType;
        }
        if (Challenge_IsMPSeedType(theSeedType)) {
            switch (theSeedType) {
                case SeedType::ZombieTrashBin:
                case SeedType::ZombieTrafficCone:
                case SeedType::ZombiePolevaulter:
                case SeedType::ZombiePail:
                case SeedType::ZombieFlag:
                case SeedType::ZombieFootball:
                case SeedType::ZombieDancer:
                case SeedType::ZombieJackInTheBox:
                case SeedType::ZombieDigger:
                case SeedType::ZombieBungee:
                case SeedType::ZombieLadder:
                case SeedType::ZombieBalloon:
                    refreshTime = 3000;
                    break;
                case SeedType::ZombieNewsPaper:
                case SeedType::ZombieScreenDoor:
                    refreshTime = 1500;
                    break;
                case SeedType::Zomboni:
                case SeedType::ZombiePogo:
                case SeedType::ZombieCatapult:
                case SeedType::ZombieGargantuar:
                    refreshTime = 6000;
                    break;
                default:
                    refreshTime = 750;
                    break;
            }
        } else {
            switch (theSeedType) {
                case SeedType::Cherrybomb:
                case SeedType::Iceshroom:
                case SeedType::Doomshroom:
                case SeedType::Jalapeno:
                    refreshTime = 6000;
                    break;
                case SeedType::Gravebuster:
                case SeedType::Squash:
                    refreshTime = 3000;
                    break;
                case SeedType::Threepeater:
                case SeedType::Starfruit:
                case SeedType::Melonpult:
                    refreshTime = 1500;
                    break;
                default:
                    refreshTime = GetPlantDefinition(theSeedType).mRefreshTime;
                    break;
            }
        }
        if ( Challenge_IsMPSuddenDeath(lawnApp->mBoard->mChallenge) && *Challenge_gVSSuddenDeathMode_Addr == 1 )
        {
            if (theSeedType == SeedType::ZombieTombsTone || theSeedType == SeedType::Sunflower || theSeedType == SeedType::Tallnut || theSeedType == SeedType::Wallnut || theSeedType == SeedType::ZombieScreenDoor || theSeedType == SeedType::Pumpkinshell || theSeedType == SeedType::ZombieTrashBin){
                return refreshTime;
            }
            refreshTime /= 3;
        }
        return refreshTime;
    }
    return old_Plant_GetRefreshTime(theSeedType, theImitaterType);
}

int (*old_Plant_GetCost)(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType);

int Plant_GetCost(SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType) {
    LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
        if (theSeedType == SeedType::Imitater && theImitaterType != SeedType::None) {
            theSeedType = theImitaterType;
        }
        switch (theSeedType) {
            case SeedType::Cherrybomb:
            case SeedType::Snowpea:
            case SeedType::Repeater:
            case SeedType::ZombieFootball:
            case SeedType::ZombieDancer:
            case SeedType::ZombieDigger:
            case SeedType::ZombieLadder:
                return 150;
            case SeedType::Squash:
            case SeedType::Garlic:
            case SeedType::ZombieTrafficCone:
                return 75;
            case SeedType::Threepeater:
            case SeedType::ZombieCatapult:
                return 200;
            case SeedType::Jalapeno:
            case SeedType::Torchwood:
            case SeedType::ZombieBungee:
            case SeedType::ZombieSnorkel:
                return 125;
            case SeedType::Cactus:
            case SeedType::Cabbagepult:
            case SeedType::Kernelpult:
            case SeedType::ZombiePolevaulter:
            case SeedType::ZombiePail:
            case SeedType::ZombieScreenDoor:
            case SeedType::ZombieJackInTheBox:
            case SeedType::ZombieDuckyTube:
                return 100;
            case SeedType::Starfruit:
            case SeedType::Zomboni:
                return 175;
            case SeedType::InstantCoffee:
            case SeedType::ZombieNormal:
                return 25;
            case SeedType::Melonpult:
            case SeedType::ZombieFlag:
            case SeedType::ZombieBalloon:
                return 300;
            case SeedType::ZombieTombsTone:
            case SeedType::ZombieTrashBin:
            case SeedType::ZombieNewsPaper:
            case SeedType::ZombieImp:
                return 50;
            case SeedType::ZombiePogo:
                return 225;
            case SeedType::ZombieGargantuar:
            case SeedType::ZombieDolphinRider:
                return 250;
            default:
                return GetPlantDefinition(theSeedType).mSeedCost;
        }
    }
    return old_Plant_GetCost(theSeedType, theImitaterType);
}

bool abilityFastCoolDown = false;

void (*old_Plant_Update)(Plant *plant);

void Plant_Update(Plant *plant) {
    //用于修复植物受击闪光、生产发光、铲子下方植物发光，同时实现技能无冷却

    SeedType::SeedType mSeedType = plant->mSeedType;
    if (abilityFastCoolDown && mSeedType != SeedType::Spikeweed && mSeedType != SeedType::Spikerock) { // 修复地刺和地刺王开启技能无冷却后不攻击敌人
        if (plant->mStateCountdown > 10) {
            plant->mStateCountdown = 10;
        }
    }

    int mHighLightCounter = plant->mEatenFlashCountdown;
    int cancelHighLightLimit = 999 - (speedUpMode > 0 ? 10 : 0);    //铲子的发光计数是1000。这段代码用于在铲子移走之后的1ms内取消植物发光
    if (mHighLightCounter >= 900 && mHighLightCounter <= cancelHighLightLimit) {
        plant->mBeghouledFlashCountdown = 0;
        plant->mEatenFlashCountdown = 0;
    } else if (mHighLightCounter > 0) {
        plant->mBeghouledFlashCountdown = mHighLightCounter > 25 ? 25 : mHighLightCounter;
    }

    LawnApp *lawnApp = plant->mApp;
    GameScenes::GameScenes mGameScene = lawnApp->mGameScene;

    if ((!Plant_IsOnBoard(plant) || mGameScene != GameScenes::LevelIntro || !LawnApp_IsWallnutBowlingLevel(lawnApp)) &&
        (!Plant_IsOnBoard(plant) || lawnApp->mGameMode != GameMode::ChallengeZenGarden) &&
        (!Plant_IsOnBoard(plant) || !CutScene_ShouldRunUpsellBoard(plant->mBoard->mCutScene)) &&
        Plant_IsOnBoard(plant) && mGameScene != GameScenes::Playing) {
        return;
    }


    if (requestPause) {
        //如果开了高级暂停
        Plant_UpdateReanimColor(plant);
        if (mHighLightCounter == 1000) {
            plant->mBeghouledFlashCountdown = 0;
            plant->mEatenFlashCountdown = 0;
        }
        return;
    }
//为了不影响改so，这里不是完全重写，而是执行旧函数
//    Plant_UpdateAbilities(plant);
//    Plant_Animate(plant);
//    if (plant->mPlantHealth < 0)
//        Plant_Die(plant);
//    Plant_UpdateReanim(plant);

    old_Plant_Update(plant);
}

bool mushroomsNoSleep = false;

void (*old_Plant_SetSleeping)(Plant *a, bool a2);

void Plant_SetSleeping(Plant *a, bool isSleeping) {
    if (mushroomsNoSleep) {
        //如果开启"蘑菇免唤醒"
        isSleeping = false;
    }

    return old_Plant_SetSleeping(a, isSleeping);
}

void (*old_Plant_UpdateReanimColor)(Plant *a);

void Plant_UpdateReanimColor(Plant *plant) {
    //修复玩家选中但不拿起(gameState为1就是选中但不拿起，为7就是选中且拿起)某个紫卡植物时，相应的可升级绿卡植物也会闪烁的BUG。
    Board *board = plant->mBoard;
    if (board == NULL) {
        return old_Plant_UpdateReanimColor(plant);
    }
    SeedType::SeedType seedType = plant->mSeedType;
    if (!Plant_IsUpgrade(seedType)) {
        return old_Plant_UpdateReanimColor(plant);
    }
    if (seedType == SeedType::ExplodeONut) {
        return old_Plant_UpdateReanimColor(plant);
    }
    GamepadControls* gamePad = board->mGamepadControls1;
    if (gamePad->mGamepadState != 7) {
        plant->mSeedType = SeedType::Peashooter;
        old_Plant_UpdateReanimColor(plant);
        plant->mSeedType = seedType;
        return;
    }
    return old_Plant_UpdateReanimColor(plant);
}

GridItem* Plant_FindTargetGridItem(Plant *plant, PlantWeapon::PlantWeapon weapon) {
    // 对战模式专用，植物索敌僵尸墓碑和靶子僵尸。
    // 原版函数BUG：植物还会索敌梯子和毁灭菇弹坑，故重写以修复BUG。
    GridItem *gridItem = NULL;
    GridItem *resultGridItem = NULL;
    int lastGridX = 0;
    if (plant->mApp->mGameMode == GameMode::TwoPlayerVS) { //如果是对战模式(关卡ID为76)
        int mRow = plant->mStartRow;
        int mPlantCol = plant->mPlantCol;
        Board* board = plant->mBoard;
        SeedType::SeedType mSeedType = plant->mSeedType;
        while (Board_IterateGridItems(board, &gridItem)) {//遍历场上的所有GridItem

            GridItemType::GridItemType mGridItemType =  gridItem->mGridItemType;
            if (mGridItemType != GridItemType::Gravestone && mGridItemType != GridItemType::VSTargetZombie) {
                //修复植物们攻击核坑和梯子
                continue;
            }
            int mGridX = gridItem->mGridX;
            int mGridY = gridItem->mGridY;
            if (mSeedType == SeedType::Threepeater ? abs(mGridY - mRow) > 1 : mGridY != mRow) {
                //如果是三线射手，则索敌三行; 反之，索敌一行
                //注释掉此行，就会发现投手能够命中三格内的靶子了，但会导致很多其他BUG。尚不清楚原因。
                continue;
            }


            if (resultGridItem == NULL || mGridX < lastGridX) {
                if (mSeedType == SeedType::Fumeshroom && mGridX - mPlantCol > 3) {
                    //如果是大喷菇，则索敌三格以内的靶子或墓碑
                    continue;
                }
                if (mSeedType == SeedType::Puffshroom || mSeedType == SeedType::Seashroom) {
                    //如果是小喷菇或水兵菇，则索敌三格以内的墓碑
                    if (mGridX - mPlantCol > 3) {
                        continue;
                    }
                    //不主动攻击靶子
                    if (mGridItemType == GridItemType::VSTargetZombie) {
                        continue;
                    }
                }
                resultGridItem = gridItem;
                lastGridX = mGridX;
            }
        }
    }
    return resultGridItem;
}


void (*old_Plant_DoSpecial)(Plant *plant);

void Plant_DoSpecial(Plant *plant) {
    //试图修复辣椒爆炸后反而在本行的末尾处产生冰道。失败。


    if (plant->mSeedType == SeedType::Cherrybomb) {
        // 用于 极限一换十 成就
        int num1 = Board_GetLiveZombiesCount(plant->mBoard);
        old_Plant_DoSpecial(plant);
        int num2 = Board_GetLiveZombiesCount(plant->mBoard);
        if (num1 - num2 >= 10 && !LawnApp_IsLittleTroubleLevel(plant->mApp)) {
            Board_GrantAchievement(plant->mBoard, AchievementId::ACHIEVEMENT_EXPLODONATOR, true);
        }
        return;
    }
    return old_Plant_DoSpecial(plant);
}

void
(*old_Plant_PlantInitialize)(Plant *plant, int theGridX, int theGridY, SeedType::SeedType theSeedType,
                             SeedType::SeedType theImitaterType, int a6);

void Plant_PlantInitialize(Plant *plant, int theGridX, int theGridY, SeedType::SeedType theSeedType,
                           SeedType::SeedType theImitaterType, int a6) {
    //在初始化植物后更新一次动画，以解决开场前存在的植物只绘制阴影而不绘制植物本体的问题
    old_Plant_PlantInitialize(plant, theGridX, theGridY, theSeedType, theImitaterType, a6);
    Plant_UpdateReanim(plant);

    //在对战模式修改指定植物的血量
    if (plant->mApp->mGameMode == GameMode::TwoPlayerVS) {
        SeedType::SeedType mSeedType = plant->mSeedType;
        switch (mSeedType) {
            case SeedType::Sunflower:
                plant->mPlantMaxHealth = 300;
                break;
            case SeedType::Peashooter:
                plant->mPlantMaxHealth = 300;
                break;
        }
        plant->mPlantHealth = plant->mPlantMaxHealth;
    }
}

bool (*old_Plant_IsUpgrade)(SeedType::SeedType theSeedType);

bool Plant_IsUpgrade(SeedType::SeedType theSeedType) {
    //修复机枪射手在SeedBank光标移动到shop栏后变为绿卡。
    if (theSeedType == SeedType::Gatlingpea) {
        LawnApp *lawnApp = (LawnApp *) *gLawnApp_Addr;
        Board *board = lawnApp->mBoard;
        if (board == NULL) {
            return old_Plant_IsUpgrade(theSeedType); // 等价于直接return true;但方便改版修改所以返回旧函数
        }
        if (lawnApp->mSeedChooserScreen != NULL) {
            return true;
        }
        GamepadControls* gamePad = board->mGamepadControls1;
        return !(gamePad->mGamepadState == 7 && gamePad->mIsInShopSeedBank);
    }
    return old_Plant_IsUpgrade(theSeedType);
}

void Plant_SetImitaterFilterEffect(Plant *plant) {
    FilterEffectType::FilterEffectType aFilterEffect = FilterEffectType::WashedOut;
    SeedType::SeedType mSeedType = plant->mSeedType;
    if (mSeedType == SeedType::Hypnoshroom || mSeedType == SeedType::Squash || mSeedType == SeedType::Potatomine || mSeedType == SeedType::Garlic || mSeedType == SeedType::Lilypad)
    {
        aFilterEffect = FilterEffectType::LessWashedOut;
    }
    LawnApp* lawnApp = plant->mApp;
    Reanimation* mBodyReanim = LawnApp_ReanimationTryToGet(lawnApp, plant->mBodyReanimID);
    if ( mBodyReanim != NULL)
        mBodyReanim->mFilterEffect = aFilterEffect;
    Reanimation* mHeadReanim = LawnApp_ReanimationTryToGet(lawnApp, plant->mHeadReanimID);
    if ( mHeadReanim != NULL)
        mHeadReanim->mFilterEffect = aFilterEffect;
    Reanimation* mHeadReanim2 = LawnApp_ReanimationTryToGet(lawnApp, plant->mHeadReanimID2);
    if ( mHeadReanim2 != NULL)
        mHeadReanim2->mFilterEffect = aFilterEffect;
    Reanimation* mHeadReanim3 = LawnApp_ReanimationTryToGet(lawnApp,plant->mHeadReanimID3);
    if ( mHeadReanim3 != NULL)
        mHeadReanim3->mFilterEffect = aFilterEffect;
}

//void (*old_Plant_CobCannonFire)(Plant* Plant,int x,int y);
//
//void Plant_CobCannonFire(Plant *plant, int x, int y) {
//    LOGD("fire:%d %d",x,y);
//    old_Plant_CobCannonFire(plant,x,y);
//}


#endif //PVZ_TV_1_1_5_PLANT_CPP
