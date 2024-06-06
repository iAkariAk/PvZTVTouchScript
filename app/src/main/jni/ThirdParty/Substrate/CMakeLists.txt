add_library(Substrate STATIC
        hde64.c
        SubstrateDebug.cpp
        SubstrateHook.cpp
        SubstratePosixMemory.cpp
        SymbolFinder.cpp
)
target_include_directories(Substrate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
