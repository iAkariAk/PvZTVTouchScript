package com.fairy.tv.script;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Typeface;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.DialogFragment;
import androidx.recyclerview.widget.LinearLayoutManager;

import com.fairy.tv.floating.FloatingController;
import com.fairy.tv.floating.FloatingLauncher;
import com.fairy.tv.floating.widget.FloatingDraggableAreas;
import com.fairy.tv.util.LimitedList;
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

    @SuppressLint("NotifyDataSetChanged")
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
            viewPostField.setOnLongClickListener(v1 -> {
                new FullInputFragment(viewPostField)
                        .show(((AppCompatActivity) activity).getSupportFragmentManager(), "FullInputFragment");
                return true;
            });
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

        var logMessageList = new LimitedList<LogMessage>(300);
        FairyScript.logMessageLiveData.observe((AppCompatActivity) activity, e -> {
            logMessageList.add(e);
            Objects.requireNonNull(binding.printBuffer.getAdapter()).notifyDataSetChanged();
        });
        binding.printBuffer.setLayoutManager(new LinearLayoutManager(activity));
        binding.printBuffer.setAdapter(new LogBufferItemAdapter(logMessageList));
    }

    @Override
    public void onActivityDestroyed(@NonNull Activity activity) {
        super.onActivityDestroyed(activity);
        binding = null;
    }

    public static class FullInputFragment extends DialogFragment {
        private final TextInputEditText viewPostField;

        public FullInputFragment(TextInputEditText viewPostField) {
            this.viewPostField = viewPostField;
        }

        @Override
        public void onStart() {
            super.onStart();
            if (getDialog() != null && getDialog().getWindow() != null) {
                getDialog().getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            }
        }

        @NonNull
        @Override
        public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
            var input = new TextInputEditText(requireContext());
            input.setLayoutParams(new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
            input.addTextChangedListener(new TextWatcher() {
                @Override
                public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                }

                @Override
                public void onTextChanged(CharSequence s, int start, int before, int count) {
                    viewPostField.setText(s);
                }

                @Override
                public void afterTextChanged(Editable s) {
                }
            });
            return input;
        }
    }
}
