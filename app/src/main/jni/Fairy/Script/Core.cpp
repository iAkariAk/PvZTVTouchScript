#include "Core.h"

namespace fairy::script::core {
    int LuaCall_NewEAString8(lua_State *L) {
        size_t stringSize = 0;
        const char *utf8cstring = luaL_checklstring(L, 1, &stringSize);
        eastl::allocator allocator("EASTL basic_string");
        eastl::string8 *eastring = new eastl::string8(utf8cstring, allocator);
        intptr_t eastring_address = (intptr_t) eastring;
        lua_pushinteger(L, eastring_address);
        return 1;
    }

    int LuaCall_ReleaseEAString8(lua_State *L) {
        intptr_t eastring_address = luaL_checkinteger(L, 1);
        eastl::string8 *eastring = (eastl::string8 *) eastring_address;
        if (eastring) {
            delete eastring;
        }
        return 0;
    }

    int LuaCall_EAString8ToString(lua_State *L) {
        intptr_t eastring_address = luaL_checkinteger(L, 1);
        eastl::string8 *eastring = (eastl::string8 *) eastring_address;
        if (eastring) {
            lua_pushstring(L, eastring->c_str());
        } else {
            lua_pushnil(L);
        }
        return 1;
    }

    int LuaCall_NewEAString16(lua_State *L) {
        size_t stringSize = 0;
        const char *utf8cstring = luaL_checklstring(L, 1, &stringSize);
        std::string utf8string(utf8cstring);
        std::u16string utf16string = utils::String8To16(utf8string);
        const char16_t *utf16cstring = utf16string.c_str();
        eastl::allocator allocator("EASTL basic_string");
        eastl::string16 *eastring = new eastl::string16(utf16cstring, allocator);
        intptr_t eastring_address = (intptr_t) eastring;
        lua_pushinteger(L, eastring_address);
        return 1;
    }

    int LuaCall_ReleaseEAString16(lua_State *L) {
        intptr_t eastring_address = luaL_checkinteger(L, 1);
        eastl::string16 *eastring = (eastl::string16 *) eastring_address;
        if (eastring) {
            delete eastring;
        }
        return 0;
    }

    int LuaCall_EAString16ToString(lua_State *L) {
        intptr_t eastring_address = luaL_checkinteger(L, 1);
        eastl::string16 *eastring = (eastl::string16 *) eastring_address;
        if (eastring) {
            const char16_t *utf16cstring = eastring->c_str();
            std::u16string utf16string(utf16cstring, eastring->size());
            std::string utf8string = utils::String16To8(utf16string);
            lua_pushstring(L, utf8string.c_str());
        } else {
            lua_pushnil(L);
        }
        return 1;
    }

    static const luaL_Reg corelib[] = {
            {"newEAString8",                 LuaCall_NewEAString8},
            {"releaseEAString8",             LuaCall_ReleaseEAString8},
            {"toStringFromEAString8",        LuaCall_EAString8ToString},
            {"newEAString16",                LuaCall_NewEAString16},
            {"releaseEAString16",            LuaCall_ReleaseEAString16},
            {"toStringFromEAString16",       LuaCall_EAString16ToString},
            /* placeholders */
            {"version",                      nullptr},
            {"platform", nullptr},
            {"isAndroid",                    nullptr},
            {"is64bits",                     nullptr},
            {"isArm",                        nullptr},
            {"baseAddress",                  nullptr},
            {"onUpdateGame",                 nullptr},
            {"onUpdateChallenge",            nullptr},
            {"onUpdateApp",                  nullptr},
            {nullptr,                        nullptr}
    };

    int luaopen_core(lua_State *L) {
        luaL_newlib(L, corelib);
        lua_pushnumber(L, LIB_PVZ_3_4_0);
        lua_setfield(L, -2, "version");
        lua_pushboolean(L, true);
        lua_setfield(L, -2, "isAndroid");
        lua_pushboolean(L, true);
        lua_setfield(L, -2, "is64bits");
        lua_pushboolean(L, true);
        lua_setfield(L, -2, "isArm");
        lua_pushinteger(L, (int64_t) utils::GetLibBaseOffset());
        lua_setfield(L, -2, "platform");
#ifdef FLAVOR_CHINESE
        lua_pushstring(L, "free_cn");
#elifdef FLAVOR_VANILLA
        lua_pushstring(L, "free_vanilla");
#endif

        lua_setfield(L, -2, "baseAddress");
        lua_newtable(L);
        lua_setfield(L, -2, "onUpdateGame");
        lua_newtable(L);
        lua_setfield(L, -2, "onUpdateChallenge");
        lua_newtable(L);
        lua_setfield(L, -2, "onUpdateApp");
        return 1;
    }
}