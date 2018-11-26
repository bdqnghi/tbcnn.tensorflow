template<typename Content>
FordFulkerson<Content>::FordFulkerson(FlowNetwork<Content> & network):
  _network(network),
  _residualBuilder(_network),
  _traverser( _residualBuilder.residualGraph() ),
  _violation(GraphTypes::FlowTypes::Violation::UNDEFINED)
{}

template<typename Content>
bool FordFulkerson<Content>::flowConserving()
{
  GraphTypes::FlowTypes::Flow sigmaContrib = 0;

  for(typename Graph<Content>::NodeIterator node = _network.flowGraph().nodes_begin();
      node != _network.flowGraph().nodes_end();
      ++node)
    {
      sigmaContrib += _network.contribution(*node);
    }

  if(sigmaContrib != 0)
    _violation = GraphTypes::FlowTypes::Violation::CONSERVATION_VIOLATION;

  return (_violation != GraphTypes::FlowTypes::Violation::CONSERVATION_VIOLATION);
}

template<typename Content>
bool FordFulkerson<Content>::flowLimitCompliant()
{

  GraphTypes::node_id source, target;
  typename Graph<Content>::EdgeIterator edge = _network.flowGraph().edges_begin();
  bool compliant;

  compliant = true;
  while( edge != _network.flowGraph().edges_end() && compliant )
    {
      source = edge->source();
      target = edge->target();

      if( _network.flow(source, target) < _network.minCapacity(source, target)
	  ||
	  _network.flow(source, target) > _network.maxCapacity(source, target) )
	_violation = GraphTypes::FlowTypes::Violation::FLOW_LIMITS_VIOLATION;

      compliant = (_violation != GraphTypes::FlowTypes::Violation::FLOW_LIMITS_VIOLATION);

      ++edge;
    }

  return compliant;
}

template<typename Content>
bool FordFulkerson<Content>::internallyNeutral()
{
  bool neutral;
  typename Graph<Content>::NodeIterator node = _network.flowGraph().nodes_begin();

  neutral = true;
  while( node != _network.flowGraph().nodes_end() && neutral )
    {
      if(*node != _network.source() && *node != _network.sink() && _network.contribution(*node) != 0)
	_violation = GraphTypes::FlowTypes::Violation::INTERNAL_NEUTRALITY_VIOLATION;

      neutral = (_violation != GraphTypes::FlowTypes::Violation::INTERNAL_NEUTRALITY_VIOLATION);

      ++node;
    }

  return neutral;
}

template<typename Content>
bool FordFulkerson<Content>::compatible()
{
  return ( flowConserving() && flowLimitCompliant() );
}

template<typename Content>
const GraphTypes::FlowTypes::Violation &  FordFulkerson<Content>::violation()const
{
  return _violation;
}

template<typename Content>
void FordFulkerson<Content>::nilFlow()
{
  for(typename Graph<Content>::EdgeIterator edge = _network.flowGraph().edges_begin();
      edge != _network.flowGraph().edges_end();
      ++edge)
    {
      _network.setFlow(edge->source(), edge->target(), 0);
    }
}

template<typename Content>
void FordFulkerson<Content>::maximizeFlow()  throw(GraphException::IncompatibleNetwork)
{
  GraphTypes::FlowTypes::Flow delta;

  if( !compatible() )
    throw GraphException::IncompatibleNetwork(_violation, "FordFulkerson<Content>::maximizeFlow()");

  _residualBuilder.build();
  _traverser.breadth_once( _network.source(), _noaction );

  while( _exists_path_to_sink() )
    {
      _extract_path_to_sink();

      delta = _min_residual_on_path();

      _change_flow(delta);

      _residualBuilder.build();
      _traverser.breadth_once( _network.source(), _noaction );
    }
}

template<typename Content>
bool FordFulkerson<Content>::_exists_path_to_sink()
{
  return _traverser.traversingGraph().has_node( _network.sink() );
}

template<typename Content>
void FordFulkerson<Content>::_extract_path_to_sink()
{
  GraphTypes::node_id currentNode, predecessor;
  const Graph<> & traversing = _traverser.traversingGraph();

  if( _path.size() > 0 )
    _path.clear();

  currentNode = _network.sink();
  _path.push_front(currentNode);

  while( traversing.predecessors_begin(currentNode) != traversing.predecessors_end(currentNode) )
    {
      currentNode = *traversing.predecessors_begin(currentNode);
      _path.push_front(currentNode);
    }
}

template<typename Content>
GraphTypes::FlowTypes::Flow FordFulkerson<Content>::_min_residual_on_path()
{
  GraphTypes::Cost min;
  std::list<GraphTypes::node_id>::iterator pred, succ;
  const Graph<> & traversing = _traverser.traversingGraph();

  min = ::abs( traversing.getCost(*_path.begin(), *++_path.begin()) );

  succ = _path.begin();
  while( succ != _path.end() )
    {
      pred = succ++ ;

      if( succ != _path.end() )
	{
	  GraphTypes::Cost cost = ::abs( traversing.getCost(*pred, *succ) );
	  if(cost < min)
	    min = cost;
	}
    }

  return (GraphTypes::FlowTypes::Flow) min;
}

template<typename Content>
void FordFulkerson<Content>::_change_flow(const GraphTypes::FlowTypes::Flow & delta)
{
  std::list<GraphTypes::node_id>::iterator it_pred, it_succ;
  GraphTypes::node_id pred, succ;
  GraphTypes::FlowTypes::Flow oldFlow, newFlow;
  GraphTypes::Cost residual;
  int sign;

  it_succ = _path.begin();
  while( it_succ != _path.end() )
    {
      it_pred = it_succ++;

      if( it_succ != _path.end() )
	{
	  sign = ( _residualBuilder.residualGraph().getCost(*it_pred, *it_succ) >= 0 ) ? 1 : -1;

	  if(sign > 0)
	    {
	      pred = *it_pred;
	      succ = *it_succ;
	    }

	  else
	    {
	      pred = *it_succ;
	      succ = *it_pred;
	    }

	  oldFlow = _network.flow(pred, succ);

	  newFlow = oldFlow + sign*delta;

	  _network.setFlow(pred, succ, newFlow);
	}

    }
}
