//
// Created by Administrator on 2024/3/4.
//

#ifndef PVZ_TV_1_1_5_SEEDBANK_CPP
#define PVZ_TV_1_1_5_SEEDBANK_CPP


#include "HookGame/Graphics/Graphics.h"
#include "HookGame/Misc/Misc.h"
#include "HookGame/SpecialConstraints.h"
#include "HookGame/Board/Board.h"
#include "HookGame/GlobalVariable.h"
#include "HookGame/SeedPacket/SeedPacket.h"
#include "HookGame/Board/Board.h"
#include "HookGame/CutScene/CutScene.h"
#include "HookGame/HookAddr.h"


void (*old_SeedBank_Draw)(SeedBank *seedBank, Sexy::Graphics *graphics);

void SeedBank_Draw(SeedBank *seedBank, Sexy::Graphics *graphics) {
    // 在对战模式取消0.9倍缩放
    if (seedBank->mApp->mGameMode != GameMode::TwoPlayerVS) {
        return old_SeedBank_Draw(seedBank, graphics);
    }
    Sexy_Graphics_PushState(graphics);
    LawnApp *lawnApp = seedBank->mApp;
    Board *board = seedBank->mBoard;
//    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
//        graphics->mTransX = 0;
//        graphics->mTransY = 0;
//        int transform[12];
//        Sexy_SexyTransform2D_SexyTransform2D(transform);
//        Sexy_SexyTransform2D_Scale(transform, 0.9, 0.9);
//        int theOffsetX = *(_BYTE *) (*(_DWORD *) (*((_DWORD *) seedBank + 4) + 740) + 96) ? 240 : 80;
//        float theTranslateX = seedBank->mX + theOffsetX;
//        float theTranslateY = seedBank->mY + 60;
//        Sexy_SexyTransform2D_Translate(transform, theTranslateX, theTranslateY);
////        Sexy_Graphics_PushTransform(graphics,transform, true);
////        Sexy_Image_PushTransform(graphics->mDestImage,transform,true);
//        (*(void (__fastcall **)(_DWORD, int *, bool))(**((_DWORD **)graphics + 1) + 140))(*((_DWORD *)graphics + 1),transform,true);
//    }
    if (lawnApp->mGameScene != GameScenes::Playing) {
        graphics->mTransX = graphics->mTransX - board->mX;
        graphics->mTransY = graphics->mTransY - board->mY;
    }
    CutScene *cutScene = board->mCutScene;
    if (cutScene != NULL && CutScene_IsBeforePreloading(cutScene)) {
        return;
    }
    if (LawnApp_IsSlotMachineLevel(lawnApp)) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SUNBANK_Addr, 0, 0);
    } else if (Board_HasConveyorBeltSeedBank(board, seedBank->mPlayerIndex)) {
        if (LawnApp_IsCoopMode(lawnApp)) {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_CONVEYORBELT_BACKDROP_COOP_Addr, 0, 0);
            Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_CONVEYORBELT_COOP_Addr, 7, 63, 0,seedBank->mConveyorBeltCounter / 4 % 6);
            Sexy_Graphics_SetClipRect(graphics, 7, 0, 313, 600);
        } else {
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_CONVEYORBELT_BACKDROP_Addr, 83, 0);
            Sexy_Graphics_DrawImageCel(graphics, *Sexy_IMAGE_CONVEYORBELT_Addr, 90, 63, 0,seedBank->mConveyorBeltCounter / 4 % 6);
            Sexy_Graphics_SetClipRect(graphics, 90, 0, 501, 600);
        }
    } else if (LawnApp_IsCoopMode(lawnApp)) {
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SEEDBANK_COOP_Addr, 0, 0);
    } else if (lawnApp->mGameMode == GameMode::TwoPlayerVS && seedBank->mPlayerIndex) {
        int theSeedBankExtraWidth = Board_GetSeedBankExtraWidth(board);
        Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_ZOMBIE_SEEDBANK_Addr, theSeedBankExtraWidth, 0);
    } else {
        Sexy::Image *seedBankImage = *Sexy_IMAGE_SEEDBANK_Addr;
        int theSeedBankExtraWidth = Board_GetSeedBankExtraWidth(board);
        int theRect[4];
        theRect[0] = seedBankImage->mWidth - 12 - theSeedBankExtraWidth;
        theRect[1] = 0;
        theRect[2] = theSeedBankExtraWidth + 12;
        theRect[3] = seedBankImage->mHeight;
        Sexy_Graphics_DrawImage(graphics, seedBankImage, 0, 0);
        Sexy_Graphics_DrawImage2(graphics, seedBankImage, seedBankImage->mWidth - 12, 0, theRect);
    }
    SeedPacket* seedPacket1 = NULL;
    SeedPacket* seedPacket2 = NULL;
    int mNumPackets = seedBank->mNumPackets;
    if (mNumPackets > 0) {
        for (int i = 0; i < mNumPackets; ++i) {
            SeedPacket *seedPacket = &(seedBank->mSeedPackets[i]);
            if (seedPacket->mPacketType == SeedType::None) {
                continue;
            }
            if (!LawnApp_IsSlotMachineLevel(lawnApp)) {
                if (LawnApp_IsCoopMode(lawnApp) || lawnApp->mGameMode == GameMode::TwoPlayerVS) {
                    bool mPlayerIndex = board->mSeedBank2 == seedBank;
                    GamepadControls *gamepadControls = mPlayerIndex ? board->mGamepadControls2 : board->mGamepadControls1;
                    if (gamepadControls->mPlayerIndex2 != -1 &&
                        i == gamepadControls->mSelectedSeedIndex) {
                        if (mPlayerIndex) {
                            seedPacket2 = seedPacket;
                        } else {
                            seedPacket1 = seedPacket;
                        }
                        continue;
                    }
                } else {
                    GamepadControls *gamepadControls1 = board->mGamepadControls1;
                    if (gamepadControls1->mPlayerIndex2 != -1 &&
                        i == gamepadControls1->mSelectedSeedIndex) {
                        seedPacket1 = seedPacket;
                        continue;
                    }
                    GamepadControls *gamepadControls2 = board->mGamepadControls2;
                    if (gamepadControls2->mPlayerIndex2 != -1 &&
                        i == gamepadControls2->mSelectedSeedIndex) {
                        seedPacket2 = seedPacket;
                        continue;
                    }
                }
            }
            if (SeedPacket_BeginDraw(seedPacket, graphics)) {
                SeedPacket_DrawBackground(seedPacket, graphics);
                SeedPacket_EndDraw(seedPacket, graphics);
            }
        }
        for (int i = 0; i < mNumPackets; ++i) {
            SeedPacket *seedPacket = &(seedBank->mSeedPackets[i]);
            if (seedPacket->mPacketType == SeedType::None) {
                continue;
            }
            if (seedPacket == seedPacket1 || seedPacket == seedPacket2) {
                continue;
            }
            if (SeedPacket_BeginDraw(seedPacket, graphics)) {
                SeedPacket_DrawMiddle(seedPacket, graphics);
                SeedPacket_EndDraw(seedPacket, graphics);
            }
        }

        for (int i = 0; i < mNumPackets; ++i) {
            SeedPacket *seedPacket = &(seedBank->mSeedPackets[i]);
            if (seedPacket->mPacketType == SeedType::None) {
                continue;
            }
            if (seedPacket == seedPacket1 || seedPacket == seedPacket2) {
                continue;
            }
            if (SeedPacket_BeginDraw(seedPacket, graphics)) {
                SeedPacket_DrawOverlay(seedPacket, graphics);
                SeedPacket_EndDraw(seedPacket, graphics);
            }
        }
    }
    graphics->mClipRect.mX -= 20;
    graphics->mClipRect.mY -= 20;
    graphics->mClipRect.mWidth += 20;
    graphics->mClipRect.mHeight += 30;
    if (seedPacket2 != NULL && SeedPacket_BeginDraw(seedPacket2, graphics)) {
        SeedPacket_Draw(seedPacket2, graphics);
        SeedPacket_EndDraw(seedPacket2, graphics);
    }
    if (seedPacket1 != NULL && SeedPacket_BeginDraw(seedPacket1, graphics) )
    {
        SeedPacket_Draw(seedPacket1, graphics);
        SeedPacket_EndDraw(seedPacket1, graphics);
    }
    Sexy_Graphics_ClearClipRect(graphics);
    if (LawnApp_IsSlotMachineLevel(lawnApp))
    {
        if ( seedBank->mY > -(*(int (__fastcall **)(Sexy::Image*))(*Sexy_IMAGE_SEEDBANK_Addr + 20))(*Sexy_IMAGE_SEEDBANK_Addr) )
            Sexy_Graphics_DrawImage(graphics, *Sexy_IMAGE_SLOTMACHINE_OVERLAY_Addr, 189, -2);
    }
    if (!Board_HasConveyorBeltSeedBank(board, 0))
    {
        int theMoney;
        if (seedBank->mPlayerIndex) {
            theMoney = board->mDeathMoney & ~board->mDeathMoney >> 31; // mDeathMoney
        } else {
            theMoney = board->mSunMoney1 & ~board->mSunMoney1 >> 31; // mSunMoney1
        }

        if (LawnApp_IsCoopMode(lawnApp) && board->mSeedBank2 == seedBank) {
            theMoney = board->mSunMoney2 & ~board->mSunMoney2 >> 31; // mSunMoney2
        }
        int holder[1];
        Color theColor = {0,0,0,255};
        Sexy_StrFormat(holder, "%d", theMoney);
        int mOutOfMoneyCounter = board->mOutOfMoneyCounter;
        if (mOutOfMoneyCounter > 0 && mOutOfMoneyCounter % 20 <= 9) {
            theColor.mRed = 255;
            theColor.mGreen = 0;
            theColor.mBlue = 0;
            theColor.mAlpha = 255;
        }
        TodDrawString(graphics, holder, seedBank->mPlayerIndex ? (408 + Board_GetSeedBankExtraWidth(board)) : 38, 78, *Sexy_FONT_CONTINUUMBOLD14_Addr, theColor, DrawStringJustification::Center);
        Sexy_String_Delete(holder);

        if ( LawnApp_IsTwinSunbankMode(lawnApp) )
        {
            int holder1[1];
            Sexy_StrFormat(holder1, "%d", board->mSunMoney2 & ~board->mSunMoney2 >> 31);
            TodDrawString(graphics, holder1, 644, 49, *Sexy_FONT_CONTINUUMBOLD14_Addr, theColor, DrawStringJustification::Center);
            Sexy_String_Delete(holder1);
        }
    }
    if ( lawnApp->mGameScene != GameScenes::Playing)
    {
        graphics->mTransX = graphics->mTransX + board->mX;
        graphics->mTransY = graphics->mTransY + board->mY;
    }
