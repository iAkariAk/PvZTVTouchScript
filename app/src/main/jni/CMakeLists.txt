cmake_minimum_required(VERSION 3.9)

set(CMAKE_VERBOSE_MAKEFILE ON)


project(Homura LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 23)
set(LOCAL_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(JNI_LIBS_DIR ${LOCAL_PATH}/../jniLibs)

add_compile_options(-O3 -fpermissive -fexceptions -w -Wno-error=format-security -Wno-error=c++11-narrowing)
add_link_options(-Wl,--gc-sections,--strip-all)

file(GLOB_RECURSE GameLogicSource "${CMAKE_SOURCE_DIR}/HookGame/**/*.cpp" "${CMAKE_SOURCE_DIR}/HookGame/**/*.c")

add_subdirectory(ThirdParty/Lua)
add_subdirectory(ThirdParty/LuaCJSON)
add_subdirectory(ThirdParty/ThreadPool)
#add_subdirectory(ThirdParty/AndroidLibffi)
add_subdirectory(ThirdParty/KittyMemory)
add_subdirectory(ThirdParty/Substrate)

add_library(Homura SHARED)
target_sources(Homura PRIVATE
        Main.cpp
        Fairy/FUtils.cpp
        Fairy/JNInteraction.cpp
        Fairy/Script/ScriptInterface.cpp
        Fairy/Script/Core.cpp
)



if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-fvisibility=hidden)
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
#        AndroidLibffi
        KittyMemory
        Substrate
        ${log-lib}
        ${android-lib}
        ${EGL-lib}
        ${GLESv2-lib}
        ${OpenSLES-lib}
)
