/*
 * Decompiled with CFR 0_115.
 */
package com.growingio.e.a.a.a;

import java.nio.charset.Charset;
import java.util.Collections;
import java.util.Comparator;
import java.util.SortedMap;
import java.util.TreeMap;

public class b {
    public static final Charset a = Charset.forName("ISO-8859-1");
    public static final Charset b = Charset.forName("US-ASCII");
    public static final Charset c = Charset.forName("UTF-16");
    public static final Charset d = Charset.forName("UTF-16BE");
    public static final Charset e = Charset.forName("UTF-16LE");
    public static final Charset f = Charset.forName("UTF-8");

    public static SortedMap<String, Charset> a() {
        TreeMap<String, Charset> treeMap = new TreeMap<String, Charset>(String.CASE_INSENSITIVE_ORDER);
        treeMap.put(a.name(), a);
        treeMap.put(b.name(), b);
        treeMap.put(c.name(), c);
        treeMap.put(d.name(), d);
        treeMap.put(e.name(), e);
        treeMap.put(f.name(), f);
        return Collections.unmodifiableSortedMap(treeMap);
    }

    public static Charset a(Charset charset) {
        return charset == null ? Charset.defaultCharset() : charset;
    }

    public static Charset a(String string) {
        return string == null ? Charset.defaultCharset() : Charset.forName(string);
    }
}

