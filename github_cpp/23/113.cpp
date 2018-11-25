#ifndef _FordFulkerson
#define _FordFulkerson

#include <cmath>

#include "FlowNetwork.hpp"
#include "Traverse.hpp"
#include "DoNothingVisitor.hpp"
#include "FnResidualBuilder.hpp"

template<typename Content=GraphTypes::Default>
class FordFulkerson
{
public:
  FordFulkerson(FlowNetwork<Content> & network);

  bool flowConserving();

  bool flowLimitCompliant();

  bool internallyNeutral();

  bool compatible();

  const GraphTypes::FlowTypes::Violation &  violation()const;

  void nilFlow();

  void maximizeFlow() throw(GraphException::IncompatibleNetwork);

private:
  FlowNetwork<Content> & _network;
  FnResidualBuilder<Content> _residualBuilder;
  Traverse<Content> _traverser;
  std::list<GraphTypes::node_id> _path;
  GraphFunctor::DoNothingVisitor _noaction;
  GraphTypes::FlowTypes::Violation _violation;

  bool _exists_path_to_sink();

  void _extract_path_to_sink();

  GraphTypes::FlowTypes::Flow _min_residual_on_path();

  void _change_flow(const GraphTypes::FlowTypes::Flow & delta);
};

#include "FordFulkerson.cpp"

#endif
