#include "minos/dijkstra_search.h"
#include "minos/grid_graph.h"
#include "minos/reconstruct_path.h"
#include "minos/pathfinder.h"

int main() {
    minos::GridWithCapacity grid = minos::make_diagram5();

    using L = minos::GridLocation;
    std::vector<L> starts = {
        L{0,4},
        L{1,5},
        L{1,6},
        L{10,5},
        L{11,3},
        L{14,4}
    };

    std::vector<std::vector<L>> targets = {
        {L{8, 5}},
        {L{8, 7}},
        {L{9, 8}},
        {L{12,13}},
        {L{10,13}},
        {L{10, 5}},
    };

    auto paths = minos::pathfinder(grid, starts, targets);
    for (auto path : paths) {
        minos::draw_grid(grid, 1, nullptr, nullptr, &path);
        std::cout << std::endl;
    }
}