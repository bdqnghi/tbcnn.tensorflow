



































#ifndef INCLUDE_SEQAN_GRAPH_ALGORITHMS_DEPTH_FIRST_SEARCH_H_
#define INCLUDE_SEQAN_GRAPH_ALGORITHMS_DEPTH_FIRST_SEARCH_H_

namespace seqan {





















template <typename TSpec, typename TVertexDescriptor, typename TTokenMap, typename TPredecessorMap, typename TDiscoveryTimeMap, typename TFinishingTimeMap, typename TVal>
void
_dfsVisit(Graph<TSpec> const& g,
           TVertexDescriptor const u,
           TTokenMap& tokenMap,
           TPredecessorMap& predecessor,
           TDiscoveryTimeMap& disc,
           TFinishingTimeMap& finish,
           TVal& time)
{
    typedef typename Iterator<Graph<TSpec>, AdjacencyIterator>::Type TAdjacencyIterator;

    assignProperty(tokenMap, u, true);
    ++time;
    assignProperty(disc, u, time);
    TAdjacencyIterator itad(g,u);
    for(;!atEnd(itad);goNext(itad)) {
        TVertexDescriptor v = getValue(itad);
        if (getProperty(tokenMap, v) == false) {
            assignProperty(predecessor, v, u);
            _dfsVisit(g, v, tokenMap, predecessor, disc, finish, time);
        }
    }
    ++time;
    assignProperty(finish, u, time);
}


template <typename TSpec, typename TPredecessorMap, typename TDiscoveryTimeMap, typename TFinishingTimeMap>
void depthFirstSearch(TPredecessorMap & predecessor,
                      TDiscoveryTimeMap & disc,
                      TFinishingTimeMap & finish,
                      Graph<TSpec> const & g)
{
    typedef Graph<TSpec> TGraph;
    typedef typename Size<TGraph>::Type TSize;
    typedef typename Iterator<TGraph, VertexIterator>::Type TVertexIterator;
    typedef typename VertexDescriptor<TGraph>::Type TVertexDescriptor;
    typedef typename Value<TPredecessorMap>::Type TPredVal;

    
    resizeVertexMap(predecessor, g);
    resizeVertexMap(disc, g);
    resizeVertexMap(finish, g);
    TPredVal nilPred = getNil<TVertexDescriptor>();

    String<bool> tokenMap;
    resizeVertexMap(tokenMap, g);
    TVertexIterator it(g);
    for(;!atEnd(it);goNext(it)) {
        assignProperty(tokenMap, getValue(it), false);
        assignProperty(predecessor, getValue(it), nilPred);
    }

    TSize time = 0;

    goBegin(it);
    for(;!atEnd(it);goNext(it)) {
        TVertexDescriptor u = getValue(it);
        if (getProperty(tokenMap, u) == false) {
            _dfsVisit(g, u, tokenMap, predecessor, disc, finish, time);
        }
    }
}

}  

#endif  
