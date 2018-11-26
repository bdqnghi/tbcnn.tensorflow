package com.facebook.common.collect;

public class TopologicalSort$Edge<T>
{
  final TopologicalSort.Node<T> a;
  final TopologicalSort.Node<T> b;

  public TopologicalSort$Edge(TopologicalSort.Node<T> paramNode1, TopologicalSort.Node<T> paramNode2)
  {
    this.a = paramNode1;
    this.b = paramNode2;
  }
}

/* Location:           /data1/software/jd-gui/com.facebook.katana_2.0_liqucn.com-dex2jar.jar
 * Qualified Name:     com.facebook.common.collect.TopologicalSort.Edge
 * JD-Core Version:    0.6.0
 */