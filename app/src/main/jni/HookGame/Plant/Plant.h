//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_PLANT_H
#define PVZ_TV_1_1_5_PLANT_H
#include "../Enums.h"

void (*Plant_Die)(Plant *instance);

static Sexy::Image *(*Plant_GetImage)(SeedType::SeedType seedType);

void (*Plant_GetPlantRect)(TRect *rect, Plant *plant);

bool (*Plant_NotOnGround)(Plant *plant);

static int Plant_GetCost(SeedType::SeedType seedType, SeedType::SeedType imitaterType);

bool (*Plant_IsOnBoard)(Plant *);

void (*Plant_UpdateAbilities)(Plant *);

void (*Plant_Animate)(Plant *);

void (*Plant_UpdateReanim)(Plant *);

void Plant_Update(Plant *);

static bool (*Plant_IsFlying)(SeedType::SeedType);

static PlantDefinition &(*GetPlantDefinition)(SeedType::SeedType);

void Plant_SetSleeping(Plant *a, bool isSleeping);

void Plant_SetImitaterFilterEffect(Plant* plant);

void Plant_DrawSeedType(Sexy::Graphics* graphics,SeedType::SeedType theSeedType,SeedType::SeedType theImitaterType,DrawVariation::DrawVariation,float thePosX,float thePosY);

static bool (*Plant_IsNocturnal)(SeedType::SeedType);

void (*Plant_DrawShadow)(Plant*,Sexy::Graphics*,float,float);

bool (*Plant_IsPartOfUpgradableTo)(Plant*,SeedType::SeedType);

bool (*Plant_IsInPlay)(Plant*);

bool (*Plant_DrawMagnetItemsOnTop)(Plant*);

void (*Plant_DrawMagnetItems)(Plant*,Sexy::Graphics*);

void Plant_UpdateReanimColor(Plant *plant);

int (*Plant_GetDamageRangeFlags)(Plant*,PlantWeapon::PlantWeapon);

bool Plant_IsUpgrade(SeedType::SeedType theSeedType);

#endif //PVZ_TV_1_1_5_PLANT_H
