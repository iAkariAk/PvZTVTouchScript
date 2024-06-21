package com.fairy.tv;

import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import java.util.LinkedList;
import java.util.Objects;
import java.util.function.Consumer;

public class PacketDispatcher {
    private static final LinkedList<ConsumeTarget> consumerTargets = new LinkedList<>();

    static {
        var looper = Looper.getMainLooper();
        var handler = new Handler(looper);
        handler.post(new Runnable() {
            @Override
            public void run() {
                for (ConsumeTarget target : consumerTargets) {
                    var packet = Packet.receiveFromNative(target.packetName);
                    if (packet != null) {
                        Log.d("Fairy", packet.toString());
                        target.consumer.accept(packet);
                    }
                }
                handler.postDelayed(this, 10);
            }
        });
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

    private record ConsumeTarget(String packetName, Consumer<Packet> consumer) {
    }
}
