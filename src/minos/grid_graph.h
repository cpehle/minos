// Copyright 2014 Red Blob Games <redblobgames@gmail.com> 
// Feel free to use this code in your own projects, including commercial projects
// License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>
#pragma once
#include <vector>
#include <array>
#include <set>
#include <map>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace minos {
struct GridLocation {
  int x, y;

  bool operator == (const GridLocation& b) const {
    return x == b.x && y == b.y;
  }
  
  bool operator != (const GridLocation& b) const {
    return !(*this == b);
  }
  
  bool operator < (const GridLocation& b) const {
    return std::make_pair(x,y) < std::make_pair(b.x, b.y);
  }

  std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out) {
      out << '(' << x << ',' << y << ')';
      return out;
  }
};

struct SquareGrid {
  const std::array<GridLocation, 4> DIRS = {GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1}};

  int width, height;
  std::set<GridLocation> walls;

  SquareGrid(int width_, int height_)
     : width(width_), height(height_) {}

  bool in_bounds(GridLocation id) const {
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
  }

  bool passable(GridLocation id) const {
    return walls.find(id) == walls.end();
  }

  std::vector<GridLocation> neighbors(GridLocation id) const {
    std::vector<GridLocation> results;

    for (GridLocation dir : DIRS) {
      GridLocation next{id.x + dir.x, id.y + dir.y};
      if (in_bounds(next) && passable(next)) {
        results.push_back(next);
      }
    }

    if ((id.x + id.y) % 2 == 0) {
      // aesthetic improvement on square grids
      std::reverse(results.begin(), results.end());
    }

    return results;
  }
};

// Helpers for GridLocation


// This outputs a grid. Pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path.
template<class Graph>
void draw_grid(const Graph& graph, int field_width,
               std::map<GridLocation, double>* distances = nullptr,
               std::map<GridLocation, GridLocation>* point_to = nullptr,
               std::vector<GridLocation>* path = nullptr) {
  for (int y = 0; y != graph.height; ++y) {
    for (int x = 0; x != graph.width; ++x) {
      GridLocation id {x, y};
      std::cout << std::left << std::setw(field_width);
      if (graph.walls.find(id) != graph.walls.end()) {
        std::cout << std::string(field_width, '#');
      } else if (point_to != nullptr && point_to->count(id)) {
        GridLocation next = (*point_to)[id];
        if (next.x == x + 1) { std::cout << "> "; }
        else if (next.x == x - 1) { std::cout << "< "; }
        else if (next.y == y + 1) { std::cout << "v "; }
        else if (next.y == y - 1) { std::cout << "^ "; }
        else { std::cout << "* "; }
      } else if (distances != nullptr && distances->count(id)) {
        std::cout << (*distances)[id];
      } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
        std::cout << '@';
      } else {
        std::cout << '.';
      }
    }
    std::cout << '\n';
  }
}

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2);

struct GridWithWeights: SquareGrid {
  std::set<GridLocation> forests;
  GridWithWeights(int w, int h): SquareGrid(w, h) {}
  double cost(GridLocation from_node, GridLocation to_node) const {
    return forests.find(to_node) != forests.end()? 5 : 1;
  }
};

struct GridWithCapacity: SquareGrid {
  std::map<GridLocation, double> capacity;
  std::map<GridLocation, double> utilization;
  int iteration;

  GridWithCapacity(int w, int h) : SquareGrid(w, h) , iteration(0) {}
  double cost(GridLocation from_node, GridLocation to_node) const {
    auto cap = capacity.find(to_node);
    auto util = utilization.find(to_node);
    double base_cost = 1.0;

    if (cap != capacity.end() && util != utilization.end()) {
        double penalty = std::max(util->second - cap->second, 0.0);
        return base_cost * (1 + iteration * penalty);
    } else if (cap != capacity.end()) { 
        return base_cost;
    } else {
        return 100.0 * iteration * iteration;
    }
  }

  double congestion() {
    double congestion = 0.0;
    for (auto [vertex,util] : utilization) {
      auto cap = capacity.find(vertex);
      if (cap != capacity.end()) {
        double penalty = std::max(util - cap->second, 0.0);
        congestion += penalty;
      }
    }
    return congestion;
  }

  void reset_utilization() {
    for (auto& [vertex,util] : utilization) {
      util = 0.0;
    }
  }

  void increment_utilization_at(GridLocation node) {
      utilization[node] += 1.0;
  }
};

void set_capacity(GridWithCapacity& grid, int x1, int y1, int x2, int y2, double capacity);
void set_utilization(GridWithCapacity& grid, int x1, int y1, int x2, int y2, double utilization);

SquareGrid make_diagram1();
GridWithWeights make_diagram4();
GridWithCapacity make_diagram5();

}