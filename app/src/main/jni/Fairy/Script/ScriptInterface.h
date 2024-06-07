//
// Created by 12595 on 2023/6/23.
//

#ifndef PVZFREE_FAIRY_ATTRIBUTE_SCRIPTINTERFACE_H
#define PVZFREE_FAIRY_ATTRIBUTE_SCRIPTINTERFACE_H

#include <fstream>
#include <jni.h>
#include "lua.hpp"

extern "C" {
#include "lua_cjson.h"
};

namespace fairy::script {
    enum LuaCppType {
        LUA_CPP_TYPE_VOID,
        LUA_CPP_TYPE_POINTER,
        LUA_CPP_TYPE_INT8,
        LUA_CPP_TYPE_INT16,
        LUA_CPP_TYPE_INT32,
        LUA_CPP_TYPE_INT64,
        LUA_CPP_TYPE_UINT8,
        LUA_CPP_TYPE_UINT16,
        LUA_CPP_TYPE_UINT32,
        LUA_CPP_TYPE_UINT64,
        LUA_CPP_TYPE_FLOAT32,
        LUA_CPP_TYPE_FLOAT64,
        LUA_CPP_TYPE_BOOLEAN,
        LUA_CPP_TYPE_CSTRING8,
    };

    void OnUpdateChallenge(intptr_t challengeAddress);

    void OnUpdateGame(intptr_t boardAddress);

    void OnUpdateApp(intptr_t appAddress);

    bool Init();

    void Execute(JNIEnv *env, jclass thiz, jstring codeStr, jobject onResult);

    void ExecuteFile(JNIEnv *env, jclass thiz, jstring pathStr, jobject onResult);
}

#endif //PVZFREE_FAIRY_ATTRIBUTE_SCRIPTINTERFACE_H
