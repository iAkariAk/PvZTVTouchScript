package com.fairy.tv;

import android.app.Application;

import com.google.android.material.color.DynamicColors;

public class MyApplication extends Application {
    public static MyApplication INSTANCE = null;

    @Override
    public void onCreate() {
        DynamicColors.applyToActivitiesIfAvailable(this);
        super.onCreate();
        INSTANCE = this;
        CrashHandler.applyToApplication(this);
    }
}

