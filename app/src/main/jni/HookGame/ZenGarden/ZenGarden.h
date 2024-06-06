//
// Created by Administrator on 2024/3/8.
//

#ifndef PVZ_TV_1_1_5_ZENGARDEN_H
#define PVZ_TV_1_1_5_ZENGARDEN_H

int *(*ZenGarden_GetStinky)(int **zenGarden);

bool (*ZenGarden_IsStinkyHighOnChocolate)(int *zenGarden);

void (*ZenGarden_OpenStore)(int*);

int (*ZenGarden_GetPottedPlantInWheelbarrow)(int*);

void (*ZenGarden_DrawPottedPlant)(int *a1,Sexy::Graphics *g, float x,float y,PottedPlant *thePottedPlant,float theScale,bool theDrawPot);

float (*PlantFlowerPotHeightOffset)(SeedType::SeedType,float);
#endif //PVZ_TV_1_1_5_ZENGARDEN_H
