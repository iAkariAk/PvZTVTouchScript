#ifndef PVZFREE_FAIRY_ATTRIBUTE_LUAUTILS_H
#define PVZFREE_FAIRY_ATTRIBUTE_LUAUTILS_H

#include <type_traits>
#include <iostream>
#include "lua.hpp"

namespace fairy::script::luautils {
    template<typename T>
    constexpr bool isNil() {
        return std::is_same<T, std::nullptr_t>();
    }

    template<typename T>
    constexpr bool isInteger() {
        return std::is_same<T, int8_t>()
               || std::is_same<T, int16_t>()
               || std::is_same<T, int32_t>()
               || std::is_same<T, int64_t>()
               || std::is_same<T, uint8_t>()
               || std::is_same<T, uint16_t>()
               || std::is_same<T, uint32_t>()
               || std::is_same<T, uint64_t>();
    }

    template<typename T>
    constexpr bool isNumber() {
        return std::is_same<T, float>()
               || std::is_same<T, double>()
               || std::is_same<T, long double>();
    }

    template<typename T>
    constexpr bool isBoolean() {
        return std::is_same<T, bool>();
    }

    template<typename T>
    constexpr bool isString() {
        return std::is_same<T, char *>()
               || std::is_same<T, const char *>();
    }

    template<typename T>
    constexpr bool isLuaType() {
        return isNil<T>()
               || isInteger<T>()
               || isNumber<T>()
               || isBoolean<T>()
               || std::is_same<T, std::string>()
               || isString<T>();
    }

    template<typename T>
    inline void pushValue(lua_State *state, T value) {
        static_assert(isLuaType<T>(), "Illegal type!");

        if constexpr (isNil<T>()) {
            lua_pushnil(state);
        } else if constexpr (isInteger<T>()) {
            lua_pushinteger(state, value);
        } else if constexpr (isNumber<T>()) {
            lua_pushnumber(state, value);
        } else if constexpr (isBoolean<T>()) {
            lua_pushboolean(state, value);
        } else if constexpr (isString<T>()) {
            lua_pushstring(state, value);
        }
    }

    template<typename T, typename... Ts>
    inline void pushValues(lua_State *state, T value, Ts... values) {
        (pushValue(state, values), ...);
    }

    template<typename T>
    inline T toValue(lua_State *state, int index) {
        static_assert(isLuaType<T>(), "Illegal type!");

        if constexpr (isNil<T>()) {
            return nullptr;
        } else if constexpr (isInteger<T>()) {
            return lua_tointeger(state, index);
        } else if constexpr (isNumber<T>()) {
            return lua_tonumber(state, index);
        } else if constexpr (isBoolean<T>()) {
            return lua_toboolean(state, index);
        } else if constexpr (isString<T>()) {
            return lua_tostring(state, index);
        }
    }
}

#endif //PVZFREE_FAIRY_ATTRIBUTE_LUAUTILS_H
