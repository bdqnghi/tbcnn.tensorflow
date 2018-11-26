package com.qylk.base.cache;

import android.text.TextUtils;
import com.jakewharton.disklrucache.DiskLruCache;
import org.apache.commons.io.IOUtils;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public final class MpDiskLruCache {

    private static final int DISK_CACHE_INDEX = 0;
    private static MpDiskLruCache sInstance;
    private DiskLruCache diskLruCache;
    private File cacheFolder;
    private long maxCacheSize = 20 * 1024 * 1024; // 20MB

    private MpDiskLruCache() {
    }

    public static MpDiskLruCache getInstance() {
        if (sInstance == null) {
            sInstance = new MpDiskLruCache();
        }
        return sInstance;
    }

    public void init(File dir) {
        this.cacheFolder = dir;
    }

    public void init(File dir, long maxCacheSize) {
        this.cacheFolder = dir;
        this.maxCacheSize = maxCacheSize;
    }

    public File getFile(String key) {
        File file = null;
        if (getDiskLruCache() != null) {
            key = hashKeyForDisk(key);
            try {
                file = new File(diskLruCache.getDirectory(), key + "." + DISK_CACHE_INDEX);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return file;
    }

    public InputStream getInputStream(String key) {
        InputStream is = null;
        if (getDiskLruCache() != null) {
            key = hashKeyForDisk(key);
            try {
                DiskLruCache.Snapshot snapshot = diskLruCache.get(key);
                if (snapshot != null && snapshot.getLength(DISK_CACHE_INDEX) > 0) {
                    is = snapshot.getInputStream(DISK_CACHE_INDEX);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return is;
    }

    public boolean put(String key, byte[] bytes) {
        boolean success = false;
        if (getDiskLruCache() != null) {
            key = hashKeyForDisk(key);
            OutputStream out = null;
            try {
                DiskLruCache.Snapshot snapshot = diskLruCache.get(key);
                if (snapshot == null) {
                    final DiskLruCache.Editor editor = diskLruCache.edit(key);
                    if (editor != null) {
                        out = editor.newOutputStream(DISK_CACHE_INDEX);
                        out.write(bytes);
                        editor.commit();
                        success = true;
                    }
                } else {
                    snapshot.getInputStream(DISK_CACHE_INDEX).close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                IOUtils.closeQuietly(out);
            }
        }
        return success;
    }

    public boolean put(String key, InputStream is) {
        boolean success = false;
        if (getDiskLruCache() != null) {
            key = hashKeyForDisk(key);
            OutputStream out = null;
            try {
                DiskLruCache.Snapshot snapshot = diskLruCache.get(key);
                if (snapshot == null) {
                    final DiskLruCache.Editor editor = diskLruCache.edit(key);
                    if (editor != null) {
                        out = editor.newOutputStream(DISK_CACHE_INDEX);
                        IOUtils.copy(is, out);
                        editor.commit();
                        success = true;
                    }
                } else {
                    snapshot.getInputStream(DISK_CACHE_INDEX).close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                IOUtils.closeQuietly(out);
            }
        }
        return success;
    }

    private static String hashKeyForDisk(String key) {
        String cacheKey = com.qylk.base.utils.HashUtils.MD5(key);
        return TextUtils.isEmpty(cacheKey) ? String.valueOf(key.hashCode()) : cacheKey;
    }

    public DiskLruCache getDiskLruCache() {
        if (diskLruCache == null) {
            synchronized (this) {
                if (diskLruCache == null && cacheFolder != null) {
                    try {
                        diskLruCache = DiskLruCache.open(cacheFolder, 1, 1, maxCacheSize);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        return diskLruCache;
    }
}
