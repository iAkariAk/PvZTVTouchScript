//
// Created by 12595 on 2023/6/23.
//

#ifndef PVZFREE_FAIRY_ATTRIBUTE_SCRIPT_CORE_H
#define PVZFREE_FAIRY_ATTRIBUTE_SCRIPT_CORE_H

#include "Utils.h"
#include "lua.hpp"

namespace fairy::script::core {
    int luaopen_core(lua_State *L);
}

#endif //PVZFREE_FAIRY_ATTRIBUTE_SCRIPT_CORE_H
