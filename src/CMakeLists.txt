add_executable(sortalgs
    "main.c"
    "application.c"
    "visualizer.c"
    "visualizers/histogram.c"
    "algorithms/bubblesort.c"
    "algorithms/mergesort.c"
)

target_include_directories(sortalgs PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(sortalgs PRIVATE
    glfw
    glad
    cglm
)