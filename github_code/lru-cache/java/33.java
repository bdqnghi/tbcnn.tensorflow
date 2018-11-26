package com.doctor.mybatis.cache.practice;

import static org.junit.Assert.*;
import static org.hamcrest.core.IsEqual.*;

import org.apache.ibatis.cache.decorators.LruCache;
import org.apache.ibatis.cache.impl.PerpetualCache;
import org.junit.Test;

/**
 * mybatis3 LruCache
 * ---------------------------
 * 
 * {@code LruCache} 的实现和FifoCache的实现思路是一样的，不同的是key序列的维护数据结构不一样， {@code LruCache }　key的LRU算法维护利用了jdk　
 * {@code LinkedHashMap}　数据结构（请看文档说明，也提到LRU算法）．
 * 
 * 没有实现锁功能，不支持并发．
 * 
 * @author doctor {@link https://github.com/doctorwho1986}
 *
 *
 * @time 2015年3月10日
 */
public class LruCachePractice {

	@Test
	public void test_LruCache() {
		LruCache lruCache = new LruCache(new PerpetualCache("test_LruCache"));
		lruCache.setSize(2);
		assertThat(lruCache.getSize(), equalTo(0));

		lruCache.putObject("name", "doctor");
		lruCache.putObject("age", 2000);
		lruCache.putObject("age", 3000);
		lruCache.putObject("age", 29000);
		lruCache.putObject("url", "https://github.com/doctorwho1986");

		assertThat(lruCache.getSize(), equalTo(2));
		assertThat(lruCache.getObject("name"), equalTo(null));
	}
}
