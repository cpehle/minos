// Copyright 2014 Red Blob Games <redblobgames@gmail.com> 
// Feel free to use this code in your own projects, including commercial projects
// License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>
#pragma once

#include <queue>
#include <map>

namespace minos {
template<typename Location, typename Graph>
auto breadth_first_search(Graph graph, Location start) -> std::map<Location, Location> {
    std::queue<Location> frontier;
    std::map<Location, Location> came_from;

    frontier.push(start);
    came_from[start] = start;

    while (!frontier.empty()) {
        Location current = frontier.front();
        frontier.pop();

        for (Location next : graph.neighbors(current)) {
           if (came_from.find(next) == came_from.end()) {
               frontier.push(next);
               came_from[next] = current;
           }
        }
    }

    return came_from;
}
}