//
// Created by 12595 on 2023/6/17.
//

#ifndef PVZFREE_FAIRY_UTILS_H
#define PVZFREE_FAIRY_UTILS_H

#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <cassert>
#include <chrono>
#include <codecvt>
#include <functional>
#include <vector>
#include <mutex>
#include <jni.h>
#include <list>
#include <locale>
#include <cmath>
#include <new>
#include <span>
#include <sstream>
#include <string>
#include <sys/mman.h>
#include <unistd.h>

#include "Def.h"
#include "SubstrateHook.h"

constexpr char *TAG_FUNCTION_CALL = "XIAN_FUNCTION_CALL";
constexpr char *TAG_LOGGER_FUNCTION_CALL = "TAG_LOGGER_FUNCTION_CALL";
constexpr char *TAG_BASE_ADDRESS = "XIAN_BASE_ADDRESS";

#define REPLACE_FUNCTION(offset, function) (fairy::utils::ReplaceFunction<offset>(&function, nullptr))
#define EXTRA_FUNCTION(offset, function) (fairy::utils::ExtraFunction<offset>(&function, nullptr))
#define OVERRIDE_FUNCTION(offset, function) (fairy::utils::OverrideFunction<offset>(&function, nullptr))
#define WIND_ASSERT(x) (fairy::utils::Assert(x, #x))
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

namespace fairy::utils {
    namespace internal {
        template<uint64_t offset, typename R, typename... Args>
        struct OverrideStaticFunctionWrapper {
            static inline R (*func)(R(*)(Args...), Args...);

            static inline R (*original)(Args...);

            static inline const char *name;

            static R call(Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                R returnValue = func(original, args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
                return returnValue;
#else
                return func(original, args...);
#endif
            }
        };

        template<uint64_t offset, typename... Args>
        struct OverrideStaticFunctionWrapper<offset, void, Args...> {
            static inline void (*func)(void(*)(Args...), Args...);

            static inline void (*original)(Args...);

            static inline const char *name;

            static void call(Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                func(original, args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
#else
                func(original, args...);
#endif
            }
        };

        template<uint64_t offset, typename T, typename R, typename... Args>
        struct OverrideMemberFunctionWrapper {
            static inline R (T::*func)(R(*)(T *, Args...), Args...);

            static inline R (*original)(T *, Args...);

            static inline const char *name;

            static R call(T *instance, Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                R returnValue = (instance->*func)(original, args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
                return returnValue;
#else
                return (instance->*func)(original, args...);
#endif
            }
        };

        template<uint64_t offset, typename T, typename... Args>
        struct OverrideMemberFunctionWrapper<offset, T, void, Args...> {
            static inline void (T::*func)(void(*)(T *, Args...), Args...);

            static inline void (*original)(T *, Args...);

            static inline const char *name;

            static void call(T *instance, Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                (instance->*func)(original, args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
#else
                (instance->*func)(original, args...);
#endif
            }
        };


        template<uint64_t offset, typename R, typename... Args>
        struct ReplaceStaticFunctionWrapper {
            static inline R (*func)(Args...);

            static inline const char *name;

            static R call(Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                R returnValue = func(args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
                return returnValue;
#else
                return func(args...);
#endif
            }
        };

        template<uint64_t offset, typename... Args>
        struct ReplaceStaticFunctionWrapper<offset, void, Args...> {
            static inline void (*func)(Args...);

            static inline const char *name;

            static void call(Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                func(args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
#else
                func(args...);
#endif
            }
        };

        template<uint64_t offset, typename T, typename R, typename... Args>
        struct ReplaceMemberFunctionWrapper {
            static inline R (T::*func)(Args...);

            static inline const char *name;

            static R call(T *instance, Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                R returnValue = (instance->*func)(args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
                return returnValue;
#else
                return (instance->*func)(args...);
#endif
            }
        };

        template<uint64_t offset, typename T, typename... Args>
        struct ReplaceMemberFunctionWrapper<offset, T, void, Args...> {
            static inline void (T::*func)(Args...);

            static inline const char *name;

            static void call(T *instance, Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                (instance->*func)(args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
#else
                (instance->*func)(args...);
#endif
            }
        };


