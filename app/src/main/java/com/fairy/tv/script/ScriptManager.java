package com.fairy.tv.script;

import android.annotation.SuppressLint;
import android.util.Log;

import com.fairy.tv.MyApplication;
import com.fairy.tv.util.Jsons;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

import kotlin.io.FilesKt;
import kotlin.io.OnErrorAction;

public class ScriptManager {
    private static final String TAG = "ScriptManager";
    @SuppressLint("NewApi")
    private static final Path ROOT_DIR = Objects.requireNonNull(MyApplication.INSTANCE.getExternalFilesDir("scripts")).toPath();

    @SuppressLint("NewApi")
    public static List<ScriptManifest> list() {
        try {
            try (var list = Files.list(ROOT_DIR)) {
                return list.filter(path -> Files.exists(path.resolve("manifest.json")))
                        .map(path -> {
                            try {
                                return Jsons.fromJson(ScriptManifest.class, new String(Files.readAllBytes(path.resolve("manifest.json"))));
                            } catch (IOException e) {
                                throw new RuntimeException(e);
                            }
                        })
                        .collect(Collectors.toList());
            }

        } catch (IOException e) {
            return new ArrayList<>();
        }
    }

    @SuppressLint("NewApi")
    public static void loadAll() {
        list().stream()
                .map(manifest -> ROOT_DIR.resolve(manifest.id()))
                .forEach(path -> FairyScript.submitFileExecutionTask(Long.toString(System.nanoTime()), path.toAbsolutePath().toString()));
    }

    @SuppressLint("NewApi")
    public static ScriptManifest install(ZipInputStream inputStream) throws IOException {
        var tempDir = Files.createTempDirectory("ScriptInstall");
        ZipEntry entry;
        while ((entry = inputStream.getNextEntry()) != null) {
            var copyTarget = tempDir.resolve(entry.getName());
            if (entry.isDirectory()) {
                Files.createDirectories(copyTarget);
                continue;
            }

            Files.copy(inputStream, copyTarget);
            Log.d(TAG, "Copied: " + entry.getName());
        }
        if (!Files.exists(tempDir.resolve("manifest.json")))
            throw new IllegalStateException("Missing manifest.json");
        ScriptManifest manifest = Jsons.fromJson(ScriptManifest.class, new String(Files.readAllBytes(tempDir.resolve("manifest.json"))));
        FilesKt.copyRecursively(tempDir.toFile(), ROOT_DIR.resolve(manifest.id()).toFile(), true, (file, e) -> OnErrorAction.SKIP);
        return manifest;
    }

    @SuppressLint("NewApi")
    public static void uninstall(String id) {
        FilesKt.deleteRecursively(ROOT_DIR.resolve(id).toFile());
    }
}
