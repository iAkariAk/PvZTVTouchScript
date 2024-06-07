package com.fairy.tv.util;

import androidx.annotation.NonNull;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;

public interface DefaultActivityLifecycleCallbacks extends Application.ActivityLifecycleCallbacks {
    @Override
    default void onActivityCreated(@NonNull Activity activity, Bundle savedInstanceState) {
    }

    @Override
    default void onActivityStarted(@NonNull Activity activity) {
    }

    @Override
    default void onActivityResumed(@NonNull Activity activity) {
    }

    @Override
    default void onActivityPaused(@NonNull Activity activity) {
    }

    @Override
    default void onActivityStopped(@NonNull Activity activity) {
    }

    @Override
    default void onActivitySaveInstanceState(@NonNull Activity activity, @NonNull Bundle outState) {
    }

    @Override
    default void onActivityDestroyed(@NonNull Activity activity) {
    }
}
