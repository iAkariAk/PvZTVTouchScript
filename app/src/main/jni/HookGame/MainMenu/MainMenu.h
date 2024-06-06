//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_MAINMENU_H
#define PVZ_TV_1_1_5_MAINMENU_H
#include "../Enums.h"
bool (*MainMenu_InTransition)(MainMenu *);

void (*MainMenu_SetScene)(MainMenu *, int scene);

void (*MainMenu_StartAdventureMode)(MainMenu *);

void MainMenu_SyncButtons(MainMenu *mainMenu);

void (*DaveHelp_DaveHelp)(LeaderboardsWidget *leaderboardsWidget, LawnApp *lawnApp);

void LeaderboardsWidget_LeaderboardsWidget(LeaderboardsWidget *leaderboardsWidget, LawnApp *lawnApp);

void DaveHelp_Delete2(LeaderboardsWidget *leaderboardsWidget);

void MainMenu_Enter(MainMenu *mainMenu);

void ZombatarWidget_ZombatarWidget(ZombatarWidget* zombatarWidget,LawnApp* lawnApp);

void TestMenuWidget_DrawPortrait(ZombatarWidget *zombatarWidget, Sexy::Graphics *graphics,int x,int y);

bool ZombatarWidget_AccessoryIsColorized(int tab, int accessory);
#endif //PVZ_TV_1_1_5_MAINMENU_H
