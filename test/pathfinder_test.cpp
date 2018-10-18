#include "minos/dijkstra_search.h"
#include "minos/grid_graph.h"
#include "minos/reconstruct_path.h"
#include "minos/pathfinder.h"

int main() {
    minos::GridWithCapacity grid = minos::make_diagram5();
    minos::draw_grid(grid, 2, nullptr);
}