



































#ifndef INCLUDE_SEQAN2_GRAPH_ALGORITHMS_BREADTH_FIRST_SEARCH_H_
#define INCLUDE_SEQAN2_GRAPH_ALGORITHMS_BREADTH_FIRST_SEARCH_H_

namespace seqan2 {























template <typename TSpec, typename TVertexDescriptor, typename TPredecessorMap, typename TDistanceMap>
void breadthFirstSearch(TPredecessorMap & predecessor,
                        TDistanceMap & distance,
                        Graph<TSpec> const & g,
                        TVertexDescriptor const source)
{
    typedef Graph<TSpec> TGraph;
    typedef typename Iterator<TGraph, VertexIterator>::Type TVertexIterator;
    typedef typename Value<TPredecessorMap>::Type TPredVal;
    typedef typename Value<TDistanceMap>::Type TDistVal;

    
    resizeVertexMap(predecessor, g);
    resizeVertexMap(distance, g);
    TPredVal nilPred = getNil<typename VertexDescriptor<TGraph>::Type>();
    TDistVal infDist = _getInfinityDistance(distance);

    String<bool> tokenMap;
    resizeVertexMap(tokenMap, g);
    TVertexIterator it(g);
    for(;!atEnd(it);goNext(it)) {
        assignProperty(tokenMap, getValue(it), false);
        assignProperty(distance, getValue(it), infDist);
        assignProperty(predecessor, getValue(it), nilPred);
    }
    assignProperty(tokenMap, source, true);
    assignProperty(distance, source, 0);
    assignProperty(predecessor, source, nilPred);
    std::deque<TVertexDescriptor> queue;
    queue.push_back(source);

    
    while (!queue.empty()) {
        TVertexDescriptor u = queue.front();
        queue.pop_front();
        typedef typename Iterator<Graph<TSpec>, OutEdgeIterator>::Type TOutEdgeIterator;
        TOutEdgeIterator itout(g,u);
        for(;!atEnd(itout);goNext(itout)) {
            TVertexDescriptor v = targetVertex(itout);
            if (getProperty(tokenMap, v) == false) {
                assignProperty(tokenMap, v, true);
                assignProperty(distance, v, getProperty(distance,u) + 1);
                assignProperty(predecessor, v, u);
                queue.push_back(v);
            }
        }
    }
}

}  

#endif  