        template<uint64_t offset, typename R, typename... Args>
        struct ExtraStaticFunctionWrapper {
            static inline R (*func)(R, Args...);

            static inline R (*original)(Args...);

            static inline const char *name;

            static R call(Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                R returnValue = original(args...);
                returnValue = func(returnValue, args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
                return returnValue;
#else
                R returnValue = original(args...);
                returnValue = func(returnValue, args...);
                return returnValue;
#endif
            }
        };

        template<uint64_t offset, typename... Args>
        struct ExtraStaticVoidFunctionWrapper {
            static inline void (*func)(Args...);

            static inline void (*original)(Args...);

            static inline const char *name;

            static void call(Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                original(args...);
                func(args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
#else
                original(args...);
                func(args...);
#endif
            }
        };

        template<uint64_t offset, typename T, typename R, typename... Args>
        struct ExtraMemberFunctionWrapper {
            static inline R (T::*func)(R, Args...);

            static inline R (*original)(T *, Args...);

            static inline const char *name;

            static R call(T *instance, Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                R returnValue = original(instance, args...);
                returnValue = (instance->*func)(returnValue, args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
                return returnValue;
#else
                R returnValue = original(instance, args...);
                returnValue = (instance->*func)(returnValue, args...);
                return returnValue;
#endif
            }
        };

        template<uint64_t offset, typename T, typename... Args>
        struct ExtraMemberVoidFunctionWrapper {
            static inline void (T::*func)(Args...);

            static inline void (*original)(T *, Args...);

            static inline const char *name;

            static void call(T *instance, Args... args) {
#ifdef LOG_FUNCTION_NAME
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) Start", name, offset);
                original(instance, args...);
                (instance->*func)(args...);
                if (name) __android_log_print(ANDROID_LOG_DEBUG, TAG_FUNCTION_CALL, "%s(0x%08x) End", name, offset);
#else
                original(instance, args...);
                (instance->*func)(args...);
#endif
            }
        };

        template<uint64_t offset, typename R, typename... Args>
        struct LogFunctionWrapper {
            static inline R (*func)(Args...);

            static inline const char *name;

            static R call(Args... args) {
                R result = func(args...);

                // 这里本来打算constexpr & std::string的,但是这编译器不支持,所以就暂时这样了
                auto message = [&] /* () constexpr */ {
                    std::stringstream ss;
                    ss << std::string(name) << "(";
                    ((ss << std::to_string(args) << ", "), ...);
                    ss.seekp(-2, ss.cur);
                    ss << ") -> " << std::to_string(result) << " // "
                       << std::string(typeid(R).name()) << "(";
                    ((ss << std::string(typeid(args).name()) << ", "), ...);
                    ss.seekp(-2, ss.cur);
                    ss << ") at 0x" << std::hex << offset << "(offset)";
                    return ss.str();
                }();

                __android_log_print(ANDROID_LOG_DEBUG, TAG_LOGGER_FUNCTION_CALL, message.c_str());
                return result;
            }
        };
    }

    extern uint64_t gLibBaseOffset;
    extern JavaVM *gJavaVM;
    extern const char *gLocale;
    extern AAssetManager *gAAssetManager;
    extern std::string gCacheDir;

    /**
     * @brief 初始化一些全局变量和函数指针
     *
     */
    void Init();

    /**
     * @brief 初始化JNI相关的变量和函数
     *
     * @param vm Java虚拟机的指针
     */
    void InitJni(JavaVM *vm);

    /**
     * @brief 获取当前线程的JNIEnv指针
     *
     * 通过Java虚拟机的GetEnv函数，获取当前线程的JNIEnv指针，如果失败则返回nullptr
     *
     * @return 当前线程的JNIEnv指针，或者nullptr
     */
    inline JNIEnv *GetJniEnv() {
        JNIEnv *env;
        if (gJavaVM->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
            return nullptr;
        }
        return env;
    }

    /**
     * @brief 获取so文件的基址偏移量
     *
     * 返回一个全局变量，表示so文件的基址偏移量，该变量在初始化时被赋值
     *
     * @return so文件的基址偏移量
     */
    inline uint64_t GetLibBaseOffset() {
        return gLibBaseOffset;
    }

