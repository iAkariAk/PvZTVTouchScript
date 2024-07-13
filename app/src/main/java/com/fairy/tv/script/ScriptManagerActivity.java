package com.fairy.tv.script;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.activity.EdgeToEdge;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.button.MaterialButton;
import com.google.android.material.snackbar.Snackbar;
import com.google.android.material.textview.MaterialTextView;
import com.trans.pvztv.R;
import com.trans.pvztv.databinding.ScriptManagerBinding;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.zip.ZipInputStream;

public class ScriptManagerActivity extends AppCompatActivity {
    private static final String TAG = "ScriptManagerActivity";
    private ScriptManagerBinding binding;
    private final ScriptAdapter adapter = new ScriptAdapter();
    private final ActivityResultLauncher<String> importLauncher = registerForActivityResult(
            new ActivityResultContracts.GetContent(), uri -> {
                if (uri != null) {
                    try (var zis = new ZipInputStream(getContentResolver().openInputStream(uri))) {
                        var manifest = adapter.install(zis);
                        showSnackbar("Imported script: " + manifest.name());
                    } catch (IOException e) {
                        showSnackbar("Failed to import script: " + e.getMessage());
                        Log.e(TAG, "Failed to import script", e);
                    }
                }
            });

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        binding = ScriptManagerBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.script_manager), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        binding.fabImport.setOnClickListener(v -> importLauncher.launch("application/zip"));

        binding.scriptEntries.setLayoutManager(new LinearLayoutManager(this));
        binding.scriptEntries.setAdapter(adapter);

        adapter.refresh();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        binding = null;
    }

    private void showSnackbar(String message) {
        runOnUiThread(() -> Snackbar.make(binding.getRoot(), message, Snackbar.LENGTH_LONG).show());
    }

    private static class ScriptAdapter extends RecyclerView.Adapter<ScriptAdapter.MyHolder> {
        private List<ScriptManifest> scriptManifests = new ArrayList<>();

        @NonNull
        @Override
        public MyHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            var view = LayoutInflater.from(parent.getContext())
                    .inflate(R.layout.script_entry_item, parent, false);
            return new MyHolder(view);
        }

        @Override
        public void onBindViewHolder(@NonNull MyHolder holder, int position) {
            ScriptManifest manifest = scriptManifests.get(position);
            holder.title.setText(manifest.name());
            holder.version.setText(manifest.version());
            holder.description.setText(manifest.description());
            holder.uninstall.setOnClickListener(v -> uninstall(manifest.id()));
        }

        @Override
        public int getItemCount() {
            return scriptManifests.size();
        }

        public ScriptManifest install(ZipInputStream zipInputStream) throws IOException {
            ScriptManifest manifest = ScriptManager.install(zipInputStream);
            refresh();
            return manifest;
        }

        public void uninstall(String id) {
            ScriptManager.uninstall(id);
            refresh();
        }

        @SuppressLint("NotifyDataSetChanged")
        private void refresh() {
            scriptManifests = ScriptManager.list();
            notifyDataSetChanged();
        }

        private static class MyHolder extends RecyclerView.ViewHolder {
            final MaterialTextView title;
            final MaterialTextView version;
            final MaterialTextView description;
            final MaterialButton uninstall;

            public MyHolder(@NonNull View itemView) {
                super(itemView);
                this.title = itemView.findViewById(R.id.script_manager_item_title);
                this.version = itemView.findViewById(R.id.script_manager_item_version);
                this.description = itemView.findViewById(R.id.script_manager_item_description);
                this.uninstall = itemView.findViewById(R.id.script_manager_item_uninstall);
            }
        }
    }
}
