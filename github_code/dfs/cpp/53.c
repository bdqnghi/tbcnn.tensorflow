///
/// Created by Terae on 05/01/18.
///

#include <queue>
#include <stack>
#include "model/Graph.h"

namespace search {
    template <class stateType, class costType>
    class path {
        template <class, class>                      friend class path_comparator;
        template <class, class, class, Nature, bool> friend class abstract_first_search;
        template <class, class, class, Nature>       friend class dls;
        template <class, class, class, Nature>       friend class ucs;
        template <class, class, class, Nature>       friend class astar;
        template <class, class, class, Nature>       friend class dijkstra;

      public:
        path();
        path(const path<stateType, costType> &);

        costType total_cost() const;
        inline std::size_t get_nr_steps() const;

        inline bool empty() const;

        inline bool contain_state(const stateType &) const;

        std::pair<stateType, costType> pop_front();

      private:
        inline void addState(const stateType &);
        inline void addCost (const  costType &);


        inline stateType back_state()  const;

        std::deque<stateType> _states;
        std::deque<costType>  _costs;
    };

    template <class stateType, class costType>
    class path_comparator {
      private:
        std::function<double(stateType)> _heuristic;

      public:
        path_comparator(std::function<double(stateType)> heuristic);

        bool operator() (const path<stateType, costType> &, const path<stateType, costType> &);
    };

    ///
    /// @brief Abstract class for all search algorithms
    ///
    /// Subclasses:
    /// - @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// - @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// - @ref bfs Breadth-First Search algorithm
    /// - @ref dfs Depth-First Search algorithm
    /// - @ref dls Depth-Limited Search algorithm
    /// - @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// - @ref ucs Uniform-Cost Search algorithm
    /// - @ref astar A* Search algorithm
    /// - @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    class abstract_search {
      public:
        using state = typename graph<Key, T, Cost, Nat>::const_iterator;

        explicit abstract_search(const graph<Key, T, Cost, Nat> &, std::function<bool(state)> is_goal);

      protected:
        const graph<Key, T, Cost, Nat> &g;