    /**
     * @brief 通过一个偏移量，获取一个绝对地址
     *
     * 通过GetLibBaseOffset函数，获取so文件的基址偏移量，然后将其与传入的偏移量相加，得到一个绝对地址
     *
     * @param offset 在so文件中的偏移量
     * @return 一个绝对地址，可以用于访问或修改该地址的内容
     */
    inline uint64_t GetAddress(uint64_t offset) {
        return GetLibBaseOffset() + offset;
    }

    inline uint64_t GetRelativeAddress(uint64_t offset) {
        return offset - GetLibBaseOffset();
    }

    inline void Log(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, fmt, args);
        va_end(args);
    }

    inline void LogDebug(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __android_log_vprint(ANDROID_LOG_DEBUG, LOG_TAG, fmt, args);
        va_end(args);
    }

    inline void LogError(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, fmt, args);
        va_end(args);
    }

    // Deprecated
    inline void *GetFunction(uint64_t offset) {
        return (void *) (GetLibBaseOffset() + offset);
    }

    // Deprecated
    inline void *GetConst(uint64_t offset) {
        return (void *) (GetLibBaseOffset() + offset);
    }

    /**
     * @brief 用一个新函数替换旧函数，并在参数中获取到原函数的指针
     *
     * 通过MSHookFunction函数，将旧函数在so文件中的地址和新函数的指针传入，实现函数的替换，并将原函数指针保存在参数中
     *
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param offset 旧函数在so文件中的偏移量
     * @param replaced 新函数的指针
     * @param original 一个指针的引用，用于保存原函数的指针
     */
    template<typename R, typename... Args>
    inline void HookFunction(uint64_t offset, R(*replaced)(Args...), R(*&original)(Args...)) {
        MSHookFunction(reinterpret_cast<void *>(GetAddress(offset)),
                        reinterpret_cast<void *>(replaced),
                        reinterpret_cast<void **>(&original));
    }

    /**
     * @brief 用一个新函数替换旧函数，并在参数中获取到原函数的指针（成员函数专用）
     *
     * 通过MSHookFunction函数，将旧函数在so文件中的地址和新函数的指针传入，实现函数的替换，并将原函数指针保存在参数中
     *
     * @tparam T 成员函数所在类或结构体的类型
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param offset 旧函数在so文件中的偏移量
     * @param replaced 新函数的指针
     * @param original 一个指针的引用，用于保存原函数的指针
     */
    template<typename T, typename R, typename... Args>
    inline void
    HookMemberFunction(uint64_t offset, R(*replaced)(T *, Args...), R(*&original)(T *, Args...)) {
        MSHookFunction(reinterpret_cast<void *>(GetAddress(offset)),
                        reinterpret_cast<void *>(replaced),
                        reinterpret_cast<void **>(&original));
    }

    /**
     * @brief 通过一个偏移量，获取一个函数的指针
     *
     * 通过GetAddress函数，将偏移量转换为绝对地址，然后将其强制转换为函数指针类型
     *
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param offset 函数在so文件中的偏移量
     * @return 一个函数指针，可以用于调用该函数
     */
    template<typename R, typename... Args>
    inline auto GetFunction(uint64_t offset) {
        uint64_t address = GetAddress(offset);
        return reinterpret_cast<R(*)(Args...)>(address);
    }

    /**
     * @brief 通过一个偏移量，调用一个函数，并传入参数
     *
     * 通过GetFunction函数，获取一个函数指针，然后用传入的参数调用该函数
     *
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param offset 函数在so文件中的偏移量
     * @param args 函数的参数
     * @return 函数的返回值
     */
    template<typename R, typename... Args>
    inline R CallFunction(uint64_t offset, Args... args) {
        return GetFunction<R, Args...>(offset)(args...);
    }

    /**
     * @brief 通过一个偏移量，获取一个指针
     *
     * 通过GetAddress函数，将偏移量转换为绝对地址，然后将其强制转换为指针类型
     *
     * @tparam T 指针所指向的类型
     * @param offset 指针在so文件中的偏移量
     * @return 一个指针，可以用于访问该地址的内容
     */
    template<typename T>
    inline T *GetPtr(uint64_t offset) {
        uint64_t address = GetAddress(offset);
        return reinterpret_cast<T *>(address);
    }

