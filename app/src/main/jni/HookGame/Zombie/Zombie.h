//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_ZOMBIE_H
#define PVZ_TV_1_1_5_ZOMBIE_H

#include "../Enums.h"

void Zombie_DieNoLoot(Zombie* zombie);

void (*Zombie_ApplyBurn)(Zombie* zombie);

void (*Zombie_ApplyButter)(Zombie *zombie);

void (*Zombie_GetZombieRect)(TRect *a1, Zombie *a2);

bool (*Zombie_IsImmobilizied)(Zombie *zombie);

bool (*Zombie_EffectedByDamage)( Zombie* zombie, int flag);

void (*Zombie_RemoveColdEffects)( Zombie* zombie);

void (*Zombie_StartEating)(Zombie *);

void (*Zombie_TakeDamage)(Zombie *, int, unsigned int);

bool (*Zombie_IsWalkingBackwards)(Zombie *);

void (*Zombie_AddAttachedParticle)(Zombie*,int,int,int);

bool (*Zombie_CanBeFrozen)(Zombie*);

void Zombie_Update(Zombie*);

void (*Zombie_StopEating)(Zombie*);

void (*Zombie_DropArm)(Zombie*,unsigned int);

void (*Zombie_PlayZombieReanim)(Zombie*,char*,int,int,float);

void Zombie_AddButter(Zombie* zombieUnderButter);

static ZombieDefinition & GetZombieDefinition(ZombieType::ZombieType type);

void (*Zombie_SetupReanimLayers)(Reanimation*,ZombieType::ZombieType);

void (*Zombie_SetupShieldReanims)(ZombieType::ZombieType,Reanimation*);

void (*Zombie_UpdateReanim)(Zombie*);

void (*Zombie_UpdateActions)(Zombie*);

void (*Zombie_UpdatePlaying)(Zombie*);

bool (*Zombie_IsDeadOrDying)(Zombie*);

bool (*Zombie_IsOnBoard)(Zombie*);

void (*Zombie_ReanimShowPrefix)(Zombie*,const char*,int);

void (*Zombie_ReanimShowTrack)(Zombie*,const char*,int);

void (*Zombie_TakeHelmDamage)(Zombie*,int,unsigned int);

bool (*Zombie_IsFlying)(Zombie*);

void (*Zombie_TakeFlyingDamage)(Zombie*,int,unsigned int);

void (*Zombie_TakeShieldDamage)(Zombie*,int,unsigned int);

void (*Zombie_TakeBodyDamage)(Zombie*,int,unsigned int);

void (*Zombie_UpdateDamageStates)(Zombie*,unsigned int);

int (*Zombie_GetShieldDamageIndex)(Zombie*);

int (*Zombie_GetHelmDamageIndex)(Zombie*);

int (*Zombie_GetBodyDamageIndex)(Zombie*);

void (*Zombie_GetTrackPosition)(Zombie*,const char*,float*,float*);

void (*Zombie_UpdateAnimationSpeed)(Zombie* );

void (*Zombie_HitIceTrap)(Zombie*);

bool ZombieTypeCanGoInPool(ZombieType::ZombieType zombieType);

void (*Zombie_Zombie)(Zombie*);

void Zombie_SetZombatarReanim(Zombie* zombie);

inline bool Zombie_IsZombatarZombie(ZombieType::ZombieType type);

void Zombie_SetupLostArmReanim(Zombie* zombie);
#endif //PVZ_TV_1_1_5_ZOMBIE_H
