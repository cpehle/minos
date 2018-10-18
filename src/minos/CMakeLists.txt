add_library(minos
    simple_graph.h
    a_star_search.h
    breadth_first_search.h
    CMakeLists.txt
    dijkstra_search.h
    pathfinder.h
    priority_queue.h
    reconstruct_path.h
    grid_graph.h
    grid_graph.cpp
)

target_include_directories(minos PUBLIC "${PROJECT_SOURCE_DIR}/src")
