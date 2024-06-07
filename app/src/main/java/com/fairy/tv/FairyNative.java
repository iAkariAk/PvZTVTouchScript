package com.fairy.tv;

import android.content.res.AssetManager;

import androidx.annotation.Nullable;

public class FairyNative {
    public static native void setAssetManager(AssetManager manager);

    public static native void setCatchDir(String path);

    public static native void sendPacket(String name, String content);

    public static native @Nullable String receivePacket(String name);
}
