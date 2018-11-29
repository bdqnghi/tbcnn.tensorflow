package com.facebook.common.collect;

import com.google.common.collect.ImmutableList;
import com.google.common.collect.ImmutableList.Builder;
import com.google.common.collect.Sets;
import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public class TopologicalSort
{
  public static <T> ImmutableList<TopologicalSort.Node<T>> a(Collection<TopologicalSort.Node<T>> paramCollection)
  {
    LinkedHashSet localLinkedHashSet = Sets.b();
    Iterator localIterator1 = paramCollection.iterator();
    while (localIterator1.hasNext())
    {
      TopologicalSort.Node localNode3 = (TopologicalSort.Node)localIterator1.next();
      if (!localNode3.b.isEmpty())
        continue;
      localLinkedHashSet.add(localNode3);
    }
    ImmutableList.Builder localBuilder = ImmutableList.e();
    while (!localLinkedHashSet.isEmpty())
    {
      TopologicalSort.Node localNode1 = (TopologicalSort.Node)localLinkedHashSet.iterator().next();
      localLinkedHashSet.remove(localNode1);
      localBuilder.b(localNode1);
      Iterator localIterator3 = localNode1.c.iterator();
      while (localIterator3.hasNext())
      {
        TopologicalSort.Edge localEdge = (TopologicalSort.Edge)localIterator3.next();
        TopologicalSort.Node localNode2 = localEdge.b;
        localIterator3.remove();
        localNode2.b.remove(localEdge);
        if (!localNode2.b.isEmpty())
          continue;
        localLinkedHashSet.add(localNode2);
      }
    }
    Iterator localIterator2 = paramCollection.iterator();
    while (localIterator2.hasNext())
    {
      if (((TopologicalSort.Node)localIterator2.next()).b.isEmpty())
        continue;
      throw new RuntimeException("Cycle in background tasks dependencies");
    }
    return localBuilder.b();
  }
}

/* Location:           /data1/software/jd-gui/com.facebook.katana_2.0_liqucn.com-dex2jar.jar
 * Qualified Name:     com.facebook.common.collect.TopologicalSort
 * JD-Core Version:    0.6.0
 */