#include "minos/dijkstra_search.h"
#include "minos/grid_graph.h"
#include "minos/reconstruct_path.h"
#include "minos/pathfinder.h"

int main() {
    minos::GridWithCapacity grid = minos::make_diagram5();
    minos::draw_grid(grid, 2, &grid.capacity);
    std::cout << std::endl;
    minos::draw_grid(grid, 2, &grid.utilization);

    using L = minos::GridLocation;
    std::vector<L> starts = {L{1,4}, L{1,5}};   
    std::vector<std::vector<L>> targets = {
        {L{8, 5}, L{8,8}},
        {L{8, 1}, L{8,5}},
    };

    auto paths = minos::pathfinder(grid, starts, targets);
    std::cout << std::endl;
    minos::draw_grid(grid, 2, nullptr, nullptr, &paths[0]);
    minos::draw_grid(grid, 2, nullptr, nullptr, &paths[1]);
}