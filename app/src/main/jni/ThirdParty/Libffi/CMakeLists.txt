add_library(Libffi STATIC
        ffi.c
        closures.c
        debug.c
        java_raw_api.c
        prep_cif.c
        raw_api.c
        tramp.c
        types.c
        win64_armasm.S
        sysv.S
        )
add_compile_options(-Wimplicit-function-declaration -Wint-conversion)
target_include_directories(Libffi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})