//
// Created by 12595 on 2023/6/23.
//

#include <map>
#include <dlfcn.h>
#include <iostream>
//#include <opencl-c-base.h>
#include "ScriptInterface.h"
//#include "ffi.h"
#include "Core.h"
#include "LuaUtils.h"
#include "../../ThirdParty/Lua/lua.hpp"
#include "Fairy/FUtils.h"

namespace fairy::script {
    lua_State *lua_state;
    bool isInit = false;
    utils::TaskQueue executeLuaTaskQueue;
    std::string assetScriptsDir;

//    std::map<char, ffi_type *> signTypeMap = {
//            {'v', &ffi_type_void},
//            {'*', &ffi_type_pointer},
//            {'B', &ffi_type_uint8},
//            {'b', &ffi_type_sint8},
//            {'S', &ffi_type_uint16},
//            {'s', &ffi_type_sint16},
//            {'I', &ffi_type_uint32},
//            {'i', &ffi_type_sint32},
//            {'L', &ffi_type_uint64},
//            {'l', &ffi_type_sint64},
//            {'f', &ffi_type_float},
//            {'d', &ffi_type_double},
//            {'z', &ffi_type_uint8},
//            {'c', &ffi_type_pointer},
//    };

    const luaL_Reg luaLibraries[] = {
            {"_G",            luaopen_base},
            {LUA_LOADLIBNAME, luaopen_package},
            {LUA_COLIBNAME,   luaopen_coroutine},
            {LUA_TABLIBNAME,  luaopen_table},
            {LUA_IOLIBNAME,   luaopen_io},
            {LUA_OSLIBNAME,   luaopen_os},
            {LUA_STRLIBNAME,  luaopen_string},
            {LUA_MATHLIBNAME, luaopen_math},
            {LUA_UTF8LIBNAME, luaopen_utf8},
            {LUA_DBLIBNAME,   luaopen_debug},
            {"cjson",         lua_cjson_safe_new},
            {"core",          core::luaopen_core},
            {nullptr,         nullptr}
    };

    inline void CallAllFunctionsByParam(const char *argName, intptr_t param) {
        lua_State *L = lua_state;
        lua_getglobal(L, "core");
        lua_getfield(L, -1, argName);
        if (lua_istable(L, -1)) {
            lua_pushnil(L);
            while (lua_next(L, -2)) {
                if (lua_isfunction(L, -1)) {
                    lua_pushvalue(L, -1);
                    lua_pushinteger(L, param);
                    lua_pcall(L, 1, 0, 0);
                }
                lua_pop(L, 1);
            }
        }
        lua_pop(L, 2);
    }

    void OnUpdateChallenge(intptr_t challengeAddress) {
        CallAllFunctionsByParam("onUpdateChallenge", challengeAddress);
    }

    void OnUpdateGame(intptr_t boardAddress) {
        CallAllFunctionsByParam("onUpdateGame", boardAddress);
    }

    void OnUpdateApp(intptr_t appAddress) {
        if (!isInit) {
            Init();
            isInit = true;
        }
        CallAllFunctionsByParam("onUpdateApp", appAddress);
        try {
            auto packet = JNIInteraction::ReceivePacket("ScriptExecuteTask");
            auto &content = packet.second;
            auto separatorIndex = content.find(":");
            auto id = content.substr(0, separatorIndex);
            auto code = content.substr(separatorIndex + 1);
            int rc = luaL_dostring(lua_state, code.c_str());
            const char *result;
            if (rc != 0) {
                result = lua_tostring(lua_state, -1);
                utils::LogError("lua execute -> %s", result);
            } else {
                result = "Success";
                utils::LogDebug("lua execute -> %s", result);
            }
        } catch (...) {}
        try {
            auto packet = JNIInteraction::ReceivePacket("ScriptExecuteFileTask");
            auto &content = packet.second;
            auto separatorIndex = content.find(":");
            auto id = content.substr(0, separatorIndex);
            auto path = content.substr(separatorIndex + 1);
            int rc = luaL_dofile(lua_state, path.c_str());
            const char *result;
            if (rc != 0) {
                result = lua_tostring(lua_state, -1);
                utils::LogError("lua execute -> %s", result);
            } else {
                result = "Success";
                utils::LogDebug("lua execute -> %s", result);
            }
        } catch (...) {}
    }

