package com.iqoption.util.b;

import android.support.annotation.Nullable;
import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NavigableMap;
import java.util.TreeMap;

/* compiled from: TreeMapSet */
public class b<T> {
    private final NavigableMap<T, T> dwW;

    public b() {
        this.dwW = new TreeMap();
    }

    public b(Comparator<? super T> comparator) {
        this.dwW = new TreeMap(comparator);
    }

    public T add(T t) {
        return this.dwW.put(t, t);
    }

    public T remove(T t) {
        return this.dwW.remove(t);
    }

    public T get(T t) {
        return this.dwW.get(t);
    }

    @Nullable
    public T first() {
        return this.dwW.firstEntry().getValue();
    }

    public void clear() {
        this.dwW.clear();
    }

    public void addAll(Collection<? extends T> collection) {
        for (Object add : collection) {
            add(add);
        }
    }

    public int size() {
        return this.dwW.size();
    }

    public boolean isEmpty() {
        return this.dwW.isEmpty();
    }

    public Collection<T> aGI() {
        return this.dwW.values();
    }

    public Iterator<Entry<T, T>> iterator() {
        return this.dwW.entrySet().iterator();
    }
}
