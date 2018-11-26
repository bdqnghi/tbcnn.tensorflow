#include <climits>
#include <cassert>

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <queue>

using namespace std;

using ll = long long int;

struct ReadEdge {
  size_t u, v;
  ll c;
};

class FlowGraph {
 public:
  enum Algorithm {
    kFordFulkerson,
    kPushRelabel,
  };

 public:
  void ReadGraph(vector<ReadEdge> &edges, size_t sz) {
    _graph.resize(sz);
    for (size_t i = 0; i < sz; ++i) {
      _graph[i].idx = i;
    }

    for (size_t i = 0; i < edges.size(); ++i) {
      auto e = edges[i];
      _edges.push_back({i, e.u, e.v, e.c, 0});
      _r_edges.push_back({i, e.v, e.u, 0, 0});
    }

    // must insert here, becuase of the copy of the edge vector
    for (auto &e : _edges) {
      _graph[e.u].adjs.push_back(&e);
    }
    for (auto &e : _r_edges) {
      _graph[e.u].adjs.push_back(&e);
    }
  }

  void PrintGraph(void) {
    for (auto &e : _edges) {
      print_edge(&e);
    }
  }

  ll MaxFlow(size_t s, size_t t, Algorithm algo) {
    reset_node(s);
    reset_edge();

    if (algo == kFordFulkerson) {
      return FordFulkerson(s, t);
    } else if (algo == kPushRelabel) {
      return PushRelabel(s, t);
    }

    return -1;
  }

 private:
  struct Edge {
    size_t idx;
    size_t u, v;
    ll c, f;
  };

  struct Node {
    size_t idx;
    size_t h;
    ll e;
    Edge *last_edge;
    list<Edge *> adjs;
    decltype(adjs)::iterator cur;
  };

 private:
  vector<Node> _graph;
  vector<Edge> _edges;
  vector<Edge> _r_edges;

 private:
  bool is_real_edge(Edge &e) { return e.c != 0; }

  ll get_res(Edge &e) { return is_real_edge(e) ? (e.c - e.f) : e.f; }

  Node &node_at(size_t u) { return _graph[u]; }

  void reset_node(size_t s) {
    for (auto &u : _graph) {
      u.last_edge = nullptr;
      u.cur = u.adjs.begin();
      u.e = 0;
      u.h = 0;
    }
    _graph[s].h = _graph.size();
  }

  void reset_edge(void) {
    for (auto &e : _edges) {
      e.f = 0;
    }
    for (auto &e : _r_edges) {
      e.f = 0;
    }
  }

  void print_edge(Edge *pe, string prefix = "") {
    cout << prefix << " Edge " << pe->idx << ": " << pe->u << " -> " << pe->v
         << " cap: " << pe->c << " f: " << pe->f << endl;
  }

  void print_node(Node &u, string prefix = "") {
    cout << prefix << " Node " << u.idx << " e: " << u.e << " h: " << u.h
         << endl;
  }

  Edge *reverse_edge(Edge *e) {
    return is_real_edge(*e) ? &_r_edges[e->idx] : &_edges[e->idx];
  }

  void ApplyEdge(Edge *e, ll augmented) {
    if (is_real_edge(*e)) {
      e->f += augmented;
      reverse_edge(e)->f += augmented;
    } else {
      e->f -= augmented;
      reverse_edge(e)->f -= augmented;
    }
  }

  // FordFulkerson
 private:
  ll RecordPath(size_t t, vector<Edge *> &path) {
    vector<Edge *> tmp;
    auto augmented = INT_MAX;
    cout << "path: " << endl;
    while (_graph[t].last_edge) {
      print_edge(_graph[t].last_edge, "");
      tmp.push_back(_graph[t].last_edge);
      auto aug = get_res(*(_graph[t].last_edge));
      if (aug < augmented) {
        augmented = aug;
      }
      t = _graph[t].last_edge->u;
    }

    path.clear();
    path.resize(tmp.size());
    copy(tmp.rbegin(), tmp.rend(), path.begin());

    return augmented;
  }

