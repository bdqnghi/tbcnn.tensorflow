package ch.unine.vauchers.erasuretester.utils;

import it.unimi.dsi.fastutil.ints.IntLinkedOpenHashSet;

/**
 * An LRU-cache set
 */
public class IntCacheSet extends IntLinkedOpenHashSet {
    private final int cacheSize;

    public IntCacheSet(int cacheSize) {
        super(cacheSize);
        this.cacheSize = cacheSize;
    }

    @Override
    public boolean add(int key) {
        if (addAndMoveToFirst(key)) { // The key was not present, aka the list grew
            if (size > cacheSize) {
                removeLastInt();
            }
            return true;
        }
        return false;
    }
}
