//
// Created by 23976 on 2024/6/7.
//

#ifndef PVZ_TV_1_1_1_SYMBOLS_H
#define PVZ_TV_1_1_1_SYMBOLS_H

#include <jni.h>
#include "SymbolTable.h"

namespace Libraries {
    using GameMain = library<"libGameMain">;
    using NativeCore = library<"libnative_code.so">;
}

namespace Symbols {
    namespace NativeCore {
        using getEnv = name_symbol<Libraries::NativeCore,
        function_type<void*> ,"Native::NativeApp::getEnv","_ZNK6Native9NativeApp6getEnvEv">;
    }

}

#endif //PVZ_TV_1_1_1_SYMBOLS_H
