package ru.leventov.psgs.index;

import gnu.trove.function.Consumer;
import gnu.trove.function.IntObjConsumer;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import static ru.leventov.psgs.util.ByteBuffers.*;

public class BTree {
    private static final int CPU_CACHE_LINE_SIZE = 64;
    private static final int MIN_PAGE_HEADER_SIZE = 8;
    private static int cpuCacheLineAligningHeader(int blockSize) {
        return MIN_PAGE_HEADER_SIZE + ((CPU_CACHE_LINE_SIZE - MIN_PAGE_HEADER_SIZE) % blockSize);
    }

    private static final byte LEAF_LEVEL = 0;

    private static class Stats {
        private ArrayList<Integer> pageCountsByLevel;
        private long entryCount;
        private long capacity;
        private float load;
        private float memoryUtilization;
    }

    private final int valueLength;
    private final int innerBlockSize;
    private final int innerPageHeaderSize;
    private final int entrySize;
    private final int leafPageHeaderSize;
    private final int innerPageCapacity;
    private final int leafPageCapacity;

    private transient Storage storage;

    private transient ByteBuffer root;
    private int rootIndex;
    private byte rootLevel;

    private Stats stats;

    public BTree(Storage storage, int valueLength) {
        this.valueLength = valueLength;
        // + int key
        entrySize = valueLength + 4;
        leafPageHeaderSize = cpuCacheLineAligningHeader(entrySize);
        int leafPageCapacity = (storage.pageSize() - leafPageHeaderSize) / entrySize;
        // make odd
        this.leafPageCapacity = (leafPageCapacity - 1) | 1;

        // + child page index
        innerBlockSize = entrySize + 4;
        innerPageHeaderSize = cpuCacheLineAligningHeader(innerBlockSize);
        // 4 bytes for additional child page index in the end
        int innerPageCapacity = (storage.pageSize() - innerPageHeaderSize - 4) / innerBlockSize;
        this.innerPageCapacity = (innerPageCapacity - 1) | 1;

        this.storage = storage;

        rootIndex = 0;
        root = storage.allocateNewPage();
        rootLevel = LEAF_LEVEL;

        stats = new Stats();
        stats.pageCountsByLevel = new ArrayList<>();
        stats.pageCountsByLevel.add(1);
        stats.entryCount = 1;
    }

    void setStorageAfterDeserialization(Storage storage) {
        this.storage = storage;
        root = storage.cacheAndGetPage(rootIndex);
    }

    void countStats() {
        stats.capacity = stats.pageCountsByLevel.get(0) * leafPageCapacity;
        for (int i = 1; i < stats.pageCountsByLevel.size(); i++) {
            stats.capacity += stats.pageCountsByLevel.get(i) * innerPageCapacity;
        }
        stats.load = ((float) stats.entryCount) / stats.capacity;
        stats.memoryUtilization =
                (((float) stats.entryCount) * (4 + valueLength)) /
                (((float) storage.pageCount()) * storage.pageSize());
    }

    @Nullable
    public ByteBuffer get(int key) {
        ByteBuffer page = root;
        boolean rootIsInner = rootLevel != LEAF_LEVEL;
        if (rootIsInner) {
            do {
                int keyIndex = keyIndexOnInner(page, key);
                if (keyIndex >= 0) {
                    locateValueOnInner(page, keyIndex);
                    return slice(page);
                } else {
                    int childIndex = -keyIndex - 1;
                    page = getChild(page, childIndex);
                }
            } while (!isLeaf(page));
        }
        int keyIndex = keyIndexOnLeaf(page, key);
        if (keyIndex >= 0) {
            locateValueOnLeaf(page, keyIndex);
            return slice(page);
        } else {
            return null;
        }
    }

