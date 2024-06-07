package com.fairy.tv;

import android.content.res.AssetManager;

public class FairyNative {
    public static native void setAssetManager(AssetManager manager);
    public static native void setCatchDir(String path);
}
