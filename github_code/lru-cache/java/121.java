package com.kappa_labs.ohunter.client.utilities;


import android.support.v4.util.LruCache;
import android.util.Log;

import com.kappa_labs.ohunter.client.activities.DummyApplication;
import com.kappa_labs.ohunter.lib.entities.Photo;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Class to support storing memory intensive photos of all targets.
 */
public class PhotosManager {

    private static final String TAG = "PhotosManager";

    private static LruCache<TargetPhotoKey, Photo> mPhotosCache;


    /**
     * Initializes the LRU-cache for photos.
     */
    private static void initMemoryCache() {
        /* Clear the cache */
        if (mPhotosCache != null) {
            mPhotosCache.evictAll();
        }

        final int maxMemory = (int) (Runtime.getRuntime().maxMemory() / 1024);

        /* Use specified part of the available memory just for this memory cache */
        final int cacheSize = maxMemory / 8;

        Log.d(TAG, "Available max memory = " + maxMemory + "; cacheSize = " + cacheSize);

        mPhotosCache = new LruCache<TargetPhotoKey, Photo>(cacheSize) {
            @Override
            protected int sizeOf(TargetPhotoKey key, Photo photo) {
                return photo.getWidth() * photo.getHeight() * 4 / 1024;
            }
        };
    }

    /**
     * Adds given photos to the cache.
     *
     * @param placeID Place ID of the target whose photos should be stored.
     * @param photos  The photos to be stored into cache.
     */
    public static void addPhotosOfTarget(String placeID, Photo[] photos) {
        for (int i = 0; i < photos.length; i++) {
            addPhotoOfTarget(placeID, photos[i], i);
        }
    }

    /**
     * Adds given photos to the cache.
     *
     * @param placeID Place ID of the target whose photos should be stored.
     * @param photos  The photos to be stored into cache.
     */
    public static void addPhotosOfTarget(String placeID, List<Photo> photos) {
        for (int i = 0; i < photos.size(); i++) {
            addPhotoOfTarget(placeID, photos.get(i), i);
        }
    }

    /**
     * Adds given photo to the cache.
     *
     * @param placeID Place ID of the target whose photos should be stored.
     * @param photo   The photo to be stored into cache.
     * @param index   Unique index of the photo for given target.
     */
    public static void addPhotoOfTarget(String placeID, Photo photo, int index) {
        if (mPhotosCache != null) {
            mPhotosCache.remove(new TargetPhotoKey(placeID, index));
        }
        SharedDataManager.saveTargetPhoto(DummyApplication.getContext(), placeID, index, photo);
    }

    /**
     * Loads and gets all photos from the cache (internal or external).
     * This function can be slow when loading all the photos from external memory.
     *
     * @param placeID Place ID of the target whose photos should be returned.
     * @return All the photos from the cache (internal or external).
     */
    public static List<Photo> getPhotosOfTarget(String placeID) {
        List<Photo> photos = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            Photo photo = getPhotoOfTarget(placeID, i);
            if (photo != null) {
                photos.add(photo);
            }
        }
        return photos;
    }

    /**
     * Loads and gets one photo from the cache (internal or external).
     * This function can be slow when loading the photo from external memory.
     *
     * @param placeID Place ID of the target whose photo should be returned.
     * @param index   Unique index of the photo to return.
     * @return The photo from the cache (internal or external).
     */
    public static Photo getPhotoOfTarget(String placeID, int index) {
        if (mPhotosCache == null) {
            initMemoryCache();
        }
        TargetPhotoKey targetPhotoKey = new TargetPhotoKey(placeID, index);
        Photo photo = mPhotosCache.get(targetPhotoKey);
        if (photo == null) {
            photo = SharedDataManager.getTargetPhoto(DummyApplication.getContext(), placeID, index);
            if (photo != null) {
                mPhotosCache.put(targetPhotoKey, photo);
            }
        }
        return photo;
    }

    /**
     * Removes all photos for given target's place ID from the internal memory.
     *
     * @param placeID Place ID of the target whose photos should be removed.
     */
    public static void removePhotosOfTarget(String placeID) {
        if (mPhotosCache != null) {
            for (int i = 0; i < 10; i++) {
                mPhotosCache.remove(new TargetPhotoKey(placeID, i));
            }
        }
        SharedDataManager.removeTargetPhotos(DummyApplication.getContext(), placeID);
    }

    /**
     * Initializes the LRU-cache. Context is used
     * to load and save the cache from/to external memory.
     */
    public static void init() {
        if (mPhotosCache == null) {
            initMemoryCache();
        }
    }

    /**
     * Releases the LRU-cache content.
     */
    public static void disconnect() {
        if (mPhotosCache != null) {
            mPhotosCache.evictAll();
            mPhotosCache = null;
        }
    }

    private static class TargetPhotoKey {

        private String placeID;
        private int photoIndex;

        public TargetPhotoKey(String placeID, int photoIndex) {
            this.placeID = placeID;
            this.photoIndex = photoIndex;
        }

        @Override
        public boolean equals(Object o) {
            if (o instanceof TargetPhotoKey) {
                return ((TargetPhotoKey) o).photoIndex == photoIndex && Objects.equals(((TargetPhotoKey) o).placeID, placeID);
            }
            return super.equals(o);
        }

        @Override
        public int hashCode() {
            /* Just a random constant hash for all target photos to allow value comparison instead of reference */
            return 42;
        }

    }

}
