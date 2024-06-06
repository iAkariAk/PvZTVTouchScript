//
// 此文件记录着所有111和115不中不同的内容。
//

#ifndef PVZ_TV_1_1_5_SPECIALCONSTRAINTS_H
#define PVZ_TV_1_1_5_SPECIALCONSTRAINTS_H

#define SexyAppBaseSize  553
#define SexyAppBasePartSize  527
#define VERSION_111

inline int LAWNAPP_PLAYSAMPLE_OFFSET = 680;

inline int BOARD_UPDATE_ADDR_RELATIVE = 0x1669E4;

inline int ZOMBIE_ISTANGLEKELPTARGET_ADDR_RELATIVE = 0x1AA288;

inline int ZOMBIE_ISTANGLEKELPTARGET2_ADDR_RELATIVE = 0x1ACCE8;

inline int J_AUDIOWRITE_ADDR_RELATIVE = 0x524E28;

#define targetLibName "libGameMain.so"

struct Game_Patches {
    MemoryPatch
            WhackAZombieNormalSpeed,
            RepairShopA,
            RepairShopB,
            UsefulSeedPacketAutoPickupDisable;
} GamePatches;

bool IsPatched = false;
bool enableNewOptionsDialog = false;

void StepOnePatchGame(){
    if (!IsPatched) {
//        GamePatches.LawnMouseMode = MemoryPatch::createWithHex(targetLibName,string2Offset("0x2BE9D8"),"4F F0 01 00",true);
//        GamePatches.LawnMouseMode.Modify();
        GamePatches.WhackAZombieNormalSpeed = MemoryPatch::createWithHex(targetLibName,string2Offset("0x183448"),"4F F0 01 00",true);
        GamePatches.WhackAZombieNormalSpeed.Modify();
        GamePatches.RepairShopA = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C3B06"),"05 E0",true);
        GamePatches.RepairShopA.Modify();
        GamePatches.RepairShopB = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C3C6C"),"06 E0",true);
        GamePatches.RepairShopB.Modify();
        GamePatches.UsefulSeedPacketAutoPickupDisable = MemoryPatch::createWithHex(targetLibName,string2Offset("0x1C6068"),"99",true);
        IsPatched = true;
    }
}

typedef unsigned int _DWORD;
typedef unsigned char _BYTE;

#endif //PVZ_TV_1_1_5_SPECIALCONSTRAINTS_H
