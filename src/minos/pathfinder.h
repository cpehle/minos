#pragma once

#include "minos/breadth_first_search.h"
#include "minos/dijkstra_search.h"
#include "minos/reconstruct_path.h"

namespace minos {

/// pathfinder algorithm
template<typename Location, typename Graph>
auto pathfinder(Graph g, std::vector<Location> starts, std::vector<std::vector<Location>> targets) -> std::vector<std::vector<Location>> {
    std::vector<std::vector<Location>> paths;
    paths.reserve(starts.size());

    for (int idx = 0; auto start : starts) {
        auto came_from = breadth_first_search<Location, Graph>(start);
        for (auto target : targets[idx]) {
            auto path = reconstruct_path(start, target, came_from);
            paths[idx].push_back(path);
        }
        idx++;
    }

    for (auto path : paths) {
        for (auto location : path) {
            graph.increment_utilization_at(location);
        }
    }

    while (int iteration = 0; graph.congestion() != 0.0) {
        graph.iteration = iteration;

        for (int idx = 0; auto start : starts) {
            auto [came_from, cost_so_far] = dijkstra_search<Location, Graph>(start);
            for (auto target : targets[idx]) {
                auto path = reconstruct_path(start, target, came_from);
                paths[idx].push_back(path);
            }
            idx++;
        }

        graph.reset_utilization();

        for (auto path : paths) {
            for (int i = 0; i < path.size()-1; i++) {
                graph.increment_utilization_at(path[i], path[i+1]);
            }
        }

        iteration++;
    }

    return paths;
}
}