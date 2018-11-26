package ingvar.android.processor.memory.persistence;

import android.util.LruCache;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import ingvar.android.processor.exception.PersistenceException;
import ingvar.android.processor.persistence.AbstractRepository;
import ingvar.android.processor.persistence.CompositeKey;
import ingvar.android.processor.persistence.IRepository;

import static ingvar.android.processor.util.CommonUtils.isEquals;
import static ingvar.android.processor.util.CommonUtils.objectHashCode;

/**
 * Simple implementation memory LRU-cache.
 *
 * <br/><br/>Created by Igor Zubenko on 2015.03.19.
 */
public class MemoryRepository<K, R> extends AbstractRepository<K, R> {

    /**
     * Wrapper class for persisting objects
     * @param <V> object class
     */
    public static class Entry<V> {
        private long creationTime;
        private V value;

        public Entry(V value, long creationTime) {
            this.value = value;
            this.creationTime = creationTime;
        }

        public Entry(V value) {
            this(value, System.currentTimeMillis());
        }

        /**
         * Get time when object persisted to repository
         *
         * @return milliseconds
         */
        public long getCreationTime() {
            return creationTime;
        }

        /**
         * Get persisted object
         * @return object
         */
        public V getValue() {
            return value;
        }
    }

    private LruCache<Object, Entry> storage;
    private IRepository decorated;

    /**
     * @param maxSize max repository size
     */
    public MemoryRepository(int maxSize) {
        this(maxSize, null);
    }

    /**
     * @param lruCache LRU-cache
     */
    public MemoryRepository(LruCache<Object, Entry> lruCache) {
        this(lruCache, null);
    }

    /**
     * @param maxSize max repository size
     * @param decorated decorated repository
     */
    public MemoryRepository(int maxSize, IRepository decorated) {
        storage = new LruCache<>(maxSize);
        this.decorated = decorated;
    }

    /**
     * @param lruCache LRU-cache
     * @param decorated decorated repository
     */
    public MemoryRepository(LruCache<Object, Entry> lruCache, IRepository decorated) {
        this.storage = lruCache;
        this.decorated = decorated;
    }

    @Override
    protected Object composeKey(Object major, Object minor) {
        return major == null ? minor : new Pair(major, minor);
    }

    @Override
    protected R persistSingle(K key, R data) {
        storage.put(key, new Entry<>(data));
        if(decorated != null) {
            decorated.persist(key, data);
        }
        return data;
    }

    @Override
    protected Collection<R> persistCollection(CompositeKey<K> key, Collection<R> data) {
        if(key.getMinors().size() > 0) {
            if(key.getMinors().size() != data.size()) {
                throw new PersistenceException("Count of minor keys and data mismatch!");
            }
            Iterator ik = key.getMinors().iterator();
            Iterator id = data.iterator();
            while (ik.hasNext()) {
                storage.put(composeKey(key.getMajor(), ik.next()), new Entry<>(id.next()));
            }
        } else {
            storage.put(key.getMajor(), new Entry<>(data));
        }
        if(decorated != null) {
            decorated.persist(key, data);
        }
        return data;
    }

    @Override
    @SuppressWarnings("unchecked")
    protected R obtainSingle(K key, long expiryTime) {
        R result = null;
        Entry<R> entry = storage.get(key);

        if(entry != null) {
            if(isNotExpired(entry.creationTime, expiryTime)) {
                result = entry.getValue();
            }
        } else if (decorated != null) {
            //try to load from decorated repository
            result = decorated.obtain(key, expiryTime);
            if(result != null) {
                storage.put(key, new Entry<>(result, decorated.getCreationTime(key)));
            }
        }

        return result;
    }

    @Override
    @SuppressWarnings("unchecked")
    protected Collection<R> obtainCollection(CompositeKey<K> key, long expiryTime) {
        Collection<R> result = null;
        if(key.getMinors().size() > 0) {
            result = new ArrayList<>();
            for(Object minor : key.getMinors()) {
                Entry<R> single = storage.get(composeKey(key.getMajor(), minor));
                if(single != null && isNotExpired(single.creationTime, expiryTime)) {
                    result.add(single.value);
                } else {
                    result.clear();
                    break;
                }
            }
        } else {
            Entry<Collection<R>> entry = storage.get(key);
            if(entry != null && isNotExpired(entry.creationTime, expiryTime)) {
                result = entry.value;
            }
        }
        if((result == null || result.isEmpty()) && decorated != null) {
            result = decorated.obtain(key, expiryTime);
            if(result != null) {
                persist(key, result);
            }
        }
        return result == null || result.isEmpty() ? null : result;
    }

    @Override
    protected void removeSingle(K key) {
        storage.remove(key);
        if(decorated != null) {
            decorated.remove(key);
        }
    }

    @Override
    protected void removeCollection(CompositeKey<K> key) {
        if(key.getMinors().isEmpty()) {
            storage.remove(key);
        } else {
            for(Object minor : key.getMinors()) {
                storage.remove(composeKey(key.getMajor(), minor));
            }
        }
        if(decorated != null) {
            decorated.remove(key);
        }
    }

    @Override
    public void removeAll() {
        storage.evictAll();
        if(decorated != null) {
            decorated.removeAll();
        }
    }

    @Override
    public long getCreationTime(Object key) {
        long time = -1;
        Entry entry = storage.get(key);
        if(entry != null) {
            time = entry.getCreationTime();

        } else if(decorated != null) {
            time = decorated.getCreationTime(key);
        }

        return time;
    }

    @Override
    public boolean canHandle(Class dataClass) {
        return true;
    }

    private class Pair {

        Object head;
        Object tail;

        public Pair(Object head, Object tail) {
            this.head = head;
            this.tail = tail;
        }

        @Override
        public int hashCode() {
            int hashCode = 0;
            hashCode += objectHashCode(head) * 31;
            hashCode += objectHashCode(tail) * 31;
            return hashCode;
        }

        @Override
        public boolean equals(Object obj) {
            if(obj instanceof MemoryRepository.Pair) {
                Pair o = (Pair) obj;
                return isEquals(head, o.head) && isEquals(tail, o.tail);
            }
            return false;
        }
    }

}
