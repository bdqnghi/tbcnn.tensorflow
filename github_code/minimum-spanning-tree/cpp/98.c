#include "SpanningTree.h"

#include "DepthFirstSearch.h"
#include "PriorityQueue.h"
#include "UnionFind.h"


namespace algorithm
{
   SpanningTree::SpanningTree(Graph const& g)
      : m_trees()
   {
      DFS<Edge> dfs(g);
      for (size_t v : g.vertices())
      {
         if (dfs.isMarked(v))
            continue;

         Edges edges;
         dfs.pathsFrom(v, [&edges](Edge const& e){ edges.push_back(e); return false; });
         m_trees.emplace_back(std::move(edges));
      }
   }

   size_t SpanningTree::connectedComponentCount() const
   {
      return m_trees.size();
   }

   utils::Range<SpanningTree::edge_it> SpanningTree::edges(size_t ccId) const
   {
      return utils::Range<SpanningTree::edge_it>{ begin(m_trees[ccId]), end(m_trees[ccId]) };
   }

   //--------------------------------------------------------------------------

   LazyPrimMinimumSpanningTree::LazyPrimMinimumSpanningTree(WeightedGraph const& g)
      : m_trees()
   {
      auto less = [](WeightedEdge const& lhs, WeightedEdge const& rhs) { return lhs.weight() < rhs.weight(); };

      MinPriorityQueue<WeightedEdge, decltype(less)> edgeQueue(less);
      std::vector<bool> marked(g.vertexCount(), false);

      for (size_t v : g.vertices())
      {
         if (marked[v])
            continue;

         m_trees.emplace_back();
         marked[v] = true;
         for (auto e : g.edgesFrom(v))
            edgeQueue.add(e);

         while (!edgeQueue.empty())
         {
            auto e = edgeQueue.removeTop();
            if (marked[e.to()])
               continue;

            auto w = e.to();
            marked[w] = true;
            m_trees.back().push_back(e);

            for (auto e : g.edgesFrom(w))
               if (!marked[e.to()])
                  edgeQueue.add(e);
         }
      }
   }

   size_t LazyPrimMinimumSpanningTree::connectedComponentCount() const
   {
      return m_trees.size();
   }

   utils::Range<LazyPrimMinimumSpanningTree::edge_it> LazyPrimMinimumSpanningTree::edges(size_t ccId) const
   {
      return utils::Range<LazyPrimMinimumSpanningTree::edge_it>{ begin(m_trees[ccId]), end(m_trees[ccId]) };
   }

   //--------------------------------------------------------------------------

   EagerPrimMinimumSpanningTree::EagerPrimMinimumSpanningTree(WeightedGraph const& g)
      : m_trees()
   {
      auto less = [](WeightedEdge const& lhs, WeightedEdge const& rhs) { return lhs.weight() < rhs.weight(); };

      MinPriorityQueue<WeightedEdge, decltype(less)> edgeQueue(less);
      std::vector<bool> marked(g.vertexCount(), false);
      std::vector<double> minEdgeDistTo(g.vertexCount(), std::numeric_limits<double>::max());

      for (size_t v : g.vertices())
      {
         if (marked[v])
            continue;

         m_trees.emplace_back();
         marked[v] = true;
         for (auto e : g.edgesFrom(v))
         {
            edgeQueue.add(e);
            minEdgeDistTo[e.to()] = e.weight();
         }

         while (!edgeQueue.empty())
         {
            auto e = edgeQueue.removeTop();
            if (marked[e.to()])
               continue;

            auto w = e.to();
            marked[w] = true;
            m_trees.back().push_back(e);

            for (auto e : g.edgesFrom(w))
            {
               auto to = e.to();
               if (!marked[to] && minEdgeDistTo[to] > e.weight())
               {
                  edgeQueue.add(e);
                  minEdgeDistTo[to] = e.weight();
               }
            }
         }
      }
   }

   size_t EagerPrimMinimumSpanningTree::connectedComponentCount() const
   {
      return m_trees.size();
   }

   utils::Range<EagerPrimMinimumSpanningTree::edge_it> EagerPrimMinimumSpanningTree::edges(size_t ccId) const
   {
      return utils::Range<EagerPrimMinimumSpanningTree::edge_it>{ begin(m_trees[ccId]), end(m_trees[ccId]) };
   }

   //--------------------------------------------------------------------------

   KruskalMinimumSpanningTree::KruskalMinimumSpanningTree(WeightedGraph const& g)
      : m_tree()
   {
      std::vector<WeightedEdge> edges;
      for (size_t v : g.vertices())
      {
         auto range = g.edgesFrom(v);
         edges.insert(edges.end(), begin(range), end(range));
      }

      auto less = [](WeightedEdge const& lhs, WeightedEdge const& rhs) { return lhs.weight() < rhs.weight(); };
      MinPriorityQueue<WeightedEdge, decltype(less)> edgeQueue(less, begin(edges), end(edges));

      UnionFind uf(g.vertexCount());
      size_t stopCount = g.vertexCount() - 1;
      while (!edgeQueue.empty() && m_tree.size() < stopCount)
      {
         auto e = edgeQueue.removeTop();
         if (!uf.connect(e.from(), e.to()))
            continue;

         m_tree.push_back(e);
      }
   }

   utils::Range<KruskalMinimumSpanningTree::edge_it> KruskalMinimumSpanningTree::edges() const
   {
      return utils::Range<KruskalMinimumSpanningTree::edge_it>{ begin(m_tree), end(m_tree) };
   }
}