    void ReleaseScriptsInAsset() {
        assetScriptsDir = fairy::utils::gCacheDir + "/scripts";
        if (!std::filesystem::exists(assetScriptsDir)) {
            std::filesystem::create_directory(assetScriptsDir);
        } else {
            fairy::utils::ClearFolder(assetScriptsDir);
        }
        AAssetDir *dir = AAssetManager_openDir(utils::gAAssetManager, "scripts");
        while (const char *fileName = AAssetDir_getNextFileName(dir)) {
            std::string filePath = "scripts/";
            filePath += fileName;
            AAsset *asset = AAssetManager_open(utils::gAAssetManager, filePath.c_str(),
                                               AASSET_MODE_BUFFER);
            off_t bufferSize = AAsset_getLength(asset);
            const void *buffer = AAsset_getBuffer(asset);
            std::ofstream ofs(assetScriptsDir + "/" + fileName);
            ofs.write((const char *) buffer, bufferSize);
            ofs.close();
            AAsset_close(asset);
        }
        AAssetDir_close(dir);
    }

//    void Execute(JNIEnv *env, jclass thiz, jstring idJStr, jstring codeJStr) {
//        auto code = utils::JStringToString(env, codeJStr);
//        utils::LogDebug("lua execute: %s", code.c_str());
//        auto id = utils::JStringToString(env, idJStr);
//        executeLuaTaskQueue.submit([code, id] {
//            int rc = luaL_dostring(lua_state, code.c_str());
//            const char *result;
//            if (rc != 0) {
//                result = lua_tostring(lua_state, -1);
//                utils::LogError("lua execute -> %s", result);
//            } else {
//                result = "Success";
//            }
//            auto jenv = utils::GetJniEnv();
//            utils::LogError("lua  -> %s", jenv);
//            auto resultJStr = jenv->NewStringUTF(result);
//            jclass functionClass = jenv->GetObjectClass(globalOnResult);
//            jmethodID invokeMethod = jenv->GetMethodID(functionClass, "accept",
//                                                       "(Ljava/lang/Object;)V");
//            jenv->CallVoidMethod(globalOnResult, invokeMethod, resultJStr);
//            jenv->DeleteGlobalRef(globalOnResult);
//        });
//    }
//
//    void ExecuteFile(JNIEnv *env, jclass thiz, jstring pathJStr, jobject onResult) {
//        auto pathStr = utils::JStringToString(env, pathJStr);
//        jobject globalOnResult = env->NewGlobalRef(onResult);
//        executeLuaTaskQueue.submit([pathStr, globalOnResult] {
//            utils::LogDebug("lua execute file: %s", pathStr.c_str());
//            lua_getglobal(lua_state, "package");
//            std::string pathDir = fairy::utils::GetFolderName(pathStr);
//            pathDir.append("/?.lua;");
//            pathDir.append(assetScriptsDir);
//            pathDir.append("/?.lua;");
//            lua_pushlstring(lua_state, pathDir.c_str(), pathDir.size());
//            lua_setfield(lua_state, -2, "path");
//            lua_pop(lua_state, 1);
//            int rc = luaL_dofile(lua_state, pathStr.c_str());
//            const char *result;
//            if (rc != 0) {
//                result = lua_tostring(lua_state, -1);
//                utils::LogError("lua execute -> %s", result);
//            } else {
//                result = "Success";
//            }
//            auto jenv = utils::GetJniEnv();
//            auto resultJStr = jenv->NewStringUTF(result);
//            jclass functionClass = jenv->GetObjectClass(globalOnResult);
//            jmethodID invokeMethod = jenv->GetMethodID(functionClass, "accept",
//                                                       "(Ljava/lang/Object;)V");
//            jenv->CallVoidMethod(globalOnResult, invokeMethod, resultJStr);
//            jenv->DeleteGlobalRef(globalOnResult);
//        });
//    }


//    void ParseFnParam(const char *sign, ffi_type *&returnType, ffi_type **params) {
//        auto getFfiType = [](char ch) {
//            auto it = signTypeMap.find(ch);
//            if (it == signTypeMap.end()) {
//                throw "Illage param";
//            }
//            return it->second;
//        };
//
//        for (int i = 0; i < strlen(sign); i++) {
//            auto &&ch = sign[i];
//            if (i == 0) {
//                returnType = getFfiType(ch);
//            } else {
//                params[i - 1] = getFfiType(ch);
//            }
//        }
//    }


//    /**
//     * sign example: vii*lfd
//     * -> void(int, int, void *, long, float, double)
//     **/
//    int LuaCall_Invoke(lua_State *L) {
//        intptr_t address = luaL_checkinteger(L, 1);
//        const char *sign = luaL_optlstring(L, 2, nullptr, nullptr);
//        size_t signSize = strlen(sign);
//        if (signSize == 0) {
//            lua_pushstring(L, "sign is empty");
//            lua_error(L);
//        }
//        size_t paramSize = signSize - 1;
//        ffi_cif cif;
//        ffi_type *returnType;
//        ffi_type *params[signSize - 1];
//        void *args[signSize - 1];
//        void *result;
//        try {
//            ParseFnParam(sign, returnType, params);
//        } catch (const std::exception &e) {
//            lua_pushstring(L, e.what());
//            lua_error(L);
//        }
//
//        uint64_t memForArgs[paramSize + 1];
//        result = &memForArgs[paramSize];
//        for (int i = 0; i < paramSize; i++) {
//            if (sign[i + 1] == '*') {
//                *(uint64_t * ) & memForArgs[i] = luautils::toValue<uint64_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'B') {
//                *(uint8_t * ) & memForArgs[i] = luautils::toValue<uint8_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'b') {
//                *(int8_t * ) & memForArgs[i] = luautils::toValue<int8_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'S') {
//                *(uint16_t * ) & memForArgs[i] = luautils::toValue<uint16_t>(L, 3 + i);
//            } else if (sign[i + 1] == 's') {
//                *(int16_t * ) & memForArgs[i] = luautils::toValue<int16_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'I') {
//                *(uint32_t * ) & memForArgs[i] = luautils::toValue<uint32_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'i') {
//                *(int32_t * ) & memForArgs[i] = luautils::toValue<int32_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'L') {
//                *(uint64_t * ) & memForArgs[i] = luautils::toValue<uint64_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'l') {
//                *(int64_t * ) & memForArgs[i] = luautils::toValue<int64_t>(L, 3 + i);
//            } else if (sign[i + 1] == 'f') {
//                *(float *) &memForArgs[i] = luautils::toValue<float>(L, 3 + i);
//            } else if (sign[i + 1] == 'd') {
//                *(double *) &memForArgs[i] = luautils::toValue<double>(L, 3 + i);
//            } else if (sign[i + 1] == 'z') {
//                *(uint8_t * ) & memForArgs[i] = luautils::toValue<bool>(L, 3 + i) ? 1 : 0;
//            } else if (sign[i + 1] == 'c') {
//                const char *theStr = luautils::toValue<const char *>(L, 3 + i);
//                *(intptr_t *) &memForArgs[i] = (intptr_t) theStr;
//            }
//            args[i] = &memForArgs[i];
//        }
//        ffi_prep_cif(&cif, ffi_abi::FFI_DEFAULT_ABI, paramSize, returnType, params);
//        ffi_call(&cif, reinterpret_cast<void (*)(void)>(address), result, args);
//        if (returnType == &ffi_type_void) {
//            return 0;
//        }
//        if (sign[0] == '*') {
//            luautils::pushValue<uint64_t>(L, *reinterpret_cast<uint64_t *>(result));
//        } else if (sign[0] == 'B') {
//            luautils::pushValue<uint8_t>(L, *reinterpret_cast<uint8_t *>(result));
//        } else if (sign[0] == 'b') {
//            luautils::pushValue<int8_t>(L, *reinterpret_cast<int8_t *>(result));
//        } else if (sign[0] == 'S') {
//            luautils::pushValue<uint16_t>(L, *reinterpret_cast<uint16_t *>(result));
//        } else if (sign[0] == 's') {
//            luautils::pushValue<int16_t>(L, *reinterpret_cast<int16_t *>(result));
//        } else if (sign[0] == 'I') {
//            luautils::pushValue<uint32_t>(L, *reinterpret_cast<uint32_t *>(result));
//        } else if (sign[0] == 'i') {
//            luautils::pushValue<int32_t>(L, *reinterpret_cast<int32_t *>(result));
//        } else if (sign[0] == 'L') {
//            luautils::pushValue<uint64_t>(L, *reinterpret_cast<uint64_t *>(result));
//        } else if (sign[0] == 'l') {
//            luautils::pushValue<int64_t>(L, *reinterpret_cast<int64_t *>(result));
//        } else if (sign[0] == 'f') {
//            luautils::pushValue<float>(L, *reinterpret_cast<float *>(result));
//        } else if (sign[0] == 'd') {
//            luautils::pushValue<double>(L, *reinterpret_cast<double *>(result));
//        } else if (sign[0] == 'z') {
//            luautils::pushValue<bool>(L, (*(int8_t * )(result) & 1) != 0);
//        } else if (sign[0] == 'c') {
//            luautils::pushValue<const char *>(L, (const char *) *(intptr_t *) (result));
//        }
//        return 1;
//    }

//    int LuaCall_CreateClosure(lua_State *L) {
//        if (!lua_isfunction(L, 2)) {
//            lua_pushstring(L, "param 2 is not a function");
//            lua_error(L);
//        }
//        const char *sign = luaL_optlstring(L, 1, nullptr, nullptr);
//        int signSize = strlen(sign);
//        int paramSize = signSize - 1;
//        if (signSize == 0) {
//            lua_pushstring(L, "sign is empty");
//            lua_error(L);
//        }
//        ffi_cif cif;
//        ffi_type *returnType;
//        ffi_type *params[paramSize];
//        void *func;
//        ffi_closure *closure;
//
//        try {
//            ParseFnParam(sign, returnType, params);
//        } catch (const std::exception &e) {
//            lua_pushstring(L, e.what());
//            lua_error(L);
//        }
//
//
//        ffi_prep_cif(&cif, FFI_DEFAULT_ABI, paramSize, returnType, params);
//        closure = reinterpret_cast<ffi_closure *>(ffi_closure_alloc(sizeof(ffi_closure), &func));
//        lua_pushvalue(L, 2);
//        int *ref = reinterpret_cast<int *>(malloc(sizeof(int)));
//        *ref = luaL_ref(L, LUA_REGISTRYINDEX);
//        ffi_prep_closure_loc(closure, &cif,
//                             [](ffi_cif *cif, void *ret, void *args[], void *user_data) {
//                                 lua_geti(lua_state, LUA_REGISTRYINDEX,
//                                          *reinterpret_cast<int *>(user_data));
//
//                                 for (int i = 0; i < cif->nargs; i++) {
//                                     if (cif->arg_types[i] == &ffi_type_pointer) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<uint64_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_uint8) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<uint8_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_sint8) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<int8_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_uint16) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<uint16_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_sint16) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<int16_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_uint32) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<uint32_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_sint32) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<int32_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_uint64) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<uint64_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_sint64) {
//                                         lua_pushinteger(lua_state,
//                                                        *reinterpret_cast<int64_t *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_float) {
//                                         lua_pushnumber(lua_state,
//                                                        *reinterpret_cast<float *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_double) {
//                                         lua_pushnumber(lua_state,
//                                                        *reinterpret_cast<double *>(args[i]));
//                                     } else if (cif->arg_types[i] == &ffi_type_longdouble) {
//                                         lua_pushnumber(lua_state,
//                                                        *reinterpret_cast<long double *>(args[i]));
//                                     }
//                                 }
//
//                                 lua_pcall(lua_state, cif->nargs, 1, 0);
//                                 ffi_type *returnType = cif->rtype;
//                                 if (returnType == &ffi_type_void) {
//                                     ret = nullptr;
//                                 } else if (returnType == &ffi_type_pointer) {
//                                     *reinterpret_cast<uint64_t *>(ret) = luaL_checknumber(
//                                             lua_state, -1);
//                                 } else if (returnType == &ffi_type_uint8) {
//                                     *reinterpret_cast<uint8_t *>(ret) = luaL_checknumber(lua_state,
//                                                                                          -1);
//                                 } else if (returnType == &ffi_type_sint8) {
//                                     *reinterpret_cast<int8_t *>(ret) = luaL_checknumber(lua_state,
//                                                                                         -1);
//                                 } else if (returnType == &ffi_type_uint16) {
//                                     *reinterpret_cast<uint16_t *>(ret) = luaL_checknumber(
//                                             lua_state, -1);
//                                 } else if (returnType == &ffi_type_sint16) {
//                                     *reinterpret_cast<int16_t *>(ret) = luaL_checknumber(lua_state,
//                                                                                          -1);
//                                 } else if (returnType == &ffi_type_uint32) {
//                                     *reinterpret_cast<uint32_t *>(ret) = luaL_checknumber(
//                                             lua_state, -1);
//                                 } else if (returnType == &ffi_type_sint32) {
//                                     *reinterpret_cast<int32_t *>(ret) = luaL_checknumber(lua_state,
//                                                                                          -1);
//                                 } else if (returnType == &ffi_type_uint64) {
//                                     *reinterpret_cast<uint64_t *>(ret) = luaL_checknumber(
//                                             lua_state, -1);
//                                 } else if (returnType == &ffi_type_sint64) {
//                                     *reinterpret_cast<int64_t *>(ret) = luaL_checknumber(lua_state,
//                                                                                          -1);
//                                 } else if (returnType == &ffi_type_float) {
//                                     *reinterpret_cast<float *>(ret) = luaL_checknumber(lua_state,
//                                                                                        -1);
//                                 } else if (returnType == &ffi_type_double) {
//                                     *reinterpret_cast<double *>(ret) = luaL_checknumber(lua_state,
//                                                                                         -1);
//                                 } else if (returnType == &ffi_type_longdouble) {
//                                     *reinterpret_cast<long double *>(ret) = luaL_checknumber(
//                                             lua_state, -1);
//                                 }
//                             }, ref, func);
//        luautils::pushValue<uint64_t>(L, reinterpret_cast<uint64_t>(func));
//        luautils::pushValue<uint64_t>(L, reinterpret_cast<uint64_t>(func));
//        luautils::pushValue<uint64_t>(L, reinterpret_cast<uint64_t>(ref));
//        return 0;
//    }