    /**
     * @brief 通过一个偏移量，获取一个引用
     *
     * 通过GetPtr函数，获取一个指针，然后解引用该指针，得到一个引用
     *
     * @tparam T 引用所指向的类型
     * @param offset 引用在so文件中的偏移量
     * @return 一个引用，可以用于修改该地址的内容
     */
    template<typename T>
    inline T &GetRef(uint64_t offset) {
        return *GetPtr<T>(offset);
    }

    /**
     * @brief 通过一个偏移量和一个大小，获取一个span对象（固定大小）
     *
     * 通过GetPtr函数，获取一个指针，然后构造一个span对象，表示该地址开始的一段内存区域
     *
     * @tparam T span对象所包含的元素类型
     * @tparam Size span对象所包含的元素个数（固定）
     * @param offset span对象在so文件中的偏移量
     * @return 一个span对象，可以用于遍历或修改该内存区域中的元素
     */
    template<typename T, size_t size>
    inline std::span <T, size> GetSpan(uint64_t offset) {
        return std::span < T, size > (GetPtr<T>(offset), size);
    }

    /**
     * @brief 通过一个偏移量和一个大小，获取一个span对象（动态大小）
     *
     * 通过GetPtr函数，获取一个指针，然后构造一个span对象，表示该地址开始的一段内存区域
     *
     * @tparam T span对象所包含的元素类型
     * @param offset span对象在so文件中的偏移量
     * @param size span对象所包含的元素个数（动态）
     * @return 一个span对象，可以用于遍历或修改该内存区域中的元素
     */
    template<typename T>
    inline std::span <T> GetSpan(uint64_t offset, size_t size) {
        return std::span(GetPtr<T>(offset), size);
    }

    /**
     * @brief 通过一个对象指针和一个成员变量偏移量，获取该成员变量的指针（成员变量专用）
     *
     * 通过将对象指针和成员变量偏移量相加，得到成员变量的绝对地址，然后将其强制转换为指针类型
     *
     * @tparam T 成员变量所属的类型
     * @param thiz 对象指针（任意类型）
     * @param offset 成员变量在对象内部的偏移量
     * @return 一个指针，可以用于访问该成员变量的内容
     */
    template<typename T>
    inline T *GetMemberPtr(auto *thiz, uint64_t offset) {
        uint64_t address = reinterpret_cast<uint64_t>(thiz) + offset;
        return reinterpret_cast<T *>(address);
    }

    /**
     * @brief 通过一个对象指针和一个成员变量偏移量，获取该成员变量的引用（成员变量专用）
     *
     * 通过GetMemberPtr函数，获取一个指针，然后解引用该指针，得到一个引用
     *
     * @tparam T 成员变量所属的类型
     * @param thiz 对象指针（任意类型）
     * @param offset 成员变量在对象内部的偏移量
     * @return 一个引用，可以用于修改该成员变量的内容
     */
    template<typename T>
    inline T &GetMemberRef(auto *thiz, uint64_t offset) {
        return *GetMemberPtr<T>(thiz, offset);
    }

    /**
     * @brief 通过一个对象指针和一个成员变量偏移量，获取该成员变量的span对象（固定大小）（成员变量专用）
     *
     * 通过GetMemberPtr函数，获取一个指针，然后构造一个span对象，表示该成员变量所占的一段内存区域
     *
     * @tparam T span对象所包含的元素类型
     * @tparam Size span对象所包含的元素个数（固定）
     * @param thiz 对象指针（任意类型）
     * @param offset 成员变量在对象内部的偏移量
     * @return 一个span对象，可以用于遍历或修改该成员变量中的元素
     */
    template<typename T, size_t size>
    inline std::span <T, size> GetMemberSpan(auto *thiz, uint64_t offset) {
        return std::span<T, size>(GetMemberPtr<T>(thiz, offset), size);
    }

