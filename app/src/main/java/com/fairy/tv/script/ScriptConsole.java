package com.fairy.tv.script;

import android.app.Activity;
import android.graphics.Color;
import android.graphics.Typeface;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

import androidx.annotation.NonNull;
import androidx.cardview.widget.CardView;
import androidx.core.widget.NestedScrollView;
import androidx.recyclerview.widget.RecyclerView;

import com.fairy.tv.floating.FloatingController;
import com.fairy.tv.floating.FloatingLauncher;
import com.fairy.tv.floating.weight.FloatingDraggableAreas;
import com.fairy.tv.util.Pixels;
import com.google.android.material.button.MaterialButton;
import com.google.android.material.card.MaterialCardView;
import com.google.android.material.color.DynamicColors;
import com.google.android.material.color.utilities.DynamicColor;
import com.google.android.material.textfield.TextInputEditText;
import com.google.android.material.textview.MaterialTextView;
import com.trans.pvztv.R;

import java.lang.ref.WeakReference;

public class ScriptConsole {
    private final Activity activity;
    private final FrameLayout rootContainer;
    private final FloatingController floatingController;
    private final FloatingLauncher floatingLauncher;
    private boolean registered = false;

    public ScriptConsole(Activity activity) {
        this.activity = activity;
        this.rootContainer = new FrameLayout(activity);
        this.floatingController = new FloatingController(new WeakReference<>(activity), rootContainer, FloatingController.defaultLayoutParams());
        this.floatingLauncher = new FloatingLauncher(floatingController);

        build();
    }

    public void register() {
        if (!registered)
            activity.getApplication().registerActivityLifecycleCallbacks(floatingLauncher);
        registered = true;
    }

    public void build() {
        var viewCollapsed = new MaterialButton(activity);
        viewCollapsed.setText("LuaConsole");
        viewCollapsed.setTypeface(Typeface.SERIF);
        FloatingDraggableAreas.asFloatingDraggableArea(viewCollapsed, floatingController);
        rootContainer.addView(viewCollapsed);
        var viewExpended = new MaterialCardView(activity);
        viewExpended.setLayoutParams(new FrameLayout.LayoutParams((int) Pixels.dpToPx(activity, 250), (int) Pixels.dpToPx(activity, 350)));
        var viewExpendedLayout = new LinearLayout(activity);
        viewExpendedLayout.setOrientation(LinearLayout.VERTICAL);
        var viewExpendedScrolledLayout = new NestedScrollView(activity);
        viewExpendedScrolledLayout.addView(viewExpendedLayout);
        viewExpended.addView(viewExpendedScrolledLayout);
        var viewExpendedClose = new MaterialTextView(activity);
        viewExpendedClose.setText("Console");
        viewExpendedClose.setGravity(Gravity.CENTER);
        viewExpendedClose.setTextSize(30);
        viewExpendedClose.setTypeface(Typeface.SERIF);
        viewExpendedClose.setBackgroundColor(Color.GRAY);
        FloatingDraggableAreas.asFloatingDraggableArea(viewExpendedClose, floatingController);
        viewExpendedLayout.addView(viewExpendedClose);
//        var viewExpendedMessages = new RecyclerView(activity);
        var viewExpendedMessages = new MaterialTextView(activity);
        viewExpendedMessages.setHeight((int) Pixels.dpToPx(activity, 200));
        FairyScript.logMessageLiveData.addObserver(message -> viewExpendedMessages.append(message.message()));
        viewExpendedLayout.addView(viewExpendedMessages);
        var viewExpendedExecuteArea = new LinearLayout(activity);
        viewExpendedExecuteArea.setOrientation(LinearLayout.HORIZONTAL);
        var viewExpendedInput = new TextInputEditText(activity);
        var viewExpendedExecute = new TextInputEditText(activity);
        viewExpendedExecuteArea.addView(viewExpendedInput);
        viewExpendedExecuteArea.addView(viewExpendedExecute);
        viewExpendedLayout.addView(viewExpendedExecuteArea);
        viewExpendedClose.setOnClickListener(v -> {
            rootContainer.removeView(viewExpended);
            rootContainer.addView(viewCollapsed);
        });
        viewCollapsed.setOnClickListener(v -> {
            rootContainer.removeView(viewCollapsed);
            rootContainer.addView(viewExpended);
        });
    }
}
