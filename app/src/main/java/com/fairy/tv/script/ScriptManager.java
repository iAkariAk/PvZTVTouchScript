package com.fairy.tv.script;

import android.annotation.SuppressLint;

import com.fairy.tv.MyApplication;
import com.fairy.tv.util.Jsons;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class ScriptManager {
    @SuppressLint("NewApi")
    private static final Path ROOT_DIR = MyApplication.INSTANCE.getExternalFilesDir("scripts").toPath();

    @SuppressLint("NewApi")
    public static List<ScriptManifest> list() {
        try {
            return Files.list(ROOT_DIR)
                    .filter(path -> Files.exists(path.resolve("manifest.json")))
                    .map(path -> {
                        try {
                            return Jsons.fromJson(ScriptManifest.class, new String(Files.readAllBytes(path)));
                        } catch (IOException e) {
                            throw new RuntimeException(e);
                        }
                    })
                    .collect(Collectors.toList());
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
}
