//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_GRIDITEM_CPP
#define PVZ_TV_1_1_5_GRIDITEM_CPP

#include "../GlobalVariable.h"
#include "../SpecialConstraints.h"
#include "../Graphics/Graphics.h"
#include "HookGame/Challenge/Challenge.cpp"
#include "../Board/Board.h"
#include "HookGame/Reanimation/Reanimation.cpp"
#include "HookGame/Misc/Misc.h"
#include "HookGame/ZenGarden/ZenGarden.h"

void GridItem_DrawScaryPot(GridItem *scaryPot, Sexy::Graphics *graphics) {
    //修复路灯花照透罐子

    int theCelCol = scaryPot->mGridItemState - 3;
    int thePixelX = Board_GridToPixelX(scaryPot->mBoard, scaryPot->mGridX, scaryPot->mGridY) - 5;
    int thePixelY = Board_GridToPixelY(scaryPot->mBoard, scaryPot->mGridX, scaryPot->mGridY) - 15;
    TodDrawImageCelCenterScaledF(graphics, *Sexy_IMAGE_PLANTSHADOW2_Addr, thePixelX - 5.0, thePixelY + 72.0, 0, 1.3, 1.3);

    if (scaryPot->mTransparentCounter > 0) {//如果罐子要被照透(透明度不为0)
        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SCARY_POT_Addr, thePixelX, thePixelY, theCelCol, 0);
        Sexy::Graphics newGraphics;
        Sexy_Graphics_Graphics(&newGraphics, graphics);
        ScaryPotType::ScaryPotType mScaryPotType = scaryPot->mScaryPotType;
        if (mScaryPotType == ScaryPotType::Seed) {
            newGraphics.mScaleX = 0.7f;
            newGraphics.mScaleY = 0.7f;
            DrawSeedPacket(&newGraphics, thePixelX + 23, thePixelY + 33, scaryPot->mSeedType, SeedType::None, 0.0, 255, false, false, false, true);
        } else if (mScaryPotType == ScaryPotType::Zombie) {
            newGraphics.mScaleX = 0.4f;
            newGraphics.mScaleY = 0.4f;
            float theOffsetX = 6.0;
            float theOffsetY = 19.0;
            if (scaryPot->mZombieType == ZombieType::Football) {
                theOffsetX = 1.0;
                theOffsetY = 16.0;
            } else if (scaryPot->mZombieType == ZombieType::Gargantuar) {
                theOffsetX = 15.0;
                theOffsetY = 26.0;
                newGraphics.mScaleX = 0.3f;
                newGraphics.mScaleY = 0.3f;
            }
            ReanimatorCache_DrawCachedZombie(scaryPot->mApp->mReanimatorCache, &newGraphics, theOffsetX + thePixelX, theOffsetY + thePixelY, scaryPot->mZombieType);
        } else if (mScaryPotType == ScaryPotType::Sun) {
            int theSunCount = Challenge_ScaryPotterCountSunInPot(scaryPot->mBoard->mChallenge, scaryPot);
            Reanimation newReanim;
            Reanimation_Reanimation(&newReanim);
//            Reanimation_ReanimationInitializeType(&newReanim, 0.0, 0.0, ReanimationType::Sun);

            Reanimation_ReanimationInitializeType(&newReanim, 0.0, 0.0, ReanimationType::ZombatarHead);

            Reanimation_HideTrackByPrefix(&newReanim,"hats",true);
            Reanimation_HideTrackByPrefix(&newReanim,"hair",true);
            Reanimation_HideTrackByPrefix(&newReanim,"facialHair",true);
            Reanimation_HideTrackByPrefix(&newReanim,"accessories",true);
            Reanimation_HideTrackByPrefix(&newReanim,"eyeWear",true);
            Reanimation_HideTrackByPrefix(&newReanim,"tidBits",true);

            Reanimation_HideTrackByPrefix(&newReanim,"hats_00",false);
            Reanimation_HideTrackByPrefix(&newReanim,"hair_00",false);
            Reanimation_HideTrackByPrefix(&newReanim,"facialHair_00",false);
            Reanimation_HideTrackByPrefix(&newReanim,"accessories_00",false);
            Reanimation_HideTrackByPrefix(&newReanim,"eyeWear_00",false);
            Reanimation_HideTrackByPrefix(&newReanim,"tidBits_00",false);

            Reanimation_OverrideScale(&newReanim, 0.5f, 0.5f);
            Reanimation_Update(&newReanim); // 一次Update是必要的，否则绘制出来是Empty
            newReanim.mFrameStart = (scaryPot->mBoard->mMainCounter / 10) % (newReanim.mFrameCount - 1); // 这行代码可让阳光动起来
            for (int i = 0; i < theSunCount; i++) {
                float theOffsetX = 42.0f;
                float theOffsetY = 62.0f;
                switch (i) {
                    case 1:
                        theOffsetX += 3.0f;
                        theOffsetY += -20.0f;
                        break;
                    case 2:
                        theOffsetX += -6.0f;
                        theOffsetY += -10.0f;
                        break;
                    case 3:
                        theOffsetX += 6.0f;
                        theOffsetY += -5.0f;
                        break;
                    case 4:
                        theOffsetX += 5.0f;
                        break;
                }
                Reanimation_SetPosition(&newReanim, thePixelX + theOffsetX, thePixelY + theOffsetY);
                Reanimation_Draw(&newReanim, graphics);
            }
            Reanimation_Delete2(&newReanim);
        }
        int theAlpha = TodAnimateCurve(0, 50, scaryPot->mTransparentCounter, 255, 58, TodCurves::Linear);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        Color theColor = {255, 255, 255, theAlpha};
        Sexy_Graphics_SetColor(graphics, &theColor);
        Sexy_Graphics_Delete2(&newGraphics);
    }

    Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SCARY_POT_Addr, thePixelX, thePixelY, theCelCol, 1);
    if (scaryPot->mHighlighted) {
        Sexy_Graphics_SetDrawMode(graphics, DrawMode::DRAWMODE_ADDITIVE);
        Sexy_Graphics_SetColorizeImages(graphics, true);
        if (scaryPot->mTransparentCounter == 0) {
            Color theColor = {255, 255, 255, 196};
            Sexy_Graphics_SetColor(graphics, &theColor);
        }
        Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_SCARY_POT_Addr, thePixelX, thePixelY, theCelCol, 1);
        Sexy_Graphics_SetDrawMode(graphics, DrawMode::DRAWMODE_NORMAL);
    }
    return Sexy_Graphics_SetColorizeImages(graphics, false);
}

