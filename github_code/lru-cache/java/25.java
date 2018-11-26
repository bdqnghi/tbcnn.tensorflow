package com.protel.network.util;

import android.util.LruCache;

import com.protel.network.ProNetwork;

/**
 * Created by mesutbeyaztas on 04/02/16.
 */
public class MemoryCacheHolder {

    private static final int DEFAULT_MEMORY_CACHE_SIZE = 1024;
    private static MemoryCacheHolder memoryCacheHolder;
    private LruCache cache;

    private MemoryCacheHolder() {
        Integer cacheSize = ProNetwork.getSingleton().getMemoryCacheSize();
        if (cacheSize == null) {
            cacheSize = DEFAULT_MEMORY_CACHE_SIZE;
        }
        cache = new LruCache<String, LruResponse>(cacheSize);
    }

    private static MemoryCacheHolder getInstance() {
        if (memoryCacheHolder == null) {
            memoryCacheHolder = new MemoryCacheHolder();
        }
        return memoryCacheHolder;
    }

    public static void putResponse(String key, Object response, Long resultMillis) {
        LruCache cache = MemoryCacheHolder.getInstance().cache;
        LruResponse lruResponse = new LruResponse(response, resultMillis);

        cache.put(key, lruResponse);
    }

    public static Object getResponse(String key) {
        LruCache cache = MemoryCacheHolder.getInstance().cache;
        LruResponse lruResponse = ((LruResponse) cache.get(key));

        if (lruResponse == null) {
            return null;
        }

        return lruResponse.response;
    }

    public static Long getResultMillis(String key) {
        LruCache cache = MemoryCacheHolder.getInstance().cache;
        LruResponse lruResponse = ((LruResponse) cache.get(key));

        if (lruResponse == null) {
            return null;
        }

        return lruResponse.resultMillis;
    }

    public static class LruResponse {
        public Object response;
        public Long resultMillis;

        public LruResponse(Object response, Long resultMillis) {
            this.response = response;
            this.resultMillis = resultMillis;
        }
    }

}
