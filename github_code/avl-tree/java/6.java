/*
 * Decompiled with CFR 0_115.
 * 
 * Could not load the following classes:
 *  javax.annotation.Nullable
 */
package com.google.common.collect;

import com.google.common.annotations.GwtCompatible;
import com.google.common.annotations.GwtIncompatible;
import com.google.common.base.Preconditions;
import com.google.common.collect.AbstractSortedMultiset;
import com.google.common.collect.BoundType;
import com.google.common.collect.CollectPreconditions;
import com.google.common.collect.GeneralRange;
import com.google.common.collect.Iterables;
import com.google.common.collect.Multiset$Entry;
import com.google.common.collect.Ordering;
import com.google.common.collect.Serialization;
import com.google.common.collect.SortedMultiset;
import com.google.common.collect.TreeMultiset$1;
import com.google.common.collect.TreeMultiset$2;
import com.google.common.collect.TreeMultiset$3;
import com.google.common.collect.TreeMultiset$4;
import com.google.common.collect.TreeMultiset$Aggregate;
import com.google.common.collect.TreeMultiset$AvlNode;
import com.google.common.collect.TreeMultiset$Reference;
import com.google.common.primitives.Ints;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.NavigableSet;
import java.util.Set;
import javax.annotation.Nullable;

@GwtCompatible(emulated=1)
public final class TreeMultiset
extends AbstractSortedMultiset
implements Serializable {
    private final transient TreeMultiset$Reference rootReference;
    private final transient GeneralRange range;
    private final transient TreeMultiset$AvlNode header;
    @GwtIncompatible(value="not needed in emulated source")
    private static final long serialVersionUID = 1;

    public static TreeMultiset create() {
        return new TreeMultiset(Ordering.natural());
    }

    public static TreeMultiset create(@Nullable Comparator comparator) {
        TreeMultiset treeMultiset;
        if (comparator == null) {
            treeMultiset = new TreeMultiset(Ordering.natural());
            return treeMultiset;
        }
        treeMultiset = new TreeMultiset(comparator);
        return treeMultiset;
    }

    public static TreeMultiset create(Iterable iterable) {
        TreeMultiset treeMultiset = TreeMultiset.create();
        Iterables.addAll(treeMultiset, iterable);
        return treeMultiset;
    }

    TreeMultiset(TreeMultiset$Reference treeMultiset$Reference, GeneralRange generalRange, TreeMultiset$AvlNode treeMultiset$AvlNode) {
        super(generalRange.comparator());
        this.rootReference = treeMultiset$Reference;
        this.range = generalRange;
        this.header = treeMultiset$AvlNode;
    }

    TreeMultiset(Comparator comparator) {
        super(comparator);
        this.range = GeneralRange.all(comparator);
        this.header = new TreeMultiset$AvlNode(null, 1);
        TreeMultiset.successor(this.header, this.header);
        this.rootReference = new TreeMultiset$Reference(null);
    }

    private long aggregateForEntries(TreeMultiset$Aggregate treeMultiset$Aggregate) {
        TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        long l2 = treeMultiset$Aggregate.treeAggregate(treeMultiset$AvlNode);
        if (this.range.hasLowerBound()) {
            l2 -= this.aggregateBelowRange(treeMultiset$Aggregate, treeMultiset$AvlNode);
        }
        if (!this.range.hasUpperBound()) return l2;
        l2 -= this.aggregateAboveRange(treeMultiset$Aggregate, treeMultiset$AvlNode);
        return l2;
    }

    private long aggregateBelowRange(TreeMultiset$Aggregate treeMultiset$Aggregate, @Nullable TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (treeMultiset$AvlNode == null) {
            return 0;
        }
        int n2 = this.comparator().compare(this.range.getLowerEndpoint(), TreeMultiset$AvlNode.access$500(treeMultiset$AvlNode));
        if (n2 < 0) {
            return this.aggregateBelowRange(treeMultiset$Aggregate, TreeMultiset$AvlNode.access$600(treeMultiset$AvlNode));
        }
        if (n2 != 0) return treeMultiset$Aggregate.treeAggregate(TreeMultiset$AvlNode.access$600(treeMultiset$AvlNode)) + (long)treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + this.aggregateBelowRange(treeMultiset$Aggregate, TreeMultiset$AvlNode.access$700(treeMultiset$AvlNode));
        switch (TreeMultiset$4.$SwitchMap$com$google$common$collect$BoundType[this.range.getLowerBoundType().ordinal()]) {
            case 1: {
                return (long)treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + treeMultiset$Aggregate.treeAggregate(TreeMultiset$AvlNode.access$600(treeMultiset$AvlNode));
            }
            case 2: {
                return treeMultiset$Aggregate.treeAggregate(TreeMultiset$AvlNode.access$600(treeMultiset$AvlNode));
            }
        }
        throw new AssertionError();
    }

    private long aggregateAboveRange(TreeMultiset$Aggregate treeMultiset$Aggregate, @Nullable TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (treeMultiset$AvlNode == null) {
            return 0;
        }
        int n2 = this.comparator().compare(this.range.getUpperEndpoint(), TreeMultiset$AvlNode.access$500(treeMultiset$AvlNode));
        if (n2 > 0) {
            return this.aggregateAboveRange(treeMultiset$Aggregate, TreeMultiset$AvlNode.access$700(treeMultiset$AvlNode));
        }
        if (n2 != 0) return treeMultiset$Aggregate.treeAggregate(TreeMultiset$AvlNode.access$700(treeMultiset$AvlNode)) + (long)treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + this.aggregateAboveRange(treeMultiset$Aggregate, TreeMultiset$AvlNode.access$600(treeMultiset$AvlNode));
        switch (TreeMultiset$4.$SwitchMap$com$google$common$collect$BoundType[this.range.getUpperBoundType().ordinal()]) {
            case 1: {
                return (long)treeMultiset$Aggregate.nodeAggregate(treeMultiset$AvlNode) + treeMultiset$Aggregate.treeAggregate(TreeMultiset$AvlNode.access$700(treeMultiset$AvlNode));
            }
            case 2: {
                return treeMultiset$Aggregate.treeAggregate(TreeMultiset$AvlNode.access$700(treeMultiset$AvlNode));
            }
        }
        throw new AssertionError();
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
    public int count(@Nullable Object object) {
        try {
            Object object2 = object;
            TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
            if (!this.range.contains(object2)) return 0;
            if (treeMultiset$AvlNode != null) return treeMultiset$AvlNode.count(this.comparator(), object2);
            return 0;
        }
        catch (ClassCastException var2_3) {
            return 0;
        }
        catch (NullPointerException var2_4) {
            return 0;
        }
    }

    @Override
    public int add(@Nullable Object object, int n2) {
        CollectPreconditions.checkNonnegative(n2, "occurrences");
        if (n2 == 0) {
            return this.count(object);
        }
        Preconditions.checkArgument(this.range.contains(object));
        TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode == null) {
            this.comparator().compare(object, object);
            TreeMultiset$AvlNode treeMultiset$AvlNode2 = new TreeMultiset$AvlNode(object, n2);
            TreeMultiset.successor(this.header, treeMultiset$AvlNode2, this.header);
            this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode2);
            return 0;
        }
        int[] arrn = new int[1];
        TreeMultiset$AvlNode treeMultiset$AvlNode3 = treeMultiset$AvlNode.add(this.comparator(), object, n2, arrn);
        this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode3);
        return arrn[0];
    }

    @Override
    public int remove(@Nullable Object object, int n2) {
        TreeMultiset$AvlNode treeMultiset$AvlNode;
        CollectPreconditions.checkNonnegative(n2, "occurrences");
        if (n2 == 0) {
            return this.count(object);
        }
        TreeMultiset$AvlNode treeMultiset$AvlNode2 = (TreeMultiset$AvlNode)this.rootReference.get();
        int[] arrn = new int[1];
        try {
            Object object2 = object;
            if (!this.range.contains(object2)) return 0;
            if (treeMultiset$AvlNode2 == null) {
                return 0;
            }
            treeMultiset$AvlNode = treeMultiset$AvlNode2.remove(this.comparator(), object2, n2, arrn);
        }
        catch (ClassCastException var6_6) {
            return 0;
        }
        catch (NullPointerException var6_7) {
            return 0;
        }
        this.rootReference.checkAndSet(treeMultiset$AvlNode2, treeMultiset$AvlNode);
        return arrn[0];
    }

    @Override
    public int setCount(@Nullable Object object, int n2) {
        CollectPreconditions.checkNonnegative(n2, "count");
        if (!this.range.contains(object)) {
            Preconditions.checkArgument(n2 == 0);
            return 0;
        }
        TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode == null) {
            if (n2 <= 0) return 0;
            this.add(object, n2);
            return 0;
        }
        int[] arrn = new int[1];
        TreeMultiset$AvlNode treeMultiset$AvlNode2 = treeMultiset$AvlNode.setCount(this.comparator(), object, n2, arrn);
        this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode2);
        return arrn[0];
    }

    @Override
    public boolean setCount(@Nullable Object object, int n2, int n3) {
        CollectPreconditions.checkNonnegative(n3, "newCount");
        CollectPreconditions.checkNonnegative(n2, "oldCount");
        Preconditions.checkArgument(this.range.contains(object));
        TreeMultiset$AvlNode treeMultiset$AvlNode = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode == null) {
            if (n2 != 0) return false;
            if (n3 <= 0) return true;
            this.add(object, n3);
            return true;
        }
        int[] arrn = new int[1];
        TreeMultiset$AvlNode treeMultiset$AvlNode2 = treeMultiset$AvlNode.setCount(this.comparator(), object, n2, n3, arrn);
        this.rootReference.checkAndSet(treeMultiset$AvlNode, treeMultiset$AvlNode2);
        if (arrn[0] != n2) return false;
        return true;
    }

    private Multiset$Entry wrapEntry(TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return new TreeMultiset$1(this, treeMultiset$AvlNode);
    }

    @Nullable
    private TreeMultiset$AvlNode firstNode() {
        TreeMultiset$AvlNode treeMultiset$AvlNode;
        TreeMultiset$AvlNode treeMultiset$AvlNode2 = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode2 == null) {
            return null;
        }
        if (this.range.hasLowerBound()) {
            Object object = this.range.getLowerEndpoint();
            treeMultiset$AvlNode = TreeMultiset$AvlNode.access$800((TreeMultiset$AvlNode)this.rootReference.get(), this.comparator(), object);
            if (treeMultiset$AvlNode == null) {
                return null;
            }
            if (this.range.getLowerBoundType() == BoundType.OPEN && this.comparator().compare(object, treeMultiset$AvlNode.getElement()) == 0) {
                treeMultiset$AvlNode = TreeMultiset$AvlNode.access$900(treeMultiset$AvlNode);
            }
        } else {
            treeMultiset$AvlNode = TreeMultiset$AvlNode.access$900(this.header);
        }
        if (treeMultiset$AvlNode == this.header) return null;
        if (!this.range.contains(treeMultiset$AvlNode.getElement())) return null;
        TreeMultiset$AvlNode treeMultiset$AvlNode3 = treeMultiset$AvlNode;
        return treeMultiset$AvlNode3;
    }

    @Nullable
    private TreeMultiset$AvlNode lastNode() {
        TreeMultiset$AvlNode treeMultiset$AvlNode;
        TreeMultiset$AvlNode treeMultiset$AvlNode2 = (TreeMultiset$AvlNode)this.rootReference.get();
        if (treeMultiset$AvlNode2 == null) {
            return null;
        }
        if (this.range.hasUpperBound()) {
            Object object = this.range.getUpperEndpoint();
            treeMultiset$AvlNode = TreeMultiset$AvlNode.access$1000((TreeMultiset$AvlNode)this.rootReference.get(), this.comparator(), object);
            if (treeMultiset$AvlNode == null) {
                return null;
            }
            if (this.range.getUpperBoundType() == BoundType.OPEN && this.comparator().compare(object, treeMultiset$AvlNode.getElement()) == 0) {
                treeMultiset$AvlNode = TreeMultiset$AvlNode.access$1100(treeMultiset$AvlNode);
            }
        } else {
            treeMultiset$AvlNode = TreeMultiset$AvlNode.access$1100(this.header);
        }
        if (treeMultiset$AvlNode == this.header) return null;
        if (!this.range.contains(treeMultiset$AvlNode.getElement())) return null;
        TreeMultiset$AvlNode treeMultiset$AvlNode3 = treeMultiset$AvlNode;
        return treeMultiset$AvlNode3;
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
    public SortedMultiset headMultiset(@Nullable Object object, BoundType boundType) {
        return new TreeMultiset(this.rootReference, this.range.intersect(GeneralRange.upTo(this.comparator(), object, boundType)), this.header);
    }

    @Override
    public SortedMultiset tailMultiset(@Nullable Object object, BoundType boundType) {
        return new TreeMultiset(this.rootReference, this.range.intersect(GeneralRange.downTo(this.comparator(), object, boundType)), this.header);
    }

    static int distinctElements(@Nullable TreeMultiset$AvlNode treeMultiset$AvlNode) {
        if (treeMultiset$AvlNode == null) {
            return 0;
        }
        int n2 = TreeMultiset$AvlNode.access$400(treeMultiset$AvlNode);
        return n2;
    }

    private static void successor(TreeMultiset$AvlNode treeMultiset$AvlNode, TreeMultiset$AvlNode treeMultiset$AvlNode2) {
        TreeMultiset$AvlNode.access$902(treeMultiset$AvlNode, treeMultiset$AvlNode2);
        TreeMultiset$AvlNode.access$1102(treeMultiset$AvlNode2, treeMultiset$AvlNode);
    }

    private static void successor(TreeMultiset$AvlNode treeMultiset$AvlNode, TreeMultiset$AvlNode treeMultiset$AvlNode2, TreeMultiset$AvlNode treeMultiset$AvlNode3) {
        TreeMultiset.successor(treeMultiset$AvlNode, treeMultiset$AvlNode2);
        TreeMultiset.successor(treeMultiset$AvlNode2, treeMultiset$AvlNode3);
    }

    @GwtIncompatible(value="java.io.ObjectOutputStream")
    private void writeObject(ObjectOutputStream objectOutputStream) {
        objectOutputStream.defaultWriteObject();
        objectOutputStream.writeObject(this.elementSet().comparator());
        Serialization.writeMultiset(this, objectOutputStream);
    }

    @GwtIncompatible(value="java.io.ObjectInputStream")
    private void readObject(ObjectInputStream objectInputStream) {
        objectInputStream.defaultReadObject();
        Comparator comparator = (Comparator)objectInputStream.readObject();
        Serialization.getFieldSetter(AbstractSortedMultiset.class, "comparator").set((Object)this, comparator);
        Serialization.getFieldSetter(TreeMultiset.class, "range").set((Object)this, GeneralRange.all(comparator));
        Serialization.getFieldSetter(TreeMultiset.class, "rootReference").set((Object)this, new TreeMultiset$Reference(null));
        TreeMultiset$AvlNode treeMultiset$AvlNode = new TreeMultiset$AvlNode(null, 1);
        Serialization.getFieldSetter(TreeMultiset.class, "header").set((Object)this, treeMultiset$AvlNode);
        TreeMultiset.successor(treeMultiset$AvlNode, treeMultiset$AvlNode);
        Serialization.populateMultiset(this, objectInputStream);
    }

    static /* synthetic */ TreeMultiset$AvlNode access$1200(TreeMultiset treeMultiset) {
        return treeMultiset.firstNode();
    }

    static /* synthetic */ GeneralRange access$1300(TreeMultiset treeMultiset) {
        return treeMultiset.range;
    }

    static /* synthetic */ Multiset$Entry access$1400(TreeMultiset treeMultiset, TreeMultiset$AvlNode treeMultiset$AvlNode) {
        return treeMultiset.wrapEntry(treeMultiset$AvlNode);
    }

    static /* synthetic */ TreeMultiset$AvlNode access$1500(TreeMultiset treeMultiset) {
        return treeMultiset.header;
    }

    static /* synthetic */ TreeMultiset$AvlNode access$1600(TreeMultiset treeMultiset) {
        return treeMultiset.lastNode();
    }

    static /* synthetic */ void access$1700(TreeMultiset$AvlNode treeMultiset$AvlNode, TreeMultiset$AvlNode treeMultiset$AvlNode2, TreeMultiset$AvlNode treeMultiset$AvlNode3) {
        TreeMultiset.successor(treeMultiset$AvlNode, treeMultiset$AvlNode2, treeMultiset$AvlNode3);
    }

    static /* synthetic */ void access$1800(TreeMultiset$AvlNode treeMultiset$AvlNode, TreeMultiset$AvlNode treeMultiset$AvlNode2) {
        TreeMultiset.successor(treeMultiset$AvlNode, treeMultiset$AvlNode2);
    }
}

