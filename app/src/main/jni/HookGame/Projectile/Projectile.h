//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_PROJECTILE_H
#define PVZ_TV_1_1_5_PROJECTILE_H

#include "../Enums.h"

void (*Projectile_Die)(Projectile *a);

void (*Projectile_GetProjectileRect)(TRect *a1, Projectile *a2);

Plant *(*Projectile_FindCollisionTargetPlant)(Projectile *a1);

ProjectileDefinition &(*Projectile_GetProjectileDef)(Projectile *a);

bool (*Projectile_CantHitHighGround)(Projectile *a);

Zombie *(*Projectile_FindCollisionTarget)(Projectile *a);

GridItem *(*Projectile_FindCollisionTargetGridItem)(Projectile *a);

void (*Projectile_DoImpactGridItem)(Projectile *a, GridItem *a2);

void (*Projectile_PlayImpactSound)(Projectile *, Zombie *);

bool (*Projectile_IsSplashDamage)(Projectile *, Zombie *);

void (*Projectile_DoSplashDamage)(Projectile *, Zombie *, int);

unsigned int (*Projectile_GetDamageFlags)(Projectile *, Zombie *);

void Projectile_Update(Projectile *projectile);

bool (*Projectile_PeaAboutToHitTorchwood)(Projectile*);
#endif //PVZ_TV_1_1_5_PROJECTILE_H
