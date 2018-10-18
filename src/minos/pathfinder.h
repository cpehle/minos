#pragma once

#include "minos/breadth_first_search.h"
#include "minos/dijkstra_search.h"
#include "minos/reconstruct_path.h"

namespace minos {

/// pathfinder algorithm
template<typename Location, typename Graph>
auto pathfinder(Graph graph, std::vector<Location> starts, std::vector<std::vector<Location>> targets) -> std::vector<std::vector<Location>> {
    std::vector<std::vector<Location>> paths;
    paths.reserve(starts.size());

    {
        int idx = 0; 
        for (auto start : starts) {
            auto came_from = breadth_first_search<Location, Graph>(graph, start);
            for (auto target : targets[idx]) {
                paths.push_back(reconstruct_path<Location>(start, target, came_from));
            }
            idx++;
        }
    }

    for (auto path : paths) {
        for (auto location : path) {
            graph.increment_utilization_at(location);
        }
    }

    {
    int iteration = 0; 
    std::cout << iteration << ":" <<  graph.congestion() << std::endl;

    while (graph.congestion() != 0.0) {
        draw_grid(graph, 2, &graph.utilization);
        graph.iteration = iteration;

        int idx = 0;
        for (auto start : starts) {
            auto [came_from, cost_so_far] = dijkstra_search<Location, Graph>(graph, start);
            draw_grid(graph, 2, &cost_so_far);
            for (auto target : targets[idx]) {
                paths[idx] = reconstruct_path(start, target, came_from);
                for (auto vertex : paths[idx]) {
                    graph.increment_utilization_at(vertex);
                }
            }
            idx++;
        }
        graph.reset_utilization();
        for (auto path : paths) {
            for (auto vertex : path) {
                graph.increment_utilization_at(vertex);
            }
        }
        iteration++;
    }
    }

    return paths;
}
}