
package EvacSim.jme3tools.navmesh.util;

import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.Vector;


public abstract class Heap<T> extends Vector<T> {
    
    

    private Comparator<T> comp = null;
    
    
    
    
    
    protected boolean isHeap = true;

    
    public Heap() {
        super();
    }

    
    public Heap(Comparator<T> c) {
        super();
        comp = c;
    }

    
    public Heap(int capacity) {
        super(capacity);
    }

    
    public Heap(Collection<T> c) {
        super();
        addAll(c);
    }

    
    @Override
    public T remove(int index) {
        if (!isHeap) {
            rebuildHeap();
        }

        T o = get(index);

        set(index, get(size() - 1));
        removeElementAt(size() - 1);

        heapify(index);

        return o;
    }

    
    @Override
    public boolean remove(Object o) {
        boolean found = false;
        for (int i = 0; i < size(); i++) {
            if (o == null ? get(i) == null : o.equals(get(i))) {
                found = true;
                remove(i);

                break;
            }
        }

        return found;
    }

    
    @Override
    public boolean add(T o) {
        if (!isHeap) {
            rebuildHeap();
        }

        boolean b = super.add(o);

        for (int node = size() - 1; node > 0;) {
            int cmp;
            int parent = (int) ((node - 1) / 2);

            if (cmp(node, parent) < 0) {
                
                T tmp = get(node);
                set(node, get(parent));
                set(parent, tmp);
            }

            node = parent;
        }

        
        
        
        

        return b;
    }

    
    @Override
    public boolean addAll(Collection c) {
        boolean b = super.addAll(c);
        rebuildHeap();
        return (b);
    }

    
    public void rebuildHeap() {
        
        for (int i = (int) (size() / 2); i >= 0; i--) {
            heapify(i);
        }

        isHeap = true;
    }

    
    public void sort() {
        Object[] a = toArray();
        if (comp == null) {
            Arrays.sort(a);
        } else {
            Arrays.sort((T[])a, comp);
        }

        elementData = a;

        
        
        
        
        
        
        
        
        
        
        

        
        
        
        
        
        
        isHeap = false;
    }

    
    protected int cmp(int node1, int node2) {
        int c = 0;
        if (comp != null) {
            c = comp.compare(get(node1), get(node2));
        } else {
            c = ((Comparable<T>) get(node1)).compareTo(get(node2));
        }

        return c;
    }

    
    private void heapify(int node, int size) {
        if (node > size) {
            return;
        }

        int left = (node + 1) * 2 - 1;
        int right = (node + 1) * 2;

        int minidx = node;

        if (left < size && cmp(left, node) <= 0) {
            minidx = left;
        }
        if (right < size && cmp(right, node) <= 0 && cmp(right, left) <= 0) {
            minidx = right;
        }

        if (minidx != node) {
            
            T tmp = get(node);
            set(node, get(minidx));
            set(minidx, tmp);

            heapify(minidx, size);
        }
    }

    
    private void heapify(int node) {
        heapify(node, size());
    }

    
    public boolean isHeap() {
        return isHeap;
    }
}
