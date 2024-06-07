package com.fairy.tv;

public record Packet(String name, String content) {
    public Packet {
        if (name.contains(":")) throw new IllegalArgumentException("Name can't contains ':'!");
    }


    public static Packet receiveFromNative(String name) {
        var rawPacket = FairyNative.receivePacket(name);
        if (rawPacket == null) {
            return null;
        }
        var index = rawPacket.indexOf(":");
        if (index == -1) return null;
        return new Packet(rawPacket.substring(0, index), rawPacket.substring(index + 1));
    }
}