//    if (lawnApp->mGameMode == GameMode::TwoPlayerVS) {
////        Sexy_Graphics_PopTransform(graphics);
////        Sexy_Image_PopTransform(graphics->mDestImage);
//        (*(void (__fastcall **)(_DWORD))(**((_DWORD **)graphics + 1) + 144))(*((_DWORD *)graphics + 1));
//    }
    Sexy_Graphics_PopState(graphics);
}

bool SeedBank_MouseHitTest(SeedBank *seedBank, int x, int y, HitResult *hitResult) {
    int relativeX = x - seedBank->mX;
    int relativeY = y - seedBank->mY;
    int mNumPackets = seedBank->mNumPackets;
    if (seedBank->mWidth - 4 <= relativeX || mNumPackets <= 0) {
        hitResult->mObject = NULL;
        hitResult->mObjectType = GameObjectType::None;
        return false;
    }

    for (int i = 0; i < mNumPackets; i++) {
        if (SeedPacket_MouseHitTest(&seedBank->mSeedPackets[i], relativeX, relativeY, hitResult)) {
            return true;
        }
    }

    hitResult->mObject = NULL;
    hitResult->mObjectType = GameObjectType::None;
    return false;

}

void (*old_SeedBank_SeedBank)(SeedBank *seedBank, bool playerIndex);

