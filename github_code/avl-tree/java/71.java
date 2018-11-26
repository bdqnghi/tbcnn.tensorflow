package com.google.common.collect;

import com.google.common.annotations.*;
import javax.annotation.*;
import com.google.common.primitives.*;
import java.io.*;
import java.util.*;
import com.google.common.base.*;

@GwtCompatible(emulated = true)
public final class TreeMultiset extends AbstractSortedMultiset implements Serializable
{
    private final transient TreeMultiset$Reference rootReference;
    private final transient GeneralRange range;
    private final transient TreeMultiset$AvlNode header;
    @GwtIncompatible("not needed in emulated source")
    private static final long serialVersionUID = 1L;
    
    public static TreeMultiset create() {
        return new TreeMultiset(Ordering.natural());
    }
    
    public static TreeMultiset create(@Nullable final Comparator comparator) {
        return (comparator == null) ? new TreeMultiset(Ordering.natural()) : new TreeMultiset(comparator);
    }
    
    public static TreeMultiset create(final Iterable iterable) {
        final TreeMultiset create = create();
        Iterables.addAll(create, iterable);
        return create;
    }
    
    TreeMultiset(final TreeMultiset$Reference rootReference, final GeneralRange range, final TreeMultiset$AvlNode header) {
        super(range.comparator());
        this.rootReference = rootReference;
        this.range = range;
        this.header = header;
    }
    
    TreeMultiset(final Comparator comparator) {
        super(comparator);
        this.range = GeneralRange.all(comparator);
        successor(this.header = new TreeMultiset$AvlNode(null, 1), this.header);
        this.rootReference = new TreeMultiset$Reference(null);
    }
    
