



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

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class Key, class T, class Cost, Nature Nat>
    class abstract_search {
      public:
        using state = typename graph<Key, T, Cost, Nat>::const_iterator;

        explicit abstract_search(const graph<Key, T, Cost, Nat> &, std::function<bool(state)> is_goal);

      protected:
        const graph<Key, T, Cost, Nat> &g;

        std::function<bool(state)> _is_goal;
    };

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class Key, class T, class Cost, Nature Nat, bool insertFront>
    class abstract_first_search : public abstract_targeted_search<Key, T, Cost, Nat> {
      public:
        using abstract_targeted_search<Key, T, Cost, Nat>::abstract_targeted_search;

        using state = typename abstract_targeted_search<Key, T, Cost, Nat>::state;

        path<state, Cost> run(Key   begin) const;
        path<state, Cost> run(state begin) const;
    };

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class Key, class T, class Cost, Nature Nat>
    using bfs = abstract_first_search<Key, T, Cost, Nat, false>;

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr bfs<Key, T, Cost, Nat> make_bfs(const graph<Key, T, Cost, Nat> &, Args &&...);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class Key, class T, class Cost, Nature Nat>
    using dfs = abstract_first_search<Key, T, Cost, Nat, true>;

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr dfs<Key, T, Cost, Nat> make_dfs(const graph<Key, T, Cost, Nat> &, Args &&...);

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class Key, class T, class Cost, Nature Nat>
    class dijkstra : public abstract_search<Key, T, Cost, Nat> {
      public:
        using abstract_search<Key, T, Cost, Nat>::abstract_search;

        using state = typename abstract_search<Key, T, Cost, Nat>::state;

        std::map<state, path<state, Cost>> run(Key   begin) const;
        
        std::map<state, path<state, Cost>> run(state begin) const;
    };

    template <class Key, class T, class Cost, Nature Nat, class... Args>
    constexpr dijkstra<Key, T, Cost, Nat> make_dijkstra(const graph<Key, T, Cost, Nat> &, Args &&...);
}

#include "GraphSearch.cpp"