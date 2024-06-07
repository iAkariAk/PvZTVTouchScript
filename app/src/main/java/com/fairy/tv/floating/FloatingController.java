package com.fairy.tv.floating;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.PixelFormat;
import android.os.Build;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;

import java.lang.ref.WeakReference;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Supplier;

public class FloatingController {
    public FloatingController(WeakReference<Activity> activity, View view, WindowManager.LayoutParams layoutParams) {
        this.activity = activity;
        this.view = view;
        this.layoutParams = layoutParams;
        windowManager = activity.get().getWindowManager();
    }

    public static WindowManager.LayoutParams defaultLayoutParams() {
        var lp = new WindowManager.LayoutParams(
                /* w = */ WindowManager.LayoutParams.WRAP_CONTENT,
                /* h = */ WindowManager.LayoutParams.WRAP_CONTENT,
                /* xpos = */ 150,
                /* ypos = */ 150,
                /* _type = */ WindowManager.LayoutParams.TYPE_APPLICATION_PANEL,
                /* _flags = */ WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN | WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE,
                /* _format = */ PixelFormat.TRANSLUCENT
        );
        lp.gravity = Gravity.START | Gravity.TOP;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            lp.layoutInDisplayCutoutMode =
                    WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }
        return lp;
    }

    private final WeakReference<Activity> activity;
    private final WindowManager windowManager;

    private final View view;
    private WindowManager.LayoutParams layoutParams;

    private boolean shown = false;

    public View getView() {
        return view;
    }

    public WindowManager.LayoutParams getLayoutParams() {
        return layoutParams;
    }

    @SuppressLint("NewApi")
    public void setLayoutParams(Consumer<WindowManager.LayoutParams> edit) {
        edit.accept(layoutParams);
        windowManager.updateViewLayout(view, layoutParams);
    }

    public void show() {
        if (!shown && activity.get() != null) {
            windowManager.addView(view, layoutParams);
            shown = true;
            Log.i("FL", "show");
        }
    }

    public void destroy() {
        if (shown && activity.get() != null) {
            windowManager.removeView(view);
            shown = false;
        }
    }


    public boolean isShown() {
        return shown;
    }

    public void move(int x, int y) {
        setLayoutParams(lp -> {
            lp.x = x;
            lp.y = y;
        });
    }

    public void offset(int ox, int oy) {
        setLayoutParams(lp -> {
            lp.x += ox;
            lp.y += oy;
        });
    }
}
