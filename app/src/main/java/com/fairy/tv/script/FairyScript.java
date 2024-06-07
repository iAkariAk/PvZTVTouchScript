package com.fairy.tv.script;

import java.util.function.Consumer;

public class FairyScript {
    public static native void execute(String code, Consumer<String> onResult);

    public static native void executeFile(String path, Consumer<String> onResult);
}
