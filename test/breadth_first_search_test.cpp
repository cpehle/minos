#include "minos/breadth_first_search.h"
#include "minos/simple_graph.h"
#include "minos/grid_graph.h"

#include <iostream>

minos::SimpleGraph example_graph {{
    {'A', {'B'}},
    {'B', {'A', 'C', 'D'}},
    {'C', {'A'}},
    {'D', {'E', 'A'}},
    {'E', {'B'}}
  }};

int main() {
  auto came_from = minos::breadth_first_search(example_graph, 'A');
  for (auto [key,value] : came_from) {
      std::cout << key << " " << value << std::endl;
  }

  {
    minos::SquareGrid grid = minos::make_diagram1();
    minos::draw_grid(grid, 2);
  }

  {
    minos::SquareGrid grid = minos::make_diagram1();
    auto parents = breadth_first_search(grid, minos::GridLocation{7, 8});
    minos::draw_grid(grid, 2, nullptr, &parents);
  }
}