  ll AuxFordFulkerson(size_t s, size_t t, vector<Edge *> &path) {
    reset_node(s);

    cout << __func__ << endl;

    queue<size_t> q;
    q.push(s);
    while (!q.empty()) {
      size_t u = q.front();
      q.pop();

      if (u == t) {
        return RecordPath(t, path);
      }

      for (auto pe : _graph[u].adjs) {
        // the visited flag 'nullptr' conflict with the s's status
        if (!_graph[pe->v].last_edge && get_res(*pe) > 0 && pe->v != s) {
          cout << u << "->" << pe->v << " res: " << get_res(*pe) << endl;
          _graph[pe->v].last_edge = pe;
          q.push(pe->v);
        }
      }
    }

    return 0;
  }

  ll FordFulkerson(size_t s, size_t t) {
    vector<Edge *> path;

    ll augmented;
    while ((augmented = AuxFordFulkerson(s, t, path)) > 0) {
      for (auto pe : path) {
        ApplyEdge(pe, augmented);
      }
    }

    ll result = 0;
    for (auto pe : _graph[s].adjs) {
      result += pe->f;
    }
    return result;
  }

 private:
  void Push(Edge *pe) {
    auto delta = min(_graph[pe->u].e, get_res(*pe));
    ApplyEdge(pe, delta);
    _graph[pe->u].e -= delta;
    _graph[pe->v].e += delta;
    cout << "push: " << pe->u << "->" << pe->v << ": " << delta << endl;
  }

  void Relabel(size_t u) {
    size_t min_h = INT_MAX;
    for (auto pe : _graph[u].adjs) {
      if (get_res(*pe) > 0) {
        min_h = min(min_h, _graph[pe->v].h);
      }
    }
    cout << "Node " << u << "'s h rise from " << _graph[u].h << " to "
         << min_h + 1 << endl;
    _graph[u].h = 1 + min_h;
  }

  void InitPreflow(size_t s) {
    reset_edge();
    reset_node(s);

    for (auto pe : _graph[s].adjs) {
      ApplyEdge(pe, pe->c);
      _graph[pe->v].e = pe->c;
      _graph[s].e -= pe->c;
    }
  }

  void PrintPushRelabel(void) {
    for (auto &u : _graph) {
      print_node(u);
    }
  }

  void Discharge(size_t u) {
    while (node_at(u).e > 0) {
      auto cur = *(node_at(u).cur);
      size_t v = cur->v;
      if (get_res(**node_at(u).cur) > 0 && node_at(u).h == node_at(v).h + 1) {
        Push(cur);
      } else {
        if (++node_at(u).cur == node_at(u).adjs.end()) {
          Relabel(u);
          node_at(u).cur = node_at(u).adjs.begin();
        }
      }
      // cout << " h" << endl;
    }
  }

  ll PushRelabel(size_t s, size_t t) {
    InitPreflow(s);

    list<size_t> l;
    for (auto &u : _graph) {
      if (u.idx != s && u.idx != t) {
        l.push_back(u.idx);
      }
    }

    auto iter = l.begin();
    while (iter != l.end()) {
      PrintPushRelabel();
      auto u = *iter;
      auto old_h = node_at(u).h;
      Discharge(u);
      if (node_at(u).h > old_h && l.size() > 1) {
        l.splice(l.begin(), l, iter);
      }
      ++iter;
    }

    return node_at(t).e;
  }
}; /* class: FlowGraph */

int main(void) {
  vector<ReadEdge> edges = {
      {0, 1, 16}, {0, 4, 13}, {1, 2, 12}, {2, 3, 20}, {2, 4, 9},
      {4, 1, 4},  {4, 5, 14}, {5, 3, 4},  {5, 2, 7},
  };
  FlowGraph graph;
  graph.ReadGraph(edges, 6);
  cout << "kFordFulkerson" << endl;
  cout << "max flow is: "
       << graph.MaxFlow(0, 3, FlowGraph::Algorithm::kFordFulkerson) << endl;
  cout << "-------------------" << endl;

  edges = {
      {0, 1, 12}, {0, 2, 14}, {1, 2, 5},  {1, 4, 16},
      {2, 3, 8},  {3, 1, 7},  {3, 4, 10},
  };
  FlowGraph graph2;
  graph2.ReadGraph(edges, 5);
  cout << "kPushRelabel" << endl;
  cout << "max flow is: "
       << graph2.MaxFlow(0, 4, FlowGraph::Algorithm::kPushRelabel) << endl;
  cout << "-------------------" << endl;

  return 0;
}
