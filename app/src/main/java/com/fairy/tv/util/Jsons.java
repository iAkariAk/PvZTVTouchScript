package com.fairy.tv.util;

import com.squareup.moshi.Moshi;
import com.squareup.moshi.Types;

import java.io.IOException;

public class Jsons {
    private static final Moshi MOSHI = new Moshi.Builder().build();

    public static <T> String toJson(T object) {
        return MOSHI.adapter(Types.newParameterizedType(object.getClass())).toJson(object);
    }

    public static <T> T fromJson(Class<T> type, String json) throws IOException {
        return MOSHI.adapter(type).fromJson(json);
    }
}
