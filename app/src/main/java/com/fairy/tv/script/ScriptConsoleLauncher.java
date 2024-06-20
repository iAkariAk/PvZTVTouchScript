package com.fairy.tv.script;

import android.app.Activity;
import android.graphics.Typeface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;

import com.fairy.tv.floating.FloatingController;
import com.fairy.tv.floating.FloatingLauncher;
import com.fairy.tv.floating.widget.FloatingDraggableAreas;
import com.fairy.tv.util.Pixels;
import com.google.android.material.button.MaterialButton;
import com.google.android.material.card.MaterialCardView;
import com.google.android.material.dialog.MaterialAlertDialogBuilder;
import com.google.android.material.textfield.TextInputEditText;
import com.trans.pvztv.databinding.FloatingConsoleBinding;

import java.lang.ref.WeakReference;
import java.util.Objects;

public class ScriptConsoleLauncher extends FloatingLauncher {
    private final Activity activity;
    private final FloatingController floatingController;
    private final FrameLayout rootContainer;
    private FloatingConsoleBinding binding;

    public ScriptConsoleLauncher(Activity activity) {
        super(new FloatingController(
                new WeakReference<>(activity),
                new FrameLayout(activity),
                FloatingController.defaultLayoutParams()
        ));
        this.activity = activity;
        this.floatingController = floatingController();
        this.rootContainer = (FrameLayout) floatingController.getView();
    }

    @Override
    public void onActivityCreated(@NonNull Activity activity, Bundle savedInstanceState) {
        super.onActivityCreated(activity, savedInstanceState);
        var viewExpended = new MaterialCardView(this.activity);
        viewExpended.setLayoutParams(new FrameLayout.LayoutParams((int) Pixels.dpToPx(this.activity, 250), (int) Pixels.dpToPx(this.activity, 350)));
        viewExpended.setVisibility(View.GONE);
        rootContainer.addView(viewExpended);
        binding = FloatingConsoleBinding.inflate(LayoutInflater.from(activity), viewExpended, false);
        var viewExpendedContent = binding.getRoot();
        viewExpended.addView(viewExpendedContent);

        var viewCollapsed = new MaterialButton(activity);
        viewCollapsed.setText("LuaConsole");
        viewCollapsed.setTypeface(Typeface.SERIF);
        FloatingDraggableAreas.makeDraggable(viewCollapsed, floatingController);
        FloatingDraggableAreas.makeDraggable(binding.topBar, floatingController);
        rootContainer.addView(viewCollapsed);

        binding.topBar.setOnClickListener(v -> {
            viewExpended.setVisibility(View.GONE);
            viewCollapsed.setVisibility(View.VISIBLE);
        });

        viewCollapsed.setOnClickListener(v -> {
            viewExpended.setVisibility(View.VISIBLE);
            viewCollapsed.setVisibility(View.GONE);
        });

        binding.postScript.setOnClickListener(v -> {
            var viewPostField = new TextInputEditText(activity);
            viewPostField.setHint("Please typing...");
            new MaterialAlertDialogBuilder(activity)
                    .setTitle("Post Script")
                    .setView(viewPostField)
                    .setPositiveButton("Post", (dialog, which) -> {
                        var code = Objects.requireNonNull(viewPostField.getText()).toString();
                        FairyScript.submitExecutionTask(Integer.toString(code.hashCode()), code);;
                    })
                    .show();
        });
    }

    @Override
    public void onActivityDestroyed(@NonNull Activity activity) {
        super.onActivityDestroyed(activity);
        binding = null;
    }

}