    @NotNull
    public ByteBuffer insert(int key) {
        boolean rootIsLeaf = rootLevel == LEAF_LEVEL;
        if (isFull(root, rootIsLeaf)) {
            splitRoot();
            rootIsLeaf = false;
        }
        ByteBuffer page = root;
        if (!rootIsLeaf) {
            for (; ;) {
                page.clear();
                int keyIndex = keyIndexOnInner(page, key);
                if (keyIndex >= 0) {
                    locateValueOnInner(page, keyIndex);
                    return slice(page);
                } else {
                    int childIndex = -keyIndex - 1;
                    ByteBuffer childPage = getChild(page, childIndex);
                    boolean childIsLeaf = isLeaf(childPage);
                    if (isFull(childPage, childIsLeaf)) {
                        if (childIsLeaf) splitLeafChild(page, childIndex, childPage);
                        else splitInnerChild(page, childIndex, childPage);
                        int newSplitKey = getKeyOnInner(page, childIndex);
                        if (newSplitKey == key) {
                            locateValueOnInner(page, childIndex);
                            return slice(page);
                        }
                        else if (newSplitKey < key) {
                            childIndex += 1;
                        }
                    }
                    page = getChild(page, childIndex);
                    if (childIsLeaf) break;
                }
            }
        }
        page.clear();
        int keyIndex = keyIndexOnLeaf(page, key);
        if (keyIndex >= 0) {
            locateValueOnLeaf(page, keyIndex);
        } else {
            int insertIndex = -keyIndex - 1;
            int pageEntryCount = getEntryCount(page);
            int insertPos = leafPageHeaderSize + insertIndex * entrySize;
            shiftWithin(page, insertPos,
                    (pageEntryCount - insertIndex) * entrySize, entrySize);
            setEntryCount(page, pageEntryCount + 1);
            stats.entryCount++;
            page.putInt(insertPos, key);
            locateValueOnLeaf(page, insertIndex);
        }
        return slice(page);
    }

    public void forEachEntry(final IntObjConsumer<ByteBuffer> action) {
        storage.forEachPage(new Consumer<ByteBuffer>() {
            @Override
            public void accept(ByteBuffer page) {
                boolean isLeaf = isLeaf(page);
                int entryCount = getEntryCount(page);
                if (isLeaf) {
                    page.position(leafPageHeaderSize);
                    for (int i = 0; i < entryCount; i++) {
                        int key = page.getInt();
                        int nextPos = page.position() + valueLength;
                        page.limit(nextPos);
                        action.accept(key, slice(page));
                        page.position(nextPos);
                        page.limit(page.capacity());
                    }
                } else {
                    page.position(innerPageHeaderSize + 4);
                    for (int i = 0; i < entryCount; i++) {
                        int key = page.getInt();
                        int valueLimit = page.position() + valueLength;
                        page.limit(valueLimit);
                        action.accept(key, slice(page));
                        page.limit(page.capacity());
                        page.position(valueLimit + 4);
                    }
                }
            }
        });
    }

    private boolean isFull(ByteBuffer page, boolean isLeaf) {
        return getEntryCount(page) == (isLeaf ? leafPageCapacity : innerPageCapacity);
    }

    private void splitRoot() {
        root.clear();
        int rightHalfIndex = storage.pageCount();
        ByteBuffer rightHalf = storage.allocateNewPage();
        setLevel(rightHalf, rootLevel);

        incrementPageCountByLevel(rootLevel);
        int halfRootEntryCount;
        int rootHalfSize;
        int headerSize;

        if (rootLevel == LEAF_LEVEL) {
            halfRootEntryCount = leafPageCapacity / 2;
            rootHalfSize = halfRootEntryCount * entrySize;
            headerSize = leafPageHeaderSize;

        } else {
            halfRootEntryCount = innerPageCapacity / 2;
            rootHalfSize = halfRootEntryCount * innerBlockSize + 4;
            headerSize = innerPageHeaderSize;
        }
        ByteBuffer leftHalf = root;
        setEntryCount(leftHalf, halfRootEntryCount);
        setEntryCount(rightHalf, halfRootEntryCount);

        int toNewRootCopyPos = headerSize + rootHalfSize;
        int toRightHalfCopyPos = toNewRootCopyPos + entrySize;
        copy(leftHalf, toRightHalfCopyPos, rightHalf, headerSize, rootHalfSize);

        int newRootIndex = storage.pageCount();
        ByteBuffer newRoot = storage.allocateNewPage();
        setLevel(newRoot, ++rootLevel);
        newRoot.putInt(4, 1); // set entry count
        newRoot.position(innerPageHeaderSize);
        newRoot.putInt(rootIndex);

        leftHalf.position(toNewRootCopyPos);
        leftHalf.limit(toRightHalfCopyPos);
        newRoot.put(leftHalf);

        newRoot.putInt(rightHalfIndex);

        rootIndex = newRootIndex;
        root = newRoot;
        stats.pageCountsByLevel.add(1); // new level
    }

    private void splitLeafChild(ByteBuffer parentPage, int childIndex, ByteBuffer childPage) {
        int newChildEntryCount = leafPageCapacity / 2;
        int childHalfSize = newChildEntryCount * entrySize;
        splitChild(parentPage, childIndex, childPage, LEAF_LEVEL, newChildEntryCount,
                childHalfSize, leafPageHeaderSize);
    }

