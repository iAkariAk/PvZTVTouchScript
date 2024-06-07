//
// Created by 23976 on 2024/6/7.
//

#ifndef PVZ_TV_1_1_1_JNINTERACTION_H
#define PVZ_TV_1_1_1_JNINTERACTION_H


#include <queue>
#include <mutex>
#include "FUtils.h"

namespace JNIInteraction {
    using packet = std::pair<std::string, std::string>;

    void SendPacket(packet packet);
    inline void SendPacket(std::string name, std::string content) {
        SendPacket(std::pair(name, content));
    }
    packet ReceivePacket(std::string_view name);
}

#endif //PVZ_TV_1_1_1_JNINTERACTION_H

