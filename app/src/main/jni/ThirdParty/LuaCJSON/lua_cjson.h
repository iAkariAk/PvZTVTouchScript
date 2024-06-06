//
// Created by 12595 on 2023/7/3.
//

#ifndef LUA_CJSON_H
#define LUA_CJSON_H

#include <assert.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <lua.h>
#include <lauxlib.h>

#include "strbuf.h"
#include "fpconv.h"

int lua_cjson_safe_new(lua_State *l);

#endif //LUA_CJSON_H
