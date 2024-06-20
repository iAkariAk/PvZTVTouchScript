package com.fairy.tv.script;

import android.util.Log;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;

import com.fairy.tv.FairyNative;
import com.fairy.tv.PacketDispatcher;

import java.util.Arrays;

/**
 */
public class FairyScript {
    private static final MutableLiveData<LogMessage> _logMessageLiveData = new MutableLiveData<>();
    public static final LiveData<LogMessage> logMessageLiveData = _logMessageLiveData;
    private static final MutableLiveData<ExcuteResult> _executeResultLiveData = new MutableLiveData<>();
    public static final LiveData<ExcuteResult> executeResultLiveData = _executeResultLiveData;
    public static void submitExecutionTask(String id, String code) {
        FairyNative.sendPacket("ScriptExecuteTask", id + ":" + code);
    }

    public static void submitFileExecutionTask(String id, String path) {
        FairyNative.sendPacket("ScriptExecuteFileTask", id + ":" + path);
    }

    static {
        PacketDispatcher.registerConsumer("LogToJava", packet -> {
            var parts = packet.spiltContent();
            if (parts.length >= 3) {

                var tagStr = parts[0];
                var levelStr = parts[1];
                var messageStr = packet.spiltAndDropContent(2);
                var level = LogMessage.Level.Info;
                try {
                    level = LogMessage.Level.valueOf(levelStr);
                } catch (Throwable throwable) {
                    Log.e("Fairy", Arrays.toString(throwable.getStackTrace()));

                }
                var log = new LogMessage(tagStr, level, messageStr);
                _logMessageLiveData.postValue(log);
            }
        });
        PacketDispatcher.registerConsumer("ResultForScriptExecute", packet -> {
            var parts = packet.spiltContent();
            if (parts.length >= 2) {

                var source = parts[0];
                var content = packet.spiltAndDropContent(1);
                var result = new ExcuteResult(source, content);
                _executeResultLiveData.postValue(result);
            }
        });
    }
}
