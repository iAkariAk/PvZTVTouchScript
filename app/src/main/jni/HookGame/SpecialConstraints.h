//
// 此文件记录着所有111和115不中不同的内容。
//

#ifndef PVZ_TV_1_1_5_SPECIALCONSTRAINTS_H
#define PVZ_TV_1_1_5_SPECIALCONSTRAINTS_H

#include "KittyMemory/MemoryPatch.h"
#include "Includes/Utils.h"

#define SexyAppBaseSize  552
#define SexyAppBasePartSize  526
//#define VERSION_111

inline int LAWNAPP_PLAYSAMPLE_OFFSET = 676;

inline int BOARD_UPDATE_ADDR_RELATIVE = 0x164A88;

inline int ZOMBIE_ISTANGLEKELPTARGET_ADDR_RELATIVE = 0x1AAD98; // 符号重复，无法dlsym获取地址，只好常量封装

inline int ZOMBIE_ISTANGLEKELPTARGET2_ADDR_RELATIVE = 0x1A8338; // 符号重复，无法dlsym获取地址，只好常量封装

inline int J_AUDIOWRITE_ADDR_RELATIVE = 0x12E6C4;

#define targetLibName "libGameMain.so"

struct Game_Patches {
    MemoryPatch
            WhackAZombieNormalSpeed,//锤僵尸关卡的僵尸速度恢复为原速
            RepairShopA,//破解商店
            RepairShopB,//破解商店
            UsefulSeedPacketAutoPickupDisable;//禁止光标自动拾取植物卡片

} GamePatches;

bool IsPatched = false;
bool enableNewOptionsDialog = false;

void StepOnePatchGame() {
    if (!IsPatched) {
//        GamePatches.LawnMouseMode = MemoryPatch::createWithHex(targetLibName,string2Offset("0x2C0A44"),"4F F0 01 00",true);
        GamePatches.WhackAZombieNormalSpeed = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1814F0"),"4F F0 01 00",true);
        GamePatches.RepairShopA = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C1BB6"),"05 E0",true);
        GamePatches.RepairShopB = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C1D1C"),"06 E0",true);
        GamePatches.UsefulSeedPacketAutoPickupDisable = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C4114"),"16",true);

//        MemoryPatch::createWithHex(targetLibName,string2Offset("0x2B63AE"),"5F",true).Modify();
//        MemoryPatch::createWithHex(targetLibName,string2Offset("0x14FC7E"),"19",true).Modify();

        GamePatches.WhackAZombieNormalSpeed.Modify();
        GamePatches.RepairShopA.Modify();
        GamePatches.RepairShopB.Modify();
        IsPatched = true;
    }

}


#endif //PVZ_TV_1_1_5_SPECIALCONSTRAINTS_H
