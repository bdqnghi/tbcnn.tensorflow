package study.leet.fun;

/**
 * @author teng.qian
 * @date 2016/2/2.
 */
public class LRUCache {

    /**
     * 内部存储entry数组
     */
    private Entry[] array;
    /**
     * 容量
     */
    private int capacity;
    /**
     * 已经存储的数据量
     */
    private int size;
    /**
     * 实现lru的链表
     */
    private CacheQueue cacheQueue;

    /**
     * @param capacity
     */
    public LRUCache(int capacity) {
        array = new Entry[fullToPower(capacity)];
        this.capacity = capacity;
        cacheQueue = new CacheQueue();
    }

    /**
     * @param key
     * @return
     */
    public int get(int key) {
        Entry inner = getInner(key);
        if (inner == null) {
            return -1;
        }
        modifyCacheQueue(inner);
        return inner.value;
    }

    /**
     * @param key
     * @param value
     */
    public void set(int key, int value) {
        Entry innerEntry = getInner(key);
        if (innerEntry == null) {
            innerEntry = new Entry(key, value);

            if (checkFull()) {
                Entry toBeRemove = cacheQueue.last;
                removeInArray(toBeRemove);
                removeInQueue(toBeRemove);
            } else {
                size++;
            }
            insertCacheQueue(innerEntry);
            insertArray(innerEntry);
        } else {
            innerEntry.value = value;
            modifyCacheQueue(innerEntry);
        }
    }

    /**
     * 移出一个链表中的元素
     *
     * @param toBeRemove
     */
    private void removeInQueue(Entry toBeRemove) {
        if (toBeRemove.preInCache == null) {
            if (toBeRemove.nextInCache == null) {
                cacheQueue.first = null;
                cacheQueue.last = null;
            } else {
                cacheQueue.first = toBeRemove.nextInCache;
                toBeRemove.nextInCache.preInCache = null;
            }

        } else {
            if (toBeRemove.nextInCache == null) {
                toBeRemove.preInCache.nextInCache = null;
                cacheQueue.last = toBeRemove.preInCache;
            } else {
                toBeRemove.preInCache.nextInCache = toBeRemove.nextInCache;
                toBeRemove.nextInCache.preInCache = toBeRemove.preInCache;
            }
        }
    }

    /**
     * 给数组添加一个元素
     *
     * @param innerEntry
     */
    private void insertArray(Entry innerEntry) {
        int index = innerEntry.key % array.length;
        Entry entry = array[index];
        if (entry != null && entry.next != null) {
            entry = entry.next;
        }
        if (entry == null) {
            array[index] = innerEntry;
        } else {
            entry.next = innerEntry;
            innerEntry.pre = entry;
        }
    }

    /**
     * 移出一个链表中的元素
     *
     * @param toBeRemove
     */
    private void removeInArray(Entry toBeRemove) {
        int index = toBeRemove.key % array.length;
        if (toBeRemove.pre == null) {
            if (toBeRemove.next == null) {
                array[index] = null;
            } else {
                array[index] = toBeRemove.next;
                toBeRemove.next.pre = null;
            }
        } else {
            if (toBeRemove.next == null) {
                toBeRemove.pre.next = null;
            } else {
                toBeRemove.pre.next = toBeRemove.next;
                toBeRemove.next.pre = toBeRemove.pre;
            }
        }
    }

    private Entry getInner(int key) {
        Entry entry = array[key % array.length];
        while (entry != null && entry.key != key) {
            entry = entry.next;
        }
        if (entry == null) {
            return null;
        }
        return entry;
    }

    /**
     * 内部队列，进行排除最久未使用
     */
    private class CacheQueue {
        private Entry first;
        private Entry last;
    }

    /**
     * 内部数据结构
     */
    private class Entry {
        private int key;
        private int value;
        private Entry next;
        private Entry pre;
        private Entry preInCache;
        private Entry nextInCache;

