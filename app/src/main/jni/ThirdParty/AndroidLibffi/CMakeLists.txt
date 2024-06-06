add_library(AndroidLibffi STATIC
        closures.c
        debug.c
        java_raw_api.c
        prep_cif.c
        raw_api.c
        types.c
        sysv.S
        ffi.c
        )
add_compile_options(
        -Wall
        -Werror
        -Wno-error=incompatible-pointer-types
        -Wno-incompatible-pointer-types
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-null-pointer-arithmetic
        -Wno-pointer-arith
        -Wno-sign-compare
        -Wno-unused-parameter
        -Wno-unused-result
        )
target_include_directories(AndroidLibffi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})