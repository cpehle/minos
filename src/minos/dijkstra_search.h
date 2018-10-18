// Copyright 2014 Red Blob Games <redblobgames@gmail.com> 
// Feel free to use this code in your own projects, including commercial projects
// License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>
#pragma once

#include <map>
#include <tuple>

#include "minos/priority_queue.h"

namespace minos {

template<typename Location, typename Graph>
auto dijkstra_search(Graph graph, Location start) -> std::pair<std::map<Location, Location>, std::map<Location, double>>
{
  PriorityQueue<Location, double> frontier;
  std::map<Location, Location> came_from;
  std::map<Location, double> cost_so_far;

  frontier.put(start, 0);
  came_from[start] = start;
  cost_so_far[start] = 0;
  
  while (!frontier.empty()) {
    Location current = frontier.get();

    for (Location next : graph.neighbors(current)) {
      double new_cost = cost_so_far[current] + graph.cost(current, next);
      if (cost_so_far.find(next) == cost_so_far.end()
          || new_cost < cost_so_far[next]) {
        cost_so_far[next] = new_cost;
        came_from[next] = current;
        frontier.put(next, new_cost);
      }
    }
  }

  return std::make_pair(came_from, cost_so_far);
}
}