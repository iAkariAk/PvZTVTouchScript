add_library(KittyMemory STATIC
        KittyMemory.cpp
        MemoryPatch.cpp
        MemoryBackup.cpp
        KittyUtils.cpp
)
target_include_directories(KittyMemory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