        std::function<bool(state)> _is_goal;
    };

    ///
    /// @brief Abstract class for all search algorithms with a specified target
    ///
    /// Allow the user to give one or several nodes-goal to the algorithm
    /// instead of giving a function<bool(state)> parameter in entry
    ///
    /// Subclasses:
    /// - @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// - @ref bfs Breadth-First Search algorithm
    /// - @ref dfs Depth-First Search algorithm
    /// - @ref dls Depth-Limited Search algorithm
    /// - @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// - @ref ucs Uniform-Cost Search algorithm
    /// - @ref astar A* Search algorithm
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    class abstract_targeted_search : public abstract_search<Key, T, Cost, Nat> {
      public:
        using abstract_search<Key, T, Cost, Nat>::abstract_search;

        using state = typename graph<Key, T, Cost, Nat>::const_iterator;

        explicit abstract_targeted_search(const graph<Key, T, Cost, Nat> &, Key   target);
        explicit abstract_targeted_search(const graph<Key, T, Cost, Nat> &, state target);

        explicit abstract_targeted_search(const graph<Key, T, Cost, Nat> &, const std::list<Key>   &list_target);
        explicit abstract_targeted_search(const graph<Key, T, Cost, Nat> &, const std::list<state> &list_target);

      protected:
        std::list<state> _targets;
    };

    ///
    /// @brief Abstract class for Depth-First and Breadth-First Searches
    ///
    /// @tparam insertFront Specialization parameter between dfs (true) and bfs(false) using respectively a `std::stack` and a `std::queue`
    ///
    /// Subclasses:
    /// - @ref bfs Breadth-First Search algorithm
    /// - @ref dfs Depth-First Search algorithm
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref dls Depth-Limited Search algorithm
    /// @sa @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// @sa @ref ucs Uniform-Cost Search algorithm
    /// @sa @ref astar A* Search algorithm
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    template <class Key, class T, class Cost, Nature Nat, bool insertFront>
    class abstract_first_search : public abstract_targeted_search<Key, T, Cost, Nat> {
      public:
        using abstract_targeted_search<Key, T, Cost, Nat>::abstract_targeted_search;

        using state = typename abstract_targeted_search<Key, T, Cost, Nat>::state;

        path<state, Cost> run(Key   begin) const;
        path<state, Cost> run(state begin) const;
    };

    ///
    /// @brief Breadth-First Search class
    /// @see https://en.wikipedia.org/wiki/Breadth-First_Search
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref dfs Depth-First Search algorithm
    /// @sa @ref dls Depth-Limited Search algorithm
    /// @sa @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// @sa @ref ucs Uniform-Cost Search algorithm
    /// @sa @ref astar A* Search algorithm
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    using bfs = abstract_first_search<Key, T, Cost, Nat, false>;

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr bfs<Key, T, Cost, Nat> make_bfs(const graph<Key, T, Cost, Nat> &, Args &&...);

    ///
    /// @brief Depth-First Search class
    /// @see https://en.wikipedia.org/wiki/Depth-First_Search
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref bfs Breadth-First Search algorithm
    /// @sa @ref dls Depth-Limited Search algorithm
    /// @sa @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// @sa @ref ucs Uniform-Cost Search algorithm
    /// @sa @ref astar A* Search algorithm
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    using dfs = abstract_first_search<Key, T, Cost, Nat, true>;

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr dfs<Key, T, Cost, Nat> make_dfs(const graph<Key, T, Cost, Nat> &, Args &&...);

    ///
    /// @brief Depth-Limited Search class
    /// @see https://en.wikipedia.org/wiki/Iterative_Deepening_Depth-First_Search
    ///
    /// @tparam l Predetermined depth limit 'l' to create a Depth-Limited Search (fix dfs's loop problem). Have to be well choose, in function of the problem.
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref bfs Breadth-First Search algorithm
    /// @sa @ref dfs Depth-First Search algorithm
    /// @sa @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// @sa @ref ucs Uniform-Cost Search algorithm
    /// @sa @ref astar A* Search algorithm
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    class dls : public abstract_targeted_search<Key, T, Cost, Nat> {
      public:
        using abstract_targeted_search<Key, T, Cost, Nat>::abstract_targeted_search;

        using state = typename abstract_targeted_search<Key, T, Cost, Nat>::state;

        path<state, Cost> run(Key   begin, int depth) const;
        path<state, Cost> run(state begin, int depth) const;
    };

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr dls<Key, T, Cost, Nat> make_dls(const graph<Key, T, Cost, Nat> &, Args &&...);

    ///
    /// @brief Iterative-Deepening Depth-First Search
    /// @see https://en.wikipedia.org/wiki/Iterative_Deepening_Depth-First_Search
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref bfs Breadth-First Search algorithm
    /// @sa @ref dfs Depth-First Search algorithm
    /// @sa @ref dls Depth-Limited Search algorithm
    /// @sa @ref ucs Uniform-Cost Search algorithm
    /// @sa @ref astar A* Search algorithm
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    class iddfs : public abstract_targeted_search<Key, T, Cost, Nat> {
      public:
        using abstract_targeted_search<Key, T, Cost, Nat>::abstract_targeted_search;

        using state = typename abstract_targeted_search<Key, T, Cost, Nat>::state;

        path<state, Cost> run(Key   begin) const;
        path<state, Cost> run(state begin) const;
    };

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr iddfs<Key, T, Cost, Nat> make_iddfs(const graph<Key, T, Cost, Nat> &, Args &&...);

    ///
    /// @brief Uniform-Cost Search
    /// @see https://en.wikipedia.org/wiki/Talk:Uniform-Cost_Search
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref bfs Breadth-First Search algorithm
    /// @sa @ref dfs Depth-First Search algorithm
    /// @sa @ref dls Depth-Limited Search algorithm
    /// @sa @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// @sa @ref astar A* Search algorithm
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    class ucs : public abstract_targeted_search<Key, T, Cost, Nat> {
      public:
        using abstract_targeted_search<Key, T, Cost, Nat>::abstract_targeted_search;

        using state = typename abstract_targeted_search<Key, T, Cost, Nat>::state;

        path<state, Cost> run(Key   begin) const;
        path<state, Cost> run(state begin) const;
    };

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr ucs<Key, T, Cost, Nat> make_ucs(const graph<Key, T, Cost, Nat> &, Args &&...);

    ///
    /// @brief A* Search class
    /// @see https://en.wikipedia.org/wiki/A*_search_algorithm
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref bfs Breadth-First Search algorithm
    /// @sa @ref dfs Depth-First Search algorithm
    /// @sa @ref dls Depth-Limited Search algorithm
    /// @sa @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// @sa @ref ucs Uniform-Cost Search algorithm
    /// @sa @ref dijkstra dijkstra algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    class astar : public abstract_targeted_search<Key, T, Cost, Nat> {
      public:
        using abstract_targeted_search<Key, T, Cost, Nat>::abstract_targeted_search;

        using state = typename abstract_targeted_search<Key, T, Cost, Nat>::state;

        path<state, Cost> run(Key   begin, std::function<double(state)> heuristic) const;
        path<state, Cost> run(state begin, std::function<double(state)> heuristic) const;
    };

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr astar<Key, T, Cost, Nat> make_astar(const graph<Key, T, Cost, Nat> &, Args &&...);

    ///
    /// @brief dijkstra class
    /// @see https://en.wikipedia.org/wiki/dijkstra%27s_algorithm
    ///
    /// @sa @ref abstract_search Abstract class for all search algorithms
    /// @sa @ref abstract_targeted_search Abstract class for all search algorithms with a specified target
    /// @sa @ref abstract_first_search Abstract class for First Search algorithms (BFS, DFS)
    /// @sa @ref bfs Breadth-First Search algorithm
    /// @sa @ref dfs Depth-First Search algorithm
    /// @sa @ref dls Depth-Limited Search algorithm
    /// @sa @ref iddfs Iterative-Deepening Depth-First Search algorithm
    /// @sa @ref ucs Uniform-Cost Search algorithm
    /// @sa @ref astar A* Search algorithm
    ///
    /// @since version 1.1
    ///
    template <class Key, class T, class Cost, Nature Nat>
    class dijkstra : public abstract_search<Key, T, Cost, Nat> {
      public:
        using abstract_search<Key, T, Cost, Nat>::abstract_search;

        using state = typename abstract_search<Key, T, Cost, Nat>::state;

        std::map<state, path<state, Cost>> run(Key   begin) const;
        // TODO
        std::map<state, path<state, Cost>> run(state begin) const;
    };

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr dijkstra<Key, T, Cost, Nat> make_dijkstra(const graph<Key, T, Cost, Nat> &, Args &&...);
}

#include "GraphSearch.cpp"