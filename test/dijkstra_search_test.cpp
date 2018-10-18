#include "minos/dijkstra_search.h"
#include "minos/grid_graph.h"
#include "minos/reconstruct_path.h"

int main() {
  minos::GridWithWeights grid = minos::make_diagram4();
  minos::GridLocation start{1, 4};
  minos::GridLocation goal{8, 5};

  auto [came_from, cost_so_far] = minos::dijkstra_search(grid, start);
  minos::draw_grid<minos::GridWithWeights>(grid, 2, nullptr, &came_from);
  std::cout << '\n';
  minos::draw_grid(grid, 3, &cost_so_far, nullptr);
  std::cout << '\n';
  auto path = minos::reconstruct_path(start, goal, came_from);
  minos::draw_grid(grid, 3, nullptr, nullptr, &path);
}