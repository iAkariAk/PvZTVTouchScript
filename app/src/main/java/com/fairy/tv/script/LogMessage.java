package com.fairy.tv.script;

public record LogMessage(String tag, Level level, String message) {
    public enum Level {
        Debug, Info, Error, Warning
    }
}
