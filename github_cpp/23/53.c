



































#ifndef INCLUDE_SEQAN_GRAPH_ALGORITHMS_FORD_FULKERSON_H_
#define INCLUDE_SEQAN_GRAPH_ALGORITHMS_FORD_FULKERSON_H_

namespace seqan {





















template <typename TSpec, typename TCapMap, typename TFlowMap, typename TResidualGraph>
void
_buildResidualGraph(Graph<TSpec> const& g,
                      TCapMap const& capacity,
                      TFlowMap const& flow,
                      TResidualGraph& rG)
{
    typedef Graph<TSpec> TGraph;
    typedef typename Iterator<TGraph, VertexIterator>::Type TVertexIterator;
    typedef typename Iterator<TGraph, EdgeIterator>::Type TEdgeIterator;
    typedef typename Value<TFlowMap>::Type TFlow;
    typedef typename Value<TCapMap>::Type TCap;

    clear(rG);
    TVertexIterator itV(g);
    for(;!atEnd(itV);goNext(itV)) {
        _createVertices(rG, getValue(itV));
    }

    TEdgeIterator itE(g);
    for(;!atEnd(itE);goNext(itE)) {
        typedef typename EdgeDescriptor<TResidualGraph>::Type TEdgeDescriptor;
        TFlow f = getProperty(flow, getValue(itE));
        TCap cap = getProperty(capacity, getValue(itE));
        if (f > 0) {
            TEdgeDescriptor e_rG = findEdge(rG, targetVertex(itE), sourceVertex(itE));
            if (e_rG == 0) addEdge(rG, targetVertex(itE), sourceVertex(itE), f);
            else cargo(e_rG) += f;
        }
        if (f < cap) {
            TEdgeDescriptor e_rG = findEdge(rG, sourceVertex(itE), targetVertex(itE));
            if (e_rG == 0) addEdge(rG, sourceVertex(itE), targetVertex(itE), cap - f);
            else cargo(e_rG) += cap - f;
        }
    }
}

template <typename TSpec, typename TPredecessorMap, typename TVertexDescriptor>
inline typename Size<Graph<TSpec> >::Type
_getMinimumAug(Graph<TSpec> const & rG,
                 TPredecessorMap & predecessor,
                 TVertexDescriptor const source,
                 TVertexDescriptor sink)
{
    typedef Graph<TSpec> TGraph;
    typedef typename Size<TGraph>::Type TSize;
    typedef TSize TFlow;
    typedef typename Iterator<String<TVertexDescriptor>, Rooted>::Type TIterator;

    
    TVertexDescriptor nilPred = getNil<typename VertexDescriptor<TGraph>::Type>();
    String<TVertexDescriptor> predMap;
    resizeVertexMap(predMap, rG);
    TIterator it = begin(predMap);
    for(;!atEnd(it);goNext(it)) {
        *it = nilPred;
    }

    
    TVertexDescriptor pred = getProperty(predecessor, sink);
    TFlow f = getCargo(findEdge(rG, pred,sink));
    assignProperty(predMap, sink, pred);
    while(pred != source) {
        sink = pred;
        pred = getProperty(predecessor, sink);
        TFlow f2 = getCargo(findEdge(rG, pred,sink));
        assignProperty(predMap, sink, pred);
        if (f2 < f) f = f2;
    }

    
    predecessor = predMap;
    return f;
}


template <typename TSpec, typename TVertexDescriptor, typename TCapMap, typename TFlowMap>
typename Value<TFlowMap>::Type
fordFulkersonAlgorithm(TFlowMap & flow,
                       Graph<TSpec> const & g,
                       TVertexDescriptor const source,
                       TVertexDescriptor const sink,
                       TCapMap const & capacity)
{
    typedef Graph<TSpec> TGraph;
    typedef typename EdgeDescriptor<TGraph>::Type TEdgeDescriptor;
    typedef typename Iterator<TGraph, EdgeIterator>::Type TEdgeIterator;
    typedef typename Iterator<TGraph, OutEdgeIterator>::Type TOutEdgeIterator;
    typedef typename Value<TFlowMap>::Type TFlow;

    
    TVertexDescriptor nilPred = getNil<typename VertexDescriptor<TGraph>::Type>();
    resizeEdgeMap(flow, g);
    TEdgeIterator itE(g);
    for(;!atEnd(itE);goNext(itE)) {
        assignProperty(flow, getValue(itE), 0);
    }

    
    Graph<Directed<TFlow> > rG;
    _buildResidualGraph(g,capacity, flow, rG);


    
    String<TVertexDescriptor> predMap;
    String<TVertexDescriptor> distMap;
    breadthFirstSearch(predMap, distMap, rG, source);

    while (getProperty(predMap, sink) != nilPred) {
        TFlow inc = _getMinimumAug(rG, predMap, source, sink);
        TEdgeIterator itEdge(g);
        for(;!atEnd(itEdge);goNext(itEdge)) {
            TVertexDescriptor u = sourceVertex(itEdge);
            TVertexDescriptor v = targetVertex(itEdge);
            TEdgeDescriptor e = getValue(itEdge);
            if (getProperty(predMap, v) == u) assignProperty(flow, e, getProperty(flow, e) + inc);
            if (getProperty(predMap, u) == v) assignProperty(flow, e, getProperty(flow, e) - inc);
        }
        
        _buildResidualGraph(g, capacity, flow, rG);
        
        clear(predMap);
        clear(distMap);
        breadthFirstSearch(predMap, distMap, rG, source);
    }

    TFlow valF = 0;
    TOutEdgeIterator itOutEdge(g, source);
    for(;!atEnd(itOutEdge);goNext(itOutEdge)) {
        valF += getProperty(flow, getValue(itOutEdge));
    }
    return valF;
}

}  

#endif  