    /**
     * @brief 通过一个对象指针和一个成员变量偏移量，获取该成员变量的span对象（动态大小）（成员变量专用）
     *
     * 通过GetMemberPtr函数，获取一个指针，然后构造一个span对象，表示该成员变量所占的一段内存区域
     *
     * @tparam T span对象所包含的元素类型
     * @param thiz 对象指针（任意类型）
     * @param offset 成员变量在对象内部的偏移量
     * @param size span对象所包含的元素个数（动态）
     * @return 一个span对象，可以用于遍历或修改该成员变量中的元素
     */
    template<typename T>
    inline std::span <T> GetMemberSpan(auto *thiz, uint64_t offset, size_t size) {
        return std::span(GetMemberPtr<T>(thiz, offset), size);
    }

    /**
     * @brief 用新函数替换旧函数（静态函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，替换掉旧函数
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename R, typename... Args>
    inline auto ReplaceFunction(R(*replaced)(Args...), const char *name) {
        R (*original)(Args...) = nullptr;
        internal::ReplaceStaticFunctionWrapper<offset, R, Args...>::func = replaced;
        internal::ReplaceStaticFunctionWrapper<offset, R, Args...>::name = name;
        HookFunction<R, Args...>(offset,
                                 internal::ReplaceStaticFunctionWrapper<offset, R, Args...>::call,
                                 original);
        return original;
    }

    /**
     * @brief 用新函数替换旧函数（成员函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，替换掉旧函数
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam T 成员函数所在类或结构体的类型
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename T, typename R, typename... Args>
    inline auto ReplaceFunction(R(T::*replaced)(Args...), const char *name) {
        R (*original)(T *, Args...) = nullptr;
        internal::ReplaceMemberFunctionWrapper<offset, T, R, Args...>::func = replaced;
        internal::ReplaceMemberFunctionWrapper<offset, T, R, Args...>::name = name;
        HookMemberFunction<T, R, Args...>(offset,
                                          internal::ReplaceMemberFunctionWrapper<offset, T, R, Args...>::call,
                                          original);
        return original;
    }

    /**
     * @brief 将新函数添加到旧函数后执行（静态函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，将新函数添加到旧函数后执行
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename R, typename... Args>
    inline auto ExtraFunction(R(*replaced)(R, Args...), const char *name) {
        R (*original)(Args...) = nullptr;
        internal::ExtraStaticFunctionWrapper<offset, R, Args...>::func = replaced;
        internal::ExtraStaticFunctionWrapper<offset, R, Args...>::name = name;
        HookFunction<R, Args...>(offset,
                                 internal::ExtraStaticFunctionWrapper<offset, R, Args...>::call,
                                 original);
        internal::ExtraStaticFunctionWrapper<offset, R, Args...>::original = original;
        return original;
    }

    /**
     * @brief 将新函数添加到旧函数后执行（静态无返回值函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，将新函数添加到旧函数后执行
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename... Args>
    inline auto ExtraFunction(void (*replaced)(Args...), const char *name) {
        void (*original)(Args...) = nullptr;
        internal::ExtraStaticVoidFunctionWrapper<offset, Args...>::func = replaced;
        internal::ExtraStaticVoidFunctionWrapper<offset, Args...>::name = name;
        HookFunction<void, Args...>(offset,
                                    internal::ExtraStaticVoidFunctionWrapper<offset, Args...>::call,
                                    original);
        internal::ExtraStaticVoidFunctionWrapper<offset, Args...>::original = original;
        return original;
    }

    /**
     * @brief 将新函数添加到旧函数后执行（成员函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，将新函数添加到旧函数后执行
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam T 成员函数所在类或结构体的类型
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename T, typename R, typename... Args>
    inline auto ExtraFunction(R(T::*replaced)(R, Args...), const char *name) {
        R (*original)(T *, Args...) = nullptr;
        internal::ExtraMemberFunctionWrapper<offset, R, T, Args...>::func = replaced;
        internal::ExtraMemberFunctionWrapper<offset, R, T, Args...>::name = name;
        HookMemberFunction<T, R, Args...>(offset,
                                          internal::ExtraMemberFunctionWrapper<offset, R, T, Args...>::call,
                                          original);
        internal::ExtraMemberFunctionWrapper<offset, R, T, Args...>::original = original;
        return original;
    }

    /**
     * @brief 将新函数添加到旧函数后执行（成员无返回值函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，将新函数添加到旧函数后执行
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam T 成员函数所在类或结构体的类型
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename T, typename... Args>
    inline auto ExtraFunction(void (T::*replaced)(Args...), const char *name) {
        void (*original)(T *, Args...) = nullptr;
        internal::ExtraMemberVoidFunctionWrapper<offset, T, Args...>::func = replaced;
        internal::ExtraMemberVoidFunctionWrapper<offset, T, Args...>::name = name;
        HookMemberFunction<T, void, Args...>(offset,
                                             internal::ExtraMemberVoidFunctionWrapper<offset, T, Args...>::call,
                                             original);
        internal::ExtraMemberVoidFunctionWrapper<offset, T, Args...>::original = original;
        return original;
    }

    /**
     * @brief 用新函数替换旧函数，并在参数中获取到原函数的指针（静态函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，替换掉旧函数
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename R, typename... Args>
    inline auto OverrideFunction(R(*replaced)(R(*)(Args...), Args...), const char *name) {
        R (*original)(Args...) = nullptr;
        internal::OverrideStaticFunctionWrapper<offset, R, Args...>::func = replaced;
        internal::OverrideStaticFunctionWrapper<offset, R, Args...>::name = name;
        HookFunction<R, Args...>(offset,
                                 internal::OverrideStaticFunctionWrapper<offset, R, Args...>::call,
                                 original);
        internal::OverrideStaticFunctionWrapper<offset, R, Args...>::original = original;
        return original;
    }

    /**
     * @brief 用新函数替换旧函数，并在参数中获取到原函数的指针（成员函数专用）
     *
     * 通过新函数的指针和旧函数在so文件中的地址，替换掉旧函数
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam T 成员函数所在类或结构体的类型
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param replaced 新函数的指针
     * @param name 函数名称，用于调试
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename T, typename R, typename... Args>
    inline auto OverrideFunction(R(T::*replaced)(R(*)(T *, Args...), Args...), const char *name) {
        R (*original)(T *, Args...) = nullptr;
        internal::OverrideMemberFunctionWrapper<offset, T, R, Args...>::func = replaced;
        internal::OverrideMemberFunctionWrapper<offset, T, R, Args...>::name = name;
        HookMemberFunction<T, R, Args...>(offset,
                                          internal::OverrideMemberFunctionWrapper<offset, T, R, Args...>::call,
                                          original);
        internal::OverrideMemberFunctionWrapper<offset, T, R, Args...>::original = original;
        return original;
    }

    /**
     * @brief 用一个带有日志功能的函数替换旧函数，并在参数中获取到原函数的指针
     *
     * 通过旧函数在so文件中的地址和一个日志包装器，替换掉旧函数，并将原函数指针保存在包装器中
     *
     * @tparam offset 旧函数在so文件中的地址
     * @tparam R 函数返回类型
     * @tparam Args 函数传参类型
     * @param name 函数名称，用于日志输出
     * @return 一个指针，用于调用旧函数
     */
    template<uint64_t offset, typename R, typename... Args>
    inline auto AddLoggerToFunction(const char *name) {
        R (*original)(Args...) = nullptr;
        internal::LogFunctionWrapper<offset, R, Args...>::name = name;
        HookFunction<R, Args...>(offset,
                                 internal::LogFunctionWrapper<offset, R, Args...>::call,
                                 original);
        internal::LogFunctionWrapper<offset, R, Args...>::func = original;
        return original;
    }

