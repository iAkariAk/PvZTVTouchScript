//
// Created by Administrator on 2024/5/31.
//

#include <jni.h>
#include "OpenSL.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <pthread.h>

// 同步机制变量
pthread_mutex_t mutex;
pthread_cond_t cond;
bool bufferConsumed = false;

// OpenSL ES engine interfaces
static SLObjectItf engineObject = nullptr;
static SLEngineItf engineEngine = nullptr;

// Output mix interfaces
static SLObjectItf outputMixObject = nullptr;

// Player interfaces
static SLObjectItf playerObject = nullptr;
static SLPlayItf playerPlay = nullptr;
static SLAndroidSimpleBufferQueueItf playerBufferQueue = nullptr;

// Buffer
static unsigned char buffer[8192];

// Callback to handle buffer queue events
void playerCallback(SLAndroidSimpleBufferQueueItf bq, void *context) {
    pthread_mutex_lock(&mutex);
    bufferConsumed = true;
    pthread_cond_signal(&cond);  // 通知主线程
    pthread_mutex_unlock(&mutex);
}

void waitForBufferConsumption() {
    pthread_mutex_lock(&mutex);
    while (!bufferConsumed) {
        pthread_cond_wait(&cond, &mutex);  // 阻塞等待
    }
    bufferConsumed = false;
    pthread_mutex_unlock(&mutex);
}

// 写入音频数据到音频流
void AudioWrite(const void *data, int dataSize) {
    (*playerBufferQueue)->Enqueue(playerBufferQueue, data, dataSize);
    waitForBufferConsumption();
}

void setup(int sampleRate, int channels, int bits) {
    slCreateEngine(&engineObject, 0, nullptr, 0, nullptr, nullptr);
    (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, nullptr, nullptr);
    (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);

    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 1};
    SLDataFormat_PCM format_pcm = {
            SL_DATAFORMAT_PCM,
            2,
            SL_SAMPLINGRATE_44_1,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN
    };
    SLDataSource audioSrc = {&loc_bufq, &format_pcm};

    // Configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, nullptr};

    // Create audio player
    const SLInterfaceID ids[1] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};
    (*engineEngine)->CreateAudioPlayer(engineEngine, &playerObject, &audioSrc, &audioSnk, 1, ids, req);
    (*playerObject)->Realize(playerObject, SL_BOOLEAN_FALSE);
    (*playerObject)->GetInterface(playerObject, SL_IID_PLAY, &playerPlay);
    (*playerObject)->GetInterface(playerObject, SL_IID_BUFFERQUEUE, &playerBufferQueue);
    (*playerBufferQueue)->RegisterCallback(playerBufferQueue, playerCallback, nullptr);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

void play() {
    if (playerPlay != nullptr) {
        (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_PLAYING);
    }
}

// Stop playback
void stop() {
    if (playerPlay != nullptr) {
        (*playerPlay)->SetPlayState(playerPlay, SL_PLAYSTATE_STOPPED);
    }
}

// Shutdown and cleanup
void shutdown() {
    if (playerObject != nullptr) {
        (*playerObject)->Destroy(playerObject);
        playerObject = nullptr;
        playerPlay = nullptr;
        playerBufferQueue = nullptr;
    }

    // Destroy the output mix object
    if (outputMixObject != nullptr) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = nullptr;
    }

    // Destroy the engine object
    if (engineObject != nullptr) {
        (*engineObject)->Destroy(engineObject);
        engineObject = nullptr;
        engineEngine = nullptr;
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void (*old_Native_AudioOutput_initialize)(Native::AudioOutput *audioOutput);

void Native_AudioOutput_initialize(Native::AudioOutput *audioOutput) {
    old_Native_AudioOutput_initialize(audioOutput);
}

bool (*old_Native_AudioOutput_setup)(Native::AudioOutput *audioOutput, int sampleRate, int channels, int bits);

bool Native_AudioOutput_setup(Native::AudioOutput *audioOutput, int sampleRate, int channels, int bits) {
    bool result = old_Native_AudioOutput_setup(audioOutput,sampleRate,channels,bits);
    setup(sampleRate,channels,bits);
    play();
    return result;
}

void (*old_Native_AudioOutput_shutdown)(Native::AudioOutput *audioOutput);

void Native_AudioOutput_shutdown(Native::AudioOutput *audioOutput) {
    old_Native_AudioOutput_shutdown(audioOutput);
    stop();
    shutdown();
}

int (*old_Native_AudioOutput_write)(Native::AudioOutput *audioOutput, const void *a2, int a3);

int Native_AudioOutput_write(Native::AudioOutput *audioOutput, const void *a2, int a3) {
//    return old_Native_AudioOutput_write(audioOutput,a2,a3);
    AudioWrite(a2, a3);
    return a3;
}