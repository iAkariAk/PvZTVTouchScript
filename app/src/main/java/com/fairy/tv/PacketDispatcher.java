package com.fairy.tv;

import android.util.Log;

import java.util.LinkedList;
import java.util.Objects;
import java.util.function.Consumer;

public class PacketDispatcher {
    private static final LinkedList<ConsumeTarget> consumerTargets = new LinkedList<>();

    static {
        new Thread(() -> {
            while (true) {
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                synchronized (consumerTargets) {
                    for (ConsumeTarget target : consumerTargets) {
                        var packet = Packet.receiveFromNative(target.packetName);
                        if (packet != null) {
                            Log.d("Fairy", packet.toString());
                            target.consumer.accept(packet);
                        }
                    }
                }
            }
        }).start();
    }

    public static void registerConsumer(String packetName, Consumer<Packet> consumer) {
        synchronized (consumerTargets) {
            consumerTargets.add(new ConsumeTarget(packetName, consumer));
        }
    }

    public static void unregisterConsumer(String packetName, Consumer<Packet> consumer) {
        synchronized (consumerTargets) {
            consumerTargets.removeIf(target -> Objects.equals(target.packetName, packetName) && target.consumer == consumer);
        }
    }

    private record ConsumeTarget(String packetName, Consumer<Packet> consumer) { }
}