    int LuaCall_HookFunction(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        intptr_t replaced = luaL_checkinteger(L, 2);
        intptr_t original = 0;
        MSHookFunction(reinterpret_cast<void *>(address), reinterpret_cast<void *>(replaced),
                       reinterpret_cast<void **>(&original));
        luautils::pushValue(L, original);
        return 1;
    }

//    int LuaCall_ReleaseClosure(lua_State *L) {
//        intptr_t closure = luaL_checkinteger(L, 1);
//        intptr_t ref = luaL_checkinteger(L, 2);
//        ffi_closure_free(reinterpret_cast<void *>(closure));
//        free(reinterpret_cast<void *>(ref));
//        return 0;
//    }

    int LuaCall_dlopen(lua_State *L) {
        const char *name = luaL_optlstring(L, 1, nullptr, nullptr);
        int32_t flag = luaL_checkinteger(L, 2);
        intptr_t handle = reinterpret_cast<intptr_t>(dlopen(name, flag));
        lua_pushinteger(L, handle);
        return 1;
    }

    int LuaCall_dlsym(lua_State *L) {
        void *handle = reinterpret_cast<void *>(luaL_checkinteger(L, 1));
        const char *name = luaL_optlstring(L, 2, nullptr, nullptr);
        intptr_t ptr = reinterpret_cast<intptr_t>(dlsym(handle, name));
        lua_pushinteger(L, ptr);
        return 1;
    }

