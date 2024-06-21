package com.fairy.tv.script;

import android.os.Bundle;
import android.util.Log;

import androidx.activity.EdgeToEdge;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.snackbar.Snackbar;
import com.trans.pvztv.R;
import com.trans.pvztv.databinding.ScriptManagerBinding;

import java.util.zip.ZipInputStream;

public class ScriptManagerActivity extends AppCompatActivity {
    private static final String TAG = "ScriptManagerActivity";
    private static ScriptManagerBinding binding;
    private ActivityResultLauncher<String> importLauncher =
            registerForActivityResult(new ActivityResultContracts.GetContent(), uri -> {
                try (var zis = new ZipInputStream(getContentResolver().openInputStream(uri))) {
                    var manifest = ScriptManager.install(zis);
                    Snackbar.make(binding.getRoot(), "Imported script: " + manifest.name(), Snackbar.LENGTH_LONG).show();
                } catch (Throwable e) {
                    Snackbar.make(binding.getRoot(), "Failed to import script: " + e.getMessage(), Snackbar.LENGTH_LONG).show();
                    Log.e(TAG, "Failed to import script", e);
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

        binding.fabImport.setOnClickListener(v -> {
            importLauncher.launch("application/zip");
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        binding = null;
    }
}