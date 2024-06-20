package com.fairy.tv.floating;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.NonNull;

import com.fairy.tv.util.DefaultActivityLifecycleCallbacks;

import java.util.Objects;

public class FloatingLauncher implements DefaultActivityLifecycleCallbacks {
    protected final FloatingController floatingController;

    public FloatingLauncher(
            FloatingController floatingController) {
        this.floatingController = floatingController;
    }

    @Override
    public void onActivityCreated(@NonNull Activity activity, Bundle savedInstanceState) {
        activity.findViewById(android.R.id.content).post(floatingController::show);

    }

    @Override
    public void onActivityDestroyed(@NonNull Activity activity) {
        floatingController.destroy();
        activity.getApplication().unregisterActivityLifecycleCallbacks(this);
    }

    public FloatingController floatingController() {
        return floatingController;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null || obj.getClass() != this.getClass()) return false;
        var that = (FloatingLauncher) obj;
        return Objects.equals(this.floatingController, that.floatingController);
    }

    @Override
    public int hashCode() {
        return Objects.hash(floatingController);
    }

    @Override
    public String toString() {
        return "FloatingLauncher[" +
                "floatingController=" + floatingController + ']';
    }

}
