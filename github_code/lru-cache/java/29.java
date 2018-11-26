package com.longway.framework.cache;

import com.longway.framework.cache.diskcache.LruDiskCache;
import com.longway.framework.cache.memorycache.CustomBeanLruMemoryCache;
import com.longway.framework.cache.memorycache.CustomBitmapLruMemoryCache;
import com.longway.framework.cache.memorycache.CustomStringLruMemoryCache;

import java.io.File;
import java.io.IOException;

/**
 * Email:longway1991117@sina.com
 * 缓存管理 磁盘，内存 基本管理
 */
public class CacheManager {

    private volatile LruDiskCache sLruDiskCache;
    private volatile CustomBitmapLruMemoryCache sLruMemoryBitmapCache;
    private volatile CustomBeanLruMemoryCache sCustomBeanLruMemoryCache;
    private volatile CustomStringLruMemoryCache stringLruMemoryCache;

    private CacheManager() {

    }

    private static final class Inner {
        private static CacheManager sCacheManager = new CacheManager();
    }

    public static CacheManager getInstance() {
        return Inner.sCacheManager;
    }

    public LruDiskCache getDiskCache(File dir, int version, int maxSize) throws IOException {
        if (sLruDiskCache == null) {
            synchronized (LruDiskCache.class) {
                if (sLruDiskCache == null) {
                    sLruDiskCache = LruDiskCache.open(dir, version, 1, maxSize);
                }
            }
        }
        return sLruDiskCache;
    }

    public CustomBitmapLruMemoryCache getMemCache(int maxSize) {
        if (sLruMemoryBitmapCache == null) {
            synchronized (CustomBitmapLruMemoryCache.class) {
                if (sLruMemoryBitmapCache == null) {
                    sLruMemoryBitmapCache = new CustomBitmapLruMemoryCache(maxSize);
                }
            }
        }
        return sLruMemoryBitmapCache;
    }

    public CustomBeanLruMemoryCache getsCustomBeanLruMemoryCache(int maxSize) {
        if (sCustomBeanLruMemoryCache == null) {
            synchronized (CustomBeanLruMemoryCache.class) {
                if (sCustomBeanLruMemoryCache == null) {
                    sCustomBeanLruMemoryCache = new CustomBeanLruMemoryCache(maxSize);
                }
            }
        }
        return sCustomBeanLruMemoryCache;
    }

    public CustomStringLruMemoryCache getsCustomStringLruMemoryCache(int maxSize) {
        if (stringLruMemoryCache == null) {
            synchronized (CustomStringLruMemoryCache.class) {
                if (stringLruMemoryCache == null) {
                    stringLruMemoryCache = new CustomStringLruMemoryCache(maxSize);
                }
            }
        }
        return stringLruMemoryCache;
    }
}

