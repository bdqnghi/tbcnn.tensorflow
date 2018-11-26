
package com.nreader.cache;

import android.graphics.Bitmap;
import android.support.v4.util.LruCache;

import com.nreader.utility.LogUtil;

/**
 * The class that's used to do bitmap cache, the cache strategy is "Lru-Cache"
 * or latest recently used algorithm.
 */
public class LruBitmapCache extends LruCache<String, Bitmap> {
    public static final String TAG = "LruBitmapCache";

    public LruBitmapCache(int maxSize) {
        super(maxSize);
        LogUtil.v(TAG + "The image cache maximum size is " + maxSize);
    }

    @Override
    protected int sizeOf(String key, Bitmap value) {
        return value.getRowBytes() * value.getHeight();
    }
}
