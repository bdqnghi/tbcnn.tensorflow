package rui.coder.algorithms.cache;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * 实现LRU 算法
 * <p>
 * <a href="https://mp.weixin.qq.com/s/ofQ_VSVI1Qj9BYM0sV_MWw">10 行 Java 代码实现最近被使用（LRU）缓存</a>
 * </p>
 * <p>
 * 数据结构的支持
 * <ol>
 * <li>链表 ，链式</li>
 * <li>hash 表 ，快速定位</li>
 * </ol>
 * </p>
 * <p>
 * java 提供了相应的数据结构 {@link LinkedHashMap}
 * </p>
 *
 * @author 赵睿
 * @see java.util.LinkedHashMap#removeEldestEntry(Map.Entry)
 */
public class LRU<K, V> extends LinkedHashMap<K, V> {

    private int cacheSize;

    public LRU(int initialCapacity, int cacheSize) {
        super(16, 0.75f, true);
        this.cacheSize = cacheSize;
    }


    @Override
    protected boolean removeEldestEntry(Map.Entry<K, V> eldest) {
        return size() >= cacheSize;

    }

    /*
        问题：
            1. linkedhashmap号称java里面最耗内存的数据结构，没有之一
            2. linkedhashmap非线程安全哦，用了sync就性能太低了
     */
}
