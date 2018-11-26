package com.MCWorld.framework.base.cache;

import android.annotation.TargetApi;
import android.os.StatFs;
import android.os.SystemClock;
import android.support.v4.util.LruCache;
import com.MCWorld.framework.AppConfig;
import com.MCWorld.framework.base.log.HLog;
import com.MCWorld.framework.base.utils.DiskLruCache;
import com.MCWorld.framework.base.utils.DiskLruCache.Editor;
import com.MCWorld.framework.base.utils.DiskLruCache.Snapshot;
import com.MCWorld.framework.base.utils.UtilsFunction;
import com.MCWorld.framework.base.utils.UtilsVersion;
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class StringLruCache {
    private static final int DEFAULT_DISK_CACHE_SIZE = 5242880;
    private static final int DEFAULT_MEM_CACHE_SIZE = 2097152;
    private static final int DISK_CACHE_INDEX = 0;
    private static final String TAG = "StringLruCache";
    private String mCachePath;
    private final Object mDiskCacheLock = new Object();
    private volatile boolean mDiskCacheStarting = true;
    private DiskLruCache mDiskLruCache;
    private LruCache<String, String> mLruCache;
    private float mScale;
    private int memCacheSize = 2097152;

    public StringLruCache(float scale, String cachePath) {
        init(scale, cachePath);
        initDiskCache();
    }

    private void init(float scale, String cachePath) {
        this.mCachePath = cachePath;
        this.mScale = scale;
        this.memCacheSize = Math.min(Math.round((((float) Runtime.getRuntime().freeMemory()) * scale) / 1024.0f), 2097152);
        this.mLruCache = new LruCache<String, String>(this.memCacheSize) {
            @TargetApi(12)
            protected int sizeOf(String key, String value) {
                return value == null ? 1 : value.getBytes().length;
            }

            protected void entryRemoved(boolean evicted, String key, String oldValue, String newValue) {
            }
        };
    }

    public String getMemoryLruCache(String data) {
        return (String) this.mLruCache.get(hashKeyForDisk(data));
    }

    public void unit() {
        flush();
    }

    private void initDiskCache() {
        new Thread("string-cache-" + SystemClock.elapsedRealtime()) {
            public void run() {
                synchronized (StringLruCache.this.mDiskCacheLock) {
                    if (StringLruCache.this.mDiskLruCache == null || StringLruCache.this.mDiskLruCache.isClosed()) {
                        File diskCacheDir = new File(StringLruCache.this.mCachePath);
                        if (diskCacheDir != null) {
                            if (!diskCacheDir.exists()) {
                                diskCacheDir.mkdirs();
                            }
                            if (StringLruCache.getUsableSpace(diskCacheDir) > 5242880) {
                                try {
                                    StringLruCache.this.mDiskLruCache = DiskLruCache.open(diskCacheDir, UtilsVersion.getVersionCode(AppConfig.getInstance().getAppContext()), 1, 5242880);
                                } catch (IOException e) {
                                    HLog.error(StringLruCache.TAG, "initDiskCache - " + e, new Object[0]);
                                }
                            }
                        }
                    }
                    StringLruCache.this.mDiskCacheStarting = false;
                    StringLruCache.this.mDiskCacheLock.notifyAll();
                    HLog.info(StringLruCache.TAG, "string disk cache init completely", new Object[0]);
                }
            }
        }.start();
    }

    public String getEntry(String data) {
        String key = hashKeyForDisk(data);
        String value = (String) this.mLruCache.get(key);
        if (value != null) {
            return value;
        }
        if (this.mDiskCacheStarting) {
            return null;
        }
        return getEntryInternal(key);
    }

    public void addEntry(String data, String value) {
        if (!UtilsFunction.empty(data) && value != null) {
            String key = hashKeyForDisk(data);
            this.mLruCache.put(key, value);
            if (this.mDiskCacheStarting) {
                HLog.warn(TAG, "add entry when disk cache is starting initialization", new Object[0]);
                return;
            }
            try {
                this.mDiskLruCache.remove(key);
                flush();
                addEntryInternal(data, value);
                flush();
            } catch (IOException e) {
                HLog.error(TAG, "remove key %s when putting %s", new Object[]{data, value});
            }
        }
    }

    @TargetApi(9)
    public static long getUsableSpace(File path) {
        if (UtilsVersion.hasGingerbread()) {
            return path.getUsableSpace();
        }
        StatFs stats = new StatFs(path.getPath());
        return ((long) stats.getBlockSize()) * ((long) stats.getAvailableBlocks());
    }

    private void addEntryInternal(String data, String value) {
        if (data != null && value != null) {
            synchronized (this.mDiskCacheLock) {
                if (this.mDiskLruCache != null) {
                    String key = hashKeyForDisk(data);
                    OutputStream out = null;
                    try {
                        Snapshot snapshot = this.mDiskLruCache.get(key);
                        if (snapshot == null) {
                            Editor editor = this.mDiskLruCache.edit(key);
                            if (editor != null) {
                                out = editor.newOutputStream(0);
                                out.write(value.getBytes());
                                editor.commit();
                                out.close();
                            }
                        } else {
                            snapshot.getInputStream(0).close();
                        }
                        if (out != null) {
                            try {
                                out.close();
                            } catch (IOException e) {
                            }
                        }
                    } catch (IOException e2) {
                        HLog.error(TAG, "addFileListToDiskCache - " + e2, new Object[0]);
                        if (out != null) {
                            try {
                                out.close();
                            } catch (IOException e3) {
                            }
                        }
                    } catch (Exception e4) {
                        HLog.error(TAG, "addFileListToDiskCache - " + e4, new Object[0]);
                        if (out != null) {
                            try {
                                out.close();
                            } catch (IOException e5) {
                            }
                        }
                    } catch (Throwable th) {
                        if (out != null) {
                            try {
                                out.close();
                            } catch (IOException e6) {
                            }
                        }
                    }
                }
            }
            return;
        }
        return;
    }

    public static String hashKeyForDisk(String key) {
        try {
            MessageDigest mDigest = MessageDigest.getInstance("MD5");
            mDigest.update(key.getBytes());
            return bytesToHexString(mDigest.digest());
        } catch (NoSuchAlgorithmException e) {
            return String.valueOf(key.hashCode());
        }
    }

    private static String bytesToHexString(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            String hex = Integer.toHexString(b & 255);
            if (hex.length() == 1) {
                sb.append('0');
            }
            sb.append(hex);
        }
        return sb.toString();
    }

    private String getEntryInternal(String key) {
        Exception e;
        Throwable th;
        String value = null;
        synchronized (this.mDiskCacheLock) {
            while (this.mDiskCacheStarting) {
                try {
                    this.mDiskCacheLock.wait();
                } catch (InterruptedException e2) {
                }
            }
            if (this.mDiskLruCache != null) {
                InputStream inputStream = null;
                BufferedInputStream bis = null;
                try {
                    Snapshot snapshot = this.mDiskLruCache.get(key);
                    if (snapshot != null) {
                        inputStream = snapshot.getInputStream(0);
                        if (inputStream != null) {
                            BufferedInputStream bis2 = new BufferedInputStream(new FileInputStream(((FileInputStream) inputStream).getFD()));
                            try {
                                byte[] bytes = new byte[bis2.available()];
                                bis2.read(bytes);
                                bis = bis2;
                                value = new String(bytes, "UTF-8");
                            } catch (Exception e3) {
                                e = e3;
                                bis = bis2;
                                try {
                                    HLog.error(TAG, "getHpkFileListFromDiskCache - " + e, new Object[0]);
                                    if (bis != null) {
                                        try {
                                            bis.close();
                                        } catch (IOException e4) {
                                        }
                                    }
                                    if (inputStream != null) {
                                        inputStream.close();
                                    }
                                    return value;
                                } catch (Throwable th2) {
                                    th = th2;
                                    if (bis != null) {
                                        try {
                                            bis.close();
                                        } catch (IOException e5) {
                                            throw th;
                                        }
                                    }
                                    if (inputStream != null) {
                                        inputStream.close();
                                    }
                                    throw th;
                                }
                            } catch (Throwable th3) {
                                th = th3;
                                bis = bis2;
                                if (bis != null) {
                                    bis.close();
                                }
                                if (inputStream != null) {
                                    inputStream.close();
                                }
                                throw th;
                            }
                        }
                    }
                    if (bis != null) {
                        try {
                            bis.close();
                        } catch (IOException e6) {
                        }
                    }
                    if (inputStream != null) {
                        inputStream.close();
                    }
                } catch (Exception e7) {
                    e = e7;
                    HLog.error(TAG, "getHpkFileListFromDiskCache - " + e, new Object[0]);
                    if (bis != null) {
                        bis.close();
                    }
                    if (inputStream != null) {
                        inputStream.close();
                    }
                    return value;
                }
            }
        }
        return value;
    }

    public void clearCache() {
        synchronized (this.mDiskCacheLock) {
            this.mDiskCacheStarting = true;
            if (!(this.mDiskLruCache == null || this.mDiskLruCache.isClosed())) {
                try {
                    this.mDiskLruCache.delete();
                } catch (IOException e) {
                    HLog.error(TAG, "clearCache - " + e, new Object[0]);
                }
                this.mDiskLruCache = null;
                initDiskCache();
            }
        }
    }

    public void flush() {
        synchronized (this.mDiskCacheLock) {
            if (this.mDiskLruCache != null) {
                try {
                    this.mDiskLruCache.flush();
                } catch (IOException e) {
                    HLog.error(TAG, "flush - " + e, new Object[0]);
                }
            }
        }
    }
}
