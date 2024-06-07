#include "Core.h"
#include "Fairy/Def.h"
#include "Fairy/FUtils.h"

namespace fairy::script::core {
    static const luaL_Reg corelib[] = {
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
        lua_pushnumber(L, LIB_PVZ_TV_115);
        lua_setfield(L, -2, "version");
        lua_pushboolean(L, true);
        lua_setfield(L, -2, "isAndroid");
        lua_pushboolean(L, true);
        lua_setfield(L, -2, "is64bits");
        lua_pushboolean(L, true);
        lua_setfield(L, -2, "isArm");
        lua_pushinteger(L, (int64_t) utils::GetLibBaseOffset());
        lua_setfield(L, -2, "baseAddress");
        lua_pushstring(L, "tv_touch_1.1.5");
        lua_setfield(L, -2, "platform");
        lua_newtable(L);
        lua_setfield(L, -2, "onUpdateGame");
        lua_newtable(L);
        lua_setfield(L, -2, "onUpdateChallenge");
        lua_newtable(L);
        lua_setfield(L, -2, "onUpdateApp");
        return 1;
    }
}