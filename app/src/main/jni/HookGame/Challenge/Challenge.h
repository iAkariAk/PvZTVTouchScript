//
// Created by Administrator on 2023/11/18.
//

#ifndef PVZ_TV_1_1_1_CHALLENGEINGAMEFUNCTION_H
#define PVZ_TV_1_1_1_CHALLENGEINGAMEFUNCTION_H
#include "../Enums.h"
int (*Challenge_ScaryPotterCountSunInPot)(Challenge *a1, GridItem *a2);

GridItem *(*Challenge_IZombieGetBrainTarget)(Challenge *, Zombie *);

void (*Challenge_IZombieScoreBrain)(Challenge *, GridItem *);

bool (*Challenge_MouseDown)(Challenge*,int,int,int,HitResult*,int);

void Challenge_Update(Challenge *challenge);

SeedType::SeedType (*Challenge_GetArtChallengeSeed)(Challenge *,int,int);

void (*Challenge_TreeOfWisdomOpenStore)(Challenge *);

static bool (*Challenge_IsZombieSeedType)(SeedType::SeedType type);

static ZombieType::ZombieType Challenge_IZombieSeedTypeToZombieType(SeedType::SeedType);

static bool (*Challenge_IsMPSeedType)(SeedType::SeedType type);

bool (*Challenge_IsMPSuddenDeath)(Challenge*);

void (*Challenge_InitZombieWavesFromList)(Challenge*,ZombieType::ZombieType*,int);

void Challenge_IZombieDrawPlant(Challenge *challenge, Sexy::Graphics *graphics, Plant *plant);

void (*Challenge_IZombieSetupPlant)(Challenge *challenge, Plant *plant);

void (*Challenge_IZombiePlaceZombie)(Challenge *challenge, ZombieType::ZombieType, int,int);

void (*Challenge_GraveDangerSpawnGraveAt)(Challenge *challenge, int x, int y);

bool Challenge_UpdateZombieSpawning(Challenge *challenge);

void (*Challenge_IZombieSetPlantFilterEffect)(Challenge*,Plant*,FilterEffectType::FilterEffectType);
#endif //PVZ_TV_1_1_1_CHALLENGEINGAMEFUNCTION_H