    private void splitInnerChild(ByteBuffer parentPage, int childIndex, ByteBuffer childPage) {
        int newChildEntryCount = innerPageCapacity / 2;
        int childHalfSize = newChildEntryCount * innerBlockSize + 4;
        splitChild(parentPage, childIndex, childPage, getLevel(childPage), newChildEntryCount,
                childHalfSize, innerPageHeaderSize);
    }

    private void splitChild(ByteBuffer parentPage, int childIndex, ByteBuffer childPage,
                            byte childLevel, int newChildEntryCount, int childHalfSize, int childHeaderSize) {
        childPage.clear();
        int rightHalfIndex = storage.pageCount();
        ByteBuffer rightHalf = storage.allocateNewPage();
        setLevel(rightHalf, childLevel);
        incrementPageCountByLevel(childLevel);
        setEntryCount(childPage, newChildEntryCount);
        setEntryCount(rightHalf, newChildEntryCount);

        int parentEntryCount = getEntryCount(parentPage);
        setEntryCount(parentPage, parentEntryCount + 1);
        int parentShiftPos = innerPageHeaderSize + childIndex * innerBlockSize + 4;
        int parentShiftLength = (parentEntryCount - childIndex) * innerBlockSize;
        shiftWithin(parentPage, parentShiftPos, parentShiftLength, innerBlockSize);

        parentPage.putInt(parentShiftPos + entrySize, rightHalfIndex);

        int childCopyPos = childHeaderSize + childHalfSize;

        copy(childPage, childCopyPos, parentPage, parentShiftPos, entrySize);

        copy(childPage, childCopyPos + entrySize, rightHalf, childHeaderSize, childHalfSize);
    }

    private void incrementPageCountByLevel(int level) {
        stats.pageCountsByLevel.set(level, stats.pageCountsByLevel.get(level) + 1);
    }

    private static byte getLevel(ByteBuffer page) {
        return page.get(0);
    }

    private static boolean isLeaf(ByteBuffer page) {
        return getLevel(page) == LEAF_LEVEL;
    }

    private static void setLevel(ByteBuffer page, byte level) {
        page.put(0, level);
    }

    private static int getEntryCount(ByteBuffer page) {
        return page.getInt(4);
    }

    private static void setEntryCount(ByteBuffer page, int entryCount) {
        page.putInt(4, entryCount);
    }

    private ByteBuffer getChild(ByteBuffer innerPage, int index) {
        int childPageIndex = innerPage.getInt(innerPageHeaderSize + index * innerBlockSize);
        if (rootLevel < 2 || getLevel(innerPage) > 1) {
            return storage.cacheAndGetPage(childPageIndex);
        } else {
            return storage.getPage(childPageIndex);
        }
    }

    private int getKeyOnInner(ByteBuffer innerPage, int index) {
        return innerPage.getInt(innerPageHeaderSize + 4 + index * innerBlockSize);
    }

    private int keyIndexOnLeaf(ByteBuffer leafPage, int key) {
        ByteBuffer page = ByteBuffer.allocate(storage.pageSize());
        page.put(leafPage);
        int blockSize = this.entrySize;
        int low = 0;
        int high = getEntryCount(leafPage) - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int midKey = leafPage.getInt(leafPageHeaderSize + mid * blockSize);

            if (midKey < key) low = mid + 1;
            else if (midKey > key) high = mid - 1;
            else return mid;
        }
        return -low - 1;
    }

    private int keyIndexOnInner(ByteBuffer innerPage, int key) {
        innerPage.clear();
        int blockSize = this.innerBlockSize;
        int low = 0;
        int high = getEntryCount(innerPage) - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int midKey = innerPage.getInt(innerPageHeaderSize + 4 + mid * blockSize);

            if (midKey < key) low = mid + 1;
            else if (midKey > key) high = mid - 1;
            else return mid;
        }
        return -low - 1;
    }

    private void locateValueOnLeaf(ByteBuffer leafPage, int index) {
        int valuePos = leafPageHeaderSize + index * entrySize + 4;
        leafPage.position(valuePos);
        leafPage.limit(valuePos + valueLength);
    }

    private void locateValueOnInner(ByteBuffer innerPage, int index) {
        int valuePos = innerPageHeaderSize + index * innerBlockSize + 8;
        innerPage.position(valuePos);
        innerPage.limit(valuePos + valueLength);
    }
}
