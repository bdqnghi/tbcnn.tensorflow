




































#ifndef INCLUDE_SEQAN_GRAPH_ALGORITHMS_DEPTH_FIRST_SEARCH_H_
#define INCLUDE_SEQAN_GRAPH_ALGORITHMS_DEPTH_FIRST_SEARCH_H_

namespace seqan {





















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
    typedef typename Iterator<Graph<TSpec>, AdjacencyIterator>::Type TAdjacencyIterator;

    enum class _DfsTask : uint8_t
    {
        EXPLORE,
        FINISH
    };

    
    resizeVertexMap(predecessor, g);
    resizeVertexMap(disc, g);
    resizeVertexMap(finish, g);
    TPredVal nil = getNil<TVertexDescriptor>();
    String<bool> tokenMap;
    resizeVertexMap(tokenMap, g);
    TVertexIterator it(g);
    for(;!atEnd(it);goNext(it))
    {
        assignProperty(tokenMap, getValue(it), false);
        assignProperty(predecessor, getValue(it), nil);
    }
    TSize time = 0;

    
    
    
    std::vector<std::pair<TVertexDescriptor, _DfsTask> > vStack;

    
    goBegin(it);
    for(; !atEnd(it); goNext(it))
    {
        
        TVertexDescriptor v = getValue(it);
        if (getProperty(tokenMap, v))
        {
            continue;
        }

        vStack.clear();
        vStack.emplace_back(v, _DfsTask::EXPLORE);
        while (!vStack.empty())
        {
            
            auto stackItem = vStack.back();
            vStack.pop_back();
            TVertexDescriptor v = stackItem.first;

            if (stackItem.second == _DfsTask::FINISH)
            {
                assignProperty(finish, v, ++time);
            }
            else if (!getProperty(tokenMap, v))       
            {
                assignProperty(tokenMap, v, true);    
                assignProperty(disc, v, ++time);      
                vStack.emplace_back(v, _DfsTask::FINISH); 

                
                
                
                TAdjacencyIterator itad(g, v);
                goEnd(itad);
                while (!atBegin(itad))
                {
                    goPrevious(itad);
                    TVertexDescriptor nextV = getValue(itad);
                    if (!getProperty(tokenMap, nextV))
                    {
                        vStack.emplace_back(nextV, _DfsTask::EXPLORE);
                        assignProperty(predecessor, nextV, v);
                    }
                }
            }
        }
    }
}

}  

#endif  
