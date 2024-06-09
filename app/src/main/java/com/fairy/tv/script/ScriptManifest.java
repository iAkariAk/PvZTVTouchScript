package com.fairy.tv.script;

public record ScriptManifest(
        String id,
        String name,
        String version,
        String description,
        int minSdk
) {}
