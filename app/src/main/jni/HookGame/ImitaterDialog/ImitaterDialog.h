//
// Created by Administrator on 2024/4/7.
//

#ifndef PVZ_TV_1_1_5_IMITATERDIALOG_H
#define PVZ_TV_1_1_5_IMITATERDIALOG_H

#include "../Enums.h"
SeedType::SeedType (*ImitaterDialog_SeedHitTest)(LawnDialog*,int,int);

void ImitaterDialog_ImitaterDialog(LawnDialog *instance, int playerIndex);

#endif //PVZ_TV_1_1_5_IMITATERDIALOG_H
