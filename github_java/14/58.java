package u.aly;

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

public final class bB
{
  private static final Comparator a = new bC(0);

  private static int a(int paramInt1, int paramInt2)
  {
    if (paramInt1 < paramInt2)
      return -1;
    if (paramInt2 < paramInt1)
      return 1;
    return 0;
  }

  public static int a(Comparable paramComparable1, Comparable paramComparable2)
  {
    return paramComparable1.compareTo(paramComparable2);
  }

  public static int a(Object paramObject1, Object paramObject2)
  {
    if ((paramObject1 instanceof Comparable))
      return ((Comparable)paramObject1).compareTo((Comparable)paramObject2);
    if ((paramObject1 instanceof List))
      return a((List)paramObject1, (List)paramObject2);
    if ((paramObject1 instanceof Set))
      return a((Set)paramObject1, (Set)paramObject2);
    if ((paramObject1 instanceof Map))
      return a((Map)paramObject1, (Map)paramObject2);
    if ((paramObject1 instanceof byte[]))
      return a((byte[])paramObject1, (byte[])paramObject2);
    throw new IllegalArgumentException("Cannot compare objects of type " + paramObject1.getClass());
  }

  public static int a(List paramList1, List paramList2)
  {
    int i = a(paramList1.size(), paramList2.size());
    int m;
    if (i != 0)
    {
      m = i;
      return m;
    }
    for (int j = 0; ; j++)
    {
      int k = paramList1.size();
      m = 0;
      if (j >= k)
        break;
      int n = a.compare(paramList1.get(j), paramList2.get(j));
      if (n != 0)
        return n;
    }
  }

  public static int a(Map paramMap1, Map paramMap2)
  {
    int i = a(paramMap1.size(), paramMap2.size());
    if (i != 0)
      return i;
    TreeMap localTreeMap1 = new TreeMap(a);
    localTreeMap1.putAll(paramMap1);
    Iterator localIterator1 = localTreeMap1.entrySet().iterator();
    TreeMap localTreeMap2 = new TreeMap(a);
    localTreeMap2.putAll(paramMap2);
    Iterator localIterator2 = localTreeMap2.entrySet().iterator();
    int k;
    do
    {
      if ((!localIterator1.hasNext()) || (!localIterator2.hasNext()))
        return 0;
      Map.Entry localEntry1 = (Map.Entry)localIterator1.next();
      Map.Entry localEntry2 = (Map.Entry)localIterator2.next();
      int j = a.compare(localEntry1.getKey(), localEntry2.getKey());
      if (j != 0)
        return j;
      k = a.compare(localEntry1.getValue(), localEntry2.getValue());
    }
    while (k == 0);
    return k;
  }

  public static int a(Set paramSet1, Set paramSet2)
  {
    int i = a(paramSet1.size(), paramSet2.size());
    if (i != 0)
      return i;
    TreeSet localTreeSet1 = new TreeSet(a);
    localTreeSet1.addAll(paramSet1);
    TreeSet localTreeSet2 = new TreeSet(a);
    localTreeSet2.addAll(paramSet2);
    Iterator localIterator1 = localTreeSet1.iterator();
    Iterator localIterator2 = localTreeSet2.iterator();
    int j;
    do
    {
      if ((!localIterator1.hasNext()) || (!localIterator2.hasNext()))
        return 0;
      j = a.compare(localIterator1.next(), localIterator2.next());
    }
    while (j == 0);
    return j;
  }

  public static int a(byte[] paramArrayOfByte1, byte[] paramArrayOfByte2)
  {
    int i = a(paramArrayOfByte1.length, paramArrayOfByte2.length);
    int m;
    if (i != 0)
    {
      m = i;
      return m;
    }
    for (int j = 0; ; j++)
    {
      int k = paramArrayOfByte1.length;
      m = 0;
      if (j >= k)
        break;
      int n = paramArrayOfByte1[j];
      int i1 = paramArrayOfByte2[j];
      int i2;
      if (n < i1)
        i2 = -1;
      while (i2 != 0)
      {
        return i2;
        if (i1 < n)
        {
          i2 = 1;
          continue;
        }
        i2 = 0;
      }
    }
  }

  public static ByteBuffer a(ByteBuffer paramByteBuffer)
  {
    if (paramByteBuffer == null)
      paramByteBuffer = null;
    do
      return paramByteBuffer;
    while (c(paramByteBuffer));
    byte[] arrayOfByte;
    if (c(paramByteBuffer))
      arrayOfByte = paramByteBuffer.array();
    while (true)
    {
      return ByteBuffer.wrap(arrayOfByte);
      arrayOfByte = new byte[paramByteBuffer.remaining()];
      int i = paramByteBuffer.remaining();
      System.arraycopy(paramByteBuffer.array(), paramByteBuffer.arrayOffset() + paramByteBuffer.position(), arrayOfByte, 0, i);
    }
  }

  public static void a(ByteBuffer paramByteBuffer, StringBuilder paramStringBuilder)
  {
    byte[] arrayOfByte = paramByteBuffer.array();
    int i = paramByteBuffer.arrayOffset();
    int j = i + paramByteBuffer.position();
    int k = i + paramByteBuffer.limit();
    int m;
    if (k - j > 128)
      m = j + 128;
    for (int n = j; ; n++)
    {
      if (n >= m)
      {
        if (k != m)
          paramStringBuilder.append("...");
        return;
        m = k;
        break;
      }
      if (n > j)
        paramStringBuilder.append(" ");
      paramStringBuilder.append(Integer.toHexString(0x1FF & (0x100 | arrayOfByte[n])).toUpperCase().substring(1));
    }
  }

  public static ByteBuffer b(ByteBuffer paramByteBuffer)
  {
    if (paramByteBuffer == null)
      return null;
    ByteBuffer localByteBuffer = ByteBuffer.wrap(new byte[paramByteBuffer.remaining()]);
    if (paramByteBuffer.hasArray())
    {
      System.arraycopy(paramByteBuffer.array(), paramByteBuffer.arrayOffset() + paramByteBuffer.position(), localByteBuffer.array(), 0, paramByteBuffer.remaining());
      return localByteBuffer;
    }
    paramByteBuffer.slice().get(localByteBuffer.array());
    return localByteBuffer;
  }

  private static boolean c(ByteBuffer paramByteBuffer)
  {
    return (paramByteBuffer.hasArray()) && (paramByteBuffer.position() == 0) && (paramByteBuffer.arrayOffset() == 0) && (paramByteBuffer.remaining() == paramByteBuffer.capacity());
  }
}

/* Location:           E:\Progs\Dev\Android\Decompile\apktool\zssq\zssq-dex2jar.jar
 * Qualified Name:     u.aly.bB
 * JD-Core Version:    0.6.0
 */