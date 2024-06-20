package com.fairy.tv;

import java.util.Arrays;
import java.util.Objects;
import java.util.stream.Collectors;

public record Packet(String name, String rawContent) {

    public Packet {
        if (name.contains(":")) {
            throw new IllegalArgumentException("Name can't contain ':'!");
        }
        Objects.requireNonNull(rawContent, "Raw content cannot be null");
    }

    public String[] spiltContent() {
        return rawContent.split(":");
    }

    public String spiltAndDropContent(int index) {
        var spiltContent = spiltContent();
        if (index < 0 || index > spiltContent.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }

        return Arrays.stream(spiltContent, index, spiltContent.length)
                .collect(Collectors.joining());
    }

    public static Packet receiveFromNative(String name) {
        String rawPacket = FairyNative.receivePacket(name);
        if (rawPacket == null) {
            return null;
        }
        int index = rawPacket.indexOf(":");
        if (index == -1) {
            return null;
        }
        String rawContent = rawPacket.substring(index + 1);
        return new Packet(rawPacket.substring(0, index), rawContent);
    }
}
