package com.transmension.mobile;

import android.media.AudioTrack;

class MobileAudioTrack extends AudioTrack {
    private final int mFrameSize;

    public MobileAudioTrack(int streamType, int sampleRateInHz, int channelConfig, int audioFormat, int bufferSizeInBytes, int mode) throws IllegalArgumentException {
        super(streamType, sampleRateInHz, channelConfig, audioFormat, bufferSizeInBytes, mode);
        this.mFrameSize = audioFormat == 2 ? getChannelCount() * 2 : getChannelCount();
    }

    @Override
    public void play() throws IllegalStateException {
        super.play();
        initBuffer();
    }

    public void initBuffer() {
        byte[] audioData = new byte[getNativeFrameCount() * this.mFrameSize];
        write(audioData, 0, audioData.length);
    }
}