



































#ifndef INCLUDE_SEQAN_GRAPH_ALGORITHMS_TOPOLOGICAL_SORT_H_
#define INCLUDE_SEQAN_GRAPH_ALGORITHMS_TOPOLOGICAL_SORT_H_

namespace seqan {






















template <typename TSpec, typename TVertexDescriptor>
void topologicalSort(String<TVertexDescriptor> & topSort,
                     Graph<TSpec> const & g)
{
    typedef typename Size<Graph<TSpec> >::Type TSize;

    
    String<TSize> predMap;
    String<TSize> discoveryTimeMap;
    String<TSize> finishingTimeMap;

    
    depthFirstSearch(predMap, discoveryTimeMap, finishingTimeMap, g);
    SEQAN_ASSERT_EQ(numVertices(g), length(predMap));
    SEQAN_ASSERT_EQ(numVertices(g), length(discoveryTimeMap));
    SEQAN_ASSERT_EQ(numVertices(g), length(finishingTimeMap));

    
    typedef std::pair<TSize, TVertexDescriptor> TTimeVertexPair;
    std::priority_queue<TTimeVertexPair> q;
    typedef typename Iterator<Graph<TSpec>, VertexIterator>::Type TVertexIterator;
    TVertexIterator it(g);
    for (; !atEnd(it); goNext(it))
        q.push(std::make_pair(getProperty(finishingTimeMap, getValue(it)), getValue(it)));

    
    resize(topSort, numVertices(g));
    TSize count = 0;
    while (!q.empty())
    {
        assignValue(topSort, count, q.top().second);
        q.pop();
        ++count;
    }
    SEQAN_ASSERT_EQ(length(topSort), numVertices(g));
}

}  

#endif  
