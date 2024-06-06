//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_MISC_H
#define PVZ_TV_1_1_5_MISC_H

#include "../Enums.h"

int (*CursorObject_Draw)(CursorObject *a, Sexy::Graphics *a2);

int (*StoreScreen_SetSelectedSlot)(int a1, int a2);

int (*Attachment_AttachmentDie)(int *);

//bool (*SeedBank_MouseHitTest)(int *a1, int a2, int a3, int *a4);

int (*WaitForSecondPlayerDialog_GameButtonDown)(int *a1, int a2, int a3);

static void DrawSeedPacket(Sexy::Graphics *graphics, float x, float y, SeedType::SeedType seedType, SeedType::SeedType imitaterType,
                           float coolDownPercent, int grayness, bool drawCostText, bool isInGame,
                           bool isZombieSeed, bool a11);

int (*ReanimatorCache_DrawCachedZombie)(ReanimatorCache* a1, Sexy::Graphics *a2, float a3, float a4, int a5);

void ReanimatorCache_DrawCachedPlant(ReanimatorCache* a1, Sexy::Graphics* graphics, float thePosX, float thePosY, SeedType::SeedType theSeedType, DrawVariation::DrawVariation theDrawVariation);

void (*Sexy_StrFormat)(int *holder, const char *theFormat, ...);

void (*TodStringTranslate)(int *holder, const char *theText);

int (*GetRectOverlap)(TRect *a1, TRect *a2);

int (*LawnPlayerInfo_GetFlag)(PlayerInfo *, int);

void (*GetFlashingColor)(Color *, int, int);

bool (*Sexy_GamepadApp_HasGamepad)(LawnApp *);

bool (*GameButton_IsMouseOver)(Sexy::GameButton *);

void (*GameButton_Resize)(Sexy::GameButton *a, int a2, int a3, int a4, int a5);

void (*GameButton_Update)(Sexy::GameButton *a);

void (*GameButton_GameButton)(Sexy::GameButton *a, int id, int *);

void (*GameButton_SetLabel)(Sexy::GameButton *a, int*);

void (*GameButton_SetDisabled)(Sexy::GameButton *a, bool);

Sexy::GameButton* (*MakeButton)(int id, Sexy::ButtonListener *listener, Sexy::Widget *theParent, int *name);

Sexy::Checkbox* (*MakeNewCheckbox)(int id, int **listener, Sexy::Widget *theParent, bool checkedByDefault);

void (*Sexy_ButtonWidget_ButtonWidget)(Sexy::ButtonWidget *, int ,Sexy::ButtonListener *);

void (*GameButton_Draw)(Sexy::GameButton *a, Sexy::Graphics *a2);

void (*GameButton_OnPressed)(Sexy::GameButton *a);

void  (*GameButton_Delete)(Sexy::GameButton *a);

void (*Sexy_SexyMatrix3_SexyMatrix3)(int *);

void DrawSeedType(Sexy::Graphics *graphics, float x, float y, SeedType::SeedType theSeedType, SeedType::SeedType theImitaterType, float xOffset, float yOffset, float scale);

int (*RandRangeInt)(int,int);

void (*Sexy_SexyTransform2D_SexyTransform2D)(SexyTransform2D *);

void (*Sexy_SexyTransform2D_Scale)(SexyTransform2D *, float, float);

void (*Sexy_SexyTransform2D_Translate)(SexyTransform2D *, float, float);

bool (*GameObject_BeginDraw)(int *, float *);

void (*GameObject_EndDraw)(int *, float *);

void (*CursorPreview_Update)(int *);

void (*CursorObject_Update)(int *);

void (*ShopSeedPacket_Update)(int *seedPacket);

void LawnMower_Update(int *lawnMover);

Sexy::Image *(*Sexy_SexyAppBase_GetImage)(LawnApp *, int *, int);

void (*Sexy_Widget_Resize)(Sexy::Widget *widget, int x, int y, int width, int height);

void (*Sexy_Widget_Widget)(Sexy::Widget *widget);

void (*Sexy_Widget_SetVisible)(Sexy::Widget *, bool a2);

void (*Sexy_WidgetManager_SetFocus)(int *manager,Sexy::Widget*);

void (*Sexy_WidgetContainer_SetFocus)(Sexy::WidgetContainer*,Sexy::Widget*);

int* (*Sexy_WidgetManager_GetWidgetAt)(int *manager, int x, int y, int *widgetX, int *widgetY);

int (*Sexy_Image_GetWidth)(Sexy::Image *);

int (*Sexy_Image_GetHeight)(Sexy::Image *);

int (*Sexy_Image_GetCelHeight)(Sexy::Image *);

float(*PlantDrawHeightOffset)(Board*,int,SeedType::SeedType,int,int);

void Sexy_String_Delete(int* holder);

void Sexy_Image_PushTransform(Sexy::Image* image,int* transform,bool concatenate);

void Sexy_Image_PopTransform(Sexy::Image* image);

void Sexy_GLImage_PushTransform(Sexy::Image* image,int* transform,bool concatenate);

void Sexy_GLImage_PopTransform(Sexy::Image* image);

void Sexy_MemoryImage_PushTransform(Sexy::Image* image,int* transform,bool concatenate);

void Sexy_MemoryImage_PopTransform(Sexy::Image* image);

void (*TypingCheck_SetPhrase)(int *a1, int *a2);

int (*Sexy_SexyAppBase_RegistryReadString)(int*, int*, int*);

Sexy::Image *(*Sexy_SexyAppBase_CopyImage)(LawnApp *, Sexy::Image *);

Sexy::Image *(*Sexy_SexyAppBase_CopyImage2)(LawnApp *, Sexy::Image *,TRect*);

