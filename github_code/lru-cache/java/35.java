package de.uni_leipzig.simba.GeoCache.cache;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 * @author rspeck
 */
public class Lru extends AbstractCache {

    protected final List<Object> m_access = new LinkedList<Object>();

    /**
     * Constructor calls super constructor with same parameters.
     */
    public Lru(int size, int evictCount) {
        super(size, evictCount);
    }

    /**
     * Evicts the 1st object or m_evictCount objects form m_access list.
     */
    @Override
    protected void evict() {
        Iterator<Object> it = m_access.iterator();
        for (int i = 0; i < m_evictCount; i++)
            if (it.hasNext()) {
                Object o = it.next();
                m_cacheMap.remove(o);
                it.remove();
            }
    }

    @Override
    protected void hitAccess(Object key) {
        int index = m_access.indexOf(key);
        if (index >= 0)
            m_access.remove(index);
        else
            log4j.error("Was it realy a hit?");
        m_access.add(key);
    }

    @Override
    protected void putAccess(Object key) {
        int index = m_access.indexOf(key);
        if (index >= 0) {
            log4j.error("Key in cache!");
            m_access.remove(index);
        }
        m_access.add(key);
    }

    @Override
    public List<Object> removeValues(Object value) {
        List<Object> removed = super.removeValues(value);
        m_access.removeAll(removed);
        return removed;
    }

    @Override
    public int size() {
        return m_cacheMap.size();
    }

    /**
     * return false, if we have an error.
     */
    @Override
    public boolean test() {
        if (size() > m_cacheMaxSize || m_access.size() > size() || m_access.size() > m_cacheMaxSize)
            return false;
        return true;
    }

    @Override
    public String toString() {
        return m_cacheMap.toString() + "\n" + m_access.toString();
    }
    
    @Override
    public boolean contains(Object key) {
    	// TODO Auto-generated method stub
    	return super.contains(key);
    }
    
}