void (*old_GridItem_Update)(GridItem *a1);

void GridItem_Update(GridItem *a1) {
    if (requestPause) {
        //如果开了高级暂停
        return;
    }
    old_GridItem_Update(a1);
}
bool transparentVase = false;

void (*old_GridItem_UpdateScaryPot)(GridItem *scaryPot);

void GridItem_UpdateScaryPot(GridItem *scaryPot) {
    old_GridItem_UpdateScaryPot(scaryPot);
    if (transparentVase) {//如果玩家开启“罐子透视”
        if (scaryPot->mTransparentCounter < 50) {
            //透明度如果小于50，则为透明度加2
            scaryPot->mTransparentCounter += 2;
        }
    }
}

void (*old_GridItem_DrawStinky)(GridItem *mStinky, Sexy::Graphics *graphics);

void GridItem_DrawStinky(GridItem *mStinky, Sexy::Graphics *graphics) {
    // 在玩家选取巧克力时，高亮显示光标下方且没喂巧克力的Stinky。
    // 从而修复Stinky无法在醒着时喂巧克力、修复Stinky在喂过巧克力后还能继续喂巧克力。
    // 因为游戏通过Stinky是否高亮来判断是否能喂Stinky。这个机制是为鼠标操作而生，但渡维不加改动地将其用于按键操作，导致无法在Stinky醒着时喂它。
    Board *board = mStinky->mBoard;
    GamepadControls* gamePad = board->mGamepadControls1;
    int mCursorX = gamePad->mCursorPositionX;
    int mCursorY = gamePad->mCursorPositionY;
    int mCursorGridX = Board_PixelToGridX(board, mCursorX, mCursorY);
    int mCursorGridY = Board_PixelToGridY(board, mCursorX, mCursorY);
    float mStinkyX = mStinky->mPosX;
    float mStinkyY = mStinky->mPosY;
    int mStinkyGridX = Board_PixelToGridX(board, mStinkyX, mStinkyY);
    int mStinkyGridY = Board_PixelToGridY(board, mStinkyX, mStinkyY);
    if (mStinkyGridX != mCursorGridX || mStinkyGridY != mCursorGridY) {
        //如果Stinky不在光标位置处，则取消高亮。
        mStinky->mHighlighted = false;
        return old_GridItem_DrawStinky(mStinky, graphics);
    }
    //如果Stinky在光标位置处
    CursorObject* cursorObject = board->mCursorObject1;
    CursorType::CursorType mCursorType = cursorObject->mCursorType;
    if (mCursorType == CursorType::Chocolate) {
        //如果光标类型为巧克力
        bool isStinkyHighOnChocolate = ZenGarden_IsStinkyHighOnChocolate(mStinky->mApp->mZenGarden);
        mStinky->mHighlighted = !isStinkyHighOnChocolate; //为没喂巧克力的Stinky加入高亮效果
    }
    return old_GridItem_DrawStinky(mStinky, graphics);
}


void GridItem_DrawSquirrel(GridItem *squirrel, Sexy::Graphics *graphics) {
    //绘制松鼠
    float mSquirrelX = Board_GridToPixelX(squirrel->mBoard, squirrel->mGridX, squirrel->mGridY);
    float mSquirrelY = Board_GridToPixelY(squirrel->mBoard, squirrel->mGridX, squirrel->mGridY);
    switch (squirrel->mGridItemState) {
        case GridItemState::SquirrelPeeking:
            mSquirrelY += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, 0, -40.0f, TodCurves::BounceSlowMiddle);
            break;
        case GridItemState::SquirrelRunningUp:
            mSquirrelY += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, 100, 0.0f, TodCurves::EaseIn);
            break;
        case GridItemState::SquirrelRunningDown:
            mSquirrelY += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, -100, 0.0f, TodCurves::EaseIn);
            break;
        case GridItemState::SquirrelRunningLeft:
            mSquirrelX += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, 80, 0.0f, TodCurves::EaseIn);
            break;
        case GridItemState::SquirrelRunningRight:
            mSquirrelX += TodAnimateCurve(50, 0, squirrel->mGridItemCounter, -80, 0.0f, TodCurves::EaseIn);
            break;
    }
    Sexy_Graphics_DrawImage(graphics, Addon_Images.squirrel, mSquirrelX, mSquirrelY);
}

#endif //PVZ_TV_1_1_5_GRIDITEM_CPP
