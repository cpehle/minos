// Copyright 2014 Red Blob Games <redblobgames@gmail.com> 
// Feel free to use this code in your own projects, including commercial projects
// License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>

#include "minos/grid_graph.h"

namespace minos {

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) {
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.walls.insert(GridLocation{x, y});
    }
  }
}

void set_capacity(GridWithCapacity& grid, int x1, int y1, int x2, int y2, double capacity) {
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.capacity.emplace(GridLocation{x, y}, capacity);
    }
  }
}

void set_utilization(GridWithCapacity& grid, int x1, int y1, int x2, int y2, double utilization) {
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.utilization.emplace(GridLocation{x, y}, utilization);
    }
  }
}

SquareGrid make_diagram1() {
  SquareGrid grid(30, 15);
  add_rect(grid, 3, 2, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);
  return grid;
}

GridWithWeights make_diagram4() {
  GridWithWeights grid(10, 10);
  add_rect(grid, 1, 7, 4, 9);
  using L = GridLocation;
  grid.forests = std::map<GridLocation, double> {
    {L{3, 4},5.0}, {L{3, 5},5.0},
    {L{4, 1},5.0}, {L{4, 2}, 5.0},
    {L{4, 3}, 5.0}, {L{4, 4}, 5.0}, {L{4, 5}, 5.0}, {L{4, 6}, 5.0},
    {L{4, 7}, 5.0}, {L{4, 8}, 5.0}, {L{5, 1}, 5.0}, {L{5, 2}, 5.0},
    {L{5, 3}, 5.0}, {L{5, 4}, 5.0}, {L{5, 5}, 5.0}, {L{5, 6}, 5.0},
    {L{5, 7}, 5.0}, {L{5, 8}, 5.0}, {L{6, 2}, 5.0}, {L{6, 3}, 5.0},
    {L{6, 4}, 5.0}, {L{6, 5}, 5.0}, {L{6, 6}, 5.0}, {L{6, 7}, 5.0},
    {L{7, 3}, 5.0}, {L{7, 4}, 5.0}, {L{7, 5}, 5.0}
  };
  return grid;
}

GridWithCapacity make_diagram5() {
  GridWithCapacity grid(30, 15);
  add_rect(grid, 3, 2, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);

  set_capacity(grid,0,0,30,15,2.0);
  set_utilization(grid,0,0,30,15,0.0);
  return grid;
}


}
