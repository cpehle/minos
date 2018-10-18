// Copyright 2014 Red Blob Games <redblobgames@gmail.com> 
// Feel free to use this code in your own projects, including commercial projects
// License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>
#pragma once

#include <vector>
#include <map>

namespace minos {
struct SimpleGraph {
  std::map<char, std::vector<char> > edges;

  std::vector<char> neighbors(char id) {
    return edges[id];
  }
};
}