void (*Sexy_MemoryImage_MemoryImage)(Sexy::Image *);

unsigned int* (*Sexy_MemoryImage_GetBits)(Sexy::Image *);

void (*Sexy_MemoryImage_Create)(Sexy::Image *, int x, int y);

void (*Sexy_MemoryImage_SetImageMode)(Sexy::Image *, bool , bool );

void (*Sexy_MemoryImage_WriteToPng)(Sexy::Image *,int*);

void (*Sexy_MemoryImage_WriteToJPEG)(Sexy::Image *,int*);

void (*Sexy_MemoryImage_Delete)(Sexy::Image *);

void (*Sexy_MemoryImage_BitsChanged)(Sexy::Image *);

Sexy::Image* FilterEffectCreateImage(Sexy::Image* image,FilterEffectType::FilterEffectType);

Sexy::Image *FilterEffectGetImage(Sexy::Image *image, FilterEffectType::FilterEffectType);

void (*FilterEffectDoWashedOut)(Sexy::Image*);

void (*FilterEffectDoLessWashedOut)(Sexy::Image*);

void (*FilterEffectDoWhite)(Sexy::Image*);

int**(*ReanimAtlas_GetEncodedReanimAtlas)(int*,int*);

void (*ReanimatorCache_GetPlantImageSize)(ReanimatorCache*,int,int*,int*,int*,int*);

bool Sexy_SexyAppBase_Is3DAccelerated(LawnApp*);

void Sexy_SexyAppBase_Set3DAccelerated(LawnApp*,bool);

int* (*Sexy_ResourceManager_GetSoundThrow)(int*,int*);

float (*RandRangeFloat)(float,float);

unsigned int (*PoolEffect_BilinearLookupFixedPoint)(PoolEffect*,unsigned int,unsigned int);

static int ClampInt(int num, int minNum, int maxNum);

bool CursorObject_BeginDraw(CursorObject *cursorObject, Sexy::Graphics *graphics);

void CursorObject_EndDraw(CursorObject *cursorObject, Sexy::Graphics *graphics);

bool (*TodFoley_IsFoleyPlaying)(TodFoley* soundSystem, FoleyType::FoleyType theFoleyType);

void (*TodFoley_StopFoley)(TodFoley* soundSystem, FoleyType::FoleyType theFoleyType);

FoleyInstance* (*SoundSystemFindInstance)(TodFoley*,FoleyType::FoleyType);

int (*Sexy_AudiereSoundManager_LoadSound)(int* mSoundManager, int* theFileName);

void (*MessageWidget_MessageWidget)(MessageWidget *messageWidget, LawnApp *a2);

void (*MessageWidget_Delete)(MessageWidget *messageWidget);

Sexy::Font* (*MessageWidget_GetFont)(MessageWidget *messageWidget);

void (*TodStringListLoad)(const char*);

void (*TodReplaceString)(int*,int*,const char*,int*);

void (*TodReplaceNumberString)(int*,int*,const char*,int);

void (*Sexy_Widget_Move)(Sexy::Widget *a, int a2, int a3);

void (*MaskHelpWidget_MaskHelpWidget)(AchievementsWidget*,LawnApp*);

void (*MaskHelpWidget_Delete)(AchievementsWidget*);

void (*TrashBin_Delete)(TrashBin *a1);

void (*TodParticleSystem_OverrideColor)(TodParticleSystem *, char *theEmitterName, Color *theColor);

void (*TodParticleSystem_OverrideImage)(TodParticleSystem *,char *theEmitterName, Sexy::Image*);

PlayerInfo* (*Sexy_DefaultProfileMgr_GetAnyProfile)(int* );

void (*DrawCheckboxText)(Sexy::Graphics *graphics, int* text1, Sexy::Checkbox* a3, const char *text2);

void  (*Sexy_Checkbox_Delete)(Sexy::Checkbox* );

void (*CreditScreen_PauseCredits)(Sexy::Widget*);

int (*Sexy_RandInt)(int );

void PoolEffect_PoolEffectDraw(PoolEffect* poolEffect,Sexy::Graphics* graphics,bool theIsNight);

void (*Sexy_Image_SetWrapMode)(Sexy::Image*,int,int);

void (*Sexy_WidgetContainer_MarkDirty)(Sexy::WidgetContainer*);

void (*ReanimatorEnsureDefinitionLoaded)(ReanimationType::ReanimationType type, bool b);

void (*Sexy_MenuWidget_Draw)(Sexy::MenuWidget*,Sexy::Graphics*);

void (*Sexy_Widget_DeferOverlay)(Sexy::Widget*,int);

int (*Mailbox_GetNumUnseenMessages)(int*);

void (*LawnMower_StartMower)(int*);

Sexy::Image* (*ReanimatorCache_MakeCachedPlantFrame)(ReanimatorCache*,SeedType::SeedType,DrawVariation::DrawVariation);

TodAllocator * (*FindGlobalAllocator)(int aSize);

void (*AttachParticle)(int*,TodParticleSystem *,float,float);

int FloatRoundToInt(float theFloatValue);

void (*TodLoadResources)(int*);

void (*TodParticleSystem_Draw)(TodParticleSystem*,Sexy::Graphics*);

void (*ToolTipWidget_SetWarningText)(int* , int*);

void (*TestMenuWidget_TestMenuWidget)(ZombatarWidget* );

void (*Sexy_SexyAppBase_EraseFile)(SexyAppBase*, int*);

void (*SaveGameContext_SyncInt)(int*,int*);

bool LawnPlayerInfo_EnableZombatar(PlayerInfo *playerInfo,ZombieType::ZombieType);
#endif //PVZ_TV_1_1_5_MISC_H