void SeedBank_SeedBank(SeedBank *seedBank, bool playerIndex) {
    old_SeedBank_SeedBank(seedBank, playerIndex);
}

void (*old_SeedBank_UpdateWidth)(SeedBank *seedBank);

void SeedBank_UpdateWidth(SeedBank *seedBank) {
    old_SeedBank_UpdateWidth(seedBank);
}

bool SeedBank_ContainsPoint(SeedBank *seedBank, int theX, int theY) {
    return theX >= seedBank->mX && theX < seedBank->mX + seedBank->mWidth && theY >= seedBank->mY && theY < seedBank->mY + seedBank->mHeight;
}

void SeedBank_Move(SeedBank *seedBank, int x, int y) {
    // 在对战模式 错开双方的Bank
    seedBank->mX = x;
    seedBank->mY = y;
    if (seedBank->mApp->mGameMode == GameMode::TwoPlayerVS) {
        int theSeedBankExtraWidth = Board_GetSeedBankExtraWidth(seedBank->mBoard);
        if (seedBank->mPlayerIndex) {
            seedBank->mX += (5 - theSeedBankExtraWidth / 2);
        } else {
            seedBank->mX -= (45 + theSeedBankExtraWidth / 2);
        }
    }
}

bool (*old_SeedBank_BeginDraw)(SeedBank* seedBank,Sexy::Graphics* graphics);

bool SeedBank_BeginDraw(SeedBank *seedBank, Sexy::Graphics *graphics) {
    return old_SeedBank_BeginDraw(seedBank,graphics);
}

void (*old_SeedBank_EndDraw)(SeedBank*seedBank,Sexy::Graphics* graphics);

void SeedBank_EndDraw(SeedBank *seedBank, Sexy::Graphics *graphics) {
    old_SeedBank_EndDraw(seedBank,graphics);
}
#endif //PVZ_TV_1_1_5_SEEDBANK_CPP