    inline std::string JStringToString(JNIEnv *env, jstring jstr) {
        const char *cstr = env->GetStringUTFChars(jstr, nullptr);
        std::string str(cstr);
        env->ReleaseStringUTFChars(jstr, cstr);
        return str;
    }

    inline bool BooleanArrayAllFalse(bool *array, int size) {
        for (int i = 0; i < size; i++) {
            if (array[i]) {
                return false;
            }
        }
        return true;
    }

    inline std::string String16To8(std::u16string &theString) {
        std::wstring_convert <std::codecvt_utf8<char16_t>, char16_t> converter;
        std::string utf8string = converter.to_bytes(theString);
        return utf8string;
    }

    inline std::u16string String8To16(std::string &theString) {
        std::wstring_convert <std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        std::u16string utf16string = converter.from_bytes(theString);
        return utf16string;
    }

    class TaskQueue {
    public:
        using Task = std::function<void()>;

        void submit(Task task);

        void execute();

    private:
        std::vector <Task> tasks;
        std::mutex tasksMutex;
    };

    inline template<typename C, typename... Args>

    C *InGameNew(Args... args) {
        C *object = (C *) CallFunction<void *, size_t>(0x123ED94, sizeof(C));
        new(object)C(args...);
        return object;
    }

    inline template