    private long aggregateForEntries(final TreeMultiset$Aggregate treeMultiset$Aggregate) {
        final TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        long treeAggregate = treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode);
        if (this.range.hasLowerBound()) {
            treeAggregate -= this.aggregateBelowRange(treeMultiset$Aggregate, treeMultiset$AvlNode);
        }
        if (this.range.hasUpperBound()) {
            treeAggregate -= this.aggregateAboveRange(treeMultiset$Aggregate, treeMultiset$AvlNode);
        }
        return treeAggregate;
    }
    
    private long aggregateBelowRange(final TreeMultiset$Aggregate treeMultiset$Aggregate, @Nullable final TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (treeMultiset$AvlNode == null) {
            return 0L;
        }
        final int compare = this.comparator().compare(this.range.getLowerEndpoint(), treeMultiset$AvlNode.elem);
        if (compare < 0) {
            return this.aggregateBelowRange(treeMultiset$Aggregate, treeMultiset$AvlNode.left);
        }
        if (compare != 0) {
            return treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode.left) + treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + this.aggregateBelowRange(treeMultiset$Aggregate, treeMultiset$AvlNode.right);
        }
        switch (TreeMultiset$4.$SwitchMap$com$google$common$collect$BoundType[this.range.getLowerBoundType().ordinal()]) {
            case 1: {
                return treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode.left);
            }
            case 2: {
                return treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode.left);
            }
            default: {
                throw new AssertionError();
            }
        }
    }
    
    private long aggregateAboveRange(final TreeMultiset$Aggregate treeMultiset$Aggregate, @Nullable final TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (treeMultiset$AvlNode == null) {
            return 0L;
        }
        final int compare = this.comparator().compare(this.range.getUpperEndpoint(), treeMultiset$AvlNode.elem);
        if (compare > 0) {
            return this.aggregateAboveRange(treeMultiset$Aggregate, treeMultiset$AvlNode.right);
        }
        if (compare != 0) {
            return treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode.right) + treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + this.aggregateAboveRange(treeMultiset$Aggregate, treeMultiset$AvlNode.left);
        }
        switch (TreeMultiset$4.$SwitchMap$com$google$common$collect$BoundType[this.range.getUpperBoundType().ordinal()]) {
            case 1: {
                return treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode.right);
            }
            case 2: {
                return treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode.right);
            }
            default: {
                throw new AssertionError();
            }
        }
    }
    
    @Override
    public int size() {
        return Ints.saturatedCast(this.aggregateForEntries(TreeMultiset$Aggregate.SIZE));
    }
    
    @Override
    int distinctElements() {
        return Ints.saturatedCast(this.aggregateForEntries(TreeMultiset$Aggregate.DISTINCT));
    }
    
    @Override
    public int count(@Nullable final Object o) {
        try {
            final TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
            if (!this.range.contains(o) || treeMultiset$AvlNode == null) {
                return 0;
            }
            return treeMultiset$AvlNode.count(this.comparator(), o);
        }
        catch (ClassCastException ex) {
            return 0;
        }
        catch (NullPointerException ex2) {
            return 0;
        }
    }
    
    @Override
    public int add(@Nullable final Object o, final int n) {
        CollectPreconditions.checkNonnegative(n, "occurrences");
        if (n == 0) {
            return this.count(o);
        }
        Preconditions.checkArgument(this.range.contains(o));
        final TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode == null) {
            this.comparator().compare(o, o);
            final TreeMultiset$AvlNode treeMultiset$AvlNode2 = new TreeMultiset$AvlNode(o, n);
            successor(this.header, treeMultiset$AvlNode2, this.header);
            this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode2);
            return 0;
        }
        final int[] array = { 0 };
        this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode.add(this.comparator(), o, n, array));
        return array[0];
    }
    
    @Override
    public int remove(@Nullable final Object o, final int n) {
        CollectPreconditions.checkNonnegative(n, "occurrences");
        if (n == 0) {
            return this.count(o);
        }
        final TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        final int[] array = { 0 };
        TreeMultiset$AvlNode remove;
        try {
            if (!this.range.contains(o) || treeMultiset$AvlNode == null) {
                return 0;
            }
            remove = treeMultiset$AvlNode.remove(this.comparator(), o, n, array);
        }
        catch (ClassCastException ex) {
            return 0;
        }
        catch (NullPointerException ex2) {
            return 0;
        }
        this.rootReference.checkAndSet(treeMultiset$AvlNode, remove);
        return array[0];
    }
    
    @Override
    public int setCount(@Nullable final Object o, final int n) {
        CollectPreconditions.checkNonnegative(n, "count");
        if (!this.range.contains(o)) {
            Preconditions.checkArgument(n == 0);
            return 0;
        }
        final TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode == null) {
            if (n > 0) {
                this.add(o, n);
            }
            return 0;
        }
        final int[] array = { 0 };
        this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode.setCount(this.comparator(), o, n, array));
        return array[0];
    }
    
    @Override
    public boolean setCount(@Nullable final Object o, final int n, final int n2) {
        CollectPreconditions.checkNonnegative(n2, "newCount");
        CollectPreconditions.checkNonnegative(n, "oldCount");
        Preconditions.checkArgument(this.range.contains(o));
        final TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode != null) {
            final int[] array = { 0 };
            this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode.setCount(this.comparator(), o, n, n2, array));
            return array[0] == n;
        }
        if (n == 0) {
            if (n2 > 0) {
                this.add(o, n2);
            }
            return true;
        }
        return false;
    }
    
    private Multiset$Entry wrapEntry(final TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return new TreeMultiset$1(this, treeMultiset$AvlNode);
    }
    
    @Nullable
    private TreeMultiset$AvlNode firstNode() {
        if (this.rootReference.get() == null) {
            return null;
        }
        TreeMultiset$AvlNode treeMultiset$AvlNode;
        if (this.range.hasLowerBound()) {
            final Object lowerEndpoint = this.range.getLowerEndpoint();
            treeMultiset$AvlNode = ((TreeMultiset$AvlNode)this.rootReference.get()).ceiling(this.comparator(), lowerEndpoint);
            if (treeMultiset$AvlNode == null) {
                return null;
            }
            if (this.range.getLowerBoundType() == BoundType.OPEN && this.comparator().compare(lowerEndpoint, treeMultiset$AvlNode.getElement()) == 0) {
                treeMultiset$AvlNode = treeMultiset$AvlNode.succ;
            }
        }
        else {
            treeMultiset$AvlNode = this.header.succ;
        }
        return (treeMultiset$AvlNode == this.header || !this.range.contains(treeMultiset$AvlNode.getElement())) ? null : treeMultiset$AvlNode;
    }
    
    @Nullable
    private TreeMultiset$AvlNode lastNode() {
        if (this.rootReference.get() == null) {
            return null;
        }
        TreeMultiset$AvlNode treeMultiset$AvlNode;
        if (this.range.hasUpperBound()) {
            final Object upperEndpoint = this.range.getUpperEndpoint();
            treeMultiset$AvlNode = ((TreeMultiset$AvlNode)this.rootReference.get()).floor(this.comparator(), upperEndpoint);
            if (treeMultiset$AvlNode == null) {
                return null;
            }
            if (this.range.getUpperBoundType() == BoundType.OPEN && this.comparator().compare(upperEndpoint, treeMultiset$AvlNode.getElement()) == 0) {
                treeMultiset$AvlNode = treeMultiset$AvlNode.pred;
            }
        }
        else {
            treeMultiset$AvlNode = this.header.pred;
        }
        return (treeMultiset$AvlNode == this.header || !this.range.contains(treeMultiset$AvlNode.getElement())) ? null : treeMultiset$AvlNode;
    }
    
    @Override
    Iterator entryIterator() {
        return new TreeMultiset$2(this);
    }
    
    @Override
    Iterator descendingEntryIterator() {
        return new TreeMultiset$3(this);
    }
    
    @Override
    public SortedMultiset headMultiset(@Nullable final Object o, final BoundType boundType) {
        return new TreeMultiset(this.rootReference, this.range.intersect(GeneralRange.upTo(this.comparator(), o, boundType)), this.header);
    }
    
    @Override
    public SortedMultiset tailMultiset(@Nullable final Object o, final BoundType boundType) {
        return new TreeMultiset(this.rootReference, this.range.intersect(GeneralRange.downTo(this.comparator(), o, boundType)), this.header);
    }
    
    static int distinctElements(@Nullable final TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return (treeMultiset$AvlNode == null) ? 0 : treeMultiset$AvlNode.distinctElements;
    }
    
    private static void successor(final TreeMultiset$AvlNode treeMultiset$AvlNode, final TreeMultiset$AvlNode treeMultiset$AvlNode2) {
        treeMultiset$AvlNode.succ = treeMultiset$AvlNode2;
        treeMultiset$AvlNode2.pred = treeMultiset$AvlNode;
    }
    
    private static void successor(final TreeMultiset$AvlNode treeMultiset$AvlNode, final TreeMultiset$AvlNode treeMultiset$AvlNode2, final TreeMultiset$AvlNode treeMultiset$AvlNode3) {
        successor(treeMultiset$AvlNode, treeMultiset$AvlNode2);
        successor(treeMultiset$AvlNode2, treeMultiset$AvlNode3);
    }
    
    @GwtIncompatible("java.io.ObjectOutputStream")
    private void writeObject(final ObjectOutputStream objectOutputStream) {
        objectOutputStream.defaultWriteObject();
        objectOutputStream.writeObject(this.elementSet().comparator());
        Serialization.writeMultiset(this, objectOutputStream);
    }
    
    @GwtIncompatible("java.io.ObjectInputStream")
    private void readObject(final ObjectInputStream objectInputStream) {
        objectInputStream.defaultReadObject();
        final Comparator comparator = (Comparator)objectInputStream.readObject();
        Serialization.getFieldSetter(AbstractSortedMultiset.class, "comparator").set(this, comparator);
        Serialization.getFieldSetter(TreeMultiset.class, "range").set(this, GeneralRange.all(comparator));
        Serialization.getFieldSetter(TreeMultiset.class, "rootReference").set(this, new TreeMultiset$Reference(null));
        final TreeMultiset$AvlNode treeMultiset$AvlNode = new TreeMultiset$AvlNode(null, 1);
        Serialization.getFieldSetter(TreeMultiset.class, "header").set(this, treeMultiset$AvlNode);
        successor(treeMultiset$AvlNode, treeMultiset$AvlNode);
        Serialization.populateMultiset(this, objectInputStream);
    }
}
