package com.fairy.tv.script;

import android.util.Log;

import com.fairy.tv.FairyNative;
import com.fairy.tv.PacketDispatcher;
import com.fairy.tv.util.LiveData;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.stream.Collectors;

/**
 * @noinspection JavaJniMissingFunction
 */
public class FairyScript {
    public static final LiveData<LogMessage> logMessageLiveData = new LiveData<>();

    public static void submitExecutionTask(String id, String code) {
        FairyNative.sendPacket("ScriptExecuteTask", id + ":" + code);
    }

    public static void submitFileExecutionTask(String id, String path) {
        FairyNative.sendPacket("ScriptExecuteFileTask", id + ":" + path);
    }

    static {
        PacketDispatcher.registerConsumer("LogToJava", packet -> {
            var parts = packet.content().split(":");
            if (parts.length >= 3) {

                var tagStr = parts[0];
                var levelStr = parts[1];
                var messageStr = Arrays.stream(parts, 2, parts.length)
                        .collect(Collectors.joining());
                var level = LogMessage.Level.Info;
                try {
                    level = LogMessage.Level.valueOf(levelStr);
                } catch (Throwable throwable) {
                    Log.e("Fairy", Arrays.toString(throwable.getStackTrace()));

                }
                var log = new LogMessage(tagStr, level, messageStr);
                logMessageLiveData.send(log);
            }
        });
    }
}
