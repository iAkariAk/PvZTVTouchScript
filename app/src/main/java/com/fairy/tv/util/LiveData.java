package com.fairy.tv.util;

import java.util.LinkedList;
import java.util.function.Consumer;

public class LiveData<T> {
    private final LinkedList<Consumer<T>> observers = new LinkedList<>();

    public void addObserver(Consumer<T> observer) {
        observers.add(observer);
    }
    public synchronized void removeObserver(Consumer<T> observer) {
        observers.remove(observer);
    }

    public void send(T data) {
        observers.forEach(observer -> observer.accept(data));
    }
}