    <typename C> void InGameDelete(C *object) {
        if (object) {
            CallFunction<void, void *>(0x123EE14, (void *) object);
        }
    }

    inline template<typename C, typename... Args>

    C *InGameNewArray(size_t size, Args... args) {
        C *object = (C *) CallFunction<void *, size_t>(0x123F138, sizeof(C) * size);
        for (size_t i = 0; i < size; i++) {
            new(object++)C(args...);
        }
        return object;
    }

    inline template

    <typename C> void InGameDeleteArray(C *object) {
        if (object) {
            CallFunction<void, size_t>(0x123F3E4, (size_t) object);
        }
    }

    inline void Assert(bool condition, const char *info) {
        if (!condition) {
            LogError("Wind Assert Error: %s", info);
        }
    }

    inline bool ProtectMemory(void *addr, size_t length, int protection) {
        long sys_page_size = sysconf(_SC_PAGE_SIZE);
        uintptr_t pageStart = ((uintptr_t) addr & ~(uintptr_t) (sys_page_size - 1));
        uintptr_t pageEnd = ((uintptr_t)((uintptr_t) addr + length - 1) &
                             ~(uintptr_t)(sys_page_size - 1));
        uintptr_t pageLen = pageEnd - pageStart + sys_page_size;
        return mprotect(reinterpret_cast<void *>(pageStart), pageLen, protection) != -1;
    }

    inline bool UnlockMemory(void *addr, size_t length) {
        return ProtectMemory(addr, length, PROT_READ | PROT_WRITE | PROT_EXEC);
    }

    inline bool LockMemory(void *addr, size_t length) {
        return ProtectMemory(addr, length, PROT_READ | PROT_EXEC);
    }

    template<typename T>
    inline bool UnlockMemory(T *addr) {
        return UnlockMemory(addr, sizeof(T));
    }

    template<typename T>
    inline bool LockMemory(T *addr) {
        return LockMemory(addr, sizeof(T));
    }

    inline bool PatchMemory(uint64_t addr, size_t length, ...) {
        va_list args;
        va_start(args, length);
        uint64_t readAddr = GetAddress(addr);
        utils::UnlockMemory((void *) readAddr, length);
        unsigned char *readArr = (unsigned char *) readAddr;
        for (size_t i = 0; i < length; i++) {
            readArr[i] = va_arg(args, unsigned char);
        }
        utils::LockMemory((void *) readAddr, length);
        va_end(args);
    }

    inline std::string GetFolderName(const std::string &path) {
        size_t lastSlashPos = path.find_last_of("/");
        if (lastSlashPos != std::string::npos) {
            return path.substr(0, lastSlashPos);
        }
        return "";
    }

    void ClearFolder(const std::string &path, bool clearSubFolder = true);

    class FrameShower {
        int64_t mTime;
        int mFrames;
        std::string mDebugInfo;

    public:
        inline FrameShower(const char *debugInfo) {
            mTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            mFrames = 0;
            mDebugInfo = debugInfo;
            mDebugInfo += ": %d";
        }

        inline void Update(int frames = 1) {
            mFrames += frames;
            if (std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count() >= mTime + 1000) {
                mTime += 1000;
                fairy::utils::LogDebug(mDebugInfo.c_str(), mFrames);
                mFrames = 0;
            }
        }
    };
}
#endif //PVZFREE_FAIRY_UTILS_H
