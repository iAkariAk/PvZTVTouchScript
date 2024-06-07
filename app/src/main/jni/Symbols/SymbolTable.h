//
// Created by 23976 on 2024/6/7.
//

#ifndef PVZ_TV_1_1_1_SYMBOLTABLE_H
#define PVZ_TV_1_1_1_SYMBOLTABLE_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <dlfcn.h>
#include "Logger.h"

template<size_t N>
struct template_string {
    char string[N]{};

    constexpr template_string(const char (&arr)[N]) { // NOLINT(*-explicit-constructor)
        std::copy(arr, arr + N, string);
    }
};

template<typename R, typename... Args>
struct function_type {
    using type_fn = R(*)(Args...);
    using type_over_fn = R(*)(type_fn, Args...);
    using type_f = R(Args...);
    using type_r = R;
    using type_args = std::tuple<Args...>;
};

template<template_string _name>
struct library {
    static inline constexpr auto name = _name.string;

    static inline intptr_t baseAddr = [] -> uintptr_t {
        std::ifstream maps("/proc/self/maps");
        std::string line;
        uintptr_t addr = 0;
        if (!maps.is_open()) {
            LOGE("Can not open");
            return 0;
        }
        while (std::getline(maps, line)) {
            if (line.find(name) != std::string::npos) {
                std::stringstream ss(line);
                ss >> std::hex >> addr;
                break;
            }
        }
        LOGD("Base addr: %p", addr);
        return addr;
    }();

    static inline auto dl_handle  = [] {
        return dlopen(_name.string, RTLD_NOLOAD);
    }();
};


template<typename _library, typename T, template_string _name, long _offset>
struct offset_symbol {
    using type = T;
    static inline std::string name = _name.string;

    static T &ref() {
        return *(T *) (_library::baseAddr + _offset);
    }
};

template<typename _library, typename T, template_string _name, template_string _symbol_name>
struct name_symbol {
    using type = T;
    static inline std::string name = _name.string;
    static inline auto ptr = dlsym(_library::dl_handle, _symbol_name.string);
    static inline auto invoke = reinterpret_cast<type::type_fn>(ptr);

    static T &ref() {
        return *(T *) (ptr);
    }
};


#endif //PVZ_TV_1_1_1_SYMBOLTABLE_H
