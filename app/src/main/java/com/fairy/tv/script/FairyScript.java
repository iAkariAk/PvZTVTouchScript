package com.fairy.tv.script;

import com.fairy.tv.FairyNative;

import java.util.function.Consumer;

/**
 * @noinspection JavaJniMissingFunction
 */
public class FairyScript {
    public static void submitExecutionTask(String id, String code) {
        FairyNative.sendPacket("ScriptExecuteTask", id + ":" + code);
    }

    public static native void submitFileExecutionTask(String id, String path);
}
