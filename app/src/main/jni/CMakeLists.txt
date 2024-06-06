cmake_minimum_required(VERSION 3.9)

set(CMAKE_VERBOSE_MAKEFILE ON)


project(Homura LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(LOCAL_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(JNI_LIBS_DIR ${LOCAL_PATH}/../jniLibs)

# 设置编译选项和链接选项，使用-O3优化级别，允许非标准代码，开启异常处理，关闭所有警告，忽略一些错误，移除无用的段和符号。
add_compile_options(-O3 -fpermissive -fexceptions -w -Wno-error=format-security -Wno-error=c++11-narrowing)
# 设置编译选项和链接选项，隐藏符号信息，
add_compile_options(-fvisibility=hidden)
add_link_options(-Wl,--gc-sections,--strip-all)

add_subdirectory(ThirdParty/Lua)
add_subdirectory(ThirdParty/LuaCJSON)
add_subdirectory(ThirdParty/ThreadPool)
add_subdirectory(ThirdParty/KittyMemory)
add_subdirectory(ThirdParty/Substrate)
add_library(Homura SHARED)
target_sources(Homura PRIVATE
        Main.cpp
)


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif ()

target_include_directories(Homura PUBLIC ${LOCAL_PATH}/)
target_include_directories(Homura PUBLIC ${LOCAL_PATH}/Includes)

find_library(log-lib log)
find_library(android-lib android)
find_library(EGL-lib EGL)
find_library(GLESv2-lib GLESv2)
find_library(OpenSLES-lib OpenSLES)

target_link_libraries(Homura
        Lua
        LuaCJSON
        ThreadPool
        KittyMemory
        Substrate
        ${log-lib}
        ${android-lib}
        ${EGL-lib}
        ${GLESv2-lib}
        ${OpenSLES-lib}
)
