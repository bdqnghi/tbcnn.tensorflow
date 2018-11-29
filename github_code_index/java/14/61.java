package org.apache.thrift;

import java.nio.ByteBuffer;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.SortedMap;
import java.util.SortedSet;
import java.util.TreeMap;
import java.util.TreeSet;

public final class b {
    private static final Comparator a = new a();

    private static class a implements Comparator {
        private a() {
        }

        public int compare(Object obj, Object obj2) {
            return (obj == null && obj2 == null) ? 0 : obj == null ? -1 : obj2 == null ? 1 : obj instanceof List ? b.a((List) obj, (List) obj2) : obj instanceof Set ? b.a((Set) obj, (Set) obj2) : obj instanceof Map ? b.a((Map) obj, (Map) obj2) : obj instanceof byte[] ? b.a((byte[]) obj, (byte[]) obj2) : b.a((Comparable) obj, (Comparable) obj2);
        }
    }

    public static int a(byte b, byte b2) {
        return b < b2 ? -1 : b2 < b ? 1 : 0;
    }

    public static int a(double d, double d2) {
        return d < d2 ? -1 : d2 < d ? 1 : 0;
    }

    public static int a(int i, int i2) {
        return i < i2 ? -1 : i2 < i ? 1 : 0;
    }

    public static int a(long j, long j2) {
        return j < j2 ? -1 : j2 < j ? 1 : 0;
    }

    public static int a(Comparable comparable, Comparable comparable2) {
        return comparable.compareTo(comparable2);
    }

    public static int a(String str, String str2) {
        return str.compareTo(str2);
    }

    public static int a(ByteBuffer byteBuffer, byte[] bArr, int i) {
        int remaining = byteBuffer.remaining();
        System.arraycopy(byteBuffer.array(), byteBuffer.arrayOffset() + byteBuffer.position(), bArr, i, remaining);
        return remaining;
    }

    public static int a(List list, List list2) {
        int a = a(list.size(), list2.size());
        if (a != 0) {
            return a;
        }
        for (int i = 0; i < list.size(); i++) {
            int compare = a.compare(list.get(i), list2.get(i));
            if (compare != 0) {
                return compare;
            }
        }
        return 0;
    }

    public static int a(Map map, Map map2) {
        int a = a(map.size(), map2.size());
        if (a != 0) {
            return a;
        }
        SortedMap treeMap = new TreeMap(a);
        treeMap.putAll(map);
        Iterator it = treeMap.entrySet().iterator();
        treeMap = new TreeMap(a);
        treeMap.putAll(map2);
        Iterator it2 = treeMap.entrySet().iterator();
        while (it.hasNext() && it2.hasNext()) {
            Entry entry = (Entry) it.next();
            Entry entry2 = (Entry) it2.next();
            int compare = a.compare(entry.getKey(), entry2.getKey());
            if (compare != 0) {
                return compare;
            }
            a = a.compare(entry.getValue(), entry2.getValue());
            if (a != 0) {
                return a;
            }
        }
        return 0;
    }

    public static int a(Set set, Set set2) {
        int a = a(set.size(), set2.size());
        if (a != 0) {
            return a;
        }
        SortedSet treeSet = new TreeSet(a);
        treeSet.addAll(set);
        SortedSet treeSet2 = new TreeSet(a);
        treeSet2.addAll(set2);
        Iterator it = treeSet.iterator();
        Iterator it2 = treeSet2.iterator();
        while (it.hasNext() && it2.hasNext()) {
            a = a.compare(it.next(), it2.next());
            if (a != 0) {
                return a;
            }
        }
        return 0;
    }

    public static int a(short s, short s2) {
        return s < s2 ? -1 : s2 < s ? 1 : 0;
    }

    public static int a(boolean z, boolean z2) {
        return Boolean.valueOf(z).compareTo(Boolean.valueOf(z2));
    }

    public static int a(byte[] bArr, byte[] bArr2) {
        int a = a(bArr.length, bArr2.length);
        if (a != 0) {
            return a;
        }
        for (int i = 0; i < bArr.length; i++) {
            int a2 = a(bArr[i], bArr2[i]);
            if (a2 != 0) {
                return a2;
            }
        }
        return 0;
    }

    public static String a(byte b) {
        return Integer.toHexString((b | 256) & 511).toUpperCase().substring(1);
    }

    public static void a(ByteBuffer byteBuffer, StringBuilder stringBuilder) {
        byte[] array = byteBuffer.array();
        int arrayOffset = byteBuffer.arrayOffset();
        int limit = byteBuffer.limit();
        int i = limit - arrayOffset > 128 ? arrayOffset + 128 : limit;
        for (int i2 = arrayOffset; i2 < i; i2++) {
            if (i2 > arrayOffset) {
                stringBuilder.append(" ");
            }
            stringBuilder.append(a(array[i2]));
        }
        if (limit != i) {
            stringBuilder.append("...");
        }
    }

    public static byte[] a(ByteBuffer byteBuffer) {
        if (b(byteBuffer)) {
            return byteBuffer.array();
        }
        byte[] bArr = new byte[byteBuffer.remaining()];
        a(byteBuffer, bArr, 0);
        return bArr;
    }

    public static boolean b(ByteBuffer byteBuffer) {
        return byteBuffer.hasArray() && byteBuffer.position() == 0 && byteBuffer.arrayOffset() == 0 && byteBuffer.remaining() == byteBuffer.capacity();
    }

    public static ByteBuffer c(ByteBuffer byteBuffer) {
        return b(byteBuffer) ? byteBuffer : ByteBuffer.wrap(a(byteBuffer));
    }
}
