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

    template<typename... Parts>
    inline void SendPacket(std::string name, Parts... parts) {
        std::stringstream ss;
        bool first = true;
        auto append = [&first, &ss] (auto part){
            if (!first) ss << ":";
            ss << part;
            first = false;
        };
        (append(parts), ...);
        SendPacket(std::pair(name, ss.str()));
    }
    packet ReceivePacket(std::string_view name);
}

#endif //PVZ_TV_1_1_1_JNINTERACTION_H

