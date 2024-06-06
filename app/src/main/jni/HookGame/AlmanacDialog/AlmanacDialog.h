//
// Created by Administrator on 2024/4/8.
//

#ifndef PVZ_TV_1_1_5_ALMANACDIALOG_H
#define PVZ_TV_1_1_5_ALMANACDIALOG_H

#include "../Enums.h"

bool (*AlmanacDialog_KeyDown)(AlmanacDialog* , int);
SeedType::SeedType (*AlmanacDialog_SeedHitTest)(AlmanacDialog *, int, int);
ZombieType::ZombieType (*AlmanacDialog_ZombieHitTest)(AlmanacDialog *, int, int);
void (*AlmanacDialog_SetupPlant)(AlmanacDialog *);
void (*AlmanacDialog_SetupZombie)(AlmanacDialog *);
void (*old_AlmanacDialog_SetPage)(AlmanacDialog *almanacDialog, int targetPage);
void AlmanacDialog_SetPage(AlmanacDialog *almanacDialog, int targetPage);
void AlmanacDialog_MouseDown(AlmanacDialog *almanacDialog, int x, int y, int a4);
void (*old_AlmanacDialog_MouseDrag)(AlmanacDialog *almanacDialog, int, int);
void AlmanacDialog_MouseDrag(AlmanacDialog *almanacDialog, int x, int y);
void AlmanacDialog_MouseUp(AlmanacDialog *almanacDialog, int x, int y, int a4);
void (*old_AlmanacDialog_AddedToManager)(AlmanacDialog *almanacDialog, int *manager);
void AlmanacDialog_AddedToManager(AlmanacDialog *almanacDialog, int *manager);
void (*old_AlmanacDialog_RemovedFromManager)(AlmanacDialog *almanacDialog, int *manager);
void AlmanacDialog_RemovedFromManager(AlmanacDialog *almanacDialog, int *manager);
void (*old_AlmanacDialog_AlmanacDialog)(AlmanacDialog* almanacDialog,LawnApp* lawnApp);
void AlmanacDialog_AlmanacDialog(AlmanacDialog *almanacDialog, LawnApp *lawnApp);
void AlmanacDialog_ButtonDepress(AlmanacDialog *almanacDialog, int id);




#endif //PVZ_TV_1_1_5_ALMANACDIALOG_H
