//
// Created by Administrator on 2024/5/31.
//

#ifndef PVZ_TV_1_1_5_OPENSL_H
#define PVZ_TV_1_1_5_OPENSL_H

#include <jni.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

namespace Native {
    class NativeApp;

    class AudioOutput {
    public:
        Native::NativeApp *mNativeApp;
        JNIEnv* mEnv;
        bool mUnkBool;
    };
}
//
//bool Native_AudioOutput_setup(Native::AudioOutput *audioOutput, int sampleRate, int channels, int bits);
//void Native_AudioOutput_shutdown(Native::AudioOutput *audioOutput);
//int Native_AudioOutput_write(Native::AudioOutput *audioOutput, const void *a2, int a3);

#endif //PVZ_TV_1_1_5_OPENSL_H
