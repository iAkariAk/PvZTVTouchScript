//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_SEEDPACKET_H
#define PVZ_TV_1_1_5_SEEDPACKET_H
#include "../Enums.h"
//void (*SeedPacket_MouseDown)(int*, int x,int y, int);

void (*SeedPacket_DrawBackground)(SeedPacket *seedPacket, Sexy::Graphics *graphics);

void SeedPacket_Update(SeedPacket* seedPacket);

bool (*SeedPacket_CanPickUp)(SeedPacket *seedPacket);

bool (*SeedPacket_MouseHitTest)(SeedPacket*,int,int,HitResult*);

bool (*SeedPacket_GetPlayerIndex)(SeedPacket *);

bool SeedPacket_BeginDraw(SeedPacket* a, Sexy::Graphics* a2);

void SeedPacket_EndDraw(SeedPacket* a, Sexy::Graphics* a2);

void SeedPacket_DrawOverlay(SeedPacket *seedPacket, Sexy::Graphics *graphics);

void (*SeedPacket_DrawMiddle)(SeedPacket *seedPacket, Sexy::Graphics *graphics);

void SeedPacket_Draw(SeedPacket *seedPacket, Sexy::Graphics *graphics);
#endif //PVZ_TV_1_1_5_SEEDPACKET_H
