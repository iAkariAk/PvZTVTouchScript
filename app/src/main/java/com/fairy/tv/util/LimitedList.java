package com.fairy.tv.util;

import java.util.LinkedList;

public class LimitedList<E> extends LinkedList<E> {
    private final int limitedSize;

    public LimitedList(int limitedSize) {
        this.limitedSize = limitedSize;
    }

    @Override
    public boolean add(E e) {
        synchronized (this) {
            if (size() < limitedSize) {
                return super.add(e);
            } else {
                return false;
            }
        }
    }
}
