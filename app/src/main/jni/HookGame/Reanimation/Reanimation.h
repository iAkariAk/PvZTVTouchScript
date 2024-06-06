//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_REANIMATION_H
#define PVZ_TV_1_1_5_REANIMATION_H
#include "../Enums.h"
void (*Reanimation_SetPosition)(Reanimation* a, float a2, float a3);

void (*Reanimation_OverrideScale)(Reanimation* ream, float a2, float a3);

void (*Reanimation_DrawRenderGroup)(Reanimation* a, Sexy::Graphics *graphics, int a3);

void (*Reanimation_Reanimation)(Reanimation *a);

void (*Reanimation_ReanimationInitializeType)(Reanimation *a1, float a2, float a3, ReanimationType::ReanimationType a4);

bool *(*Reanimation_Draw)(Reanimation *a, Sexy::Graphics *a2);

void (*Reanimation_Delete2)(Reanimation *a);

int (*Reanimation_FindTrackIndexById)(Reanimation *a, char *a2);

void (*Reanimation_GetCurrentTransform)(Reanimation*, int, ReanimatorTransform *);

void (*ReanimatorTransform_ReanimatorTransform)(ReanimatorTransform *a);

void (*Reanimation_PlayReanim)(Reanimation *a1, char *a2, ReanimLoopType::ReanimLoopType a3, int a4, float a5);

void (*Reanimation_SetAnimRate)(Reanimation *a, float a2);

void Reanimation_SetImageOrigin(Reanimation*,char*,Sexy::Image*);

void Reanimation_SetImageDefinition(Reanimation *reanim, char *trackName, Sexy::Image *theImage);

void (*Reanimation_SetImageOverride)(Reanimation*,char*,Sexy::Image*);

int (*Reanimation_FindTrackIndex)(Reanimation*,const char*);

void (*Reanimation_ShowOnlyTrack)(Reanimation *, const char *);

int Reanimation_HideTrack(Reanimation* reanim,const char* trackName,bool hide);

void Reanimation_HideTrackById(Reanimation *reanim, int trackIndex, bool hide);

void Reanimation_HideTrackByPrefix(Reanimation *reanim, char *trackPrefix, bool hide);

void (*Reanimation_ReanimationDie)(Reanimation* reanim);

ReanimatorTrackInstance* (*Reanimation_GetTrackInstanceByName)(Reanimation *reanim,const char*);

AttachEffect* (*AttachReanim)(unsigned short *,Reanimation*,float,float);

void (*Reanimation_SetFramesForLayer)(Reanimation*,const char*);

bool (*Reanimation_TrackExists)(Reanimation*,const char*);

void (*Reanimation_AttachToAnotherReanimation)(Reanimation*,Reanimation* reanim,const char* trackName);

void (*Reanimation_Update)(Reanimation*);

void  (*Reanimation_AssignRenderGroupToTrack)(Reanimation*, const char *trackName, int group);

void (*Reanimation_MatrixFromTransform)(ReanimatorTransform*,Sexy::SexyMatrix3*);

void (*Reanimation_GetFrameTime)(Reanimation*,ReanimatorFrameTime *pTime) ;

void (*TodScaleRotateTransformMatrix)(Sexy::SexyMatrix3*,float,float,float,float,float);

void Reanimation_SetZombatarReanim(Reanimation* zombatarReanim);

void Reanimation_SetZombatarHats(Reanimation* zombatarReanim, unsigned char hats,unsigned char hatsColor);

void Reanimation_SetZombatarHair(Reanimation* zombatarReanim, unsigned char hair, unsigned char hairColor);

void Reanimation_SetZombatarFHair(Reanimation* zombatarReanim, unsigned char facialHair, unsigned char facialHairColor);

void Reanimation_SetZombatarAccessories(Reanimation* zombatarReanim, unsigned char accessories, unsigned char accessoriesColor);

void Reanimation_SetZombatarEyeWear(Reanimation* zombatarReanim, unsigned char eyeWear, unsigned char eyeWearColor);

void Reanimation_SetZombatarTidBits(Reanimation* zombatarReanim, unsigned char tidBits, unsigned char tidBitsColor);

void Reanimation_GetZombatarTrackIndex(Reanimation* zombatarReanim,int *indexArray);

int Reanimation_GetZombatarHatTrackIndex(Reanimation* zombatarReanim);

int Reanimation_GetZombatarEyeWearTrackIndex(Reanimation* zombatarReanim);

void (*Reanimation_GetTrackMatrix)(Reanimation *pInstance, int i, SexyTransform2D *pD);
#endif //PVZ_TV_1_1_5_REANIMATION_H
