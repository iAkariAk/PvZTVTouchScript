package com.fairy.tv.floating;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;

import com.fairy.tv.util.DefaultActivityLifecycleCallbacks;

public record FloatingLauncher(
        FloatingController floatingController) implements DefaultActivityLifecycleCallbacks {

    @Override
    public void onActivityCreated(@NonNull Activity activity, Bundle savedInstanceState) {
        activity.findViewById(android.R.id.content).post(floatingController::show);

    }

    @Override
    public void onActivityDestroyed(@NonNull Activity activity) {
        floatingController.destroy();
        activity.getApplication().unregisterActivityLifecycleCallbacks(this);
    }
}