    int LuaCall_dlclose(lua_State *L) {
        void *handle = reinterpret_cast<void *>(luaL_checkinteger(L, 1));
        int result = dlclose(handle);
        lua_pushinteger(L, result);
        return 1;
    }

    int LuaCall_getBoolean(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        bool value = *(bool *) address;
        lua_pushboolean(L, value);
        return 1;
    }

    int LuaCall_setBoolean(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        bool value = lua_toboolean(L, 2);
        *(bool *) address = value;
        return 0;
    }

    int LuaCall_getInt8(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int8_t value = *(int8_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setInt8(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int8_t value = luaL_checkinteger(L, 2);
        *(int8_t *) address = value;
        return 0;
    }

    int LuaCall_getInt16(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int16_t value = *(int16_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setInt16(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int16_t value = luaL_checkinteger(L, 2);
        *(int16_t *) address = value;
        return 0;
    }

    int LuaCall_getInt32(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int32_t value = *(int32_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setInt32(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int32_t value = luaL_checkinteger(L, 2);
        *(int32_t *) address = value;
        return 0;
    }

    int LuaCall_getInt64(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int64_t value = *(int64_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setInt64(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        int64_t value = luaL_checkinteger(L, 2);
        *(int64_t *) address = value;
        return 0;
    }

    int LuaCall_getUInt8(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        uint8_t value = *(uint8_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setUInt8(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        uint8_t value = luaL_checkinteger(L, 2);
        *(uint8_t *) address = value;
        return 0;
    }

    int LuaCall_getUInt16(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        uint16_t value = *(uint16_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setUInt16(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        uint16_t value = luaL_checkinteger(L, 2);
        *(uint16_t *) address = value;
        return 0;
    }

    int LuaCall_getUInt32(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        uint32_t value = *(uint32_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setUInt32(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        uint32_t value = luaL_checkinteger(L, 2);
        *(uint32_t *) address = value;
        return 0;
    }

    int LuaCall_getPointer(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        intptr_t value = *(intptr_t *) address;
        lua_pushinteger(L, value);
        return 1;
    }

    int LuaCall_setPointer(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        intptr_t value = luaL_checkinteger(L, 2);
        *(intptr_t *) address = value;
        return 0;
    }

    int LuaCall_getFloat32(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        float value = *(float *) address;
        lua_pushnumber(L, value);
        return 1;
    }

    int LuaCall_setFloat32(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        float value = (float) luaL_checknumber(L, 2);
        *(float *) address = value;
        return 0;
    }

    int LuaCall_getFloat64(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        double value = *(double *) address;
        lua_pushnumber(L, value);
        return 1;
    }

    int LuaCall_setFloat64(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        double value = luaL_checknumber(L, 2);
        *(double *) address = value;
        return 0;
    }

    int LuaCall_getCString8(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        const char *value = (const char *) address;
        lua_pushstring(L, value);
        return 1;
    }

    int LuaCall_malloc(lua_State *L) {
        size_t memSize = luaL_checkinteger(L, 1);
        void *memory = malloc(memSize);
        intptr_t address = (intptr_t) memory;
        lua_pushinteger(L, address);
        return 1;
    }

    int LuaCall_free(lua_State *L) {
        intptr_t address = luaL_checkinteger(L, 1);
        void *memory = (void *) address;
        free(memory);
        return 0;
    }

    inline int64_t getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        return milliseconds.count();
    }

    int LuaCall_getTime(lua_State *L) {
        lua_pushinteger(L, (int64_t) getCurrentTimestamp());
        return 1;
    }

    const int PRINT_BUFFER_SIZE = 256;
    char gPrintBuffer[PRINT_BUFFER_SIZE];
    std::ofstream fout;

    inline void LogToJava(const char *tag, const char *level, const char *message) {
        JNIInteraction::SendPacket("LogToJava", tag, level, message);
    }

    int LuaCall_log(lua_State *L) {
        auto tag = luaL_optlstring(L, 1, nullptr, nullptr);
        auto level = luaL_optlstring(L, 2, nullptr, nullptr);
        auto message = luaL_optlstring(L, 3, nullptr, nullptr);
        LogToJava(tag, level, message);
        return 0;
    }

    int LuaCall_print(lua_State *L) {
        int n = lua_gettop(L);  /* number of arguments */
        int i;
        char *gPrintPtr = gPrintBuffer;
        int index = 0;
        for (i = 1; i <= n; i++) {  /* for each argument */
            size_t l;
            const char *s = luaL_tolstring(L, i, &l);  /* convert it to string */
            if (i > 1)  /* not the first element? */
            {
                index++;
                if (index >= PRINT_BUFFER_SIZE) {
                    *gPrintPtr++ = 0;
                    utils::LogDebug(gPrintBuffer);
                    fout << gPrintBuffer << std::endl;
                    gPrintPtr = gPrintBuffer;
                    index = 1;
                }
                *gPrintPtr++ = '\t';  /* add a tab before it */
            }
            for (int j = 0; j < l; j++) {
                index++;
                if (index >= PRINT_BUFFER_SIZE) {
                    *gPrintPtr++ = 0;
                    utils::LogDebug(gPrintBuffer);
                    fout << gPrintBuffer << std::endl;
                    gPrintPtr = gPrintBuffer;
                    index = 1;
                }
                *gPrintPtr++ = *s++;  /* print it */
            }
            lua_pop(L, 1);  /* pop result */
        }
        *gPrintPtr++ = 0;
        utils::LogDebug(gPrintBuffer);
        LogToJava("print", "Info", gPrintBuffer);
        return 0;
    }

    bool Init() {
        utils::LogDebug("Initialize lua script");
        ReleaseScriptsInAsset();

        lua_state = luaL_newstate();
        const luaL_Reg *lib = luaLibraries;
        while (lib->func) {
            luaL_requiref(lua_state, lib->name, lib->func, 1);
            utils::LogDebug("finish loading core lib %s", lib->name);
            lua_pop(lua_state, 1);
            lib++;
        }
        lua_register(lua_state, "getBoolean", LuaCall_getBoolean);
        lua_register(lua_state, "setBoolean", LuaCall_setBoolean);
        lua_register(lua_state, "getInt8", LuaCall_getInt8);
        lua_register(lua_state, "setInt8", LuaCall_setInt8);
        lua_register(lua_state, "getInt16", LuaCall_getInt16);
        lua_register(lua_state, "setInt16", LuaCall_setInt16);
        lua_register(lua_state, "getInt32", LuaCall_getInt32);
        lua_register(lua_state, "setInt32", LuaCall_setInt32);
        lua_register(lua_state, "getInt64", LuaCall_getInt64);
        lua_register(lua_state, "setInt64", LuaCall_setInt64);
        lua_register(lua_state, "getUInt8", LuaCall_getUInt8);
        lua_register(lua_state, "setUInt8", LuaCall_setUInt8);
        lua_register(lua_state, "getUInt16", LuaCall_getUInt16);
        lua_register(lua_state, "setUInt16", LuaCall_setUInt16);
        lua_register(lua_state, "getUInt32", LuaCall_getUInt32);
        lua_register(lua_state, "setUInt32", LuaCall_setUInt32);
        lua_register(lua_state, "getPointer", LuaCall_getPointer);
        lua_register(lua_state, "setPointer", LuaCall_setPointer);
        lua_register(lua_state, "getFloat32", LuaCall_getFloat32);
        lua_register(lua_state, "setFloat32", LuaCall_setFloat32);
        lua_register(lua_state, "getFloat64", LuaCall_getFloat64);
        lua_register(lua_state, "setFloat64", LuaCall_setFloat64);
        lua_register(lua_state, "getCString8", LuaCall_getCString8);
        lua_register(lua_state, "getTime", LuaCall_getTime);
        lua_register(lua_state, "malloc", LuaCall_malloc);
        lua_register(lua_state, "free", LuaCall_free);
        lua_register(lua_state, "__log", LuaCall_log);
        lua_register(lua_state, "print", LuaCall_print);
//        lua_register(lua_state, "invoke", LuaCall_Invoke);
//        lua_register(lua_state, "createClosure", LuaCall_CreateClosure);
//        lua_register(lua_state, "releaseClosure", LuaCall_ReleaseClosure);
        lua_register(lua_state, "hookFunction", LuaCall_HookFunction);
        lua_register(lua_state, "dlopen", LuaCall_dlopen);
        lua_register(lua_state, "dlsym", LuaCall_dlsym);
        lua_register(lua_state, "dlclose", LuaCall_dlclose);

        return true;
    }
}