        Entry(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

    /**
     * 更新原本已经存在的entry的位置
     *
     * @param entry
     */
    private void modifyCacheQueue(Entry entry) {
        removeInQueue(entry);
        insertCacheQueue(entry);
    }

    /**
     * 插入entry
     */
    private void insertCacheQueue(Entry entry) {
        if (cacheQueue.first == null) {
            entry.preInCache = null;
            entry.nextInCache = null;
            cacheQueue.first = entry;
            cacheQueue.last = entry;
        } else {
            entry.nextInCache = cacheQueue.first;
            cacheQueue.first.preInCache = entry;
            cacheQueue.first = entry;
            entry.preInCache = null;
        }
    }

    private boolean checkFull() {
        return size + 1 > capacity;
    }

    /**
     * 将一个数补充到它最近的2的倍数
     *
     * @param i
     * @return
     */
    private int fullToPower(int i) {
        int result = 1;
        while (i > 0) {
            i = i >> 1;
            result = result << 1;
        }
        return result;
    }

    public static void main(String[] args) {
        LRUCache lruCache = new LRUCache(10);
        lruCache.set(10, 13);
        lruCache.set(3, 17);
        lruCache.set(6, 11);
        lruCache.set(10, 5);
        lruCache.set(9, 10);
        lruCache.get(13);
        lruCache.set(2, 19);
        lruCache.get(2);
        lruCache.get(3);
        lruCache.set(5, 25);
        lruCache.get(8);
        lruCache.set(9, 22);
        lruCache.set(5, 5);
        lruCache.set(1, 30);
        lruCache.get(11);
        lruCache.set(9, 12);
        lruCache.get(7);
        lruCache.get(5);
        lruCache.get(8);
        lruCache.get(9);
        lruCache.set(4, 30);
        lruCache.set(9, 3);
        lruCache.get(9);
        lruCache.get(10);
        lruCache.get(10);
        lruCache.set(6, 14);
        lruCache.set(3, 1);
        lruCache.get(3);
        lruCache.set(10, 11);
        lruCache.get(8);
        lruCache.set(2, 14);
        lruCache.get(1);
        lruCache.get(5);
        lruCache.get(4);
        lruCache.set(11, 4);
        lruCache.set(12, 24);
        lruCache.set(5, 18);
        lruCache.get(13);
        lruCache.set(7, 23);
        lruCache.get(8);
        lruCache.get(12);
        lruCache.set(3, 27);
        lruCache.set(2, 12);
        lruCache.get(5);
        lruCache.set(2, 9);
        lruCache.set(13, 4);
        lruCache.set(8, 18);
        lruCache.set(1, 7);
        lruCache.get(6);
        lruCache.set(9, 29);
        lruCache.set(8, 21);
        lruCache.get(5);
        lruCache.set(6, 30);
        lruCache.set(1, 12);
        lruCache.get(10);
        lruCache.set(4, 15);
        lruCache.set(7, 22);
        lruCache.set(11, 26);
        lruCache.set(8, 17);
        lruCache.set(9, 29);
        lruCache.get(5);
        lruCache.set(3, 4);
        lruCache.set(11, 30);
        lruCache.get(12);
        lruCache.set(4, 29);
        lruCache.get(3);
        lruCache.get(9);
        lruCache.get(6);
        lruCache.set(3, 4);
        lruCache.get(1);
        lruCache.get(10);
        lruCache.set(3, 29);
        lruCache.set(10, 28);
        lruCache.set(1, 20);
        lruCache.set(11, 13);
        lruCache.get(3);
        lruCache.set(3, 12);
        lruCache.set(3, 8);
        lruCache.set(10, 9);
        lruCache.set(3, 26);
        lruCache.get(8);
        lruCache.get(7);
        lruCache.get(5);
        lruCache.set(13, 17);
        lruCache.set(2, 27);
        lruCache.set(11, 15);
        lruCache.get(12);
        lruCache.set(9, 19);
        lruCache.set(2, 15);
        lruCache.set(3, 16);
        lruCache.get(1);
        lruCache.set(12, 17);
        lruCache.set(9, 1);
        lruCache.set(6, 19);
        lruCache.get(4);
        lruCache.get(5);
        lruCache.get(5);
        lruCache.set(8, 1);
        lruCache.set(11, 7);
        lruCache.set(5, 2);
        lruCache.set(9, 28);
        lruCache.get(1);
        lruCache.set(2, 2);
        lruCache.set(7, 4);
        lruCache.set(4, 22);
        lruCache.set(7, 24);
        lruCache.set(9, 26);
        lruCache.set(13, 28);
        lruCache.set(11, 26);
    }


}
