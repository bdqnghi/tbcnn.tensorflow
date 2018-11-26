///
// File:  minimum_spanning_tree.cpp
// Author: ymiyamoto
//
// Created on Tue Jul 18 06:32:51 2017
//

#include <algorithm>
#include <cstdint>

using namespace std;

enum status_t {
  WHITE,
  GRAY,
  BLACK,
};

#define GRAPH_SIZE 101

static uint32_t graph[GRAPH_SIZE][GRAPH_SIZE];
static status_t state[GRAPH_SIZE];
static uint32_t shortest_path[GRAPH_SIZE];

size_t minimum_spanning_tree(size_t num)
{
  size_t minimum_cost = 0;

  for (uint32_t i = 0; i < num; i++) {
    shortest_path[i] = UINT32_MAX;
    state[i] = WHITE;
  }

  shortest_path[0] = 0;
  state[0] = GRAY;

  while (true) {
    uint32_t minimum = UINT32_MAX;
    uint32_t to = 0;
    for (uint32_t j = 0; j < num; j++) {
      if ((shortest_path[j] < minimum) && state[j] != BLACK) {
        minimum = shortest_path[j];
        to = j;
      }
    }

    if (minimum == UINT32_MAX) break;

    state[to] = BLACK;
    minimum_cost += minimum;

    for (uint32_t j = 0; j < num; j++) {
      if ((graph[to][j] != UINT32_MAX) && (state[j] != BLACK)) {
        state[j] = GRAY;
        shortest_path[j] = min(shortest_path[j], graph[to][j]);
      }
    }
  }

  return minimum_cost;
}

#include <iostream>

int32_t main()
{
  uint32_t num;
  cin >> num;

  for (uint32_t i = 0; i < num; i++) {
    for (uint32_t j = 0; j < num; j++) {
      int32_t val;
      cin >> val;
      if (val == -1) {
        graph[i][j] = UINT32_MAX;
      } else {
        graph[i][j] = val;
      }
    }
  }

  cout << minimum_spanning_tree(num) << endl;

  return 0;
}
