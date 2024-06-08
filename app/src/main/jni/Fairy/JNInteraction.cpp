// Created by 23976 on 2024/6/7.
//

#include "JNInteraction.h"
#include <jni.h>
#include <vector>
#include <string>
#include <mutex>
#include <algorithm>
#include <stdexcept>

namespace JNIInteraction {
    std::vector<packet> packets;
    std::mutex packetsMutex;

    void SendPacket(packet packet) {
        std::lock_guard<std::mutex> lock(packetsMutex);
        packets.push_back(packet);
    }

    packet ReceivePacket(std::string_view name) {
        std::lock_guard<std::mutex> lock(packetsMutex);
        if (packets.empty()) {
            throw std::runtime_error("Packets is empty!");
        }

        auto it = std::find_if(packets.begin(), packets.end(), [&name](const packet& p) {
            return p.first == name;
        });

        if (it != packets.end()) {
            packet foundPacket = *it;
            packets.erase(it);
            return foundPacket;
        }

        throw std::runtime_error("Can't find packet with the specified name");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fairy_tv_FairyNative_sendPacket(JNIEnv *env, jclass clazz, jstring name, jstring content) {
    JNIInteraction::SendPacket({fairy::utils::JStringToString(env, name), fairy::utils::JStringToString(env, content)});
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_fairy_tv_FairyNative_receivePacket(JNIEnv *env, jclass clazz, jstring name) {
    try {
        const auto &packet = JNIInteraction::ReceivePacket(fairy::utils::JStringToString(env, name));
        return env->NewStringUTF((packet.first + ":" + packet.second).c_str());
    } catch (const std::exception& e) {
//        fairy::utils::LogError(e.what());
        return nullptr;
    }
}
